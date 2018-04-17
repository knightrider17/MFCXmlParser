// TestDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "SOU-Generator.h"
#include "TestDlg.h"
#include "afxdialogex.h"
#include "helpful.h"

// диалоговое окно CTestDlg

IMPLEMENT_DYNAMIC(CTestDlg, CDialog)

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
{

}

CTestDlg::~CTestDlg()
{
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INI_DET_EDIT, m_IniDetEdit);
	DDX_Control(pDX, IDC_INI_DIV_EDIT, m_IniDivEdit);
	DDX_Control(pDX, IDC_GET_EXE_EDIT, m_GetExeEdit);
	DDX_Control(pDX, IDC_GET_PATH_EDIT, m_GetExePathEdit);
	DDX_Control(pDX, IDC_SET_PATH_EDIT, m_CreatePathEdit);
	DDX_Control(pDX, IDC_CREATE_STATUS, m_CreatePathStatus);
	DDX_Control(pDX, IDC_EDIT6, m_nError);
}


BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CTestDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTestDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// обработчики сообщений CTestDlg


BOOL CTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	CString EmptyStr("");
	CString Edit1(""), Edit2(""), Edit3(""), Edit4(""), Edit5(""), Edit6("");

	// 2 Проходимся по ini-файлу
	// 2.1 Проверяем указан ли в ini-файле путь к XML-файлу со списком датчиков
	TCHAR IniFileName[_MAX_PATH];
	::GetModuleFileName(AfxGetApp()->m_hInstance, IniFileName, MAX_PATH);


	m_GetExeEdit.SetWindowText(IniFileName);
	Edit1 = Edit1 + IniFileName + _T("\n");
/////////////////////////////////////////////////////////////////////////////////////

	TCHAR* szExt = _tcsrchr(IniFileName, '.');


	CString OurPath = IniFileName;
	m_GetExePathEdit.SetWindowText(OurPath);
	Edit2 = Edit2 + OurPath + _T("\n");


	if(szExt) *(szExt+1) = 0;
	//приставить расширение
	_tcscat_s(IniFileName, _MAX_PATH, _T("ini"));
	//1 theApp // Путь до ini-файла, включающий имя самого файла в этом пути
	theApp.IniFileName = IniFileName;

////////////////////////////////////////////////////////////////////////////////////


	CIniParam AppDetectorsPath(IniFileName, _T("Program"), _T("DetectorPath"), EmptyStr);	 // Датчики
	//2,3 theApp // Путь к XML-файлу со списком Датчиков, включающий имя самого файла в этом пути //2 ВЗЯТЫЙ из ini-файла //3 Текущий
	m_IniDetEdit.SetWindowText( AppDetectorsPath.AsString() );
	Edit3 = Edit3 + AppDetectorsPath.AsString() + _T("\n");

/////////////////////////////////////////////////////////////////////////////////////

	// По умолчанию при первом запуске, и создании ini-файла задаём в него путь до папки Участков в том же месте где и EXE-шник утилиты
	CIniParam AppDivisionsPath(IniFileName, _T("Program"), _T("DivisionsPath"), EmptyStr); // Участки
	//4,5 theApp // Путь к файлам (*.sou) Участков, в конце пути по умолчанию установлено "\Участки", ВЗЯТЫЙ из ini-файла //4 ВЗЯТЫЙ из ini-файла //5 Текущий
	m_IniDivEdit.SetWindowText( AppDivisionsPath.AsString() );
	Edit4 = Edit3 + AppDetectorsPath.AsString() + _T("\n");
/////////////////////////////////////////////////////////////////////////////////////


	TCHAR DivPathName[_MAX_PATH];
	::GetModuleFileName(AfxGetApp()->m_hInstance, DivPathName, MAX_PATH);
	TCHAR* szExtbs = _tcsrchr(DivPathName, '\\');
	if(szExtbs) *(szExtbs+1) = 0;
	//приставить конец пути, который должен заканчиваться папкой "Участки"
	_tcscat_s(DivPathName, _MAX_PATH, _T("Участки"));

	m_CreatePathEdit.SetWindowText( AppDivisionsPath.AsString() );

	// Создаём папку "Участки" по тому пути, что указан в ini-файле
	if( CreateDirectory(AppDivisionsPath.AsString(), NULL) == ERROR_ALREADY_EXISTS )//== GetLastError())
	{
		//AfxMessageBox(_T("Folder allready exists"));
		m_CreatePathStatus.SetWindowText(_T("Created"));
	}
	else
	{// Failed to create directory.
		m_CreatePathStatus.SetWindowText(_T("NotCreated"));
		long nError = CreateDirectory(AppDivisionsPath.AsString(), NULL);

		m_nError.SetWindowText(LintToCStr(nError));
		//AfxMessageBox(_T("Created directory."));
	}


	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}



void CTestDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialog::OnOK();
}


void CTestDlg::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialog::OnCancel();
}


// Прочие методы для Конвертирования
CString CTestDlg::LintToCStr(long int x)
{
	CString strX;
	strX.Format( _T("%i"), x ); //%i for int // %d for ?? // %l for long
	return strX;
}