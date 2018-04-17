#pragma once
#include "afxwin.h"


// ���������� ���� CTestDlg

class CTestDlg : public CDialog
{
	DECLARE_DYNAMIC(CTestDlg)

public:
	CTestDlg(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CTestDlg();
	virtual BOOL OnInitDialog();

	CString LintToCStr(long int x);
// ������ ����������� ����
	enum { IDD = IDD_TEST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

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
