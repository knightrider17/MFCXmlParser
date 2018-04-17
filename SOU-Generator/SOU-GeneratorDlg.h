// SOU-GeneratorDlg.h : ���� ���������
//

// ������: ���� ���� � ini ������, �� ��������� ���������� �� ����� � ����� � ���. ���� ����� ��� 
// (������ �� ���� ��������� "�������� ���� � ����� � ��������� �� ���� "�� ����������" - "��/���"), �� 
// ���������� ����, ��� ��� �������� � ini � ������������ �� ���� "�� ���������" ����� � exe � ������� ����� ���.
// ��������� ������ "���������".

#pragma once
#include "afxwin.h"
#include <sql.h>
#include <sqlext.h>
#include <stdio.h>
#include <tchar.h>

#pragma comment(lib,"odbc32.lib")

//#include "CheckListCtrl.h"



// ���������� ���� CSOUGeneratorDlg
class CSOUGeneratorDlg : public CDialog//Ex
						 //public CWinApp
{
// ��������
public:

	CSOUGeneratorDlg(CWnd* pParent = NULL);	// ����������� �����������
	//CString DocErrorGetErrorInRus(CString DescriptionEng);
//    static  LRESULT CALLBACK    MainWndProc(HWND, UINT, WPARAM, LPARAM);
	static  LRESULT CALLBACK    MainWndProc( HWND hwndMain, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void readDetectorsFile(CString bstrXMLFile);
	void GetAndCheckDetectorsFile();

	bool writeDetectorsFile(CString bstrXMLFile);

	BOOL PreTranslateMessage(LPMSG pMgs);
    //static PTCHAR pchInputBuf; // ����� �����
    PTCHAR pchInputBuf; // ����� �����
	
	HWND TestDlgHWND;


	// All Parametrs and Functions that we need for SQL-Version
	bool Connect();
	bool DBGetDetectors();
	void DisConnect();

	CString ConnectStep;
	void LogConnectionStatus(CString Step, CString ParamsOrErrReason, bool bError);
	//void ConnectionFailed(CString Reason);
	//CString NumToCStr(uint64_t Num);

	CString Driver_St_CStr;
	CString Server_St_CStr;
	CString DB_St_CStr;
	CString UID_St_CStr;
	CString PWD_St_CStr;
	CString TrCon_St_CStr;
	CString APP_St_CStr;

	CString Driver_CStr;
	CString Server_CStr;
	CString DB_CStr;
	CString UID_CStr;
	CString PWD_CStr;
	CString TrCon_CStr;
	CString APP_CStr;

	CString ConnectStr_CStr;

	bool bConnect;

	SQLHANDLE henv;
	SQLHDBC	  hdbc; // dbc
	SQLHSTMT  hstmt; // ��������� �� �����

    SQLSMALLINT bufsize;
    SQLINTEGER nativeerror;
    SQLSMALLINT textlen;
	SQLRETURN retcode;


	CString DBMes_CStr;

	SQLTCHAR *selecttxt;
	(SQLWCHAR *) conn;
	//wchar_t *conn;
	//SQLCHAR *selecttxt;
	//char *conn;

	std::vector<CString> v_SQLTopStr; // "�����" � ���������� ��������
	std::vector<std::vector<CString>> v_SQLFullTable; 


// ������ ����������� ����
	enum { IDD = IDD_SOUGENERATOR_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV

// ����������
protected:
	HICON m_hIcon;

	bool WndDivisionOpen;
	bool WndDivisionChange;
	//CString NumToCStr(uint64_t Num);
	CString LintToCStr(long int x);
	CString DoubleToCStr(double x, int count); // x - �����, count - ����� ������ ����� �������
	char* CStrAToChar(CStringA origa);
	char* CStrWToChar(CStringW origw);

	// ��������� ������� ����� ���������
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	//bool FileExists(LPCTSTR fname);
	bool FileExists(const wchar_t *fname);

public:
	CStatic m_TextText; //������� ���������
	CButton m_BtnOK; //������� ���������

	CEdit m_EditTest;
	CStatic m_TitlePath;
	CButton m_BtnDetectorsPath;
	CButton m_BtnDivisionChange;
	CButton m_BtnDivisionOpen;
	CButton m_BtnCancel;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedDetectorsPath();
	afx_msg void OnBnClickedOpenDetectors();
	afx_msg void OnBnClickedChangeDetectors();
	afx_msg void OnBnClickedDivisionOpen();
	afx_msg void OnBnClickedDivisionChange();
	afx_msg void OnEnChangeTestEdit();

	afx_msg LRESULT OnDivisionOpenExit( WPARAM wparam , LPARAM lparam );
	afx_msg LRESULT OnDivisionChangeExit( WPARAM wparam , LPARAM lparam );
	afx_msg LRESULT OnDetectprsPathCheck( WPARAM wparam , LPARAM lparam );

	afx_msg void OnBnClickedTestBtn();
};