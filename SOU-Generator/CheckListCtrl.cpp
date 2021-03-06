// CheckListCtrl.cpp: ���� ����������
//

#include "stdafx.h"
#include "SOU-Generator.h"
#include "CheckListCtrl.h"


// CCheckListCtrl

IMPLEMENT_DYNAMIC(CCheckListCtrl, CListCtrl)

CCheckListCtrl::CCheckListCtrl() : m_blInited(FALSE)
{
}

//CCheckListCtrl::CCheckListCtrl()
//{
//	m_blInited = FALSE;
//}

CCheckListCtrl::~CCheckListCtrl()
{
}


BEGIN_MESSAGE_MAP(CCheckListCtrl, CListCtrl)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckListCtrl message handlers
void CCheckListCtrl::OnItemChanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLISTVIEW* pNMLV = (NMLISTVIEW*)pNMHDR;
	*pResult = 0;

	if ( m_blInited && LVIF_STATE == pNMLV->uChanged)
	{
		BOOL blAllChecked = TRUE;
		int nCount = GetItemCount();
		for(int nItem = 0; nItem < nCount; nItem++)
		{
			if ( !ListView_GetCheckState(GetSafeHwnd(), nItem) )
			{
				blAllChecked = FALSE;
				break;
			}
		}
		
		HDITEM hdItem;
		hdItem.mask = HDI_IMAGE;
		if (blAllChecked)
			hdItem.iImage = 2;
		else
			hdItem.iImage = 1;
		VERIFY( m_checkHeadCtrl.SetItem(0, &hdItem) );
	}

}

BOOL CCheckListCtrl::Init()
{
	if (m_blInited)
		return TRUE;

	CHeaderCtrl* pHeadCtrl = this->GetHeaderCtrl();
	ASSERT(pHeadCtrl->GetSafeHwnd());

	VERIFY( m_checkHeadCtrl.SubclassWindow(pHeadCtrl->GetSafeHwnd()) );
	VERIFY( m_checkImgList.Create(IDB_CHECKBOXES, 16, 3, RGB(255,0,255)) );
	int i = m_checkImgList.GetImageCount();
	m_checkHeadCtrl.SetImageList(&m_checkImgList);
	
	HDITEM hdItem;
	hdItem.mask = HDI_IMAGE | HDI_FORMAT;
	VERIFY( m_checkHeadCtrl.GetItem(0, &hdItem) );
	hdItem.iImage = 1;
	hdItem.fmt |= HDF_IMAGE;
	
	VERIFY( m_checkHeadCtrl.SetItem(0, &hdItem) );

	m_blInited = TRUE;

	return TRUE;
}

// ����������� ��������� CheckListCtrl


