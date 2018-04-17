// CheckHeadCtrl.cpp: файл реализации
//

#include "stdafx.h"
#include "SOU-Generator.h"
#include "CheckHeadCtrl.h"


/////////////////////////////////////////////////////////////////////////////
// CCheckHeadCtrl

CCheckHeadCtrl::CCheckHeadCtrl()
{
}

CCheckHeadCtrl::~CCheckHeadCtrl()
{
}


BEGIN_MESSAGE_MAP(CCheckHeadCtrl, CHeaderCtrl)
	//{{AFX_MSG_MAP(CCheckHeadCtrl)
	ON_NOTIFY_REFLECT(HDN_ITEMCLICK, OnItemClicked)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckHeadCtrl message handlers
void CCheckHeadCtrl::OnItemClicked(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMHEADER* pNMHead = (NMHEADER*)pNMHDR;
	*pResult = 0;

	int nItem = pNMHead->iItem;
	if (0 != nItem)
		return;

	HDITEM hdItem;
	hdItem.mask = HDI_IMAGE;
	VERIFY( GetItem(nItem, &hdItem) );

	if (hdItem.iImage == 1)
		hdItem.iImage = 2;
	else
		hdItem.iImage = 1;

	VERIFY( SetItem(nItem, &hdItem) );
	
	BOOL bl = hdItem.iImage == 2 ? TRUE : FALSE;
	CListCtrl* pListCtrl = (CListCtrl*)GetParent();
	int nCount = pListCtrl->GetItemCount();	
	for(nItem = 0; nItem < nCount; nItem++)
	{
		ListView_SetCheckState(pListCtrl->GetSafeHwnd(), nItem, bl);
	}
	
}

// обработчики сообщений CCheckHeadCtrl


