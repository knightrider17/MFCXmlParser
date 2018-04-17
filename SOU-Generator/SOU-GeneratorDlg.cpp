
// SOU-GeneratorDlg.cpp : ���� ����������
//

#include "stdafx.h"
#include "SOU-Generator.h"
#include "SOU-GeneratorDlg.h"
#include "afxdialogex.h"
#include "afxwin.h"

#include "DetectorsPath.h"
#include "DivisionOpen.h"
#include "DivisionChoose.h"
#include "DivisionEdit.h"

#include "TestDlg.h"

#include "helpful.h"
#include <io.h>
#include <Psapi.h>

#include "TElem.h"
#include "NoSQLConnect.h"

#define BUFSIZE 65535
#define SHIFTED 0x8000

/*
#define DIV_DET_NAME	0
#define DIV_DET_NUMBER	1
#define DIV_DET_ACTIVE	2
#define DIV_DET_PATH	3
#define DIV_DET_PTFIX	4
#define DIV_DET_DIST	5
#define DIV_DET_DPRESS	6
#define DIV_DET_DTIIME	7
*/

#define DIV_DET_NUMBER		0
#define DIV_DET_NAME		1
#define DIV_DET_PTFIX		2
#define DIV_DET_DIST		3
#define DIV_DET_PATH		4
#define DIV_DET_PRODTYPE	5
#define DIV_DET_PRODID		6
#define DIV_DET_PRODVIEW	7
#define DIV_DET_WAVESPEED	8
#define DIV_DET_PIPEID		9
#define DIV_DET_PIPESHNAME	10
#define DIV_DET_PIPELENGHT	11
#define DIV_DET_BEGINNAME	12
#define DIV_DET_ENDINGNAME	13

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ���������� ���� CAboutDlg ������������ ��� �������� �������� � ����������

class CAboutDlg : public CDialog//Ex
				  //public CWinApp
{
public:
	CAboutDlg();

// ������ ����������� ����
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

// ����������
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// ���������� ���� CSOUGeneratorDlg




CSOUGeneratorDlg::CSOUGeneratorDlg(CWnd* pParent /*=NULL*/)
		: CDialog(CSOUGeneratorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	WndDivisionOpen=true;
	WndDivisionChange=true;
}

void CSOUGeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_BtnOK);
	DDX_Control(pDX, IDCANCEL, m_BtnCancel);
	DDX_Control(pDX, IDC_TEXTTEXT, m_TextText);
	DDX_Control(pDX, IDC_TITLE_PATH, m_TitlePath);
	DDX_Control(pDX, IDC_DETECTORS_PATH, m_BtnDetectorsPath);
	DDX_Control(pDX, IDC_DIVISION_CHANGE, m_BtnDivisionChange);
	DDX_Control(pDX, IDC_DIVISION_OPEN, m_BtnDivisionOpen);
	DDX_Control(pDX, IDC_TEST_EDIT, m_EditTest);
}

BEGIN_MESSAGE_MAP(CSOUGeneratorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CSOUGeneratorDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSOUGeneratorDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_DETECTORS_PATH, &CSOUGeneratorDlg::OnBnClickedDetectorsPath)
	ON_BN_CLICKED(IDC_DIVISION_OPEN, &CSOUGeneratorDlg::OnBnClickedDivisionOpen)
	ON_BN_CLICKED(IDC_DIVISION_CHANGE, &CSOUGeneratorDlg::OnBnClickedDivisionChange)
	ON_MESSAGE(WM_DIVISION_OPEN_EXIT, &CSOUGeneratorDlg::OnDivisionOpenExit)
	ON_MESSAGE(WM_DIVISION_CHOOSE_EXIT, &CSOUGeneratorDlg::OnDivisionChangeExit)
	ON_MESSAGE(WM_DET_PATH_OK, &CSOUGeneratorDlg::OnDetectprsPathCheck)
	ON_EN_CHANGE(IDC_TEST_EDIT, &CSOUGeneratorDlg::OnEnChangeTestEdit)
	ON_BN_CLICKED(IDC_TEST_BTN, &CSOUGeneratorDlg::OnBnClickedTestBtn)
END_MESSAGE_MAP()


// ����������� ��������� CSOUGeneratorDlg

BOOL CSOUGeneratorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���������� ������ "� ���������..." � ��������� ����.

	// IDM_ABOUTBOX ������ ���� � �������� ��������� �������.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ������ ������ ��� ����� ����������� ����. ����� ������ ��� �������������,
	//  ���� ������� ���� ���������� �� �������� ����������
	SetIcon(m_hIcon, TRUE);			// ������� ������
	SetIcon(m_hIcon, FALSE);		// ������ ������

	// TODO: �������� �������������� �������������
	// 1 ������ ���������� ������ ������
	m_EditTest.ShowWindow(FALSE);
	m_TextText.ShowWindow(FALSE);
	m_BtnOK.ShowWindow(FALSE);
	m_BtnDivisionOpen.ShowWindow(FALSE);
	//m_BtnCancel.ShowWindow(FALSE);


	CString EmptyStr("");
	CString ERROR_STR("������");

	// 2 ���������� �� ini-�����
	// 2.1 ��������� ������ �� � ini-����� ���� � XML-����� �� ������� ��������

/*////////////////////////////////////////////////////////////////////////
	// 1 // �������� ���� � exe-����� ���������� � ��� ini-����� ����������� � ���
	TCHAR IniFileName[_MAX_PATH];
	TCHAR IniFilePath[_MAX_PATH];
	::GetModuleFileName(AfxGetApp()->m_hInstance, IniFileName, MAX_PATH);
	for(int i=0; i<_MAX_PATH; i++) {IniFilePath[i] = IniFileName[i];}

	TCHAR* szExt = _tcsrchr(IniFileName, '.');
	if(szExt) *(szExt+1) = 0;
	szExt = _tcsrchr(IniFilePath, '\\');
	if(szExt) *(szExt+1) = 0;
	//���������� ����������
	_tcscat_s(IniFileName, _MAX_PATH, _T("ini"));

	//1 theApp // ���� �� ini-�����, ���������� ��� ������ ����� � ���� ����
	theApp.IniFileName = IniFileName;
	theApp.IniFilePath = IniFilePath;
	//*/

//*///////////////////////////////////////////////////////////////////////
	// 2 // �������� ���� � exe-����� ���������� � ��� ini-����� ����������� � ���
	//CHAR szFullModulePath[_MAX_PATH]; szFullModulePath[0]=0;
	TCHAR szFullModulePath[_MAX_PATH]; szFullModulePath[0]=0;
	//TCHAR IniFileName[_MAX_PATH];
	TCHAR IniFilePath[_MAX_PATH];

	HANDLE hProcess = ::OpenProcess(
									PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
									FALSE,
									GetCurrentProcessId()
									);
	if(NULL != hProcess)
	{
		//if( ::GetModuleFileNameExA( hProcess, NULL, szFullModulePath, _MAX_PATH ) )
		if( ::GetModuleFileNameExW( hProcess, NULL, szFullModulePath, _MAX_PATH ) )
		{
			for(int i=0; i<_MAX_PATH; i++) {IniFilePath[i] = szFullModulePath[i];}

			TCHAR* szExt = _tcsrchr(szFullModulePath, '.');
			if(szExt) *(szExt+1) = 0;
			//�������� ���
			//CHAR* szName = strrchr(szFullModulePath, '\\');
			TCHAR* szName = _tcsrchr(IniFilePath, '\\');
			if(szName) *(szName+1) = 0;
			//���������� ����������
			_tcscat_s(szFullModulePath, _MAX_PATH, _T("ini"));
			//�������� ����
			//m_prot_name.insert(0,szFullModulePath);

		}
		CloseHandle(hProcess);
	}

	theApp.IniFileName = szFullModulePath; //���� �� ini-�����, ���������� ��� ������ ����� � ���� ����
	theApp.IniFilePath = IniFilePath;
	/////////////////////////////////////////////////////////////////////////
//*/

		// !!! �������� ������ �� ������ ���� ������� SQL ��� XML-��� [���� ������ �� �������, �� ��������� ������ SQL-���]:
	CIniParam AppVersion(theApp.IniFileName, _T("Program"), _T("SQLorXML"), _T("0"));
	theApp.Version = AppVersion.AsInt();

	if(theApp.Version==theApp.VER_SQL)
	{m_BtnDetectorsPath.EnableWindow(FALSE);}
	else
	{m_BtnDetectorsPath.EnableWindow(TRUE);}

	CIniParam AppDBLoginTimeout(theApp.IniFileName, _T("Program"), _T("DBLoginTimeout"), _T("5"));	 // ����� ��������������� � �� �� ��������� 5 ������
	theApp.IniDBLoginTimeout = AppDBLoginTimeout.AsInt();


	// ������ �� ��������� ������������ �������� ��� ����� �������� �� ����� ������� ������  8
	CIniParam AppMaxDetectors(theApp.IniFileName, _T("Program"), _T("MaxDetectors"), _T("0"));
	theApp.MaxDetectors = AppMaxDetectors.AsInt();

	if(theApp.Version == theApp.VER_XML)
	{
		GetAndCheckDetectorsFile();
	}
	else
	{
		m_TitlePath.SetWindowText(EmptyStr);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ��������� ����� ������������� ��������� �� ����� �������� ��� ��� ������ � XML ��� � � SQL �������
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	// 3 ��������� ��������� (���� ������) � ini-����� ���� � ����� � ��������� (�������  *.sou)
	// ���� ���� ������������� ��� ��������� ���������� � ������ ������, ���� �� � ����� �����, ��� � exe-���� ����� "�������"
	// � ��������� ��������� �� [����, ��� ��������� ��� exe-����] + [/�������] � ���, ��� ������� � ini-�����, ���� ��� ��������������, � ����������������� ����������.

	//::GetModuleFileName(m_hInstance, IniFileName, _MAX_PATH);
	//�������� ����������
	//TCHAR* szDest = _tcsrchr(IniFileName, '\\');
	// �������� ��������� �� �������� ������:
	//TCHAR* bigstring = new TCHAR(_MAX_PATH);
	//bigstring = IniFileName;

	//wchar_t *tmpSubstringFoundAt;
	//int tmpSubstringLength;

	//tmpSubstringFoundAt = wcsstr(IniFileName, szDest);
	//tmpSubstringLength = wcslen(szDest);

	// ��������� ��� ������� ������ ���� � ����, ����� ������������ ����� �� ���,
	// �� ����� ����������� ������, ��� ������ ����� �� ������������ �������� �����
	//wcsncpy ( tmpSubstringFoundAt, tmpSubstringFoundAt + tmpSubstringLength,
	//						 sizeof(IniFileName) - (tmpSubstringFoundAt-IniFileName));


	// 3.1 ���� ���� �� ini-�����
	CIniParam AppDivisionsPath(theApp.IniFileName, _T("Program"), _T("DivisionsPath"), EmptyStr); // �������
	theApp.IniDivisionsPath = AppDivisionsPath.AsString();

	// 3.1.1 ���� ���� ����
	// ������ ����������� ���� "�� ���������", ����������� � ���� �� exe-����� ������� + \�������

	CString DefaultPath("�������");
	CString DivPathName("");
	if(theApp.IniDivisionsPath == EmptyStr)
	{
		/*
		TCHAR DivPathName[_MAX_PATH];
		::GetModuleFileName(AfxGetApp()->m_hInstance, DivPathName, MAX_PATH);
		TCHAR* szExtbs = _tcsrchr(DivPathName, '\\');
		if(szExtbs) *(szExtbs+1) = 0;
		//���������� ����� ����, ������� ������ ������������� ������ "�������"
		_tcscat_s(DivPathName, _MAX_PATH, _T("�������"));

		theApp.IniDivisionsPath = DivPathName;
		theApp.CurDivisionsPath = DivPathName;

		CreateDirectory(theApp.IniDivisionsPath,NULL);

		AppDivisionsPath.Set(DivPathName);
		AppDivisionsPath.Save();
		*/
		theApp.IniDivisionsPath = DefaultPath;
		theApp.CurDivisionsPath = DefaultPath;

		CreateDirectory(theApp.IniDivisionsPath,NULL);

		AppDivisionsPath.Set(DefaultPath);
		AppDivisionsPath.Save();
	}
	else
	{
	// 3.1.2 ���� ���� ������
		// ��������: ���������� �� �� ����, ��� �������� � ini-����� �������������� �����
		bool PathExistance = PathFileExists(theApp.IniDivisionsPath);

		// ��  =>  ������ �� ������, � ������ ��� �� ��������� �����, ������ ������ ���� � ���������� theApp.CurDivisionPath
		if(PathExistance)
		{
			//AfxMessageBox(_T("Path = TRUE"));
			if( !(GetFileAttributes(theApp.IniDivisionsPath) == INVALID_FILE_ATTRIBUTES) )
			{
				if(!CreateDirectory(theApp.IniDivisionsPath,NULL))
				{
					if(GetLastError() == ERROR_ALREADY_EXISTS)
					{ //AfxMessageBox(_T("ERROR_ALREADY_EXISTS"));	// directory already exists
						PathExistance=true;
						theApp.CurDivisionsPath = theApp.IniDivisionsPath;
					}
					//else	// creation failed due to some other reason
				}
				else
				{	// ������� �����, ��� ������, ��� ����� �� ���� �� ����!
					CFile::Remove(theApp.IniDivisionsPath);
					PathExistance=false;
				}	
			}
			else
			{
				PathExistance=false;
				//AfxMessageBox(_T("INVALID_FILE_ATTRIBUTES"));
			}
		}
		else
		{
			PathExistance=false;
			//AfxMessageBox(_T("Path = FALSE"));
		}

		// ��� =>  �������� � ini-����� � ������ ���� ini-���� �� ���� "�� ���������", ����������� � ���� �� exe-����� ������� + \�������
		if(!PathExistance)
		{
			/*
			TCHAR DivPathName[_MAX_PATH];
			::GetModuleFileName(AfxGetApp()->m_hInstance, DivPathName, MAX_PATH);
			TCHAR* szExtbs = _tcsrchr(DivPathName, '\\');
			if(szExtbs) *(szExtbs+1) = 0;
			//���������� ����� ����, ������� ������ ������������� ������ "�������"
			_tcscat_s(DivPathName, _MAX_PATH, _T("�������"));

			//theApp.IniDivisionsPath = DefaultPath;
			//theApp.CurDivisionsPath = DefaultPath;

			//AppDivisionsPath.Set(DefaultPath);
			//AppDivisionsPath.Save();
			//*/

			theApp.IniDivisionsPath = DefaultPath;
			theApp.CurDivisionsPath = DefaultPath;

			AppDivisionsPath.Set(DefaultPath);
			AppDivisionsPath.Save();
		}
	}

	DivPathName = theApp.CurDivisionsPath;


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// !!! ��� ������� ����� � ������������������, �.�. ����� �� ����� ������� ����� �� ���� "�� ���������" (������� ������������� ���� ���� � INI �������� "��������������������")
	// ���� ����� �� ����� ���� ��� ����, �� ������ � ��� �� �������Ĩ�.
	int CreationResult = CreateDirectory(theApp.CurDivisionsPath, NULL);
	if(CreationResult!=0)
	{
		if( CreationResult == ERROR_ALREADY_EXISTS )//== GetLastError())
		{
			//AfxMessageBox(_T("Folder allready exists"));
		}
		else
		{// Failed to create directory.
			//AfxMessageBox(_T("������ ��� �������� ����� � ������� ��������."));
			// !!!!! ��� ������ ���������� ����������������� !!!!!
		}
	}

	// ���������� �������� �������� ��������������� ������ � ����������� .sou �� ������� ���� !!!!!

	// http://www.rsdn.ru/article/qna/baseserv/fileexist.xml

	CString DivPathWithFiles("");
	CString DivPath("");

	DivPath = DivPathName;
	DivPathWithFiles = DivPath + _T("\\*.sou");

	//const wchar_t* _DivPathWithFiles = new wchar_t [_MAX_PATH];  // �������� delete � ����� !!!
	//_DivPathWithFiles = DivPathWithFiles;

	if( !FileExists(DivPathWithFiles) )
	{
		MessageBox(	  _T("� ����� � ��������� ����������� ����� ��������\n ���������, ���:\n") 
					_T("1) ����� \"�������\" ��������� � ��� �� �����, ��� � �������.\n")
					_T("2) � ����� ������� ����� � ������������ .sou"),
					_T("������"), MB_ICONERROR);
		// !!!!! ��� ������ ���������� ����������������� !!!!!
	}

	//CIniParam parInjProd1 (CBLOWApp::IniFileName, _T("Injection"), _T("InjProd1"));
	//parInjProd1.Set(m_InjProducts[0]);
	//parInjProd1.Save();

	return TRUE;  // ������� �������� TRUE, ���� ����� �� ������� �������� ����������
}


void CSOUGeneratorDlg::GetAndCheckDetectorsFile()
{
	CString EmptyStr("");
	
	CIniParam AppDetectorsPath(theApp.IniFileName, _T("Program"), _T("DetectorPath"), EmptyStr);	 // �������
	//2,3 theApp // ���� � XML-����� �� ������� ��������, ���������� ��� ������ ����� � ���� ���� //2 ������ �� ini-����� //3 �������
	theApp.IniDetectorsPath = AppDetectorsPath.AsString();
	theApp.CurDetectorsPath = theApp.IniDetectorsPath;

	if(theApp.IniDetectorsPath==EmptyStr)
	{
		m_TitlePath.SetWindowText(_T("! ������������� !"));
		m_BtnDivisionChange.EnableWindow(FALSE);
		theApp.XMLDetectorsFound=false;
		return;
	}
	else
	{
		m_TitlePath.SetWindowText(_T("�����������"));
		m_BtnDivisionChange.EnableWindow(TRUE);
		theApp.XMLDetectorsFound=true;
	}
	// ���������� �������� �������� ��������������� ����� �� ������� ���� !!!!!
	// http://www.sources.ru/msdn/library/cfile_in_mfc.shtml

	CFile XMLFile;
	CFileException fileException;
	//BOOL bOpenOK;
	CFileStatus status;

	if(theApp.IniDetectorsPath!=EmptyStr)
	if( !CFile::GetStatus( theApp.IniDetectorsPath, status ) && !(PathFileExists(theApp.IniDetectorsPath)) )
	{
		m_TitlePath.SetWindowText(_T("! ���� ���������� !"));
		m_BtnDivisionChange.EnableWindow(FALSE);
		theApp.XMLDetectorsFound=false;
		return;
		//return TRUE; // ������� ��� ���������� �������� � ������� �������� ������ �� XML-�����
	}
	else
	{ // �� ������ �������� ����� ��������� �� ������ �� ���� �� ������
		//if ( !XMLFile.Open( theApp.IniDetectorsPath, 
		//								CFile::modeCreate | CFile::modeNoTruncate |	
		//								CFile::modeReadWrite, &fileException ) )
		//{
		//	TRACE( "�������� ����� %s, ���������� � ������� = %u\n",
		//		theApp.IniDetectorsPath, fileException.m_cause );
		//
		//}
		//else
		{
			wchar_t* _IniDetectorsPath = new wchar_t [_MAX_PATH];  // �������� delete � ����� !!!
			wcscpy(_IniDetectorsPath, theApp.IniDetectorsPath);

			//for(int i=0; i < theApp.IniDetectorsPath.GetLength() ; i++)
			//{ 
			//	_IniDetectorsPath[i] = theApp.IniDetectorsPath[i];
			//	if(i+1 == theApp.IniDetectorsPath.GetLength())
			//	{_IniDetectorsPath[i+1]='\0';}
			//}


			TCHAR* szExt = _tcsrchr(_IniDetectorsPath, '\\');
			CString CutPart = szExt;
			if(CutPart.GetLength() > 1)
			{
				int j=0;
				for(; j<(CutPart.GetLength()-1) ; j++)
				{szExt[j] = CutPart[j+1];}
				szExt[j]='\0';
			}

			CutPart = szExt;
			theApp.DetectorsFileName = CutPart;
			theApp.XMLDetectorsFound=true;

			delete [] _IniDetectorsPath;
		}
	}

	// 2.2 ���������, ��� ����� ����� ������� ��� �� ������ ������� ��������� � ������ ��� XML-������
	//	 ��� ��� ��������� ������ �������� �� XML �����, ���� ������� ���������� � ������, � ��������� ��� 
	//	 � �������������� �������, � �������� theApp, ���� ����� �� ���������� � �����. � ���������� � �����
	//	 ������ �������� ������ � ���� �� ����� ���������� ��� �������� ��������������� ��������

	CString DetectorsFullPath("");
	DetectorsFullPath = theApp.CurDetectorsPath;
	_bstr_t DetectorsFullPathBstr = DetectorsFullPath;

	//CStringA p_DetFullPath(DetectorsFullPath);

	if(DetectorsFullPath.GetLength() > 0)
	{
		_bstr_t bstrOutput("");
		bool validXml=false;
		
		HRESULT hr = CoInitialize(NULL);
		if(SUCCEEDED(hr))
		{
			try{ bstrOutput = theApp.validateDetFile(DetectorsFullPathBstr, validXml); }
			catch(_com_error &e)
			{bstrOutput = theApp.dump_com_error(e);}
		}

		if(validXml) // ������, ����� ���� �� ������� �������� "��������" � ������� ����� ���������
		{
			//readDetectorsFile(L"U4ASTOK.sou");
			readDetectorsFile(DetectorsFullPath);

			m_BtnDivisionChange.EnableWindow(TRUE);
			theApp.XMLDetectorsFound=true;
		}
		else //if(!validXml)
		{
			if(bstrOutput.length()>0)
			MessageBox(bstrOutput, L"������ � ����� ��� ��� ��������", MB_OK);
			m_TitlePath.SetWindowText(_T("! �������� � ������ !"));

			m_BtnDivisionChange.EnableWindow(FALSE);
			theApp.XMLDetectorsFound=false;
		}
		CoUninitialize();
	}
}




//void test(CString bstrXMLFile)
void CSOUGeneratorDlg::readDetectorsFile(CString bstrXMLFile)
{
  CComPtr<IXMLDOMDocument> iXMLDoc;
  iXMLDoc.CoCreateInstance(__uuidof(DOMDocument));
 	
  // Following is a bugfix for PocketPC.
#ifdef _UNDER_CE
  gargle bargle
  iXMLDoc->put_async(VARIANT_FALSE);
  CComQIPtr<IObjectSafety,&IID_IObjectSafety> iSafety(iXMLDoc);
  if (iSafety) 
  { DWORD dwSupported, dwEnabled; 
    iSafety->GetInterfaceSafetyOptions(IID_IXMLDOMDocument,&dwSupported,&dwEnabled);
    iSafety->SetInterfaceSafetyOptions(IID_IXMLDOMDocument,dwSupported,0);
  }
#endif
 	// Load the file. 
	VARIANT_BOOL bSuccess=false;
	// Can load it from a url/filename...
	//iXMLDoc->load(CComVariant(url),&bSuccess);
	//iXMLDoc->load(CComVariant("D:/SDHW-5-SOU/Test-Interface2/XML MSXML/sou.sou"), &bSuccess);
	iXMLDoc->load(CComVariant(bstrXMLFile), &bSuccess);
	
	// or from a BSTR...
	//iXMLDoc->loadXML(CComBSTR(src),&bSuccess);
 
	// Get a pointer to the root
	CComPtr<IXMLDOMElement> iRootElm;
	iXMLDoc->get_documentElement(&iRootElm);

	// Thanks to the magic of CComPtr, we never need call
	// Release() -- that gets done automatically.

	//detnum	
	//detname
	//detptfix
	//detdistance
	//detfilepath
	//detprodtype
	//detprodid
	//detprodview
	//detwavespeed
	//detpipeid
	//detpipeshrtname
	//detpipelenght
	//detbeginname
	//detendname


	TElem eroot(iRootElm);
	TElem subroot = eroot.subnode(L"Detector");
	wstring DetAtrs;
	std::vector<CString> TitleDetector;
	std::vector<CString> OneDetector;

	for(TElem e=eroot.begin(); e!=eroot.end(); e++)
	{
		DetAtrs = e.attr(L"detnum");		OneDetector.push_back(DetAtrs.c_str());
		//AfxMessageBox(DetAtrs.c_str(), 0, 0);
		DetAtrs = e.attr(L"detname");		OneDetector.push_back(DetAtrs.c_str());
		DetAtrs = e.attr(L"detptfix");		OneDetector.push_back(DetAtrs.c_str());
		DetAtrs = e.attr(L"detdistance");	OneDetector.push_back(DetAtrs.c_str());
		DetAtrs = e.attr(L"detfilepath");	OneDetector.push_back(DetAtrs.c_str());
		DetAtrs = e.attr(L"detprodtype");	OneDetector.push_back(DetAtrs.c_str());
		DetAtrs = e.attr(L"detprodid");		OneDetector.push_back(DetAtrs.c_str());
		DetAtrs = e.attr(L"detprodview");	OneDetector.push_back(DetAtrs.c_str());
		DetAtrs = e.attr(L"detwavespeed");	OneDetector.push_back(DetAtrs.c_str());
		DetAtrs = e.attr(L"detpipeid");			OneDetector.push_back(DetAtrs.c_str());
		DetAtrs = e.attr(L"detpipeshrtname");	OneDetector.push_back(DetAtrs.c_str());
		DetAtrs = e.attr(L"detpipelenght");		OneDetector.push_back(DetAtrs.c_str());
		DetAtrs = e.attr(L"detbeginname");		OneDetector.push_back(DetAtrs.c_str());
		DetAtrs = e.attr(L"detendname");		OneDetector.push_back(DetAtrs.c_str());

	//detnum //detname //detptfix //detdistance //detfilepath //detprodtype //detprodid
		theApp.AllDetectors.push_back(OneDetector);
		OneDetector.clear();
	}

	// ����������� ������ �������� �� �������:
	TitleDetector = theApp.AllDetectors[0]; // ��������� ������ ������� � "������", ����� ��� �� �������� ��� ����������
	theApp.AllDetectors.erase(theApp.AllDetectors.begin()+0); // ������� �� ������� ������ ������� � ������� ����� ���� � ��������
	for (int i=0; i < theApp.AllDetectors.size(); i++)
	{
		// ������ ��������������� � ����� �� ������� i � "������ �������� ���������"
		for (int j = theApp.AllDetectors.size()-1; j > i; j--)
		{
			// ���� �������� �������� ����������� � ������������ �������, �� ������ �� �������
			if ( _tstol(theApp.AllDetectors[j][0]) < _tstol(theApp.AllDetectors[j-1][0]))
			{
				//std::swap(tesr[j], tesr[j-1]);
				OneDetector.clear();
				OneDetector = theApp.AllDetectors[j];
				theApp.AllDetectors.erase(theApp.AllDetectors.begin()+j); // ������� �� ������� j-��� ������ (�������)
				theApp.AllDetectors.insert(theApp.AllDetectors.begin()+(j-1), OneDetector); // �������� j-��� ������ �� ��� �����
			}
		}
	}
	theApp.AllDetectors.insert(theApp.AllDetectors.begin(), TitleDetector); // ��������� ����� ������� � ������
	TitleDetector.clear();

	int u=0;
}


void CSOUGeneratorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// ��� ���������� ������ ����������� � ���������� ���� ����� ��������������� ����������� ���� �����,
//  ����� ���������� ������. ��� ���������� MFC, ������������ ������ ���������� ��� �������������,
//  ��� ������������� ����������� ������� ��������.

void CSOUGeneratorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �������� ���������� ��� ���������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ������������ ������ �� ������ ����������� ��������������
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ��������� ������
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ������� �������� ��� ������� ��� ��������� ����������� ������� ��� �����������
//  ���������� ����.
HCURSOR CSOUGeneratorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSOUGeneratorDlg::OnBnClickedOk()
{
	// TODO: �������� ���� ��� ����������� �����������
	//CDialog::OnOK();
}


void CSOUGeneratorDlg::OnBnClickedCancel()
{
	// TODO: �������� ���� ��� ����������� �����������
	CDialog::OnCancel();
}


// ������ "���� � ������ ��������"
void CSOUGeneratorDlg::OnBnClickedDetectorsPath()
{
	// TODO: �������� ���� ��� ����������� �����������
	
	CDetectorsPath DetectorsPathDlg;	//DetectorsPathDlg.DoModal();
	if( DetectorsPathDlg.DoModal() == IDCANCEL ) // IDOK
	{}
}


// ������� �� ������ "���������" �� ���� "���� �� XML-����� �� ������� ��������"
LRESULT CSOUGeneratorDlg::OnDetectprsPathCheck( WPARAM wparam , LPARAM lparam )
{
	m_TitlePath.SetWindowText(_T("�����������"));
	m_BtnDivisionChange.EnableWindow(TRUE);
	return 0;
}


// ������ "���������" // ������� (����/���������)
void CSOUGeneratorDlg::OnBnClickedDivisionChange()
{
	// TODO: �������� ���� ��� ����������� �����������
	//CDivisionChange DivisionChangeDlg;
	//DivisionChangeDlg.DoModal();
	//if( DivisionChangeDlg.DoModal() == IDCANCEL ) // IDOK
	//{}
	bool ConnectAndGetData=false;
	bool validXml=false;


	HRESULT hr = CoInitialize(NULL);
	if(FAILED(hr))
	{
		CString ErrorStr = theApp.GetErrorCSTRString(hr);
		AfxMessageBox(ErrorStr);
		LogConnectionStatus( ConnectStep, ErrorStr, false);
		return;
	}

	if(theApp.Version == theApp.VER_SQL)
	{
		CString DetectorsFileName = _T("������ ��������.xml");

		bool bReConnect=true;
		long nDlgConnect=0;

		while(bReConnect)
		{	// sougen_logconnect	// sougen_logfiles
			if( Connect() )
			{
				if( DBGetDetectors() )
				{
					bReConnect=false;
					ConnectAndGetData=true;
					//DisConnect();

					if( !(writeDetectorsFile(DetectorsFileName)) )
					{
						CString ErrorStr = _T("��� �������� ����� ������ �������� ��������� ������. ��������� ��������� ������ � ��������� ������� ����� ������ ��������.");
						AfxMessageBox(ErrorStr);
						LogConnectionStatus( ConnectStep, ErrorStr, false);
						//AfxMessageBox(ErrorStr);
					}

					//////////////////////////////////////////////////////////////////////////////////
					//// �������������� �������� ������������� ����� � ������ ���������� �� ��

					// � SQL-��� ������ ��������� ���� �� ������� �������� �������� ������ ��� ����� � EXE-������
					CString DetectorsFullPath("");
					DetectorsFullPath = theApp.IniFilePath + _T("\\") + DetectorsFileName;
					_bstr_t DetectorsFullPathBstr = DetectorsFullPath;

					if(DetectorsFullPath.GetLength() > 0)
					{
						_bstr_t bstrOutput("");
						validXml=false;
		
//						HRESULT hr = CoInitialize(NULL);
//						if(SUCCEEDED(hr))
						{
							try{ bstrOutput = theApp.validateDetFile(DetectorsFullPathBstr, validXml); }
							catch(_com_error &e)
							{bstrOutput = theApp.dump_com_error(e);}
						}

						if(validXml) // ������, ����� ���� �� ������� �������� "��������" � ������� ����� ���������
						{
							//m_BtnDivisionChange.EnableWindow(TRUE);
							//theApp.XMLDetectorsFound=true;
							int o=0;
						}
						else //if(!validXml)
						{
							if(bstrOutput.length()>0)
							{
								MessageBox(bstrOutput, L"������ � ����� ��� ��� ��������", MB_OK);
								
								// ��� ��� ������ ������, �� XML �� ������� �������� ���������� ������������, ������ �������� � ���� ������!
								// !!!!! ���������� !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						// 2.4 ��������� � ��� ���������� �� ���������, �� ���������� ������. !!!!!
								CString LogFileName("sougen_logfiles.txt");
								CString DotSOU(".sou");
								CString lLine;

								// ������� ��������� � ��� ���������� � ������������ ������
								CString LogFiles("");
								CString LogPath("");

								///////////////////////////////////////////////////////////////////////////////////////
								// ���������� �����, �������� � ����� ����� ������ ������ ������ �� ������� ��� �� 
								// �������� �������� ���������� � ������, ���������� ������� �� � ����� �������� � ����
								CStdioFile cfile_object_write;
								BOOL lOk = cfile_object_write.Open(LogFileName, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite);
								//CFile cfile_object_write( LogFileName, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite);
								cfile_object_write.SeekToEnd();

								GetLocalTime(&theApp.m_CurTime);	//�������������� ��������� �����

								LogFiles += _T("*******************************************************************************************************************************\n");
								lLine.Format(_T("|SOU|%02i.%02i.%04i | %02i:%02i:%02i|******************************************************************************************\n"),
									theApp.m_CurTime.wDay, theApp.m_CurTime.wMonth, theApp.m_CurTime.wYear, theApp.m_CurTime.wHour, theApp.m_CurTime.wMinute, theApp.m_CurTime.wSecond);

								LogFiles += lLine;
								LogFiles += LPCTSTR(bstrOutput);

								LogPath = LogPath + theApp.IniFilePath + LogFileName;

								CStringA LogPathA(LogPath);
								CStringA LogFilesA(LogFiles);

								cfile_object_write.Write(LogFilesA, LogFilesA.GetLength());
								cfile_object_write.Close();

								//m_TitlePath.SetWindowText(_T("! �������� � ������ !"));
								//m_BtnDivisionChange.EnableWindow(FALSE);
								//theApp.XMLDetectorsFound=false;
							}
						}
						CoUninitialize();
					}
					//////////////////////////////////////////////////////////////////////////////////
				}
				else
				{// 1541 - ��� ������ "Connection Busy"
					CNoSQLConnect NoSQLConnectDlg;
					nDlgConnect = NoSQLConnectDlg.DoModal();
					DisConnect();
				}
			}
			else
			{
				//CNoSQLConnect* p_NoSQLConnectDlg = new CNoSQLConnect;
				//p_NoSQLConnectDlg->Create(IDD_NO_SQL_CONNECT, this);
				//p_NoSQLConnectDlg->ShowWindow(SW_SHOW);
				
				CNoSQLConnect NoSQLConnectDlg;
				nDlgConnect = NoSQLConnectDlg.DoModal();
			}

			switch(nDlgConnect)
			{
			case IDRETRY:			// ��������� �������
				bReConnect=true;
				break;
			case IDOK:				// ������� � ������ � ��������� XML
				bReConnect=false;
				theApp.Version = theApp.VER_XML;

				m_BtnDetectorsPath.EnableWindow(TRUE);
				GetAndCheckDetectorsFile();
				break;
			case IDCANCEL:			// �����
				bReConnect=false;
				break;


				if(ConnectAndGetData)
				{
					DisConnect();
					break;
				}
			}
		}

		// � ������ ��������� ��������� � ��������� ������� ������ � ��������� � ���������� ���������� XML �� ������� ��������
		if(ConnectAndGetData && validXml)
		{
			CDivisionChoose* p_DivisionChooseDlg = new CDivisionChoose;
			p_DivisionChooseDlg->Create(IDD_DIVISION_CHOOSE_DLG, this);
			p_DivisionChooseDlg->ShowWindow(SW_SHOW);

			WndDivisionChange=false;
			m_BtnDivisionChange.EnableWindow(FALSE);
			m_BtnCancel.EnableWindow(FALSE);
		}
	}
	else
	{
		CDivisionChoose* p_DivisionChooseDlg = new CDivisionChoose;
		p_DivisionChooseDlg->Create(IDD_DIVISION_CHOOSE_DLG, this);
		p_DivisionChooseDlg->ShowWindow(SW_SHOW);

		WndDivisionChange=false;
		m_BtnDivisionChange.EnableWindow(FALSE);
		m_BtnCancel.EnableWindow(FALSE);
	}
}


// ������� ����� ODBC // ��� ������� � ��� �� ������� � ODBC // ��� ODBC ����������, ����� � ������ (���� ������ ������� ����.=NO), ������� �������� = ��� (��� �������� �������������)
/*

//*/

/*
// ������� ����� SQLConnect
bool CSOUGeneratorDlg::Connect()
{
//	SQLConnect_ref.cpp
//	compile with: odbc32.lib
//	#include <windows.h>
//	#include <sqlext.h>

//	int main() 
//	{
	SQLHENV henv;
	SQLHDBC hdbc;
	SQLHSTMT hstmt;
	SQLRETURN retcode;

	//SQLCHAR * OutConnStr = (SQLCHAR * )malloc(255);
	SQLWCHAR * OutConnStr = (SQLWCHAR * )malloc(255);
	SQLSMALLINT * OutConnStrLen = (SQLSMALLINT *)malloc(255);

   // Allocate environment handle
   retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);

   // Set the ODBC version environment attribute
   if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
   {
      retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0); 

      // Allocate connection handle
      if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
	  {
         retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc); 

         // Set login timeout to 5 seconds
         if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
		 {
            SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);

            // Connect to data source
            //retcode = SQLConnect(hdbc, (SQLCHAR*) "NorthWind", SQL_NTS, (SQLCHAR*) NULL, 0, NULL, 0);
            retcode = SQLConnect(hdbc, (SQLWCHAR*) "NorthWind", SQL_NTS, (SQLWCHAR*) NULL, 0, NULL, 0);

            // Allocate statement handle
            if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
			{
               retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt); 

               // Process data
               if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
			   {
                  SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
               }

               SQLDisconnect(hdbc);
            }

            SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
         }
      }
      SQLFreeHandle(SQL_HANDLE_ENV, henv);
   }
}
//*/


//*
// ������� ����� SQLDriverConnect // ������ SQLStringConnect
bool CSOUGeneratorDlg::Connect()
{
	CString EmptyCStr("");

	ConnectStep = _T("���������� � ��");
	LogConnectionStatus( ConnectStep, _T("������������ ����������"), false);

	Driver_St_CStr	="DRIVER=";
	Server_St_CStr	="SERVER=";
	DB_St_CStr		="DATABASE=";
	UID_St_CStr		="UID=";
	PWD_St_CStr		="PWD=";
	TrCon_St_CStr	="Trusted_Connection=";
	APP_St_CStr		="APP=";

	Driver_CStr	=EmptyCStr;
	Server_CStr	=EmptyCStr;
	DB_CStr		=EmptyCStr;
	UID_CStr	=EmptyCStr;
	PWD_CStr	=EmptyCStr;
	TrCon_CStr	=EmptyCStr;
	APP_CStr	=EmptyCStr;

	ConnectStr_CStr	=EmptyCStr;
	DBMes_CStr		=EmptyCStr;

	CIniParam AppDriver(theApp.IniFileName, _T("SQL"),	_T("Driver"),	EmptyCStr);
	CIniParam AppServer(theApp.IniFileName, _T("SQL"),	_T("Server"),	EmptyCStr);
	CIniParam AppDB(theApp.IniFileName, _T("SQL"),		_T("DataBase"),	EmptyCStr);
	CIniParam AppUID(theApp.IniFileName, _T("SQL"),		_T("UserID"),	EmptyCStr);
	CIniParam AppPWD(theApp.IniFileName, _T("SQL"),		_T("Password"),	EmptyCStr);
	CIniParam AppTrCon(theApp.IniFileName, _T("SQL"),	_T("TrstConn"),	_T("Yes"));
	CIniParam AppAPP(theApp.IniFileName, _T("SQL"),		_T("App"),		_T("SOU-Generator-SQL"));

	Driver_CStr	= AppDriver.AsString();
	Server_CStr	= AppServer.AsString();
	DB_CStr		= AppDB.AsString();
	UID_CStr	= AppUID.AsString();
	PWD_CStr	= AppPWD.AsString();
	TrCon_CStr	= AppTrCon.AsString();
	APP_CStr	= AppAPP.AsString();


	// TODO: �������� ���� ��� ����������� �����������
	CString CommaStr(";");
	ConnectStr_CStr.Empty();

	if(Driver_CStr != EmptyCStr)	{ ConnectStr_CStr = ConnectStr_CStr + Driver_St_CStr + Driver_CStr + CommaStr; }
	if(Server_CStr != EmptyCStr)	{ ConnectStr_CStr = ConnectStr_CStr + Server_St_CStr + Server_CStr + CommaStr; }
	if(DB_CStr != EmptyCStr)		{ ConnectStr_CStr = ConnectStr_CStr + DB_St_CStr + DB_CStr + CommaStr; }
									  ConnectStr_CStr = ConnectStr_CStr + UID_St_CStr + UID_CStr + CommaStr;
									  ConnectStr_CStr = ConnectStr_CStr + PWD_St_CStr + PWD_CStr + CommaStr;
	if(TrCon_CStr != EmptyCStr)		{ ConnectStr_CStr = ConnectStr_CStr + TrCon_St_CStr + TrCon_CStr + CommaStr; }
	if(APP_CStr != EmptyCStr)		{ ConnectStr_CStr = ConnectStr_CStr + APP_St_CStr + APP_CStr + CommaStr; }


	//m_StaticConStr.SetWindowText(ConnectStr_CStr);
	conn = (wchar_t *)(LPCTSTR)(LPCTSTR)ConnectStr_CStr;
    wchar_t connStrOut[256];
    wchar_t sqlstate[32];
    wchar_t message[256];
 
	// Set Time: http://stackoverflow.com/questions/2018046/c-sqldriverconnect-api

	bConnect=false;
	CString ErrorStr("");

	// Allocate environment handle
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
	ErrorStr = _T("������������� ����������� ��������� ����������� ��������.");
	if(retcode != SQL_SUCCESS || retcode != SQL_SUCCESS_WITH_INFO)
	{
		// Set the ODBC version environment attribute
		retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER*)SQL_OV_ODBC3, 0); 
		ErrorStr = _T("������� ����������� ������ ODBC ���������� �������� (SQLSetEnvAttr).");

		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
		{
			// Allocate connection handle
			retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc); 
			ErrorStr = _T("������������� ����������� ���������� ����������� ��������.");

			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
			{
				// ������������� ������� ��������������� (login timeout) ������ 5 ������
				//SQLSetConnectAttr(hdbc, SQL_ATTR_LOGIN_TIMEOUT, (SQLPOINTER)theApp.IniDBLoginTimeout, 0); // (void*)2
				SQLSetConnectAttr(hdbc, SQL_ATTR_CONNECTION_TIMEOUT, (void *)theApp.IniDBLoginTimeout, 0);
				SQLSetConnectAttr(hdbc, SQL_ATTR_LOGIN_TIMEOUT, (void*)theApp.IniDBLoginTimeout, 0);

				//retcode = SQLDriverConnect(hconn, NULL, conn, SQL_NTS, connStrOut, 256, &bufsize, SQL_DRIVER_NOPROMPT);	// 1-�� �������
				//retcode = SQLDriverConnect(hdbc, desktopHandle, (SQLWCHAR *)ConnStrIn, SQL_NTS, OutConnStr, 255, &OutConnStrLen, SQL_DRIVER_NOPROMPT); 
				// SQLDriverConnect // ������ SQLStringConnect /////////////////////////////////////////////////////////////////////////////////////////
				retcode = SQLDriverConnect(hdbc, NULL, conn, SQL_NTS, connStrOut, 255, &bufsize, SQL_DRIVER_NOPROMPT);

				//http://datasql.ru/proektbd/4.htm
				if( ((retcode==SQL_SUCCESS) || (retcode==SQL_SUCCESS_WITH_INFO)) && (bufsize > 0))
				{
					// ������������� ����������� ���������		// Allocate statement handle
					// �������������� ����� ��������� ��� ���������� SQL-��������� SELECT. ��� ���������� ������ SQL-��������� ������������� ������ ���� ������ ���������� ���������.
					// ������ �������� ��������� ���������� ����������, ��� �������� ��������� ���������� ���������, � ������ �������� ���������� ������� ������, ���������� ��� ���������� ���������.
					//retcode = SQLAllocHandle(SQL_HANDLE_STMT, hconn, &hstmt);
					retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
					ErrorStr = _T("������������� ����������� ��������� ����������� ��������.");
					if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
					{
						//���������� !!! ��� ������.
						bConnect=true;

						// ��������� ���������� ������ (������� � �.�.)
						// ������������ ��������� ���� �������, ��� ��� ����������� ����������, ��� �������� ������, ��� � ����� ������ ���������� ������ � ������ ������  DisConnect()
						// SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
					}
					else
					{LogConnectionStatus( ConnectStep, ErrorStr, true);}
					// ������������ ��������� ���� �������, ��� ��� ����������� ����������, ��� �������� ������, ��� � ����� ������ ���������� ������ � ������ ������  DisConnect()
					//SQLDisconnect(hdbc);
				}
				else
				{
					//retcode = SQLGetDiagRec(SQL_HANDLE_DBC, hconn, 1,  sqlstate, &nativeerror, message, 256, &textlen);
					retcode = SQLGetDiagRec(SQL_HANDLE_DBC, hdbc, 1,  sqlstate, &nativeerror, message, 256, &textlen);
					if (retcode != SQL_ERROR)
					{
						ErrorStr.Format(_T("%s=%s"),sqlstate, message);
						//LogConnectionStatus( _T("������� ODBC"), ErrorStr, true);
						LogConnectionStatus( _T("������"), ErrorStr, true);
					}
				}
				// ������������ ��������� ���� �������, ��� ��� ����������� ����������, ��� �������� ������, ��� � ����� ������ ���������� ������ � ������ ������  DisConnect()
				//SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
			}
			else	
			{LogConnectionStatus( ConnectStep, ErrorStr, true);}
		}
		else
		{LogConnectionStatus( ConnectStep, ErrorStr, true);}
		// ������������ ��������� ���� �������, ��� ��� ����������� ����������, ��� �������� ������, ��� � ����� ������ ���������� ������ � ������ ������  DisConnect()
		//SQLFreeHandle(SQL_HANDLE_ENV, henv);
	}
	else
	{LogConnectionStatus( ConnectStep, ErrorStr, true);}


	return bConnect;
}
//*/


void CSOUGeneratorDlg::DisConnect()
{
	ConnectStep = _T("���������� � ��");
	LogConnectionStatus( ConnectStep, _T("���������� �� ���� ������"), false);

	// TODO: �������� ���� ��� ����������� �����������

// ������� ����� ODBC

// ������� ����� SQLConnect

// ������� ����� SQLDriverConnect // ������ SQLStringConnect
	SQLFreeHandle(SQL_HANDLE_ENV, henv);
	SQLDisconnect(hdbc);
	SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
	SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
}


//DBQuery
bool CSOUGeneratorDlg::DBGetDetectors()
{
	// TODO: �������� ���� ��� ����������� �����������
	v_SQLTopStr.clear();
	v_SQLFullTable.clear();
	theApp.AllDetectors.clear();


	//DBMes_CStr = _T("Select * FROM dbo.ViewGrafListSpots");
	DBMes_CStr = _T("Select * FROM dbo.fn_AreaListSpots()");

	ConnectStep = _T("������ ������ �� ��");
	LogConnectionStatus( ConnectStep, _T("������� ����������� ������"), false);

	RETCODE retcode=NULL;
	const int t = 50;

	SQLINTEGER  sqf1;
	SQLCHAR	sqf2[t];
	//SQLCHAR* psqf2 = new SQLCHAR [t]; // typedef unsigned char   SQLCHAR;
	//memset(); // zeromemory;


	SQLINTEGER	sbf1,sbf2;
	SQLINTEGER	row_num;
	SQLSMALLINT	col_num;

	int col1=0;
	CString col2("");

	selecttxt = (wchar_t *)(LPCTSTR)(LPCTSTR)DBMes_CStr;

	// ��������  ��������������� ������
	retcode = SQLExecDirect(hstmt,  selecttxt,   SQL_NTS);
	if (retcode == SQL_SUCCESS)
	{
		const int MAXCOLS = 30000;
		SQLRowCount(hstmt, &row_num);
		SQLNumResultCols(hstmt, &col_num);

		SQLTCHAR        colname[32];	// ok
		SQLSMALLINT     colnum=0;		// ok
		SQLSMALLINT		pcbColName=0;	// ok
		SQLSMALLINT     coltype=0;		// ok
		SQLSMALLINT     colnamelen=0;	// ok
		SQLSMALLINT     nullable=0;		// ok
		SQLUINTEGER     collen[MAXCOLS];
		SQLSMALLINT     scale=0;		// ok
		//SQLINTEGER      outlen[MAXCOLS];
		//SQLCHAR *       data[MAXCOLS];
		SQLCHAR         errmsg[256]="";
		SQLRETURN       retcode=0;
		SQLINTEGER      i=0;
		SQLINTEGER      displaysize=0;

		//retcode = SQLDescribeCol(stmt, colnum, colname, colnamelen, &pcbColName, &coltype, &displaysize, &scale, &nullable);

		//while (TRUE)
		for(long SqlRow=0 ;; SqlRow++)
		{
			// ������� ������
			retcode = SQLFetch(hstmt);
			
			if(retcode == SQL_ERROR)
			{
				//if( !(retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) )
				//{
					LogConnectionStatus( ConnectStep, _T("�� ������� ������� ������ �� ��������� ������ �������"), true);
					break;
				//}
			}	


			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
			{
				vector<CString> v_SQLOneStr;
				for (long i=0; i<col_num; i++)
				{
					SQLDescribeCol(hstmt, i+1, colname, sizeof (colname), &colnamelen, &coltype, &collen[i], &scale, &nullable);

					if(SqlRow==0)
						v_SQLTopStr.push_back(colname);

					// get display lenght for column
					SQLColAttributes (hstmt, i+1, SQL_COLUMN_DISPLAY_SIZE, NULL, 0, NULL, &displaysize);


					// ���������� ������ ���� ����� ��������������� ������
					//*
					switch(coltype)
					{
					case SQL_CHAR:	// 1
						memset(sqf2,0,t);
						SQLGetData(hstmt, i+1, SQL_C_CHAR, sqf2, t, &sbf2);
						col2 = sqf2;
						if(col2 == _T(".000")) {col2=_T("0.000");}
						v_SQLOneStr.push_back(col2);
						break;
					case SQL_NUMERIC:	// 2
						memset(sqf2,0,t);
						SQLGetData(hstmt, i+1, SQL_C_CHAR, sqf2, t, &sbf2);
						col2 = sqf2;
						if(col2 == _T(".000")) {col2=_T("0.000");}
						v_SQLOneStr.push_back(col2);
						//SQL_C_NUMERIC
						break;
					case SQL_DECIMAL:	// 3
						memset(sqf2,0,t);
						SQLGetData(hstmt, i+1, SQL_C_CHAR, sqf2, t, &sbf2);
						col2 = sqf2;	
						if(col2 == _T(".000")) {col2=_T("0.000");}
						v_SQLOneStr.push_back(col2);
						break;
					case SQL_INTEGER:	// 4
						SQLGetData(hstmt, i+1, SQL_C_LONG, &sqf1, 0, &sbf1);
						col1 = sqf1;
						v_SQLOneStr.push_back(LintToCStr(col1));
						//SQLGetData(hstmt, i+1, SQL_C_ULONG, &sqf1, 0, &sbf1);
						break;
					case SQL_SMALLINT:	// 5
						SQLGetData(hstmt, i+1, SQL_C_SHORT, &sqf1, 0, &sbf1);
						col1 = sqf1;
						v_SQLOneStr.push_back(LintToCStr(col1));
						break;
					case SQL_FLOAT:	// 6
						//SQL_C_DOUBLE
						break;
					case SQL_REAL:	// 7
						//SQL_C_FLOAT
						break;
					case SQL_DOUBLE:	// 8
						//SQL_C_DOUBLE
						break;
					case SQL_DATETIME:	// 9 = SQL_DATE
						//SQL_C_DATE 
						break;
					case SQL_TIME:	// 10
						//SQL_C_TIME
						break;
					case SQL_TIMESTAMP:	// 11
						//SQL_C_TIMESTAMP 
						memset(sqf2,0,t);
						SQLGetData(hstmt, i+1, SQL_C_CHAR, sqf2, t, &sbf2);
						col2 = sqf2;
						if(col2 == _T(".000")) {col2=_T("0.000");}
						v_SQLOneStr.push_back(col2);
						break;
					case SQL_VARCHAR:	// 12
						memset(sqf2,0,t);
						SQLGetData(hstmt, i+1, SQL_C_CHAR, sqf2, t, &sbf2);
						col2 = sqf2;
						if(col2 == _T(".000")) {col2=_T("0.000");}
						v_SQLOneStr.push_back(col2);
						break;
					case SQL_TYPE_DATE:	// 91
						//SQL_C_TYPE_DATE 
						break;
					case SQL_TYPE_TIME:	// 92
						//SQL_C_TYPE_TIME
						break;
					case SQL_TYPE_TIMESTAMP:	// 93
						memset(sqf2,0,t);
						SQLGetData(hstmt, i+1, SQL_C_CHAR, sqf2, t, &sbf2);
						col2 = sqf2;
						if(col2 == _T(".000")) {col2=_T("0.000");}
						v_SQLOneStr.push_back(col2);
						//SQL_C_TYPE_TIMESTAMP 
						break;
					case SQL_BINARY:	// (-2)
						//SQL_C_BINARY 
						break;
					case SQL_BIT:	// (-7)
						//SQL_C_BIT 
						break;
					case SQL_GUID:	// (-11)
						//SQL_C_GUID 
						break;

					}


					// ������� ������ ������� ������, ��� �������� �� ���� ������
					if(v_SQLOneStr.size()>0)
					{v_SQLOneStr[v_SQLOneStr.size()-1].TrimRight();}
					//*/
				}

				v_SQLFullTable.push_back(v_SQLOneStr);
			}
			else
			{
				break;
			}
		}
	}
	else
	{
		//retcode
		//LogConnectionStatus( ConnectStep, _T("������ ��� �������� ��������������� ������."), true);
		//return false;
		CString ErrorStr = _T("������ ��� �������� ��������������� ������.");
		SQLWCHAR	SqlState[6], SQLStmt[100], Msg[SQL_MAX_MESSAGE_LENGTH];
		SQLINTEGER	NativeError;
		SQLSMALLINT	i, MsgLen;
		SQLRETURN	rc;

		//if ((retcode == SQL_SUCCESS_WITH_INFO) || (retcode == SQL_ERROR))
		//{
			// Get the status records.
			i = 1;
			while ((rc = SQLGetDiagRec(SQL_HANDLE_STMT, hstmt, i, SqlState, 
										&NativeError, Msg, sizeof(Msg), &MsgLen)) != SQL_NO_DATA)
			{
				//DisplayError(SqlState,NativeError,Msg,MsgLen);
				ErrorStr += Msg;
				ErrorStr += _T("\n");
				i++;
			}
			LogConnectionStatus( ConnectStep, ErrorStr, true);
		//}
		return false;
	}

	// ������������ ������������
	//if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
	//{
		//SQLFreeHandle(SQL_HANDLE_STMT, stmt);
	//}
	//SQLDisconnect(dbc);


	std::vector<CString> TitleDetector;
	std::vector<CString> OneDetector;


	// �������������� ������� ������� �� ������� ��������, ����� �� �����������
	// ��������������� ��� ������ ������� �� ������ "������ ��������"
	theApp.AllDetectors.clear();



	if(v_SQLTopStr.size()>0 && v_SQLFullTable.size()>0)
	{
		// ��������� ����� � ������ theApp.AllDetectors
		theApp.AllDetectors.push_back(v_SQLTopStr);
		for(long i=0; i<v_SQLFullTable.size(); i++) // ����� ��������� ��� �������
		{theApp.AllDetectors.push_back(v_SQLFullTable[i]);}
		//detnum //detname //detptfix //detdistance //detfilepath //detprodtype //detprodid

		// ����������� ������ �������� �� �������:
		TitleDetector = theApp.AllDetectors[0]; // ��������� ������ ������� � "������", ����� ��� �� �������� ��� ����������
		theApp.AllDetectors.erase(theApp.AllDetectors.begin()+0); // ������� �� ������� ������ ������� � ������� ����� ���� � ��������
		for (int i=0; i < theApp.AllDetectors.size(); i++) // i ���������� � 1-��, ��� ��� ������ ������� ��� �� ������
		{
			// ������ ��������������� � ����� �� ������� i � "������ �������� ���������"
			for (int j = theApp.AllDetectors.size()-1; j > i; j--)
			{
				// ���� �������� �������� ����������� � ������������ �������, �� ������ �� �������
				if ( _tstol(theApp.AllDetectors[j][0]) < _tstol(theApp.AllDetectors[j-1][0]))
				{
					//std::swap(tesr[j], tesr[j-1]);
					OneDetector.clear();
					OneDetector = theApp.AllDetectors[j];
					theApp.AllDetectors.erase(theApp.AllDetectors.begin()+j); // ������� �� ������� j-��� ������ (�������)
					theApp.AllDetectors.insert(theApp.AllDetectors.begin()+(j-1), OneDetector); // �������� j-��� ������ �� ��� �����
				}
			}
		}
		theApp.AllDetectors.insert(theApp.AllDetectors.begin(), TitleDetector); // ��������� ����� ������� � ������
		TitleDetector.clear();

		CString ErrorStr = _T("������ ���� ������� �������� �� ��.");
		LogConnectionStatus( ConnectStep, ErrorStr, false);

		return true;
	}
	else
	{
		LogConnectionStatus( ConnectStep, _T("��� ������� ������ �������� �� �� �������� ������ ����� ������."), true);
		return false;
	}

	int u=0;
}

//WriteFun2ComServerProt(Method,"",hr,CoRes.lVal);
//WriteFun2ComServerProt(Method,sProtStr,0);
//WriteFun2ComServerProt("Connect2Server","",0);
//void BGetData::WriteFun2ComServerProt(CString vFunName, CString vParams, HRESULT vHR, int vResult)
void CSOUGeneratorDlg::LogConnectionStatus(CString Step, CString ParamsOrErrReason, bool bError)
{
	CString LogFileName("sougen_logconnect.txt");


	if(bError)
	{
		//if( Step==_T("���������� � ��") || Step==_T("������� ODBC") )
		if( Step==_T("���������� � ��") || Step==_T("������") )
		{theApp.ConnectOrDB_Step = _T("������ ��� ���������� � ����� ������ (��)");}

		if(Step==_T("������ ������ �� ��"))
		{theApp.ConnectOrDB_Step = _T("������ ��� ������� ������ �� ��");}

		theApp.ConnectOrDB_Error = ParamsOrErrReason;
	}
	//AfxMessageBox(Reason);
	//bConnect=false;

	// !!!!! ������������� ������ � Ũ �������
	int ii;
	CFile lfile;
	CStringA lLine;
	//CString lLine;
	const int l_FunName_len=30, l_Params_len=188;//������������ ����� ������
	char lOrderNum[10];

	BOOL lOk = lfile.Open(LogFileName, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite);
	if(!lOk)
	{	//"���������� ������� ���� ���������, ��������� ��������� ���� ���������";
		//OpenTmpFile(LogFileName,lfile);
	}

	lfile.SeekToEnd();


	//������� ��������� ����� ���������
	if(lfile.GetLength()>5)
	{
		ii = lfile.Seek(-8,CFile::current);
		lfile.Read(lOrderNum,11);
		ii = atoi(lOrderNum);
		if(ii>999998)
			strcpy(lOrderNum,"000000");
		else
			sprintf(lOrderNum,"%06i",ii+1);
	}
	else 
	{sprintf(lOrderNum,"%06i",0);}

	//wchar_t* tmp=NULL;
	char* tmp=NULL;

	//////////////////////////////////////////////////////////////////////
	GetLocalTime(&theApp.m_CurTime);	//�������������� ��������� �����
	//lLine.Format(_T("|SOU|%02i.%02i.%04i | %02i:%02i:%02i|"),
	lLine.Format(("|SOU|%02i.%02i.%04i | %02i:%02i:%02i|"),
		theApp.m_CurTime.wDay, theApp.m_CurTime.wMonth, theApp.m_CurTime.wYear, theApp.m_CurTime.wHour, theApp.m_CurTime.wMinute, theApp.m_CurTime.wSecond);

	lfile.Write(lLine,lLine.GetLength());

//void BGetData::WriteFun2ComServerProt(CString vFunName, CString vParams, HRESULT vHR, int vResult)
//{
#if 1


	//////////////////////////////////////////////////////////////////////////
	lLine = Step;
	tmp = lLine.GetBufferSetLength(l_FunName_len);
	if(Step.GetLength()<l_FunName_len){
		//������� ������ ������ ���������
		memset(tmp+Step.GetLength(),0x20/*space char*/,l_FunName_len-Step.GetLength());
	}
	tmp[l_FunName_len] = 0;
	lLine.ReleaseBuffer();
	lfile.Write(lLine,l_FunName_len);
	lfile.Write("|",1);

	//////////////////////////////////////////////////////////////////////////
	lLine = ParamsOrErrReason;
	tmp = lLine.GetBufferSetLength(l_Params_len);
	if(ParamsOrErrReason.GetLength()<l_Params_len)
	{
		//������� ������ ������ ���������
		memset(tmp+ParamsOrErrReason.GetLength(),0x20,l_Params_len-ParamsOrErrReason.GetLength());
	}
	tmp[l_Params_len] = 0;
	lLine.ReleaseBuffer();
	lfile.Write(lLine,l_Params_len);
	lfile.Write("|",1);

/*	//////////////////////////////////////////////////////////////////////////
	lLine.Format("%10i",vHR);
	lfile.Write(lLine,10);
	lfile.Write("|",1);

	//////////////////////////////////////////////////////////////////////////
	if(vResult!=-1978)
	{
		lLine.Format("%05i",vResult);
		if(lLine.GetLength()>5) lLine = "*" + lLine.Right(4);
	}
	else
		lLine = "     ";
	lfile.Write(lLine,lLine.GetLength());
*/
	//////////////////////////////////////////////////////////////////////////
	lfile.Write("|",1);
	lfile.Write(lOrderNum,6);
	//////////////////////////////////////////////////////////////////////////
	lfile.Write("\r\n",2);
	lfile.Close();
//#else
#endif
//}

}



/*
CString CSQLTESTDlg::NumToCStr(uint64_t Num)
{
	CString CStr;
	CStr.Format( _T("%I64u"), Num ); //%i int //%u uint //%l long //%ll longlong // %I64u Ulonglong //%5d int-right5
	return CStr;
}
*/



bool CSOUGeneratorDlg::writeDetectorsFile(CString bstrXMLFile)
{
	CString ErrorStr("");

	HRESULT hResult=NULL;
	//Create the XML
	///*
//	ErrorStr = _T("������ ��� �������� �������� �� XML ������.\n(DOM)");
	//AfxMessageBox(ErrorStr);

	theApp.CurDomVer = theApp.XMLDOM;
	MSXML2::IXMLDOMDocument2Ptr pXMLDoc;	
	HRESULT hr = pXMLDoc.CreateInstance(__uuidof(DOMDocument60));
	if(FAILED(hr))
	{
		//ErrorStr = _T("������ ��� �������� �������� �� XML ������. (DOM_60)");
		LogConnectionStatus( ConnectStep, ErrorStr, false);
		MSXML2::IXMLDOMDocument2Ptr pXMLDoc;	
		HRESULT hr = pXMLDoc.CreateInstance(__uuidof(DOMDocument40));
		if(FAILED(hr))
		{
			//ErrorStr = _T("������ ��� �������� �������� �� XML ������. (DOM_40)");
			LogConnectionStatus( ConnectStep, ErrorStr, false);
			MSXML2::IXMLDOMDocument2Ptr pXMLDoc;	
			HRESULT hr = pXMLDoc.CreateInstance(__uuidof(DOMDocument30));
			if(FAILED(hr))
			{
				//ErrorStr = _T("������ ��� �������� �������� �� XML ������. (DOM_30)");
				LogConnectionStatus( ConnectStep, ErrorStr, false);
				MSXML2::IXMLDOMDocument2Ptr pXMLDoc;
				HRESULT hr = pXMLDoc.CreateInstance(__uuidof(DOMDocument));
				if(FAILED(hr))
				{
					//GetLastError();
					ErrorStr = theApp.GetErrorCSTRString(hr);
					//ErrorStr = _T("������ ��� �������� �������� �� XML ������. (DOM_00)");
					LogConnectionStatus( ConnectStep, ErrorStr, false);
					AfxMessageBox(ErrorStr);
					return false;
				}
				else
				{theApp.CurDomVer = theApp.XMLDOM_0;}
			}
			else
			{theApp.CurDomVer = theApp.XMLDOM_3;}
		}
		else
		{theApp.CurDomVer = theApp.XMLDOM_4;}
	}
	else
	{theApp.CurDomVer = theApp.XMLDOM_6;}


//	HRESULT hr = pXMLDoc.CreateInstance(__uuidof(DOMDocument60));
//LogConnectionStatus( ConnectStep, _T("3"), false);
//	if(FAILED(hr))
//	{
//		//AfxMessageBox(_T("Failed to create the XML class instance"));
//		AfxMessageBox(_T("������ ��� �������� �������� �� XML ������."));
//		return;
//	}


	_bstr_t DivisionHead(_T("<DetectorsList></DetectorsList>"));


	if(pXMLDoc->loadXML(DivisionHead) == VARIANT_FALSE)
	{
		//ShowError(pXMLDoc);
		ErrorStr = _T("�� ������� ��������� �������� ���� � ����������� ���� �������");
		AfxMessageBox(ErrorStr);
		LogConnectionStatus( ConnectStep, ErrorStr, false);
		return false;
	}

	//Get the root element just created
	MSXML2::IXMLDOMElementPtr pXMLRootElem = pXMLDoc->GetdocumentElement();
	
	if(theApp.AllDetectors.size()>1)
	{
		long NumOfDet=0;
		//NumOfDet = theApp.AllDetectors.size() - 1;		// NumOfDet = ����� �������� (�������� ������ ������ � ����������� �������) 
		NumOfDet = theApp.AllDetectors.size();

		MSXML2::IXMLDOMProcessingInstructionPtr pXMLProcessingNode =	pXMLDoc->createProcessingInstruction("xml", "version='1.0' encoding='UTF-8'");

		_variant_t vtObject;
		vtObject.vt = VT_DISPATCH;
		vtObject.pdispVal = pXMLRootElem;
		vtObject.pdispVal->AddRef();

		pXMLDoc->insertBefore(pXMLProcessingNode,vtObject);

		for(long i=0, j=0; j<NumOfDet; i++, j++)
		{
			//������ �������� �������� (����) � ����� �������� �� ���������
			if(i==0)
			{
				MSXML2::IXMLDOMElementPtr pXMLChild = pXMLDoc->createElement(_T("Title"));

				pXMLChild->setAttribute(_T("detnum"),			_variant_t(theApp.AllDetectors[i][DIV_DET_NUMBER	] ));
				pXMLChild->setAttribute(_T("detname"),			_variant_t(theApp.AllDetectors[i][DIV_DET_NAME		] ));
				pXMLChild->setAttribute(_T("detptfix"),			_variant_t(theApp.AllDetectors[i][DIV_DET_PTFIX		] ));
				pXMLChild->setAttribute(_T("detdistance"),		_variant_t(theApp.AllDetectors[i][DIV_DET_DIST		] ));
				pXMLChild->setAttribute(_T("detfilepath"),		_variant_t(theApp.AllDetectors[i][DIV_DET_PATH		] ));
				pXMLChild->setAttribute(_T("detprodtype"),		_variant_t(theApp.AllDetectors[i][DIV_DET_PRODTYPE	] ));
				pXMLChild->setAttribute(_T("detprodid"),		_variant_t(theApp.AllDetectors[i][DIV_DET_PRODID	] ));
				pXMLChild->setAttribute(_T("detprodview"),		_variant_t(theApp.AllDetectors[i][DIV_DET_PRODVIEW	] ));
				pXMLChild->setAttribute(_T("detwavespeed"),		_variant_t(theApp.AllDetectors[i][DIV_DET_WAVESPEED	] ));
				pXMLChild->setAttribute(_T("detpipeid"),		_variant_t(theApp.AllDetectors[i][DIV_DET_PIPEID	] ));
				pXMLChild->setAttribute(_T("detpipeshrtname"),	_variant_t(theApp.AllDetectors[i][DIV_DET_PIPESHNAME] ));
				pXMLChild->setAttribute(_T("detpipelenght"),	_variant_t(theApp.AllDetectors[i][DIV_DET_PIPELENGHT] ));
				pXMLChild->setAttribute(_T("detbeginname"),		_variant_t(theApp.AllDetectors[i][DIV_DET_BEGINNAME	] ));
				pXMLChild->setAttribute(_T("detendname"),		_variant_t(theApp.AllDetectors[i][DIV_DET_ENDINGNAME] ));

				//pXMLChild1->Puttext(_T("This is a child of Parent"));	//Set the element value
				pXMLChild = pXMLRootElem->appendChild(pXMLChild);

			}	//������ ������ �������� �������
			else
			{
				MSXML2::IXMLDOMElementPtr pXMLChild = pXMLDoc->createElement(_T("Detector"));	//������ � ����� ��� ��������� �������� ��������

				pXMLChild->setAttribute(_T("detnum"),			_variant_t(theApp.AllDetectors[i][DIV_DET_NUMBER	] ));
				pXMLChild->setAttribute(_T("detname"),			_variant_t(theApp.AllDetectors[i][DIV_DET_NAME		] ));
				pXMLChild->setAttribute(_T("detptfix"),			_variant_t(theApp.AllDetectors[i][DIV_DET_PTFIX		] ));
				pXMLChild->setAttribute(_T("detdistance"),		_variant_t(theApp.AllDetectors[i][DIV_DET_DIST		] ));
				pXMLChild->setAttribute(_T("detfilepath"),		_variant_t(theApp.AllDetectors[i][DIV_DET_PATH		] ));
				pXMLChild->setAttribute(_T("detprodtype"),		_variant_t(theApp.AllDetectors[i][DIV_DET_PRODTYPE	] ));
				pXMLChild->setAttribute(_T("detprodid"),		_variant_t(theApp.AllDetectors[i][DIV_DET_PRODID	] ));
				pXMLChild->setAttribute(_T("detprodview"),		_variant_t(theApp.AllDetectors[i][DIV_DET_PRODVIEW	] ));
				pXMLChild->setAttribute(_T("detwavespeed"),		_variant_t(theApp.AllDetectors[i][DIV_DET_WAVESPEED	] ));
				pXMLChild->setAttribute(_T("detpipeid"),		_variant_t(theApp.AllDetectors[i][DIV_DET_PIPEID	] ));
				pXMLChild->setAttribute(_T("detpipeshrtname"),	_variant_t(theApp.AllDetectors[i][DIV_DET_PIPESHNAME] ));
				pXMLChild->setAttribute(_T("detpipelenght"),	_variant_t(theApp.AllDetectors[i][DIV_DET_PIPELENGHT] ));
				pXMLChild->setAttribute(_T("detbeginname"),		_variant_t(theApp.AllDetectors[i][DIV_DET_BEGINNAME	] ));
				pXMLChild->setAttribute(_T("detendname"),		_variant_t(theApp.AllDetectors[i][DIV_DET_ENDINGNAME] ));

				//pXMLChild1->Puttext(_T("This is a child of Parent"));	//Set the element value
				pXMLChild = pXMLRootElem->appendChild(pXMLChild);
			}
		}
	}


	// Format the XML. This requires a style sheet
	MSXML2::IXMLDOMDocument2Ptr loadXSL;
	switch(theApp.CurDomVer)
	{
	case theApp.XMLDOM_6:
		hr = loadXSL.CreateInstance(__uuidof(DOMDocument60));
		if(FAILED(hr))
		{	//ShowError(loadXSL);
			ErrorStr = _T("������ ��� �������� �������� � ���� (XSL-�����) ����� �����. (DOM_60)");
			AfxMessageBox(ErrorStr);
			LogConnectionStatus( ConnectStep, ErrorStr, false);
			return false;
		}
		break;
	case theApp.XMLDOM_4:
		hr = loadXSL.CreateInstance(__uuidof(DOMDocument40));
		if(FAILED(hr))
		{	//ShowError(loadXSL);
			ErrorStr = _T("������ ��� �������� �������� � ���� (XSL-�����) ����� �����. (DOM_40)");
			AfxMessageBox(ErrorStr);
			LogConnectionStatus( ConnectStep, ErrorStr, false);
			return false;
		}
		break;
	case theApp.XMLDOM_3:
		hr = loadXSL.CreateInstance(__uuidof(DOMDocument30));
		if(FAILED(hr))
		{	//ShowError(loadXSL);
			ErrorStr = _T("������ ��� �������� �������� � ���� (XSL-�����) ����� �����. (DOM_30)");
			AfxMessageBox(ErrorStr);
			LogConnectionStatus( ConnectStep, ErrorStr, false);
			return false;
		}
		break;
	case theApp.XMLDOM_0:
		hr = loadXSL.CreateInstance(__uuidof(DOMDocument));
		if(FAILED(hr))
		{	//ShowError(loadXSL);
			ErrorStr = _T("������ ��� �������� �������� � ���� (XSL-�����) ����� �����. (DOM_00)");
			AfxMessageBox(ErrorStr);
			LogConnectionStatus( ConnectStep, ErrorStr, false);
			return false;
		}
		break;
	case theApp.XMLDOM:
		ErrorStr = _T("������ ��� �������� �������� � ���� (XSL-�����) ����� �����. (DOM)");
		AfxMessageBox(ErrorStr);
		LogConnectionStatus( ConnectStep, ErrorStr, false);
		return false;
		break;
	}



	_bstr_t XSL_bstr_t(_T(""));
	XSL_bstr_t += _T("<?xml version=\"1.0\" encoding=\"windows-1251\"?>");
	XSL_bstr_t += _T("\n<xsl:stylesheet version=\"1.0\" xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\">");
	XSL_bstr_t += _T("\n\t<xsl:output method=\"xml\" encoding=\"windows-1251\" indent=\"yes\"/>");
	XSL_bstr_t += _T("\n\t<xsl:template match=\"node() | @*\">");
	XSL_bstr_t += _T("\n\t\t<xsl:copy>");
	XSL_bstr_t += _T("\n\t\t\t<xsl:apply-templates select=\"node() | @*\"/>");
	XSL_bstr_t += _T("\n\t\t</xsl:copy>");
	XSL_bstr_t += _T("\n\t</xsl:template>");
	XSL_bstr_t += _T("\n</xsl:stylesheet>");

	/*
	<?xml version="1.0" encoding="windows-1251"?>
	<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
		<xsl:output method="xml" encoding="windows-1251" indent="yes"/>
		<xsl:template match="node() | @*">
			<xsl:copy>
				<xsl:apply-templates select="node() | @*"/>
			</xsl:copy>
		</xsl:template>
	</xsl:stylesheet>
	*/

	//We need to load the style sheet which will be used to indent the XMl properly.
	//if(loadXSL->load(variant_t(_T("format.xsl"))) == VARIANT_FALSE)
	if(loadXSL->loadXML(XSL_bstr_t) == VARIANT_FALSE)
	{
		//ShowError(loadXSL);
		ErrorStr = _T("������ ��� �������� �������� � ���� (XSL-�����) ����� �����.");
		AfxMessageBox(ErrorStr);
		LogConnectionStatus( ConnectStep, ErrorStr, false);
		return false;
	}

	//Create the final document which will be indented properly

	MSXML2::IXMLDOMDocument2Ptr pXMLFormattedDoc;
	switch(theApp.CurDomVer)
	{
	case theApp.XMLDOM_6:
		hr = pXMLFormattedDoc.CreateInstance(__uuidof(DOMDocument60));
		//if(FAILED(hr))
		//{
		//	AfxMessageBox(_T("������ ��� �������� �������� �� XML ������ (DOM60)."));
		//	//AfxMessageBox(_T("Failed to create the XML class instance"));
		//	return;
		//}
		break;
	case theApp.XMLDOM_4:
		hr = pXMLFormattedDoc.CreateInstance(__uuidof(DOMDocument40));
		break;
	case theApp.XMLDOM_3:
		hr = pXMLFormattedDoc.CreateInstance(__uuidof(DOMDocument30));
		break;
	case theApp.XMLDOM_0:
		hr = pXMLFormattedDoc.CreateInstance(__uuidof(DOMDocument));
		break;
	case theApp.XMLDOM:
		AfxMessageBox(_T("������ ��� �������� �������� �� XML ������ (DOM)."));
		//AfxMessageBox(_T("������ ��� �������� �������� �� XML ������ (DOM60)."));
		//AfxMessageBox(_T("Failed to create the XML class instance"));
		break;
	}

	CComPtr<IDispatch> pDispatch;
	hr = pXMLFormattedDoc->QueryInterface(IID_IDispatch, (void**)&pDispatch);
	if(FAILED(hr))
	{
		ErrorStr = _T("������ QueryInterface(IID_IDispatch) ���������� ��������.");
		AfxMessageBox(ErrorStr);
		LogConnectionStatus( ConnectStep, ErrorStr, false);
		return false;
	}

	_variant_t	vtOutObject;
	vtOutObject.vt = VT_DISPATCH;
	vtOutObject.pdispVal = pDispatch;
	vtOutObject.pdispVal->AddRef();

	//Apply the transformation to format the final document	
	hr = pXMLDoc->transformNodeToObject(loadXSL,vtOutObject);
	if(FAILED(hr))
	{
		ErrorStr = _T("���������� ������������ ��� �������������� ��������� ����������� ��������.");
		AfxMessageBox(ErrorStr);
		LogConnectionStatus( ConnectStep, ErrorStr, false);
		return false;
	}

	if(bstrXMLFile.IsEmpty())	//User forgot to set the lcoation?
		bstrXMLFile = _T("������ ��������.xml");
	hr = pXMLFormattedDoc->save(bstrXMLFile.AllocSysString());
	if(FAILED(hr))
	{
		ErrorStr = _T("������� ���������� ��������������� ����� �� ������� �������� ���������� ��������.");
		AfxMessageBox(ErrorStr);
		LogConnectionStatus( ConnectStep, ErrorStr, false);
		return false;
	}


//	pXMLDoc->Release();
//	loadXSL->Release();
//	pXMLFormattedDoc->Release();

	return true;
}




// ������� �� ������ "�����" �� ���� "���������"
LRESULT CSOUGeneratorDlg::OnDivisionChangeExit( WPARAM wparam , LPARAM lparam )
{
	WndDivisionChange=true;
	m_BtnDivisionChange.EnableWindow(TRUE);
	if(WndDivisionOpen && WndDivisionChange)
	{m_BtnCancel.EnableWindow(TRUE);}

	return 0;
}


// ������ "�������" // ������� (����/���������)
void CSOUGeneratorDlg::OnBnClickedDivisionOpen()
{
	// TODO: �������� ���� ��� ����������� �����������

	//CDivisionOpen DivisionOpenDlg;	//DivisionOpenDlg.DoModal();
	//if( DivisionOpenDlg.DoModal() == IDCANCEL ) // IDOK
	//{}

	CDivisionOpen* p_DivisionOpenDlg = new CDivisionOpen;
	p_DivisionOpenDlg->Create(IDD_DIVISION_OPEN_DLG, this);
	p_DivisionOpenDlg->ShowWindow(SW_SHOW);

	WndDivisionOpen=false;
	m_BtnDivisionOpen.EnableWindow(FALSE);
	m_BtnCancel.EnableWindow(FALSE);
}

// ������� �� ������ "�����" �� ���� "�������"
LRESULT CSOUGeneratorDlg::OnDivisionOpenExit( WPARAM wparam , LPARAM lparam )
{
	WndDivisionOpen=true;
	m_BtnDivisionOpen.EnableWindow(TRUE);
	if(WndDivisionOpen && WndDivisionChange)
	{m_BtnCancel.EnableWindow(TRUE);}

	return 0;
}

// ����� �� ����������� ������� ������ � ����������:
//bool CSOUGeneratorDlg::FileExists(LPCTSTR fname)
//{
//  return ::GetFileAttributes(fname) != DWORD(-1);
//}

// #include <io.h>
// ������� _findfirst ���������� ���������� � ������ �����, ��������������� �������� ����� ������.
bool CSOUGeneratorDlg::FileExists(const wchar_t *fname)
{
  //_finddata_t data;
  _wfinddata_t data;
  //long nFind = _findfirst(fname, &data);
  long nFind = _wfindfirst(fname, &data);
  if (nFind != -1)
  {
    // ���� ����� �� �������, �� ���������� ������ ��������
    _findclose(nFind);
    return true;
  }
  return false;
}
// � ������� ����� ������� ����� ���������� �� ������ ������������� ���������� �����, 
// �� ����� � ������ ������, ��������������� �������� �����. � ���� ������ ����� ��� "*.*", 
// �� ����� ������ ���� �� ����� � �������� ����������.


// ������ ������ ��� ���������������
CString CSOUGeneratorDlg::LintToCStr(long int x)
{
	CString strX;
	strX.Format( _T("%i"), x ); //%i for int // %d for ?? // %l for long
	return strX;
}


CString CSOUGeneratorDlg::DoubleToCStr(double x, int count) // x - �����, count - ����� ������ ����� �������
{	
	CString s_Result;
	CString s_Format("%.");

	CString strX;
	strX.Format( _T("%i"), count );

	s_Format = s_Format + strX;
	s_Format = s_Format + _T("f");

	s_Result.Format( s_Format, x );
	return s_Result;
}


char* CSOUGeneratorDlg::CStrAToChar(CStringA origa)
{
	//CStringA origa("Hello, World!");
	const size_t newsizea = (origa.GetLength() + 1);
	char *nstringa = new char[newsizea];
	strcpy_s(nstringa, newsizea, origa);
	return nstringa;
	//cout << nstringa << " (char *)" << endl;
}

// Convert to a char* string from a wide character CStringW string.
// To be safe, we allocate two bytes for each character in the 
// original string, including the terminating null.

char* CSOUGeneratorDlg::CStrWToChar(CStringW origw)
{
	//CStringW origw("Hello, World!");
	const size_t newsizew = (origw.GetLength() + 1)*2;
	char *nstringw = new char[newsizew];
	size_t convertedCharsw = 0;
	wcstombs_s(&convertedCharsw, nstringw, newsizew, origw, _TRUNCATE );
	return nstringw;
	//cout << nstringw << " (char *)" << endl;
}


void CSOUGeneratorDlg::OnEnChangeTestEdit()
{
	// TODO:  ���� ��� ������� ���������� RICHEDIT, �� ������� ���������� �� �����
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	m_EditTest.Undo();

	// TODO:  �������� ��� �������� ����������
}

//*
BOOL CSOUGeneratorDlg::PreTranslateMessage(LPMSG pMsg)
{
/*
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
    {
        CWnd* pFocus = GetFocus();
        if (pFocus && pFocus->IsKindOf(RUNTIME_CLASS(CEdit)))
        {
            NextDlgCtrl();
            return TRUE;
        }
    }

	return CDialog::PreTranslateMessage(pMsg);
*/



/*
	switch (pMsg->message)
	{
	case WM_KEYDOWN:
		switch (pMsg->wParam)
		{
		case VK_TAB:// ������ ������� TAB.
			AfxMessageBox(_T("TAB"));
		case VK_RETURN:// ������ ������� ENTER.
			//AfxMessageBox(_T("ENTER"));
			pMsg->wParam = VK_TAB;
		break;
		case VK_UP: // ������ ������� �����.
			AfxMessageBox(_T("UP"));
		break;
		case VK_DOWN: // ������ ������� ����.
			AfxMessageBox(_T("DOWN"));
		break;
		/*
		case VK_LEFT: // ������ ������� �����.
		break;
		case VK_RIGHT: // ������ ������� �����.
		break;
		case VK_HOME: // ������ ������� HOME.
		break;
		case VK_END:// ������ ������� END.
		break;
		case VK_INSERT:// ������ ������� INS.
		break;
		case VK_DELETE:// ������ ������� DEL.
		break;
		case VK_F2:// ������ ������� F2.
		break;
		// ��������� ������ ��-��������� ������.
		default:
			break;
		*/
//		}
//	}

	//if( (WM_KEYDOWN == pMsg->message) && (VK_RETURN == pMsg->wParam ) )
    //{	// process enter key pressing
	//	int o=0;
	//	AfxMessageBox(_T("Enterted"));
    //}

//	return FALSE;
	return CDialog::PreTranslateMessage(pMsg);
}


//LONG APIENTRY MainWndProc(HWND hwndMain, UINT uMsg, WPARAM wParam, LPARAM lParam)
//LRESULT CALLBACK CSOUGeneratorDlg::MainWndProc ( HWND hwndMain, UINT uMsg, WPARAM wParam, LPARAM lParam)
////LRESULT CALLBACK CSOUGeneratorDlg::MainWndProc ( HWND hwndMain, UINT uMsg, WPARAM wParam, LPARAM lParam)
////{

/*
//LRESULT CALLBACK CSOUGeneratorDlg::MainWndProc ( HWND hwndMain, UINT uMsg, WPARAM wParam, LPARAM lParam)
BOOL CSOUGeneratorDlg::PreTranslateMessage(LPMSG pMsg)
{
    //if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	HWND hwndMain = pMsg->hwnd;
	UINT uMsg = pMsg->message;
	WPARAM wParam = pMsg->wParam;
	LPARAM lParam = pMsg->lParam;


	HDC hdc;                   // ���������� ��������� ����������
    TEXTMETRIC tm;             // ��������� � ����������� ������
    static DWORD dwCharX;      // ������� ������ ��������
    static DWORD dwCharY;      // ������ ��������
    static DWORD dwClientX;    // ������ ���������� �������
    static DWORD dwClientY;    // ������ ���������� �������
    static DWORD dwLineLen;    // ����� ������
    static DWORD dwLines;      // ���-�� ����� � ���������� �������
    static int nCaretPosX = 0; // �������������� ���������� �������
    static int nCaretPosY = 0; // ������������ ���������� �������
    static int nCharWidth = 0; // ������ �������
    static int cch = 0;        // ���-�� �������� � ������
    static int nCurChar = 0;   // ����� �������� �������
    //static PTCHAR pchInputBuf; // ����� �����
    int i, j;                  // �������� �����
    int cCR = 0;               // ������� ��������� �������
    int nCRIndex = 0;          // ����� ���������� �������� �������
    int nVirtKey;              // ��� ����������� �������
    TCHAR szBuf[128];          // ��������� �����
    TCHAR ch;                  // ������� ������
    PAINTSTRUCT ps;            // ��������� ��� BeginPaint
    RECT rc;                   // ������������� ��� DrawText
    SIZE sz;                   // ����������� ������
    COLORREF crPrevText;       // ���������� ���� ������
    COLORREF crPrevBk;         // ���������� ���� ����
	size_t * pcch;
	HRESULT hResult;

    switch (uMsg)
    {
////////////////////////////////////////////////////////////////
        case WM_CREATE:

            // �������� ��������� �������� ������. 
            hdc = ::GetDC(hwndMain);
            GetTextMetrics(hdc, &tm);
            ::ReleaseDC(hwndMain, hdc);

            // ��������� ������� ������ � ������ �������.
            dwCharX = tm.tmAveCharWidth;
            dwCharY = tm.tmHeight;

            // �������� ����� ��� �������� ����� � ����������.
            pchInputBuf = (LPTSTR) GlobalAlloc(GPTR, BUFSIZE * sizeof(TCHAR));
            return 0;
////////////////////////////////////////////////////////////////
        case WM_SIZE:

            // ��������� ����� ������ � ������ ���������� �������.
            dwClientX = LOWORD(lParam);
            dwClientY = HIWORD(lParam);

            // ��������� ������������ ������ ������ � ������������
            // ���������� ����� � ���������� �������.
            dwLineLen = dwClientX - dwCharX;
            dwLines = dwClientY / dwCharY;
            break;

////////////////////////////////////////////////////////////////
        case WM_SETFOCUS:

            // ����� ���� �������� �����, �� ������, ������������� � ���������� �������.
			tagPOINT pnt;
			pnt.x = nCaretPosX;
			pnt.y = nCaretPosY;

            ::CreateCaret(hwndMain, (HBITMAP) 1, 0, dwCharY);
			::SetCaretPos(nCaretPosX, nCaretPosY * dwCharY);
            ::ShowCaret(hwndMain);
            break;
////////////////////////////////////////////////////////////////
        case WM_KILLFOCUS:

            // ����� ���� ������ �����, �� �������� �
            // ���������� �������.
            ::HideCaret(hwndMain);
            DestroyCaret();
            break;
////////////////////////////////////////////////////////////////
        case WM_CHAR:
		// ���������, �� ��������� �� ������� ��������� ������
		// � ����� ������, ����� �� ��������� ��� ������������.
		// ���� ���, �� ��������� ���� � ���������� ����������.
			if (cch > BUFSIZE-5)
			{
				pchInputBuf[cch] = 0x00;
				::SendMessage(hwndMain, WM_PAINT, 0, 0);
			}
            switch (wParam)
            {
                case 0x08:  // backspace
                case 0x0A:  // ������� ������
                case 0x1B:  // esc
                    MessageBeep((UINT) -1);
                    return 0;

                case 0x09:  // tab

                    // ����������� ���� � ������ ���������������� �������.
                    for (i = 0; i < 4; i++)
                        ::SendMessage(hwndMain, WM_CHAR, 0x20, 0);
                    return 0;

                case 0x0D:  // ������� �������

                    // ���������� ������� ������� � � �������
                    // � ������ ����� ������.
                    pchInputBuf[cch++] = 0x0D;
                    nCaretPosX = 0;
                    nCaretPosY += 1;
                    break;

                default:    // ������������ �������
                    ch = (TCHAR) wParam; 
                    ::HideCaret(hwndMain); 

                    // �������� ������ ������� � �������
                    // ������.
                    hdc = ::GetDC(hwndMain);
                    GetCharWidth32(hdc, (UINT) wParam, (UINT) wParam, &nCharWidth);
                    TextOut(hdc, nCaretPosX, nCaretPosY * dwCharY, &ch, 1);
                    ::ReleaseDC(hwndMain, hdc);

                    // Store the character in the buffer.
                    pchInputBuf[cch++] = ch;

                    // ��������� ����� �������������� ��������� �������.
                    // ���� ���������� �������� ���������, �� ���������
                    // ������� ������� � ���������� �������
                    // � ������ ��������� ������.

                    nCaretPosX += nCharWidth;
                    if ((DWORD) nCaretPosX > dwLineLen)
                    {
                        nCaretPosX = 0;
                        pchInputBuf[cch++] = 0x0D;
                        ++nCaretPosY;
                    }
                    nCurChar = cch;
                    ::ShowCaret(hwndMain);
                    break;
            }
            ::SetCaretPos(nCaretPosX, nCaretPosY * dwCharY);
            break;
////////////////////////////////////////////////////////////////
        case WM_KEYDOWN:
            switch (wParam)
            {
                case VK_LEFT:   // ������� �����
 
                    // ������� ����� ���� ���������� ������
                    // � ������ ������� ������.
                    if (nCaretPosX > 0)
                    {
                        ::HideCaret(hwndMain);

                        // �������� ������ ����� �� �������, ���������
                        // ������ ��������, � ����� �������� ������
                        // �� ������� �������������� ����������
                        // �������, ����� �������� ����� ����������

						ch = pchInputBuf[--nCurChar]; 
                        hdc = ::GetDC(hwndMain); 
                        GetCharWidth32(hdc, ch, ch, &nCharWidth); 
                        ::ReleaseDC(hwndMain, hdc); 
                        nCaretPosX = max(nCaretPosX - nCharWidth, 0); 
                        ::ShowCaret(hwndMain); 
                    } 
                    break; 
 
                case VK_RIGHT:  // ������� ������
 
                    // ���������� ������� ������ ���, ���� ���������
                    // ������� �������, � ������ ��������� ������.
 
                    if (nCurChar < cch)
                    {
                        ::HideCaret(hwndMain);

                        // �������� ������ ������ �� �������.
                        // ���� ��� ������� �������, �� ����������
                        // ������ � ������ ��������� ������.
 
                        ch = pchInputBuf[nCurChar];
                        if (ch == 0x0D)
                        {
                            nCaretPosX = 0;
                            nCaretPosY++;
                        }

                        // ���� ������ �� �������� ��������� �������,
                        // �� ���������, �� ������ �� ������� SHIFT.
                        // ���� ���, �� ����������� ����� ������
                        // � ������� ������.
 
                        else
                        {
                            hdc = ::GetDC(hwndMain);
                            nVirtKey = GetKeyState(VK_SHIFT);
                            if (nVirtKey & SHIFTED)
                            {
                                crPrevText = SetTextColor(hdc, RGB(255, 255, 255));
                                crPrevBk = SetBkColor(hdc, RGB(0,0,0));
                                TextOut(hdc, nCaretPosX, nCaretPosY * dwCharY, &ch, 1);
                                SetTextColor(hdc, crPrevText);
                                SetBkColor(hdc, crPrevBk);
                            }

                            // �������� ������ ������� � ���������
                            // ����� �������������� ���������� �������.
 
                            GetCharWidth32(hdc, ch, ch, &nCharWidth);
                            ::ReleaseDC(hwndMain, hdc);
                            nCaretPosX = nCaretPosX + nCharWidth;
                        }
                        nCurChar++;
                        ::ShowCaret(hwndMain);
                        break;
                    }
                    break;

                case VK_UP:     // ������� �����
                case VK_DOWN:   // ������� ����
                    MessageBeep((UINT) -1);
                    return 0;

                case VK_HOME:   // HOME
                    // ������������� ������� � ������� �����
                    // ���� ���������� �������.
 
                    nCaretPosX = nCaretPosY = 0;
                    nCurChar = 0;
                    break;

                case VK_END:    // END
                    // ���������� ������� � ����� ������.
                    for (i=0; i < cch; i++)
                    {
                        // ������� �������� ������� � ��������� �� ������.
                        if (pchInputBuf[i] == 0x0D)
                        {
                            cCR++;
                            nCRIndex = i + 1;
                        }
                    }
                    nCaretPosY = cCR;

                    // �������� ���� ����� ����� ��������� ���������
                    // ������� � ���������� ����� � ����������
                    // �� ��������� �����.
 
                    for (i = nCRIndex, j = 0; i < cch; i++, j++)
                        szBuf[j] = pchInputBuf[i];
                    szBuf[j] = TEXT('\0');

                    // ������������� �������������� ���������� �������.
 
                    hdc = ::GetDC(hwndMain);

			//hResult = ::StringCchLength(szBuf, 128, pcch);
			//if (FAILED(hResult))
			//{
			// ���������� ������
			//}
                    GetTextExtentPoint32(hdc, szBuf, *pcch, &sz);
                    nCaretPosX = sz.cx;
                    ::ReleaseDC(hwndMain, hdc);
                    nCurChar = cch;
                    break;

                default:
                    break;
            }
            ::SetCaretPos(nCaretPosX, nCaretPosY * dwCharY);
            break;
////////////////////////////////////////////////////////////////
        case WM_PAINT:
            if (cch == 0)       // � ������ ����� ������ ���
                break;

            hdc = ::BeginPaint(hwndMain, &ps);
            ::HideCaret(hwndMain);

            // ������������� ������� ��������������, � �����
            // ������ � �� �����.

            SetRect(&rc, 0, 0, dwLineLen, dwClientY);
            DrawText(hdc, pchInputBuf, -1, &rc, DT_LEFT);

            ::ShowCaret(hwndMain);
            ::EndPaint(hwndMain, &ps);
            break;

        // ������������ ������ ���������.
////////////////////////////////////////////////////////////////
        case WM_DESTROY:
            PostQuitMessage(0);

            // ����������� ����� �����.
 
            GlobalFree((HGLOBAL) pchInputBuf);
            UnregisterHotKey(hwndMain, 0xAAAA);
            break;
////////////////////////////////////////////////////////////////
        default:
            return ::DefWindowProc(hwndMain, uMsg, wParam, lParam);
			}
    return NULL;
}
*/


void CSOUGeneratorDlg::OnBnClickedTestBtn()
{
	// TODO: �������� ���� ��� ����������� �����������
	CTestDlg* p_TestDlg = new CTestDlg;
	p_TestDlg->Create(IDD_TEST_DLG, this);
	p_TestDlg->ShowWindow(SW_SHOW);

	TestDlgHWND = p_TestDlg->GetSafeHwnd();
}


/*
CString CSOUGeneratorDlg::DocErrorGetErrorInRus(CString DescriptionEng)
{
	return _T("��������� ����� �� ������������� ����������� ���.");

	if(DescriptionEng == _T("No error") )
	{return _T("��� ������");}
	else	if(DescriptionEng == _T("Error") )
	{return _T("������������� ������");}
	else 	if(DescriptionEng == _T("Failed to open file") )
	{return _T("������ ��� �������� �����");}
	else 	if(DescriptionEng == _T("Error parsing Element.") )
	{return _T("������ ��� ������� (��������) ��������");}
	else 	if(DescriptionEng == _T("Failed to read Element name") )
	{return _T("������ ��� ������ ����� ��������");}
	else 	if(DescriptionEng == _T("Error reading Element value.") )
	{return _T("������ ��� ������ �������� ��������");}
	else 	if(DescriptionEng == _T("Error reading Attributes.") )
	{return _T("������ ��� ������ ��������");}
	else 	if(DescriptionEng == _T("Error: empty tag.") )
	{return _T("������ - ������ ���");}
	else 	if(DescriptionEng == _T("Error reading end tag.") )
	{return _T("������ ��� ������ ���������� ����");}
	else 	if(DescriptionEng == _T("Error parsing Unknown.") )
	{return _T("������������� ������ �� ����� ������� (��������) �����");}
	else 	if(DescriptionEng == _T("Error parsing Comment.") )
	{return _T("������ ��� ������ (��������) �����������");}
	else 	if(DescriptionEng == _T("Error parsing Declaration.") )
	{return _T("������ ��� ������ (��������) ���������� (���������) �����");}
	else 	if(DescriptionEng == _T("Error document empty.") )
	{return _T("������ - ���� ���� (��� ���������� ������ ������)");}
	else 	if(DescriptionEng == _T("Error null (0) or unexpected EOF found in input stream.") )
	{return _T("������ NULL (0) ��� ��������� �������������� ����� ����� �� �������� ������");}
	else 	if(DescriptionEng == _T("Error parsing CDATA.") )
	{return _T("������ ��� ������ (��������) CDATA");}
	else 	if(DescriptionEng == _T("Error when TiXmlDocument added to document, because TiXmlDocument can only be at the root.") )
	{return _T("Error when TiXmlDocument added to document, because TiXmlDocument can only be at the root");}
}
*/





