#pragma once
#include "afxwin.h"


// диалоговое окно CTestDlg

class CTestDlg : public CDialog
{
	DECLARE_DYNAMIC(CTestDlg)

public:
	CTestDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CTestDlg();
	virtual BOOL OnInitDialog();

	CString LintToCStr(long int x);
// Данные диалогового окна
	enum { IDD = IDD_TEST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CEdit m_IniDetEdit;
	CEdit m_IniDivEdit;
	CEdit m_GetExeEdit;
	CEdit m_GetExePathEdit;
	CEdit m_CreatePathEdit;
	CStatic m_CreatePathStatus;
	CEdit m_nError;
};
