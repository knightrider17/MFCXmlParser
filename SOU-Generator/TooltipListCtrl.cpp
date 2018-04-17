// TooltipListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "TooltipListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTooltipListCtrl

CTooltipListCtrl::CTooltipListCtrl()
{
}

CTooltipListCtrl::~CTooltipListCtrl()
{
}


BEGIN_MESSAGE_MAP(CTooltipListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CTooltipListCtrl)
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetdispinfo)
	//}}AFX_MSG_MAP
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTooltipListCtrl message handlers


//---------------------------------------------------
/*
int CTooltipListCtrl::InsertItemTip( int nRow, CString sTip )
{
  if (nRow < 0)
    return -1;

  if ( nRow < m_pComboParent->GetCount( ) )	
  {
    for (int i = m_pComboParent->GetCount( ) - 1; i >= nRow; --i)
      m_itemToTip[nRow + 1] = GetItemTip(i);
  }

  m_itemToTip[nRow] = sTip;

  return nRow;
}
//*/
//----------------------------------------------------

// Additional code from Paul Garber (codeguru.com) required to correctly order tooltips for sorted lists.
int CTooltipListCtrl::InsertItemTip( int nRow, CString sTip)
{
  if (nRow < 0)
    return -1;

  if ( nRow < m_pComboParent->GetCount( ) )	
  {
    for (int i = m_pComboParent->GetCount( ) - 1; i >= nRow; --i)
	{
		// AJY Serious but obvious BUG: m_itemToTip[nRow + 1] = GetItemTip(i);
		// Shuffle existing tips at the end of the list along to squeeze new one into the correct place.
		int idxNew = i + 1;	// Templates can't handle expressions in-line.
		m_mpItemToTip[idxNew] = (CString)GetItemTip(i);
	}
  }

  m_mpItemToTip[nRow] = sTip;
  return nRow;
}


/*
void CTooltipListCtrl::OnKillFocus(CWnd* pNewWnd) 
{
	CPoint point;
	GetCursorPos( &point );
	CWnd *pWnd = WindowFromPoint( point );
	if ( pWnd->GetSafeHwnd( ) != m_pComboParent->GetSafeHwnd( ) )
		ShowWindow( SW_HIDE );
	m_pComboParent->SetCurSel( m_nLastItem );
	m_pComboParent->SetFocus( );

	CListCtrl::OnKillFocus( pNewWnd );
}
*/

void CTooltipListCtrl::OnKillFocus(CWnd* pNewWnd) 
{
	CPoint point;
	GetCursorPos( &point );
	CWnd *pWnd = WindowFromPoint( point );
	if ( pWnd->GetSafeHwnd( ) != m_pComboParent->GetSafeHwnd( ) )
	{
		ShowWindow( SW_HIDE );
		// AJY Start fix.
		CWnd *pParentDlg = m_pComboParent->GetParent(); // The parent's parent (typically the dialog window)
		pParentDlg->PostMessage(WM_COMMAND,MAKELONG(m_pComboParent->GetDlgCtrlID(), CBN_SELCHANGE),(LPARAM)m_pComboParent->m_hWnd);
                // AJY End Fix.
	}
	m_pComboParent->SetCurSel( m_nLastItem );
	m_pComboParent->SetFocus( );

	CListCtrl::OnKillFocus( pNewWnd );
}


void CTooltipListCtrl::Init( CComboBox *pComboParent )
{
	m_pComboParent = pComboParent;

	InsertColumn( 0, _T("") );
}

void CTooltipListCtrl::Display(CRect rc)
{
	m_nLastItem = m_pComboParent->GetCurSel( );

	int nCount = m_pComboParent->GetCount( );
	SetItemCountEx( nCount );

	int nHeight = rc.Height( );
	int nColumnWidth = rc.Width( );
	CRect rcItem;
	if ( nCount )	{
		GetItemRect( 0, &rcItem, LVIR_BOUNDS );
		nHeight = nCount * rcItem.Height( );

		if ( nHeight > rc.Height( ) )	{
			nHeight = rcItem.Height( ) * ( rc.Height( ) / rcItem.Height( ) );
			nColumnWidth -= GetSystemMetrics( SM_CXVSCROLL );
		}
	}
	rc.bottom = rc.top + nHeight + 4;


	SetWindowPos( &wndNoTopMost, rc.left, rc.top, rc.Width( ), rc.Height( ), SWP_SHOWWINDOW );
	SetColumnWidth( 0, nColumnWidth );
	int nCurSel = m_pComboParent->GetCurSel( );
	SetItemState( nCurSel, LVIS_SELECTED | LVIS_FOCUSED, ( UINT )-1 );
	Scroll( CSize( 0, nCurSel * rcItem.Height( ) ) );

	CWnd* pTopParent = m_pComboParent->GetParentOwner( );
    if ( pTopParent != NULL )	{
		pTopParent->SendMessage( WM_NCACTIVATE, TRUE );
		pTopParent->SetRedraw( TRUE );
	}
}

void CTooltipListCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CListCtrl::OnLButtonDown( nFlags, point );

	UINT uFlags;
	HitTest( point, &uFlags );
	if ( ( uFlags & LVHT_ONITEMICON ) |
		 ( uFlags & LVHT_ONITEMLABEL ) |
		 ( uFlags & LVHT_ONITEMSTATEICON ) )	{
		POSITION pos = GetFirstSelectedItemPosition( );
		int nItem = GetNextSelectedItem( pos );
		m_nLastItem = nItem;
		m_pComboParent->SetFocus( );
	}
}

void CTooltipListCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	UINT uFlags;
	int nItem = HitTest( point, &uFlags );
	if ( nItem != -1 )	{
		CListCtrl::SetItemState( nItem, LVIS_SELECTED | LVIS_FOCUSED, ( UINT )-1 );
	}

	CListCtrl::OnMouseMove( nFlags, point );
}

BOOL CTooltipListCtrl::PreTranslateMessage(MSG* pMsg) 
{
	if ( pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE &&
		 pMsg->hwnd == m_hWnd )	{
		ShowWindow( SW_HIDE );
		return TRUE;
	}
	else if ( pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN &&
			  pMsg->hwnd == m_hWnd )	{
		POSITION pos = GetFirstSelectedItemPosition( );
		int nItem = GetNextSelectedItem( pos );
		m_nLastItem = nItem;
		m_pComboParent->SetFocus( );
		return TRUE;
	}
	else if ( pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_LEFT &&
			  pMsg->hwnd == m_hWnd )	{
		pMsg->wParam = VK_UP;
	}
	else if ( pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RIGHT &&
			  pMsg->hwnd == m_hWnd )	{
		pMsg->wParam = VK_DOWN;
	}

	return CListCtrl::PreTranslateMessage(pMsg);
}

void CTooltipListCtrl::PreSubclassWindow() 
{
	EnableToolTips( );

	CListCtrl::PreSubclassWindow();
}

int CTooltipListCtrl::OnToolHitTest( CPoint point, TOOLINFO* pTI ) const
{
	POSITION pos = GetFirstSelectedItemPosition( );
	if ( !pos )
		return -1;
	int nItem = GetNextSelectedItem( pos );
	CRect rcItem;
	GetItemRect( nItem, rcItem, LVIR_BOUNDS );

	pTI->hwnd = m_hWnd;
	pTI->uId = ( UINT )( nItem + 1 );
	pTI->lpszText = LPSTR_TEXTCALLBACK;

	pTI->rect = rcItem;

	return pTI->uId;
}

BOOL CTooltipListCtrl::OnToolTipText( UINT id, NMHDR * pNMHDR, LRESULT * pResult )
{
	// need to handle both ANSI and UNICODE versions of the message
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	CString sTipText;
	UINT nID = pNMHDR->idFrom;

	if( nID == 0 )	  	// Notification in NT from automatically
		return FALSE;   	// created tooltip

	int nRow = nID - 1;
	sTipText = GetItemTip( nRow );

#ifndef _UNICODE
	if (pNMHDR->code == TTN_NEEDTEXTA)
		lstrcpyn(pTTTA->szText, sTipText, 80);
	else
		_mbstowcsz(pTTTW->szText, sTipText, 80);
#else
	if (pNMHDR->code == TTN_NEEDTEXTA)
		_wcstombsz(pTTTA->szText, sTipText, 80);
	else
		lstrcpyn(pTTTW->szText, sTipText, 80);
#endif
	*pResult = 0;

	return TRUE;    // message was handled
}

CString CTooltipListCtrl::GetItemTip(int nRow) const
{
	CString sResult;

	m_mpItemToTip.Lookup( nRow, sResult );

	return sResult;
}

int CTooltipListCtrl::SetItemTip(int nRow, CString sTip)
{
	if ( nRow < m_pComboParent->GetCount( ) )
	{
		m_mpItemToTip[ nRow ] = sTip;
		return nRow;
	}

	return -1;
}

void CTooltipListCtrl::OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;

	if ( pDispInfo->item.iItem != -1 )	{
		if ( pDispInfo->item.mask & LVIF_TEXT )	{
			CString sText;
			m_pComboParent->GetLBText( pDispInfo->item.iItem, sText );
			//strcpy( pDispInfo->item.pszText, sText );
			wcscpy( pDispInfo->item.pszText, sText );
		}
	}

	*pResult = 0;
}
