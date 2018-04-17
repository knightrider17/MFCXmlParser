// DivisionEdit.cpp: ���� ����������
//

#include "stdafx.h"
#include "SOU-Generator.h"
#include "DivisionEdit.h"
#include "afxdialogex.h"

#include "helpful.h"
#include "windows.h"
#include <iostream>
#include <io.h>
#include <map>
#include <algorithm>

#include "TElem.h"

//#define WATCH_YN 2
#define PROD_NUM 3
//*

#define DET_HEAD		0 // ��� ����� � ����� ��������
#define DIV_DIV_HEAD	0 // ��� ����� � ���� � ����� �������
#define DIV_DET_HEAD	1 // ��� ������� �������� � �������, ������� �������� ���� � �������

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
#define DIV_ELEMENS_NUM	12 


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

//using namespace std;

// ���������� ���� CDivisionEdit

IMPLEMENT_DYNAMIC(CDivisionEdit, CDialog)

CDivisionEdit::CDivisionEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CDivisionEdit::IDD, pParent)
{
	bFirstDlg=false;
}

CDivisionEdit::~CDivisionEdit()
{
}

void CDivisionEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_BtnDivOK);
	DDX_Control(pDX, IDC_DIV_SAVE_BTN, m_BtnDivSave);
	DDX_Control(pDX, IDCANCEL, m_BtnDivExit);
	DDX_Control(pDX, IDC_DIV_NAME_EDIT, m_EditDivName);
	DDX_Control(pDX, IDC_DIV_PROD_CMBX, m_CmBxDivProd);
////	DDX_Control(pDX, IDC_DIV_PARAM_EDIT, m_EditDivParam);
////	DDX_Control(pDX, IDC_DIV_WATCH_EDIT, m_EditDivWatch);
////	DDX_Control(pDX, IDC_DIV_WATCH_CMBX, m_CmBxDivWatch);
	DDX_Control(pDX, IDC_DIV_TIMEDETECT_EDIT, m_EditDivTimeDetect);
	DDX_Control(pDX, IDC_DIV_DETECTORS_LIST, m_ListDiv_Det);
	DDX_Control(pDX, IDC_DIV_ADD_BTN, m_BtnDiv_DetAdd);
	DDX_Control(pDX, IDC_DIV_DET_DELL_BTN, m_BtnDiv_DetDel);
	DDX_Control(pDX, IDC_DIV_DET_CHANGE_BTN, m_BtnDiv_DetChange);
	DDX_Control(pDX, IDC_DIV_DET_LOOK_BTN, m_BtnDiv_DetLook);
	DDX_Control(pDX, IDC_DIV_WAVE_EDIT, m_EditDivWave);
	DDX_Control(pDX, IDC_DIV_FILE_NAME_EDIT, m_EditDivFileName);
	DDX_Control(pDX, IDC_DIV_DETECTORS_STATIC, m_StaticDiv_Det);
	DDX_Control(pDX, IDC_DIV_DET_ADD_ALL_BTN, m_BtnDiv_DetAddAll);
	DDX_Control(pDX, IDC_DIV_PIPE_CMBX, m_CmBxDivPipe);
	DDX_Control(pDX, IDC_DIV_PIPE_LENGHT_EDIT, m_EditDivPipeLenght);
	DDX_Control(pDX, IDC_DIV_BEGIN_NAME_EDIT, m_EditDivBeginName);
	DDX_Control(pDX, IDC_DIV_END_NAME_EDIT, m_EditDivEndName);
}


BEGIN_MESSAGE_MAP(CDivisionEdit, CDialog)
	ON_BN_CLICKED(IDOK, &CDivisionEdit::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDivisionEdit::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_DIV_FILE_NAME_EDIT, &CDivisionEdit::OnEnChangeDivFileNameEdit)
	ON_EN_CHANGE(IDC_DIV_NAME_EDIT, &CDivisionEdit::OnEnChangeDivNameEdit)
	ON_CBN_SELCHANGE(IDC_DIV_PIPE_CMBX, &CDivisionEdit::OnCbnSelchangeDivPipeCmbx)
	ON_CBN_SELCHANGE(IDC_DIV_PROD_CMBX, &CDivisionEdit::OnCbnSelchangeDivProdCmbx)
	ON_EN_CHANGE(IDC_DIV_PARAM_EDIT, &CDivisionEdit::OnEnChangeDivParamEdit)
	//ON_EN_CHANGE(IDC_DIV_WATCH_EDIT, &CDivisionEdit::OnEnChangeDivWatchEdit)
	ON_CBN_SELCHANGE(IDC_DIV_WATCH_CMBX, &CDivisionEdit::OnCbnSelchangeDivWatchCmbx)
	ON_EN_CHANGE(IDC_DIV_PIPE_LENGHT_EDIT, &CDivisionEdit::OnEnChangeDivPipeLenghtEdit)
	ON_EN_CHANGE(IDC_DIV_BEGIN_NAME_EDIT, &CDivisionEdit::OnEnChangeDivBeginNameEdit)
	ON_EN_CHANGE(IDC_DIV_END_NAME_EDIT, &CDivisionEdit::OnEnChangeDivEndNameEdit)
	ON_EN_CHANGE(IDC_DIV_WAVE_EDIT, &CDivisionEdit::OnEnChangeDivWaveEdit)
	ON_EN_CHANGE(IDC_DIV_TIMEDETECT_EDIT, &CDivisionEdit::OnEnChangeDivTimedetectEdit)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_DIV_DETECTORS_LIST, &CDivisionEdit::OnLvnItemchangedDivDetectorsList)
	ON_BN_CLICKED(IDC_DIV_DET_ADD_ALL_BTN, &CDivisionEdit::OnBnClickedDivDetAddAllBtn)
	ON_BN_CLICKED(IDC_DIV_DET_ADD_BTN, &CDivisionEdit::OnBnClickedDivDetAddBtn)
	ON_BN_CLICKED(IDC_DIV_DET_DELL_BTN, &CDivisionEdit::OnBnClickedDivDetDellBtn)
	ON_BN_CLICKED(IDC_DIV_DET_CHANGE_BTN, &CDivisionEdit::OnBnClickedDivDetChangeBtn)
	ON_BN_CLICKED(IDC_DIV_DET_LOOK_BTN, &CDivisionEdit::OnBnClickedDivDetLookBtn)
	ON_MESSAGE(WM_DETECTOR_EDIT_SAVE, &CDivisionEdit::OnDetectorEditSave)
	ON_MESSAGE(WM_DETECTOR_EDIT_EXIT, &CDivisionEdit::OnDetectorEditExit)
	ON_EN_SETFOCUS(IDC_DIV_NAME_EDIT, &CDivisionEdit::OnEnSetfocusDivNameEdit)
	ON_EN_KILLFOCUS(IDC_DIV_NAME_EDIT, &CDivisionEdit::OnEnKillfocusDivNameEdit)
	ON_EN_SETFOCUS(IDC_DIV_FILE_NAME_EDIT, &CDivisionEdit::OnEnSetfocusDivFileNameEdit)
	ON_EN_KILLFOCUS(IDC_DIV_FILE_NAME_EDIT, &CDivisionEdit::OnEnKillfocusDivFileNameEdit)
	ON_BN_CLICKED(IDC_DIV_SAVE_BTN, &CDivisionEdit::OnBnClickedDivSaveBtn)
	ON_WM_SIZE()
END_MESSAGE_MAP()


void CDivisionEdit::SetPipesToCmBx()
{
	std::vector<CString> TitleDetector;
	TitleDetector = theApp.AllDetectors[DET_HEAD]; // ��������� ������ ������� � "������", ����� ��� �� �������� ��� ����������
	theApp.AllDetectors.erase(theApp.AllDetectors.begin() + DET_HEAD); // ������� �� ������� ������ ������� � ������� ����� ���� � ��������

	// �������� ������ ��������������� ����� ����, ��� ������� ����� ���� ��������
	UINT nDetNum( theApp.AllDetectors.size() );
	std::vector<CString> v_AllPipes;
	UINT nPipeNum(0);

	for(UINT i(0); i<nDetNum; i++)
	{	//DET_PIPE_SHNAME //DET_PIPE_ID	
		if(v_AllPipes.size() == 0)	v_AllPipes.push_back( theApp.AllDetectors[i][DET_PIPE_SHNAME] );
		else
		{
			bool bPipeFound(false);
			nPipeNum = v_AllPipes.size();
			for(UINT j(0); j<nPipeNum; j++)
			{
				if(v_AllPipes[j] == theApp.AllDetectors[i][DET_PIPE_SHNAME])
				{bPipeFound=true;}
			}
			if( !bPipeFound )
			{v_AllPipes.push_back(theApp.AllDetectors[i][DET_PIPE_SHNAME]);}
		}
	}
	nPipeNum = v_AllPipes.size();

	std::sort(v_AllPipes.begin(), v_AllPipes.end());


	// ����� ��������� ���� ����, ������� ��� ���� ��� ��������� �� ������ ����� ��������
	std::vector<CString> v_AllPipesProducts; // [0] - ����1,����2,����3 [1] - ����1,����2,����3
	for(UINT i(0); i<nPipeNum; i++)
	{	//DET_PIPE_SHNAME //DET_PIPE_ID	// DET_PROD_TYPE // DET_PROD_ID // DET_PROD_VIEW
		std::vector<CString> v_AllProducts;	 // [0] - ����1 [1] - ����2

		for(UINT j(0); j<nDetNum; j++)
		{	//DET_PIPE_SHNAME //DET_PIPE_ID	
			if(v_AllPipes[i] == theApp.AllDetectors[j][DET_PIPE_SHNAME])
			{
				if(v_AllProducts.size() == 0)	v_AllProducts.push_back( theApp.AllDetectors[j][DET_PROD_TYPE] );
				else
				{
					bool bProdFound(false);
					UINT nProdNum = v_AllProducts.size();
					for(UINT k(0); k<nProdNum; k++)
					{
						if(v_AllProducts[k] == theApp.AllDetectors[j][DET_PROD_TYPE])
						{bProdFound=true;}
					}
					if( !bProdFound )
					{v_AllProducts.push_back(theApp.AllDetectors[j][DET_PROD_TYPE]);}
				}
			}
		}
		//std::sort(v_AllProducts.begin(), v_AllProducts.end());

		// ������� �� ����� ����� ��� � �������� ��������� ����� ������� ��
		CString sOnePipeProductList("");
		UINT nProdNum = v_AllProducts.size();
		for(UINT j(0); j<nProdNum; j++)
		{	//DET_PIPE_SHNAME //DET_PIPE_ID	// DET_PROD_TYPE // DET_PROD_ID // DET_PROD_VIEW
			sOnePipeProductList += v_AllProducts[j];
			switch (nProdNum)
			{
			case 1:	break;
			default:
				if( nProdNum>j && j!=(nProdNum-1))
				{sOnePipeProductList += _T(", ");}
				break;
			}
		}
		v_AllPipesProducts.push_back(sOnePipeProductList);
	}


	theApp.AllDetectors.insert(theApp.AllDetectors.begin(), TitleDetector); // ��������� ����� ������� � ������
	TitleDetector.clear();


	// 2 // ����� ��������� ���� ���������� �������, ���� ��� ��������� ����������� �� � ������� �� �������� ��������
	//std::sort(v_AllPipes.begin(), v_AllPipes.end());

	// �������� ���������� ������ ���� � ���������
	m_CmBxDivPipe.Clear();

	// 1 // *���������� �� ���������� ����� ����
	switch(nPipeNum)
	{
	case 0:
		m_CmBxDivPipe.AddString(_T("��� ��������� ����"));
		m_CmBxDivPipe.SetCurSel(0);
		m_CmBxDivPipe.EnableWindow(FALSE);
		break;
	case 1:
		m_CmBxDivPipe.AddString(v_AllPipes[v_AllPipes.size()-1]);
		m_CmBxDivPipe.SetCurSel(0);
		m_CmBxDivPipe.EnableWindow(FALSE);

		// ����� �� ������� ��������������� ������ ���������
		//SetProdsToCmBx();
		break;
	default:
		m_CmBxDivPipe.EnableWindow(TRUE);
		for(UINT i(0); i<nPipeNum; i++)
		{
			m_CmBxDivPipe.AddString(v_AllPipes[i]);
			m_CmBxDivPipe.SetItemTip(i, v_AllPipesProducts[i]);
		}
		break;
	}

	/*// 1 // *���������� �� ���������� ����� ����
	if(nPipeNum>0)
	{
		if(nPipeNum==1)
		{
			m_CmBxDivPipe.AddString(v_AllPipes[v_AllPipes.size()-1]);
			m_CmBxDivPipe.SetCurSel(0);
			m_CmBxDivPipe.EnableWindow(FALSE);
		}
		else
		{
		for(UINT j(0); j<nPipeNum; j++)
			m_CmBxDivPipe.AddString(v_AllPipes[j]);
		}
	}
	else
	{
		m_CmBxDivPipe.AddString(_T("��� ��������� ����"));
		m_CmBxDivPipe.SetCurSel(0);
		m_CmBxDivPipe.EnableWindow(FALSE);
	}
	*/
}


void CDivisionEdit::SetProdsToCmBx()
{
	// ������� ��������� �����
	//theApp.CurDivPipe

	std::vector<CString> TitleDetector;
	TitleDetector = theApp.AllDetectors[DET_HEAD]; // ��������� ������ ������� � "������", ����� ��� �� �������� ��� ����������
	theApp.AllDetectors.erase(theApp.AllDetectors.begin() + DET_HEAD); // ������� �� ������� ������ ������� � ������� ����� ���� � ��������

	// ����� ������ �����, ������� ��� ����� ��� ��������� �� ��� ��������
	UINT nDetNum( theApp.AllDetectors.size() );

	// ������� �� ����� ����� ��� � �������� �������� �� � ���������
	//DET_PIPE_SHNAME //DET_PIPE_ID	// DET_PROD_TYPE // DET_PROD_ID // DET_PROD_VIEW
	std::vector<CString> v_AllProducts;	 // [0] - ����1 [1] - ����2

	for(UINT j(0); j<nDetNum; j++)
	{	//DET_PIPE_SHNAME //DET_PIPE_ID	
		if(theApp.CurDivPipe == theApp.AllDetectors[j][DET_PIPE_SHNAME])
		{
			if(v_AllProducts.size() == 0)	v_AllProducts.push_back( theApp.AllDetectors[j][DET_PROD_TYPE] );
			else
			{
				bool bProdFound(false);
				UINT nProdNum = v_AllProducts.size();
				for(UINT k(0); k<nProdNum; k++)
				{
					if(v_AllProducts[k] == theApp.AllDetectors[j][DET_PROD_TYPE])
					{bProdFound=true;}
				}
				if( !bProdFound )
				{v_AllProducts.push_back(theApp.AllDetectors[j][DET_PROD_TYPE]);}
			}
		}
	}
	std::sort(v_AllProducts.begin(), v_AllProducts.end());


	theApp.AllDetectors.insert(theApp.AllDetectors.begin(), TitleDetector); // ��������� ����� ������� � ������
	TitleDetector.clear();

	// 2 // ����� ��������� ���� ���������� �������, ���� ��� ��������� ����������� �� � ������� �� �������� ��������
	//std::sort(v_AllPipes.begin(), v_AllPipes.end());

	// �������� ���������� ������ ���� � ���������
	m_CmBxDivProd.Clear();

	// 1 // *���������� �� ���������� ����� ����
	UINT nProdNum(0);
	nProdNum = v_AllProducts.size();
	switch(nProdNum)
	{
	case 0:
		m_CmBxDivProd.AddString(_T("��� ��������� ���������"));
		m_CmBxDivProd.SetCurSel(0);
		m_CmBxDivProd.EnableWindow(FALSE);
		break;
	case 1:
		m_CmBxDivProd.AddString(v_AllProducts[v_AllProducts.size()-1]);
		m_CmBxDivProd.SetCurSel(0);
		m_CmBxDivProd.EnableWindow(FALSE);

		OnCbnSelchangeDivProdCmbx();
		break;
	default:
		m_CmBxDivProd.EnableWindow(TRUE);
		for(UINT i(0); i<nProdNum; i++)
		{m_CmBxDivProd.AddString(v_AllProducts[i]);}
		break;
	}
}


// ����������� ��������� CDivisionEdit

BOOL CDivisionEdit::OnInitDialog()
{
	CDialog::OnInitDialog();

	//HWND HwndDivEditDlg=NULL;
	//::GetDlgItem(HwndDivEditDlg, IDD_EDIT_DIVISION_DLG);
	//HWND* HwndDivEditDlg=NULL;
	//GetDlgItem(IDD_EDIT_DIVISION_DLG, HwndDivEditDlg);
	//theApp.hWnd_DivisionEditDlg = HwndDivEditDlg;

	m_BtnDivOK.ShowWindow(FALSE);
////	m_EditDivWatch.ShowWindow(FALSE);

	CString EmptyStr("");

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

		//CStringA p_DetFullPath(DetectorsFullPath);

		_bstr_t bstrOutput("");
		bool validXml=false;
		HRESULT hr = CoInitialize(NULL);
		if(SUCCEEDED(hr))
		{
			try{ bstrOutput = theApp.validateDivFile(DivisionFilePathBstr, validXml); }
			catch(_com_error &e)
			{bstrOutput = theApp.dump_com_error(e);}
		}

		if(validXml) // ������, ����� ���� "��������" � .SOU ���� ������� ����� ���������
		{
			readDivisionFile(DivisionFilePath);
		}
		else //if(!validXml)
		{
			if(bstrOutput.length()>0)
			MessageBox(bstrOutput, L"������ � ����� ��� ��� ��������", MB_OK);

			return FALSE; // ������ ������������ � ������ �� ������
		}
	}



	// ����� ������� ������� � ��������� ��� ������� ������� ��������� ��� ���������� � ����� �������:
	CRect rect;
	m_ListDiv_Det.GetClientRect(rect);
	m_ListDiv_Det.DeleteAllItems();
	//m_ListDiv_Det.InsertColumn(0, _T("�"), LVCFMT_LEFT, 30);
	//m_ListDiv_Det.InsertColumn(1, _T("�������� �������"), LVCFMT_LEFT, rect.Width() ); // - 230);
	//m_ListDiv_Det.InsertColumn(0, _T("��� ������� � �������"), LVCFMT_LEFT, 150);
	//m_ListDiv_Det.InsertColumn(0, _T("� ����� ���������"), LVCFMT_LEFT, 40);
	//m_ListDiv_Det.InsertColumn(1, _T("�������� ������� �� �������"), LVCFMT_LEFT, rect.Width() ); // - 230);

	(void)m_ListDiv_Det.SetExtendedStyle( LVS_EX_FULLROWSELECT );
	m_ListDiv_Det.SetHeadings( _T("� ����� ���������,		60;\
									�������� ������� �� �������,") + LintToCStr(rect.Width())
							 );
	m_ListDiv_Det.LoadColumnInfo();

//	m_CmBxDivPipe

	// � ������������� �� ���� ����� ������ ������, ��� ����� ����� ���������
	// ���������� ������ 3-�� ���������� ("�������", �������� �� XML-����� �� ������ "������������� ��������")
//	m_CmBxDivProd.AddString(_T("������"));
//	m_CmBxDivProd.AddString(_T("������"));	// ���.������� (�������������)
//	m_CmBxDivProd.AddString(_T("�������")); // ��.������� (�������������)		// theApp.DivDetectors[i][1] // theApp.AllDetectors[v][5]
	//m_CmBxDivProd.AddString(_T("��.�������")); // ��.������� (�������������)	// theApp.DivDetectors[i][1] // theApp.AllDetectors[v][6]

////	m_CmBxDivWatch.Clear();							// �������	// ������������� // 1 = ��, 0 = ��� (�� ��������� "��")
////	m_CmBxDivWatch.AddString(_T("��"));
////	m_CmBxDivWatch.AddString(_T("���"));

	// ���� �������������� ���������:
	// ��� ������� ��� "��������", ������ � �� ��������� ����� = "��������"
	CString Preassure("��������");

	CString Copy_Str(" - �����");
	UINT NumOfDet(0), NumOfDetParams(0);
	CString DivisionPipe("");
	CString DivisionProd("");


	switch(theApp.ChangeDivBtnClicked)
	{
	case theApp.DIV_BTN_ADD: // ������ ������ "�������� �������"
		// ����� ������ ��� �� ������ ������� ��� ������� ������ ��� �������:
		if(theApp.FullDivision.size() == 0)
		{
			std::vector<CString> OnlyDivision( DIV_ELEMENS_NUM, _T("") );
			theApp.FullDivision.push_back(OnlyDivision);
		}

		// �������� � ��������� ��� ��������� ������������:
		SetPipesToCmBx();

		// �������� ��� �������� ��� �������:
		//m_EditDivName.SetWindowText(EmptyStr);			// ���

		// � ������ � ������� "�������� �������" ������ ���� ��������, ��� �������� ��� ������� �� ������ ������� � ���������� ������� theApp.DivDetectors
		// ���������� �� ���, � � ������� "������� �� ���������"

		//m_CmBxDivPipe.EnableWindow(TRUE);				// �����	// ������������� !!! ������ � ������ ����������
		//m_CmBxDivProd.EnableWindow(FALSE);			// �������	// ������������� !!! ����� ����� �����		//m_EditDivParam.SetWindowText(Preassure);		// �������� // �� �������� ������������� = "��������" ������
		m_EditDivWave.SetWindowText(EmptyStr);			// �����	// �������������
		m_EditDivTimeDetect.SetWindowText(EmptyStr);	// �����_�����������	// �������������

		// � ������ � �������� ������� ������������ ������ ��� ��������, ����� �������� 
		// �� ��� ��� ���� ������������ �� ������� ������� ������� !!!!!!
		m_EditDivFileName.EnableWindow(FALSE);
		m_EditDivName.EnableWindow(FALSE);
////		m_EditDivParam.EnableWindow(FALSE);
		//m_CmBxDivWatch.EnableWindow(FALSE);
		m_EditDivWave.EnableWindow(FALSE);
		m_EditDivTimeDetect.EnableWindow(FALSE);

		m_ListDiv_Det.EnableWindow(FALSE);
		m_BtnDiv_DetAddAll.EnableWindow(FALSE);
		m_BtnDiv_DetAdd.EnableWindow(FALSE);
		m_BtnDiv_DetDel.EnableWindow(FALSE);
		m_BtnDiv_DetChange.EnableWindow(FALSE);
		m_BtnDiv_DetLook.EnableWindow(FALSE);
		m_BtnDivSave.EnableWindow(FALSE);

		break;

	case theApp.DIV_BTN_COPY: //������ ������ "���������� �������"
		// �������� ��� �������� ��� �������:

		CheckFileNameCopyString(theApp.DivisionFileName, theApp.DivNextFileName);
		m_EditDivFileName.SetWindowText(theApp.DivisionFileName);

		CheckFileNameCopyString(theApp.FullDivision[DIV_DIV_HEAD][DIV_DIV_NAME], theApp.DivNextFileName);
		m_EditDivName.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_DIV_NAME]);

		DivisionPipe = theApp.FullDivision[DIV_DIV_HEAD][DIV_PIPE_NAME];
		theApp.CurDivPipe = DivisionPipe;
		m_CmBxDivPipe.Clear();
		m_CmBxDivPipe.AddString( DivisionPipe );
		m_CmBxDivPipe.SetCurSel(0);
		m_CmBxDivPipe.EnableWindow(FALSE);

		DivisionProd = theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_NAME];
		theApp.CurDivProd = DivisionProd;
		m_CmBxDivProd.Clear();
		m_CmBxDivProd.AddString( DivisionProd );
		m_CmBxDivProd.SetCurSel(0);
		m_CmBxDivProd.EnableWindow(FALSE);

#if 0	// ����� ��� ���������� � ���������� ������ ��� "�������":
		for(long k=0; k<PROD_NUM; k++)
		{
			CString LBProduct;
			m_CmBxDivProd.GetLBText(k,LBProduct);
			if( LBProduct == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID]) // ���� � Comboboxe ����� "��.�������"
			{m_CmBxDivProd.SetCurSel(k); break;}
		}
		if(theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID] == _T("��.�������")) // ���� � theApp.FullDivision[DIV_DIV_HEAD][1] �� ������� "�������" ����� "��.�������"
		{m_CmBxDivProd.SetCurSel(2);}	// ����������� � ��������� "�������"
		if(theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID] == _T("���.�������")) // ���� � theApp.FullDivision[DIV_DIV_HEAD][1] �� ������� "�������" ����� "���.�������"
		{m_CmBxDivProd.SetCurSel(1);}	// ����������� � ��������� "������"
#endif

		// ��� �� �� �������� �� ������� �������� � ������ ��������, ������� ����� �������������� �������������� �� ������� ��������
		theApp.DivDetectors.clear();
		for(UINT v=0; v<theApp.AllDetectors.size(); v++)
		{
			//if(theApp.AllDetectors[v][6] == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID]) // ���� �������� � OnInitDialog "��.�������"
			//if(theApp.AllDetectors[v][5] == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID]) // ���� �������� � OnInitDialog "�������"
			// ������������� �������, ��� ��� �� ����� ���� �� ������� ������ �� ����, ��� �� ����� ���� � theApp.FullDivision[DIV_DIV_HEAD][1], � ��� ������ ��������� ������ "��.�������"
			// ��������� ��� ����� �� �����+������� � ��������� ��������������� � theApp.DivDetectors
			if( 
				//(theApp.AllDetectors[v][DET_PROD_ID] == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID]) || 
				//(theApp.AllDetectors[v][DET_PROD_TYPE] == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID])
				(theApp.AllDetectors[v][DET_PIPE_SHNAME] == theApp.FullDivision[DIV_DIV_HEAD][DIV_PIPE_NAME]) &&
				(theApp.AllDetectors[v][DET_PROD_TYPE]	 == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_NAME])
			  ) 
			{theApp.DivDetectors.push_back(theApp.AllDetectors[v]);}
			//theApp.DIVDET_NUM = theApp.DivDetectors.size();
		}
		//m_CmBxDivProd	// theApp.AllDetectors[0][1]
////		m_EditDivParam.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_PARAMETR]); // �� �������� ������������� = "��������" ������
		// ����� ��� ���������� � ���������� ������ ��� "�������":
////		if( theApp.FullDivision[DIV_DIV_HEAD][DIV_WATCH] == _T("1"))
////		{m_CmBxDivWatch.SetCurSel(0);}		// ���� "1" ��������� "��"
////		if( theApp.FullDivision[DIV_DIV_HEAD][DIV_WATCH] == _T("0"))
////		{m_CmBxDivWatch.SetCurSel(1);}		// ���� "0" ��������� "���"
		m_EditDivPipeLenght.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_PIPE_LENGTH]);
		m_EditDivBeginName.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_BEGIN_NAME]);
		m_EditDivEndName.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_END_NAME]);
		m_EditDivWave.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_WAVE]);
		m_EditDivTimeDetect.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_DTCT_TIME]);


		// ����� �������� ������� � ��������� ��� ������� �������
		NumOfDet=0;
		NumOfDetParams=0;
		if(theApp.FullDivision.size()>1)
		{ 
			UINT nTestDivSortDetectorsNum = theApp.DivDetectors.size();		// ����� ��������, ���������� ��� ������� �������
			NumOfDet = theApp.FullDivision.size() - 1;		// NumOfDet = ����� �������� (�������� ������ ������ � ����������� �������) 
			NumOfDetParams = theApp.FullDivision[DIV_DET_HEAD].size();	// NumOfDetParams = ����� ���������� ��������
	
			for(UINT i(DIV_DET_HEAD), j(DET_HEAD); j < NumOfDet; i++, j++)
			{	
				/*			
				m_ListDiv_Det.InsertItem(j, theApp.FullDivision[i][DIV_DET_NUMBER]); // � 1-�� ������� ��� ������� � ������� // ����� �������
				// ��� ��� ��� ����� ������:
				m_ListDiv_Det.SetItemText(j, 0, theApp.FullDivision[i][DIV_DET_NUMBER]); // � 1-�� ������� ��� ������� � ������� // ����� �������
				m_ListDiv_Det.SetItemText(j, 1, theApp.FullDivision[i][DIV_DET_NAME]); // �� 2-�� ������ �������� ������� �� ������� // �������� �������
				*/

				(void)m_ListDiv_Det.AddItem(
											theApp.FullDivision[i][DIV_DET_NUMBER],
											theApp.FullDivision[i][DIV_DET_NAME]
										 );
			}
			m_ListDiv_Det.SetExtendedStyle( m_ListDiv_Det.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

			// ����������� ��� ������ ��� �������������� ��������, ���� ���� ���� �� ����
			m_EditDivFileName.EnableWindow(TRUE);

			m_ListDiv_Det.EnableWindow(TRUE);
			if(NumOfDet >= nTestDivSortDetectorsNum)
			{
				m_BtnDiv_DetAddAll.EnableWindow(FALSE);
				m_BtnDiv_DetAdd.EnableWindow(FALSE);
			}
			else
			{
				m_BtnDiv_DetAddAll.EnableWindow(TRUE);
				m_BtnDiv_DetAdd.EnableWindow(TRUE);
			}
			m_BtnDiv_DetDel.EnableWindow(TRUE);
			m_BtnDiv_DetChange.EnableWindow(TRUE);
			m_BtnDiv_DetLook.EnableWindow(TRUE);
		}
		else
		{
			// ���� �������� ��� ����������, �� ��������� ������ "�������� ������" ��������� ������ ���������
			m_EditDivFileName.EnableWindow(TRUE);

			m_ListDiv_Det.EnableWindow(FALSE);
			m_BtnDiv_DetAddAll.EnableWindow(TRUE);
			m_BtnDiv_DetAdd.EnableWindow(TRUE);
			m_BtnDiv_DetDel.EnableWindow(FALSE);
			m_BtnDiv_DetChange.EnableWindow(FALSE);
			m_BtnDiv_DetLook.EnableWindow(FALSE);
		}

		break;

	case theApp.DIV_BTN_CHANGE: //������ ������ "�������� �������"
		// �������� ��� �������� ��� �������:
		sOriginalDivName = theApp.FullDivision[DIV_DIV_HEAD][DIV_DIV_NAME];

		m_EditDivFileName.SetWindowText(theApp.DivisionFileName);

		m_EditDivName.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_DIV_NAME]);

		DivisionPipe = theApp.FullDivision[DIV_DIV_HEAD][DIV_PIPE_NAME];
		theApp.CurDivPipe = DivisionPipe;
		m_CmBxDivPipe.Clear();
		m_CmBxDivPipe.AddString( DivisionPipe );
		m_CmBxDivPipe.SetCurSel(0);
		m_CmBxDivPipe.EnableWindow(FALSE);

		DivisionProd = theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_NAME];
		theApp.CurDivProd = DivisionProd;
		m_CmBxDivProd.Clear();
		m_CmBxDivProd.AddString( DivisionProd );
		m_CmBxDivProd.SetCurSel(0);
		m_CmBxDivProd.EnableWindow(FALSE);

#if 0	// ����� ��� ���������� � ���������� ������ ��� "�������":
		for(long k=0; k<PROD_NUM; k++)
		{
			CString LBProduct;
			m_CmBxDivProd.GetLBText(k,LBProduct);
			if( LBProduct == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID]) // ���� � Comboboxe ����� "��.�������"
			{m_CmBxDivProd.SetCurSel(k); break;}
		}
		if(theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID] == _T("��.�������")) // ���� � theApp.FullDivision[DIV_DIV_HEAD][1] �� ������� "�������" ����� "��.�������"
		{m_CmBxDivProd.SetCurSel(2);}	// ����������� � ��������� "�������"
		if(theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID] == _T("���.�������")) // ���� � theApp.FullDivision[DIV_DIV_HEAD][1] �� ������� "�������" ����� "���.�������"
		{m_CmBxDivProd.SetCurSel(1);}	// ����������� � ��������� "������"
#endif

		// ��� �� �� �������� �� ������� �������� � ������ ��������, ������� ����� �������������� �������������� �� ������� ��������
		theApp.DivDetectors.clear();
		for(long v=0; v<theApp.AllDetectors.size(); v++)
		{
			//if(theApp.AllDetectors[v][6] == theApp.FullDivision[DIV_DIV_HEAD][1]) // ���� �������� � OnInitDialog "��.�������"
			//if(theApp.AllDetectors[v][5] == theApp.FullDivision[DIV_DIV_HEAD][1]) // ���� �������� � OnInitDialog "�������"
			// ������������� �������, ��� ��� �� ����� ���� �� ������� ������ �� ����, ��� �� ����� ���� � theApp.FullDivision[DIV_DIV_HEAD][1], � ��� ������ ��������� ������ "��.�������"
			// ��������� ��� ����� �� �����+������� � ��������� ��������������� � theApp.DivDetectors
			if( 
				//(theApp.AllDetectors[v][DET_PROD_ID] == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID]) || 
				//(theApp.AllDetectors[v][DET_PROD_TYPE] == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID])
				(theApp.AllDetectors[v][DET_PIPE_SHNAME] == theApp.FullDivision[DIV_DIV_HEAD][DIV_PIPE_NAME]) &&
				(theApp.AllDetectors[v][DET_PROD_TYPE]	 == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_NAME])
			  ) 
			{theApp.DivDetectors.push_back(theApp.AllDetectors[v]);}
			//theApp.DIVDET_NUM = theApp.DivDetectors.size();
		}
		//m_CmBxDivProd	// theApp.AllDetectors[0][1]
		////m_EditDivParam.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_PARAMETR]); // �� �������� ������������� = "��������" ������
		// ����� ��� ���������� � ���������� ������ ��� "�������":
		////if( theApp.FullDivision[DIV_DIV_HEAD][DIV_WATCH] == _T("1"))
		////{m_CmBxDivWatch.SetCurSel(0);}		// ���� "1" ��������� "��"
		////if( theApp.FullDivision[DIV_DIV_HEAD][DIV_WATCH] == _T("0"))
		////{m_CmBxDivWatch.SetCurSel(1);}		// ���� "0" ��������� "���"
		m_EditDivPipeLenght.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_PIPE_LENGTH]);
		m_EditDivBeginName.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_BEGIN_NAME]);
		m_EditDivEndName.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_END_NAME]);
		m_EditDivWave.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_WAVE]);
		m_EditDivTimeDetect.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_DTCT_TIME]);


		////////////////////////////////////////////////////////////////////////
		// �� ������ ����� ���������� �������������� ���������� �� �����+�������



		// ����� �������� ������� � ��������� ��� ������� �������
		NumOfDet=0; // ����� �������� ������������� �� ������� (�������� ������ ������ � ����������� �������)
		NumOfDetParams=0;
		if(theApp.FullDivision.size()>1)
		{ 
			UINT nTestDivSortDetectorsNum = theApp.DivDetectors.size();		// ����� ��������, ���������� ��� ������� �������
			NumOfDet = theApp.FullDivision.size() - 1;		// NumOfDet = ����� �������� (�������� ������ ������ � ����������� �������) 
			NumOfDetParams = theApp.FullDivision[DIV_DET_HEAD].size();	// NumOfDetParams = ����� ���������� ��������
	
			for(UINT i(DIV_DET_HEAD), j(DET_HEAD); j < NumOfDet; i++, j++)
			{
				/*
				m_ListDiv_Det.InsertItem(j, theApp.FullDivision[i][DIV_DET_NUMBER]); // � 1-�� ������� ��� ������� � ������� // ����� �������
				// ��� ��� ��� ����� ������:
				m_ListDiv_Det.SetItemText(j, 0, theApp.FullDivision[i][DIV_DET_NUMBER]); // � 1-�� ������� ��� ������� � ������� // ����� �������
				m_ListDiv_Det.SetItemText(j, 1, theApp.FullDivision[i][DIV_DET_NAME]); // �� 2-�� ������ �������� ������� �� ������� // �������� �������
				*/

				(void)m_ListDiv_Det.AddItem(
											theApp.FullDivision[i][DIV_DET_NUMBER],
											theApp.FullDivision[i][DIV_DET_NAME]
										 );
			}
			m_ListDiv_Det.SetExtendedStyle( m_ListDiv_Det.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

			// ����������� ��� ������ ��� �������������� ��������, ���� ���� ���� �� ����
			m_EditDivFileName.EnableWindow(FALSE);

			m_ListDiv_Det.EnableWindow(TRUE);
			if(NumOfDet >= nTestDivSortDetectorsNum)
			{
				m_BtnDiv_DetAddAll.EnableWindow(FALSE);
				m_BtnDiv_DetAdd.EnableWindow(FALSE);
			}
			else
			{
				m_BtnDiv_DetAddAll.EnableWindow(TRUE);
				m_BtnDiv_DetAdd.EnableWindow(TRUE);
			}
			m_BtnDiv_DetDel.EnableWindow(TRUE);
			m_BtnDiv_DetChange.EnableWindow(TRUE);
			m_BtnDiv_DetLook.EnableWindow(TRUE);

		}
		else
		{
			// ���� �������� ��� ����������, �� ��������� ������ "�������� ������" ��������� ������ ���������
			m_EditDivFileName.EnableWindow(FALSE);

			m_ListDiv_Det.EnableWindow(FALSE);
			m_BtnDiv_DetAddAll.EnableWindow(TRUE);
			m_BtnDiv_DetAdd.EnableWindow(TRUE);
			m_BtnDiv_DetDel.EnableWindow(FALSE);
			m_BtnDiv_DetChange.EnableWindow(FALSE);
			m_BtnDiv_DetLook.EnableWindow(FALSE);
		}

		break;

	case theApp.DIV_BTN_LOOK: // ������ ������ "�������� �������"
		// �������� ��� �������� ��� �������:
		m_EditDivFileName.SetWindowText(theApp.DivisionFileName);

		m_EditDivName.SetWindowText( theApp.FullDivision[DIV_DIV_HEAD][DIV_DIV_NAME] );

		m_CmBxDivPipe.Clear();
		m_CmBxDivPipe.AddString( theApp.FullDivision[DIV_DIV_HEAD][DIV_PIPE_NAME] );
		m_CmBxDivPipe.SetCurSel(0);
		m_CmBxDivPipe.EnableWindow(FALSE);

		m_CmBxDivProd.Clear();
		m_CmBxDivProd.AddString( theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_NAME] );
		m_CmBxDivProd.SetCurSel(0);
		m_CmBxDivProd.EnableWindow(FALSE);

#if 0	//����� ��� ���������� � ���������� ������:
		for(long k=0; k<PROD_NUM; k++)
		{
			CString LBProduct;
			m_CmBxDivProd.GetLBText(k,LBProduct);
			if( LBProduct == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID])
			{m_CmBxDivProd.SetCurSel(k); break;}
		}
		if(theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID] == _T("��.�������")) // ���� � theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID] �� ������� "�������" ����� "��.�������"
		{m_CmBxDivProd.SetCurSel(2);}	// ����������� � ��������� "�������"
		if(theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID] == _T("���.�������")) // ���� � theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID] �� ������� "�������" ����� "���.�������"
		{m_CmBxDivProd.SetCurSel(1);}	// ����������� � ��������� "������"
#endif
		// ��� �� �� �������� �� ������� �������� � ������ ��������, ������� ����� �������������� �������������� �� ������� ��������
		theApp.DivDetectors.clear();
		for(long v=0; v<theApp.AllDetectors.size(); v++)
		{
			//if(theApp.AllDetectors[v][6] == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID]) // ���� �������� � OnInitDialog "��.�������"
			//if(theApp.AllDetectors[v][5] == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID]) // ���� �������� � OnInitDialog "�������"
			// ������������� �������, ��� ��� �� ����� ���� �� ������� ������ �� ����, ��� �� ����� ���� � theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID], � ��� ������ ��������� ������ "��.�������"
			// ��������� ��� ����� �� �����+������� � ��������� ��������������� � theApp.DivDetectors
			if( 
				//(theApp.AllDetectors[v][DET_PROD_ID] == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID]) || 
				//(theApp.AllDetectors[v][DET_PROD_TYPE] == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID])
				(theApp.AllDetectors[v][DET_PIPE_SHNAME] == theApp.FullDivision[DIV_DIV_HEAD][DIV_PIPE_NAME]) &&
				(theApp.AllDetectors[v][DET_PROD_TYPE]	 == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_NAME])
			  ) 
			{theApp.DivDetectors.push_back(theApp.AllDetectors[v]);}
			//theApp.DIVDET_NUM = theApp.DivDetectors.size();
		}
		//m_CmBxDivProd	// theApp.AllDetectors[0][1]
		////m_EditDivParam.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_PARAMETR]); // �� �������� ������������� = "��������" ������
		// ����� ��� ���������� � ���������� ������ ��� "�������":
		////if( theApp.FullDivision[DIV_DIV_HEAD][DIV_WATCH] == _T("1"))
		////{m_CmBxDivWatch.SetCurSel(0);}		// ���� "1" ��������� "��"
		////if( theApp.FullDivision[DIV_DIV_HEAD][DIV_WATCH] == _T("0"))
		////{m_CmBxDivWatch.SetCurSel(1);}		// ���� "0" ��������� "���"
		m_EditDivPipeLenght.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_PIPE_LENGTH]);
		m_EditDivBeginName.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_BEGIN_NAME]);
		m_EditDivEndName.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_END_NAME]);
		m_EditDivWave.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_WAVE]);
		m_EditDivTimeDetect.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_DTCT_TIME]);


		// ����� �������� ������� � ��������� ��� ������� �������
		NumOfDet=0;
		NumOfDetParams=0;
		if(theApp.FullDivision.size()>1)
		{ 
			NumOfDet = theApp.FullDivision.size() - 1;		// NumOfDet = ����� �������� (�������� ������ ������ � ����������� �������) 
			NumOfDetParams = theApp.FullDivision[DIV_DET_HEAD].size();	// NumOfDetParams = ����� ���������� ��������
		}
	
		for(UINT i(DIV_DET_HEAD), j(DET_HEAD); j < NumOfDet; i++, j++)
		{
			/*
			m_ListDiv_Det.InsertItem(j, theApp.FullDivision[i][DIV_DET_NUMBER]); // � 1-�� ������� ��� ������� � ������� // ����� �������
			// ��� ��� ��� ����� ������:
			m_ListDiv_Det.SetItemText(j, 0, theApp.FullDivision[i][DIV_DET_NUMBER]); // � 1-�� ������� ��� ������� � ������� // ����� �������
			m_ListDiv_Det.SetItemText(j, 1, theApp.FullDivision[i][DIV_DET_NAME]); // �� 2-�� ������ �������� ������� �� ������� // �������� �������
			*/

			(void)m_ListDiv_Det.AddItem(
										theApp.FullDivision[i][DIV_DET_NUMBER],
										theApp.FullDivision[i][DIV_DET_NAME]
									 );
		}
		m_ListDiv_Det.SetExtendedStyle( m_ListDiv_Det.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

		// � ������ � ������� "��������" ����������� ��� ��������, ������� ����� ����� �������������
		// ��������� �� �����: 1. �������� 2. ������ �������� 3. ������ "��������" �������
		m_EditDivFileName.EnableWindow(FALSE);
		m_EditDivName.EnableWindow(FALSE);
		//m_CmBxDivProd.EnableWindow(FALSE);
		//m_EditDivParam.EnableWindow(FALSE); // �� �������� ������������� = "��������" ������
		//m_CmBxDivWatch.EnableWindow(FALSE);
		m_EditDivWave.EnableWindow(FALSE);
		m_EditDivTimeDetect.EnableWindow(FALSE);
		m_BtnDivSave.EnableWindow(FALSE);	// ��������� ����� � ������ "���������"

		m_BtnDiv_DetAddAll.EnableWindow(FALSE);
		m_BtnDiv_DetAdd.EnableWindow(FALSE);
		m_BtnDiv_DetDel.EnableWindow(FALSE);
		m_BtnDiv_DetChange.EnableWindow(FALSE);

		if(theApp.FullDivision.size()>1)
		{ 
			// ���� ������� ���� ����������, �� ��������� ������ ������ "�������� �������"
			m_BtnDiv_DetLook.EnableWindow(TRUE);
		}
		else
		{
			// ���� �������� ��� ����������, �� ��������� ��� �� � ������ "�������� �������"
			m_BtnDiv_DetLook.EnableWindow(FALSE);
		}


		break;
	}
	


	// ���������� ������ ������� ������ ��� "����������"
	if(m_ListDiv_Det.GetItemCount() > 0)
	{m_ListDiv_Det.SetItemState(0, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);}


	bFirstDlg=true;


	//CWnd *pWnd = GetDlgItem(IDC_DIV_DETECTORS_LIST);
	//CWnd *pWnd = pDlg->GetDlgItem(IDC_DIV_DETECTORS_LIST);
	//pWnd->GetWindowRect(&OriginalRect);
	this->GetWindowRect(&OriginalRect);
	OrigW = OriginalRect.right - OriginalRect.left;
	OrigH = OriginalRect.bottom - OriginalRect.top;


	return TRUE;  // ������� �������� TRUE, ���� ����� �� ������� �������� ����������
}



//*
void CDivisionEdit::readDivisionFile(CString bstrXMLFile)
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
//		DivAtrs = e.attr(L"����������_������");	OneDetector.push_back(DivAtrs.c_str());
//		DivAtrs = e.attr(L"����������_�����");	OneDetector.push_back(DivAtrs.c_str());

		//��� //�� //������� //���� //�������� //�������� //������_�������� // ������_�����
		theApp.FullDivision.push_back(OneDetector);
		OneDetector.clear();
	}

	int u=0;
}



// ������� �� ������ "ENTER"
void CDivisionEdit::OnBnClickedOk()
{
	//CDialog::OnOK();
}


// ������ "���������" � ��������� �������
// ������ "��������� �������" ��������, �����: 1) ������� ��� ������� 2) ������� ������� �� ������� 3) ���������� "��������" = "��������" 3) �� ������� ���������� ������ 1 ������
void CDivisionEdit::OnBnClickedDivSaveBtn()
{
	// TODO: �������� ���� ��� ����������� �����������
	CString EmptyStr("");


	HRESULT hr = CoInitialize(NULL);
	if(FAILED(hr))
	{
		CString ErrorStr = theApp.GetErrorCSTRString(hr);
		AfxMessageBox(ErrorStr);
		return;
	}


	// 0.1 // ��������� �������� �������� �������
	if(
		  (theApp.ChangeDivBtnClicked == theApp.DIV_BTN_ADD)
		||(theApp.ChangeDivBtnClicked == theApp.DIV_BTN_COPY)
		||(theApp.ChangeDivBtnClicked == theApp.DIV_BTN_CHANGE)
	  )
	{
		CString DivisionName("");
		m_EditDivName.GetWindowText(DivisionName);

		for(long i=0; i<theApp.AllDivisions.size(); i++)
		{
			if(DivisionName == theApp.AllDivisions[i][DIVALL_DIV_NAME])
			{
				if(
					((sOriginalDivName != theApp.FullDivision[DIV_DIV_HEAD][DIV_DIV_NAME]) && (theApp.ChangeDivBtnClicked == theApp.DIV_BTN_CHANGE))
					|| (theApp.ChangeDivBtnClicked != theApp.DIV_BTN_CHANGE)
				  )
				{
				int msgboxID = MessageBox(	_T("������� � ������ \"") + DivisionName + _T("\" ��� ����������!"),
										_T("����� �������� ���������!"),
										MB_ICONWARNING | MB_OK );
				m_EditDivName.SetFocus();
				return;
				}
			}
		}
	}

	int u=0;

	// 0.3 // ��������� �������� �������
	// 0.4 // ��������� �������� ��������
	// 0.5 // ��������� �������� �������
	// 0.6 // ��������� �������� �����
	int curIndex = m_CmBxDivProd.GetCurSel();
	if( curIndex == (-1) )  return;

	CString DivisionWave("");
	m_EditDivWave.GetWindowText(DivisionWave);

	double dWaveSpeed = _tstof(DivisionWave);
	if(  ( ((dWaveSpeed < 0.5) || (dWaveSpeed > 1.5)) )  && curIndex!=(-1) )
	{
		AfxMessageBox( _T("��������: �������� \"�����\" ������ ���� ����� � ��������� ��������� �������� �� 0.5 �� 1.5 (��/�)."), MB_ICONWARNING );
		m_EditDivWave.SetFocus();

		return;
	}
	else
	{
		DivisionWave = DoubleToCStr(dWaveSpeed,5);
		theApp.FullDivision[DIV_DIV_HEAD][DIV_WAVE] = DivisionWave;
	}

	// 0.7 // ����� ��������� �������� ����� �����������
	CString DivisionTimeDetect("");
	m_EditDivTimeDetect.GetWindowText(DivisionTimeDetect);

	double dTimeDetect = _tstof(DivisionTimeDetect);
	if(  ( ((dTimeDetect < 0) || (dTimeDetect > 200)) )  && curIndex!=(-1) )
	{
		AfxMessageBox( _T("��������: �������� \"����� �����������\" ������ ���� ����� � ��������� ��������� �������� �� 0 �� 200 (�)."), MB_ICONWARNING );
		m_EditDivTimeDetect.SetFocus();

		return;
	}
	else
	{
		DivisionTimeDetect = DoubleToCStr(dTimeDetect,0);
		theApp.FullDivision[DIV_DIV_HEAD][DIV_DTCT_TIME] = DivisionTimeDetect;
	}

	// 0.2 // ��������� �������� ��� �����-������� 
	// ��������� ��� �� ����� � ����� �� ������!
	// ������ ��� �������� ������ � ������ ������� �� ������ "��������"
	if( (theApp.ChangeDivBtnClicked == theApp.DIV_BTN_ADD) || (theApp.ChangeDivBtnClicked == theApp.DIV_BTN_COPY) )
	{
		WIN32_FIND_DATA FindFileData;
		HANDLE hf;
		CString DivPathWithFiles("");
		DivPathWithFiles = DivPathWithFiles + theApp.CurDivisionsPath + _T("\\*.sou");
		//hf=FindFirstFile(_T("c:\\*"), &FindFileData);
		hf=FindFirstFile(DivPathWithFiles, &FindFileData);
		if (hf!=INVALID_HANDLE_VALUE)
		{
			do{
				CString test = FindFileData.cFileName;
				if(FindFileData.cFileName == (theApp.DivisionFileName + _T(".sou")) )
				{
					/*
					int msgboxID = MessageBox(	_T("���� ������� � ������ \"") + theApp.DivisionFileName + _T("\" ��� ����������!\n\n������ ������������ ����?"),
												_T("����� ������ ���������!"),
												MB_ICONWARNING | MB_YESNO | MB_DEFBUTTON2			);
					if(msgboxID == IDNO)
					{
						//"���" - ���������� ������������� ������� � �������� ��� ����� �������
						m_EditDivFileName.SetFocus();
						return;
					}
					// "��" - ������������ ���������� �����
					*/

					int msgboxID = MessageBox(	_T("���� ������� � ������ \"") + theApp.DivisionFileName + _T("\" ��� ����������!"),
											_T("����� ������ ���������!"),
											MB_ICONWARNING | MB_OK );
					m_EditDivFileName.SetFocus();
					return;
				}
			}
			while (FindNextFile(hf,&FindFileData)!=0);
			FindClose(hf);
		}
	}

	// 1 // ������� ���������

//*
	// 1.1 // ��������� ����������� ���� ��� ����������:
	wchar_t szFilters[]= _T("SOU ����� �������� (*.sou)|*.sou|��������� ����� (*.txt)|*.txt|��� ����� (*.*)|*.*||");
	// Create an Open dialog; the default file name extension is ".sou".
	
	//CFileDialog fileDlg(TRUE, _T("txt"), _T("*.txt"),
	//	  OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this,0,0);
	
	//CFileDialog fileDlg(FALSE, _T("sou"), theApp.FullDivision[DIV_DIV_HEAD][DIV_DIV_NAME] + _T(".sou"),
	m_EditDivFileName.GetWindowText(theApp.DivisionFileName);
//	CFileDialog fileDlg(FALSE, _T("sou"), theApp.DivisionFileName + _T(".sou"),
//         OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);

	// Display the file dialog. When user clicks OK, fileDlg.DoModal() returns IDOK.
//	if( fileDlg.DoModal ()==IDOK )
//	{
//		CString SOUPathname = fileDlg.GetPathName();
		//m_Text_Path.SetWindowText(m_strPathname);

//*

	///////////////////////////////////////////////////////////////////////
	bool EqualDivFileNames = false;
	bool NoWarningMessage = false;
	if( (theApp.ChangeDivBtnClicked == theApp.DIV_BTN_ADD) || (theApp.ChangeDivBtnClicked == theApp.DIV_BTN_COPY) )
	{
		//if(theApp.AllDivisionsFileNames.size()>0)
		if(theApp.AllDivisions.size()>0)
		{
			//for(long i=0; i<theApp.AllDivisionsFileNames.size(); i++)
			for(long i=0; i<theApp.AllDivisions.size(); i++)
			{
				//if(theApp.AllDivisionsFileNames[i] == theApp.DivisionFileName)//theApp.FullDivision[DIV_DIV_HEAD][DIV_DIV_NAME])
				if(theApp.AllDivisions[i][DIVALL_FILE_NAME] == theApp.DivisionFileName)//theApp.FullDivision[DIV_DIV_HEAD][DIV_DIV_NAME])
				{
					EqualDivFileNames=true;
					int msgboxID = MessageBox(	_T("���� ������� � ������ \"") + theApp.DivisionFileName + _T("\" ��� ����������!\n\n������ ������������ ����?"),
												_T("����� ������ ���������!"),
												MB_ICONWARNING | MB_YESNO | MB_DEFBUTTON2			);
					if(msgboxID == IDNO)
					{
						//"���" - ���������� ������������� ������� � �������� ��� ����� �������
						NoWarningMessage=false;
						m_EditDivFileName.SetFocus();
						break;
					}
					else // "��" - ������������ ���������� �����
					{
						// 2) ��������� �������� �� ����� .SOU:
						// 2.1) ������� ������ ����
						CString DivisionFullPath("");				// ������ ���� � ����� ���������� �������

						bool bFound = false;
						if(theApp.CurDivisionsPath != EmptyStr)
						{
							CString sPath = theApp.CurDivisionsPath;
							CFileFind hFile;

							DivisionFullPath = DivisionFullPath + sPath + _T("\\") + theApp.DivisionFileName + _T(".sou");
							bFound = hFile.FindFile( DivisionFullPath );
						}

						if(theApp.ChangeDivBtnClicked != theApp.DIV_BTN_ADD)
						{
							if(theApp.CurDivisionsPath != EmptyStr)
							{
								if(bFound)
								{
									CFile::Remove(DivisionFullPath);// ������ ���� ���������� �����
								}
							}
						}


						// 2.2) ��������� ����� ����
						//CFile RedoneFileSOU;
						//RedoneFileSOU.Open(DivisionFullPath,  CFile::modeCreate|CFile:: modeReadWrite); // ������� ����� ����, ������� �� ������ � �� ������

//AfxMessageBox(_T("1 _ ") + DivisionFullPath);
						writeDivisionFile(DivisionFullPath);

					// 2 // ����� �������� ���������
					GetParent()->PostMessage(WM_DIVISION_EDIT_SAVE,0,0);

					CDialog::OnOK();
					}
				}
				else
				{NoWarningMessage = true;}
			}
		}
		else
		{
			// 2) ��������� �������� �� ����� .SOU:
			// 2.1) ������� ������ ����
			CString DivisionFullPath("");				// ������ ���� � ����� ���������� �������

			bool bFound = false;
			if(theApp.CurDivisionsPath != EmptyStr)
			{
				CString sPath = theApp.CurDivisionsPath;
				CFileFind hFile;

				DivisionFullPath = DivisionFullPath + sPath + _T("\\") + theApp.DivisionFileName + _T(".sou");
			}

			// 2.2) ��������� ����� ����
			//CFile RedoneFileSOU;
			//RedoneFileSOU.Open(DivisionFullPath,  CFile::modeCreate|CFile:: modeReadWrite); // ������� ����� ����, ������� �� ������ � �� ������

//AfxMessageBox(_T("2 _ ") + DivisionFullPath);
			writeDivisionFile(DivisionFullPath);

		// 2 // ����� �������� ���������
		GetParent()->PostMessage(WM_DIVISION_EDIT_SAVE,0,0);

		CDialog::OnOK();
		}
	}
	else
	{NoWarningMessage = true;}

	if(NoWarningMessage)
	{
		// 2) ��������� �������� �� ����� .SOU:
		// 2.1) ������� ������ ����
		CString DivisionFullPath("");				// ������ ���� � ����� ���������� �������

		bool bFound = false;
		if(theApp.CurDivisionsPath != EmptyStr)
		{
			CString sPath = theApp.CurDivisionsPath;
			CFileFind hFile;


			DivisionFullPath = DivisionFullPath + sPath + _T("\\") + theApp.DivisionFileName + _T(".sou");
			bFound = hFile.FindFile( DivisionFullPath );
		}

		if(theApp.ChangeDivBtnClicked != theApp.DIV_BTN_ADD)
		{
			if(theApp.CurDivisionsPath != EmptyStr)
			{
				if(bFound)
				{
					CFile::Remove(DivisionFullPath);// ������ ���� ���������� �����
				}
			}
		}


		// 2.2) ��������� ����� ����
		//CFile RedoneFileSOU;
		//RedoneFileSOU.Open(DivisionFullPath,  CFile::modeCreate|CFile:: modeReadWrite); // ������� ����� ����, ������� �� ������ � �� ������


//AfxMessageBox(_T("3 _ ") + DivisionFullPath);
		writeDivisionFile(DivisionFullPath);

	// 2 // ����� �������� ���������
	GetParent()->PostMessage(WM_DIVISION_EDIT_SAVE,0,0);

	CDialog::OnOK();
	}
}



void CDivisionEdit::writeDivisionFile(CString bstrXMLFile)
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

	//Add an attribute
	pXMLRootElem->setAttribute(_T("���"),				_variant_t( theApp.FullDivision[DIV_DIV_HEAD][DIV_DIV_NAME]		));
	pXMLRootElem->setAttribute(_T("�����"),				_variant_t( theApp.FullDivision[DIV_DIV_HEAD][DIV_PIPE_NAME]	));
	pXMLRootElem->setAttribute(_T("�����_���"),			_variant_t( theApp.FullDivision[DIV_DIV_HEAD][DIV_PIPE_ID]		));
	pXMLRootElem->setAttribute(_T("�������"),			_variant_t( theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_NAME]	));
	pXMLRootElem->setAttribute(_T("�������_���"),		_variant_t( theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID]		));
	pXMLRootElem->setAttribute(_T("��������"),			_variant_t( theApp.FullDivision[DIV_DIV_HEAD][DIV_PARAMETR]		));
	pXMLRootElem->setAttribute(_T("�������"),			_variant_t( theApp.FullDivision[DIV_DIV_HEAD][DIV_WATCH]		));
	pXMLRootElem->setAttribute(_T("�����"),				_variant_t( theApp.FullDivision[DIV_DIV_HEAD][DIV_WAVE]			));
	pXMLRootElem->setAttribute(_T("�����_�����������"),	_variant_t( theApp.FullDivision[DIV_DIV_HEAD][DIV_DTCT_TIME]	));
	pXMLRootElem->setAttribute(_T("�����_�����"),		_variant_t( theApp.FullDivision[DIV_DIV_HEAD][DIV_PIPE_LENGTH]	));
	pXMLRootElem->setAttribute(_T("���_������"),		_variant_t( theApp.FullDivision[DIV_DIV_HEAD][DIV_BEGIN_NAME]	));
	pXMLRootElem->setAttribute(_T("���_�����"),			_variant_t( theApp.FullDivision[DIV_DIV_HEAD][DIV_END_NAME]		));

	if(theApp.FullDivision.size()>1)
	{
		long NumOfDet=0;
		NumOfDet = theApp.FullDivision.size() - 1;		// NumOfDet = ����� �������� (�������� ������ ������ � ����������� �������) 

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

			pXMLChild->setAttribute(_T("���"),				 _variant_t( theApp.FullDivision[i][DIV_DET_NAME]	 ));
			pXMLChild->setAttribute(_T("��"),				 _variant_t( theApp.FullDivision[i][DIV_DET_NUMBER]	 ));
			pXMLChild->setAttribute(_T("�������"),			 _variant_t( theApp.FullDivision[i][DIV_DET_ACTIVE]	 ));
			pXMLChild->setAttribute(_T("����"),				 _variant_t( theApp.FullDivision[i][DIV_DET_PATH]	 ));
			pXMLChild->setAttribute(_T("��������"),			 _variant_t( theApp.FullDivision[i][DIV_DET_PTFIX]	 ));
			pXMLChild->setAttribute(_T("��������"),			 _variant_t( theApp.FullDivision[i][DIV_DET_DIST]	 ));
			pXMLChild->setAttribute(_T("������_��������"),	 _variant_t( theApp.FullDivision[i][DIV_DET_DPRESS]	 ));
			pXMLChild->setAttribute(_T("������_�����"),		 _variant_t( theApp.FullDivision[i][DIV_DET_DTIIME]	 ));
//			pXMLChild->setAttribute(_T("����������_������"), _variant_t( theApp.FullDivision[i][DIV_DET_DISTBEG] ));
//			pXMLChild->setAttribute(_T("����������_�����"),	 _variant_t( theApp.FullDivision[i][DIV_DET_DISTEND] ));

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



// ������ "�����" � ��������� �������
void CDivisionEdit::OnBnClickedCancel()
{
	// TODO: �������� ���� ��� ����������� �����������

	// �� ������ �������� !!!!!
	// �� ������ ����� ����� ������� "��������� ���������" => "��"/"���", ���� ������� ���� �������

	GetParent()->PostMessage(WM_DIVISION_EDIT_EXIT,0,0);

	CDialog::OnCancel();
}

// ������ "��������� �������" ��������, �����: 1) ������� ��� ������� 2) ������� ������� �� ������� 3) ���������� "��������" = "��������" 3) �� ������� ���������� ������ 1 ������

// ������� �� �������������� ������ � ���� "��� ����� �������"
void CDivisionEdit::OnEnChangeDivFileNameEdit()
{
	// TODO:  ���� ��� ������� ���������� RICHEDIT, �� ������� ���������� �� �����
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	CString DivFileName("");
	CString CurDivisionName("");
	CString Correct_DivFileName("");
	CString EmptyStr("");
	CString x1("/"), x2("\\"), x3(":"), x4("*"), x5("?"), x6("\""), x7("<"), x8(">"), x9("|");
	m_EditDivFileName.GetWindowText(Correct_DivFileName);

	m_EditDivName.GetWindowText(CurDivisionName);
	m_EditDivFileName.GetWindowText(DivFileName);
	if( (CurDivisionName==EmptyStr) && (DivFileName==EmptyStr) )
	{FirstNameEdit=true; FirstFileNameEdit=true;}


	if( (FirstFileNameEdit) && (!FirstNameEdit) )
	{FirstNameEdit=true;}
	else
	{FirstFileNameEdit=false;}

	// TODO:  �������� ��� �������� ����������

	if(Correct_DivFileName != EmptyStr)
	{
		for(long i=0; i<Correct_DivFileName.GetLength(); i++)
		{
			if( Correct_DivFileName[i] == x1 || Correct_DivFileName[i] == x2 || Correct_DivFileName[i] == x3 || Correct_DivFileName[i] == x4 ||Correct_DivFileName[i] == x5 ||
				Correct_DivFileName[i] == x6 || Correct_DivFileName[i] == x7 || Correct_DivFileName[i] == x8 || Correct_DivFileName[i] == x9 
			  )
			{
				Correct_DivFileName.Delete(i, 1); // ������� �� �������� ����� ������������ ��� ����� ����� � ������ ������  / \ : * " ? < > |
				i--;
			}
		}

		theApp.DivisionFileName = Correct_DivFileName;
		//m_EditDivFileName.SetWindowText(Correct_DivFileName);
	}
	else
	{
		theApp.DivisionFileName = EmptyStr;
	}

	if(bFirstDlg)
		ChecckForBtnSave(); // ��������� ����� �� ������������ ������ "���������"
}

// ������� �� ����� ������ � ���� "�������� �������"
void CDivisionEdit::OnEnChangeDivNameEdit()
{
	// TODO:  ���� ��� ������� ���������� RICHEDIT, �� ������� ���������� �� �����
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	CString DivFileName("");
	CString CurDivisionName("");
	CString CorrectDivisionName("");
	CString x1("/"), x2("\\"), x3(":"), x4("*"), x5("?"), x6("\""), x7("<"), x8(">"), x9("|");
	CString EmptyStr("");

	m_EditDivName.GetWindowText(CurDivisionName);
	m_EditDivFileName.GetWindowText(DivFileName);
	if( (CurDivisionName==EmptyStr) && (DivFileName==EmptyStr) )
	{FirstNameEdit=true; FirstFileNameEdit=true;}


	FirstNameEdit=false;

	// TODO:  �������� ��� �������� ����������

	m_EditDivName.GetWindowText(CurDivisionName);
	if(CurDivisionName != EmptyStr)
	{
		theApp.FullDivision[DIV_DIV_HEAD][DIV_DIV_NAME] = CurDivisionName;
		// ��� ������� ��� �������� � ������ theApp.FullDivision
		m_EditDivFileName.GetWindowText(DivFileName);
				
		if(theApp.ChangeDivBtnClicked == theApp.DIV_BTN_ADD) // ������ ������ "�������� �������"
		{
			if(CurDivisionName == EmptyStr)
			{DivFileName = EmptyStr;}
			else
			{
				//if(CurDivisionName.GetLength()>0)
				//////////////////////////////////////////////////////
				CorrectDivisionName = CurDivisionName;
				for(long i=0; i<CorrectDivisionName.GetLength(); i++)
				{
					if( CorrectDivisionName[i] == x1 || CorrectDivisionName[i] == x2 || CorrectDivisionName[i] == x3 || CorrectDivisionName[i] == x4 || CorrectDivisionName[i] == x5 ||
						CorrectDivisionName[i] == x6 || CorrectDivisionName[i] == x7 || CorrectDivisionName[i] == x8 || CorrectDivisionName[i] == x9 
					  )
					{
						CorrectDivisionName.Delete(i, 1); // ������� �� �������� ����� ������������ ��� ����� ����� � ������ ������  / \ : * " ? < > |
						i--;
					}
				}
				//////////////////////////////////////////////////////
				for(long i=0, j=0; i<CorrectDivisionName.GetLength(); i++)
				{
					if( (FirstFileNameEdit) &&
					(DivFileName.GetLength()==0) && (CorrectDivisionName.GetLength()==1) )
					{
						DivFileName = CorrectDivisionName;
						theApp.DivisionFileName = DivFileName;
						break;
					}
					else
					{
						if(FirstFileNameEdit)
						{
							DivFileName = CorrectDivisionName;
							theApp.DivisionFileName = DivFileName;
						}

						//if( (DivFileName.GetLength()>0) && (DivFileName[i] == CorrectDivisionName[i]) )
						//{
						//	j++;
						//	if(DivFileName.GetLength() == (j-1))
						//	DivFileName = CorrectDivisionName;
						//	theApp.DivisionFileName = DivFileName;
						//}
					}
				}
			}

		}
		else	// ������ ������ "��������" �������
		{
			// � ���� ������ �� ��������� ������������ ������������� ������ ��� �������.
		}
	}
	else
	{
		theApp.FullDivision[DIV_DIV_HEAD][DIV_DIV_NAME] = EmptyStr;
	}

	m_EditDivFileName.SetWindowText(theApp.DivisionFileName);

	//switch(theApp.ChangeDivBtnClicked)
	//{
	//case theApp.DIV_BTN_ADD: // ������ ������ "�������� �������"
	//	break;
	//case theApp.DIV_BTN_CHANGE: //������ ������ "�������� �������"
	//	break;
	//case theApp.DIV_BTN_LOOK: // ������ ������ "�������� �������"
	//	break;
	//}


	if(bFirstDlg)
		ChecckForBtnSave(); // ��������� ����� �� ������������ ������ "���������"

}


// ������� �� ������ ������������ ����� ���������
void CDivisionEdit::OnCbnSelchangeDivPipeCmbx()
{
	// TODO: �������� ���� ��� ����������� �����������
	int curIndex=0;			// ������ �������� ���������� � Combobx
	CString DivisionPipe("");

	curIndex = m_CmBxDivPipe.GetCurSel();
	if( curIndex == (-1) )  return;

	m_CmBxDivPipe.GetLBText( curIndex, DivisionPipe );
	theApp.CurDivPipe = DivisionPipe;

	// ��� ������ ��������� ����� ��������, ����� ������������� �� ���������, 
	// �� ������� �������� ����� ������.
	UINT nPipeNum(0);
	nPipeNum = m_CmBxDivPipe.GetCount();
	switch(nPipeNum)
	{
	case 0:
		m_CmBxDivPipe.EnableWindow(FALSE);
		m_CmBxDivProd.EnableWindow(FALSE);
		break;
	default:
		m_CmBxDivPipe.EnableWindow(FALSE);
		m_CmBxDivProd.EnableWindow(TRUE);
		// ����� �� ������� ��������������� ������ ���������
		SetProdsToCmBx();
		break;
	}

	//if()
	//SetProdsToCmBx();

	int u(0);

	if(bFirstDlg)
		ChecckForBtnSave(); // ��������� ����� �� ������������ ������ "���������"
}


// ������ "��������� �������" ��������, �����: 1) ������� ��� ������� 2) ������� ������� �� ������� 3) ���������� "��������" = "��������" 3) �� ������� ���������� ������ 1 ������
// ������� �� ������ �������� ����� ��� ��������� ��� ������� �� ����������
void CDivisionEdit::OnCbnSelchangeDivProdCmbx()
{
	// TODO: �������� ���� ��� ����������� �����������
	int curIndex=0;			// ������ �������� ���������� � Combobx
	curIndex = m_CmBxDivProd.GetCurSel();
	if( curIndex == (-1) )  return;

	// ��� ������ ��������� ����� ��������, ����� ������������� �� ���������, 
	// �� ������� � ����������� �������� ����� ������.

	if(curIndex != (-1))
	{
		// ���������� ��������� ���������� � ������� ��� �����
		CString DivisionProduct("");
		m_CmBxDivProd.GetLBText( curIndex, DivisionProduct );
		theApp.CurDivProd = DivisionProduct;
		CString Preassure("��������");

		std::vector<CString> TitleDetector;
		bool bSetDivivsionHead(true);
		UINT nDetNum(0);

		switch(theApp.ChangeDivBtnClicked)
		{
		case theApp.DIV_BTN_ADD: // ������ ������ "�������� �������"
			//m_CmBxDivProd.EnableWindow(FALSE);				// �������	// �������������

			m_EditDivFileName.EnableWindow(TRUE);
			m_EditDivName.EnableWindow(TRUE);
			//m_EditDivParam.EnableWindow(TRUE);
			//m_CmBxDivWatch.EnableWindow(TRUE);
			m_EditDivWave.EnableWindow(TRUE);
			m_EditDivTimeDetect.EnableWindow(TRUE);

			// �������� ���� ��� ���, ��� ��� �� ����� ������ �������� ����� ������
			//m_ListDiv_Det.EnableWindow(TRUE);
			m_BtnDiv_DetAddAll.EnableWindow(TRUE);
			m_BtnDiv_DetAdd.EnableWindow(TRUE);
			//m_BtnDiv_DetDel.EnableWindow(TRUE);
			//m_BtnDiv_DetChange.EnableWindow(TRUE);
			//m_BtnDiv_DetLook.EnableWindow(TRUE);
			//m_BtnDivSave.EnableWindow(TRUE);				// ����� ������ �������� ������ ������� ��� ��������, ����� ��������� ������ "���������"


			TitleDetector = theApp.AllDetectors[DET_HEAD]; // ��������� ������ ������� � "������", ����� ��� �� �������� ��� ����������
			theApp.AllDetectors.erase(theApp.AllDetectors.begin() + DET_HEAD); // ������� �� ������� ������ ������� � ������� ����� ���� � ��������

			// �������������� ������� ������ � ���������, ������� ����� ���� ���������� �� ������ �������.
			theApp.DivDetectors.clear();

			nDetNum = theApp.AllDetectors.size();
			for(UINT i(0); i<nDetNum; i++)
			{	//DET_PIPE_SHNAME //DET_PIPE_ID
				if( (theApp.CurDivPipe == theApp.AllDetectors[i][DET_PIPE_SHNAME]) && (theApp.CurDivProd == theApp.AllDetectors[i][DET_PROD_TYPE]) )
				{
					if( bSetDivivsionHead )
					{
						//////////////////////////////////////////////////////////////////////
						// ����� ������ ���������� ������� ��������� (����������� �������)
						theApp.FullDivision[DIV_DIV_HEAD][DIV_PIPE_NAME]	= theApp.CurDivPipe;
						theApp.FullDivision[DIV_DIV_HEAD][DIV_PIPE_ID]		= theApp.AllDetectors[i][DET_PIPE_ID];
						theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_NAME]	= theApp.CurDivProd;
						theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID]		= theApp.AllDetectors[i][DET_PROD_VIEW];
						theApp.FullDivision[DIV_DIV_HEAD][DIV_PARAMETR]		= Preassure;
						theApp.FullDivision[DIV_DIV_HEAD][DIV_WATCH]		= _T("1");
						theApp.FullDivision[DIV_DIV_HEAD][DIV_WAVE]			= theApp.AllDetectors[i][DET_WAVE_SPEED];
						theApp.FullDivision[DIV_DIV_HEAD][DIV_DTCT_TIME]	= _T("10");
						theApp.FullDivision[DIV_DIV_HEAD][DIV_PIPE_LENGTH]	= theApp.AllDetectors[i][DET_PIPE_LENGHT];
						theApp.FullDivision[DIV_DIV_HEAD][DIV_BEGIN_NAME]	= theApp.AllDetectors[i][DET_BEGIN_NAME];
						theApp.FullDivision[DIV_DIV_HEAD][DIV_END_NAME]		= theApp.AllDetectors[i][DET_END_NAME];

						//////////////////////////////////////////////////////////////////////
						// ����� ��������� � ��� Edit � ������ �����
						////m_EditDivParam.SetWindowText(Preassure);
						////m_CmBxDivWatch.SetCurSel(0);	// ������������� �� ��������� "1" = "��"  //  SetWindowText(_T("1"));
						m_EditDivPipeLenght.SetWindowText(	theApp.FullDivision[DIV_DIV_HEAD][DIV_PIPE_LENGTH]);
						m_EditDivBeginName.SetWindowText(	theApp.FullDivision[DIV_DIV_HEAD][DIV_BEGIN_NAME]);
						m_EditDivEndName.SetWindowText(		theApp.FullDivision[DIV_DIV_HEAD][DIV_END_NAME]);
						m_EditDivWave.SetWindowText(		theApp.FullDivision[DIV_DIV_HEAD][DIV_WAVE] );
						m_EditDivTimeDetect.SetWindowText(	theApp.FullDivision[DIV_DIV_HEAD][DIV_DTCT_TIME] );

						bSetDivivsionHead=false;
					}

					// ��� �� �� ����� � ��������  �� ������� �������� � ������ ��������, ������� ����� �������������� �������������� �� ������� ��������
					theApp.DivDetectors.push_back(theApp.AllDetectors[i]);
				}
			}

			theApp.AllDetectors.insert(theApp.AllDetectors.begin(), TitleDetector); // ��������� ����� ������� � ������
			TitleDetector.clear();


			/*
			// ���������� 3 ��������� ��� �����
			if(theApp.CurDivProd == _T("������"))
			{
				m_EditDivWave.SetWindowText(_T("1.19"));
				// {m_EditDivWave.SetWindowText(_T("1190"));
			}
			if(theApp.CurDivProd == _T("������"))
			{
				m_EditDivWave.SetWindowText(_T("1.22"));
				// {m_EditDivWave.SetWindowText(_T("1220"));
			}
			if(theApp.CurDivProd == _T("�������"))
			{
				m_EditDivWave.SetWindowText(_T("1.2"));
				// {m_EditDivWave.SetWindowText(_T("1200"));
			}

			m_EditDivTimeDetect.SetWindowText(_T("10"));

			// ��� �� �� �������� �� ������� �������� � ������ ��������, ������� ����� �������������� �������������� �� ������� ��������
			theApp.DivDetectors.clear();
			for(UINT i(0); i<theApp.AllDetectors.size(); i++)
			{
				//if(theApp.AllDetectors[i][6] == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID]) // ���� �������� � OnInitDialog "��.�������"
				//if(theApp.AllDetectors[i][5] == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID]) // ���� �������� � OnInitDialog "�������"
				// ������������� �������, ��� ��� �� ����� ���� �� ������� ������ �� ����, ��� �� ����� ���� � theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID], � ��� ������ ��������� ������ "��.�������"
				if( 
					//(theApp.AllDetectors[i][DET_PROD_ID] == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID]) || 
					(theApp.AllDetectors[i][DET_PROD_TYPE] == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_NAME]) 
				  ) 
				{theApp.DivDetectors.push_back(theApp.AllDetectors[i]);}
				//theApp.DIVDET_NUM = theApp.DivDetectors.size();
			}
			//*/

			break;
		case theApp.DIV_BTN_CHANGE: //������ ������ "�������� �������"
			break;
		case theApp.DIV_BTN_LOOK: //������ ������ "�������� �������"
			break;
		}


		// ��������� � ������������� ���������� ����� ����� + ��������� ������� �� ���������� �� "�����_�������"
		if(  ( !theApp.CurDivPipe.IsEmpty() ) && ( !theApp.CurDivProd.IsEmpty() )  )
		{
			CString sDefaultDivisionAndFileName(theApp.CurDivPipe +_T("_")+ theApp.CurDivProd);		
			m_EditDivName.SetWindowText( sDefaultDivisionAndFileName + _T("") );
			m_EditDivFileName.SetWindowText( sDefaultDivisionAndFileName + _T("_���") );
		}

		// ���� ��� ������� � ������ �������� �� ���
		m_CmBxDivProd.EnableWindow(FALSE);
	}

	if(bFirstDlg)
		ChecckForBtnSave(); // ��������� ����� �� ������������ ������ "���������"
}




// ������ "��������� �������" ��������, �����: 1) ������� ��� ������� 2) ������� ������� �� ������� 3) ���������� "��������" = "��������" 3) �� ������� ���������� ������ 1 ������
void CDivisionEdit::OnEnChangeDivParamEdit() // �������� = "��������"
{
	// TODO:  ���� ��� ������� ���������� RICHEDIT, �� ������� ���������� �� �����
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  �������� ��� �������� ����������
	if(bFirstDlg)
		ChecckForBtnSave(); // ��������� ����� �� ������������ ������ "���������"
}


//void CDivisionEdit::OnEnChangeDivWatchEdit() // �������
//{
	// TODO:  ���� ��� ������� ���������� RICHEDIT, �� ������� ���������� �� �����
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  �������� ��� �������� ����������
	//FullDivParam = theApp.FullDivision[DIV_DIV_HEAD][DIV_WATCH];
	//element->SetAttribute("�������",FullDivParam);
//}



void CDivisionEdit::OnCbnSelchangeDivWatchCmbx()  // ������� // ��=1, ���=0
{
	// TODO: �������� ���� ��� ����������� �����������
	int curIndex=0;			// ������ �������� ���������� � Combobx
	CString DivisionWatch("");

////	curIndex = m_CmBxDivWatch.GetCurSel();
////	if( curIndex == (-1) )  return;

////	m_CmBxDivWatch.GetLBText( curIndex, DivisionWatch );
	
	if( DivisionWatch == _T("��") )
	{theApp.FullDivision[DIV_DIV_HEAD][DIV_WATCH] = _T("1");}
	if( DivisionWatch == _T("���") )
	{theApp.FullDivision[DIV_DIV_HEAD][DIV_WATCH] = _T("0");}
}


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////


void CDivisionEdit::OnEnChangeDivPipeLenghtEdit()
{
	// TODO:  �������� ��� �������� ����������
}


void CDivisionEdit::OnEnChangeDivBeginNameEdit()
{
	// TODO:  �������� ��� �������� ����������
}


void CDivisionEdit::OnEnChangeDivEndNameEdit()
{
	// TODO:  �������� ��� �������� ����������
}




void CDivisionEdit::OnEnChangeDivWaveEdit() // �����
{
/*
	// TODO:  ���� ��� ������� ���������� RICHEDIT, �� ������� ���������� �� �����
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  �������� ��� �������� ����������
	bool NoNeedToChange=true;
	CString DivisionWave("");
	m_EditDivWave.GetWindowText(DivisionWave);
	NoNeedToChange = CheckString(DivisionWave);

	int curIndex = m_CmBxDivProd.GetCurSel();
	if( curIndex == (-1) )  return;

	double dWaveSpeed = _tstof(DivisionWave);
	if(  ( ((dWaveSpeed < 0.5) || (dWaveSpeed > 1.5)) )  && curIndex!=(-1) )
	{
		AfxMessageBox( _T("��������: �������� \"�����\" ������ ���� ����� � ��������� ��������� �������� �� 0.5 �� 1.5 (��/�)."), MB_ICONWARNING );
		//if(dWaveSpeed < 0.5)
		//{m_EditDivWave.SetWindowText(_T("0.5"));}
		//if(dWaveSpeed > 1.5)
		//{m_EditDivWave.SetWindowText(_T("1.5"));}
	}


	int StartCh=0, EndCh=0;
	m_EditDivWave.GetSel(StartCh, EndCh);
	if(WaveEdit && !NoNeedToChange)
	{
		WaveEdit=false;
		//m_EditDetDPress.Undo();
		m_EditDivWave.SetWindowText(DivisionWave);
	}

	if(!NoNeedToChange)
	{m_EditDivWave.SetSel(StartCh-1, EndCh-1, 0);}

	WaveEdit=true;


	theApp.FullDivision[DIV_DIV_HEAD][DIV_WAVE] = DivisionWave;
*/
}


void CDivisionEdit::OnEnChangeDivTimedetectEdit() // �����_�����������
{
/*
	// TODO:  ���� ��� ������� ���������� RICHEDIT, �� ������� ���������� �� �����
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  �������� ��� �������� ����������
	bool NoNeedToChange=true;
	CString DivisionTimeDetect("");
	m_EditDivTimeDetect.GetWindowText(DivisionTimeDetect);
	NoNeedToChange = CheckString(DivisionTimeDetect);

	int curIndex = m_CmBxDivProd.GetCurSel();
	if( curIndex == (-1) )  return;

	double dTimeDetect = _tstof(DivisionTimeDetect);
	if(  ( ((dTimeDetect < 0) || (dTimeDetect > 200)) )  && curIndex!=(-1) )
	{
		AfxMessageBox( _T("��������: �������� \"����� �����������\" ������ ���� ����� � ��������� ��������� �������� �� 0 �� 200 (�)."), MB_ICONWARNING );
		//if(dTimeDetect < 0)
		//{m_EditDivTimeDetect.SetWindowText(_T("0"));}
		//if(dTimeDetect > 200)
		//{m_EditDivTimeDetect.SetWindowText(_T("200"));}
	}


	int StartCh=0, EndCh=0;
	m_EditDivTimeDetect.GetSel(StartCh, EndCh);
	if(TimeDetEdit && !NoNeedToChange)
	{
		TimeDetEdit=false;
		//m_EditDetDPress.Undo();
		m_EditDivTimeDetect.SetWindowText(DivisionTimeDetect);
	}

	if(!NoNeedToChange)
	{m_EditDivTimeDetect.SetSel(StartCh-1, EndCh-1, 0);}

	TimeDetEdit=true;


	theApp.FullDivision[DIV_DIV_HEAD][DIV_DTCT_TIME] = DivisionTimeDetect;
*/
}


// ������� �� ������� �� ������ ��������
void CDivisionEdit::OnLvnItemchangedDivDetectorsList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �������� ���� ��� ����������� �����������
	CString EmptyStr("");
	long nCount=0;		// ����� ������� � Listbox
	long curIndex=0;	// ������ �������� ���������� � Listbox
	POSITION pos=NULL;	// ����� ���������� �������� (pos = curIndex+1)

	nCount = m_ListDiv_Det.GetItemCount();
	if(nCount>0)
		m_CmBxDivProd.EnableWindow(FALSE);
	else
		m_CmBxDivProd.EnableWindow(FALSE); //m_CmBxDivProd.EnableWindow(TRUE);


	//����� ���������� ������� �� ������ �����������
	pos = m_ListDiv_Det.GetFirstSelectedItemPosition();
	if(pos==NULL) return;	// ������ �� ������ �����, ���� � ������ ������ �� �������
	curIndex = m_ListDiv_Det.GetNextSelectedItem(pos);
	if( curIndex == (-1) )  return;

	//sDivDetNum
	CString sDivDetNum = m_ListDiv_Det.GetItemText(curIndex,0);
	CString sDivDetName = m_ListDiv_Det.GetItemText(curIndex,1);
	//if(theApp.FullDivision.size()>1)
	//{
	//	for(long i=1; i<theApp.FullDivision.size(); i++)
	//	{
	//		if(theApp.FullDivision[DIV_DIV_HEAD][DIV_DIV_NAME] == )
	//		{
	//		}
	//	}
	//}

	//long lDivDetNum = _tstol(sDivDetNum);


	// "��������" ����� ������ ���� ������ �� ��� ���������� ��� ������ �� ����
	// "��������" �� ����� ����������� � ���������� �������� ��������, �������� �� ������ �� ��� �� ������� � ������
	if(theApp.EditDivDetBtnClicked == theApp.DET_BTN_LOOK)
	{
		//int x,y;
		//x = sDivDetNum.GetLength();
		//wchar_t* buffer = new wchar_t[x+1];
		//if (buffer!=NULL)
		//{
		//	for (y=0; y<x; y++)
		//	buffer[y]=sDivDetNum[y];
		//	buffer[y]='\0';
		//}

/*
		wchar_t buffer[1000];
		int x=1000,y=0;
		x = sDivDetNum.GetLength();
		for (y=0; y<x; y++)
		buffer[y]=sDivDetNum[y];
		buffer[y]='\0';
*/

		CString NumPlusName =  sDivDetNum +_T(" - ")+ sDivDetName;

		wchar_t buffer[1000];
		int x=1000,y=0;
		x = NumPlusName.GetLength();
		for (y=0; y<x; y++)
		buffer[y]=NumPlusName[y];
		buffer[y]='\0';


		//::PostMessage( DetectorDlgHWND, WM_DIV_DETECTOR_CHANGE, (WPARAM)buffer, 0);
		::SendMessage( DetectorDlgHWND, WM_DIV_DETECTOR_CHANGE, (WPARAM)buffer, 0);
		//delete[] buffer;

		//::PostMessage( DetectorDlgHWND, WM_DIV_DETECTOR_CHANGE, 0, (LPARAM)lDivDetNum);
	}

	*pResult = 0;
}

// ������ "������� ������" � ��������� �������
void CDivisionEdit::OnBnClickedDivDetDellBtn()
{
	// TODO: �������� ���� ��� ����������� �����������
	CString EmptyStr("");
	long nCount=0;		// ����� ������� � Listbox
	long curIndex=0;	// ������ �������� ���������� � Listbox
	POSITION pos=NULL;	// ����� ���������� �������� (pos = curIndex+1)

	nCount = m_ListDiv_Det.GetItemCount();
	//����� ���������� ������� �� ������ �����������
	pos = m_ListDiv_Det.GetFirstSelectedItemPosition();
	if(pos==NULL) return;	// ������ �� ������ �����, ���� � ������ ������ �� �������
	curIndex = m_ListDiv_Det.GetNextSelectedItem(pos);
	if( curIndex == (-1) )  return;

	//CString sDivDetNum = m_ListDiv_Det.GetItemText(curIndex,0);
	CString sDivDetNum = m_ListDiv_Det.GetItemText(curIndex,0);

	//CString sGroup;
	//if(sUser!=_T("smth."))
	//	sGroup.Format(_T("%d"),m_DivChangeList.GetItemData(nCurItem));
	//else
	//	sGroup = sUser;

	// ��������������� �������� ������ �� ������
	m_ListDiv_Det.DeleteItem(curIndex);

	// (*) �.�. �������� ������ �� ����������� ������������� ������������ ��������� ��������, �� �������� ��� ������� �������
	//CString LowerName("");
	//nCount = m_DivChangeList.GetItemCount(); // ����� �������� ����� ��������� ������ ������ �� 1-�
	//for(long i=curIndex; i<nCount; i++)
	//{
	//	LowerName = m_DivChangeList.GetItemText(i,0);
	//	m_DivChangeList.InsertItem(i, LowerName);
	//}

	//������� ���� (*) �����������, ��� ��� �� ������� ������ ������� "������" �� ������� theApp.FullDivision[1...n][]
	// � ����� ������ ������ � ������� �� .sou-�����, � ����� ������ �������� �������� ��� ����������� �������� ������ � ������:
	// 1) ��������� ������� �� �������:
	nCount = m_ListDiv_Det.GetItemCount();	// ������ �����, ��� ��������� ����� �� ���� ������.
	
	for(long i=1; i<theApp.FullDivision.size(); i++)
	{
		//if(theApp.FullDivision[i][0] == sDivDetNum)
		if(theApp.FullDivision[i][DIV_DET_NUMBER] == sDivDetNum)
		{
			theApp.FullDivision.erase(theApp.FullDivision.begin()+i); // ������� �� ������� i-��� ������ (�������)
			break;
		}
	}
/*
	// 2) ��������� ������� �� ����� .SOU:
	// 2.1) ������� ������ ����
	CString DivisionFullPath("");				// ������ ���� � ����� ���������� �������
	if(theApp.CurDivisionsPath != EmptyStr)
	{
		CString sPath = theApp.CurDivisionsPath;
		CFileFind hFile;

		DivisionFullPath = DivisionFullPath + sPath + _T("\\") + theApp.DivisionFileName + _T(".sou");
		bool bFound = false;
		bFound = hFile.FindFile( DivisionFullPath );
				
		if(bFound)
		{
			CFile::Remove(DivisionFullPath);// ������ ���� ���������� �����
		}
	}

	// 2.2) ��������� ����� ����
	//CFile RedoneFileSOU;
	//RedoneFileSOU.Open(DivisionFullPath,  CFile::modeCreate|CFile:: modeReadWrite); // ������� ����� ����, ������� �� ������ � �� ������

	TiXmlDocument doc;
	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "windows-1251", "" );
	doc.LinkEndChild( decl );

	TiXmlElement* element = new TiXmlElement( "�������_���" );
	TiXmlText* text = new TiXmlText( "" );

	CStringA FullDivParam("");
	FullDivParam = theApp.FullDivision[DIV_DIV_HEAD][DIV_DIV_NAME];
	element->SetAttribute("���",FullDivParam);
	FullDivParam = theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID];
	element->SetAttribute("�������",FullDivParam);
	FullDivParam = theApp.FullDivision[DIV_DIV_HEAD][DIV_PARAMETR];
	element->SetAttribute("��������",FullDivParam);
	FullDivParam = theApp.FullDivision[DIV_DIV_HEAD][DIV_WATCH];
	element->SetAttribute("�������",FullDivParam);
	FullDivParam = theApp.FullDivision[DIV_DIV_HEAD][DIV_WAVE];
	element->SetAttribute("�����",FullDivParam);
	FullDivParam = theApp.FullDivision[DIV_DIV_HEAD][DIV_DTCT_TIME];
	element->SetAttribute("�����_�����������",FullDivParam);

	doc.LinkEndChild( element );
	element->LinkEndChild( text );

	if(theApp.FullDivision.size()>1)
	{
		long NumOfDet=0;
		NumOfDet = theApp.FullDivision.size() - 1;		// NumOfDet = ����� �������� (�������� ������ ������ � ����������� �������) 

		for(long i=1, j=0; j<NumOfDet; i++, j++)
		{
			TiXmlElement* element2 = new TiXmlElement( "������" );
			TiXmlText* text2 = new TiXmlText( "" );

			FullDivParam = theApp.FullDivision[i][DIV_DET_NUMBER];	element2->SetAttribute("���",FullDivParam);
			FullDivParam = theApp.FullDivision[i][DIV_DET_NAME];	element2->SetAttribute("��",FullDivParam);
			FullDivParam = theApp.FullDivision[i][DIV_DET_ACTIVE];	element2->SetAttribute("�������",FullDivParam);
			FullDivParam = theApp.FullDivision[i][DIV_DET_PATH];	element2->SetAttribute("����",FullDivParam);
			FullDivParam = theApp.FullDivision[i][DIV_DET_PTFIX];	element2->SetAttribute("��������",FullDivParam);
			FullDivParam = theApp.FullDivision[i][DIV_DET_DIST];	element2->SetAttribute("��������",FullDivParam);
			FullDivParam = theApp.FullDivision[i][DIV_DET_DPRESS];	element2->SetAttribute("������_��������",FullDivParam);
			FullDivParam = theApp.FullDivision[i][DIV_DET_DTIIME];	element2->SetAttribute("������_�����",FullDivParam);

			element->LinkEndChild( element2 );
			element2->LinkEndChild( text2 );
		}
	}
	doc.SaveFile( (CStringA)DivisionFullPath );
*/

	// 3) �������������� ������
	CString DetectorName(""); // ��� ���������� �������

	m_ListDiv_Det.DeleteAllItems(); // �������������� ���������� ������

	//CRect rect;
	//m_ListDiv_Det.GetClientRect(rect);
	(void)m_ListDiv_Det.SetExtendedStyle( LVS_EX_FULLROWSELECT );
	//m_ListDiv_Det.SetHeadings( _T("� ����� ���������,		60;\
	//								�������� ������� �� �������,") + LintToCStr(rect.Width())
	//						 );
	//m_ListDiv_Det.LoadColumnInfo();

	//*
	// ��������� ������ ���������� �������� ��������� �������� ������ .sou �� ����� "�������"
		long NumOfDet=0;
		long NumOfDetParams=0;
		if(theApp.FullDivision.size()>1)
		{ 
			NumOfDet = theApp.FullDivision.size() - 1;		// NumOfDet = ����� �������� (�������� ������ ������ � ����������� �������) 
			NumOfDetParams = theApp.FullDivision[DIV_DET_HEAD].size();	// NumOfDetParams = ����� ���������� ��������
	
			for(UINT i(DIV_DET_HEAD), j(DET_HEAD); j < NumOfDet; i++, j++)
			{
				/*
				m_ListDiv_Det.InsertItem(j, theApp.FullDivision[i][DIV_DET_NUMBER]); // � 1-�� ������� ��� ������� � ������� // ����� �������
				// ��� ��� ��� ����� ������:
				m_ListDiv_Det.SetItemText(j, 0, theApp.FullDivision[i][DIV_DET_NUMBER]); // � 1-�� ������� ��� ������� � ������� // ����� �������
				m_ListDiv_Det.SetItemText(j, 1, theApp.FullDivision[i][DIV_DET_NAME]); // �� 2-�� ������ �������� ������� �� ������� // �������� �������
				*/

				(void)m_ListDiv_Det.AddItem(
											theApp.FullDivision[i][DIV_DET_NUMBER],
											theApp.FullDivision[i][DIV_DET_NAME]
										 );
			}
			m_ListDiv_Det.SetExtendedStyle( m_ListDiv_Det.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
		}

	//*/

	// ���� ��������� �� ������� �� ��� �������, ����� �������� ���� ������ ������ "��������", ��������� �������������
	if(m_ListDiv_Det.GetItemCount()>0)
	{
		m_ListDiv_Det.EnableWindow(TRUE);
		m_BtnDiv_DetAddAll.EnableWindow(TRUE);
		m_BtnDiv_DetAdd.EnableWindow(TRUE);
		m_BtnDiv_DetDel.EnableWindow(TRUE);
		m_BtnDiv_DetChange.EnableWindow(TRUE);
		m_BtnDiv_DetLook.EnableWindow(TRUE);

		m_BtnDivExit.EnableWindow(TRUE);
	}
	else
	{
		m_ListDiv_Det.EnableWindow(FALSE);
		m_BtnDiv_DetAddAll.EnableWindow(TRUE);
		m_BtnDiv_DetAdd.EnableWindow(TRUE);
		m_BtnDiv_DetDel.EnableWindow(FALSE);
		m_BtnDiv_DetChange.EnableWindow(FALSE);
		m_BtnDiv_DetLook.EnableWindow(FALSE);

		m_BtnDivExit.EnableWindow(TRUE);
	}


	ChecckForBtnSave();
}


// ������ "�������� ������" � ��������� �������
void CDivisionEdit::OnBnClickedDivDetAddBtn()
{
	// ���������� �������� �������� �� �� ������ �� ���� ������ �� XML-����� � ���������, ���� ����� �� ����� ���� ���, �� ������ ���������
	// !!!!!


	// TODO: �������� ���� ��� ����������� �����������
	// 0 // � ������ � "��������" ��� �� ����� �������� ��� ���������� ������� ��� ���������, ��� ������ ������ � ��������.

	// 1.2	��������� �������������� ���������� �� ��������, ��� ��� ����������� �� �������
	//		����� � ���������� ������ ���� ������ ��������������� ������� �������������, ��� 2-�� ���������� �������� �� ������� ���� �� �����
	//		��  theApp.DivDetectors[0...n][]  ���������� ������� ���  theApp.FullDivision[1...n][] 
	//theApp.DivSortDetectors.clear();
	std::vector<std::vector<CString>> TestDivSortDetectors; // ������� ���������� �� XML-�����, ������� ������� �� �������� �� �������, � �� ���������� ��� ��������, ��� ��� ���� �� �������
	TestDivSortDetectors = theApp.DivDetectors; // ELSE // �� ���� ������� ������ �� ������ � ELSE
	if(theApp.FullDivision.size() > 1)
	{
		for(long j=DIV_DET_HEAD; j<theApp.FullDivision.size(); j++)
		{
			for(long i=0; i<TestDivSortDetectors.size(); i++)
			{
				//if(TestDivSortDetectors[i][1] == theApp.FullDivision[j][DIV_DET_NAME])
				if(TestDivSortDetectors[i][DET_NAME] == theApp.FullDivision[j][DIV_DET_NAME])
				{
					TestDivSortDetectors.erase(TestDivSortDetectors.begin()+i); // ������� �� ������� i-��� ������ (�������)
					break;
				}
			}
		}
	}
	else // ELSE // � ������ ���� �� ������� ��� ��������, �� ������ ��������� ��������������� �� �������� ������� ��� �������� �� XML-�����
	{
		//for(long i=0; i<theApp.DivDetectors.size(); i++)
		//{
		//	if(theApp.FullDivision[DIV_DIV_HEAD][DET_NAME])
		//	{
		//		TestDivSortDetectors.push_back(theApp.DivDetectors[i]);
		//	}
		//}
	}


	//if( // � ������ ���� ��������� ���� �� �� "�������� �������" � 
	//	(theApp.ChangeDivBtnClicked == theApp.DIV_BTN_ADD)  &&
	//	(  (TestDivSortDetectors.size() != 0) || (theApp.FullDivision.size() == 1)  ) 
	//  )	// �� ������� ��������������� ������ � ����������� ��������� 
		// ��� � ������� ������� ������ ������ � ������� � ��� �� ���������� �������� - ��� �����, �������� ������ � ����� �������, �������� ������������ ����� ����� ������ �������� � XML
	//{
	// ������ �� ��������� ������������ �������� ��� ����� �������� �� ����� ������� ������  8
	//CIniParam AppMaxDetectors(theApp.IniFileName, _T("Program"), _T("MaxDetectors"), _T("8"));
	//theApp.MaxDetectors = AppMaxDetectors.AsInt();

	if(TestDivSortDetectors.size() > 0)
	{
		if(theApp.MaxDetectors > 0)
		{
			if(m_ListDiv_Det.GetItemCount() < theApp.MaxDetectors)
			{
				// 1 // ������ ����� ���� �������� ��� ������ ���� ����� �����, ��� ������ ������ "��������"
				theApp.EditDivDetBtnClicked = theApp.DET_BTN_ADD;

				// 2 // ��������� ��� ������ (+������ ��������) �� ��� ��� ���� ������������ �� �������� �������� � ��������� ��������
				m_ListDiv_Det.EnableWindow(FALSE);
				m_BtnDiv_DetAddAll.EnableWindow(FALSE);
				m_BtnDiv_DetAdd.EnableWindow(FALSE);
				m_BtnDiv_DetDel.EnableWindow(FALSE);
				m_BtnDiv_DetChange.EnableWindow(FALSE);
				m_BtnDiv_DetLook.EnableWindow(FALSE);
				m_BtnDivSave.EnableWindow(FALSE);
				m_BtnDivExit.EnableWindow(FALSE);

				// 3 // ��������� ���� ��� ������������� �������
				CDetectorsEdit* p_DetectorsEditDlg = new CDetectorsEdit;
				p_DetectorsEditDlg->Create(IDD_EDIT_DETECTOR_DLG, this);
				p_DetectorsEditDlg->ShowWindow(SW_SHOW);

				DetectorDlgHWND = p_DetectorsEditDlg->GetSafeHwnd();
			}
			else
			{
				AfxMessageBox(_T("����� �������� ������������� �� ���� ������� �� ����� ���� ������ ") + LintToCStr(theApp.MaxDetectors));
			}
		}
		else
		{
				// 1 // ������ ����� ���� �������� ��� ������ ���� ����� �����, ��� ������ ������ "��������"
				theApp.EditDivDetBtnClicked = theApp.DET_BTN_ADD;

				// 2 // ��������� ��� ������ (+������ ��������) �� ��� ��� ���� ������������ �� �������� �������� � ��������� ��������
				m_ListDiv_Det.EnableWindow(FALSE);
				m_BtnDiv_DetAddAll.EnableWindow(FALSE);
				m_BtnDiv_DetAdd.EnableWindow(FALSE);
				m_BtnDiv_DetDel.EnableWindow(FALSE);
				m_BtnDiv_DetChange.EnableWindow(FALSE);
				m_BtnDiv_DetLook.EnableWindow(FALSE);
				m_BtnDivSave.EnableWindow(FALSE);
				m_BtnDivExit.EnableWindow(FALSE);

				// 3 // ��������� ���� ��� ������������� �������
				CDetectorsEdit* p_DetectorsEditDlg = new CDetectorsEdit;
				p_DetectorsEditDlg->Create(IDD_EDIT_DETECTOR_DLG, this);
				p_DetectorsEditDlg->ShowWindow(SW_SHOW);

				DetectorDlgHWND = p_DetectorsEditDlg->GetSafeHwnd();
		}
	}
	else
	{
		if(theApp.AllDetectors.size() > 0)
		{
			AfxMessageBox(_T("��� ��������� ������� ��� ������� ��������, ���������� �� ������� �������, �������������! ")
						  _T("�������� ��������� ��� ���������� ������ �� ��������."));
		}
		else
		{
			AfxMessageBox(_T("�� ������� ������� XML-���� � ���������!\n\n")
						  _T("���������:\n")
						  _T("1) ����� �� ������ ���� � ����� �� ������� ��������.\n")
						  _T("2) ���������� �� ��� ���� �� ������� ����.\n")
						  _T("3) ������� �� ��������� XML-���� ��� ������."));
		}
	}

}

// ���������� ���� ��������� �� ������ ����� ��������
// ������ "�������� ��� �������" � ��������� �������
void CDivisionEdit::OnBnClickedDivDetAddAllBtn()
{
	// ���������� �������� �������� �� �� ������ �� ���� ������ �� XML-����� � ���������, ���� ����� �� ����� ���� ���, �� ������ ���������
	// !!!!!

	// TODO: �������� ���� ��� ����������� �����������
	// 0 // � ������ � "��������" ��� �� ����� �������� ��� ���������� ������� ��� ���������, ��� ������ ������ � ��������.

	// 1.2	��������� �������������� ���������� �� ��������, ��� ��� ����������� �� �������
	//		����� � ���������� ������ ���� ������ ��������������� ������� �������������, ��� 2-�� ���������� �������� �� ������� ���� �� �����
	//		��  theApp.DivDetectors[0...n][]  ���������� ������� ���  theApp.FullDivision[1...n][] 
	//theApp.DivSortDetectors.clear();
	std::vector<std::vector<CString>> TestDivSortDetectors; // ������� ���������� �� XML-�����, ������� ������� �� �������� �� �������, � �� ���������� ��� ��������, ��� ��� ���� �� �������
	TestDivSortDetectors = theApp.DivDetectors; // ELSE // �� ���� ������� ������ �� ������ � ELSE
	if(theApp.FullDivision.size() > 1)
	{
		CString TmpStr("");
		UINT nDivSortDetectorsNum = TestDivSortDetectors.size();
		std::vector<CString> OneDetector;
		for(UINT i(0); i<nDivSortDetectorsNum; i++)
		{	// DIV_DET_NAME // DIV_DET_NUMBER
			bool bDetectorFound(false);
			UINT nDivDetectorsNum = theApp.FullDivision.size();
			for(UINT j(DIV_DET_HEAD); j<nDivDetectorsNum; j++)
			{
				/*
				CString sTmp("");
				sTmp = TestDivSortDetectors[i][DET_NAME];
				TestDivSortDetectors[i][DET_NAME] = TestDivSortDetectors[i][DET_NUMBER]; 
				TestDivSortDetectors[i][DET_NUMBER] = sTmp; 
				*/
				//CString a = TestDivSortDetectors[i][DET_NAME];
				//CString b = theApp.FullDivision[j][DIV_DET_NAME];

				if(TestDivSortDetectors[i][DET_NAME] == theApp.FullDivision[j][DIV_DET_NAME])
				{
					bDetectorFound=true;
					break;
				}
			}

			if( !bDetectorFound )
			{
				// ������� ��� ������������� � ����������� ������� ������
				OneDetector.push_back( TestDivSortDetectors[i][DET_NAME] );
				//OneDetector.push_back(DivDetGRAN);
				OneDetector.push_back( TestDivSortDetectors[i][DET_NUMBER] );
				OneDetector.push_back( _T("1") );
				OneDetector.push_back( TestDivSortDetectors[i][DET_FILE_PATH]	);
				OneDetector.push_back( TestDivSortDetectors[i][DET_POSTFIX]		);
				OneDetector.push_back( TestDivSortDetectors[i][DET_DISTANCE]	);
				OneDetector.push_back( _T("0.010") );
				OneDetector.push_back( _T("0.5") );
				OneDetector.push_back( TestDivSortDetectors[i][DET_BEGIN_NAME]	);
				OneDetector.push_back( TestDivSortDetectors[i][DET_END_NAME]	);


				theApp.FullDivision.push_back( OneDetector );
				OneDetector.clear();
			}
		}
	}
	else // ELSE // � ������ ���� �� ������� ��� ��������, �� ������ ��������� ��������������� �� �������� ������� ��� �������� �� XML-�����
	{
		CString TmpStr("");
		UINT nDivSortDetectorsNum = TestDivSortDetectors.size();
		std::vector<CString> OneDetector;
		for(UINT i=0; i < nDivSortDetectorsNum; i++)
		{
			OneDetector.push_back( TestDivSortDetectors[i][DET_NAME] );
			//OneDetector.push_back(DivDetGRAN);
			OneDetector.push_back( TestDivSortDetectors[i][DET_NUMBER] );
			OneDetector.push_back( _T("1") );
			OneDetector.push_back( TestDivSortDetectors[i][DET_FILE_PATH]	);
			OneDetector.push_back( TestDivSortDetectors[i][DET_POSTFIX]		);
			OneDetector.push_back( TestDivSortDetectors[i][DET_DISTANCE]	);
			OneDetector.push_back( _T("0.010") );
			OneDetector.push_back( _T("0.5") );
			OneDetector.push_back( TestDivSortDetectors[i][DET_BEGIN_NAME]	);
			OneDetector.push_back( TestDivSortDetectors[i][DET_END_NAME]	);


			theApp.FullDivision.push_back( OneDetector );
			OneDetector.clear();
		}
	}


	/////////////////////////////////////////////////////////////////////////////
	// 2 // ����� ��������� ���� ���������� �������, ���� ��� ��������� ����������� �� � ������� �� �������� ��������
	/*
	if(theApp.FullDivision.size()>2) // ������ � ������� + ����� ������ �������
	{
		std::vector<long> AllDetectorsNums;
		std::vector<CString> AllDetectorsSysNames;
		for(long i=1, j=0; i<theApp.FullDivision.size(); i++)
		{
			for(j=0; j<theApp.AllDetectors.size();j++)
			{
				if(theApp.AllDetectors[j][DET_NUMBER] == theApp.FullDivision[i][DIV_DET_NUMBER]) // IMPORTANT
				{break;}
			}

			//AllDetectorsNums.push_back( _tstol(NewFullDivision[i][0]) );
			AllDetectorsNums.push_back(	 _tstol(theApp.AllDetectors[j][DET_NUMBER]) );
			AllDetectorsSysNames.push_back( theApp.AllDetectors[j][DET_NAME] );
		}

		// ��������� ��� ������ � �������� �������� ������� ����������� ���������:
		// ����������
		for (long i=0; i < AllDetectorsNums.size(); i++)
		{	// ������ ��������������� � ����� �� ������� i � "������ �������� ���������"
			for (long j = AllDetectorsNums.size()-1; j > i; j--)
			{	// ���� �������� �������� ����������� � ������������ �������, �� ������ �� �������
				if (AllDetectorsNums[j] < AllDetectorsNums[j-1])
				{
					std::swap(AllDetectorsNums[j], AllDetectorsNums[j-1]);
					std::swap(AllDetectorsSysNames[j], AllDetectorsSysNames[j-1]);
				}
			}
		}

		// ������ � �������� � ������� ������������
		theApp.FullDivision.clear();
		theApp.FullDivision.insert( theApp.FullDivision.begin(), theApp.FullDivision[0] );
		for(long i=0; i<AllDetectorsNums.size(); i++)
		{
			for(long j=1; j<theApp.FullDivision.size(); j++)
			{
				if( AllDetectorsNums[i] == _tstol(theApp.FullDivision[j][DIV_DET_NUMBER]) )
					theApp.FullDivision.push_back( theApp.FullDivision[j] );
			}
		}

	}

	//if( (theApp.FullDivision.size()==1) && (theApp.FullDivision.size()==2) )
	//{theApp.FullDivision.push_back(NewDetector);}
	//*/

	//*

	// �������� ������� ����� �������
	std::vector<CString> DivisionHead;
	DivisionHead = theApp.FullDivision[DIV_DIV_HEAD]; // ��������� ������ ������� � "������", ����� ��� �� �������� ��� ����������
	theApp.FullDivision.erase(theApp.FullDivision.begin() + DIV_DIV_HEAD);


	std::vector<UINT> FullDivisionDetectorsNumbers;
	UINT nDivDetectorsNum = theApp.FullDivision.size();
	for(UINT i(0); i<nDivDetectorsNum; i++)
	{FullDivisionDetectorsNumbers.push_back( _wtoi( theApp.FullDivision[i][DIV_DET_NUMBER] ) );}

	std::sort(FullDivisionDetectorsNumbers.begin(), FullDivisionDetectorsNumbers.end());

	UINT nSortDivDetectorsNumbers = FullDivisionDetectorsNumbers.size();
	for(UINT i(0); i<nSortDivDetectorsNumbers; i++)
	{
		for(UINT j(0); j<nDivDetectorsNum; j++)
		{
			if(FullDivisionDetectorsNumbers[i] == _wtoi( theApp.FullDivision[j][DIV_DET_NUMBER]) )
			{
				std::vector<CString> Tmp_Vec;
				Tmp_Vec = theApp.FullDivision[j];
				theApp.FullDivision.erase(theApp.FullDivision.begin() + j);
				theApp.FullDivision.insert(theApp.FullDivision.begin() + i, Tmp_Vec);
				break;
			}
		}
		//FullDivisionDetectorsNumbers.push_back(theApp.FullDivision[i][DIV_DET_NUMBER]);
	}
	FullDivisionDetectorsNumbers.clear();
	//*/

	// ���������� ����� ������� � �������
	theApp.FullDivision.insert(theApp.FullDivision.begin(), DivisionHead);
	DivisionHead.clear();


	///////////////////////////////////////////////////////////////////////////////////////////
	// ��� �������� ���������� ���������� ���� ������ ����� ����� �������� �٨ ��������
	///////////////////////////////////////////////////////////////////////////////////////////
	if(TestDivSortDetectors.size() > 0)
	{
		if(theApp.MaxDetectors > 0)
		{
			if(m_ListDiv_Det.GetItemCount() < theApp.MaxDetectors)
			{
				// 1 // ������ ����� ���� �������� ��� ������ ���� ����� �����, ��� ������ ������ "��������"
				theApp.EditDivDetBtnClicked = theApp.DET_BTN_ADD_ALL;
				// 2 // ��������� ��� ������ (+������ ��������) �� ��� ��� ���� ������������ �� �������� �������� � ��������� ��������
			}
			else
			{AfxMessageBox(
				_T("����� �������� ������������� �� ���� ������� �� ����� ���� ������ ") + LintToCStr(theApp.MaxDetectors));
			}
		}
		else
		{		// 1 // ������ ����� ���� �������� ��� ������ ���� ����� �����, ��� ������ ������ "��������"
				theApp.EditDivDetBtnClicked = theApp.DET_BTN_ADD_ALL;
		}
	}
	else
	{
		if(theApp.AllDetectors.size() > 0)
		{
			AfxMessageBox(_T("��� ��������� ������� ��� ������� ��������, ���������� �� ������� �������, �������������! ")
						  _T("�������� ��������� ��� ���������� ������ �� ��������."));
		}
		else
		{
			AfxMessageBox(_T("�� ������� ������� XML-���� � ���������!\n\n")
						  _T("���������:\n")
						  _T("1) ����� �� ������ ���� � ����� �� ������� ��������.\n")
						  _T("2) ���������� �� ��� ���� �� ������� ����.\n")
						  _T("3) ������� �� ��������� XML-���� ��� ������."));
		}
	}


	///////////////////////////////////////////////////////////////////////////////////////////
	// ��������� ����-���� �� ������� ���������� ��� �������
	///////////////////////////////////////////////////////////////////////////////////////////
	m_ListDiv_Det.EnableWindow(TRUE);
	m_ListDiv_Det.DeleteAllItems(); // �������������� ���������� ������

	//CRect rect;
	//m_ListDiv_Det.GetClientRect(rect);
	(void)m_ListDiv_Det.SetExtendedStyle( LVS_EX_FULLROWSELECT );
	//m_ListDiv_Det.m_ListDiv_Det.SetHeadings( _T("� ����� ���������,		60;\
	//								�������� ������� �� �������,") + LintToCStr(rect.Width())
	//						 );
	//m_ListDiv_Det.LoadColumnInfo();

	//*
	// ��������� ������ ���������� �������� ��������� �������� ������ .sou �� ����� "�������"
	long NumOfDet(0);
	long NumOfDetParams(0);
	if(theApp.FullDivision.size()>1)
	{ 
		NumOfDet = theApp.FullDivision.size() - 1;		// NumOfDet = ����� �������� (�������� ������ ������ � ����������� �������) 
		NumOfDetParams = theApp.FullDivision[DIV_DET_HEAD].size();	// NumOfDetParams = ����� ���������� ��������
	
		for(UINT i(DIV_DET_HEAD), j(DET_HEAD); j < NumOfDet; i++, j++)
		{
			/*
			m_ListDiv_Det.InsertItem(j, theApp.FullDivision[i][DIV_DET_NUMBER]); // � 1-�� ������� ��� ������� � ������� // ����� �������
			// ��� ��� ��� ����� ������:
			m_ListDiv_Det.SetItemText(j, 0, theApp.FullDivision[i][DIV_DET_NUMBER]); // � 1-�� ������� ��� ������� � ������� // ����� �������
			m_ListDiv_Det.SetItemText(j, 1, theApp.FullDivision[i][DIV_DET_NAME]); // �� 2-�� ������ �������� ������� �� ������� // �������� �������
			*/

			(void)m_ListDiv_Det.AddItem(
										theApp.FullDivision[i][DIV_DET_NUMBER],
										theApp.FullDivision[i][DIV_DET_NAME]
									 );
		}
		m_ListDiv_Det.SetExtendedStyle( m_ListDiv_Det.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	}
	
	// 3 // ���� ������ ��������� �� "��������� ����� ������", �� ����� ����� ��������� ��� ��������� ������.
	if(m_ListDiv_Det.GetItemCount()>0)
	{
		m_ListDiv_Det.EnableWindow(TRUE);
		m_BtnDiv_DetAddAll.EnableWindow(FALSE);
		m_BtnDiv_DetAdd.EnableWindow(FALSE);
		m_BtnDiv_DetDel.EnableWindow(TRUE);
		m_BtnDiv_DetChange.EnableWindow(TRUE);
		m_BtnDiv_DetLook.EnableWindow(TRUE);

		m_BtnDivExit.EnableWindow(TRUE);
	}
	else
	{
		m_ListDiv_Det.EnableWindow(FALSE);
		m_BtnDiv_DetAddAll.EnableWindow(TRUE);
		m_BtnDiv_DetAdd.EnableWindow(TRUE);
		m_BtnDiv_DetDel.EnableWindow(FALSE);
		m_BtnDiv_DetChange.EnableWindow(FALSE);
		m_BtnDiv_DetLook.EnableWindow(FALSE);

		m_BtnDivExit.EnableWindow(TRUE);
	}


	// ��������� ��� ������ "��������� ���", ��� � ������ "��������"
	m_BtnDiv_DetAddAll.EnableWindow(FALSE);;
	m_BtnDiv_DetAdd.EnableWindow(FALSE);

	if(bFirstDlg)
		ChecckForBtnSave(); // ��������� ����� �� ������������ ������ "���������"

}


// ������ "�������� ������" � ��������� �������
void CDivisionEdit::OnBnClickedDivDetChangeBtn()
{
	// TODO: �������� ���� ��� ����������� �����������
	// 0 // � ������ � "��������" ��� ����� �������� ��� ���������� ������� � ���������, ��� ������ ������ � ��������.
	// 1 // ��������� ��� ���������� �������, ����� ������������ ��� � ���� �������������� �������
	CString EmptyStr("");
	long nCount=0;		// ����� ������� � Listbox
	long curIndex=0;	// ������ �������� ���������� � Listbox
	POSITION pos=NULL;	// ����� ���������� �������� (pos = curIndex+1)

	nCount = m_ListDiv_Det.GetItemCount();
	//����� ���������� ������� �� ������ �����������
	pos = m_ListDiv_Det.GetFirstSelectedItemPosition();
	if(pos==NULL) return;	 // � ������, ���� ������ �� �������:
							// 1) �� ��������� ���� �������������� �������
							// 2) �� ��������� �� ���� �� ������

	curIndex = m_ListDiv_Det.GetNextSelectedItem(pos);
	if( curIndex == (-1) )  return;

	CString sDetSysName = m_ListDiv_Det.GetItemText(curIndex,0);	// 1 �������
	CString sDetGrafName = m_ListDiv_Det.GetItemText(curIndex,1);	// 2 �������
	//CString sDetNum = m_ListDiv_Det.GetItemText(curIndex,0);	// 1 �������
	//CString sDetName = m_ListDiv_Det.GetItemText(curIndex,1);	// 2 �������

	// 1.1 // ������ ����� ���� �������� ��� ������ ���� ����� ����� ����� � ��� �������� �������
	theApp.CurDetSysName = sDetSysName;
	theApp.CurDetGrafName = sDetGrafName;
	//theApp.CurDetNum = sDetNum;
	//theApp.CurDetName = sDetName;
	// 1.2 // ������ ����� ���� �������� ��� ������ ���� ����� �����, ��� ������ ������ "��������"
	theApp.EditDivDetBtnClicked = theApp.DET_BTN_CHANGE;

	// 2 // ��������� ��� ������ (+������ ��������) �� ��� ��� ���� ������������ �� �������� �������� � ��������� ��������
	m_ListDiv_Det.EnableWindow(FALSE);
	m_BtnDiv_DetAddAll.EnableWindow(FALSE);
	m_BtnDiv_DetAdd.EnableWindow(FALSE);
	m_BtnDiv_DetDel.EnableWindow(FALSE);
	m_BtnDiv_DetChange.EnableWindow(FALSE);
	m_BtnDiv_DetLook.EnableWindow(FALSE);
	m_BtnDivSave.EnableWindow(FALSE);
	m_BtnDivExit.EnableWindow(FALSE);

	// 3 // ��������� ���� ��� ������������� �������
	CDetectorsEdit* p_DetectorsEditDlg = new CDetectorsEdit;
	p_DetectorsEditDlg->Create(IDD_EDIT_DETECTOR_DLG, this);
	p_DetectorsEditDlg->ShowWindow(SW_SHOW);
	
	DetectorDlgHWND = p_DetectorsEditDlg->GetSafeHwnd();
}


// ������ "����������� ������" � ��������� �������
void CDivisionEdit::OnBnClickedDivDetLookBtn()
{
	// TODO: �������� ���� ��� ����������� �����������
	// 0 // � ������ � "��������" ��� ����� �������� ��� ���������� ������� � ���������, ��� ������ ������ � ��������.
	// 1 // ��������� ��� ���������� �������, ����� ������������ ��� � ���� �������������� �������
	CString EmptyStr("");
	long nCount=0;		// ����� ������� � Listbox
	long curIndex=0;	// ������ �������� ���������� � Listbox
	POSITION pos=NULL;	// ����� ���������� �������� (pos = curIndex+1)

	nCount = m_ListDiv_Det.GetItemCount();
	//����� ���������� ������� �� ������ �����������
	pos = m_ListDiv_Det.GetFirstSelectedItemPosition();
	if(pos==NULL) return;	 // � ������, ���� ������ �� �������:
							// 1) �� ��������� ���� �������������� �������
							// 2) �� ��������� �� ���� �� ������
	curIndex = m_ListDiv_Det.GetNextSelectedItem(pos);
	if( curIndex == (-1) )  return;


	CString sDetSysName = m_ListDiv_Det.GetItemText(curIndex,0);	// 1 �������
	CString sDetGrafName = m_ListDiv_Det.GetItemText(curIndex,1);	// 2 �������
	//CString sDetNum = m_ListDiv_Det.GetItemText(curIndex,0);	// 1 �������
	//CString sDetName = m_ListDiv_Det.GetItemText(curIndex,1);	// 2 �������

	// 1.1 // ������ ����� ���� �������� ��� ������ ���� ����� ����� ��� ������� � ������� � ��� ������� �� ������� //����� � ��� �������� �������
	theApp.CurDetSysName = sDetSysName;
	theApp.CurDetGrafName = sDetGrafName;
	//theApp.CurDetNum = sDetNum;
	//theApp.CurDetName = sDetName;
	// 1.2 // ������ ����� ���� �������� ��� ������ ���� ����� �����, ��� ������ ������ "��������"
	theApp.EditDivDetBtnClicked = theApp.DET_BTN_LOOK;

	// 2 // ��������� ��� ������ �� ��� ��� ���� ������������ �� �������� �������� � ��������� ��������
	//m_ListDiv_Det.EnableWindow(FALSE);
	//(������ ��������) ��������� ���������, ����� � �� ������������ ����� ���� �� ������������� ����� ������ ������ �� ������� � ������
	m_BtnDiv_DetAddAll.EnableWindow(FALSE);
	m_BtnDiv_DetAdd.EnableWindow(FALSE);
	m_BtnDiv_DetDel.EnableWindow(FALSE);
	m_BtnDiv_DetChange.EnableWindow(FALSE);
	m_BtnDiv_DetLook.EnableWindow(FALSE);
	m_BtnDivSave.EnableWindow(FALSE);
	m_BtnDivExit.EnableWindow(FALSE);

	// 3 // ��������� ���� ��� ������������� �������
	CDetectorsEdit* p_DetectorsEditDlg = new CDetectorsEdit;
	p_DetectorsEditDlg->Create(IDD_EDIT_DETECTOR_DLG, this);
	p_DetectorsEditDlg->ShowWindow(SW_SHOW);

	DetectorDlgHWND = p_DetectorsEditDlg->GetSafeHwnd();
}


// ������� �� ������ "���������" �� ���� "��������� ������"
LRESULT CDivisionEdit::OnDetectorEditSave( WPARAM wparam , LPARAM lparam )
{
	// 1 // �� ������� �� ������ "���������" ��� ����� � ������������ � ����� ��������� ������� ��������������� ��������� � ��� ������: theApp.DivDetectors  (theApp.DivSortDetectors ����������� ������ � DetectorsEdit.cpp)
	// ��� ��� ���������� �� ����������, ��� ��� ��� ��������� �������, �� XML-����� ���������� ��� ������� �������, ��� ��������������� ������ �� ������-�� ��������

	// 2 // ���� �� ������ ��������� �� � �������, � �� � ����� .sou
		 // �� ������ � ��������� ��� ���� ����� ������������� ��� ������
	CString DetectorName(""); // ��� ���������� �������

	m_ListDiv_Det.EnableWindow(TRUE);
	m_ListDiv_Det.DeleteAllItems(); // �������������� ���������� ������

	//CRect rect;
	//m_ListDiv_Det.GetClientRect(rect);
	(void)m_ListDiv_Det.SetExtendedStyle( LVS_EX_FULLROWSELECT );
	//m_ListDiv_Det.SetHeadings( _T("� ����� ���������,		60;\
	//								�������� ������� �� �������,") + LintToCStr(rect.Width())
	//						 );
	//m_ListDiv_Det.LoadColumnInfo();

	//*
	// ��������� ������ ���������� �������� ��������� �������� ������ .sou �� ����� "�������"
	long NumOfDet=0;
	long NumOfDetParams=0;
	if(theApp.FullDivision.size()>1)
	{ 
		NumOfDet = theApp.FullDivision.size() - 1;		// NumOfDet = ����� �������� (�������� ������ ������ � ����������� �������) 
		NumOfDetParams = theApp.FullDivision[DIV_DET_HEAD].size();	// NumOfDetParams = ����� ���������� ��������
	
		for(UINT i(DIV_DET_HEAD), j(DET_HEAD); j < NumOfDet; i++, j++)
		{
			/*
			m_ListDiv_Det.InsertItem(j, theApp.FullDivision[i][DIV_DET_NUMBER]); // � 1-�� ������� ��� ������� � ������� // ����� �������
			// ��� ��� ��� ����� ������:
			m_ListDiv_Det.SetItemText(j, 0, theApp.FullDivision[i][DIV_DET_NUMBER]); // � 1-�� ������� ��� ������� � ������� // ����� �������
			m_ListDiv_Det.SetItemText(j, 1, theApp.FullDivision[i][DIV_DET_NAME]); // �� 2-�� ������ �������� ������� �� ������� // �������� �������
			*/

			(void)m_ListDiv_Det.AddItem(
										theApp.FullDivision[i][DIV_DET_NUMBER],
										theApp.FullDivision[i][DIV_DET_NAME]
									 );
		}
		m_ListDiv_Det.SetExtendedStyle( m_ListDiv_Det.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	}
	

	// 3 // ���� ������ ��������� �� "��������� ����� ������", �� ����� ����� ��������� ��� ��������� ������.
	UINT nTestDivSortDetectorsNum = theApp.DivDetectors.size();		// ����� ��������, ���������� ��� ������� �������
	UINT nCurDivisionDetectorsNum = theApp.FullDivision.size() - 1;	// ����� �������� ������������� �� ������� (�������� ������ ������ � ����������� �������) 

	if(m_ListDiv_Det.GetItemCount()>0)
	{
		m_ListDiv_Det.EnableWindow(TRUE);
		if(nCurDivisionDetectorsNum >= nTestDivSortDetectorsNum)
		{
			m_BtnDiv_DetAddAll.EnableWindow(FALSE);
			m_BtnDiv_DetAdd.EnableWindow(FALSE);
		}
		else
		{
			m_BtnDiv_DetAddAll.EnableWindow(TRUE);
			m_BtnDiv_DetAdd.EnableWindow(TRUE);
		}
		m_BtnDiv_DetDel.EnableWindow(TRUE);
		m_BtnDiv_DetChange.EnableWindow(TRUE);
		m_BtnDiv_DetLook.EnableWindow(TRUE);

		m_BtnDivExit.EnableWindow(TRUE);
	}
	else
	{
		m_ListDiv_Det.EnableWindow(FALSE);
		if(nCurDivisionDetectorsNum >= nTestDivSortDetectorsNum)
		{
			m_BtnDiv_DetAddAll.EnableWindow(FALSE);
			m_BtnDiv_DetAdd.EnableWindow(FALSE);
		}
		else
		{
			m_BtnDiv_DetAddAll.EnableWindow(TRUE);
			m_BtnDiv_DetAdd.EnableWindow(TRUE);
		}
		m_BtnDiv_DetDel.EnableWindow(FALSE);
		m_BtnDiv_DetChange.EnableWindow(FALSE);
		m_BtnDiv_DetLook.EnableWindow(FALSE);

		m_BtnDivExit.EnableWindow(TRUE);
	}

	if(bFirstDlg)
		ChecckForBtnSave(); // ��������� ����� �� ������������ ������ "���������"

	return 0;
}


// ������� �� ������ "�����" �� ���� "��������� ������"
LRESULT CDivisionEdit::OnDetectorEditExit( WPARAM wparam , LPARAM lparam )
{
	// ���� ������ ��������� �� "����� �� �������", �� ����� ��������� ����� �� ��������� ��� ��������� ������.
	// ��������� �� ����� ���������, ����������� � ������
	UINT nTestDivSortDetectorsNum = theApp.DivDetectors.size();		// ����� ��������, ���������� ��� ������� �������
	UINT nCurDivisionDetectorsNum = theApp.FullDivision.size() - 1;	// ����� �������� ������������� �� ������� (�������� ������ ������ � ����������� �������) 

	if(m_ListDiv_Det.GetItemCount()>0)
	{
		m_ListDiv_Det.EnableWindow(TRUE);
		if(nCurDivisionDetectorsNum >= nTestDivSortDetectorsNum)
		{
			m_BtnDiv_DetAddAll.EnableWindow(FALSE);
			m_BtnDiv_DetAdd.EnableWindow(FALSE);
		}
		else
		{
			m_BtnDiv_DetAddAll.EnableWindow(TRUE);
			m_BtnDiv_DetAdd.EnableWindow(TRUE);
		}
		m_BtnDiv_DetDel.EnableWindow(TRUE);
		m_BtnDiv_DetChange.EnableWindow(TRUE);
		m_BtnDiv_DetLook.EnableWindow(TRUE);

		m_BtnDivExit.EnableWindow(TRUE);
	}
	else
	{
		m_ListDiv_Det.EnableWindow(FALSE);
		if(nCurDivisionDetectorsNum >= nTestDivSortDetectorsNum)
		{
			m_BtnDiv_DetAddAll.EnableWindow(FALSE);
			m_BtnDiv_DetAdd.EnableWindow(FALSE);
		}
		else
		{
			m_BtnDiv_DetAddAll.EnableWindow(TRUE);
			m_BtnDiv_DetAdd.EnableWindow(TRUE);
		}
		m_BtnDiv_DetDel.EnableWindow(FALSE);
		m_BtnDiv_DetChange.EnableWindow(FALSE);
		m_BtnDiv_DetLook.EnableWindow(FALSE);

		m_BtnDivExit.EnableWindow(TRUE);
	}

	// ������ ���� ��� ���� ���������� ������, ����� �� ����� � "��������� �������" -> "�������� �������" -> ����� �� �������
	// � ���� ������ ��� ��� ������� ����� ��������� �� ����� ����� ����������� �� ����� ������ "�������� �������" � "�����"
	if(theApp.ChangeDivBtnClicked == theApp.DIV_BTN_LOOK)
	{
		m_BtnDiv_DetAddAll.EnableWindow(FALSE);
		m_BtnDiv_DetAdd.EnableWindow(FALSE);
		m_BtnDiv_DetDel.EnableWindow(FALSE);
		m_BtnDiv_DetChange.EnableWindow(FALSE);
		m_BtnDiv_DetLook.EnableWindow(TRUE);
		
		m_BtnDivSave.EnableWindow(FALSE); // ��� ��� ��������� ������
		m_BtnDivExit.EnableWindow(TRUE);
	}
	else
	{
		if(bFirstDlg) 
			ChecckForBtnSave(); // ��������� ����� �� ������������ ������ "���������"
	}

	return 0;
}



// ������ "��������� �������" ��������, �����: 1) ������� ��� ������� 2) ������� ������� �� ������� 3) ���������� "��������" = "��������" 3) �� ������� ���������� ������ 1 ������
void CDivisionEdit::ChecckForBtnSave()
{
	CString EmptyStr("");
	CString CurDivisionFName("");
	CString CurDivisionName("");
	CString CurDivisionPipe("");
	CString CurDivisionProd("");
////	CString CurDivisionParam("");
	CString Preassure("��������");
	long CurDivisionDet=0;


	m_EditDivFileName.GetWindowText(CurDivisionFName);
	m_EditDivName.GetWindowText(CurDivisionName);
	int curIndex(0);			// ������ �������� ���������� � Combobx
	curIndex = m_CmBxDivProd.GetCurSel();
	if(curIndex != (-1))	m_CmBxDivProd.GetLBText( curIndex, CurDivisionProd );
	curIndex = m_CmBxDivPipe.GetCurSel();
	if(curIndex != (-1))	m_CmBxDivPipe.GetLBText( curIndex, CurDivisionPipe );


////	m_EditDivParam.GetWindowText(CurDivisionParam);
	int nCount=0;			// ����� ������� � Listbox
	nCount = m_ListDiv_Det.GetItemCount();
	// ��� �� ���������� �������� �� ����������� ����������� ������ � ���������:
	//if(nCount>0)
	//	m_CmBxDivProd.EnableWindow(FALSE);
	//else
	//	m_CmBxDivProd.EnableWindow(FALSE); //m_CmBxDivProd.EnableWindow(TRUE);

//	���� �������� ������� ���� �� ���������� � ����� ������������ �� ��������� ��������� � ����� ���������� �����/�������.


	if(		(!CurDivisionFName.IsEmpty() )
		 && (!CurDivisionName.IsEmpty() )
		 && (!CurDivisionPipe.IsEmpty() )
		 && (!CurDivisionProd.IsEmpty() )
////		 && (!CurDivisionParam.IsEmpty() )
		 && (nCount > 0)
	  )
	{m_BtnDivSave.EnableWindow(TRUE);}
	else
	{m_BtnDivSave.EnableWindow(FALSE);}

}

//*	
/////////////////////////////////////////////////////////////////
//////////////////// ������ ������

// #include <io.h>
// ������� _findfirst ���������� ���������� � ������ �����, ��������������� �������� ����� ������.
bool CDivisionEdit::FileExists(const wchar_t *fname)
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


CString CDivisionEdit::LintToCStr(long int x)
{
	CString strX;
	strX.Format( _T("%i"), x ); //%i for int // %d for ?? // %l for long
	return strX;
}


void CDivisionEdit::OnEnSetfocusDivNameEdit()
{
	// TODO: �������� ���� ��� ����������� �����������
	//if(theApp.ChangeDivBtnClicked == theApp.DIV_BTN_ADD) // ������ ������ "�������� �������"
	//{FirstFileNameSFocus=false;}
}


void CDivisionEdit::OnEnKillfocusDivNameEdit()
{
	// TODO: �������� ���� ��� ����������� �����������
	//if(theApp.ChangeDivBtnClicked == theApp.DIV_BTN_ADD) // ������ ������ "�������� �������"
	//{
	//	if(FirstFileNameSFocus)
	//	FirstFileNameKFocus=false;
	//}
}


void CDivisionEdit::OnEnSetfocusDivFileNameEdit()
{
	// TODO: �������� ���� ��� ����������� �����������
	//if(theApp.ChangeDivBtnClicked == theApp.DIV_BTN_ADD) // ������ ������ "�������� �������"
	//{FirstNameSFocus=false;}
}


void CDivisionEdit::OnEnKillfocusDivFileNameEdit()
{
	// TODO: �������� ���� ��� ����������� �����������
	//if(theApp.ChangeDivBtnClicked == theApp.DIV_BTN_ADD) // ������ ������ "�������� �������"
	//{
	//	if(FirstNameSFocus)
	//	FirstNameKFocus=false;
	//}
}


BOOL CDivisionEdit::PreTranslateMessage(LPMSG pMsg)
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


CString CDivisionEdit::DoubleToCStr(double x, int count) // x - �����, count - ����� ������ ����� �������
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



bool CDivisionEdit::CheckString(CString& StrToCheck)
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

// �������� �� 100.000 �����, +����� �������� ��������� ��������
bool CDivisionEdit::CheckFileNameCopyString(CString& StrToCheck, long Next)
{
	CString OrigString=StrToCheck;
	CString ResString("");		    // 123456789112
	CString CopyAdd(" - ����� (1)");// _-_�����_(1)
	CString CopyNum("");
	bool OriginalCheck1=false;
	bool OriginalCheck2=false;
	//LintToCStr

	if(StrToCheck.GetLength() <=8)
	{
		if(Next==1)
		ResString = OrigString + CopyAdd;
	}
	//if(StrToCheck.GetLength() == 8)
	//{
	//	if(OrigString == CopyAdd)
	//	{ResString = CopyAdd + _T(" (1)");}
	//	else
	//	{ResString = OrigString + CopyAdd;}
	//}
	if(StrToCheck.GetLength() > 8)
	{	 
		if(	( StrToCheck[StrToCheck.GetLength() - 1] == (CString)"�" ) &&
			( StrToCheck[StrToCheck.GetLength() - 2] == (CString)"�" ) &&
			( StrToCheck[StrToCheck.GetLength() - 3] == (CString)"�" ) &&
			( StrToCheck[StrToCheck.GetLength() - 4] == (CString)"�" ) &&
			( StrToCheck[StrToCheck.GetLength() - 5] == (CString)"�" ) &&
			( StrToCheck[StrToCheck.GetLength() - 6] == (CString)" " ) &&
			( StrToCheck[StrToCheck.GetLength() - 7] == (CString)"-" ) &&
			( StrToCheck[StrToCheck.GetLength() - 8] == (CString)" " )
		  )
		{
			if(Next==1)
			ResString = OrigString + _T(" (1)");
		}
		else
		{OriginalCheck1=true;}

		if( StrToCheck[StrToCheck.GetLength() - 1] == ')' )
		{
			for(long i=0, j=0 ;; i++)
			{
				CopyNum = LintToCStr(i);
				if(i<10)
				{
					j=1;
					if( (CString)StrToCheck[StrToCheck.GetLength() - (j+1)]  ==  (CString)CopyNum[j-1] )
					{
						if(	( StrToCheck[StrToCheck.GetLength() - (j+2)] == (CString)"(" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+3)] == (CString)" " ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+4)] == (CString)"�" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+5)] == (CString)"�" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+6)] == (CString)"�" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+7)] == (CString)"�" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+8)] == (CString)"�" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+9)] == (CString)" " ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+10)] == (CString)"-" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+11)] == (CString)" " )
						  )
						{
							for(long k=(j+1) ;k!=0; k--)
							{StrToCheck.Delete( StrToCheck.GetLength() - k, 1);}

							if( (i+1) == Next )
							{ResString = StrToCheck + LintToCStr(i+1) + _T(")");}
							else
							{ResString = StrToCheck + LintToCStr(Next) + _T(")");}

							break;
						}
					}
				}
				else if( (i>=10) && (i<100) )
				{
					j=2;
					if( ( StrToCheck[StrToCheck.GetLength() - (j+0)] == CopyNum[j-1] ) &&
						( StrToCheck[StrToCheck.GetLength() - (j+1)] == CopyNum[j-2] ) 
					  )
					{
						if(	( StrToCheck[StrToCheck.GetLength() - (j+2)] == (CString)"(" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+3)] == (CString)" " ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+4)] == (CString)"�" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+5)] == (CString)"�" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+6)] == (CString)"�" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+7)] == (CString)"�" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+8)] == (CString)"�" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+9)] == (CString)" " ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+10)] == (CString)"-" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+11)] == (CString)" " )
						  )
						{
							for(long k=(j+1) ;k!=0; k--)
							{StrToCheck.Delete( StrToCheck.GetLength() - k, 1);}

							if( (i+1) == Next )
							{ResString = StrToCheck + LintToCStr(i+1) + _T(")");}
							else
							{ResString = StrToCheck + LintToCStr(Next) + _T(")");}

							break;
						}
					}
				}
				else if( (i>=100) && (i<1000) )
				{
					j=3;
					if( ( StrToCheck[StrToCheck.GetLength() - (j-1)] == CopyNum[j-1] ) &&
						( StrToCheck[StrToCheck.GetLength() - (j+0)] == CopyNum[j-2] ) &&
						( StrToCheck[StrToCheck.GetLength() - (j+1)] == CopyNum[j-3] ) 
					  )
					{
						if(	( StrToCheck[StrToCheck.GetLength() - (j+2)] == (CString)"(" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+3)] == (CString)" " ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+4)] == (CString)"�" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+5)] == (CString)"�" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+6)] == (CString)"�" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+7)] == (CString)"�" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+8)] == (CString)"�" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+9)] == (CString)" " ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+10)] == (CString)"-" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+11)] == (CString)" " )
						  )
						{
							for(long k=(j+1) ;k!=0; k--)
							{StrToCheck.Delete( StrToCheck.GetLength() - k, 1);}

							if( (i+1) == Next )
							{ResString = StrToCheck + LintToCStr(i+1) + _T(")");}
							else
							{ResString = StrToCheck + LintToCStr(Next) + _T(")");}

							break;
						}
					}
				}
				else if( (i>=1000) && (i<10000) )
				{
					j=4;
					if( ( StrToCheck[StrToCheck.GetLength() - (j-2)] == CopyNum[j-1] ) &&
						( StrToCheck[StrToCheck.GetLength() - (j-1)] == CopyNum[j-2] ) &&
						( StrToCheck[StrToCheck.GetLength() - (j+0)] == CopyNum[j-3] ) &&
						( StrToCheck[StrToCheck.GetLength() - (j+1)] == CopyNum[j-4] ) 
					  )
					{
						if(	( StrToCheck[StrToCheck.GetLength() - (j+2)] == (CString)"(" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+3)] == (CString)" " ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+4)] == (CString)"�" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+5)] == (CString)"�" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+6)] == (CString)"�" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+7)] == (CString)"�" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+8)] == (CString)"�" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+9)] == (CString)" " ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+10)] == (CString)"-" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+11)] == (CString)" " )
						  )
						{
							for(long k=(j+1) ;k!=0; k--)
							{StrToCheck.Delete( StrToCheck.GetLength() - k, 1);}

							if( (i+1) == Next )
							{ResString = StrToCheck + LintToCStr(i+1) + _T(")");}
							else
							{ResString = StrToCheck + LintToCStr(Next) + _T(")");}

							break;
						}
					}
				}
				else if( (i>=10000) && (i<100000) )
				{
					j=5;
					if( ( StrToCheck[StrToCheck.GetLength() - (j-3)] == CopyNum[j-1] ) &&
						( StrToCheck[StrToCheck.GetLength() - (j-2)] == CopyNum[j-2] ) &&
						( StrToCheck[StrToCheck.GetLength() - (j-1)] == CopyNum[j-3] ) &&
						( StrToCheck[StrToCheck.GetLength() - (j+0)] == CopyNum[j-4] ) &&
						( StrToCheck[StrToCheck.GetLength() - (j+1)] == CopyNum[j-5] ) 
					  )
					{
						if(	( StrToCheck[StrToCheck.GetLength() - (j+2)] == (CString)"(" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+3)] == (CString)" " ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+4)] == (CString)"�" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+5)] == (CString)"�" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+6)] == (CString)"�" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+7)] == (CString)"�" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+8)] == (CString)"�" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+9)] == (CString)" " ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+10)] == (CString)"-" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+11)] == (CString)" " )
						  )
						{
							for(long k=(j+1) ;k!=0; k--)
							{StrToCheck.Delete( StrToCheck.GetLength() - k, 1);}

							if( (i+1) == Next )
							{ResString = StrToCheck + LintToCStr(i+1) + _T(")");}
							else
							{ResString = StrToCheck + LintToCStr(Next) + _T(")");}

							break;
						}
					}
				}
			}

			/*
			( StrToCheck[StrToCheck.GetLength() - 3] == '(' ) &&
			( StrToCheck[StrToCheck.GetLength() - 4] == ' ' ) &&
			( StrToCheck[StrToCheck.GetLength() - 5] == '�' ) &&
			( StrToCheck[StrToCheck.GetLength() - 6] == '�' ) &&
			( StrToCheck[StrToCheck.GetLength() - 7] == '�' ) &&
			( StrToCheck[StrToCheck.GetLength() - 8] == '�' ) &&
			( StrToCheck[StrToCheck.GetLength() - 9] == '�' ) &&
			( StrToCheck[StrToCheck.GetLength() - 10] == ' ' ) &&
			( StrToCheck[StrToCheck.GetLength() - 11] == '-' ) &&
			( StrToCheck[StrToCheck.GetLength() - 12] == ' ' )
			*/

		}
		else
		{OriginalCheck2=true;}
	}
	
	if( OriginalCheck1 && OriginalCheck2)
	{
		if( Next == 0 )
		{ResString = StrToCheck + CopyAdd;}
		else
		{ResString = StrToCheck + _T(" - ����� (") + LintToCStr(Next) + _T(")");}
	}

	StrToCheck = ResString;

	if(OrigString == ResString)
	{return true;} // ������ ������������
	else
	{return false;} // ������ ����������
}



// This OnSize function resizes one large control in a dialog. 
// The one control grows horizontally and vertically to fill the dialog. It's position remains unchanged.
// Other controls (buttons etc) would typically be above the one resizable control.
// How to add OnSize:
// [1] add to .h:                     afx_msg void OnSize(UINT nType, int cx, int cy);
// [2] add to message map in .cpp:    ON_WM_SIZE()
// [3] add this OnSize function.
void CDivisionEdit::OnSize(UINT nType, int formWidthArg, int formHeightArg)
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

			// ������ �������:	Edit-����� � ������ �������
			pWnd = GetDlgItem(IDC_DIV_NAME_EDIT);
			pWnd->GetWindowRect(&CurObjectRect);
			ScreenToClient(&CurObjectRect);
			m_EditDivName.MoveWindow( CurObjectRect.left	, CurObjectRect.top		, formWidthArg - CurObjectRect.left - 15	, CurObjectRect.Height()	);
		
			// ������ �������:	Edit-����� � ������ ����� �������
			pWnd = GetDlgItem(IDC_DIV_FILE_NAME_EDIT);
			pWnd->GetWindowRect(&CurObjectRect);
			ScreenToClient(&CurObjectRect);
			m_EditDivFileName.MoveWindow( CurObjectRect.left , CurObjectRect.top	, formWidthArg - CurObjectRect.left - 15	, CurObjectRect.Height()	);

			// ������ �������:	Static-����� ��� List-������ � ���������
			pWnd = GetDlgItem(IDC_DIV_DETECTORS_STATIC);
			pWnd->GetWindowRect(&CurObjectRect);
			ScreenToClient(&CurObjectRect);
			m_StaticDiv_Det.MoveWindow( CurObjectRect.left	, CurObjectRect.top		, formWidthArg - CurObjectRect.left - 15	, CurObjectRect.Height()	);
						
			// ������ �������:	List-����� � ���������
			pWnd = GetDlgItem(IDC_DIV_DETECTORS_LIST);
			pWnd->GetWindowRect(&CurObjectRect);
			ScreenToClient(&CurObjectRect);
			//position:  rect.left, rect.top
			//size: rect.Width(), rect.Height()

			LONG dObjx(CurObjectRect.left), dObjy(CurObjectRect.top), dObjw(formWidthArg - CurObjectRect.left), dObjh(formHeightArg - CurObjectRect.top);
			m_ListDiv_Det.MoveWindow( dObjx
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
			pWnd = GetDlgItem(IDC_DIV_DET_ADD_ALL_BTN);
			pWnd->GetWindowRect(&CurObjectRect);
			ScreenToClient(&CurObjectRect);
			m_BtnDiv_DetAddAll.MoveWindow( CurObjectRect.left	, formHeightArg - 30, CurObjectRect.Width()	, CurObjectRect.Height()	);

			// ������ �������:
			pWnd = GetDlgItem(IDC_DIV_ADD_BTN);
			pWnd->GetWindowRect(&CurObjectRect);
			ScreenToClient(&CurObjectRect);
			m_BtnDiv_DetAdd.MoveWindow( CurObjectRect.left	, formHeightArg - 30, CurObjectRect.Width()	, CurObjectRect.Height()	);

			// ������ �������:
			pWnd = GetDlgItem(IDC_DIV_DET_DELL_BTN);
			pWnd->GetWindowRect(&CurObjectRect);
			ScreenToClient(&CurObjectRect);
			m_BtnDiv_DetDel.MoveWindow( CurObjectRect.left	, formHeightArg - 30, CurObjectRect.Width()	, CurObjectRect.Height()	);

			// ������ �������:
			pWnd = GetDlgItem(IDC_DIV_DET_CHANGE_BTN);
			pWnd->GetWindowRect(&CurObjectRect);
			ScreenToClient(&CurObjectRect);
			m_BtnDiv_DetChange.MoveWindow( CurObjectRect.left	, formHeightArg - 30, CurObjectRect.Width()	, CurObjectRect.Height()	);

			// ������ �������:
			pWnd = GetDlgItem(IDC_DIV_DET_LOOK_BTN);
			pWnd->GetWindowRect(&CurObjectRect);
			ScreenToClient(&CurObjectRect);
			m_BtnDiv_DetLook.MoveWindow( CurObjectRect.left	, formHeightArg - 30, CurObjectRect.Width()	, CurObjectRect.Height()	);

			int u=0;
		}
		else
		{
		} // ������ ������ ��� �� ����������
	}
//#endif


#if 0

/*
template< typename T >
void sort( T array[], int size )   // ���������� � �����������
{
  T t;
  for (int i = 0; i < size - 1; i++)
    for (int j = size - 1; j > i; j--)
      if (array[j] < array[j-1])
      {
        t = array[j];
        array[j] = array[j-1];
        array[j-1] = t;
      }
}
*/

	if(bFirstDlg)
	{
		//AfxMessageBox(_T("111"));


		ScreenToClient(&rect); //optional step - see below
		//pDlg->ScreenToClient(&rect); //optional step - see below

		//position:  rect.left, rect.top
		//size: rect.Width(), rect.Height()

/*
		// get pointer to the control to be resized dynamically
	   CWnd* pCtl = GetDlgItem(IDC_MSFLEXGRID1);
 
	   if (!pCtl) { return; } // control may not exist yet.
 
	   CRect rectCtl;                 // Allocate CRect for control's position.
	   pCtl->GetWindowRect(&rectCtl); // Get control's position.
	   ScreenToClient(&rectCtl);      // Convert from absolute screen coordinates to dialog-relative coordinates.
 
	   // Now resize the control dynamically by calling MoveWindow
	   // rectCtl.left is assumed to be the left, bottom and right margin for the control. 
	   pCtl->MoveWindow(
		  rectCtl.left,                               // x. remains unchanged
		  rectCtl.top,                                // y. remains unchanged
		  formWidthArg - 2 * rectCtl.left,            // w. Grow to fill horizontally
		  formHeightArg - rectCtl.top - rectCtl.left, // h. Grow to fill vertically
		  TRUE)
	   ;
*/

		// x left	// y top
		// Width	// Height



		CRect rct(NULL);
		m_ListDiv_Det.GetClientRect(rct);

		//m_ListDiv_Det.MoveWindow(rct.left, rct.top, rct.Width(), rct.Height());
		m_ListDiv_Det.MoveWindow(rect.left, rect.top, formWidthArg-10, formHeightArg-40);

/*		LPRECT plrect;
		m_ListDiv_Det.GetInsertMarkRect(plrect);
		m_ListDiv_Det.GetViewRect(plrect);
		m_ListDiv_Det.Get
*/




/*
		LPRECT ListDiv_DetRect=NULL;
		m_ListDiv_Det.GetWindowRect(ListDiv_DetRect);
		
		long *a=NULL, *b=NULL, *c=NULL, *d=NULL;
		VARIANT varChild;
		m_ListDiv_Det.accLocation(a,b,c,d,varChild);


		int x1, y1, x2, y2;
		x1 = ListDiv_DetRect->left;
		y1 = ListDiv_DetRect->top;
		x2 = ListDiv_DetRect->bottom;
		y2 = ListDiv_DetRect->right;

		//m_ListDiv_Det.MoveWindow(ListDiv_DetRect->left);
*/

		int u=0;
	}
/*
//	m_EditDivFileName.SetRect();
	m_EditDivName;
	m_EditDivParam;
	m_EditDivWatch;
	m_CmBxDivWatch;
	m_EditDivWave;
	m_EditDivTimeDetect;

	m_ListDiv_Det;
	m_BtnDiv_DetAdd;
	m_BtnDiv_DetDel;
	m_BtnDiv_DetChange;
	m_BtnDiv_DetLook;
	
	m_BtnDivSave;
	m_BtnDivExit;
*/


/*
   // http://www.codersource.net/mfc_resize_controls.html
   // http://wwwusers.brookes.ac.uk/p0071643/resize.htm
 
   // get pointer to the control to be resized dynamically
   CWnd* pCtl = GetDlgItem(IDC_MSFLEXGRID1);
 
   if (!pCtl) { return; } // control may not exist yet.
 
   CRect rectCtl;                 // Allocate CRect for control's position.
   pCtl->GetWindowRect(&rectCtl); // Get control's position.
   ScreenToClient(&rectCtl);      // Convert from absolute screen coordinates to dialog-relative coordinates.
 
   // Now resize the control dynamically by calling MoveWindow
   // rectCtl.left is assumed to be the left, bottom and right margin for the control. 
   pCtl->MoveWindow(
      rectCtl.left,                               // x. remains unchanged
      rectCtl.top,                                // y. remains unchanged
      formWidthArg - 2 * rectCtl.left,            // w. Grow to fill horizontally
      formHeightArg - rectCtl.top - rectCtl.left, // h. Grow to fill vertically
      TRUE)
   ;
*/ 

#endif

	return;


} // OnSize()



/*
CString CDivisionEdit::DocErrorGetErrorInRus(CString DescriptionEng)
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




