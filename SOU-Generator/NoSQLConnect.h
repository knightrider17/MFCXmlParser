#pragma once
#include "afxwin.h"


// ���������� ���� CNoSQLConnect

class CNoSQLConnect : public CDialog
{
	DECLARE_DYNAMIC(CNoSQLConnect)

public:
	CNoSQLConnect(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CNoSQLConnect();
	virtual BOOL OnInitDialog();

	//void SetErrorString(CString ErrorString);
	//CString ErrorString_CStr;

// ������ ����������� ����
	enum { IDD = IDD_NO_SQL_CONNECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()

public:
	CButton m_BrnExit;
	CButton m_BtnGoXML;
	CButton m_BtnRetry;
	CStatic m_TextErrConnect;

	afx_msg void OnBnClickedBtnRetry();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnStnClickedTextErrConnect();
};
