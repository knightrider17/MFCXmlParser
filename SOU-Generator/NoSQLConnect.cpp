// NoSQLConnect.cpp: файл реализации
//

#include "stdafx.h"
#include "SOU-Generator.h"
#include "NoSQLConnect.h"
#include "afxdialogex.h"


// диалоговое окно CNoSQLConnect

IMPLEMENT_DYNAMIC(CNoSQLConnect, CDialog)

CNoSQLConnect::CNoSQLConnect(CWnd* pParent /*=NULL*/)
	: CDialog(CNoSQLConnect::IDD, pParent)
{

}

CNoSQLConnect::~CNoSQLConnect()
{
}

void CNoSQLConnect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXT_ERR_CONNECT, m_TextErrConnect);
	DDX_Control(pDX, IDC_BTN_RETRY, m_BtnRetry);
	DDX_Control(pDX, IDOK, m_BtnGoXML);
	DDX_Control(pDX, IDCANCEL, m_BrnExit);
}


BEGIN_MESSAGE_MAP(CNoSQLConnect, CDialog)
	ON_BN_CLICKED(IDC_BTN_RETRY, &CNoSQLConnect::OnBnClickedBtnRetry)
	ON_BN_CLICKED(IDOK, &CNoSQLConnect::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CNoSQLConnect::OnBnClickedCancel)
	ON_STN_CLICKED(IDC_TEXT_ERR_CONNECT, &CNoSQLConnect::OnStnClickedTextErrConnect)
END_MESSAGE_MAP()


// обработчики сообщений CNoSQLConnect

BOOL CNoSQLConnect::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	CString EmptyCStr("");
	if(theApp.ConnectOrDB_Error != EmptyCStr)
	{
		SetWindowText(theApp.ConnectOrDB_Step);
		theApp.ConnectOrDB_Step.Empty();

		m_TextErrConnect.SetWindowText(theApp.ConnectOrDB_Error);
		theApp.ConnectOrDB_Error.Empty();
	}

	return TRUE;
}

//void CNoSQLConnect::SetErrorString(CString ErrorString)
//{
	// TODO: добавьте свой код обработчика уведомлений
//	ErrorString_CStr = ErrorString;
//	m_TextErrConnect.SetWindowText(ErrorString_CStr);
//}


void CNoSQLConnect::OnBnClickedBtnRetry()
{
	// TODO: добавьте свой код обработчика уведомлений
	//CDialog::SendMessage(IDRETRY);
	//CDialog::CloseWindow();
	//CDialog::OnClose();
	EndDialog(IDRETRY);
}


void CNoSQLConnect::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialog::OnOK();
}


void CNoSQLConnect::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialog::OnCancel();
}


void CNoSQLConnect::OnStnClickedTextErrConnect()
{
	// TODO: добавьте свой код обработчика уведомлений
}
