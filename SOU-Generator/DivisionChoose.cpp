// DivisionChoose.cpp: ���� ����������
//

#include "stdafx.h"
#include "SOU-Generator.h"
#include "SOU-GeneratorDlg.h"
#include "DivisionChoose.h"
#include "DivisionEdit.h"
#include "afxdialogex.h"

#include <io.h>
#include <map>
#include <algorithm>

#include "TElem.h"

#define DET_NUMBER		0
#define DET_NAME		1
#define DET_POSTFIX		2
#define DET_DISTANCE	3
#define DET_FILE_PATH	4
#define DET_PROD_TYPE	5
#define DET_PROD_ID		6
#define DET_PROD_VIEW	7
#define DET_WAVE_SPEED	8
#define DET_PIPE_ID		9
#define DET_PIPE_SHNAME	10
#define DET_PIPE_LENGHT	11
#define DET_BEGIN_NAME	12
#define DET_END_NAME	13


#define DIV_LIST_PIPE	0
#define DIV_LIST_PROD	1
#define DIV_LIST_NAME	2

#define DIV_DIV_NAME	0  
#define DIV_PIPE_NAME	1  
#define DIV_PIPE_ID		2  
#define DIV_PROD_NAME	3  
#define DIV_PROD_ID		4  
#define DIV_PARAMETR	5  
#define DIV_WATCH		6  
#define DIV_WAVE		7  
#define DIV_DTCT_TIME	8  
#define DIV_PIPE_LENGTH	9  
#define DIV_BEGIN_NAME	10 
#define DIV_END_NAME	11 

#define DIV_DET_NAME	0
#define DIV_DET_NUMBER	1
#define DIV_DET_ACTIVE	2
#define DIV_DET_PATH	3
#define DIV_DET_PTFIX	4
#define DIV_DET_DIST	5
#define DIV_DET_DPRESS	6
#define DIV_DET_DTIIME	7
//#define DIV_DET_DISTBEG	8
//#define DIV_DET_DISTEND	9

// �������� ��� theApp.AllDivisions
#define DIVALL_FILE_NAME	0
#define DIVALL_DIV_NAME		0  +1
#define DIVALL_PIPE_NAME	1  +1
#define DIVALL_PIPE_ID		2  +1
#define DIVALL_PROD_NAME	3  +1
#define DIVALL_PROD_ID		4  +1
#define DIVALL_PARAMETR		5  +1
#define DIVALL_WATCH		6  +1
#define DIVALL_WAVE			7  +1
#define DIVALL_DTCT_TIME	8  +1
#define DIVALL_PIPE_LENGTH	9  +1
#define DIVALL_BEGIN_NAME	10 +1
#define DIVALL_END_NAME		11 +1

// ���������� ���� CDivisionChoose

IMPLEMENT_DYNAMIC(CDivisionChoose, CDialog)

CDivisionChoose::CDivisionChoose(CWnd* pParent /*=NULL*/)
	: CDialog(CDivisionChoose::IDD, pParent)
{
	//iCtrListItem=0;
	bFirstDlg=false;
}

CDivisionChoose::~CDivisionChoose()
{
}

void CDivisionChoose::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_BtnOK);
	DDX_Control(pDX, IDCANCEL, m_BtnDiv_Exit);
	DDX_Control(pDX, IDC_DEV_CHANGE_LIST, m_DivChangeList);
	DDX_Control(pDX, IDC_DIV_ADD_BTN, m_BtnDiv_Add);
	DDX_Control(pDX, IDC_DIV_DEL_BTN, m_BtnDiv_Del);
	DDX_Control(pDX, IDC_DIV_EDIT_BTN, m_BtnDiv_Change);
	DDX_Control(pDX, IDC_DIV_LOOK_BTN, m_BtnDiv_Look);
	DDX_Control(pDX, IDC_DIV_COPY_BTN, m_BtnDiv_Copy);
	DDX_Control(pDX, IDC_DIV_VALID_BTN, m_BtnDiv_Valid);
}


BEGIN_MESSAGE_MAP(CDivisionChoose, CDialog)
	ON_BN_CLICKED(IDC_DIV_ADD_BTN, &CDivisionChoose::OnBnClickedDivAddBtn)
	ON_BN_CLICKED(IDC_DIV_EDIT_BTN, &CDivisionChoose::OnBnClickedDivEditBtn)
	ON_BN_CLICKED(IDC_DIV_DEL_BTN, &CDivisionChoose::OnBnClickedDivDelBtn)
	ON_BN_CLICKED(IDCANCEL, &CDivisionChoose::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_DIV_LOOK_BTN, &CDivisionChoose::OnBnClickedDivLookBtn)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_DEV_CHANGE_LIST, &CDivisionChoose::OnLvnItemchangedDevChangeList)
	ON_MESSAGE(WM_DIVISION_EDIT_SAVE, &CDivisionChoose::OnDivisionEditSave)
	ON_MESSAGE(WM_DIVISION_EDIT_EXIT, &CDivisionChoose::OnDivisionEditExit)
	ON_BN_CLICKED(IDOK, &CDivisionChoose::OnBnClickedOk)
	ON_BN_CLICKED(IDC_DIV_COPY_BTN, &CDivisionChoose::OnBnClickedDivCopyBtn)
	ON_BN_CLICKED(IDC_DIV_VALID_BTN, &CDivisionChoose::OnBnClickedDivValidBtn)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// ����������� ��������� CDivisionChoose

BOOL CDivisionChoose::OnInitDialog()
{
	CDialog::OnInitDialog();

	//HWND HwndDivChangeDlg=NULL;
	//::GetDlgItem(HwndDivChangeDlg, IDD_DIVISION_CHOOSE_DLG);
	//HWND* HwndDivChangeDlg=NULL;
	//GetDlgItem(IDD_DIVISION_CHOOSE_DLG, HwndDivChangeDlg);
	//theApp.hWnd_DivisionChooseDlg = HwndDivChangeDlg;

	theApp.AllDivisions.clear();
	theApp.ErrDivisions.clear();


	m_BtnOK.ShowWindow(FALSE);

	CString DivisionFileName(""); // ��� ����� ���������� ������� ()
	CString wStr(""); // ��� ���������� �������
	//CString wStr_DivName(""); // ��� ���������� �������
	//CString wStr_Product(""); // ������� �� ������ �������
	CString EmptyStr("");
	theApp.AllDivisionsFileNames.clear();

	//for(int i = 0; i < 5; i++)
	//{
	//	cs.Format(_T("������� � %d"), i+1);
	//	m_DivChangeList.InsertItem(i, cs);
	//}


	CRect rect;
	m_DivChangeList.GetClientRect(rect);
	m_DivChangeList.RedrawItems(0,0);

	bool badXml=false;		// ��������� �� ��, ��� ���� ������� ������ ���� ������������ ������� 
	bool changeXml=false;	// ����� ��� �������� ���������� �� ���-�� � ������ �������� ������ ������� (����������)
	int  ichangeXml=0;		// ���� ������ ��� 0, �� ��������� ��������� ����� � ����� �������

	std::vector<CString> OneDivision;
	// ��������� ������ ���������� �������� ��������� �������� ������ .sou �� ����� "�������"
	if(theApp.CurDivisionsPath != EmptyStr)
	{
		CString sPath = theApp.CurDivisionsPath;
		CFileFind hFile;
		bool bFound = false;
		bFound = hFile.FindFile( sPath + _T("\\*.sou") );

		(void)m_DivChangeList.SetExtendedStyle( LVS_EX_FULLROWSELECT );
		m_DivChangeList.SetHeadings( _T("�����������,		110;\
										�������,			80;\
										�������� ��������,	300"
									   ) );
		m_DivChangeList.LoadColumnInfo();

		//m_DivChangeList.InsertColumn(0, _T("�����������"), LVCFMT_LEFT, 90);
		//m_DivChangeList.InsertColumn(1, _T("�������"), LVCFMT_LEFT, 90);
		//m_DivChangeList.InsertColumn(2, _T("�������� ��������"), LVCFMT_LEFT, 400); //rect.Width() );
		
		long LBiter=0;
		while ( bFound )
		{
			bFound = hFile.FindNextFile();
			//if( (! hFile.IsDots()) && ( hFile.IsDirectory() ) )		
			if( ! hFile.IsDots() )
			{
				DivisionFileName = hFile.GetFileName();

				CString szExt = _tcsrchr(DivisionFileName, '.'); // �������� szExt = ".sou"
				if(szExt == _T(".sou"))
				{
					// ������� ��������� 4 ������� �� ����� ������� �����
					DivisionFileName.Delete(DivisionFileName.GetLength() - szExt.GetLength(), 4);
					// ��������� ������ � ��� ������, ���� ���������� .sou ����
					//m_DivChangeList.InsertItem(LBiter, DivisionFileName);

/////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// �������� �� ���� .SOU ������ �������� ���� "�������"
					CString IniFileName = theApp.IniFileName;
					CString CurDivisionsPath = theApp.CurDivisionsPath;

					// ���������� �������� �������� ��������������� ������ � ����������� .sou �� ������� ���� !!!!!
					// http://www.rsdn.ru/article/qna/baseserv/fileexist.xml

					CString DivPathWithFiles("");
					CString DivPath("");
	
					DivPath = theApp.CurDivisionsPath;
					DivPathWithFiles = DivPathWithFiles + DivPath + _T("\\*.sou");

					//const wchar_t* _DivPathWithFiles = new wchar_t [_MAX_PATH];  // �������� delete[] � ����� !!!
					//_DivPathWithFiles = DivPathWithFiles;

					if( !FileExists(DivPathWithFiles) )
					{
						MessageBox( _T("� ����� � ��������� ����������� ����� ��������\n ���������, ���:\n")
									_T("1) ����� \"�������\" ��������� � ��� �� �����, ��� � �������.\n")
									_T("2) � ����� ������� ����� � ����������� .sou"),
									_T("������"), MB_ICONERROR);
					}

					//CIniParam parInjProd1 (CBLOWApp::IniFileName, _T("Injection"), _T("InjProd1"));
					//parInjProd1.Set(m_InjProducts[0]);
					//parInjProd1.Save();


					// ����� ����������� �������� �����
					OneDivision.push_back(DivisionFileName);		// [0] - �������� �����

					//theApp.ErrDivisions.push_back(OneDivision);
					theApp.AllDivisions.push_back(OneDivision);

					// 2 ��������� ��� �������� �� .SOU ����� �������, ���� ������� ���������� � ������, � ��������� ��� 
					//	 ��������� � �������������� �������, � �������� theApp, ��� ���������/����������/��������� ����� �������
					//	 ������ �������� ������ � ���� �� ����� ���������� ��� �������� ��������������� �������� ��� ��������� 
					//	 ��������� ���������� ������� � ��� ���������������� ����� ����� 
	
					//CString FileName("������ ������.sou"); 
					CString DivisionFilePath("");
					DivisionFilePath =  CurDivisionsPath + _T("\\") + DivisionFileName + _T(".sou");
					//MessageBox(	DivisionFilePath, _T("PATH"), 0 );
					////CStringA p_FilePath(DivisionFilePath);

//*
					_bstr_t DivisionFilePathBstr = DivisionFilePath;
					_bstr_t bstrOutput("");
					bool validXml=false;
					//bool changeXml=false; // ������ �� ����������
					HRESULT hr = CoInitialize(NULL);
					if(SUCCEEDED(hr))
					{
						try{
							changeXml=false;
						// 1 �������� // SOU-����� �������. ��������� ���������, ����������� ���� �����, ������� ���� �����/���������
							bstrOutput = theApp.validateDivFile(DivisionFilePathBstr, validXml);
							//CString cstrOutput = (LPCTSTR)bstrOutput;
						// 2.1 �������� // SOU-����� �������. �������� ����������. ������ ��������+������� � ��������
										// SOU-����� �������. �������� �������� �� ������� � ��������� ���� �� �������� � ���� ��������
							if(validXml)
							{
							bstrOutput = validateDivFileByDetKeyAndDetMaxNum(DivisionFilePath, validXml);
							}

							if(validXml)
							{
							// 2.3 �������� // SOU-����� �������. �������� ���������� ��������: ���� ���� ������, ���������� �������������
								bstrOutput = correctDivFileByDetParams(DivisionFilePath, DivisionFileName, changeXml);
							// ��������� � ��� ���������� ��������� ������ ���� ������� ���� !!!
							// � ���������� bstrOutput
								if(changeXml) // =true ������ ��������� � SOU-���� ���� �������
								{
									if(ichangeXml==0)
									{ichangeXml++;}
							// 2.4 ��������� � ��� ���������� �� ���������, �� ���������� ������. !!!!!
									// ������� ��������� � ��� ���������� � ������������ ������
									CString LogFileName("sougen_logfiles.txt");
									CString DotSOU(".sou");
									CString lLine;

									CStdioFile cfile_object_write;
									BOOL lOk = cfile_object_write.Open(LogFileName, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite);
									cfile_object_write.SeekToEnd();

									CString LogFiles("");
									CString LogPath("");


									GetLocalTime(&theApp.m_CurTime);	//�������������� ��������� �����

									LogFiles += _T("*******************************************************************************************************************************\n");
									lLine.Format(_T("|SOU|%02i.%02i.%04i | %02i:%02i:%02i|******************************************************************************************\n"),
										theApp.m_CurTime.wDay, theApp.m_CurTime.wMonth, theApp.m_CurTime.wYear, theApp.m_CurTime.wHour, theApp.m_CurTime.wMinute, theApp.m_CurTime.wSecond);

									LogFiles += lLine;
									LogFiles += LPCTSTR(bstrOutput);

									LogPath = LogPath + theApp.IniFilePath + LogFileName;

									CStringA LogPathA(LogPath);
									CStringA LogFilesA(LogFiles);

									// ����� ���������� �� � log-����
									//CFile cfile_object_write( AllClFileNameFin, CFile::modeCreate|CFile:: modeReadWrite);

									//CFile cfile_object_write( LogFileName, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite);
									//cfile_object_write.SeekToEnd();
									cfile_object_write.Write( LogFilesA, LogFilesA.GetLength());
									cfile_object_write.Close();
								}
							}
						}
						catch(_com_error &e)
						{
							badXml=true;
							bstrOutput = theApp.dump_com_error(e);
						}
					}

					if(validXml) // ������, ����� ���� "��������" � ����� ��������� ����� �������
 					{
						readDivisionHeadFile(DivisionFilePath);
						//theApp.ErrDivisions.erase(  theApp.ErrDivisions.begin() + (theApp.ErrDivisions.size()-1)  );
					}
					else //if(!validXml)
					{
						badXml=true;

						// �� ����� ��������� ������� �������� ������, ���� ������� ����������
						// ��� ����������������� ��������� ������� � ���. � ������������ � ���� ������� ����� ���������� ������ � �� �����. 
						//MessageBox(bstrOutput, L"������ � ����� ��� ��� ��������", MB_OK);
						//return TRUE;
						//theApp.ErrDivisions.push_back(DivisionFileName)

						OneDivision.push_back( (LPCTSTR)bstrOutput );
						theApp.ErrDivisions.push_back( OneDivision );

						theApp.AllDivisions.erase(  theApp.AllDivisions.begin() + (theApp.AllDivisions.size()-1)  );


						// ����������� ������������ ������ !

						// �������������� ������ ����� ��� �� ��������, ���� ������� ���
						int CreationResult = CreateDirectory(theApp.CurDivisionsPath + _T("//Bad"), NULL);
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

						// ������� ��� �������������� ����� WinAPI
						// MoveFile � DeleteFile ����� ��������� FALSE ���� �������� �� �����������.
						MoveFile(DivisionFilePath, CurDivisionsPath + _T("//Bad") + _T("\\") + DivisionFileName + _T(".sou") );
						DeleteFile(DivisionFilePath);
					}
					CoUninitialize();
//*/
////////////////////////////////////// ��������� ������
					// ����� ������������ ��� ����� �������: 
					//m_DivChangeList.InsertItem(LBiter, DivisionFileName);
					// ��� ��� ��� ����� ������:
					//m_DivChangeList.SetItemText(LBiter, 0, DivisionFileName);
					//m_DivChangeList.SetItemText(LBiter, 1, wStr_Product);



					//////// ������ ������������ �������� �������:
					//////// m_DivChangeList.InsertItem(LBiter, wStr_DivName);
					//////// ��� ��� ��� ����� ������:
					//////// m_DivChangeList.SetItemText(LBiter, 0, wStr_DivName);
					//////// m_DivChangeList.SetItemText(LBiter, 1, wStr_Product);

					/////////////////////////////////////////////////////////////////////////////
					// 1 // ��������� � ����� ��� ��� �������� ��� ��������� ������� ���������
					//theApp.AllDivisionsFileNames.push_back(DivisionFileName);
				}
				//AfxMessageBox(DivisionFileName);
			}
			LBiter++;
			OneDivision.clear();
		}

		//////// m_DivChangeList.SetExtendedStyle( m_DivChangeList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	}


	// 2.5 ����� ��������� �� ���������, �� ���������� ������. !!!!!
	//if(changeXml) // =true ������ ��������� � SOU-���� ���� �������
	if(ichangeXml>0) // >0 ������ ��������� � �����-�� �� SOU-������ ���� �������
	{
		CString LogPath("");
		CString MesFiles("");

		// ������� ��������� � ��� ���������� � ������������ ������
		CString LogFileName("sougen_logfiles.txt");
		LogPath = LogPath + theApp.IniFilePath + LogFileName;
		CStringA LogPathA(LogPath);

		MesFiles += _T("��� �������� ������ �������� ���� ������� � ������������� ���������� ������.\n");
		MesFiles += _T("������ ������� � ��������������� ���������� � ������ �������� ��������� � ��.\n");
		MesFiles += _T("���� � ��������� ��������� � ������ �������� ��������� �:\n");
		MesFiles = MesFiles + theApp.IniDivisionsPath + _T("\\") + LogFileName;

		// ������� ��� �� � ���������, � ��� ��� LOG-���� ����� ������, �� � ��������� ���.
		int msgboxID = AfxMessageBox(MesFiles);
		//if(msgboxID == IDOK)
	}


	/////////////////////////////////////////////////////////////////////////////
	// 2 // ����� ��������� ���� ���������� �������, ���� ��� ��������� ����������� �� � ������� �� �������� ��������
	
	for(long i=0; i<theApp.AllDivisions.size(); i++)
	{OneDivision.push_back(theApp.AllDivisions[i][DIVALL_DIV_NAME]);}

	std::sort(OneDivision.begin(), OneDivision.end());

	for(long i=0; i<OneDivision.size(); i++)
	{
		for(long j=0; j<theApp.AllDivisions.size(); j++)
		{
			if(OneDivision[i] == theApp.AllDivisions[j][DIVALL_DIV_NAME])
			{
				std::vector<CString> Tmp_Vec;
				Tmp_Vec = theApp.AllDivisions[j];
				theApp.AllDivisions.erase(theApp.AllDivisions.begin() + j);
				theApp.AllDivisions.insert(theApp.AllDivisions.begin() + i, Tmp_Vec);
			}
		}
	}

	OneDivision.clear();

	/////////////////////////////////////////////////////////////////////////////
	// 3 // � ������ ����� ���������� ������ ������� ������� �������� �� � ListBox, ����� ���� ������ ����������� ��������� � ������ � �������� � ������� !

	for(long i=0; i<theApp.AllDivisions.size(); i++)
	{
/*
		m_DivChangeList.InsertItem(i, theApp.AllDivisions[i][DIVALL_PIPE_NAME]);
		// ��� ��� ��� ����� ������:
		m_DivChangeList.SetItemText(i, 0, theApp.AllDivisions[i][DIVALL_PIPE_NAME]);
		m_DivChangeList.SetItemText(i, 1, theApp.AllDivisions[i][DIVALL_PROD_NAME]);
		m_DivChangeList.SetItemText(i, 2, theApp.AllDivisions[i][DIVALL_DIV_NAME]);
*/

//		(void)m_DivChangeList.AddItem( _T("Mark Jackson"), _T("09/08/1974"), _T("100") );
//		(void)m_DivChangeList.AddItem( _T("Trevor McSplatt"), _T("03/12/1970"), _T("25") );
//		(void)m_DivChangeList.AddItem( _T("Sidney Finkelstein"), _T("01/01/1960"), _T("40") );

//*
		(void)m_DivChangeList.AddItem(	theApp.AllDivisions[i][DIVALL_PIPE_NAME],
										theApp.AllDivisions[i][DIVALL_PROD_NAME],
										theApp.AllDivisions[i][DIVALL_DIV_NAME]
									 );
//*/

	}
////////////////////////////////////////////////////////////////////////////////////////////////////
// ������ ��������� �����, ������� ���� ����� ��� ������ �� ������  //CListCtrl m_DivChangeList;
////	m_DivChangeList.SetExtendedStyle( m_DivChangeList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);


	// ��������� ������ ������� ������ ��� "����������"
////	if(m_DivChangeList.GetItemCount() > 0)
////	{m_DivChangeList.SetItemState(0, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);}


	// ���� � ������� � ����������� ������� �������� � ���������� �� ������ ���� ������, 
	// �� ������� ����������������� ���������, � ����������� ��� ��� ������ � ���.
	if(theApp.ErrDivisions.size() > 0)
	{
		CString LogErrFiles("");
		CString LogErrPath("");
		CString MesErrFiles("");
		bool bError=false;

		// ������� ��������� � ��� ���������� � ������������ ������
		LogBadFiles( LogErrFiles, LogErrPath, MesErrFiles, bError);

		CStringA LogErrFilesA(LogErrFiles);
		CStringA LogErrPathA(LogErrPath);

		// ������� ��� �� � ���������, � ��� ��� LOG-���� ����� ������, �� � ��������� ���.
		int msgboxID = AfxMessageBox(MesErrFiles);
		//if(msgboxID == IDOK)
		//{}
	}



	if( (ichangeXml>0) || badXml)
	{
		CString LogPath("");
		CString LogPathQuotes("");

		// ������� ��������� � ��� ���������� � ������������ ������
		CString LogFileName("sougen_logfiles.txt");
		LogPath = LogPath + theApp.IniFilePath + LogFileName;
		LogPathQuotes = _T("\"")+ LogPath +_T("\"");
		// �������������� ������� ���� �� ������� ������� � ������, ������� ������ ��������� start
		// ���� ������� ����, �� ������ ����� ���������� ��������� �������: start "������ � ���������" 
		// �� ��� ���� ���� ��������� � ���� ����: start ������_���_��������
		bool WithQuotes=false;
		for(long k=0; k < LogPath.GetLength(); k++)
		{
			if(LogPath.Find(_T(" ")) != -1) // ������� ������
			WithQuotes = true;
		}


		CStringA LogPathA(LogPath);
		CStringA LogPathQuotesA(LogPathQuotes);

		// 3) �������� ��������� ���������:	
		// ������� �����  "system()"
		if(WithQuotes)
		{
			system("start " + LogPathQuotesA);
		}
		else
		{
			system("start " + LogPathA);
		}

		// ������:
		// ���� ��������� �������� �� ��� "txt" � �������� �������� �� ��������� ����-���� ���������� // ����� ����, ��� �������� ������ �����.
		// ���� ���, �� ������� �������� ��������, ������� �������������� �������� � ����� ���������� �� ������ ������.
////////////////
		//system("�����_���������" + "start " + LogErrPathA);
/*
		// 3) �������� ��������� ���������:	
		SHELLEXECUTEINFO lpExecInfo;
		lpExecInfo.cbSize  = sizeof(SHELLEXECUTEINFO);
		lpExecInfo.lpFile = L"sougen_logfiles.txt";
		lpExecInfo.fMask = SEE_MASK_DOENVSUBST|SEE_MASK_NOCLOSEPROCESS;
		lpExecInfo.hwnd = NULL;  
		lpExecInfo.lpVerb = L"open";
		//lpExecInfo.lpParameters = L"-cf test.xml";

		lpExecInfo.lpDirectory = NULL;
		lpExecInfo.nShow = SW_HIDE; // hide shell during execution
		//lpExecInfo.nShow = SW_SHOW; // show shell during execution
		lpExecInfo.hInstApp = (HINSTANCE) SE_ERR_DDEFAIL;
		ShellExecuteEx(&lpExecInfo);

		// wait until the process is finished
		if (lpExecInfo.hProcess != NULL)
		{
			::WaitForSingleObject(lpExecInfo.hProcess, INFINITE);
			::CloseHandle(lpExecInfo.hProcess);
			AfxMessageBox( _T("Process finished") );
		}
*/
	}	

	bFirstDlg=true;

	this->GetWindowRect(&OriginalRect);
	OrigW = OriginalRect.right - OriginalRect.left;
	OrigH = OriginalRect.bottom - OriginalRect.top;

	return TRUE;  // ������� �������� TRUE, ���� ����� �� ������� �������� ����������
}


void CDivisionChoose::LogBadFiles( CString& LogErrFiles, CString& LogErrPath, CString& MesErrFiles, bool bError)
{
		CString LogErrFileName("sougen_logfiles.txt");

		long NumErrFiles = theApp.ErrDivisions.size();
		CString DotSOU(".sou");
		LogErrFiles = _T("");
		LogErrPath = _T("");
		MesErrFiles = _T("");

		CString lLine;

		GetLocalTime(&theApp.m_CurTime);	//�������������� ��������� �����

		CStdioFile cfile_object_write;
		BOOL lOk = cfile_object_write.Open(LogErrFileName, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite);
		//CFile cfile_object_write( LogFileName, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite);
		cfile_object_write.SeekToEnd();

		LogErrFiles = _T("*******************************************************************************************************************************\n");

		lLine.Format(_T("|SOU|%02i.%02i.%04i | %02i:%02i:%02i|******************************************************************************************\n"),
			theApp.m_CurTime.wDay, theApp.m_CurTime.wMonth, theApp.m_CurTime.wYear, theApp.m_CurTime.wHour, theApp.m_CurTime.wMinute, theApp.m_CurTime.wSecond);
		LogErrFiles += lLine;


		MesErrFiles += _T("��� �������� ������ �������� ���� ���������� ������.\n");
		MesErrFiles += _T("���������� �� ������ � �������� �� ����� ������������ � ��������� ����.\n");
		MesErrFiles += _T("������ ���� ������� �  ") + LintToCStr(NumErrFiles) + _T("  ������.\n\n");
		MesErrFiles += _T("������ ��������� � ��������� ������:\n");
		LogErrFiles += MesErrFiles;

		for(long i=0; i < theApp.ErrDivisions.size(); i++)
		{
			MesErrFiles = MesErrFiles + _T("\"") + theApp.ErrDivisions[i][0] + DotSOU + _T("\"");
		
			LogErrFiles = LogErrFiles + _T("\"") + theApp.ErrDivisions[i][0] + DotSOU + _T("\"");
			LogErrFiles += _T("\n");
			LogErrFiles += theApp.ErrDivisions[i][1];

			if(i != (theApp.ErrDivisions.size()-1))
			{
				MesErrFiles += _T("\n");
				LogErrFiles += _T("\n");
			}
		}


		MesErrFiles += _T("\n\n");
		MesErrFiles += _T("���� � ��������� ��������� ������ ��������� �:\n");
		MesErrFiles = MesErrFiles + theApp.IniDivisionsPath +_T("\\")+ LogErrFileName;
		MesErrFiles += _T("\n\n��� ����� � �������� ���� ���������� �� ����� \"�������\" � ����� \"�������\\Bad\".");

		LogErrPath = LogErrPath + theApp.IniFilePath + LogErrFileName;

		LogErrFiles += _T("\n");
		CStringA LogErrFilesA(LogErrFiles);
		cfile_object_write.Write(LogErrFilesA, LogErrFilesA.GetLength());

		cfile_object_write.Close();

/*
		CStdioFile cfile_object_write;
		BOOL lOk = cfile_object_write.Open(LogErrFileName, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite);
		//CFile cfile_object_write( LogFileName, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite);
		cfile_object_write.SeekToEnd();

		LogErrFiles = _T("*******************************************************************************************************************************\n");
		cfile_object_write.WriteString( LogErrFiles );
//		cfile_object_write.WriteString( _T("\n"));

		lLine.Format(_T("|SOU|%02i.%02i.%04i | %02i:%02i:%02i|******************************************************************************************\n"),
			theApp.m_CurTime.wDay, theApp.m_CurTime.wMonth, theApp.m_CurTime.wYear, theApp.m_CurTime.wHour, theApp.m_CurTime.wMinute, theApp.m_CurTime.wSecond);
		LogErrFiles = lLine;
		cfile_object_write.WriteString(LogErrFiles);
//		cfile_object_write.WriteString( _T("\n"));


		MesErrFiles += _T("��� �������� ������ �������� ���� ���������� ������.\n");
		MesErrFiles += _T("���������� �� ������ � �������� �� ����� ������������ � ��������� ����.\n");
		MesErrFiles += _T("������ ���� ������� �  ") + LintToCStr(NumErrFiles) + _T("  ������.\n\n");
		MesErrFiles += _T("������ ��������� � ��������� ������:\n");
		LogErrFiles = MesErrFiles;
		cfile_object_write.WriteString(LogErrFiles);
//		cfile_object_write.WriteString( _T("\n"));

		for(long i=0; i < theApp.ErrDivisions.size(); i++)
		{
			MesErrFiles = MesErrFiles + _T("\"") + theApp.ErrDivisions[i][0] + DotSOU + _T("\"");
		
			LogErrFiles = LogErrFiles + _T("\"") + theApp.ErrDivisions[i][0] + DotSOU + _T("\"");
			cfile_object_write.WriteString(LogErrFiles);
//			cfile_object_write.WriteString( _T("\n"));
			LogErrFiles = _T("\n");
			cfile_object_write.WriteString(LogErrFiles);
//			cfile_object_write.WriteString( _T("\n"));
			LogErrFiles = theApp.ErrDivisions[i][1];
			cfile_object_write.WriteString(LogErrFiles);
//			cfile_object_write.WriteString( _T("\n"));

			if(i != (theApp.ErrDivisions.size()-1))
			{
				MesErrFiles += _T("\n");
				LogErrFiles = _T("\n");
				LogErrFiles += _T("\n");
			}
		}

		MesErrFiles += _T("\n\n");
		MesErrFiles += _T("���� � ��������� ��������� ������ ��������� �:\n");
		MesErrFiles = MesErrFiles + theApp.IniDivisionsPath +_T("\\")+ LogErrFileName;
		MesErrFiles += _T("\n\n��� ����� � �������� ���� ���������� �� ����� \"�������\" � ����� \"�������\\Bad\".");

		LogErrPath = LogErrPath + theApp.IniFilePath + LogErrFileName;

		cfile_object_write.WriteString( _T("\n"));
		cfile_object_write.Close();
*/

/*
		//CStdioFile lfile_obj_w;
		//CFileFind hFile;
		//bool bFound = false;
		//bFound = hFile.FindFile( LogErrPath );
				
		//if(bFound)
		//{
		//	BOOL lOk = lfile_obj_w.Open(LogErrFileName, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite);
		//	lfile_obj_w.SeekToEnd();
		//	lfile_obj_w.Write( LogErrFilesA, LogErrFilesA.GetLength());
		//	lfile_obj_w.Close();
		//}
		//else
		//{
			CFile cfile_object_write( LogErrFileName, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite);
			cfile_object_write.SeekToEnd();
			cfile_object_write.Write( LogErrFilesA, LogErrFilesA.GetLength());
			cfile_object_write.Close();
		//}
//*/
}


void CDivisionChoose::LogChangedFiles( CString& LogFiles, CString& LogPath, CString& MesFiles )
{

}


//*
void CDivisionChoose::readDivisionHeadFile(CString bstrXMLFile)
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

	TElem eroot(iRootElm);
	//TElem subroot = eroot.subnode(L"�������_���");
	wstring DivAtrs;
	std::vector<CString> DivisionHead;

	
	DivAtrs = eroot.attr(L"���"				 );	theApp.AllDivisions[theApp.AllDivisions.size()-1].push_back(DivAtrs.c_str());	// [0] - �������� �������
	DivAtrs = eroot.attr(L"�����"			 );	theApp.AllDivisions[theApp.AllDivisions.size()-1].push_back(DivAtrs.c_str());	// [1] - �������� ������������
	DivAtrs = eroot.attr(L"�����_���"		 );	theApp.AllDivisions[theApp.AllDivisions.size()-1].push_back(DivAtrs.c_str());	// [2] - ID ������������
	DivAtrs = eroot.attr(L"�������"			 );	theApp.AllDivisions[theApp.AllDivisions.size()-1].push_back(DivAtrs.c_str());	// [3] - �������� �������� � ����������
	DivAtrs = eroot.attr(L"�������_���"		 );	theApp.AllDivisions[theApp.AllDivisions.size()-1].push_back(DivAtrs.c_str());	// [4] - ID ��������
	DivAtrs = eroot.attr(L"��������"		 );	theApp.AllDivisions[theApp.AllDivisions.size()-1].push_back(DivAtrs.c_str());	// [5] - ��������
	DivAtrs = eroot.attr(L"�������"			 );	theApp.AllDivisions[theApp.AllDivisions.size()-1].push_back(DivAtrs.c_str());	// [6] - �������
	DivAtrs = eroot.attr(L"�����"			 );	theApp.AllDivisions[theApp.AllDivisions.size()-1].push_back(DivAtrs.c_str());	// [7] - �����
	DivAtrs = eroot.attr(L"�����_�����������");	theApp.AllDivisions[theApp.AllDivisions.size()-1].push_back(DivAtrs.c_str());	// [8] - �����_�����������
	DivAtrs = eroot.attr(L"�����_�����"		 );	theApp.AllDivisions[theApp.AllDivisions.size()-1].push_back(DivAtrs.c_str());	// [9] - ����� ������������
	DivAtrs = eroot.attr(L"���_������"		 );	theApp.AllDivisions[theApp.AllDivisions.size()-1].push_back(DivAtrs.c_str());	// [10] - ��� ������ �������
	DivAtrs = eroot.attr(L"���_�����"		 );	theApp.AllDivisions[theApp.AllDivisions.size()-1].push_back(DivAtrs.c_str());	// [11] - ��� ����� �������
	theApp.AllDivisions[theApp.AllDivisions.size()-1].push_back(DivAtrs.c_str());

	int u=0;
}




void CDivisionChoose::readDivisionFile(CString bstrXMLFile)
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

	TElem eroot(iRootElm);
	wstring DivAtrs;
	std::vector<CString> DivisionHead;

	DivAtrs = eroot.attr(L"���"			);		DivisionHead.push_back(DivAtrs.c_str());	// [0] - �������� �������
	DivAtrs = eroot.attr(L"�����"		);		DivisionHead.push_back(DivAtrs.c_str());	// [1] - �������� ������������
	DivAtrs = eroot.attr(L"�����_���"	);		DivisionHead.push_back(DivAtrs.c_str());	// [2] - ID ������������
	DivAtrs = eroot.attr(L"�������"		);		DivisionHead.push_back(DivAtrs.c_str());	// [3] - �������� �������� � ����������
	DivAtrs = eroot.attr(L"�������_���"	);		DivisionHead.push_back(DivAtrs.c_str());	// [4] - ID ��������
	DivAtrs = eroot.attr(L"��������"	);		DivisionHead.push_back(DivAtrs.c_str());	// [5] - ��������
	DivAtrs = eroot.attr(L"�������"		);		DivisionHead.push_back(DivAtrs.c_str());	// [6] - �������
	DivAtrs = eroot.attr(L"�����"		);		DivisionHead.push_back(DivAtrs.c_str());	// [7] - �����
	DivAtrs = eroot.attr(L"�����_�����������");	DivisionHead.push_back(DivAtrs.c_str());	// [8] - �����_�����������
	DivAtrs = eroot.attr(L"�����_�����"	);		DivisionHead.push_back(DivAtrs.c_str());	// [9] - ����� ������������
	DivAtrs = eroot.attr(L"���_������"	);		DivisionHead.push_back(DivAtrs.c_str());	// [10] - ��� ������ �������
	DivAtrs = eroot.attr(L"���_�����"	);		DivisionHead.push_back(DivAtrs.c_str());	// [11] - ��� ����� �������

	theApp.FullDivision.clear();
	theApp.FullDivision.push_back(DivisionHead);
	DivisionHead.clear();

////////////////////////////////////////////////////////////////////////////////////////
	TElem subroot = eroot.subnode(L"������");
	//wstring DivAtrs;
	std::vector<CString> OneDetector;

	for(TElem e=eroot.begin(); e!=eroot.end(); e++)
	{
		OneDetector.clear();
		DivAtrs = e.attr(L"���"		);	OneDetector.push_back(DivAtrs.c_str());
		//AfxMessageBox(DivAtrs.c_str(), 0, 0);
		DivAtrs = e.attr(L"��"			);		OneDetector.push_back(DivAtrs.c_str());
		DivAtrs = e.attr(L"�������"		);		OneDetector.push_back(DivAtrs.c_str());
		DivAtrs = e.attr(L"����"		);		OneDetector.push_back(DivAtrs.c_str());
		DivAtrs = e.attr(L"��������"	);		OneDetector.push_back(DivAtrs.c_str());
		DivAtrs = e.attr(L"��������"	);		OneDetector.push_back(DivAtrs.c_str());
		DivAtrs = e.attr(L"������_��������");	OneDetector.push_back(DivAtrs.c_str());
		DivAtrs = e.attr(L"������_�����");		OneDetector.push_back(DivAtrs.c_str());
		//DivAtrs = e.attr(L"����������_������");	OneDetector.push_back(DivAtrs.c_str());
		//DivAtrs = e.attr(L"����������_�����");	OneDetector.push_back(DivAtrs.c_str());

		//��� //�� //������� //���� //�������� //�������� //������_�������� // ������_����� // ����������_������ // ����������_�����
		theApp.FullDivision.push_back(OneDetector);
		OneDetector.clear();
	}

	int u=0;
}



// 2.1 �������� // SOU-����� �������. �������� ����������. ������ ��������+������� = ����� ������������ � ��������
// ������������� ��� "�����" � ���� �������� �� ������� � ���� �� ����� "�����" ��������, ��� �������� �� ��.
// ���� �� ������� ������� ����� ������, ������� �� ������� ����� ���, ��� ������ �� ��, �� ����������� ����.
_bstr_t CDivisionChoose::validateDivFileByDetKeyAndDetMaxNum(CString bstrXMLFile, bool &bValid)
{
	CString RetErrCString("");

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

	// �������
	CString DivPIPEID("");	// ������ ��� ��� ����� � �������
	CString DivPRODNAME("");	// ������ ��� ������� � �������
	CString DivPRODID("");	// ������ ��� ��� �������� � �������
	// ������
	CString DivDetSYSN("");		// ������ ��� ��� � ������� ������� �������
	CString DivDetPTFIX("");	// ������ ��� �������� ������� �������

	TElem eroot(iRootElm);
	wstring DivAtrs;


//	DivAtrs = eroot.attr(L"���");											// [1] - �������� �������
	DivAtrs = eroot.attr(L"�����_���");		DivPIPEID = DivAtrs.c_str();	// [3] - ID �����
	DivAtrs = eroot.attr(L"�������");		DivPRODNAME = DivAtrs.c_str();	// [4] - �������� ��������
// ��� ����� ����������� ��� ��������
	DivAtrs = eroot.attr(L"�������_���");	DivPRODID = DivAtrs.c_str();	// [5] - ID ��������
//	DivAtrs = eroot.attr(L"��������");										// [6] - ��������
//	DivAtrs = eroot.attr(L"�������");										// [7] - �������
//	DivAtrs = eroot.attr(L"�����");											// [8] - �����
//	DivAtrs = eroot.attr(L"�����_�����������");								// [9] - �����_�����������

////////////////////////////////////////////////////////////////////////////////////////
	TElem subroot = eroot.subnode(L"������");
// ��������� ���������� ��� �����
	CString DivDetKey("");	// ��� ���������� "����" = "����� ������������" = ��������+�������
	CString DetDetKey("");	// ��� ���������� "����" = "����� ������������" = ��������+�������
	// ��� ������ �������� ���� ���������� "����������" � ���� ����
	bool DetFound=false;	// ��������� �� �� ������� �� ������ ��� ���.
	// ��� ������ �������� �����, �� ���� ��� ������������� �� �����������
	bool DetPRODFound=false;	// ��������� �� �� ������� �� ������ � ������ ��������� ��� ���.
	bool DetPTFIXFound=false;	// ��������� �� �� ������� �� ������ � ������ ���������� ��� ���.

	TElem e = eroot.end();


	int eNumTest=1; // ��� �������� ����� �������� �� �������� (���� ����� 8-��, �� � ����� "Bad")
	// ������ �������� �� ����� ��������, ������������� � ����� �������
	for(TElem e=eroot.begin(); e!=eroot.end(); e++, eNumTest++)
	{
		if(
			(theApp.MaxDetectors > 0) &&
			(eNumTest > theApp.MaxDetectors)
		  )
		{
			RetErrCString = RetErrCString + _T("������ � ����� �������:") +_T("\"") + bstrXMLFile + _T("\"") + _T("\n") +
				_T("����� �������� ������������� � ����� ������� ������ ��� ") + 
				LintToCStr(theApp.MaxDetectors) + 
				_T(" ����") + _T("\n");

			// �� ��������, ��� ��� ������, ����� ���� �������� ���������� � ��� ���� ��������� � ����� "Bad"
			bValid=false;
			return RetErrCString; 
		}
	}


	for(TElem e=eroot.begin(); e!=eroot.end(); e++)
	{
		DivDetKey.Empty();

		DivAtrs = e.attr(L"���");		DivDetSYSN = DivAtrs.c_str();
//		DivAtrs = e.attr(L"��");		// ����������� ���������
//		DivAtrs = e.attr(L"�������");	// ����������� ���������
//		DivAtrs = e.attr(L"����");		// ����������� ���������
		DivAtrs = e.attr(L"��������");	DivDetPTFIX = DivAtrs.c_str();

		CString DivDetPTFIXLower = DivDetPTFIX.MakeLower(); // �������� ��� ������� ��������� � ������ ��������
// ������� ���������� �����
// ��� ����� ����������� �������� ������� �������
		//DivDetKey += DivDetPTFIX;
		DivDetKey += DivDetPTFIXLower; // !!! �������� � ����� ���������� �������� �� ����� ��������� � ������� ��������
// ��� ����� ����������� ������� �� �������
		DivDetKey += DivPRODID;

// ���� �����������, ����� ������ ������ ��� ��������� ����� �������� ����������� �� ��.
		// ����������� ������ �������� �� �������:
		std::vector<CString> TitleDetector;
		TitleDetector = theApp.AllDetectors[0]; // ��������� ������ ������� � "������", ����� ��� �� �������� ��� ����������
		theApp.AllDetectors.erase(theApp.AllDetectors.begin()+0); // ������� �� ������� ������ ������� � ������� ����� ���� � ��������

		DetFound=false;
		//DetPTFIXFound=false;
		//DetPRODFound=false;

		for (int i=0; i < theApp.AllDetectors.size(); i++)
		{
		// ��� ������ �������� ���� ���������� "����������" � ���� ����
			DetDetKey.Empty();

			CString DetDetPTFIXLower = theApp.AllDetectors[i][DET_POSTFIX];
			DetDetPTFIXLower = DetDetPTFIXLower.MakeLower(); // �������� ��� ������� ��������� � ������ ��������

			DetDetKey += DetDetPTFIXLower;			// �������� (��������������� � ������ ��������)
			DetDetKey += theApp.AllDetectors[i][DET_PROD_VIEW]; // ������� ID

			if(DivDetKey == DetDetKey)
			{DetFound=true;}

		// ��� ������ �������� �����, �� ���� ��� ������������� �� �����������
		//	if( (DivDetPTFIX == theApp.AllDetectors[i][2] && DivPRODID == theApp.AllDetectors[i][6]) ) // �������� // ������� ID
		//	{DetPTFIXFound=true; DetPRODFound=true;}

			DetDetKey.Empty();

			//if( DetFound || DetPTFIXFound || DetPRODFound)
			if( DetFound )
			{break;}
		}

		theApp.AllDetectors.insert(theApp.AllDetectors.begin(), TitleDetector); // ��������� ����� ������� � ������
		TitleDetector.clear();

		// ��� ������ �������� ���� ���������� "����������" � ���� ����
		if(!DetFound)
		{
		// � ����� ������� "����" ������������� �� ������� �������� "���=��������" �� ������� � ���� ������. ���� �����, � ����� ���������� � ����� Bad
			RetErrCString = RetErrCString + _T("������ � ����� �������:") +_T("\"") + bstrXMLFile + _T("\"") + _T("\n") 
				+_T("������������� �� �������") + _T(" ")+DivDetSYSN+_T(" ") + _T(" ��������:") + _T("\n")
				+_T("\"��������\"") + _T(" = ") + DivDetPTFIX + _T(" ") + _T("\n")
				+_T("\"�������\"") + _T(" = ") +  DivPRODNAME  + _T(" ") + _T("\n")
				+_T("�� ������� � ���� ������."); // ���� �������� � ����� Bad // ��� ��������� � ��������� ����
			bValid=false;
			break;
		}

/*		// ��� ������ �������� �����, �� ���� ��� ������������� �� �����������
		if(!DetPRODFound && !DetPTFIXFound)
		{
		// � ����� ������� "����" ������������� �� ������� �������� "���=��������" �� ������� � ���� ������. ���� �����, � ����� ���������� � ����� Bad
			RetErrCString = RetErrCString + _T("������ � ����� �������:") +_T("\"") + bstrXMLFile + _T("\"") + _T("\n") 
				+_T("������������� �� �������") + _T(" ")+DivDetSYSN+_T(" ") + _T(" ��������:") + _T("\n")
				+_T("\"��������\"") + _T(" = ") + DivDetPTFIX + _T(" ") + _T("\n")
				+_T("\"�������\"") + _T(" = ") +  DivPRODNAME  + _T(" ")
				+_T("�� ������� � ���� ������."); // ���� �������� � ����� Bad // ��� ��������� � ��������� ����
			bValid=false;
			break;
		}
		if(!DetPRODFound && DetPTFIXFound)
		{
			RetErrCString = RetErrCString + _T("������ � ����� �������:") +_T("\"") + bstrXMLFile + _T("\"") + _T("\n") 
				+_T("������������� �� �������") + _T(" ")+DivDetSYSN+_T(" ") + _T(" ��������:") + _T("\n")
				+_T("\"�������\"") + _T(" = ") +  DivPRODNAME  + _T(" ")
				+_T("�� ������� � ���� ������."); // ���� �������� � ����� Bad // ��� ��������� � ��������� ����
			bValid=false;
			break;
		}
		if(!DetPTFIXFound && DetPRODFound)
		{
			RetErrCString = RetErrCString + _T("������ � ����� �������:") +_T("\"") + bstrXMLFile + _T("\"") + _T("\n") 
				+_T("������������� �� �������") + _T(" ")+DivDetSYSN+_T(" ") + _T(" ��������:") + _T("\n")
				+_T("\"��������\"") + _T(" = ") + DivDetPTFIX + _T(" ") + _T("\n")
				+_T("�� ������� � ���� ������."); // ���� �������� � ����� Bad // ��� ��������� � ��������� ����
			bValid=false;
			break;
		}
*/

//		DivAtrs = e.attr(L"��������");			// ����������� ���������
//		DivAtrs = e.attr(L"������_��������");	// ����������� ���������
//		DivAtrs = e.attr(L"������_�����");		// ����������� ���������

		DivDetKey.Empty();
	}


	return RetErrCString;
}


// 2.2 �������� // SOU-����� �������. �������� �������� �� ������� � ��������� ���� �� �������� � ���� ��������


// 2.3 �������� // SOU-����� �������. �������� ���������� ��������: ���� ���� ������, ���������� �������������
// ���������: 1) ���� � ����� (������� ���)  2) ��������  3) ��� ������� � �������  
// ���������: 4) �������� ����� [0.5 ; 1.5] + ����� 1.123 5) ����� ����������� [0 ; 200] + ����� 123
// ���������: 6) ��� ���� ����� "��������"  6.1) !=0  6.2) !=""  6.3) !=NULL  +"��������" 6.1) =0  6.2) != ""  6.3) != NULL
_bstr_t CDivisionChoose::correctDivFileByDetParams(CString bstrXMLFile, CString XMLFileName, bool &bChanged)
{
	CString EmptyCStr("");
	CString RetErrCString("");

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

	CString DivNAME("");		// ������ ��� ��� �������
	CString DivPIPENAME("");	// ������ ��� ��� ������������
	CString DivPIPEID("");		// ������ ��� �� ������������
	CString DivPRODNAME("");	// ������ ��� ������� � �������
	CString DivPRODID("");		// ������ ��� �� �������� � �������
	CString DivPARAM("");		// ������ ��� �������� �������
	CString DivWATCH("");		// ������ ��� ������� �������
	CString DivWAVE("");		// ������ ��� ����.����� �������
	CString DivDETTIME("");		// ������ ��� �����.����� �������
	CString DivPIPELEN("");		// ������ ��� ����� ����� �������
	CString DivBEGINNAME("");	// ������ ��� ��� ������ �������
	CString DivENDNAME("");		// ������ ��� ��� ����� �������



	CString DivDetSYSN("");		// ������ ��� ��� � ������� ������� �������
	//CString DivDetGRAN("");	// ������ ��� ��� �� ������� ������� �������
	CString DivDetNUMBER("");	// ������ ��� �� ������� �������
	CString DivDetPTFIX("");	// ������ ��� �������� ������� �������
	CString DivDetACTIVE("");	// ������ ��� ������� ������� �������
	CString DivDetPATH("");		// ������ ��� ���� ������� �������
	CString DivDetDIST("");		// ������ ��� �������� ������� �������
	CString DivDetDPRESS("");	// ������ ��� ���.����. ������� �������
	CString DivDetDTIIME("");	// ������ ��� ���.����� ������� �������
	CString DivDetDISTBEGIN("");// ������ ��� �������� �� ������ ������� �������
	CString DivDetDISTEND("");	// ������ ��� �������� �� ����� ������� �������


	std::vector<CString> DivisionHead;
	std::vector<std::vector<CString>> OneDivision;
	std::vector<CString> OneDetector;

	TElem eroot(iRootElm);
	wstring DivAtrs;

// ��� �� ���� ����� �������������� ������ ��� �������� �� ������, ���� bChanged � ����� ����� false, �� ���������� ��� ������
	RetErrCString = RetErrCString + _T("� ����� �������:") +_T("\"") + bstrXMLFile + _T("\"") + _T("\n");
	RetErrCString = RetErrCString + _T("���� ������� � ������������� ���������� ������ � ��� ����������.\n");
	
//	RetErrCString = RetErrCString + _T("������ � ����� �������:") +_T("\"") + bstrXMLFile + _T("\"") + _T("\n")
//		+_T("������������� �� �������") + _T(" ")+DivDetSYSN+_T(" ") + _T(" ��������:") + _T("\n")
//		+_T("\"��������\"") + _T(" = ") + DivDetPTFIX + _T(" ") + _T("\n")
//		+_T("\"�������\"") + _T(" = ") +  DivPROD  + _T(" ") + _T("\n")
//		+_T("�� ������� � ���� ������."); // ���� �������� � ����� Bad // ��� ��������� � ��������� ����

// ���������: ������ ���� �� ������ + �� NULL => ����� => ������� ������ ����� �����
	DivAtrs = eroot.attr(L"���");					// [1] - �������� �������
	DivNAME = DivAtrs.c_str();
	if(DivNAME.IsEmpty())
	{
		bChanged=true;
		DivNAME = XMLFileName;
		DivisionHead.push_back(DivNAME);
		RetErrCString = RetErrCString + _T("���� ") +_T("\"���\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
									  + _T("����� ") +_T("\"���\"")+ _T(" = ") + DivNAME + _T("\n");
	}
	else
	{DivisionHead.push_back(DivAtrs.c_str());}

// ���������: ������ ���� �� ������ + �� NULL + ����� ������ �� �������� ����� �������� � ������ �������� => ����� �������� �� ������
	DivAtrs = eroot.attr(L"�����");					// [1] - �������� �������
	DivPIPENAME = DivAtrs.c_str();
	DivisionHead.push_back(DivPIPENAME);

// ���������: ������ ���� �� ������ + �� NULL + ����� ������ �� �������� ����� �������� � ������ �������� => ����� �������� �� ������
	DivAtrs = eroot.attr(L"�����_���");					// [1] - �������� �������
	DivPIPEID = DivAtrs.c_str();
	DivisionHead.push_back(DivPIPEID);

/*// �������� !!!!! : ����������� ������ - ����� �� ���� ������ �������� �� ��� ����, ��� ������� ����� ���� ��������

	if(DivNAME.IsEmpty())
	{

		DivisionHead.push_back(DivNAME);
		RetErrCString = RetErrCString + _T("���� ") +_T("\"���\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
									  + _T("����� ") +_T("\"���\"")+ _T(" = ") + DivNAME + _T("\n");
	}
	else
	{DivisionHead.push_back(DivAtrs.c_str());}
	*/


	DivAtrs = eroot.attr(L"�������");				// ������� ID	//  [2] - �������� ��������
	DivPRODNAME = DivAtrs.c_str();
	DivisionHead.push_back(DivPRODNAME);

	DivAtrs = eroot.attr(L"�������_���");			// ������� ID	//  [2] - �������� ��������
	DivPRODID = DivAtrs.c_str();
	DivisionHead.push_back(DivPRODID);

/// �������� !!!!! : ����������� ������ - ����� �� ���� ������ �������� �� ��� ����, ��� ������� ����� ���� ��������


	// 5 detprodid
	// � ������ � ���� ����� � ����� ���� ������ ���� 
/*
	if(DivAtrs==_T("��.�������"))					// ������� � ���������� // [3] - �������� ��������
	DivAtrs = _T("�������");
	if(DivAtrs==_T("���.�������"))
	DivAtrs = _T("������");
	DivisionHead.push_back(DivAtrs.c_str());
	// 6 detprodtype
*/

// ���������: ������ ���� �� ������ + �� NULL + ������ "��������" => ����� => �������� �� ��������� ��������.
	DivAtrs = eroot.attr(L"��������");				// [4] - ��������
	DivPARAM = DivAtrs.c_str();
	if( (!DivPARAM.IsEmpty()) && (DivPARAM==_T("��������")) ) 
	{DivisionHead.push_back(DivAtrs.c_str());}
	else
	{
		bChanged=true;
		DivPARAM = _T("��������");
		DivisionHead.push_back(DivPARAM);
		RetErrCString = RetErrCString + _T("���� ") +_T("\"��������\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
									  + _T("����� ") +_T("\"��������\"")+ _T(" = ") + DivPARAM + _T("\n");
	}

// ���������: ������ ���� �� ������ + �� NULL + ���� ���� 1 ��� 0 => ����� => �������� �� ��������� 1.
	DivAtrs = eroot.attr(L"�������");				// [5] - �������
	DivWATCH = DivAtrs.c_str();
	if( (!DivWATCH.IsEmpty()) && (  (DivWATCH==_T("0")) || (DivWATCH==_T("1"))  ) )
	{DivisionHead.push_back(DivAtrs.c_str());}
	else
	{
		bChanged=true;
		DivWATCH = _T("1");
		DivisionHead.push_back(DivWATCH);
		RetErrCString = RetErrCString + _T("���� ") +_T("\"�������\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
									  + _T("����� ") +_T("\"�������\"")+ _T(" = ") + DivWATCH + _T("\n");
	}

// ���������: ������ ���� �� ������ + �� NULL + ���� � �������� ��������: [0.5 ; 1.5] + ����� 1.123
	DivAtrs = eroot.attr(L"�����");					// [6] - �����
	DivWAVE = DivAtrs.c_str();

	bool bDivWave=false;
	if( !CheckString(DivWAVE) ) // true - ������������
	{bDivWave=true;}

	double dWaveSpeed = _tstof(DivWAVE);
	if( (dWaveSpeed < 0.5) || (dWaveSpeed > 1.5) )
	{
		//AfxMessageBox( _T("��������: �������� \"�����\" ������ ���� ����� � ��������� ��������� �������� �� 0.5 �� 1.5 (��/�)."), MB_ICONWARNING );
		if(dWaveSpeed < 0.5)
		{DivWAVE = _T("0.5");}
		if(dWaveSpeed > 1.5)
		{DivWAVE = _T("1.5");}
		bDivWave=true;
	}
	DivisionHead.push_back(DivWAVE);
	
	if(bDivWave)
	{
		bChanged=true;
		RetErrCString = RetErrCString + _T("���� ") +_T("\"�����\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
									  + _T("����� ") +_T("\"�����\"")+ _T(" = ") + DivWAVE + _T("\n");
	}

	// 8 detwavespeed

// ���������: ������ ���� �� ������ + �� NULL + ���� � �������� ��������: [0 ; 200] + ����� 123
	DivAtrs = eroot.attr(L"�����_�����������");		// [7] - �����_�����������
	DivDETTIME = DivAtrs.c_str();

	bool bDivDetTime=false;
	if( !CheckString(DivDETTIME) ) // true - ������������
	{bDivDetTime=true;}

	double dTimeDetect = _tstof(DivDETTIME);
	if(  ( dTimeDetect < 0) || (dTimeDetect > 200)  )
	{
		//AfxMessageBox( _T("��������: �������� \"����� �����������\" ������ ���� ����� � ��������� ��������� �������� �� 0 �� 200 (�)."), MB_ICONWARNING );
		if(dTimeDetect < 0)
		{DivDETTIME = _T("0");}
		if(dTimeDetect > 200)
		{DivDETTIME = _T("200");}
		bDivDetTime=true;
	}
	DivisionHead.push_back(DivDETTIME);

	if(bDivDetTime)
	{
		bChanged=true;
		RetErrCString = RetErrCString + _T("���� ") +_T("\"�����_�����������\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
									  + _T("����� ") +_T("\"�����_�����������\"")+ _T(" = ") + DivDETTIME + _T("\n");
	}


// ���������: ������ ���� �� ������ + �� NULL 
	DivAtrs = eroot.attr(L"�����_�����");		// [7] - �����_�����������
	DivPIPELEN = DivAtrs.c_str();
	DivisionHead.push_back(DivPIPELEN);
/// �������� !!!!! : ����������� ������ - ����� �� ���� ������ �������� �� ��� ����, ��� ������� ����� ���� ��������

// ���������: ������ ���� �� ������ + �� NULL 
	DivAtrs = eroot.attr(L"���_������");		// [7] - �����_�����������
	DivBEGINNAME = DivAtrs.c_str();
	DivisionHead.push_back(DivBEGINNAME);
/// �������� !!!!! : ����������� ������ - ����� �� ���� ������ �������� �� ��� ����, ��� ������� ����� ���� ��������

// ���������: ������ ���� �� ������ + �� NULL 
	DivAtrs = eroot.attr(L"���_�����");		// [7] - �����_�����������
	DivENDNAME = DivAtrs.c_str();
	DivisionHead.push_back(DivENDNAME);
/// �������� !!!!! : ����������� ������ - ����� �� ���� ������ �������� �� ��� ����, ��� ������� ����� ���� ��������


	OneDivision.clear();
	OneDivision.push_back(DivisionHead);
	DivisionHead.clear();


////////////////////////////////////////////////////////////////////////////////////////
	TElem subroot = eroot.subnode(L"������");

// ��������� ���������� ��� ����� (������ ��� ������ �� �������, ������ ��� ������� �� ���� ��������)
	CString DivDetKey("");	// ��� ���������� "����" = "����� ������������" = ��������+�������
	CString DetDetKey("");	// ��� ���������� "����" = "����� ������������" = ��������+�������

	TElem e = eroot.end();
	int elementsnumber=1;
	bool bDetChanged=false; // ��������� ����, ��� ���� �����-�� ��������� ��������� � ��������������� ��������.
	CString CurDetErrCString("");


	for(TElem e=eroot.begin(); e!=eroot.end(); e++, elementsnumber++)
	{
		bDetChanged=false;
		OneDetector.clear();
		DivDetKey.Empty();

// �� ���������: �������� �������� "��������" / ����������������� ����������� ��� �������
		DivAtrs = e.attr(L"��������");
		DivDetPTFIX = DivAtrs.c_str();

		CString DivDetPTFIXLower = DivDetPTFIX.MakeLower(); // �������� ��� ������� ��������� � ������ ��������
// ������� ���������� �����
// ��� ����� ����������� �������� ������� �������
		//DivDetKey += DivDetPTFIX;
		DivDetKey += DivDetPTFIXLower; // !!! �������� � ����� ���������� �������� �� ����� ��������� � ������� ��������
// ��� ����� ����������� ������� �� �������
		DivDetKey += DivPRODID;

// ���� �����������, ����� ������ ������ ��� ��������� ����� �������� ����������� �� ��.
		// ����������� ������ �������� �� �������:
		std::vector<CString> TitleDetector;
		TitleDetector = theApp.AllDetectors[0]; // ��������� ������ ������� � "������", ����� ��� �� �������� ��� ����������
		theApp.AllDetectors.erase(theApp.AllDetectors.begin()+0); // ������� �� ������� ������ ������� � ������� ����� ���� � ��������

		int i(0);
		bool DivDetFound(false); // ������� �� �� "�����" ������ ������
		for (i=0; i < theApp.AllDetectors.size(); i++)
		{
			bDetChanged=false;

			// ��� ������ �������� ���� ���������� "����������" � ���� ����
			DetDetKey.Empty();

			CString DetDetPTFIXLower = theApp.AllDetectors[i][DET_POSTFIX];
			DetDetPTFIXLower = DetDetPTFIXLower.MakeLower(); // �������� ��� ������� ��������� � ������ ��������

			DetDetKey += DetDetPTFIXLower;			// �������� (��������������� � ������ ��������)
			DetDetKey += theApp.AllDetectors[i][DET_PROD_VIEW]; // ������� ID

			if(DivDetKey == DetDetKey)
			{DivDetFound = true; break;}
		}
		DetDetKey.Empty();


		theApp.AllDetectors.insert(theApp.AllDetectors.begin(), TitleDetector); // ��������� ����� ������� � ������
		TitleDetector.clear();
		i++; // !!!!!!!!!!!!!!!!!!!!!!!! ����� ������ ������, ��� �� ����� �������� � ����� ���� ������� ������� � �������� ������


// ������ ��� ��������� ������ �� ��������: 
		CurDetErrCString.Empty();
		//CurDetErrCString = CurDetErrCString + _T("������ � ") + LintToCStr(elementsnumber) + _T("   "); // _T("\n");

// ���������: ������� �� ��������� �� �� ����� ��������+������� // ���� � SOU-����� �� ��������� � ���, ��� ������� � ��, �������� �� ��-���
		DivAtrs = e.attr(L"���"); // ��� ������� � �������
		DivDetSYSN = DivAtrs.c_str();
		// 2 detname
		if(DivDetSYSN != theApp.AllDetectors[i][DET_NAME])
		{
			bChanged=true; bDetChanged=true;
			DivDetSYSN = theApp.AllDetectors[i][DET_NAME];
		// ��������� � ����� ������� (� ��� ����� ���������� ������ �������) ����� ���� ����� ������� ������:
			CurDetErrCString = CurDetErrCString + DivDetSYSN + _T("\n"); //_T("   ");

			CurDetErrCString = CurDetErrCString + _T("���� ") +_T("\"���\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
												+ _T("����� ") +_T("\"���\"")+ _T(" = ") + DivDetSYSN + _T("\n");
		}
		else
		{// ��������� � ����� ������� (� ��� ����� ���������� ������ �������) ����� ���� ����� ������� ������:
			CurDetErrCString = CurDetErrCString + DivDetSYSN + _T("\n"); //_T("   ");
		}

/*
// ���������: ������ ���� �������� � �� NULL => ����� => ������� ������ ����� ������� � �������
		DivAtrs = e.attr(L"��"); // ��� ������� �� �������
		DivDetGRAN = DivAtrs.c_str();
		// ����
		if(DivDetGRAN.IsEmpty())
		{
			bChanged=true; bDetChanged=true;
			// ���� ��� ������� ������, �� ������� ������ ����� ������� � ������� + � ���������� ����� "������ - " � ������
			DivDetGRAN = _T("������ - ") + theApp.AllDetectors[i][1];
			CurDetErrCString = CurDetErrCString + _T("���� ") +_T("\"���\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
												+ _T("����� ") +_T("\"���\"")+ _T(" = ") + DivDetGRAN + _T("\n");
		}
*/

		DivAtrs = e.attr(L"��"); // ��� ������� �� �������
		DivDetNUMBER = DivAtrs.c_str();
		// 0 detnum
		if(DivDetNUMBER != theApp.AllDetectors[i][DET_NUMBER])
		{
			bChanged=true; bDetChanged=true;
			DivDetNUMBER = theApp.AllDetectors[i][DET_NUMBER];
		// ��������� � ����� ������� (� ��� ����� ���������� ������ �������) ����� ���� ����� ������� ������:
			CurDetErrCString = CurDetErrCString + DivDetNUMBER + _T("\n"); //_T("   ");

			CurDetErrCString = CurDetErrCString + _T("���� ") +_T("\"��\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
												+ _T("����� ") +_T("\"��\"")+ _T(" = ") + DivDetNUMBER + _T("\n");
		}
		else
		{// ��������� � ����� ������� (� ��� ����� ���������� ������ �������) ����� ���� ����� ������� ������:
			CurDetErrCString = CurDetErrCString + DivDetNUMBER + _T("\n"); //_T("   ");
		}

/*
// ���������: ������� �� ��������� �� �� ����� ��������+������� // ���� � SOU-����� �� ��������� � ���, ��� ������� � ��, �������� �� ��-���
		DivAtrs = e.attr(L"��"); // ��� ������� � �������
		DivDetSYSN = DivAtrs.c_str();
		// 2 detname
		if(DivDetSYSN != theApp.AllDetectors[i][1])
		{
			bChanged=true; bDetChanged=true;
			DivDetSYSN = theApp.AllDetectors[i][1];
			CurDetErrCString = CurDetErrCString + _T("���� ") +_T("\"��\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
												+ _T("����� ") +_T("\"��\"")+ _T(" = ") + DivDetSYSN + _T("\n");
		}

// ���������: ������ ���� �������� � �� NULL => ����� => ������� ������ ����� ������� � �������
		DivAtrs = e.attr(L"���"); // ��� ������� �� �������
		DivDetGRAN = DivAtrs.c_str();
		// ����
		if(DivDetGRAN.IsEmpty())
		{
			bChanged=true; bDetChanged=true;
			DivDetGRAN = theApp.AllDetectors[i][1];
			CurDetErrCString = CurDetErrCString + _T("���� ") +_T("\"���\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
												+ _T("����� ") +_T("\"���\"")+ _T(" = ") + DivDetGRAN + _T("\n");
		}
//*/
// ���������: ������ ���� �� ������ + �� NULL + ���� ���� 1 ��� 0 => ����� => �������� �� ��������� 1.
		DivAtrs = e.attr(L"�������");
		DivDetACTIVE = DivAtrs.c_str();
		if( (!DivDetACTIVE.IsEmpty()) && (  (DivDetACTIVE==_T("0")) || (DivDetACTIVE==_T("1"))  ) )
		{}
		else
		{
			bChanged=true; bDetChanged=true;
			DivDetACTIVE = _T("1");
			CurDetErrCString = CurDetErrCString + _T("���� ") +_T("\"�������\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
												+ _T("����� ") +_T("\"�������\"")+ _T(" = ") + DivDetACTIVE + _T("\n");
		}

// ���������: ������� �� ��������� �� �� ����� ��������+������� // ���� � SOU-����� �� ��������� � ���, ��� ������� � ��, �������� �� ��-���
		DivAtrs = e.attr(L"����");
		DivDetPATH = DivAtrs.c_str();
		CString DivDetPATHLower = DivDetPATH.MakeLower();
		CString DetDetPATHLower = theApp.AllDetectors[i][DET_FILE_PATH].MakeLower();

		// 5 detfilepath
		//if(DivDetPATH != theApp.AllDetectors[i][4])
		if(DivDetPATHLower != DetDetPATHLower) // ������ �������� �� ��������� �������/������� ������� � ������� �������� �����
		{
			bChanged=true; bDetChanged=true;
			DivDetPATH = theApp.AllDetectors[i][DET_FILE_PATH];
			CurDetErrCString = CurDetErrCString + _T("���� ") +_T("\"����\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
												+ _T("����� ") +_T("\"����\"")+ _T(" = ") + DivDetPATH + _T("\n");
		}

// ���������: ������� �� ��������� �� �� ����� ��������+������� // ���� � SOU-����� �� ��������� � ���, ��� ������� � ��, �������� �� ��-���
		DivAtrs = e.attr(L"��������");
		DivDetDIST = DivAtrs.c_str();
		double DivDetDISTDouble = _tstof(DivDetDIST);
		double DetDetDISTDouble = _tstof(theApp.AllDetectors[i][DET_DISTANCE]);
		
		// 4 detdistance
		//if(DivDetDIST != theApp.AllDetectors[i][3])
		if(DivDetDISTDouble != DetDetDISTDouble)
		{
			bChanged=true; bDetChanged=true;
			DivDetDIST = theApp.AllDetectors[i][DET_DISTANCE];
			CurDetErrCString = CurDetErrCString + _T("���� ") +_T("\"��������\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
												+ _T("����� ") +_T("\"��������\"")+ _T(" = ") + DivDetDIST + _T("\n");
		}

// ���������: ������ ���� �� ������ + �� NULL + ���� � �������� ��������: [0 ; 100] + ����� 123
		DivAtrs = e.attr(L"������_��������");
		DivDetDPRESS = DivAtrs.c_str();

		bool bDPres=false;
		if( !CheckString(DivDetDPRESS) ) // true - ������������
		{bDPres=true;}

		double dDetDPress = _tstof(DivDetDPRESS);
		if(  (dDetDPress <= (double)0) || (dDetDPress > (double)100)  )
		{
			//AfxMessageBox( _T("��������: �������� \"������ ��������\" ������ ���� ����� ������ 0 � �� ������ 100"), MB_ICONWARNING );
			if(dDetDPress <= 0)
			{DivDetDPRESS = _T("0.01");}
			if(dDetDPress > 100)
			{DivDetDPRESS = _T("10");}
			bDPres=true;
		}

		if(bDPres)
		{
			bChanged=true; bDetChanged=true;
			CurDetErrCString = CurDetErrCString + _T("���� ") +_T("\"������_��������\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
												+ _T("����� ") +_T("\"������_��������\"")+ _T(" = ") + DivDetDPRESS + _T("\n");
		}

// ���������: ������ ���� �� ������ + �� NULL + ���� � �������� ��������: [0 ; 200] + ����� 123
		DivAtrs = e.attr(L"������_�����");
		DivDetDTIIME = DivAtrs.c_str();

		bool bDTime=false;
		if( !CheckString(DivDetDTIIME) ) // true - ������������
		{bDTime=true;}

		double dDetDTime = _tstof(DivDetDTIIME);
		if( (dDetDTime <= 0) || (dDetDTime > 10) )
		{
			//AfxMessageBox( _T("��������: �������� \"������ �����\" ������ ���� ����� ������ 0 � �� ������ 10"), MB_ICONWARNING );
			if(dDetDTime <= 0)
			{DivDetDTIIME = _T("0.01"); dDetDTime = 0.01;}
			if(dDetDTime > 10)
			{DivDetDTIIME = _T("10"); dDetDTime = 10;}
			bDTime=true;
		}

		DivDetDTIIME = DivDetDTIIME;
		if(bDTime)
		{
			//DivDetDTIIME = DoubleToCStr(dDetDTime, 3);
			bChanged=true; bDetChanged=true;
			CurDetErrCString = CurDetErrCString + _T("���� ") +_T("\"������_�����\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
												+ _T("����� ") +_T("\"������_�����\"")+ _T(" = ") + DivDetDTIIME + _T("\n");
		}


///////////////////////////////////////////////////////////////////
// !!!!!  �������� �� ������ � �������� �� ����� �������� ��������
///////////////////////////////////////////////////////////////////

//		DivAtrs = e.attr(L"����������_������");
//		DivDetDISTBEGIN = DivAtrs.c_str();

//		DivAtrs = e.attr(L"����������_�����");
//		DivDetDISTEND = DivAtrs.c_str();




		if(bDetChanged) // ���� �����-�� ��������� � ������� ���������, �� ������ ���� ������ � ������� ������ � ����������
		{
		// ������ ��� ��������� ������ �� ���������� ������� ���� ������� ����: 
			//RetErrCString = _T("������ � ") + LintToCStr(elementsnumber) + _T("   ")+ RetErrCString + _T("   "); //_T("\n");
			RetErrCString = RetErrCString + CurDetErrCString; // _T("\n");
		}

		DivDetKey.Empty();


		OneDetector.push_back(DivDetSYSN);
		//OneDetector.push_back(DivDetGRAN);
		OneDetector.push_back(DivDetNUMBER);
		OneDetector.push_back(DivDetACTIVE);
		OneDetector.push_back(DivDetPATH);
		OneDetector.push_back(DivDetPTFIX);
		OneDetector.push_back(DivDetDIST);
		OneDetector.push_back(DivDetDPRESS);
		OneDetector.push_back(DivDetDTIIME);
		OneDetector.push_back(DivDetDISTBEGIN);
		OneDetector.push_back(DivDetDISTEND);

		OneDivision.push_back(OneDetector);
		OneDetector.clear();
	}


	if(bChanged)
	{
		// 2.1) ������� ������ ����
		CFile::Remove(bstrXMLFile);
		// 2.2) ��������� ����� ����
		writeCurDivisionFile(bstrXMLFile, OneDivision);
	}
	else
	{RetErrCString.Empty();}


	DivisionHead.clear();
	OneDivision.clear();
	OneDetector.clear();

	return RetErrCString;
}



void CDivisionChoose::writeCurDivisionFile(CString bstrXMLFile, std::vector<std::vector<CString>> CurDivision)
{
	CString ErrorStr("");
	HRESULT hr = NULL;

//*
	//Create the XML
	///*
//	MSXML2::IXMLDOMDocument2Ptr pXMLDoc;	
//	HRESULT hr = pXMLDoc.CreateInstance(__uuidof(DOMDocument60));
//	if(FAILED(hr))
//	{
//		//AfxMessageBox(_T("Failed to create the XML class instance"));
//		AfxMessageBox(_T("������ ��� �������� �������� �� XML ������."));
//		return;
//	}


	//theApp.CurDomVer = theApp.XMLDOM;
	MSXML2::IXMLDOMDocument2Ptr pXMLDoc;	
	hr = pXMLDoc.CreateInstance(__uuidof(DOMDocument60));
	if(FAILED(hr))
	{
		ErrorStr = theApp.GetErrorCSTRString(hr);
		//LogConnectionStatus( ConnectStep, ErrorStr, false);
		MSXML2::IXMLDOMDocument2Ptr pXMLDoc;	
		hr = pXMLDoc.CreateInstance(__uuidof(DOMDocument40));
		if(FAILED(hr))
		{
			ErrorStr = theApp.GetErrorCSTRString(hr);
			//LogConnectionStatus( ConnectStep, ErrorStr, false);
			MSXML2::IXMLDOMDocument2Ptr pXMLDoc;	
			hr = pXMLDoc.CreateInstance(__uuidof(DOMDocument30));
			if(FAILED(hr))
			{
				ErrorStr = theApp.GetErrorCSTRString(hr);
				//LogConnectionStatus( ConnectStep, ErrorStr, false);
				MSXML2::IXMLDOMDocument2Ptr pXMLDoc;
				hr = pXMLDoc.CreateInstance(__uuidof(DOMDocument));
				if(FAILED(hr))
				{
					ErrorStr = theApp.GetErrorCSTRString(hr);
					//LogConnectionStatus( ConnectStep, ErrorStr, false);
					AfxMessageBox(ErrorStr);
					return;
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
//*/



	_bstr_t DivisionHead(_T("<�������_���></�������_���>"));


	if(pXMLDoc->loadXML(DivisionHead) == VARIANT_FALSE)
	{
		//ShowError(pXMLDoc);
		AfxMessageBox(_T("�� ������� ��������� �������� ���� � ����������� ���� �������"));
		return;
	}

	//Get the root element just created
	MSXML2::IXMLDOMElementPtr pXMLRootElem = pXMLDoc->GetdocumentElement();

/*
DIV_DIV_NAME	0
DIV_PROD_ID		1
DIV_PROD_NAME	2
DIV_PARAMETR	3
DIV_WATCH		4
DIV_WAVE		5
DIV_DTCT_TIME	6
*/
	//Add an attribute
	pXMLRootElem->setAttribute(_T("���"),				_variant_t( CurDivision[0][0] ));

	//if( CurDivision[0][1] == _T("�������") )
	//{pXMLRootElem->setAttribute(_T("�������"),			_variant_t(_T("��.�������")));}
	//else if( CurDivision[0][1] == _T("������") )
	//{pXMLRootElem->setAttribute(_T("�������"),			_variant_t(_T("���.�������")));}
	//else
	//{pXMLRootElem->setAttribute(_T("�������"),			_variant_t( CurDivision[0][1] ));}
	pXMLRootElem->setAttribute(_T("�������"),			_variant_t( CurDivision[0][1] ));

	// "�������", �� ID									_variant_t( CurDivision[0][2] 
	pXMLRootElem->setAttribute(_T("��������"),			_variant_t( CurDivision[0][3] ));
	pXMLRootElem->setAttribute(_T("�������"),			_variant_t( CurDivision[0][4] ));
	pXMLRootElem->setAttribute(_T("�����"),				_variant_t( CurDivision[0][5] ));
	pXMLRootElem->setAttribute(_T("�����_�����������"),	_variant_t( CurDivision[0][6] ));


	if(CurDivision.size()>1)
	{
		long NumOfDet=0;
		NumOfDet = CurDivision.size() - 1;		// NumOfDet = ����� �������� (�������� ������ ������ � ����������� �������) 

		MSXML2::IXMLDOMProcessingInstructionPtr pXMLProcessingNode =	pXMLDoc->createProcessingInstruction("xml", "version='1.0' encoding='windows-1251'");

		_variant_t vtObject;
		vtObject.vt = VT_DISPATCH;
		vtObject.pdispVal = pXMLRootElem;
		vtObject.pdispVal->AddRef();

		pXMLDoc->insertBefore(pXMLProcessingNode,vtObject);

		//Create the child elements and set the attributes
		for(long i=1, j=0; j<NumOfDet; i++, j++)
		{
			MSXML2::IXMLDOMElementPtr pXMLChild = pXMLDoc->createElement(_T("������"));	//Create first child element

			pXMLChild->setAttribute(_T("���"),				 _variant_t(CurDivision[i][DIV_DET_NAME]	));
			pXMLChild->setAttribute(_T("��"),				 _variant_t(CurDivision[i][DIV_DET_NUMBER]	));
			pXMLChild->setAttribute(_T("�������"),			 _variant_t(CurDivision[i][DIV_DET_ACTIVE]	));
			pXMLChild->setAttribute(_T("����"),				 _variant_t(CurDivision[i][DIV_DET_PATH]	));
			pXMLChild->setAttribute(_T("��������"),			 _variant_t(CurDivision[i][DIV_DET_PTFIX]	));
			pXMLChild->setAttribute(_T("��������"),			 _variant_t(CurDivision[i][DIV_DET_DIST]	));
			pXMLChild->setAttribute(_T("������_��������"),	 _variant_t(CurDivision[i][DIV_DET_DPRESS]	));
			pXMLChild->setAttribute(_T("������_�����"),		 _variant_t(CurDivision[i][DIV_DET_DTIIME]	));
//			pXMLChild->setAttribute(_T("����������_������"), _variant_t(CurDivision[i][DIV_DET_DISTBEG]	));
//			pXMLChild->setAttribute(_T("����������_�����"),	 _variant_t(CurDivision[i][DIV_DET_DISTEND]	));

			//pXMLChild1->Puttext(_T("This is a child of Parent"));	//Set the element value
			pXMLChild = pXMLRootElem->appendChild(pXMLChild);
		}
	}


	// Format the XML. This requires a style sheet
	MSXML2::IXMLDOMDocument2Ptr loadXSL;
	hr = loadXSL.CreateInstance(__uuidof(DOMDocument60));
	if(FAILED(hr))
	{
		//ShowError(loadXSL);
		AfxMessageBox(_T("������ ��� �������� �������� � ���� (XSL-�����) ����� �����."));
		return;
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
		AfxMessageBox(_T("������ ��� �������� �������� � ���� (XSL-�����) ����� �����."));
		return;
	}

	//Create the final document which will be indented properly
	MSXML2::IXMLDOMDocument2Ptr pXMLFormattedDoc;
	hr = pXMLFormattedDoc.CreateInstance(__uuidof(DOMDocument60));

	CComPtr<IDispatch> pDispatch;
	hr = pXMLFormattedDoc->QueryInterface(IID_IDispatch, (void**)&pDispatch);
	if(FAILED(hr))
	{
		return;
	}

	_variant_t	vtOutObject;
	vtOutObject.vt = VT_DISPATCH;
	vtOutObject.pdispVal = pDispatch;
	vtOutObject.pdispVal->AddRef();

	//Apply the transformation to format the final document	
	hr = pXMLDoc->transformNodeToObject(loadXSL,vtOutObject);

	if(bstrXMLFile.IsEmpty())	//User forgot to set the lcoation?
		bstrXMLFile = _T("Javed.xml");
	hr = pXMLFormattedDoc->save(bstrXMLFile.AllocSysString());

	return;
}



bool CDivisionChoose::CheckString(CString& StrToCheck)
{
	CString OrigString=StrToCheck;
	CString ResString("");

	CString k0("0"), k1("1"), k2("2"), k3("3"), k4("4"), k5("5"), k6("6"), k7("7"), k8("8"), k9("9"), k10(".");
	for(long i=0, j=0; i<StrToCheck.GetLength(); i++)
	{
		if( StrToCheck[i] == k0 || StrToCheck[i] == k1 || StrToCheck[i] == k2 || StrToCheck[i] == k3 || StrToCheck[i] == k4 ||
			StrToCheck[i] == k5 || StrToCheck[i] == k6 || StrToCheck[i] == k7 || StrToCheck[i] == k8 || StrToCheck[i] == k9 ||
			StrToCheck[i] == k10 
		  )
		{//�� � �������
			if(StrToCheck[i] == k10) // � ������ ���� ���������� 2 �������, ������� ��������� �������������
			{
				j++;
				if(j>1)
				{
					StrToCheck.Delete(i, 1);
					i--;
				}
			}
		}
		else
		{
			StrToCheck.Delete(i, 1);
			i--;
		}
	}

	if(StrToCheck.Find('.') == 0)
	{StrToCheck.Delete(0, 1);}
	if(StrToCheck.Find('.') == (StrToCheck.GetLength()-1))
	{StrToCheck.Delete((StrToCheck.GetLength()-1), 1);}

	ResString = StrToCheck;
	if(OrigString == ResString)
	{return true;} // ������ ������������
	else
	{return false;} // ������ ����������
}


// ������ "�������" // �������� ��� �������� ������� �� ������ ��������� � �������������� ���� .sou � ����� "�������"
void CDivisionChoose::OnBnClickedDivDelBtn()
{
	// TODO: �������� ���� ��� ����������� �����������
	CString EmptyStr("");
	long nCount=0;		// ����� ������� � Listbox
	long curIndex=0;	// ������ �������� ���������� � Listbox
	POSITION pos=NULL;	// ����� ���������� �������� (pos = curIndex+1)

	nCount = m_DivChangeList.GetItemCount();
	//����� ���������� ������� �� ������ �����������
	pos = m_DivChangeList.GetFirstSelectedItemPosition();
	if(pos==NULL) return;
	curIndex = m_DivChangeList.GetNextSelectedItem(pos);
	if( curIndex == (-1) )  return;

	//CString sDivName = m_DivChangeList.GetItemText(curIndex,0);
	CString sDivFileName = theApp.AllDivisions[curIndex][0];


	//CString sGroup;
	//if(sUser!=_T("smth."))
	//	sGroup.Format(_T("%d"),m_DivChangeList.GetItemData(nCurItem));
	//else
	//	sGroup = sUser;

	// ��������������� �������� ������ �� ������
	// ������ ����� �������� �� ����������� ������������� !!!! 
	// ����� ���� ���� ������ ��� ��������:
	int nItemSelected=0;
	for (int nItem = 0; nItem < m_DivChangeList.GetItemCount(); )
	{
		if (m_DivChangeList.GetItemState(nItem, LVIS_SELECTED) == LVIS_SELECTED)
		{
			m_DivChangeList.DeleteItem(nItem);
			nItemSelected = nItem;
		}
		else
		{++nItem;}
	}


	nCount = m_DivChangeList.GetItemCount();	// ������ �����, ��� ��������� ����� �� ���� ������.


	if( (nItemSelected < nCount) && (m_DivChangeList.GetItemCount() > 0) )
	{
		if(nItemSelected == 0)
		m_DivChangeList.SetItemState(0, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
		else
		m_DivChangeList.SetItemState(nItemSelected, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);

		m_DivChangeList.SetFocus();
	}
	else
	if((nItemSelected >= nCount) && (m_DivChangeList.GetItemCount() > 0) )
	{
		m_DivChangeList.SetItemState(m_DivChangeList.GetItemCount()-1, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
		m_DivChangeList.SetFocus();
	}


	// m_DivChangeList.DeleteItem(curIndex);

	// ������ ����� �������� �� ����������� ������������� !!!! 
	// (*) ������� ��� ������� �������
	//CString LowerName("");
	//nCount = m_DivChangeList.GetItemCount(); // ����� �������� ����� ��������� ������ ������ �� 1-�
	//for(long i=curIndex; i<nCount; i++)
	//{
	//	LowerName = m_DivChangeList.GetItemText(i,0);
	//	m_DivChangeList.InsertItem(i, LowerName);
	//}

	//������� ���� (*) �����������, ��� ��� �� ������� ������ ����, � ����� ������ �������� �������� ��� ����������� �������� ������ � ������:
	// 1) ��������� �����:
	// �������� ������ ���� �� ����� ��������������� �������
	// ����� ���� ���� �� ����� �� ������ ���������� (����� ��������� ������� �����)
	if(theApp.CurDivisionsPath != EmptyStr)
	{
		CString sPath = theApp.CurDivisionsPath;
		CFileFind hFile;
		CString DivisionFullPath("");				// ������ ���� � ����� ���������� �������

		//DivisionFullPath = DivisionFullPath + sPath + _T("\\") + sDivName + _T(".sou");
		DivisionFullPath = DivisionFullPath + sPath + _T("\\") + sDivFileName + _T(".sou");
		bool bFound = false;
		bFound = hFile.FindFile( DivisionFullPath );
				
		if(bFound)
		{
			CFile::Remove(DivisionFullPath);// ������ ���� ���������� �����
		}
	}

	// ����� ��������� ����� �������� ��������� �������� �� ��, ���� �� � �����
	// ����������� �������, ��� ���� �� ������ ���, �� ����� ������� 100%, � ���� ����, �� ������....

	theApp.AllDivisions.erase(theApp.AllDivisions.begin() + curIndex);

/*
	// 2) �������������� ������
	CString DivisionFileName(""); // ��� ����� ���������� �������
	CString wStr_DivName(""); // ��� ���������� �������
	CString wStr_Product(""); // ������� �� ������ �������
	theApp.AllDivisionsFileNames.clear();


	CRect rect;
	m_DivChangeList.GetClientRect(rect);


	//m_DivChangeList.DeleteAllItems(); // �������������� ���������� ������
	// ��������� ������ ���������� �������� ��������� �������� ������ .sou �� ����� "�������"
	if(theApp.CurDivisionsPath != EmptyStr)
	{
		CString sPath = theApp.CurDivisionsPath;
		CFileFind hFile;
		bool bFound = false;
		bFound = hFile.FindFile( sPath + _T("\\*.sou") );
	
		//m_DivChangeList.InsertColumn(0, _T("�������� ��������"), LVCFMT_LEFT, 300);
		//m_DivChangeList.InsertColumn(1, _T("�������"), LVCFMT_LEFT, 100); //rect.Width() );

		long LBiter=0;
		while ( bFound )
		{
			bFound = hFile.FindNextFile();
			//if( (! hFile.IsDots()) && ( hFile.IsDirectory() ) )		
			if( ! hFile.IsDots() )
			{
				DivisionFileName = hFile.GetFileName();

				CString szExt = _tcsrchr(DivisionFileName, '.'); // �������� szExt = ".sou"
				if(szExt == _T(".sou"))
				{
					// ������� ��������� 4 ������� �� ����� ������� �����
					DivisionFileName.Delete(DivisionFileName.GetLength() - szExt.GetLength(), 4);
					// ��������� ������ � ��� ������, ���� ���������� .sou ����
					//m_DivChangeList.InsertItem(LBiter, DivisionFileName);

/////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// �������� �� ���� .SOU ������ �������� ���� "�������"
					CString IniFileName = theApp.IniFileName;
					CString CurDivisionsPath = theApp.CurDivisionsPath;

					// ���������� �������� �������� ��������������� ������ � ����������� .sou �� ������� ���� !!!!!
					// http://www.rsdn.ru/article/qna/baseserv/fileexist.xml

					CString DivPathWithFiles("");
					CString DivPath("");
	
					DivPath = theApp.CurDivisionsPath;
					DivPathWithFiles = DivPath + _T("\\*.sou");

					//const wchar_t* _DivPathWithFiles = new wchar_t [_MAX_PATH];  // �������� delete � ����� !!!
					//_DivPathWithFiles = DivPathWithFiles;

					if( !FileExists(DivPathWithFiles) )
					{
						MessageBox( _T("� ����� � ��������� ����������� ����� ��������\n ���������, ���:\n")
									_T("1) ����� \"�������\" ��������� � ��� �� �����, ��� � �������.\n")
									_T("2) � ����� ������� ����� � ����������� .sou"),
									_T("������"), MB_ICONERROR);
					}

					//CIniParam parInjProd1 (CBLOWApp::IniFileName, _T("Injection"), _T("InjProd1"));
					//parInjProd1.Set(m_InjProducts[0]);
					//parInjProd1.Save();


					// 2 ��������� ��� �������� �� .SOU ����� �������, ���� ������� ���������� � ������, � ��������� ��� 
					//	 ��������� � �������������� �������, � �������� theApp, ��� ���������/����������/��������� ����� �������
					//	 ������ �������� ������ � ���� �� ����� ���������� ��� �������� ��������������� �������� ��� ��������� 
					//	 ��������� ���������� ������� � ��� ���������������� ����� ����� 
	
					//CString FileName("������ ������.sou"); 
					CString DivisionFilePath("");
					DivisionFilePath =  CurDivisionsPath + _T("\\") + DivisionFileName + _T(".sou");
					//MessageBox(	DivisionFilePath, _T("PATH"), 0 );
					CStringA p_FilePath(DivisionFilePath);

					TiXmlDocument doc(p_FilePath);
					bool loadOkay = doc.LoadFile();

					long i=0; // for sorting the entries
					long j=0, k=0;

					if(loadOkay)
					{
						TiXmlHandle hDoc(&doc);
						TiXmlElement *pRoot, *pParm;
						pRoot = doc.FirstChildElement("�������_���");
						if(pRoot)
						{
							CStringA AtributeToConvert("");
							CStringA RetConvert("");

							//AtributeToConvert = pRoot->Attribute("���");
							//wStr = CA2W((LPCSTR)AtributeToConvert);

							AtributeToConvert = pRoot->Attribute("�������");
							wStr_Product = CA2W((LPCSTR)AtributeToConvert);
							if(wStr_Product==_T("��.�������"))
							wStr_Product = _T("�������");
							if(wStr_Product==_T("���.�������"))
							wStr_Product = _T("������");

						}
					}
					else
					{
						//MessageBox(	_T("������ ��� �������� XML-�����."), ERROR_STR, MB_ICONERROR );
						if ( doc.Error() )
						{
							CStringA docErrorDescA = doc.ErrorDesc();
							CString docErrorDescW(docErrorDescA);
							CStringA docValueA;
							CString docValueW(docValueA);
							AfxMessageBox(_T("XML-���� �� ��������� ���� ����������.\n����� ������: ") + docValueW + _T(" ��������:  ") + docErrorDescW);

						}
					}
////////////////////////////////////// ��������� ������

					// ����� ������������ ��� ����� �������: 
					//m_DivChangeList.InsertItem(LBiter, DivisionFileName);
					// ��� ��� ��� ����� ������:
					//m_DivChangeList.SetItemText(LBiter, 0, DivisionFileName);
					//m_DivChangeList.SetItemText(LBiter, 1, wStr_Product);

					// ������ ������������ �������� �������:
					m_DivChangeList.InsertItem(LBiter, wStr_DivName);
					// ��� ��� ��� ����� ������:
					m_DivChangeList.SetItemText(LBiter, 0, wStr_DivName);
					m_DivChangeList.SetItemText(LBiter, 1, wStr_Product);

					theApp.AllDivisionsFileNames.push_back(DivisionFileName);
				}
				//AfxMessageBox(DivisionFileName);
			}
			LBiter++;
		}

	
		//m_DivChangeList.SetExtendedStyle( m_DivChangeList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

		// ������������� ���������� � ListControl-� ������� � ������������ � "������������" � Windows
		if( (curIndex < nCount) && (m_DivChangeList.GetItemCount() > 0) )
		{
			if(curIndex==0)
			m_DivChangeList.SetItemState(0, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
			else
			m_DivChangeList.SetItemState(curIndex, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);

			m_DivChangeList.SetFocus();
		}
		else
		if((curIndex >= nCount) && (m_DivChangeList.GetItemCount() > 0) )
		{
			m_DivChangeList.SetItemState(m_DivChangeList.GetItemCount()-1, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
			m_DivChangeList.SetFocus();
		}


		theApp.ChangeDivBtnClicked = theApp.DIV_BTN_DEL;

	}
*/
/*
		// ������������� ���������� � ListControl-� ������� � ������������ � "������������" � Windows
		if( (curIndex < nCount) && (m_DivChangeList.GetItemCount() > 0) )
		{
			if(curIndex==0)
			m_DivChangeList.SetItemState(0, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
			else
			m_DivChangeList.SetItemState(curIndex, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);

			m_DivChangeList.SetFocus();
		}
		else
		if((curIndex >= nCount) && (m_DivChangeList.GetItemCount() > 0) )
		{
			m_DivChangeList.SetItemState(m_DivChangeList.GetItemCount()-1, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
			m_DivChangeList.SetFocus();
		}
//*/

		theApp.ChangeDivBtnClicked = theApp.DIV_BTN_DEL;
}

// ������ "��������"
void CDivisionChoose::OnBnClickedDivAddBtn()
{
	// TODO: �������� ���� ��� ����������� �����������
	//iCtrListItem++;
	//m_DivChangeList.InsertItem(iCtrListItem, _T("Item ") + LintToCStr(iCtrListItem));

	// 0 // � ������ � "��������" ��� �� ����� �������� ��� ���������� ������� ��� ���������, ��� ������� ������ � ��������.
	/*
	// 1 // ��������� ��� ���������� �������, ����� ������������ ��� � ���� �������������� �������
	CString EmptyStr("");
	long nCount=0;		// ����� ������� � Listbox
	long curIndex=0;	// ������ �������� ���������� � Listbox
	POSITION pos=NULL;	// ����� ���������� �������� (pos = curIndex+1)

	nCount = m_DivChangeList.GetItemCount();
	//����� ���������� ������� �� ������ �����������
	pos = m_DivChangeList.GetFirstSelectedItemPosition();
	if(pos==NULL) return;	 // � ������, ���� ������ �� �������:
							// 1) �� ��������� ���� �������������� �������
							// 2) �� ��������� �� ���� �� ������
	curIndex = m_DivChangeList.GetNextSelectedItem(pos);

	CString sDivName = m_DivChangeList.GetItemText(curIndex,0);

	// 1.1 // ������ ����� ���� �������� ��� ������ ���� ����� ����� ��� �������� �������
	theApp.CurDivision = sDivName;
	*/
	// 1.2 // ������ ����� ���� �������� ��� ������ ���� ����� �����, ��� ������ ������ "��������"
	theApp.ChangeDivBtnClicked = theApp.DIV_BTN_ADD;

	// 2 // ��������� ��� ������ �� ��� ��� ���� ������������ �� �������� �������� � �������� ��������
	HandleBtns();

	// 3 // ��������� ���� ��� ������������� �������
	CDivisionEdit* p_DivisionEditDlg = new CDivisionEdit;
	p_DivisionEditDlg->Create(IDD_EDIT_DIVISION_DLG, this);
	p_DivisionEditDlg->ShowWindow(SW_SHOW);
}


// ������ "����������"
void CDivisionChoose::OnBnClickedDivCopyBtn()
{
	// TODO: �������� ���� ��� ����������� �����������
	// 0 // � ������ � "��������" ��� ����� �������� ��� ���������� ������� � ���������, ��� ������� ������ � ��������.
	// 1 // ��������� ��� ���������� �������, ����� ������������ ��� � ���� �������������� �������
	CString EmptyStr("");
	long nCount=0;		// ����� ������� � Listbox
	long curIndex=0;	// ������ �������� ���������� � Listbox
	POSITION pos=NULL;	// ����� ���������� �������� (pos = curIndex+1)

	nCount = m_DivChangeList.GetItemCount();
	//����� ���������� ������� �� ������ �����������
	pos = m_DivChangeList.GetFirstSelectedItemPosition();
	if(pos==NULL) return;	 // � ������, ���� ������ �� �������:
							// 1) �� ��������� ���� �������������� �������
							// 2) �� ��������� �� ���� �� ������
	curIndex = m_DivChangeList.GetNextSelectedItem(pos);
	if( curIndex == (-1) )  return;

	CString sDivName("");
	CString sDivName_Original("");

	//sDivName = m_DivChangeList.GetItemText(curIndex,0);
	//sDivName_Original = sDivName;
	sDivName = theApp.AllDivisions[curIndex][0];
	sDivName_Original = sDivName;
	theApp.DivisionFileName = sDivName;


	// 0 // ���������� �������� �� �������� ����� �������, ����������� ���� � ���� � ������� ��������_�������.sou � ������ ������� ����� �����
	// 1 ��������� ��������� (���� ������) � ini-����� ���� � ����� � ��������� (�������  *.sou)
	// ���� ���� ������������� ��� ��������� ���������� � ������ ������, ���� �� � ����� �����, ��� � exe-���� ����� "�������"
	// � ��������� ��������� �� [����, ��� ��������� ��� exe-����] + [/�������] � ���, ��� ������� � ini-�����, ���� ��� ��������������, � ����������������� ����������.

	CString IniFileName = theApp.IniFileName;
	CString CurDivisionsPath = theApp.CurDivisionsPath;

	if(theApp.ChangeDivBtnClicked != theApp.DIV_BTN_ADD) // ���� �� ���� ������ ������ "��������" �� ������ ��������� �� �����
	{
		// ���������� �������� �������� ��������������� ������ � ����������� .sou �� ������� ���� !!!!!
		// http://www.rsdn.ru/article/qna/baseserv/fileexist.xml

		CString DivPathWithFiles("");
		CString DivPath("");
	
		DivPath = CurDivisionsPath;
		DivPathWithFiles = DivPath + _T("\\*.sou");

		//const wchar_t* _DivPathWithFiles = new wchar_t [_MAX_PATH];  // �������� delete � ����� !!!
		//_DivPathWithFiles = DivPathWithFiles;

		if( !FileExists(DivPathWithFiles) )
		{
			MessageBox( _T("� ����� � ��������� ����������� ����� ��������\n ���������, ���:\n")
						_T("1) ����� \"�������\" ��������� � ��� �� �����, ��� � �������.\n")
						_T("2) � ����� ������� ����� � ����������� .sou"),
						_T("������"), MB_ICONERROR);
		}

		//CIniParam parInjProd1 (CBLOWApp::IniFileName, _T("Injection"), _T("InjProd1"));
		//parInjProd1.Set(m_InjProducts[0]);
		//parInjProd1.Save();


		// 2 ��������� ��� �������� �� .SOU ����� �������, ���� ������� ���������� � ������, � ��������� ��� 
		//	 ��������� � �������������� �������, � �������� theApp, ��� ���������/����������/��������� ����� �������
		//	 ������ �������� ������ � ���� �� ����� ���������� ��� �������� ��������������� �������� ��� ��������� 
		//	 ��������� ���������� ������� � ��� ���������������� ����� ����� 
	
		//CString FileName("������ ������.sou"); 
		CString DivisionFilePath("");
		DivisionFilePath =  CurDivisionsPath + _T("\\") + theApp.DivisionFileName + _T(".sou");
		//MessageBox(	DivisionFilePath, _T("PATH"), 0 );
		CStringA p_FilePath(DivisionFilePath);


		_bstr_t DivisionFilePathBstr = DivisionFilePath;
		_bstr_t bstrOutput("");
		bool validXml=false;

		HRESULT hr = CoInitialize(NULL);
		if(SUCCEEDED(hr))
		{
			try{ bstrOutput = theApp.validateDivFile(DivisionFilePathBstr, validXml); }
			catch(_com_error &e)
			{ bstrOutput = theApp.dump_com_error(e); }
		}

		if(validXml) // ������, ����� ���� "��������" � ������� ����� ���������
		{
			readDivisionFile(DivisionFilePath);
		}
		else //if(!validXml)
		{
			if(bstrOutput.length()>0)
			MessageBox(bstrOutput, L"������ � ����� ��� ��� ��������", MB_OK);

			return ; // ������ ������������ � ������ �� ������
		}
		CoUninitialize();

		//MessageBox(	_T("RETTRUE"), ERROR_STR, MB_ICONERROR );
	}




	// �������� �� ���������� ����������� ������ "�����", ��� ��������� �������� 
	long lNextName = 0;
	CString sNextName("");
	bool Original1=false;
	bool Original2=false;

	bool OriginalCheck1=false;
	bool OriginalCheck2=false;
	bool OriginalCheck3=false;
	CString k0("0"), k1("1"), k2("2"), k3("3"), k4("4"), k5("5"), k6("6"), k7("7"), k8("8"), k9("9");
	// 1 ����� �������� ������ - ��� �� � ����� ������������� ����� " - ����� (?)"
	CString CurCopyNum_Str("");
	long CurCopyNum_Int=0;
	std::map<long, bool> CopyMap;

	// ���� ����
	CString CopyNum("");

	if( sDivName[sDivName.GetLength() - 1] == ')' )
	{
		CurCopyNum_Str.Empty();
		CurCopyNum_Int=0;
		long i=0, j=0, k=0, t=0;
		bool Lfound=false;
		for(i=sDivName.GetLength()-1;  i>0;  i--)
		{
			if(sDivName[i] == '(')
			{Lfound=true; break;}
		}

		if(Lfound)
		for(k=(i+1);  k<sDivName.GetLength();  k++)
		{
			if( sDivName[k] == k0 || sDivName[k] == k1 || sDivName[k] == k2 || sDivName[k] == k3 ||
				sDivName[k] == k4 || sDivName[k] == k5 || sDivName[k] == k6 || sDivName[k] == k7 ||
				sDivName[k] == k8 || sDivName[k] == k9
			  )
			{CurCopyNum_Str += sDivName[k];}
			else if( (sDivName[k] == (CString)(")")) && (CurCopyNum_Str.GetLength()>0) )
			{
				CurCopyNum_Int = _tstol(CurCopyNum_Str);
				// ������� ��������� ��������� ��������� �������: " - ����� ("
				if( sDivName.GetLength() > (CurCopyNum_Str.GetLength() + 11) )
				{
					if(	( sDivName[i-0] == (CString)"(" ) &&
						( sDivName[i-1] == (CString)" " ) &&
						( sDivName[i-2] == (CString)"�" ) &&
						( sDivName[i-3] == (CString)"�" ) &&
						( sDivName[i-4] == (CString)"�" ) &&
						( sDivName[i-5] == (CString)"�" ) &&
						( sDivName[i-6] == (CString)"�" ) &&
						( sDivName[i-7] == (CString)" " ) &&
						( sDivName[i-8] == (CString)"-" ) &&
						( sDivName[i-9] == (CString)" " ) 
					  )
					{
						sDivName.Empty();
						for(t=0; t<(i-9); t++)
						{sDivName += sDivName_Original[t];}
						//Original1=false;
						//Original2=false;
						break;
					}
				}
				else
				{Original2=true;}

				break;
			}
			else //if( CurCopyNum_Str.GetLength()>0 )
			{
				Original2=true;
				break;
			}
		}
	}
	else
	{Original1=true;}

	// ���� ���
	//if(Original1 || Original2)
	for(long i=0, j=0, jmax=0, eq_elem=0, eq_part1=0; i<nCount; i++)
	{
		//OriginalCheck1=false;
		//OriginalCheck2=false;
		//OriginalCheck3=false;

		//if(i != curIndex)
		//{
			sNextName = m_DivChangeList.GetItemText(i,0);

			if( sNextName.GetLength() < sDivName.GetLength())
			{jmax = sNextName.GetLength();}
			else
			{jmax = sDivName.GetLength();}

			//for(j=0, eq_elem=0; j<(sNextName.GetLength()-1); j++)
			//for(j=0, eq_elem=0; j<sDivName.GetLength(); j++)
			for(j=0, eq_elem=0; j<jmax; j++)
			{
				if(sNextName[j] == sDivName[j])
				{eq_elem++;}
				else
				{
					if(!OriginalCheck3)
					break;
				}					//sNextName;	//sDivName;
			}

			if( (eq_elem == sDivName.GetLength()) && (sNextName != sDivName) ) // ������ ����� ��������� ������ ����� � " - ����� (?)"
			{
				OriginalCheck1=true;
				CString sDivNameCopy("");
				CString sDivNameCopyNum("");
				sDivNameCopy += _T(" - ����� (");

				if(	( sNextName[sDivName.GetLength() + 0] == (CString)" " ) &&
					( sNextName[sDivName.GetLength() + 1] == (CString)"-" ) &&
					( sNextName[sDivName.GetLength() + 2] == (CString)" " ) &&
					( sNextName[sDivName.GetLength() + 3] == (CString)"�" ) &&
					( sNextName[sDivName.GetLength() + 4] == (CString)"�" ) &&
					( sNextName[sDivName.GetLength() + 5] == (CString)"�" ) &&
					( sNextName[sDivName.GetLength() + 6] == (CString)"�" ) &&
					( sNextName[sDivName.GetLength() + 7] == (CString)"�" ) &&
					( sNextName[sDivName.GetLength() + 8] == (CString)" " ) &&
					( sNextName[sDivName.GetLength() + 9] == (CString)"(" ) &&
					( sNextName[sNextName.GetLength()-1] == (CString)")" )
				  )
				{
					CurCopyNum_Str.Empty();
					CurCopyNum_Int=0;
					long k=0, t=0;
					for(k=1, t=0;  sDivName.GetLength()+(k+9) != (sNextName.GetLength()-1);  k++, t++)
					{
						CurCopyNum_Str += sNextName[sDivName.GetLength() + (k+9)];
						if( CurCopyNum_Str[t] == k0 || CurCopyNum_Str[t] == k1 || CurCopyNum_Str[t] == k2 || CurCopyNum_Str[t] == k3 || CurCopyNum_Str[t] == k4 ||
							CurCopyNum_Str[t] == k5 || CurCopyNum_Str[t] == k6 || CurCopyNum_Str[t] == k7 || CurCopyNum_Str[t] == k8 || CurCopyNum_Str[t] == k9
						  )
						{//�� � �������
						}
						else
						{
							if(!OriginalCheck3)
							OriginalCheck2=true;
							eq_part1=0;
							break;
						}
					}

					if( sDivName.GetLength()+(k+9) == (sNextName.GetLength()-1) )
					{
						OriginalCheck3=true; // ���� �������� ����� �� ����, ������ ����� �������
						CurCopyNum_Int = _tstol(CurCopyNum_Str);
						CopyMap[CurCopyNum_Int]=true;
					}
				}
				else
				{eq_part1=0;}
			}
			else
			{eq_elem=0;}
		//}
	}
	//OriginalCheck2=true;
	if(!(OriginalCheck3))
	{lNextName=1;}
	else
	{
		for(long i=1; i<32000; i++)
		{
			if(CopyMap[i]==false)
			{// ��� ��������� ��������� ����� �����
				lNextName = i;
				break;
			}
		}
	}

	if(!Original1 && !Original2)
	sDivName = sDivName_Original;

	// 1.1 // ������ ����� ���� �������� ��� ������ ���� ����� ����� ��� ����� �������� �������
	theApp.DivisionFileName = sDivName;
	theApp.DivNextFileName = lNextName;
	// 1.2 // ������ ����� ���� �������� ��� ������ ���� ����� �����, ��� ������ ������ "��������"
	theApp.ChangeDivBtnClicked = theApp.DIV_BTN_COPY;

	// 2 // ��������� ��� ������ �� ��� ��� ���� ������������ �� �������� �������� � ��������� ��������
	HandleBtns();

	// 3 // ��������� ���� ��� ������������� �������
	CDivisionEdit* p_DivisionEditDlg = new CDivisionEdit;
	p_DivisionEditDlg->Create(IDD_EDIT_DIVISION_DLG, this);
	p_DivisionEditDlg->ShowWindow(SW_SHOW);
}



// ������ "���������"
void CDivisionChoose::OnBnClickedDivValidBtn()
{
	// TODO: �������� ���� ��� ����������� �����������
	// 0 // � ������ � "��������" ��� ����� �������� ��� ���������� ������� � ���������, ��� ������� ������ � ��������.
	// 1 // ��������� ��� ���������� �������, ����� ������������ ��� � ���� �������������� �������
	CString EmptyStr("");
	long nCount=0;		// ����� ������� � Listbox
	long curIndex=0;	// ������ �������� ���������� � Listbox
	POSITION pos=NULL;	// ����� ���������� �������� (pos = curIndex+1)

	nCount = m_DivChangeList.GetItemCount();
	//����� ���������� ������� �� ������ �����������
	pos = m_DivChangeList.GetFirstSelectedItemPosition();
	if(pos==NULL) return;	 // � ������, ���� ������ �� �������:
							// 1) �� ��������� ���� �������������� �������
							// 2) �� ��������� �� ���� �� ������
	curIndex = m_DivChangeList.GetNextSelectedItem(pos);
	if( curIndex == (-1) )  return;

	//CString sDivName = m_DivChangeList.GetItemText(curIndex,0);
	CString sDivName = theApp.AllDivisions[curIndex][0];
	theApp.DivisionFileName = sDivName;


	// 0 // ���������� �������� �� �������� ����� �������, ����������� ���� � ���� � ������� ��������_�������.sou � ������ ������� ����� �����
	// 1 ��������� ��������� (���� ������) � ini-����� ���� � ����� � ��������� (�������  *.sou)
	// ���� ���� ������������� ��� ��������� ���������� � ������ ������, ���� �� � ����� �����, ��� � exe-���� ����� "�������"
	// � ��������� ��������� �� [����, ��� ��������� ��� exe-����] + [/�������] � ���, ��� ������� � ini-�����, ���� ��� ��������������, � ����������������� ����������.

	CString IniFileName = theApp.IniFileName;			// ???
	CString CurDivisionsPath = theApp.CurDivisionsPath;	// ???

	if(theApp.ChangeDivBtnClicked != theApp.DIV_BTN_ADD) // ���� �� ���� ������ ������ "��������" �� ������ ��������� �� �����
	{
		// ���������� �������� �������� ��������������� ������ � ����������� .sou �� ������� ���� !!!!!
		// http://www.rsdn.ru/article/qna/baseserv/fileexist.xml

		CString DivPathWithFiles("");
		CString DivPath("");
	
		DivPath = CurDivisionsPath;
		DivPathWithFiles = DivPath + _T("\\*.sou");

		//const wchar_t* _DivPathWithFiles = new wchar_t [_MAX_PATH];  // �������� delete � ����� !!!
		//_DivPathWithFiles = DivPathWithFiles;

		if( !FileExists(DivPathWithFiles) )
		{
			MessageBox( _T("� ����� � ��������� ����������� ����� ��������\n ���������, ���:\n")
						_T("1) ����� \"�������\" ��������� � ��� �� �����, ��� � �������.\n")
						_T("2) � ����� ������� ����� � ����������� .sou"),
						_T("������"), MB_ICONERROR);
		}

		//CIniParam parInjProd1 (CBLOWApp::IniFileName, _T("Injection"), _T("InjProd1"));
		//parInjProd1.Set(m_InjProducts[0]);
		//parInjProd1.Save();


		// 2 ��������� ��� �������� �� .SOU ����� �������, ���� ������� ���������� � ������, � ��������� ��� 
		//	 ��������� � �������������� �������, � �������� theApp, ��� ���������/����������/��������� ����� �������
		//	 ������ �������� ������ � ���� �� ����� ���������� ��� �������� ��������������� �������� ��� ��������� 
		//	 ��������� ���������� ������� � ��� ���������������� ����� ����� 
	
		//CString FileName("������ ������.sou"); 
		CString DivisionFilePath("");
		DivisionFilePath =  CurDivisionsPath + _T("\\") + theApp.DivisionFileName + _T(".sou");
		//MessageBox(	DivisionFilePath, _T("PATH"), 0 );
		CStringA p_FilePath(DivisionFilePath);



		_bstr_t DivisionFilePathBstr = DivisionFilePath;
		_bstr_t bstrOutput("");
		bool validXml=false;
		HRESULT hr = CoInitialize(NULL);
		if(SUCCEEDED(hr))
		{
			try{ bstrOutput = theApp.validateDivFile(DivisionFilePathBstr, validXml); }
			catch(_com_error &e)
			{bstrOutput = theApp.dump_com_error(e);}
		}

		if(validXml) // ������, ����� ���� "��������" � ������� ����� ���������
		{
			readDivisionFile(DivisionFilePath);
		}
		else //if(!validXml)
		{
			if(bstrOutput.length()>0)
			MessageBox(bstrOutput, L"������ � ����� ��� ��� ��������", MB_OK);

			return ; // ������ ������������ � ������ �� ������
		}
		CoUninitialize();

	}



	// 1.1 // ������ ����� ���� �������� ��� ������ ���� ����� ����� ��� ����� �������� �������
	theApp.DivisionFileName = sDivName;
	// 1.2 // ������ ����� ���� �������� ��� ������ ���� ����� �����, ��� ������ ������ "��������"
	theApp.ChangeDivBtnClicked = theApp.DIV_BTN_VALID;

	// 2 // ��������� ��� ������ �� ��� ��� ���� ������������ �� �������� �������� � �������� ��������
	//m_BtnDiv_Add.EnableWindow(FALSE);
	//m_BtnDiv_Del.EnableWindow(FALSE);
	//m_BtnDiv_Copy.EnableWindow(FALSE);
	//m_BtnDiv_Valid.EnableWindow(FALSE);
	//m_BtnDiv_Change.EnableWindow(FALSE);
	//m_BtnDiv_Look.EnableWindow(FALSE);
	//m_BtnDiv_Exit.EnableWindow(FALSE);

	// 3 // ��������� ���� ��� �������������� �������
}



// ������ "��������"
void CDivisionChoose::OnBnClickedDivEditBtn()
{
	// TODO: �������� ���� ��� ����������� �����������
	// 0 // � ������ � "��������" ��� ����� �������� ��� ���������� ������� � ���������, ��� ������� ������ � ��������.
	// 1 // ��������� ��� ���������� �������, ����� ������������ ��� � ���� �������������� �������
	CString EmptyStr("");
	long nCount=0;		// ����� ������� � Listbox
	long curIndex=0;	// ������ �������� ���������� � Listbox
	POSITION pos=NULL;	// ����� ���������� �������� (pos = curIndex+1)

	nCount = m_DivChangeList.GetItemCount();
	//����� ���������� ������� �� ������ �����������
	pos = m_DivChangeList.GetFirstSelectedItemPosition();
	if(pos==NULL) return;	 // � ������, ���� ������ �� �������:
							// 1) �� ��������� ���� �������������� �������
							// 2) �� ��������� �� ���� �� ������
	curIndex = m_DivChangeList.GetNextSelectedItem(pos);
	if( curIndex == (-1) )  return;

	//CString sDivName = m_DivChangeList.GetItemText(curIndex,0);
	CString sDivName = theApp.AllDivisions[curIndex][DIVALL_FILE_NAME];
	theApp.DivisionFileName = sDivName;


	// 0 // ���������� �������� �� �������� ����� �������, ����������� ���� � ���� � ������� ��������_�������.sou � ������ ������� ����� �����
	// 1 ��������� ��������� (���� ������) � ini-����� ���� � ����� � ��������� (�������  *.sou)
	// ���� ���� ������������� ��� ��������� ���������� � ������ ������, ���� �� � ����� �����, ��� � exe-���� ����� "�������"
	// � ��������� ��������� �� [����, ��� ��������� ��� exe-����] + [/�������] � ���, ��� ������� � ini-�����, ���� ��� ��������������, � ����������������� ����������.

	CString IniFileName = theApp.IniFileName;
	CString CurDivisionsPath = theApp.CurDivisionsPath;

	if(theApp.ChangeDivBtnClicked != theApp.DIV_BTN_ADD) // ���� �� ���� ������ ������ "��������" �� ������ ��������� �� �����
	{
		// ���������� �������� �������� ��������������� ������ � ����������� .sou �� ������� ���� !!!!!
		// http://www.rsdn.ru/article/qna/baseserv/fileexist.xml

		CString DivPathWithFiles("");
		CString DivPath("");
	
		DivPath = CurDivisionsPath;
		DivPathWithFiles = DivPath + _T("\\*.sou");

		//const wchar_t* _DivPathWithFiles = new wchar_t [_MAX_PATH];  // �������� delete � ����� !!!
		//_DivPathWithFiles = DivPathWithFiles;

		if( !FileExists( DivPathWithFiles ) )
		{
			MessageBox( _T("� ����� � ��������� ����������� ����� ��������\n ���������, ���:\n")
						_T("1) ����� \"�������\" ��������� � ��� �� �����, ��� � �������.\n")
						_T("2) � ����� ������� ����� � ����������� .sou"),
						_T("������"), MB_ICONERROR);
		}

		//delete [] _DivPathWithFiles;

		//CIniParam parInjProd1 (CBLOWApp::IniFileName, _T("Injection"), _T("InjProd1"));
		//parInjProd1.Set(m_InjProducts[0]);
		//parInjProd1.Save();

		
		// 2 ��������� ��� �������� �� .SOU ����� �������, ���� ������� ���������� � ������, � ��������� ��� 
		//	 ��������� � �������������� �������, � �������� theApp, ��� ���������/����������/��������� ����� �������
		//	 ������ �������� ������ � ���� �� ����� ���������� ��� �������� ��������������� �������� ��� ��������� 
		//	 ��������� ���������� ������� � ��� ���������������� ����� ����� 
	
		//CString FileName("������ ������.sou"); 
		CString DivisionFilePath("");
		DivisionFilePath =  CurDivisionsPath + _T("\\") + theApp.DivisionFileName + _T(".sou");
		//MessageBox(	DivisionFilePath, _T("PATH"), 0 );
		CStringA p_FilePath(DivisionFilePath);


		_bstr_t DivisionFilePathBstr = DivisionFilePath;
		_bstr_t bstrOutput("");
		bool validXml=false;
		HRESULT hr = CoInitialize(NULL);
		if(SUCCEEDED(hr))
		{
			try{ bstrOutput = theApp.validateDivFile(DivisionFilePathBstr, validXml); }
			catch(_com_error &e)
			{bstrOutput = theApp.dump_com_error(e);}
		}

		if(validXml) // ������, ����� ���� "��������" � ������� ����� ���������
		{
			readDivisionFile(DivisionFilePath);
		}
		else //if(!validXml)
		{
			if(bstrOutput.length()>0)
			MessageBox(bstrOutput, L"������ � ����� ��� ��� ��������", MB_OK);

			return ; // ������ ������������ � ������ �� ������
		}
		CoUninitialize();

	}



	// 1.1 // ������ ����� ���� �������� ��� ������ ���� ����� ����� ��� ����� �������� �������
	theApp.DivisionFileName = sDivName;
	// 1.2 // ������ ����� ���� �������� ��� ������ ���� ����� �����, ��� ������ ������ "��������"
	theApp.ChangeDivBtnClicked = theApp.DIV_BTN_CHANGE;

	// 2 // ��������� ��� ������ �� ��� ��� ���� ������������ �� �������� �������� � �������� ��������
	HandleBtns();

	// 3 // ��������� ���� ��� ������������� �������
	CDivisionEdit* p_DivisionEditDlg = new CDivisionEdit;
	p_DivisionEditDlg->Create(IDD_EDIT_DIVISION_DLG, this);
	p_DivisionEditDlg->ShowWindow(SW_SHOW);
}

// ������ "��������"
void CDivisionChoose::OnBnClickedDivLookBtn()
{
	// TODO: �������� ���� ��� ����������� �����������
	// 0 // � ������ � "��������" ��� ����� �������� ��� ���������� ������� � ���������, ��� ������� ������ � ��������.
	// 1 // ��������� ��� ���������� �������, ����� ������������ ��� � ���� �������������� �������
	CString EmptyStr("");
	long nCount=0;		// ����� ������� � Listbox
	long curIndex=0;	// ������ �������� ���������� � Listbox
	POSITION pos=NULL;	// ����� ���������� �������� (pos = curIndex+1)

	nCount = m_DivChangeList.GetItemCount();
	//����� ���������� ������� �� ������ �����������
	pos = m_DivChangeList.GetFirstSelectedItemPosition();
	if(pos==NULL) return;	 // � ������, ���� ������ �� �������:
							// 1) �� ��������� ���� �������������� �������
							// 2) �� ��������� �� ���� �� ������
	curIndex = m_DivChangeList.GetNextSelectedItem(pos);
	if( curIndex == (-1) )  return;

	//CString sDivName = m_DivChangeList.GetItemText(curIndex,0);
	CString sDivName = theApp.AllDivisions[curIndex][0];
	theApp.DivisionFileName = sDivName;


	// 0 // ���������� �������� �� �������� ����� �������, ����������� ���� � ���� � ������� ��������_�������.sou � ������ ������� ����� �����
	// 1 ��������� ��������� (���� ������) � ini-����� ���� � ����� � ��������� (�������  *.sou)
	// ���� ���� ������������� ��� ��������� ���������� � ������ ������, ���� �� � ����� �����, ��� � exe-���� ����� "�������"
	// � ��������� ��������� �� [����, ��� ��������� ��� exe-����] + [/�������] � ���, ��� ������� � ini-�����, ���� ��� ��������������, � ����������������� ����������.

	CString IniFileName = theApp.IniFileName;
	CString CurDivisionsPath = theApp.CurDivisionsPath;

	if(theApp.ChangeDivBtnClicked != theApp.DIV_BTN_ADD) // ���� �� ���� ������ ������ "��������" �� ������ ��������� �� �����
	{
		// ���������� �������� �������� ��������������� ������ � ����������� .sou �� ������� ���� !!!!!
		// http://www.rsdn.ru/article/qna/baseserv/fileexist.xml

		CString DivPathWithFiles("");
		CString DivPath("");
	
		DivPath = CurDivisionsPath;
		DivPathWithFiles = DivPath + _T("\\*.sou");

		//const wchar_t* _DivPathWithFiles = new wchar_t [_MAX_PATH];  // �������� delete � ����� !!!
		//_DivPathWithFiles = DivPathWithFiles;

		if( !FileExists(DivPathWithFiles) )
		{
			MessageBox( _T("� ����� � ��������� ����������� ����� ��������\n ���������, ���:\n")
						_T("1) ����� \"�������\" ��������� � ��� �� �����, ��� � �������.\n")
						_T("2) � ����� ������� ����� � ����������� .sou"),
						_T("������"), MB_ICONERROR);
		}

		//CIniParam parInjProd1 (CBLOWApp::IniFileName, _T("Injection"), _T("InjProd1"));
		//parInjProd1.Set(m_InjProducts[0]);
		//parInjProd1.Save();


		// 2 ��������� ��� �������� �� .SOU ����� �������, ���� ������� ���������� � ������, � ��������� ��� 
		//	 ��������� � �������������� �������, � �������� theApp, ��� ���������/����������/��������� ����� �������
		//	 ������ �������� ������ � ���� �� ����� ���������� ��� �������� ��������������� �������� ��� ��������� 
		//	 ��������� ���������� ������� � ��� ���������������� ����� ����� 
	
		//CString FileName("������ ������.sou"); 
		CString DivisionFilePath("");
		DivisionFilePath =  CurDivisionsPath + _T("\\") + theApp.DivisionFileName + _T(".sou");
		//MessageBox(	DivisionFilePath, _T("PATH"), 0 );
		CStringA p_FilePath(DivisionFilePath);


		_bstr_t DivisionFilePathBstr = DivisionFilePath;
		_bstr_t bstrOutput("");
		bool validXml=false;
		HRESULT hr = CoInitialize(NULL);
		if(SUCCEEDED(hr))
		{
			try{ bstrOutput = theApp.validateDivFile(DivisionFilePathBstr, validXml); }
			catch(_com_error &e)
			{bstrOutput = theApp.dump_com_error(e);}
		}

		if(validXml) // ������, ����� ���� "��������" � ������� ����� ���������
		{
			readDivisionFile(DivisionFilePath);
		}
		else //if(!validXml)
		{
			if(bstrOutput.length()>0)
			MessageBox(bstrOutput, L"������ � ����� ��� ��� ��������", MB_OK);

			return ; // ������ ������������ � ������ �� ������
		}
		CoUninitialize();

	}


	// 1.1 // ������ ����� ���� �������� ��� ������ ���� ����� ����� ��� ����� ���������� �������
	theApp.DivisionFileName = sDivName;
	// 1.2 // ������ ����� ���� �������� ��� ������ ���� ����� �����, ��� ������ ������ "��������"
	theApp.ChangeDivBtnClicked = theApp.DIV_BTN_LOOK;

	// 2 // ��������� ��� ������ �� ��� ��� ���� ������������ �� �������� �������� � �������� ��������


	// 3 // ��������� ���� ��� ������������� �������
	CDivisionEdit* p_DivisionEditDlg = new CDivisionEdit;
	p_DivisionEditDlg->Create(IDD_EDIT_DIVISION_DLG, this);
	p_DivisionEditDlg->ShowWindow(SW_SHOW);
}

// ������ "�����"   �� ���� "���������"
void CDivisionChoose::OnBnClickedCancel()
{
	// TODO: �������� ���� ��� ����������� �����������
	//HWND HwndSOUDlg=NULL;
	//::GetDlgItem(HwndSOUDlg, IDD_SOUGENERATOR_DIALOG);
	//::PostMessage(HwndSOUDlg, WM_DIVISION_CHOOSE_EXIT,0,0);
	theApp.ChangeDivBtnClicked = theApp.DIV_NOBTN;

	AfxGetMainWnd()->PostMessage(WM_DIVISION_CHOOSE_EXIT, 0, 0);

	CDialog::OnCancel();
}


// ������� �� ������ "���������" �� ���� "��������� �������"
LRESULT CDivisionChoose::OnDivisionEditSave( WPARAM wparam , LPARAM lparam )
{
	long nCount=0;		// ����� ������� � Listbox
	long curIndex=0;	// ������ �������� ���������� � Listbox
	POSITION pos=NULL;	// ����� ���������� �������� (pos = curIndex+1)

	nCount = m_DivChangeList.GetItemCount();
	//����� ���������� ������� �� ������ �����������
	pos = m_DivChangeList.GetFirstSelectedItemPosition();
	curIndex = m_DivChangeList.GetNextSelectedItem(pos);
	//if( curIndex == (-1) )  return;

	// ������ ��������� � ����, �� ������� �� ������, ����� ��������� � ����������� ����� 2 �����.
	if( (curIndex!=(-1)) && (curIndex < nCount) && (m_DivChangeList.GetItemCount() > 0) )
	{
		if( (theApp.ChangeDivBtnClicked == theApp.DIV_BTN_COPY) || (theApp.ChangeDivBtnClicked == theApp.DIV_BTN_ADD) )
		{m_DivChangeList.SetItemState(curIndex, 0, LVIS_SELECTED);}
	}
	else
	if( (curIndex!=(-1)) && (curIndex >= nCount) && (m_DivChangeList.GetItemCount() > 0) )
	{
		if( (theApp.ChangeDivBtnClicked == theApp.DIV_BTN_COPY) || (theApp.ChangeDivBtnClicked == theApp.DIV_BTN_ADD) )
		{m_DivChangeList.SetItemState(curIndex, 0, LVIS_SELECTED);}
	}


	m_BtnDiv_Add.EnableWindow(TRUE);
	m_BtnDiv_Del.EnableWindow(TRUE);
	m_BtnDiv_Copy.EnableWindow(TRUE);
	m_BtnDiv_Valid.EnableWindow(TRUE);
	m_BtnDiv_Change.EnableWindow(TRUE);
	m_BtnDiv_Look.EnableWindow(TRUE);
	m_BtnDiv_Exit.EnableWindow(TRUE);

	// ���������, ��� ����� ������� �� ������ "��������� �������" ��� �������� ������ ��������
	long AddedDivNumInt=0;
	bool AddedDivNumBl=false;
	CString DivisionNameInList("");	// ��� ���������� �������, ������������ � ������ ���� ListControl
	CString DivisionFileName("");	// ��� ���������� ����� �������
	CString wStr("");				// ������� �� ������ �������
	CString EmptyStr("");
	theApp.AllDivisionsFileNames.clear();

	std::vector<std::vector<CString>> NewDivisions; // ����� ����������� ��������� � ���� SOU ������, ������ �� ����� ��� �� ��������/���������� ����� ��� ���� ���������
	std::vector<CString> OneDivision;


	//for(int i = 0; i < 5; i++)
	//{
	//	cs.Format(_T("������� � %d"), i+1);
	//	m_DivChangeList.InsertItem(i, cs);
	//}

	CRect rect;
	m_DivChangeList.GetClientRect(rect);

////	m_DivChangeList.DeleteAllItems();

	// ��������� ������ ���������� �������� ��������� �������� ������ .sou �� ����� "�������"
	//m_DivChangeList.DeleteAllItems();	// �������������� ������� ������ � ����������
	//m_DivChangeList.RemoveAllGroups();	// �������������� ������� ������ � ����������
	if(theApp.CurDivisionsPath != EmptyStr)
	{
		CString sPath = theApp.CurDivisionsPath;
		CFileFind hFile;
		bool bFound = false;
		bFound = hFile.FindFile( sPath + _T("\\*.sou") );

		//m_DivChangeList.InsertColumn(0, _T("�������� ��������"), LVCFMT_LEFT, 300);
		//m_DivChangeList.InsertColumn(1, _T("�������"), LVCFMT_LEFT, 100); //rect.Width() );

		long LBiter=0;
		while ( bFound )
		{
			bFound = hFile.FindNextFile();
			//if( (! hFile.IsDots()) && ( hFile.IsDirectory() ) )		
			if( ! hFile.IsDots() )
			{
				DivisionFileName = hFile.GetFileName();

				CString szExt = _tcsrchr(DivisionFileName, '.'); // �������� szExt = ".sou"
				if(szExt == _T(".sou"))
				{
					// ������� ��������� 4 ������� �� ����� ������� �����
					DivisionFileName.Delete(DivisionFileName.GetLength() - szExt.GetLength(), 4);

					// !!! � ������� ������ ����������� �������� ������ ��� ���������� !!!!
					OneDivision.push_back(DivisionFileName);		// [0] - �������� �����

					// ��������� ������ � ��� ������, ���� ���������� .sou ����
					//m_DivChangeList.InsertItem(LBiter, DivisionFileName);

/////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// �������� �� ���� .SOU ������ �������� ���� "�������"
					CString IniFileName = theApp.IniFileName;
					CString CurDivisionsPath = theApp.CurDivisionsPath;

					// ���������� �������� �������� ��������������� ������ � ����������� .sou �� ������� ���� !!!!!
					// http://www.rsdn.ru/article/qna/baseserv/fileexist.xml

					CString DivPathWithFiles("");
					CString DivPath("");
	
					DivPath = theApp.CurDivisionsPath;
					DivPathWithFiles = DivPath + _T("\\*.sou");

					//const wchar_t* _DivPathWithFiles = new wchar_t [_MAX_PATH];  // �������� delete � ����� !!!
					//_DivPathWithFiles = DivPathWithFiles;

					if( !FileExists(DivPathWithFiles) )
					{
						MessageBox( _T("� ����� � ��������� ����������� ����� ��������\n ���������, ���:\n")
									_T("1) ����� \"�������\" ��������� � ��� �� �����, ��� � �������.\n")
									_T("2) � ����� ������� ����� � ����������� .sou"),
									_T("������"), MB_ICONERROR);
					}

					//CIniParam parInjProd1 (CBLOWApp::IniFileName, _T("Injection"), _T("InjProd1"));
					//parInjProd1.Set(m_InjProducts[0]);
					//parInjProd1.Save();


					// 2 ��������� ��� �������� �� .SOU ����� �������, ���� ������� ���������� � ������, � ��������� ��� 
					//	 ��������� � �������������� �������, � �������� theApp, ��� ���������/����������/��������� ����� �������
					//	 ������ �������� ������ � ���� �� ����� ���������� ��� �������� ��������������� �������� ��� ��������� 
					//	 ��������� ���������� ������� � ��� ���������������� ����� ����� 
	
					//CString FileName("������ ������.sou"); 
					CString DivisionFilePath("");
					DivisionFilePath =  CurDivisionsPath + _T("\\") + DivisionFileName + _T(".sou");
					//MessageBox(	DivisionFilePath, _T("PATH"), 0 );
					CStringA p_FilePath(DivisionFilePath);


					_bstr_t DivisionFilePathBstr = DivisionFilePath;
					_bstr_t bstrOutput("");
					bool validXml=false;
					HRESULT hr = CoInitialize(NULL);
					if(SUCCEEDED(hr))
					{
						try{ bstrOutput = theApp.validateDivFile(DivisionFilePathBstr, validXml); }
						catch(_com_error &e)
						{bstrOutput = theApp.dump_com_error(e);}
					}

					if(validXml) // ������, ����� ���� "��������" � ������� ����� ���������
					{
						//readDivisionHeadFile(DivisionFilePath);

						CComPtr<IXMLDOMDocument> iXMLDoc;
						iXMLDoc.CoCreateInstance(__uuidof(DOMDocument));
 	
						// Following is a bugfix for PocketPC.
						#ifdef _UNDER_CE
						gargle bargle
						iXMLDoc->put_async(VARIANT_FALSE);
						CComQIPtr<IObjectSafety,&IID_IObjectSafety> iSafety(iXMLDoc);
						if (iSafety) 
						{	DWORD dwSupported, dwEnabled; 
							iSafety->GetInterfaceSafetyOptions(IID_IXMLDOMDocument,&dwSupported,&dwEnabled);
							iSafety->SetInterfaceSafetyOptions(IID_IXMLDOMDocument,dwSupported,0);
						}
						#endif
 						// Load the file. 
						VARIANT_BOOL bSuccess=false;
						// Can load it from a url/filename...
						//iXMLDoc->load(CComVariant(url),&bSuccess);
						//iXMLDoc->load(CComVariant("D:/SDHW-5-SOU/Test-Interface2/XML MSXML/sou.sou"), &bSuccess);
						iXMLDoc->load(CComVariant(DivisionFilePath), &bSuccess);
	
						// or from a BSTR...
						//iXMLDoc->loadXML(CComBSTR(src),&bSuccess);
 
						// Get a pointer to the root
						CComPtr<IXMLDOMElement> iRootElm;
						iXMLDoc->get_documentElement(&iRootElm);

						// Thanks to the magic of CComPtr, we never need call
						// Release() -- that gets done automatically.

						TElem eroot(iRootElm);
						//TElem subroot = eroot.subnode(L"�������_���");
						wstring DivAtrs;

						DivAtrs = eroot.attr(L"���"			);		OneDivision.push_back(DivAtrs.c_str());	// [0] - �������� �������
						DivAtrs = eroot.attr(L"�����"		);		OneDivision.push_back(DivAtrs.c_str());	//// [1] - �������� ������������
						DivAtrs = eroot.attr(L"�����_���"	);		OneDivision.push_back(DivAtrs.c_str());	//// [2] - ID ������������
						DivAtrs = eroot.attr(L"�������"		);		OneDivision.push_back(DivAtrs.c_str());	// [3] - �������� �������� � ����������
						DivAtrs = eroot.attr(L"�������_���"	);		OneDivision.push_back(DivAtrs.c_str());	//// [4] - ID ��������
						DivAtrs = eroot.attr(L"��������"	);		OneDivision.push_back(DivAtrs.c_str());	// [5] - ��������
						DivAtrs = eroot.attr(L"�������"		);		OneDivision.push_back(DivAtrs.c_str());	// [6] - �������
						DivAtrs = eroot.attr(L"�����"		);		OneDivision.push_back(DivAtrs.c_str());	// [7] - �����
						DivAtrs = eroot.attr(L"�����_�����������");	OneDivision.push_back(DivAtrs.c_str());	// [8] - �����_�����������
						DivAtrs = eroot.attr(L"�����_�����"	);		OneDivision.push_back(DivAtrs.c_str());	//// [9] - ����� ������������
						DivAtrs = eroot.attr(L"���_������"	);		OneDivision.push_back(DivAtrs.c_str());	//// [10] - ��� ������ �������
						DivAtrs = eroot.attr(L"���_�����"	);		OneDivision.push_back(DivAtrs.c_str());	//// [11] - ��� ����� �������

						NewDivisions.push_back(OneDivision);
						OneDivision.clear();

						int u=0;
					}
					else //if(!validXml)
					{
						if(bstrOutput.length()>0)
						MessageBox(bstrOutput, L"������ � ����� ��� ��� ��������", MB_OK);

						//return TRUE;
					}
					CoUninitialize();

				}
				//AfxMessageBox(DivisionFileName);
			}
			LBiter++;
		}

		m_DivChangeList.SetExtendedStyle( m_DivChangeList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	}


	/////////////////////////////////////////////////////////////////////////////
	// 2 // ����� ��������� ���� ���������� ���� ��������, ���� ��� ��������� ����������� �� � ������� �� �������� ��������
	
	for(long i=0; i<NewDivisions.size(); i++)
	{OneDivision.push_back(NewDivisions[i][DIVALL_DIV_NAME]);}

	std::sort(OneDivision.begin(), OneDivision.end());

	for(long i=0; i<OneDivision.size(); i++)
	{
		for(long j=0; j<NewDivisions.size(); j++)
		{
			if(OneDivision[i] == NewDivisions[j][DIVALL_DIV_NAME])
			{
				std::vector<CString> Tmp_Vec;
				Tmp_Vec = NewDivisions[j];
				NewDivisions.erase(NewDivisions.begin() + j);
				NewDivisions.insert(NewDivisions.begin() + i, Tmp_Vec);
			}
		}
	}



	/////////////////////////////////////////////////////////////////////////////
	// 3 // ������� ����� ��������������� ������ ���� ��������, ������� ���� �� ���-�� ���������/����������� ��� �����-�� ���� ������ ��������

	// ������� ���������� ��������: � ����������� �� ������� ������ ��
	// 1.1 �����: � ����� ��������������� ������ (NewDivisions) ������� �� ������� ������ (theApp.AllDivisions)
	// ����� �������, � ���������� ��� ������ � �����. ������ ������ ������, � �������� ����� � ��������, � �������� ���������������� ������
	// 1.2 �����: �� �� ������ ��� � �������� 
	// 1.3 �����: ������ 1.4 ��������: ������

	int nNewDivisionIndex(-1);
	UINT nAllDivisionsNum = theApp.AllDivisions.size();
	for(UINT i(0); i<nAllDivisionsNum; i++)
	{
		if(
				(theApp.AllDivisions[i][DIVALL_PIPE_NAME] != NewDivisions[i][DIVALL_PIPE_NAME])
			&&	(theApp.AllDivisions[i][DIVALL_PROD_NAME] != NewDivisions[i][DIVALL_PROD_NAME])
			&&	(theApp.AllDivisions[i][DIVALL_DIV_NAME]  != NewDivisions[i][DIVALL_DIV_NAME])
		  )
		{
			nNewDivisionIndex = i;
			break;
		}

		if( i == nAllDivisionsNum )
		{ nNewDivisionIndex = (i+1); }
	}


	UINT nNewDivisionsNum = NewDivisions.size();
	switch(theApp.ChangeDivBtnClicked)
	{
	case theApp.DIV_BTN_ADD:  // ������ ������ "�������� �������"
	case theApp.DIV_BTN_COPY: // ������ ������ "���������� �������"
		m_DivChangeList.DeleteAllItems();
		for(UINT i(0); i<nNewDivisionsNum; i++)
		{
			(void)m_DivChangeList.AddItem(	NewDivisions[i][DIVALL_PIPE_NAME],
											NewDivisions[i][DIVALL_PROD_NAME],
											NewDivisions[i][DIVALL_DIV_NAME]
										 );
		}

		if(nNewDivisionIndex >= 0)
		{
			// ���������������� �� ������ ��������� ������
			m_DivChangeList.EnsureVisible(nNewDivisionIndex, true);
			m_DivChangeList.SetItemState(nNewDivisionIndex, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
			m_DivChangeList.SetFocus();
		}
		break;

	//case theApp.DIV_BTN_CHANGE: //������ ������ "�������� �������"
	//case theApp.DIV_BTN_LOOK: // ������ ������ "�������� �������"
	//	break;
	}



#if 0
	for(long i=0; i<NewDivisions.size(); i++)
	{
		DivisionNameInList = m_DivChangeList.GetItemText(i , DIV_LIST_NAME);
		if( (!AddedDivNumBl) && (DivisionNameInList != NewDivisions[i][DIVALL_DIV_NAME]) )
		{
			AddedDivNumBl=true;
			AddedDivNumInt=i;
		}

		if(DivisionNameInList != NewDivisions[i][DIVALL_DIV_NAME])
		{
			/*
			//m_DivChangeList.InsertItem(i, theApp.AllDivisions[i][1]);
			// ��� ��� ��� ����� ������:
			m_DivChangeList.SetItemText(i, 0, NewDivisions[i][DIVALL_DIV_NAME]);
			m_DivChangeList.SetItemText(i, 1, NewDivisions[i][DIVALL_PIPE_ID]);
			*/

			(void)m_DivChangeList.AddItem(	NewDivisions[i][DIVALL_PIPE_NAME],
											NewDivisions[i][DIVALL_PROD_NAME],
											NewDivisions[i][DIVALL_DIV_NAME]
										 );
			break;
		}

		if( (nCount>0) && (nCount < (i+1)) && (theApp.ChangeDivBtnClicked != theApp.DIV_BTN_ADD) )
		{
			/*
			m_DivChangeList.InsertItem(i, NewDivisions[i][DIVALL_DIV_NAME]);
			// ��� ��� ��� ����� ������:
			m_DivChangeList.SetItemText(i, 0, NewDivisions[i][DIVALL_DIV_NAME]);
			m_DivChangeList.SetItemText(i, 1, NewDivisions[i][DIVALL_PIPE_ID]);
			*/

			(void)m_DivChangeList.AddItem(	NewDivisions[i][DIVALL_PIPE_NAME],
											NewDivisions[i][DIVALL_PROD_NAME],
											NewDivisions[i][DIVALL_DIV_NAME]
										 );
			break;
		}
	}
/*
	for(long i=0; i<theApp.AllDivisions.size(); i++)
	{
		DivisionNameInList = m_DivChangeList.GetItemText(i , 0);
		if( (!AddedDivNumBl) && (DivisionNameInList != theApp.AllDivisions[i][]) )
		{
			AddedDivNumBl=true;
			AddedDivNumInt=i;
		}

		if(DivisionNameInList != theApp.AllDivisions)
		{
			m_DivChangeList.InsertItem(i, theApp.AllDivisions[i][1]);
			// ��� ��� ��� ����� ������:
			m_DivChangeList.SetItemText(i, 0, theApp.AllDivisions[i][1]);
			m_DivChangeList.SetItemText(i, 1, theApp.AllDivisions[i][3]);
		}
	}
*/	

	theApp.AllDivisions = NewDivisions; // ����� � ��������������� ������ �������� ��������� � ������ ������

	//theApp.AllDetectors.clear();
	theApp.FullDivision.clear();
	//theApp.DivDetectors.clear();
	theApp.DivSortDetectors.clear();


	// ������������� ���������� � ListControl-� ������� � ������������ � "������������" � Windows
	if( (curIndex < nCount) && (m_DivChangeList.GetItemCount() > 0) )
	{
		if( (theApp.ChangeDivBtnClicked == theApp.DIV_BTN_COPY) || (theApp.ChangeDivBtnClicked == theApp.DIV_BTN_ADD) )
		{
			// ���������������� � �� ������ ��������� ������
			//int Scrol_pos=0;	// ����� ���������� �������� (pos = curIndex+1)
			//Scrol_pos = m_DivChangeList.GetScrollPos(SB_VERT);
			//m_DivChangeList.SetScrollPos(SB_VERT,curIndex); // ����� ��� ���������, �� � ���� ������ �� ����������
			//m_DivChangeList.ScrollWindow(SB_VERT,curIndex,0,0);
			//m_DivChangeList.SetHotItem(AddedDivNumInt);
			
			//m_DivChangeList.SetView(AddedDivNumInt);
			//m_DivChangeList.UpdateWindow();
			//m_DivChangeList.InsertItem(0, _T("1"));
			//m_DivChangeList.DeleteItem(0);
			
			// ���������������� �� ������ ��������� ������
			m_DivChangeList.EnsureVisible(AddedDivNumInt, true);
			m_DivChangeList.SetItemState(AddedDivNumInt, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
			m_DivChangeList.SetFocus();
		}
		else
		{
			//if( theApp.ChangeDivBtnClicked == theApp.DIV_BTN_DEL )
			//m_DivChangeList.SetItemState(0, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
			//else
			m_DivChangeList.EnsureVisible(curIndex, true);
			m_DivChangeList.SetItemState(curIndex, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
			m_DivChangeList.SetFocus();
		}
	}
	else
	if((curIndex >= nCount) && (m_DivChangeList.GetItemCount() > 0) )
	{
		if( (theApp.ChangeDivBtnClicked == theApp.DIV_BTN_COPY) || (theApp.ChangeDivBtnClicked == theApp.DIV_BTN_ADD) )
		{
			m_DivChangeList.EnsureVisible(AddedDivNumInt, true);
			m_DivChangeList.SetItemState(AddedDivNumInt, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
			m_DivChangeList.SetFocus();
		}
		else
		{
			m_DivChangeList.EnsureVisible(m_DivChangeList.GetItemCount()-1, true);
			m_DivChangeList.SetItemState(m_DivChangeList.GetItemCount()-1, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
			m_DivChangeList.SetFocus();
		}
	}
#endif

	theApp.AllDivisions = NewDivisions; // ����� � ��������������� ������ �������� ��������� � ������ ������

	theApp.FullDivision.clear();
	theApp.DivSortDetectors.clear();


	return 0;
}


// ������� �� ������ "�����" �� ���� "��������� �������"
LRESULT CDivisionChoose::OnDivisionEditExit( WPARAM wparam , LPARAM lparam )
{
	m_BtnDiv_Add.EnableWindow(TRUE);
	m_BtnDiv_Del.EnableWindow(TRUE);
	m_BtnDiv_Copy.EnableWindow(TRUE);
	m_BtnDiv_Valid.EnableWindow(TRUE);
	m_BtnDiv_Change.EnableWindow(TRUE);
	m_BtnDiv_Look.EnableWindow(TRUE);
	m_BtnDiv_Exit.EnableWindow(TRUE);

	//theApp.AllDetectors.clear();
	theApp.FullDivision.clear();
	//theApp.DivDetectors.clear();
	theApp.DivSortDetectors.clear();

	return 0;
}


void CDivisionChoose::HandleBtns()
{
	switch(theApp.ChangeDivBtnClicked)
	{
	case theApp.DIV_BTN_ADD:
	case theApp.DIV_BTN_COPY:
	case theApp.DIV_BTN_LOOK:
		m_BtnDiv_Add.EnableWindow(FALSE);
		m_BtnDiv_Del.EnableWindow(FALSE);
		m_BtnDiv_Copy.EnableWindow(FALSE);
		m_BtnDiv_Valid.EnableWindow(FALSE);
		m_BtnDiv_Change.EnableWindow(FALSE);
		m_BtnDiv_Look.EnableWindow(FALSE);
		m_BtnDiv_Exit.EnableWindow(FALSE);
		break;
	}

}


//*	
/////////////////////////////////////////////////////////////////
//////////////////// ������ ������

CString CDivisionChoose::LintToCStr(long int x)
{
	CString strX;
	strX.Format( _T("%i"), x ); // %d // %l
	return strX;
}


CString CDivisionChoose::DoubleToCStr(double x, int count) // x - �����, count - ����� ������ ����� �������
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


void CDivisionChoose::DeleteLastSymbol(CString& Str)
{
	if(Str.GetLength()>0)
	{
		long i = Str.GetLength() - 1;
		if(  (Str[i] != ' ')  &&  ( Str[i] != CString("") ) )
		Str.Delete(i);
	}
	//return Str;
}


//c_MyList.SetItemState(nItem, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);

// You can change this at run time by
// m_listCtrl.ModifyStyle(LVS_SINGLESEL /* reset single sel bit */, 0);
// If LVS_SINGLESEL ist not set, shift-key, shift-mouse, ctrl-mouse work fine.

// You can programatically de/select an item by
// m_listCtrl.SetItemState(itemIdx, LVIS_SELECTED, LVIS_SELECTED);	// select
// m_listCtrl.SetItemState(itemIdx, 0, LVIS_SELECTED);				// deselect


void CDivisionChoose::OnLvnItemchangedDevChangeList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �������� ���� ��� ����������� �����������

	POSITION pos=NULL;	// ����� ���������� �������� (pos = curIndex+1)
	//����� ���������� ������� �� ������ �����������
	pos = m_DivChangeList.GetFirstSelectedItemPosition();
	iCtrChoosenListItem = m_DivChangeList.GetNextSelectedItem(pos);

	*pResult = 0;
}


void CDivisionChoose::OnBnClickedOk()
{
	// TODO: �������� ���� ��� ����������� �����������
	//CDialog::OnOK();
}


BOOL CDivisionChoose::PreTranslateMessage(LPMSG pMsg)
{
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

/*	switch (pMsg->message)
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
//   return FALSE;
}


// ������� _findfirst ���������� ���������� � ������ �����, ��������������� �������� ����� ������.
bool CDivisionChoose::FileExists(const wchar_t *fname)
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






/*
CString CDivisionChoose::DocErrorGetErrorInRus(CString DescriptionEng)
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




// This OnSize function resizes one large control in a dialog. 
// The one control grows horizontally and vertically to fill the dialog. It's position remains unchanged.
// Other controls (buttons etc) would typically be above the one resizable control.
// How to add OnSize:
// [1] add to .h:                     afx_msg void OnSize(UINT nType, int cx, int cy);
// [2] add to message map in .cpp:    ON_WM_SIZE()
// [3] add this OnSize function.
void CDivisionChoose::OnSize(UINT nType, int formWidthArg, int formHeightArg)
{
	CDialog::OnSize(nType, formWidthArg, formHeightArg); // Let dialog resize itself.

//#if 0
	if(bFirstDlg)
	{
		CRect CurrentRect(NULL); // ������� ������
		this->GetWindowRect(&CurrentRect);
		LONG CurW = CurrentRect.right - CurrentRect.left;
		LONG CurH = CurrentRect.bottom - CurrentRect.top;

		if( (CurW > OrigW) || (CurH > OrigH) )
		{
			LONG DeltaW = CurW - OrigW;
			LONG DeltaH = CurH - OrigH;

			CRect CurObjectRect(NULL);
			CWnd *pWnd = NULL;

			// ������ �������:	List-����� � ���������
			pWnd = GetDlgItem(IDC_DEV_CHANGE_LIST);
			pWnd->GetWindowRect(&CurObjectRect);
			ScreenToClient(&CurObjectRect);
			//position:  rect.left, rect.top
			//size: rect.Width(), rect.Height()

			LONG dObjx(CurObjectRect.left), dObjy(CurObjectRect.top), dObjw(formWidthArg - CurObjectRect.left), dObjh(formHeightArg - CurObjectRect.top);
			m_DivChangeList.MoveWindow( dObjx
									, dObjy
									//, CurObjectRect.Width() + DeltaW
									//, CurObjectRect.Height()+ DeltaH
									//, CurW - CurObjectRect.Width()
									//, CurH - CurObjectRect.Height()
									//, CurW 
									//, CurH 
									, dObjw - 15
									, dObjh - 40
									);

			/////////////////////////////////////////////////////////////////
			// ������ ������� � �������:	������ ��� ���������� � ���������

			// ������ �������:
			pWnd = GetDlgItem(IDC_DIV_ADD_BTN);
			pWnd->GetWindowRect(&CurObjectRect);
			ScreenToClient(&CurObjectRect);
			m_BtnDiv_Add.MoveWindow( CurObjectRect.left	, formHeightArg - 30, CurObjectRect.Width()	, CurObjectRect.Height()	);

			// ������ �������:
			pWnd = GetDlgItem(IDC_DIV_DEL_BTN);
			pWnd->GetWindowRect(&CurObjectRect);
			ScreenToClient(&CurObjectRect);
			m_BtnDiv_Del.MoveWindow( CurObjectRect.left	, formHeightArg - 30, CurObjectRect.Width()	, CurObjectRect.Height()	);

			// ������ �������:
			pWnd = GetDlgItem(IDC_DIV_COPY_BTN);
			pWnd->GetWindowRect(&CurObjectRect);
			ScreenToClient(&CurObjectRect);
			m_BtnDiv_Copy.MoveWindow( CurObjectRect.left	, formHeightArg - 30, CurObjectRect.Width()	, CurObjectRect.Height()	);

			// ������ �������:
			//pWnd = GetDlgItem(IDC_DIV_VALID_BTN);
			//pWnd->GetWindowRect(&CurObjectRect);
			//ScreenToClient(&CurObjectRect);
			//m_BtnDiv_Valid.MoveWindow( CurObjectRect.left	, formHeightArg - 30, CurObjectRect.Width()	, CurObjectRect.Height()	);

			// ������ �������:
			pWnd = GetDlgItem(IDC_DIV_EDIT_BTN);
			pWnd->GetWindowRect(&CurObjectRect);
			ScreenToClient(&CurObjectRect);
			m_BtnDiv_Change.MoveWindow( CurObjectRect.left	, formHeightArg - 30, CurObjectRect.Width()	, CurObjectRect.Height()	);

			// ������ �������:
			pWnd = GetDlgItem(IDC_DIV_LOOK_BTN);
			pWnd->GetWindowRect(&CurObjectRect);
			ScreenToClient(&CurObjectRect);
			m_BtnDiv_Look.MoveWindow( CurObjectRect.left	, formHeightArg - 30, CurObjectRect.Width()	, CurObjectRect.Height()	);

			// ������ �������:
			pWnd = GetDlgItem(IDCANCEL);
			pWnd->GetWindowRect(&CurObjectRect);
			ScreenToClient(&CurObjectRect);
			m_BtnDiv_Exit.MoveWindow( CurObjectRect.left	, formHeightArg - 30, CurObjectRect.Width()	, CurObjectRect.Height()	);

			int u=0;
		}
		else
		{
		} // ������ ������ ��� �� ����������
	}
//#endif


	return;


} // OnSize()




