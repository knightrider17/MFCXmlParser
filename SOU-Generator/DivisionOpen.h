#pragma once
#include "afxwin.h"
//#include "afxcmn.h"
#include "CheckListCtrl.h"

#include <vector>

// диалоговое окно CDivisionOpen

class CDivisionOpen : public CDialog
{
	DECLARE_DYNAMIC(CDivisionOpen)

public:
	CDivisionOpen(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CDivisionOpen();

// Данные диалогового окна
	enum { IDD = IDD_DIVISION_OPEN_DLG };

protected:
	std::vector<bool> AllDivisions;

	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	//CListCtrl m_DivOpenList;
	CCheckListCtrl	m_DivOpenListCtrl;
	//CListCtrl m_DivOpenListCtrl;
	CButton m_BtnDivOpen;
	CButton m_BtnDiv_Exit;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnLvnItemchangedDevOpenList(NMHDR *pNMHDR, LRESULT *pResult);
};
