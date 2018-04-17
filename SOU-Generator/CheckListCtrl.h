#pragma once

#include "CheckHeadCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CCheckListCtrl

class CCheckListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CCheckListCtrl)

// Construction
public:
	CCheckListCtrl();

// Attributes
public:
	
// Operations
private:
	BOOL	m_blInited;
	CImageList	m_checkImgList;


public:
	BOOL Init();

protected:
	CCheckHeadCtrl	m_checkHeadCtrl;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCheckListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCheckListCtrl)
	afx_msg void OnItemChanged(NMHDR* pNMHDR, LRESULT* pResult);		
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


