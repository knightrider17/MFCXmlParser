// DivisionEdit.cpp: файл реализации
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

#define DET_HEAD		0 // для шапки в файле Датчиков
#define DIV_DIV_HEAD	0 // для шапки и инфы о самом Участке
#define DIV_DET_HEAD	1 // для второго элемента в векторе, который содержит инфу о датчике

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

// Заведено для theApp.AllDivisions
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

// диалоговое окно CDivisionEdit

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
	TitleDetector = theApp.AllDetectors[DET_HEAD]; // сохраняем первый элемент с "шапкой", чтобы она не мешалась при сортировке
	theApp.AllDetectors.erase(theApp.AllDetectors.begin() + DET_HEAD); // удалить из вектора первый элемент в котором шапка инфы о датчиках

	// Выбираем только неповторяющиеся имена Труб, что имеются среди всех Датчиков
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


	// После получения всех труб, получим для труб все доступные на каждую трубу продукты
	std::vector<CString> v_AllPipesProducts; // [0] - прод1,прод2,прод3 [1] - прод1,прод2,прод3
	for(UINT i(0); i<nPipeNum; i++)
	{	//DET_PIPE_SHNAME //DET_PIPE_ID	// DET_PROD_TYPE // DET_PROD_ID // DET_PROD_VIEW
		std::vector<CString> v_AllProducts;	 // [0] - прод1 [1] - прод2

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

		// Получив на одной трубе все её продукты фиксируем через запятую их
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


	theApp.AllDetectors.insert(theApp.AllDetectors.begin(), TitleDetector); // добавляем шапку обратно в начало
	TitleDetector.clear();


	// 2 // После получения всех параметров участка, зная эти параметры отсортируем всё в векторе по названию Участков
	//std::sort(v_AllPipes.begin(), v_AllPipes.end());

	// Помещаем полученный список Труб в Комбобокс
	m_CmBxDivPipe.Clear();

	// 1 // *Идентичные по результату куски кода
	switch(nPipeNum)
	{
	case 0:
		m_CmBxDivPipe.AddString(_T("НЕТ ДОСТУПНЫХ ТРУБ"));
		m_CmBxDivPipe.SetCurSel(0);
		m_CmBxDivPipe.EnableWindow(FALSE);
		break;
	case 1:
		m_CmBxDivPipe.AddString(v_AllPipes[v_AllPipes.size()-1]);
		m_CmBxDivPipe.SetCurSel(0);
		m_CmBxDivPipe.EnableWindow(FALSE);

		// Сразу же выведем отсортированный список Продуктов
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

	/*// 1 // *Идентичные по результату куски кода
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
		m_CmBxDivPipe.AddString(_T("НЕТ ДОСТУПНЫХ ТРУБ"));
		m_CmBxDivPipe.SetCurSel(0);
		m_CmBxDivPipe.EnableWindow(FALSE);
	}
	*/
}


void CDivisionEdit::SetProdsToCmBx()
{
	// Получим выбранную трубу
	//theApp.CurDivPipe

	std::vector<CString> TitleDetector;
	TitleDetector = theApp.AllDetectors[DET_HEAD]; // сохраняем первый элемент с "шапкой", чтобы она не мешалась при сортировке
	theApp.AllDetectors.erase(theApp.AllDetectors.begin() + DET_HEAD); // удалить из вектора первый элемент в котором шапка инфы о датчиках

	// После выбора трубы, получим для трубы все доступные на ней продукты
	UINT nDetNum( theApp.AllDetectors.size() );

	// Получив на одной трубе все её продукты помещаем их в КомбоБокс
	//DET_PIPE_SHNAME //DET_PIPE_ID	// DET_PROD_TYPE // DET_PROD_ID // DET_PROD_VIEW
	std::vector<CString> v_AllProducts;	 // [0] - прод1 [1] - прод2

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


	theApp.AllDetectors.insert(theApp.AllDetectors.begin(), TitleDetector); // добавляем шапку обратно в начало
	TitleDetector.clear();

	// 2 // После получения всех параметров участка, зная эти параметры отсортируем всё в векторе по названию Участков
	//std::sort(v_AllPipes.begin(), v_AllPipes.end());

	// Помещаем полученный список Труб в Комбобокс
	m_CmBxDivProd.Clear();

	// 1 // *Идентичные по результату куски кода
	UINT nProdNum(0);
	nProdNum = v_AllProducts.size();
	switch(nProdNum)
	{
	case 0:
		m_CmBxDivProd.AddString(_T("НЕТ ДОСТУПНЫХ ПРОДУКТОВ"));
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


// обработчики сообщений CDivisionEdit

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

	// 0 // Необходимо получить из названия Файла участка, полноценный путь и файл в формате название_участка.sou и начать парсинг этого файла

	// 1 Проверяем указанный (если указан) в ini-файле путь к папке с Участками (файлами  *.sou)
	// Если есть перепроверяем где находится приложение в данный момент, есть ли в тойже папке, что и exe-шник папка "Участки"
	// и проверяем совпадает ли [путь, где находится наш exe-шник] + [/Участки] с тем, что указано в ini-файле, если нет перезаписываем, с предупредительным сообщением.

	CString IniFileName = theApp.IniFileName;
	CString CurDivisionsPath = theApp.CurDivisionsPath;

	if(theApp.ChangeDivBtnClicked != theApp.DIV_BTN_ADD) // Если не была нажата кнопка "Добавить" то читаем параметры из файла
	{
		// НЕОБХОДИМО ДОПИСАТЬ ПРОВЕРКУ НАЛИЧЕСТВОВАНИЯ ФАЙЛОВ С РАСШИРЕНИЕМ .sou ПО ДАННОМУ ПУТИ !!!!!
		// http://www.rsdn.ru/article/qna/baseserv/fileexist.xml

		CString DivPathWithFiles("");
		CString DivPath("");
	
		DivPath = CurDivisionsPath;
		DivPathWithFiles = DivPath + _T("\\*.sou");

		//const wchar_t* _DivPathWithFiles = new wchar_t [_MAX_PATH];  // НЕЗАБЫТЬ delete в КОНЦЕ !!!
		//_DivPathWithFiles = DivPathWithFiles;

		if( !FileExists(DivPathWithFiles) )
		{
			MessageBox( _T("В папке с Участками отсутствуют файлы Участков\n Убедитесь, что:\n")
						_T("1) Папка \"Участки\" находится в той же папке, что и утилита.\n")
						_T("2) В папке имеются файлы с расширением .sou"),
						_T("ОШИБКА"), MB_ICONERROR);
		}

		//CIniParam parInjProd1 (CBLOWApp::IniFileName, _T("Injection"), _T("InjProd1"));
		//parInjProd1.Set(m_InjProducts[0]);
		//parInjProd1.Save();


		// 2 Запросить все парметры из .SOU файла Участка, если таковой существует и найден, и сохранить его 
		//	 параметры в соответсвующем векторе, в свойства theApp, для Изменения/Добавления/Просмотра этого Участка
		//	 только обновляя вектор и файл во время добавления или удаления соответствующих Датчиков или изменения 
		//	 остальных параметров Участка и при пересохраненинии этого файла 
	
		//CString FileName("Рязань Дизель.sou"); 
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

		if(validXml) // случай, когда Файл "Валидный" и .SOU файл Участка можно запросить
		{
			readDivisionFile(DivisionFilePath);
		}
		else //if(!validXml)
		{
			if(bstrOutput.length()>0)
			MessageBox(bstrOutput, L"Ошибка в файле или его стрктуре", MB_OK);

			return FALSE; // просто возвращаемся и ничего не делаем
		}
	}



	// Далее сделаем таблицу с Датчиками для данного Участка пригодной для заполнения в нашем формате:
	CRect rect;
	m_ListDiv_Det.GetClientRect(rect);
	m_ListDiv_Det.DeleteAllItems();
	//m_ListDiv_Det.InsertColumn(0, _T("№"), LVCFMT_LEFT, 30);
	//m_ListDiv_Det.InsertColumn(1, _T("Название Датчика"), LVCFMT_LEFT, rect.Width() ); // - 230);
	//m_ListDiv_Det.InsertColumn(0, _T("Имя Датчика в Системе"), LVCFMT_LEFT, 150);
	//m_ListDiv_Det.InsertColumn(0, _T("№ места установки"), LVCFMT_LEFT, 40);
	//m_ListDiv_Det.InsertColumn(1, _T("Название Датчика на Графике"), LVCFMT_LEFT, rect.Width() ); // - 230);

	(void)m_ListDiv_Det.SetExtendedStyle( LVS_EX_FULLROWSELECT );
	m_ListDiv_Det.SetHeadings( _T("№ места установки,		60;\
									Название датчика на графике,") + LintToCStr(rect.Width())
							 );
	m_ListDiv_Det.LoadColumnInfo();

//	m_CmBxDivPipe

	// В независимости от того какая кнопка нажата, нам точно нужно заполнить
	// выпадающий список 3-мя значениями ("Продукт", значения из XML-файла из коноки "Идентификатор продукта")
//	m_CmBxDivProd.AddString(_T("Бензин"));
//	m_CmBxDivProd.AddString(_T("Дизель"));	// Диз.топливо (Идентификатор)
//	m_CmBxDivProd.AddString(_T("Керосин")); // Ав.топливо (Идентификатор)		// theApp.DivDetectors[i][1] // theApp.AllDetectors[v][5]
	//m_CmBxDivProd.AddString(_T("Ав.топливо")); // Ав.топливо (Идентификатор)	// theApp.DivDetectors[i][1] // theApp.AllDetectors[v][6]

////	m_CmBxDivWatch.Clear();							// следить	// РЕДАКТИРУЕМЫЙ // 1 = ДА, 0 = НЕТ (По умолчанию "Да")
////	m_CmBxDivWatch.AddString(_T("Да"));
////	m_CmBxDivWatch.AddString(_T("Нет"));

	// Есть неизменяющиеся параметры:
	// Для Участка это "Параметр", всегда и по умолчанию равен = "Давление"
	CString Preassure("Давление");

	CString Copy_Str(" - копия");
	UINT NumOfDet(0), NumOfDetParams(0);
	CString DivisionPipe("");
	CString DivisionProd("");


	switch(theApp.ChangeDivBtnClicked)
	{
	case theApp.DIV_BTN_ADD: // нажата кнопка "Добавить Участок"
		// САМОЕ ПЕРВОЕ ЧТО МЫ ДОЛЖНЫ СДЕЛАТЬ ЭТО СОЗДАТЬ ВЕКТОР ДЛЯ УЧАСТКА:
		if(theApp.FullDivision.size() == 0)
		{
			std::vector<CString> OnlyDivision( DIV_ELEMENS_NUM, _T("") );
			theApp.FullDivision.push_back(OnlyDivision);
		}

		// Помещаем в Комбобокс все имеющиеся Трубопроводы:
		SetPipesToCmBx();

		// Заполним все значения для Участка:
		//m_EditDivName.SetWindowText(EmptyStr);			// имя

		// В случае с кнопкой "Добавить Участок" запрос всех датчиков, что подходят под продукт на данном участке и заполнение вектора theApp.DivDetectors
		// Происходит не тут, а в событии "Нажатие на комбобокс"

		//m_CmBxDivPipe.EnableWindow(TRUE);				// Труба	// РЕДАКТИРУЕМЫЙ !!! ТОЛЬКО В МОМЕНТ ДОБАВЛЕНИЯ
		//m_CmBxDivProd.EnableWindow(FALSE);			// продукт	// РЕДАКТИРУЕМЫЙ !!! ПОСЛЕ ВЫБРА Трубы		//m_EditDivParam.SetWindowText(Preassure);		// параметр // НЕ МЕНЯЕТСЯ ПОЛЬЗОВАТЕЛЕМ = "Давление" ВСЕГДА
		m_EditDivWave.SetWindowText(EmptyStr);			// волна	// РЕДАКТИРУЕМЫЙ
		m_EditDivTimeDetect.SetWindowText(EmptyStr);	// Время_обнаружения	// РЕДАКТИРУЕМЫЙ

		// В случае с Добавить Сделать недоступными ВООБЩЕ Все элементы, кроме Продукта 
		// До тех пор пока пользователь не Выберет СНАЧАЛА Продукт !!!!!!
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

	case theApp.DIV_BTN_COPY: //нажата кнопка "Копировать Участок"
		// Заполним все значения для Участка:

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

#if 0	// Найдём что установить в выпадающем списке для "Продукт":
		for(long k=0; k<PROD_NUM; k++)
		{
			CString LBProduct;
			m_CmBxDivProd.GetLBText(k,LBProduct);
			if( LBProduct == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID]) // Если в Comboboxe стоит "Ав.топливо"
			{m_CmBxDivProd.SetCurSel(k); break;}
		}
		if(theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID] == _T("Ав.топливо")) // Если в theApp.FullDivision[DIV_DIV_HEAD][1] на позиции "продукт" стоит "Ав.топливо"
		{m_CmBxDivProd.SetCurSel(2);}	// Выставаляем в Комбобокс "Керосин"
		if(theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID] == _T("Диз.топливо")) // Если в theApp.FullDivision[DIV_DIV_HEAD][1] на позиции "продукт" стоит "Диз.топливо"
		{m_CmBxDivProd.SetCurSel(1);}	// Выставаляем в Комбобокс "Дизель"
#endif

		// Тут же по продукту на Участке заполним и вектор датчиков, которые будут соответсвовать установленному на участке продукту
		theApp.DivDetectors.clear();
		for(UINT v=0; v<theApp.AllDetectors.size(); v++)
		{
			//if(theApp.AllDetectors[v][6] == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID]) // Если оставить в OnInitDialog "Ав.топливо"
			//if(theApp.AllDetectors[v][5] == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID]) // Если оставить в OnInitDialog "Керосин"
			// Универсальное решение, так как на самом деле всё зависит скорее от того, что мы найдём таки в theApp.FullDivision[DIV_DIV_HEAD][1], а там всегда находится именно "Ав.топливо"
			// СОРТИРУЕМ ТУТ СРАЗУ ПО ТРУБА+ПРОДУКТ и оставляем отсортированные в theApp.DivDetectors
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
////		m_EditDivParam.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_PARAMETR]); // НЕ МЕНЯЕТСЯ ПОЛЬЗОВАТЕЛЕМ = "Давление" ВСЕГДА
		// Найдём что установить в выпадающем списке для "Следить":
////		if( theApp.FullDivision[DIV_DIV_HEAD][DIV_WATCH] == _T("1"))
////		{m_CmBxDivWatch.SetCurSel(0);}		// Если "1" утсановим "Да"
////		if( theApp.FullDivision[DIV_DIV_HEAD][DIV_WATCH] == _T("0"))
////		{m_CmBxDivWatch.SetCurSel(1);}		// Если "0" утсановим "Нет"
		m_EditDivPipeLenght.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_PIPE_LENGTH]);
		m_EditDivBeginName.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_BEGIN_NAME]);
		m_EditDivEndName.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_END_NAME]);
		m_EditDivWave.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_WAVE]);
		m_EditDivTimeDetect.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_DTCT_TIME]);


		// Далее заполним таблицу с Датчиками для данного Участка
		NumOfDet=0;
		NumOfDetParams=0;
		if(theApp.FullDivision.size()>1)
		{ 
			UINT nTestDivSortDetectorsNum = theApp.DivDetectors.size();		// Число датчиков, подходящих для данного участка
			NumOfDet = theApp.FullDivision.size() - 1;		// NumOfDet = Число датчиков (исключая первую запись с параметрами Участка) 
			NumOfDetParams = theApp.FullDivision[DIV_DET_HEAD].size();	// NumOfDetParams = Число параметров датчиков
	
			for(UINT i(DIV_DET_HEAD), j(DET_HEAD); j < NumOfDet; i++, j++)
			{	
				/*			
				m_ListDiv_Det.InsertItem(j, theApp.FullDivision[i][DIV_DET_NUMBER]); // в 1-ой колонке Имя Датчика в Системе // номер Датчика
				// так как нам нужны только:
				m_ListDiv_Det.SetItemText(j, 0, theApp.FullDivision[i][DIV_DET_NUMBER]); // в 1-ой колонке Имя Датчика в Системе // номер Датчика
				m_ListDiv_Det.SetItemText(j, 1, theApp.FullDivision[i][DIV_DET_NAME]); // во 2-ой колнке Название Датчика на Графике // Название Датчика
				*/

				(void)m_ListDiv_Det.AddItem(
											theApp.FullDivision[i][DIV_DET_NUMBER],
											theApp.FullDivision[i][DIV_DET_NAME]
										 );
			}
			m_ListDiv_Det.SetExtendedStyle( m_ListDiv_Det.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

			// Задействуем все кнопки для редактирования датчиков, если есть хотя бы один
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
			// Если датчиков нет изначально, то оставляем только "Добавить Датчик" остальные кнопки блокируем
			m_EditDivFileName.EnableWindow(TRUE);

			m_ListDiv_Det.EnableWindow(FALSE);
			m_BtnDiv_DetAddAll.EnableWindow(TRUE);
			m_BtnDiv_DetAdd.EnableWindow(TRUE);
			m_BtnDiv_DetDel.EnableWindow(FALSE);
			m_BtnDiv_DetChange.EnableWindow(FALSE);
			m_BtnDiv_DetLook.EnableWindow(FALSE);
		}

		break;

	case theApp.DIV_BTN_CHANGE: //нажата кнопка "Изменить Участок"
		// Заполним все значения для Участка:
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

#if 0	// Найдём что установить в выпадающем списке для "Продукт":
		for(long k=0; k<PROD_NUM; k++)
		{
			CString LBProduct;
			m_CmBxDivProd.GetLBText(k,LBProduct);
			if( LBProduct == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID]) // Если в Comboboxe стоит "Ав.топливо"
			{m_CmBxDivProd.SetCurSel(k); break;}
		}
		if(theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID] == _T("Ав.топливо")) // Если в theApp.FullDivision[DIV_DIV_HEAD][1] на позиции "продукт" стоит "Ав.топливо"
		{m_CmBxDivProd.SetCurSel(2);}	// Выставаляем в Комбобокс "Керосин"
		if(theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID] == _T("Диз.топливо")) // Если в theApp.FullDivision[DIV_DIV_HEAD][1] на позиции "продукт" стоит "Диз.топливо"
		{m_CmBxDivProd.SetCurSel(1);}	// Выставаляем в Комбобокс "Дизель"
#endif

		// Тут же по продукту на Участке заполним и вектор датчиков, которые будут соответсвовать установленному на участке продукту
		theApp.DivDetectors.clear();
		for(long v=0; v<theApp.AllDetectors.size(); v++)
		{
			//if(theApp.AllDetectors[v][6] == theApp.FullDivision[DIV_DIV_HEAD][1]) // Если оставить в OnInitDialog "Ав.топливо"
			//if(theApp.AllDetectors[v][5] == theApp.FullDivision[DIV_DIV_HEAD][1]) // Если оставить в OnInitDialog "Керосин"
			// Универсальное решение, так как на самом деле всё зависит скорее от того, что мы найдём таки в theApp.FullDivision[DIV_DIV_HEAD][1], а там всегда находится именно "Ав.топливо"
			// СОРТИРУЕМ ТУТ СРАЗУ ПО ТРУБА+ПРОДУКТ и оставляем отсортированные в theApp.DivDetectors
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
		////m_EditDivParam.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_PARAMETR]); // НЕ МЕНЯЕТСЯ ПОЛЬЗОВАТЕЛЕМ = "Давление" ВСЕГДА
		// Найдём что установить в выпадающем списке для "Следить":
		////if( theApp.FullDivision[DIV_DIV_HEAD][DIV_WATCH] == _T("1"))
		////{m_CmBxDivWatch.SetCurSel(0);}		// Если "1" утсановим "Да"
		////if( theApp.FullDivision[DIV_DIV_HEAD][DIV_WATCH] == _T("0"))
		////{m_CmBxDivWatch.SetCurSel(1);}		// Если "0" утсановим "Нет"
		m_EditDivPipeLenght.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_PIPE_LENGTH]);
		m_EditDivBeginName.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_BEGIN_NAME]);
		m_EditDivEndName.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_END_NAME]);
		m_EditDivWave.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_WAVE]);
		m_EditDivTimeDetect.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_DTCT_TIME]);


		////////////////////////////////////////////////////////////////////////
		// На данном этапе производим дополнительную сортировку по Труба+Продукт



		// Далее заполним таблицу с Датчиками для данного Участка
		NumOfDet=0; // Число датчиков установленных на участке (исключая первую запись с параметрами Участка)
		NumOfDetParams=0;
		if(theApp.FullDivision.size()>1)
		{ 
			UINT nTestDivSortDetectorsNum = theApp.DivDetectors.size();		// Число датчиков, подходящих для данного участка
			NumOfDet = theApp.FullDivision.size() - 1;		// NumOfDet = Число датчиков (исключая первую запись с параметрами Участка) 
			NumOfDetParams = theApp.FullDivision[DIV_DET_HEAD].size();	// NumOfDetParams = Число параметров датчиков
	
			for(UINT i(DIV_DET_HEAD), j(DET_HEAD); j < NumOfDet; i++, j++)
			{
				/*
				m_ListDiv_Det.InsertItem(j, theApp.FullDivision[i][DIV_DET_NUMBER]); // в 1-ой колонке Имя Датчика в Системе // номер Датчика
				// так как нам нужны только:
				m_ListDiv_Det.SetItemText(j, 0, theApp.FullDivision[i][DIV_DET_NUMBER]); // в 1-ой колонке Имя Датчика в Системе // номер Датчика
				m_ListDiv_Det.SetItemText(j, 1, theApp.FullDivision[i][DIV_DET_NAME]); // во 2-ой колнке Название Датчика на Графике // Название Датчика
				*/

				(void)m_ListDiv_Det.AddItem(
											theApp.FullDivision[i][DIV_DET_NUMBER],
											theApp.FullDivision[i][DIV_DET_NAME]
										 );
			}
			m_ListDiv_Det.SetExtendedStyle( m_ListDiv_Det.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

			// Задействуем все кнопки для редактирования датчиков, если есть хотя бы один
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
			// Если датчиков нет изначально, то оставляем только "Добавить Датчик" остальные кнопки блокируем
			m_EditDivFileName.EnableWindow(FALSE);

			m_ListDiv_Det.EnableWindow(FALSE);
			m_BtnDiv_DetAddAll.EnableWindow(TRUE);
			m_BtnDiv_DetAdd.EnableWindow(TRUE);
			m_BtnDiv_DetDel.EnableWindow(FALSE);
			m_BtnDiv_DetChange.EnableWindow(FALSE);
			m_BtnDiv_DetLook.EnableWindow(FALSE);
		}

		break;

	case theApp.DIV_BTN_LOOK: // нажата кнопка "Просмотр Участка"
		// Заполним все значения для Участка:
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

#if 0	//Найдём что установить в выпадающем списке:
		for(long k=0; k<PROD_NUM; k++)
		{
			CString LBProduct;
			m_CmBxDivProd.GetLBText(k,LBProduct);
			if( LBProduct == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID])
			{m_CmBxDivProd.SetCurSel(k); break;}
		}
		if(theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID] == _T("Ав.топливо")) // Если в theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID] на позиции "продукт" стоит "Ав.топливо"
		{m_CmBxDivProd.SetCurSel(2);}	// Выставаляем в Комбобокс "Керосин"
		if(theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID] == _T("Диз.топливо")) // Если в theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID] на позиции "продукт" стоит "Диз.топливо"
		{m_CmBxDivProd.SetCurSel(1);}	// Выставаляем в Комбобокс "Дизель"
#endif
		// Тут же по продукту на Участке заполним и вектор датчиков, которые будут соответсвовать установленному на участке продукту
		theApp.DivDetectors.clear();
		for(long v=0; v<theApp.AllDetectors.size(); v++)
		{
			//if(theApp.AllDetectors[v][6] == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID]) // Если оставить в OnInitDialog "Ав.топливо"
			//if(theApp.AllDetectors[v][5] == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID]) // Если оставить в OnInitDialog "Керосин"
			// Универсальное решение, так как на самом деле всё зависит скорее от того, что мы найдём таки в theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID], а там всегда находится именно "Ав.топливо"
			// СОРТИРУЕМ ТУТ СРАЗУ ПО ТРУБА+ПРОДУКТ и оставляем отсортированные в theApp.DivDetectors
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
		////m_EditDivParam.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_PARAMETR]); // НЕ МЕНЯЕТСЯ ПОЛЬЗОВАТЕЛЕМ = "Давление" ВСЕГДА
		// Найдём что установить в выпадающем списке для "Следить":
		////if( theApp.FullDivision[DIV_DIV_HEAD][DIV_WATCH] == _T("1"))
		////{m_CmBxDivWatch.SetCurSel(0);}		// Если "1" утсановим "Да"
		////if( theApp.FullDivision[DIV_DIV_HEAD][DIV_WATCH] == _T("0"))
		////{m_CmBxDivWatch.SetCurSel(1);}		// Если "0" утсановим "Нет"
		m_EditDivPipeLenght.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_PIPE_LENGTH]);
		m_EditDivBeginName.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_BEGIN_NAME]);
		m_EditDivEndName.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_END_NAME]);
		m_EditDivWave.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_WAVE]);
		m_EditDivTimeDetect.SetWindowText(theApp.FullDivision[DIV_DIV_HEAD][DIV_DTCT_TIME]);


		// Далее заполним таблицу с Датчиками для данного Участка
		NumOfDet=0;
		NumOfDetParams=0;
		if(theApp.FullDivision.size()>1)
		{ 
			NumOfDet = theApp.FullDivision.size() - 1;		// NumOfDet = Число датчиков (исключая первую запись с параметрами Участка) 
			NumOfDetParams = theApp.FullDivision[DIV_DET_HEAD].size();	// NumOfDetParams = Число параметров датчиков
		}
	
		for(UINT i(DIV_DET_HEAD), j(DET_HEAD); j < NumOfDet; i++, j++)
		{
			/*
			m_ListDiv_Det.InsertItem(j, theApp.FullDivision[i][DIV_DET_NUMBER]); // в 1-ой колонке Имя Датчика в Системе // номер Датчика
			// так как нам нужны только:
			m_ListDiv_Det.SetItemText(j, 0, theApp.FullDivision[i][DIV_DET_NUMBER]); // в 1-ой колонке Имя Датчика в Системе // номер Датчика
			m_ListDiv_Det.SetItemText(j, 1, theApp.FullDivision[i][DIV_DET_NAME]); // во 2-ой колнке Название Датчика на Графике // Название Датчика
			*/

			(void)m_ListDiv_Det.AddItem(
										theApp.FullDivision[i][DIV_DET_NUMBER],
										theApp.FullDivision[i][DIV_DET_NAME]
									 );
		}
		m_ListDiv_Det.SetExtendedStyle( m_ListDiv_Det.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

		// В случае с кнопкой "Просмотр" заблокируем все элементы, которые имеет смысл заблокировать
		// Блокируем всё кроме: 1. Параметр 2. Список Датчиков 3. Кнопки "Просмотр" Датчика
		m_EditDivFileName.EnableWindow(FALSE);
		m_EditDivName.EnableWindow(FALSE);
		//m_CmBxDivProd.EnableWindow(FALSE);
		//m_EditDivParam.EnableWindow(FALSE); // НЕ МЕНЯЕТСЯ ПОЛЬЗОВАТЕЛЕМ = "Давление" ВСЕГДА
		//m_CmBxDivWatch.EnableWindow(FALSE);
		m_EditDivWave.EnableWindow(FALSE);
		m_EditDivTimeDetect.EnableWindow(FALSE);
		m_BtnDivSave.EnableWindow(FALSE);	// Блокируем также и кнопку "Сохранить"

		m_BtnDiv_DetAddAll.EnableWindow(FALSE);
		m_BtnDiv_DetAdd.EnableWindow(FALSE);
		m_BtnDiv_DetDel.EnableWindow(FALSE);
		m_BtnDiv_DetChange.EnableWindow(FALSE);

		if(theApp.FullDivision.size()>1)
		{ 
			// Если датчики есть изначально, то оставляем только кнопку "Просмотр Датчика"
			m_BtnDiv_DetLook.EnableWindow(TRUE);
		}
		else
		{
			// Если датчиков нет изначально, то блокируем так же и кнопку "Просмотр Датчика"
			m_BtnDiv_DetLook.EnableWindow(FALSE);
		}


		break;
	}
	


	// Выстиавить первый элемент списка как "Выделенным"
	if(m_ListDiv_Det.GetItemCount() > 0)
	{m_ListDiv_Det.SetItemState(0, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);}


	bFirstDlg=true;


	//CWnd *pWnd = GetDlgItem(IDC_DIV_DETECTORS_LIST);
	//CWnd *pWnd = pDlg->GetDlgItem(IDC_DIV_DETECTORS_LIST);
	//pWnd->GetWindowRect(&OriginalRect);
	this->GetWindowRect(&OriginalRect);
	OrigW = OriginalRect.right - OriginalRect.left;
	OrigH = OriginalRect.bottom - OriginalRect.top;


	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
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

	DivAtrs = eroot.attr(L"имя"			);		DivisionHead.push_back(DivAtrs.c_str());	// [0] - Название Участка
	DivAtrs = eroot.attr(L"труба"		);		DivisionHead.push_back(DivAtrs.c_str());	// [1] - Название трубопровода
	DivAtrs = eroot.attr(L"труба_код"	);		DivisionHead.push_back(DivAtrs.c_str());	// [2] - ID трубопровода
	DivAtrs = eroot.attr(L"продукт"		);		DivisionHead.push_back(DivAtrs.c_str());	// [3] - Название Продукта в Интерфейсе
	DivAtrs = eroot.attr(L"продукт_код"	);		DivisionHead.push_back(DivAtrs.c_str());	// [4] - ID Продукта
	DivAtrs = eroot.attr(L"параметр"	);		DivisionHead.push_back(DivAtrs.c_str());	// [5] - Параметр
	DivAtrs = eroot.attr(L"следить"		);		DivisionHead.push_back(DivAtrs.c_str());	// [6] - Следить
	DivAtrs = eroot.attr(L"волна"		);		DivisionHead.push_back(DivAtrs.c_str());	// [7] - Волна
	DivAtrs = eroot.attr(L"время_обнаружения");	DivisionHead.push_back(DivAtrs.c_str());	// [8] - Время_обнаружения
	DivAtrs = eroot.attr(L"труба_длина"	);		DivisionHead.push_back(DivAtrs.c_str());	// [9] - Длина трубопровода
	DivAtrs = eroot.attr(L"имя_начала"	);		DivisionHead.push_back(DivAtrs.c_str());	// [10] - Имя начала Участка
	DivAtrs = eroot.attr(L"имя_конца"	);		DivisionHead.push_back(DivAtrs.c_str());	// [11] - Имя Конца Участка

	theApp.FullDivision.clear();
	theApp.FullDivision.push_back(DivisionHead);
	DivisionHead.clear();

////////////////////////////////////////////////////////////////////////////////////////
	TElem subroot = eroot.subnode(L"Датчик");
	//wstring DivAtrs;
	std::vector<CString> OneDetector;

	for(TElem e=eroot.begin(); e!=eroot.end(); e++)
	{
		OneDetector.clear();
		DivAtrs = e.attr(L"имя"		);	OneDetector.push_back(DivAtrs.c_str());
		//AfxMessageBox(DivAtrs.c_str(), 0, 0);
		DivAtrs = e.attr(L"нр"			);		OneDetector.push_back(DivAtrs.c_str());
		DivAtrs = e.attr(L"активен"		);		OneDetector.push_back(DivAtrs.c_str());
		DivAtrs = e.attr(L"путь"		);		OneDetector.push_back(DivAtrs.c_str());
		DivAtrs = e.attr(L"постфикс"	);		OneDetector.push_back(DivAtrs.c_str());
		DivAtrs = e.attr(L"удаление"	);		OneDetector.push_back(DivAtrs.c_str());
		DivAtrs = e.attr(L"дельта_давление");	OneDetector.push_back(DivAtrs.c_str());
		DivAtrs = e.attr(L"дельта_время");		OneDetector.push_back(DivAtrs.c_str());
//		DivAtrs = e.attr(L"удалениеот_начала");	OneDetector.push_back(DivAtrs.c_str());
//		DivAtrs = e.attr(L"удалениеот_конца");	OneDetector.push_back(DivAtrs.c_str());

		//имя //нр //активен //путь //постфикс //удаление //дельта_давление // дельта_время
		theApp.FullDivision.push_back(OneDetector);
		OneDetector.clear();
	}

	int u=0;
}



// Нажатие на кнопку "ENTER"
void CDivisionEdit::OnBnClickedOk()
{
	//CDialog::OnOK();
}


// кнопка "Сохранить" в Настройке Участка
// кнопка "Сохранить Участок" ДОСТУПНА, когда: 1) Имеется Имя Участка 2) Имеется Продукт на Участке 3) Установлен "параметр" = "Давление" 3) На участке установлен хотябы 1 датчик
void CDivisionEdit::OnBnClickedDivSaveBtn()
{
	// TODO: добавьте свой код обработчика уведомлений
	CString EmptyStr("");


	HRESULT hr = CoInitialize(NULL);
	if(FAILED(hr))
	{
		CString ErrorStr = theApp.GetErrorCSTRString(hr);
		AfxMessageBox(ErrorStr);
		return;
	}


	// 0.1 // Проверяем параметр Название Участка
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
				int msgboxID = MessageBox(	_T("Участок с именем \"") + DivisionName + _T("\" уже существует!"),
										_T("Имена Участков совпадают!"),
										MB_ICONWARNING | MB_OK );
				m_EditDivName.SetFocus();
				return;
				}
			}
		}
	}

	int u=0;

	// 0.3 // Проверяем параметр Продукт
	// 0.4 // Проверяем параметр Параметр
	// 0.5 // Проверяем параметр Следить
	// 0.6 // Проверяем параметр Волна
	int curIndex = m_CmBxDivProd.GetCurSel();
	if( curIndex == (-1) )  return;

	CString DivisionWave("");
	m_EditDivWave.GetWindowText(DivisionWave);

	double dWaveSpeed = _tstof(DivisionWave);
	if(  ( ((dWaveSpeed < 0.5) || (dWaveSpeed > 1.5)) )  && curIndex!=(-1) )
	{
		AfxMessageBox( _T("ВНИМАНИЕ: Параметр \"Волна\" должен быть задан в следующем диапазоне значений от 0.5 до 1.5 (км/с)."), MB_ICONWARNING );
		m_EditDivWave.SetFocus();

		return;
	}
	else
	{
		DivisionWave = DoubleToCStr(dWaveSpeed,5);
		theApp.FullDivision[DIV_DIV_HEAD][DIV_WAVE] = DivisionWave;
	}

	// 0.7 // Далее проверяем параметр Время Обнаружения
	CString DivisionTimeDetect("");
	m_EditDivTimeDetect.GetWindowText(DivisionTimeDetect);

	double dTimeDetect = _tstof(DivisionTimeDetect);
	if(  ( ((dTimeDetect < 0) || (dTimeDetect > 200)) )  && curIndex!=(-1) )
	{
		AfxMessageBox( _T("ВНИМАНИЕ: Параметр \"Время обнаружения\" должен быть задан в следующем диапазоне значений от 0 до 200 (с)."), MB_ICONWARNING );
		m_EditDivTimeDetect.SetFocus();

		return;
	}
	else
	{
		DivisionTimeDetect = DoubleToCStr(dTimeDetect,0);
		theApp.FullDivision[DIV_DIV_HEAD][DIV_DTCT_TIME] = DivisionTimeDetect;
	}

	// 0.2 // Проверяем параметр Имя Файла-Участка 
	// Проверяем нет ли файла с таким же именем!
	// Делаем эту проверку толкьо в случае нажатия на кнопку "Добавить"
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
					int msgboxID = MessageBox(	_T("Файл Участка с именем \"") + theApp.DivisionFileName + _T("\" уже существует!\n\nХотите перезаписать файл?"),
												_T("Имена Файлов совпадают!"),
												MB_ICONWARNING | MB_YESNO | MB_DEFBUTTON2			);
					if(msgboxID == IDNO)
					{
						//"Нет" - продолжить редактировать участок и изменить ИМЯ Файла участка
						m_EditDivFileName.SetFocus();
						return;
					}
					// "Да" - Осуществляем перезапись файла
					*/

					int msgboxID = MessageBox(	_T("Файл Участка с именем \"") + theApp.DivisionFileName + _T("\" уже существует!"),
											_T("Имена Файлов совпадают!"),
											MB_ICONWARNING | MB_OK );
					m_EditDivFileName.SetFocus();
					return;
				}
			}
			while (FindNextFile(hf,&FindFileData)!=0);
			FindClose(hf);
		}
	}

	// 1 // Сначала сохраняем

//*
	// 1.1 // Открываем стандартное окно для сохранения:
	wchar_t szFilters[]= _T("SOU файлы участков (*.sou)|*.sou|Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*||");
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
					int msgboxID = MessageBox(	_T("Файл Участка с именем \"") + theApp.DivisionFileName + _T("\" уже существует!\n\nХотите перезаписать файл?"),
												_T("Имена Файлов совпадают!"),
												MB_ICONWARNING | MB_YESNO | MB_DEFBUTTON2			);
					if(msgboxID == IDNO)
					{
						//"Нет" - продолжить редактировать участок и изменить ИМЯ Файла участка
						NoWarningMessage=false;
						m_EditDivFileName.SetFocus();
						break;
					}
					else // "Да" - Осуществляем перезапись файла
					{
						// 2) Удаленеие ДАТЧИКОВ из файла .SOU:
						// 2.1) Удаляем старый файл
						CString DivisionFullPath("");				// Полный путь к файлу следующего Участка

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
									CFile::Remove(DivisionFullPath);// Полный путь содержится здесь
								}
							}
						}


						// 2.2) Формируем новый файл
						//CFile RedoneFileSOU;
						//RedoneFileSOU.Open(DivisionFullPath,  CFile::modeCreate|CFile:: modeReadWrite); // создать новый файл, открыть на запись и на чтение

//AfxMessageBox(_T("1 _ ") + DivisionFullPath);
						writeDivisionFile(DivisionFullPath);

					// 2 // Потом посылаем сообщение
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
			// 2) Удаленеие ДАТЧИКОВ из файла .SOU:
			// 2.1) Удаляем старый файл
			CString DivisionFullPath("");				// Полный путь к файлу следующего Участка

			bool bFound = false;
			if(theApp.CurDivisionsPath != EmptyStr)
			{
				CString sPath = theApp.CurDivisionsPath;
				CFileFind hFile;

				DivisionFullPath = DivisionFullPath + sPath + _T("\\") + theApp.DivisionFileName + _T(".sou");
			}

			// 2.2) Формируем новый файл
			//CFile RedoneFileSOU;
			//RedoneFileSOU.Open(DivisionFullPath,  CFile::modeCreate|CFile:: modeReadWrite); // создать новый файл, открыть на запись и на чтение

//AfxMessageBox(_T("2 _ ") + DivisionFullPath);
			writeDivisionFile(DivisionFullPath);

		// 2 // Потом посылаем сообщение
		GetParent()->PostMessage(WM_DIVISION_EDIT_SAVE,0,0);

		CDialog::OnOK();
		}
	}
	else
	{NoWarningMessage = true;}

	if(NoWarningMessage)
	{
		// 2) Удаленеие ДАТЧИКОВ из файла .SOU:
		// 2.1) Удаляем старый файл
		CString DivisionFullPath("");				// Полный путь к файлу следующего Участка

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
					CFile::Remove(DivisionFullPath);// Полный путь содержится здесь
				}
			}
		}


		// 2.2) Формируем новый файл
		//CFile RedoneFileSOU;
		//RedoneFileSOU.Open(DivisionFullPath,  CFile::modeCreate|CFile:: modeReadWrite); // создать новый файл, открыть на запись и на чтение


//AfxMessageBox(_T("3 _ ") + DivisionFullPath);
		writeDivisionFile(DivisionFullPath);

	// 2 // Потом посылаем сообщение
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
//		AfxMessageBox(_T("Ошибка при создании сущности из XML класса."));
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


	_bstr_t DivisionHead(_T("<Участок_СОУ></Участок_СОУ>"));


	if(pXMLDoc->loadXML(DivisionHead) == VARIANT_FALSE)
	{
		//ShowError(pXMLDoc);
		AfxMessageBox(_T("Не удалось загрузить основной узел в формируемый файл Участка"));
		return;
	}

	//Get the root element just created
	MSXML2::IXMLDOMElementPtr pXMLRootElem = pXMLDoc->GetdocumentElement();

	//Add an attribute
	pXMLRootElem->setAttribute(_T("имя"),				_variant_t( theApp.FullDivision[DIV_DIV_HEAD][DIV_DIV_NAME]		));
	pXMLRootElem->setAttribute(_T("труба"),				_variant_t( theApp.FullDivision[DIV_DIV_HEAD][DIV_PIPE_NAME]	));
	pXMLRootElem->setAttribute(_T("труба_код"),			_variant_t( theApp.FullDivision[DIV_DIV_HEAD][DIV_PIPE_ID]		));
	pXMLRootElem->setAttribute(_T("продукт"),			_variant_t( theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_NAME]	));
	pXMLRootElem->setAttribute(_T("продукт_код"),		_variant_t( theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID]		));
	pXMLRootElem->setAttribute(_T("параметр"),			_variant_t( theApp.FullDivision[DIV_DIV_HEAD][DIV_PARAMETR]		));
	pXMLRootElem->setAttribute(_T("следить"),			_variant_t( theApp.FullDivision[DIV_DIV_HEAD][DIV_WATCH]		));
	pXMLRootElem->setAttribute(_T("волна"),				_variant_t( theApp.FullDivision[DIV_DIV_HEAD][DIV_WAVE]			));
	pXMLRootElem->setAttribute(_T("время_обнаружения"),	_variant_t( theApp.FullDivision[DIV_DIV_HEAD][DIV_DTCT_TIME]	));
	pXMLRootElem->setAttribute(_T("труба_длина"),		_variant_t( theApp.FullDivision[DIV_DIV_HEAD][DIV_PIPE_LENGTH]	));
	pXMLRootElem->setAttribute(_T("имя_начала"),		_variant_t( theApp.FullDivision[DIV_DIV_HEAD][DIV_BEGIN_NAME]	));
	pXMLRootElem->setAttribute(_T("имя_конца"),			_variant_t( theApp.FullDivision[DIV_DIV_HEAD][DIV_END_NAME]		));

	if(theApp.FullDivision.size()>1)
	{
		long NumOfDet=0;
		NumOfDet = theApp.FullDivision.size() - 1;		// NumOfDet = Число датчиков (исключая первую запись с параметрами Участка) 

		MSXML2::IXMLDOMProcessingInstructionPtr pXMLProcessingNode =	pXMLDoc->createProcessingInstruction("xml", "version='1.0' encoding='windows-1251'");

		_variant_t vtObject;
		vtObject.vt = VT_DISPATCH;
		vtObject.pdispVal = pXMLRootElem;
		vtObject.pdispVal->AddRef();

		pXMLDoc->insertBefore(pXMLProcessingNode,vtObject);

		//Create the child elements and set the attributes
		for(long i=1, j=0; j<NumOfDet; i++, j++)
		{
			MSXML2::IXMLDOMElementPtr pXMLChild = pXMLDoc->createElement(_T("Датчик"));	//Create first child element

			pXMLChild->setAttribute(_T("имя"),				 _variant_t( theApp.FullDivision[i][DIV_DET_NAME]	 ));
			pXMLChild->setAttribute(_T("нр"),				 _variant_t( theApp.FullDivision[i][DIV_DET_NUMBER]	 ));
			pXMLChild->setAttribute(_T("активен"),			 _variant_t( theApp.FullDivision[i][DIV_DET_ACTIVE]	 ));
			pXMLChild->setAttribute(_T("путь"),				 _variant_t( theApp.FullDivision[i][DIV_DET_PATH]	 ));
			pXMLChild->setAttribute(_T("постфикс"),			 _variant_t( theApp.FullDivision[i][DIV_DET_PTFIX]	 ));
			pXMLChild->setAttribute(_T("удаление"),			 _variant_t( theApp.FullDivision[i][DIV_DET_DIST]	 ));
			pXMLChild->setAttribute(_T("дельта_давление"),	 _variant_t( theApp.FullDivision[i][DIV_DET_DPRESS]	 ));
			pXMLChild->setAttribute(_T("дельта_время"),		 _variant_t( theApp.FullDivision[i][DIV_DET_DTIIME]	 ));
//			pXMLChild->setAttribute(_T("удалениеот_начала"), _variant_t( theApp.FullDivision[i][DIV_DET_DISTBEG] ));
//			pXMLChild->setAttribute(_T("удалениеот_конца"),	 _variant_t( theApp.FullDivision[i][DIV_DET_DISTEND] ));

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
		AfxMessageBox(_T("Ошибка при создании сущности в виде (XSL-файла) файла схемы."));
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
		AfxMessageBox(_T("Ошибка при загрузке сущности в виде (XSL-файла) файла схемы."));
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



// кнопка "Выход" в Настройке Участка
void CDivisionEdit::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений

	// НЕ ЗАБЫТЬ ДОПИСАТЬ !!!!!
	// По кнопке Выход можно сделать "Сохранить изменения" => "Да"/"Нет", если таковые были сделаны

	GetParent()->PostMessage(WM_DIVISION_EDIT_EXIT,0,0);

	CDialog::OnCancel();
}

// кнопка "Сохранить Участок" ДОСТУПНА, когда: 1) Имеется Имя Участка 2) Имеется Продукт на Участке 3) Установлен "параметр" = "Давление" 3) На участке установлен хотябы 1 датчик

// Событие по редактированию текста в поле "Имя файла Участка"
void CDivisionEdit::OnEnChangeDivFileNameEdit()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
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

	// TODO:  Добавьте код элемента управления

	if(Correct_DivFileName != EmptyStr)
	{
		for(long i=0; i<Correct_DivFileName.GetLength(); i++)
		{
			if( Correct_DivFileName[i] == x1 || Correct_DivFileName[i] == x2 || Correct_DivFileName[i] == x3 || Correct_DivFileName[i] == x4 ||Correct_DivFileName[i] == x5 ||
				Correct_DivFileName[i] == x6 || Correct_DivFileName[i] == x7 || Correct_DivFileName[i] == x8 || Correct_DivFileName[i] == x9 
			  )
			{
				Correct_DivFileName.Delete(i, 1); // удаляем из названия файла недопустимые для имени папки и файлов смволы  / \ : * " ? < > |
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
		ChecckForBtnSave(); // Проверяем можно ли активировать кнопку "Сохранить"
}

// Событие по вводу текста в поле "Название Участка"
void CDivisionEdit::OnEnChangeDivNameEdit()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
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

	// TODO:  Добавьте код элемента управления

	m_EditDivName.GetWindowText(CurDivisionName);
	if(CurDivisionName != EmptyStr)
	{
		theApp.FullDivision[DIV_DIV_HEAD][DIV_DIV_NAME] = CurDivisionName;
		// Имя участка уже занесено в вектор theApp.FullDivision
		m_EditDivFileName.GetWindowText(DivFileName);
				
		if(theApp.ChangeDivBtnClicked == theApp.DIV_BTN_ADD) // нажата кнопка "Добавить Участок"
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
						CorrectDivisionName.Delete(i, 1); // удаляем из названия файла недопустимые для имени папки и файлов смволы  / \ : * " ? < > |
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
		else	// Нажата кнопка "Изменить" участок
		{
			// В этом режиме мы позволяем пользователю редактировать только имя участка.
		}
	}
	else
	{
		theApp.FullDivision[DIV_DIV_HEAD][DIV_DIV_NAME] = EmptyStr;
	}

	m_EditDivFileName.SetWindowText(theApp.DivisionFileName);

	//switch(theApp.ChangeDivBtnClicked)
	//{
	//case theApp.DIV_BTN_ADD: // нажата кнопка "Добавить Участок"
	//	break;
	//case theApp.DIV_BTN_CHANGE: //нажата кнопка "Изменить Участок"
	//	break;
	//case theApp.DIV_BTN_LOOK: // нажата кнопка "Просмотр Участка"
	//	break;
	//}


	if(bFirstDlg)
		ChecckForBtnSave(); // Проверяем можно ли активировать кнопку "Сохранить"

}


// Событие по выбору Трубопровода среди имеющихся
void CDivisionEdit::OnCbnSelchangeDivPipeCmbx()
{
	// TODO: добавьте свой код обработчика уведомлений
	int curIndex=0;			// Индекс элемента выбранного в Combobx
	CString DivisionPipe("");

	curIndex = m_CmBxDivPipe.GetCurSel();
	if( curIndex == (-1) )  return;

	m_CmBxDivPipe.GetLBText( curIndex, DivisionPipe );
	theApp.CurDivPipe = DivisionPipe;

	// Как только произошёл Выбор продукта, можно редактировать всё остальное, 
	// но продукт поменять более нельзя.
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
		// Сразу же выведем отсортированный список Продуктов
		SetProdsToCmBx();
		break;
	}

	//if()
	//SetProdsToCmBx();

	int u(0);

	if(bFirstDlg)
		ChecckForBtnSave(); // Проверяем можно ли активировать кнопку "Сохранить"
}


// кнопка "Сохранить Участок" ДОСТУПНА, когда: 1) Имеется Имя Участка 2) Имеется Продукт на Участке 3) Установлен "параметр" = "Давление" 3) На участке установлен хотябы 1 датчик
// Событие по выбору Продукта среди трёх доступных для Участка из Комбобокса
void CDivisionEdit::OnCbnSelchangeDivProdCmbx()
{
	// TODO: добавьте свой код обработчика уведомлений
	int curIndex=0;			// Индекс элемента выбранного в Combobx
	curIndex = m_CmBxDivProd.GetCurSel();
	if( curIndex == (-1) )  return;

	// Как только произошёл Выбор продукта, можно редактировать всё остальное, 
	// но продукт и трубопровод поменять более нельзя.

	if(curIndex != (-1))
	{
		// Определяем некоторые переменные и объекты вне Свича
		CString DivisionProduct("");
		m_CmBxDivProd.GetLBText( curIndex, DivisionProduct );
		theApp.CurDivProd = DivisionProduct;
		CString Preassure("Давление");

		std::vector<CString> TitleDetector;
		bool bSetDivivsionHead(true);
		UINT nDetNum(0);

		switch(theApp.ChangeDivBtnClicked)
		{
		case theApp.DIV_BTN_ADD: // нажата кнопка "Добавить Участок"
			//m_CmBxDivProd.EnableWindow(FALSE);				// продукт	// РЕДАКТИРУЕМЫЙ

			m_EditDivFileName.EnableWindow(TRUE);
			m_EditDivName.EnableWindow(TRUE);
			//m_EditDivParam.EnableWindow(TRUE);
			//m_CmBxDivWatch.EnableWindow(TRUE);
			m_EditDivWave.EnableWindow(TRUE);
			m_EditDivTimeDetect.EnableWindow(TRUE);

			// Датчиков пока ещё нет, так что мы можем только добавить новый датчик
			//m_ListDiv_Det.EnableWindow(TRUE);
			m_BtnDiv_DetAddAll.EnableWindow(TRUE);
			m_BtnDiv_DetAdd.EnableWindow(TRUE);
			//m_BtnDiv_DetDel.EnableWindow(TRUE);
			//m_BtnDiv_DetChange.EnableWindow(TRUE);
			//m_BtnDiv_DetLook.EnableWindow(TRUE);
			//m_BtnDivSave.EnableWindow(TRUE);				// Нужно помимо продукта хотябы указать ещё название, чтобы появилась кнопка "Сохранить"


			TitleDetector = theApp.AllDetectors[DET_HEAD]; // сохраняем первый элемент с "шапкой", чтобы она не мешалась при сортировке
			theApp.AllDetectors.erase(theApp.AllDetectors.begin() + DET_HEAD); // удалить из вектора первый элемент в котором шапка инфы о датчиках

			// предварительно очистим вектор с датчиками, которые могут быть устновлены на данном участке.
			theApp.DivDetectors.clear();

			nDetNum = theApp.AllDetectors.size();
			for(UINT i(0); i<nDetNum; i++)
			{	//DET_PIPE_SHNAME //DET_PIPE_ID
				if( (theApp.CurDivPipe == theApp.AllDetectors[i][DET_PIPE_SHNAME]) && (theApp.CurDivProd == theApp.AllDetectors[i][DET_PROD_TYPE]) )
				{
					if( bSetDivivsionHead )
					{
						//////////////////////////////////////////////////////////////////////
						// САМОЕ ПЕРВОЕ ЗАПОЛНЕНИЕ ВЕКТОРА ЗНАЧЕНЯМИ (ПАРАМЕТРАМИ УЧАСТКА)
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
						// После заполняем и все Edit и прочие боксы
						////m_EditDivParam.SetWindowText(Preassure);
						////m_CmBxDivWatch.SetCurSel(0);	// Устанавливаем по умолчанию "1" = "Да"  //  SetWindowText(_T("1"));
						m_EditDivPipeLenght.SetWindowText(	theApp.FullDivision[DIV_DIV_HEAD][DIV_PIPE_LENGTH]);
						m_EditDivBeginName.SetWindowText(	theApp.FullDivision[DIV_DIV_HEAD][DIV_BEGIN_NAME]);
						m_EditDivEndName.SetWindowText(		theApp.FullDivision[DIV_DIV_HEAD][DIV_END_NAME]);
						m_EditDivWave.SetWindowText(		theApp.FullDivision[DIV_DIV_HEAD][DIV_WAVE] );
						m_EditDivTimeDetect.SetWindowText(	theApp.FullDivision[DIV_DIV_HEAD][DIV_DTCT_TIME] );

						bSetDivivsionHead=false;
					}

					// Тут же по трубе и продукту  на Участке заполним и вектор датчиков, которые будут соответсвовать установленному на участке продукту
					theApp.DivDetectors.push_back(theApp.AllDetectors[i]);
				}
			}

			theApp.AllDetectors.insert(theApp.AllDetectors.begin(), TitleDetector); // добавляем шапку обратно в начало
			TitleDetector.clear();


			/*
			// Существуют 3 параметра для волны
			if(theApp.CurDivProd == _T("Бензин"))
			{
				m_EditDivWave.SetWindowText(_T("1.19"));
				// {m_EditDivWave.SetWindowText(_T("1190"));
			}
			if(theApp.CurDivProd == _T("Дизель"))
			{
				m_EditDivWave.SetWindowText(_T("1.22"));
				// {m_EditDivWave.SetWindowText(_T("1220"));
			}
			if(theApp.CurDivProd == _T("Керосин"))
			{
				m_EditDivWave.SetWindowText(_T("1.2"));
				// {m_EditDivWave.SetWindowText(_T("1200"));
			}

			m_EditDivTimeDetect.SetWindowText(_T("10"));

			// Тут же по продукту на Участке заполним и вектор датчиков, которые будут соответсвовать установленному на участке продукту
			theApp.DivDetectors.clear();
			for(UINT i(0); i<theApp.AllDetectors.size(); i++)
			{
				//if(theApp.AllDetectors[i][6] == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID]) // Если оставить в OnInitDialog "Ав.топливо"
				//if(theApp.AllDetectors[i][5] == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID]) // Если оставить в OnInitDialog "Керосин"
				// Универсальное решение, так как на самом деле всё зависит скорее от того, что мы найдём таки в theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID], а там всегда находится именно "Ав.топливо"
				if( 
					//(theApp.AllDetectors[i][DET_PROD_ID] == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID]) || 
					(theApp.AllDetectors[i][DET_PROD_TYPE] == theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_NAME]) 
				  ) 
				{theApp.DivDetectors.push_back(theApp.AllDetectors[i]);}
				//theApp.DIVDET_NUM = theApp.DivDetectors.size();
			}
			//*/

			break;
		case theApp.DIV_BTN_CHANGE: //нажата кнопка "Изменить Участок"
			break;
		case theApp.DIV_BTN_LOOK: //нажата кнопка "Просмотр Участка"
			break;
		}


		// Формируем и автоматически выставляем Имена файла + Назщвание Участка по умолчангию из "Труба_Продукт"
		if(  ( !theApp.CurDivPipe.IsEmpty() ) && ( !theApp.CurDivProd.IsEmpty() )  )
		{
			CString sDefaultDivisionAndFileName(theApp.CurDivPipe +_T("_")+ theApp.CurDivProd);		
			m_EditDivName.SetWindowText( sDefaultDivisionAndFileName + _T("") );
			m_EditDivFileName.SetWindowText( sDefaultDivisionAndFileName + _T("_Учк") );
		}

		// Один раз выбрали и больше выбирать не даём
		m_CmBxDivProd.EnableWindow(FALSE);
	}

	if(bFirstDlg)
		ChecckForBtnSave(); // Проверяем можно ли активировать кнопку "Сохранить"
}




// кнопка "Сохранить Участок" ДОСТУПНА, когда: 1) Имеется Имя Участка 2) Имеется Продукт на Участке 3) Установлен "параметр" = "Давление" 3) На участке установлен хотябы 1 датчик
void CDivisionEdit::OnEnChangeDivParamEdit() // параметр = "Давление"
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
	if(bFirstDlg)
		ChecckForBtnSave(); // Проверяем можно ли активировать кнопку "Сохранить"
}


//void CDivisionEdit::OnEnChangeDivWatchEdit() // следить
//{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
	//FullDivParam = theApp.FullDivision[DIV_DIV_HEAD][DIV_WATCH];
	//element->SetAttribute("следить",FullDivParam);
//}



void CDivisionEdit::OnCbnSelchangeDivWatchCmbx()  // следить // Да=1, Нет=0
{
	// TODO: добавьте свой код обработчика уведомлений
	int curIndex=0;			// Индекс элемента выбранного в Combobx
	CString DivisionWatch("");

////	curIndex = m_CmBxDivWatch.GetCurSel();
////	if( curIndex == (-1) )  return;

////	m_CmBxDivWatch.GetLBText( curIndex, DivisionWatch );
	
	if( DivisionWatch == _T("Да") )
	{theApp.FullDivision[DIV_DIV_HEAD][DIV_WATCH] = _T("1");}
	if( DivisionWatch == _T("Нет") )
	{theApp.FullDivision[DIV_DIV_HEAD][DIV_WATCH] = _T("0");}
}


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////


void CDivisionEdit::OnEnChangeDivPipeLenghtEdit()
{
	// TODO:  Добавьте код элемента управления
}


void CDivisionEdit::OnEnChangeDivBeginNameEdit()
{
	// TODO:  Добавьте код элемента управления
}


void CDivisionEdit::OnEnChangeDivEndNameEdit()
{
	// TODO:  Добавьте код элемента управления
}




void CDivisionEdit::OnEnChangeDivWaveEdit() // волна
{
/*
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
	bool NoNeedToChange=true;
	CString DivisionWave("");
	m_EditDivWave.GetWindowText(DivisionWave);
	NoNeedToChange = CheckString(DivisionWave);

	int curIndex = m_CmBxDivProd.GetCurSel();
	if( curIndex == (-1) )  return;

	double dWaveSpeed = _tstof(DivisionWave);
	if(  ( ((dWaveSpeed < 0.5) || (dWaveSpeed > 1.5)) )  && curIndex!=(-1) )
	{
		AfxMessageBox( _T("ВНИМАНИЕ: Параметр \"Волна\" должен быть задан в следующем диапазоне значений от 0.5 до 1.5 (км/с)."), MB_ICONWARNING );
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


void CDivisionEdit::OnEnChangeDivTimedetectEdit() // Время_обнаружения
{
/*
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
	bool NoNeedToChange=true;
	CString DivisionTimeDetect("");
	m_EditDivTimeDetect.GetWindowText(DivisionTimeDetect);
	NoNeedToChange = CheckString(DivisionTimeDetect);

	int curIndex = m_CmBxDivProd.GetCurSel();
	if( curIndex == (-1) )  return;

	double dTimeDetect = _tstof(DivisionTimeDetect);
	if(  ( ((dTimeDetect < 0) || (dTimeDetect > 200)) )  && curIndex!=(-1) )
	{
		AfxMessageBox( _T("ВНИМАНИЕ: Параметр \"Время обнаружения\" должен быть задан в следующем диапазоне значений от 0 до 200 (с)."), MB_ICONWARNING );
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


// Событие по нажатию на список Датчиков
void CDivisionEdit::OnLvnItemchangedDivDetectorsList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: добавьте свой код обработчика уведомлений
	CString EmptyStr("");
	long nCount=0;		// Число записей в Listbox
	long curIndex=0;	// Индекс элемента выбранного в Listbox
	POSITION pos=NULL;	// Номер выбранного элемента (pos = curIndex+1)

	nCount = m_ListDiv_Det.GetItemCount();
	if(nCount>0)
		m_CmBxDivProd.EnableWindow(FALSE);
	else
		m_CmBxDivProd.EnableWindow(FALSE); //m_CmBxDivProd.EnableWindow(TRUE);


	//взять выделенный элемент из списка отображения
	pos = m_ListDiv_Det.GetFirstSelectedItemPosition();
	if(pos==NULL) return;	// Ничего не делать далее, елси в списке ничего не выбрано
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


	// "Изменить" можно только Один датчик до его сохранения или выхода из него
	// "Просмтор" же можно осущесвлять у нескольких датчиков свободно, переходя на каждый из них по нажатию в списке
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

// кнопка "Удалить Датчик" в Настройке Участка
void CDivisionEdit::OnBnClickedDivDetDellBtn()
{
	// TODO: добавьте свой код обработчика уведомлений
	CString EmptyStr("");
	long nCount=0;		// Число записей в Listbox
	long curIndex=0;	// Индекс элемента выбранного в Listbox
	POSITION pos=NULL;	// Номер выбранного элемента (pos = curIndex+1)

	nCount = m_ListDiv_Det.GetItemCount();
	//взять выделенный элемент из списка отображения
	pos = m_ListDiv_Det.GetFirstSelectedItemPosition();
	if(pos==NULL) return;	// Ничего не делать далее, елси в списке ничего не выбрано
	curIndex = m_ListDiv_Det.GetNextSelectedItem(pos);
	if( curIndex == (-1) )  return;

	//CString sDivDetNum = m_ListDiv_Det.GetItemText(curIndex,0);
	CString sDivDetNum = m_ListDiv_Det.GetItemText(curIndex,0);

	//CString sGroup;
	//if(sUser!=_T("smth."))
	//	sGroup.Format(_T("%d"),m_DivChangeList.GetItemData(nCurItem));
	//else
	//	sGroup = sUser;

	// Непосредственно удаление записи из списка
	m_ListDiv_Det.DeleteItem(curIndex);

	// (*) Т.к. элементы списка не сортируются автоматически относительно удалённого элемента, то приджётся это сделать вручную
	//CString LowerName("");
	//nCount = m_DivChangeList.GetItemCount(); // После удаления число элементов станет меньше на 1-н
	//for(long i=curIndex; i<nCount; i++)
	//{
	//	LowerName = m_DivChangeList.GetItemText(i,0);
	//	m_DivChangeList.InsertItem(i, LowerName);
	//}

	//Задумка Выше (*) провалилась, так что мы сначала удалим элемент "датчик" из вектора theApp.FullDivision[1...n][]
	// а потом удалим запись о датчике из .sou-файла, и потом просто повторно поместим все оставшивеся названия файлов в список:
	// 1) Удаленеие ДАТЧИКА из вектора:
	nCount = m_ListDiv_Det.GetItemCount();	// Запрос важен, ибо элементов стало на один меньше.
	
	for(long i=1; i<theApp.FullDivision.size(); i++)
	{
		//if(theApp.FullDivision[i][0] == sDivDetNum)
		if(theApp.FullDivision[i][DIV_DET_NUMBER] == sDivDetNum)
		{
			theApp.FullDivision.erase(theApp.FullDivision.begin()+i); // удалить из вектора i-тый датчик (элемент)
			break;
		}
	}
/*
	// 2) Удаленеие ДАТЧИКА из файла .SOU:
	// 2.1) Удаляем старый файл
	CString DivisionFullPath("");				// Полный путь к файлу следующего Участка
	if(theApp.CurDivisionsPath != EmptyStr)
	{
		CString sPath = theApp.CurDivisionsPath;
		CFileFind hFile;

		DivisionFullPath = DivisionFullPath + sPath + _T("\\") + theApp.DivisionFileName + _T(".sou");
		bool bFound = false;
		bFound = hFile.FindFile( DivisionFullPath );
				
		if(bFound)
		{
			CFile::Remove(DivisionFullPath);// Полный путь содержится здесь
		}
	}

	// 2.2) Формируем новый файл
	//CFile RedoneFileSOU;
	//RedoneFileSOU.Open(DivisionFullPath,  CFile::modeCreate|CFile:: modeReadWrite); // создать новый файл, открыть на запись и на чтение

	TiXmlDocument doc;
	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "windows-1251", "" );
	doc.LinkEndChild( decl );

	TiXmlElement* element = new TiXmlElement( "Участок_СОУ" );
	TiXmlText* text = new TiXmlText( "" );

	CStringA FullDivParam("");
	FullDivParam = theApp.FullDivision[DIV_DIV_HEAD][DIV_DIV_NAME];
	element->SetAttribute("имя",FullDivParam);
	FullDivParam = theApp.FullDivision[DIV_DIV_HEAD][DIV_PROD_ID];
	element->SetAttribute("продукт",FullDivParam);
	FullDivParam = theApp.FullDivision[DIV_DIV_HEAD][DIV_PARAMETR];
	element->SetAttribute("параметр",FullDivParam);
	FullDivParam = theApp.FullDivision[DIV_DIV_HEAD][DIV_WATCH];
	element->SetAttribute("следить",FullDivParam);
	FullDivParam = theApp.FullDivision[DIV_DIV_HEAD][DIV_WAVE];
	element->SetAttribute("волна",FullDivParam);
	FullDivParam = theApp.FullDivision[DIV_DIV_HEAD][DIV_DTCT_TIME];
	element->SetAttribute("Время_обнаружения",FullDivParam);

	doc.LinkEndChild( element );
	element->LinkEndChild( text );

	if(theApp.FullDivision.size()>1)
	{
		long NumOfDet=0;
		NumOfDet = theApp.FullDivision.size() - 1;		// NumOfDet = Число датчиков (исключая первую запись с параметрами Участка) 

		for(long i=1, j=0; j<NumOfDet; i++, j++)
		{
			TiXmlElement* element2 = new TiXmlElement( "Датчик" );
			TiXmlText* text2 = new TiXmlText( "" );

			FullDivParam = theApp.FullDivision[i][DIV_DET_NUMBER];	element2->SetAttribute("имя",FullDivParam);
			FullDivParam = theApp.FullDivision[i][DIV_DET_NAME];	element2->SetAttribute("нр",FullDivParam);
			FullDivParam = theApp.FullDivision[i][DIV_DET_ACTIVE];	element2->SetAttribute("активен",FullDivParam);
			FullDivParam = theApp.FullDivision[i][DIV_DET_PATH];	element2->SetAttribute("путь",FullDivParam);
			FullDivParam = theApp.FullDivision[i][DIV_DET_PTFIX];	element2->SetAttribute("постфикс",FullDivParam);
			FullDivParam = theApp.FullDivision[i][DIV_DET_DIST];	element2->SetAttribute("удаление",FullDivParam);
			FullDivParam = theApp.FullDivision[i][DIV_DET_DPRESS];	element2->SetAttribute("дельта_давление",FullDivParam);
			FullDivParam = theApp.FullDivision[i][DIV_DET_DTIIME];	element2->SetAttribute("дельта_время",FullDivParam);

			element->LinkEndChild( element2 );
			element2->LinkEndChild( text2 );
		}
	}
	doc.SaveFile( (CStringA)DivisionFullPath );
*/

	// 3) Перезаполнение списка
	CString DetectorName(""); // Имя следующего Датчика

	m_ListDiv_Det.DeleteAllItems(); // Предварительно опустошаем список

	//CRect rect;
	//m_ListDiv_Det.GetClientRect(rect);
	(void)m_ListDiv_Det.SetExtendedStyle( LVS_EX_FULLROWSELECT );
	//m_ListDiv_Det.SetHeadings( _T("№ места установки,		60;\
	//								Название датчика на графике,") + LintToCStr(rect.Width())
	//						 );
	//m_ListDiv_Det.LoadColumnInfo();

	//*
	// Заполняем список Названиями Участков используя названия файлов .sou из папки "Участки"
		long NumOfDet=0;
		long NumOfDetParams=0;
		if(theApp.FullDivision.size()>1)
		{ 
			NumOfDet = theApp.FullDivision.size() - 1;		// NumOfDet = Число датчиков (исключая первую запись с параметрами Участка) 
			NumOfDetParams = theApp.FullDivision[DIV_DET_HEAD].size();	// NumOfDetParams = Число параметров датчиков
	
			for(UINT i(DIV_DET_HEAD), j(DET_HEAD); j < NumOfDet; i++, j++)
			{
				/*
				m_ListDiv_Det.InsertItem(j, theApp.FullDivision[i][DIV_DET_NUMBER]); // в 1-ой колонке Имя Датчика в Системе // номер Датчика
				// так как нам нужны только:
				m_ListDiv_Det.SetItemText(j, 0, theApp.FullDivision[i][DIV_DET_NUMBER]); // в 1-ой колонке Имя Датчика в Системе // номер Датчика
				m_ListDiv_Det.SetItemText(j, 1, theApp.FullDivision[i][DIV_DET_NAME]); // во 2-ой колнке Название Датчика на Графике // Название Датчика
				*/

				(void)m_ListDiv_Det.AddItem(
											theApp.FullDivision[i][DIV_DET_NUMBER],
											theApp.FullDivision[i][DIV_DET_NAME]
										 );
			}
			m_ListDiv_Det.SetExtendedStyle( m_ListDiv_Det.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
		}

	//*/

	// Надо проверить не удалены ли все датчики, тогда оставить надо только кнопку "Добавить", остальные заблокировать
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


// кнопка "Добавить Датчик" в Настройке Участка
void CDivisionEdit::OnBnClickedDivDetAddBtn()
{
	// НЕОБХОДИМО ДОБАВИТЬ ПРОВЕРКУ НА ТО ВЕРНЫЙ ЛИ ПУТЬ УКАЗАН ДО XML-ФАЙЛА С ДАТЧИКАМИ, ЕСЛИ ФАЙЛА ПО ЭТОМУ ПУТИ НЕТ, ТО ВЫДАТЬ СООБЩЕНИЕ
	// !!!!!


	// TODO: добавьте свой код обработчика уведомлений
	// 0 // В случае с "Добавить" нам не нужно получать Имя выбранного Датчика или проверять, что Датчик выбран в принципе.

	// 1.2	Произведём дополнительную сортировку по датчикам, что уже установлены на участке
	//		чтобы в выпадающем списке были только неповторяющиеся датчики соответсвенно, ибо 2-ух одинаковых датчиков на участке быть не может
	//		Из  theApp.DivDetectors[0...n][]  достаточно удалить все  theApp.FullDivision[1...n][] 
	//theApp.DivSortDetectors.clear();
	std::vector<std::vector<CString>> TestDivSortDetectors; // Датчики полученные из XML-файла, которые отсеяны по продукту на Участке, и не содержащие тех датчиков, что уже есть на участке
	TestDivSortDetectors = theApp.DivDetectors; // ELSE // по этой причине ничего не делаем в ELSE
	if(theApp.FullDivision.size() > 1)
	{
		for(long j=DIV_DET_HEAD; j<theApp.FullDivision.size(); j++)
		{
			for(long i=0; i<TestDivSortDetectors.size(); i++)
			{
				//if(TestDivSortDetectors[i][1] == theApp.FullDivision[j][DIV_DET_NAME])
				if(TestDivSortDetectors[i][DET_NAME] == theApp.FullDivision[j][DIV_DET_NAME])
				{
					TestDivSortDetectors.erase(TestDivSortDetectors.begin()+i); // удалить из вектора i-тый датчик (элемент)
					break;
				}
			}
		}
	}
	else // ELSE // В случае если на участке нет Датчиков, то просто заполняем отсортированные по Продукту датчики что получили из XML-файла
	{
		//for(long i=0; i<theApp.DivDetectors.size(); i++)
		//{
		//	if(theApp.FullDivision[DIV_DIV_HEAD][DET_NAME])
		//	{
		//		TestDivSortDetectors.push_back(theApp.DivDetectors[i]);
		//	}
		//}
	}


	//if( // В случае если открылось окно не по "Добавить Участок" и 
	//	(theApp.ChangeDivBtnClicked == theApp.DIV_BTN_ADD)  &&
	//	(  (TestDivSortDetectors.size() != 0) || (theApp.FullDivision.size() == 1)  ) 
	//  )	// не пустует отсортированный вектор с подходящими Датчиками 
		// или в векторе имеется только запись о Участке и ещё не содержится датчиков - это когда, появился датчик с таким номером, которого неполучается найти среди списка Датчиков в XML
	//{
	// Задали по умолчанию Максимальное значение для числа Датчиков на одном участке РАВНОЕ  8
	//CIniParam AppMaxDetectors(theApp.IniFileName, _T("Program"), _T("MaxDetectors"), _T("8"));
	//theApp.MaxDetectors = AppMaxDetectors.AsInt();

	if(TestDivSortDetectors.size() > 0)
	{
		if(theApp.MaxDetectors > 0)
		{
			if(m_ListDiv_Det.GetItemCount() < theApp.MaxDetectors)
			{
				// 1 // Теперь через этот параметр все прочие окна будут знать, что нажата кнопка "Добавить"
				theApp.EditDivDetBtnClicked = theApp.DET_BTN_ADD;

				// 2 // Блокируем все кнопки (+список Датчиков) до тех пор пока пользователь не закончит работать с выбранным Датчиком
				m_ListDiv_Det.EnableWindow(FALSE);
				m_BtnDiv_DetAddAll.EnableWindow(FALSE);
				m_BtnDiv_DetAdd.EnableWindow(FALSE);
				m_BtnDiv_DetDel.EnableWindow(FALSE);
				m_BtnDiv_DetChange.EnableWindow(FALSE);
				m_BtnDiv_DetLook.EnableWindow(FALSE);
				m_BtnDivSave.EnableWindow(FALSE);
				m_BtnDivExit.EnableWindow(FALSE);

				// 3 // Открываем окно для редктирования Датчика
				CDetectorsEdit* p_DetectorsEditDlg = new CDetectorsEdit;
				p_DetectorsEditDlg->Create(IDD_EDIT_DETECTOR_DLG, this);
				p_DetectorsEditDlg->ShowWindow(SW_SHOW);

				DetectorDlgHWND = p_DetectorsEditDlg->GetSafeHwnd();
			}
			else
			{
				AfxMessageBox(_T("Число датчиков установленных на один участок не может быть больше ") + LintToCStr(theApp.MaxDetectors));
			}
		}
		else
		{
				// 1 // Теперь через этот параметр все прочие окна будут знать, что нажата кнопка "Добавить"
				theApp.EditDivDetBtnClicked = theApp.DET_BTN_ADD;

				// 2 // Блокируем все кнопки (+список Датчиков) до тех пор пока пользователь не закончит работать с выбранным Датчиком
				m_ListDiv_Det.EnableWindow(FALSE);
				m_BtnDiv_DetAddAll.EnableWindow(FALSE);
				m_BtnDiv_DetAdd.EnableWindow(FALSE);
				m_BtnDiv_DetDel.EnableWindow(FALSE);
				m_BtnDiv_DetChange.EnableWindow(FALSE);
				m_BtnDiv_DetLook.EnableWindow(FALSE);
				m_BtnDivSave.EnableWindow(FALSE);
				m_BtnDivExit.EnableWindow(FALSE);

				// 3 // Открываем окно для редктирования Датчика
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
			AfxMessageBox(_T("Все доступные Датчики для данного продукта, выбранного на текущем Участке, задействованы! ")
						  _T("Датчиков доступных для добавления больше не осталось."));
		}
		else
		{
			AfxMessageBox(_T("Не удалось считать XML-файл с Датчиками!\n\n")
						  _T("Проверьте:\n")
						  _T("1) Верно ли указан путь к файлу со списком датчиков.\n")
						  _T("2) Существует ли сам файл по данному пути.\n")
						  _T("3) Доспуен ли указанный XML-файл для чтения."));
		}
	}

}

// добавление всех доступных на данной нитке датчиков
// кнопка "Добавить Все Датчики" в Настройке Участка
void CDivisionEdit::OnBnClickedDivDetAddAllBtn()
{
	// НЕОБХОДИМО ДОБАВИТЬ ПРОВЕРКУ НА ТО ВЕРНЫЙ ЛИ ПУТЬ УКАЗАН ДО XML-ФАЙЛА С ДАТЧИКАМИ, ЕСЛИ ФАЙЛА ПО ЭТОМУ ПУТИ НЕТ, ТО ВЫДАТЬ СООБЩЕНИЕ
	// !!!!!

	// TODO: добавьте свой код обработчика уведомлений
	// 0 // В случае с "Добавить" нам не нужно получать Имя выбранного Датчика или проверять, что Датчик выбран в принципе.

	// 1.2	Произведём дополнительную сортировку по датчикам, что уже установлены на участке
	//		чтобы в выпадающем списке были только неповторяющиеся датчики соответсвенно, ибо 2-ух одинаковых датчиков на участке быть не может
	//		Из  theApp.DivDetectors[0...n][]  достаточно удалить все  theApp.FullDivision[1...n][] 
	//theApp.DivSortDetectors.clear();
	std::vector<std::vector<CString>> TestDivSortDetectors; // Датчики полученные из XML-файла, которые отсеяны по продукту на Участке, и не содержащие тех датчиков, что уже есть на участке
	TestDivSortDetectors = theApp.DivDetectors; // ELSE // по этой причине ничего не делаем в ELSE
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
				// добавим ещё отсутствующий в формируемом участке Датчик
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
	else // ELSE // В случае если на участке нет Датчиков, то просто заполняем отсортированные по Продукту датчики что получили из XML-файла
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
	// 2 // После получения всех параметров участка, зная эти параметры отсортируем всё в векторе по названию Участков
	/*
	if(theApp.FullDivision.size()>2) // запись о участке + более одного датчика
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

		// Сортируем наш вектор с номерами участков обычной сортировкой пузырьком:
		// СОРТИРОВКА
		for (long i=0; i < AllDetectorsNums.size(); i++)
		{	// Массив просматривается с конца до позиции i и "легкие элементы всплывают"
			for (long j = AllDetectorsNums.size()-1; j > i; j--)
			{	// Если соседние элементы расположены в неправильном порядке, то меняем их местами
				if (AllDetectorsNums[j] < AllDetectorsNums[j-1])
				{
					std::swap(AllDetectorsNums[j], AllDetectorsNums[j-1]);
					std::swap(AllDetectorsSysNames[j], AllDetectorsSysNames[j-1]);
				}
			}
		}

		// Вектор с номерами и именами отсортирован
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

	// временно удаляем шапку Участка
	std::vector<CString> DivisionHead;
	DivisionHead = theApp.FullDivision[DIV_DIV_HEAD]; // сохраняем первый элемент с "шапкой", чтобы она не мешалась при сортировке
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

	// Возвращаем шапку обратно в учатсок
	theApp.FullDivision.insert(theApp.FullDivision.begin(), DivisionHead);
	DivisionHead.clear();


	///////////////////////////////////////////////////////////////////////////////////////////
	// КАК НАИБОЛЕЕ ПРАВИЛЬТНО ОБРАБОТАТЬ ЭТОТ СЛУЧАЙ НУЖНО БУДЕТ ПОДУМАТЬ ЕЩЁ ОТДЕЛЬНО
	///////////////////////////////////////////////////////////////////////////////////////////
	if(TestDivSortDetectors.size() > 0)
	{
		if(theApp.MaxDetectors > 0)
		{
			if(m_ListDiv_Det.GetItemCount() < theApp.MaxDetectors)
			{
				// 1 // Теперь через этот параметр все прочие окна будут знать, что нажата кнопка "Добавить"
				theApp.EditDivDetBtnClicked = theApp.DET_BTN_ADD_ALL;
				// 2 // Блокируем все кнопки (+список Датчиков) до тех пор пока пользователь не закончит работать с выбранным Датчиком
			}
			else
			{AfxMessageBox(
				_T("Число датчиков установленных на один участок не может быть больше ") + LintToCStr(theApp.MaxDetectors));
			}
		}
		else
		{		// 1 // Теперь через этот параметр все прочие окна будут знать, что нажата кнопка "Добавить"
				theApp.EditDivDetBtnClicked = theApp.DET_BTN_ADD_ALL;
		}
	}
	else
	{
		if(theApp.AllDetectors.size() > 0)
		{
			AfxMessageBox(_T("Все доступные Датчики для данного продукта, выбранного на текущем Участке, задействованы! ")
						  _T("Датчиков доступных для добавления больше не осталось."));
		}
		else
		{
			AfxMessageBox(_T("Не удалось считать XML-файл с Датчиками!\n\n")
						  _T("Проверьте:\n")
						  _T("1) Верно ли указан путь к файлу со списком датчиков.\n")
						  _T("2) Существует ли сам файл по данному пути.\n")
						  _T("3) Доспуен ли указанный XML-файл для чтения."));
		}
	}


	///////////////////////////////////////////////////////////////////////////////////////////
	// Заполняем Лист-Бокс со списком Датчикамов для Участка
	///////////////////////////////////////////////////////////////////////////////////////////
	m_ListDiv_Det.EnableWindow(TRUE);
	m_ListDiv_Det.DeleteAllItems(); // Предварительно опустошаем список

	//CRect rect;
	//m_ListDiv_Det.GetClientRect(rect);
	(void)m_ListDiv_Det.SetExtendedStyle( LVS_EX_FULLROWSELECT );
	//m_ListDiv_Det.m_ListDiv_Det.SetHeadings( _T("№ места установки,		60;\
	//								Название датчика на графике,") + LintToCStr(rect.Width())
	//						 );
	//m_ListDiv_Det.LoadColumnInfo();

	//*
	// Заполняем список Названиями Участков используя названия файлов .sou из папки "Участки"
	long NumOfDet(0);
	long NumOfDetParams(0);
	if(theApp.FullDivision.size()>1)
	{ 
		NumOfDet = theApp.FullDivision.size() - 1;		// NumOfDet = Число датчиков (исключая первую запись с параметрами Участка) 
		NumOfDetParams = theApp.FullDivision[DIV_DET_HEAD].size();	// NumOfDetParams = Число параметров датчиков
	
		for(UINT i(DIV_DET_HEAD), j(DET_HEAD); j < NumOfDet; i++, j++)
		{
			/*
			m_ListDiv_Det.InsertItem(j, theApp.FullDivision[i][DIV_DET_NUMBER]); // в 1-ой колонке Имя Датчика в Системе // номер Датчика
			// так как нам нужны только:
			m_ListDiv_Det.SetItemText(j, 0, theApp.FullDivision[i][DIV_DET_NUMBER]); // в 1-ой колонке Имя Датчика в Системе // номер Датчика
			m_ListDiv_Det.SetItemText(j, 1, theApp.FullDivision[i][DIV_DET_NAME]); // во 2-ой колнке Название Датчика на Графике // Название Датчика
			*/

			(void)m_ListDiv_Det.AddItem(
										theApp.FullDivision[i][DIV_DET_NUMBER],
										theApp.FullDivision[i][DIV_DET_NAME]
									 );
		}
		m_ListDiv_Det.SetExtendedStyle( m_ListDiv_Det.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	}
	
	// 3 // Если пришло сообщение от "Сохранить новый датчик", то точно можно открывать все остальные кнопки.
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


	// Блоникуем как кнопку "Добавитьв все", так и кнопку "Добавить"
	m_BtnDiv_DetAddAll.EnableWindow(FALSE);;
	m_BtnDiv_DetAdd.EnableWindow(FALSE);

	if(bFirstDlg)
		ChecckForBtnSave(); // Проверяем можно ли активировать кнопку "Сохранить"

}


// кнопка "Изменить Датчик" в Настройке Участка
void CDivisionEdit::OnBnClickedDivDetChangeBtn()
{
	// TODO: добавьте свой код обработчика уведомлений
	// 0 // В случае с "Изменить" нам важно получить Имя выбранного Датчика и проверять, что Датчик выбран в принципе.
	// 1 // Сохраняем Имя выбранного Датчика, чтобы использовать его в окне редактирования Датчика
	CString EmptyStr("");
	long nCount=0;		// Число записей в Listbox
	long curIndex=0;	// Индекс элемента выбранного в Listbox
	POSITION pos=NULL;	// Номер выбранного элемента (pos = curIndex+1)

	nCount = m_ListDiv_Det.GetItemCount();
	//взять выделенный элемент из списка отображения
	pos = m_ListDiv_Det.GetFirstSelectedItemPosition();
	if(pos==NULL) return;	 // В случае, если ничего не выбрано:
							// 1) не открываем окно редактирования Датчика
							// 2) не блокируем ни одну из кнопок

	curIndex = m_ListDiv_Det.GetNextSelectedItem(pos);
	if( curIndex == (-1) )  return;

	CString sDetSysName = m_ListDiv_Det.GetItemText(curIndex,0);	// 1 колонка
	CString sDetGrafName = m_ListDiv_Det.GetItemText(curIndex,1);	// 2 колонка
	//CString sDetNum = m_ListDiv_Det.GetItemText(curIndex,0);	// 1 колонка
	//CString sDetName = m_ListDiv_Det.GetItemText(curIndex,1);	// 2 колонка

	// 1.1 // Теперь через этот параметр все прочие окна будут знать номер и имя текущего Датчика
	theApp.CurDetSysName = sDetSysName;
	theApp.CurDetGrafName = sDetGrafName;
	//theApp.CurDetNum = sDetNum;
	//theApp.CurDetName = sDetName;
	// 1.2 // Теперь через этот параметр все прочие окна будут знать, что нажата кнопка "Изменить"
	theApp.EditDivDetBtnClicked = theApp.DET_BTN_CHANGE;

	// 2 // Блокируем все кнопки (+список Датчиков) до тех пор пока пользователь не закончит работать с выбранным Датчиком
	m_ListDiv_Det.EnableWindow(FALSE);
	m_BtnDiv_DetAddAll.EnableWindow(FALSE);
	m_BtnDiv_DetAdd.EnableWindow(FALSE);
	m_BtnDiv_DetDel.EnableWindow(FALSE);
	m_BtnDiv_DetChange.EnableWindow(FALSE);
	m_BtnDiv_DetLook.EnableWindow(FALSE);
	m_BtnDivSave.EnableWindow(FALSE);
	m_BtnDivExit.EnableWindow(FALSE);

	// 3 // Открываем окно для редктирования Датчика
	CDetectorsEdit* p_DetectorsEditDlg = new CDetectorsEdit;
	p_DetectorsEditDlg->Create(IDD_EDIT_DETECTOR_DLG, this);
	p_DetectorsEditDlg->ShowWindow(SW_SHOW);
	
	DetectorDlgHWND = p_DetectorsEditDlg->GetSafeHwnd();
}


// кнопка "Просмотреть Датчик" в Настройке Участка
void CDivisionEdit::OnBnClickedDivDetLookBtn()
{
	// TODO: добавьте свой код обработчика уведомлений
	// 0 // В случае с "Просмотр" нам важно получить Имя выбранного Датчика и проверять, что Датчик выбран в принципе.
	// 1 // Сохраняем Имя выбранного Датчика, чтобы использовать его в окне редактирования Датчика
	CString EmptyStr("");
	long nCount=0;		// Число записей в Listbox
	long curIndex=0;	// Индекс элемента выбранного в Listbox
	POSITION pos=NULL;	// Номер выбранного элемента (pos = curIndex+1)

	nCount = m_ListDiv_Det.GetItemCount();
	//взять выделенный элемент из списка отображения
	pos = m_ListDiv_Det.GetFirstSelectedItemPosition();
	if(pos==NULL) return;	 // В случае, если ничего не выбрано:
							// 1) не открываем окно редактирования Датчика
							// 2) не блокируем ни одну из кнопок
	curIndex = m_ListDiv_Det.GetNextSelectedItem(pos);
	if( curIndex == (-1) )  return;


	CString sDetSysName = m_ListDiv_Det.GetItemText(curIndex,0);	// 1 колонка
	CString sDetGrafName = m_ListDiv_Det.GetItemText(curIndex,1);	// 2 колонка
	//CString sDetNum = m_ListDiv_Det.GetItemText(curIndex,0);	// 1 колонка
	//CString sDetName = m_ListDiv_Det.GetItemText(curIndex,1);	// 2 колонка

	// 1.1 // Теперь через этот параметр все прочие окна будут знать имя датчика в системе и имя датчика на графике //номер и имя текущего Датчика
	theApp.CurDetSysName = sDetSysName;
	theApp.CurDetGrafName = sDetGrafName;
	//theApp.CurDetNum = sDetNum;
	//theApp.CurDetName = sDetName;
	// 1.2 // Теперь через этот параметр все прочие окна будут знать, что нажата кнопка "Просмотр"
	theApp.EditDivDetBtnClicked = theApp.DET_BTN_LOOK;

	// 2 // Блокируем все кнопки до тех пор пока пользователь не закончит работать с выбранным Датчиком
	//m_ListDiv_Det.EnableWindow(FALSE);
	//(список Датчиков) Оставляем доступным, чтобы в нём интерактивно можно было бы просматривать любой другой датчик по нажатию в списке
	m_BtnDiv_DetAddAll.EnableWindow(FALSE);
	m_BtnDiv_DetAdd.EnableWindow(FALSE);
	m_BtnDiv_DetDel.EnableWindow(FALSE);
	m_BtnDiv_DetChange.EnableWindow(FALSE);
	m_BtnDiv_DetLook.EnableWindow(FALSE);
	m_BtnDivSave.EnableWindow(FALSE);
	m_BtnDivExit.EnableWindow(FALSE);

	// 3 // Открываем окно для редктирования Датчика
	CDetectorsEdit* p_DetectorsEditDlg = new CDetectorsEdit;
	p_DetectorsEditDlg->Create(IDD_EDIT_DETECTOR_DLG, this);
	p_DetectorsEditDlg->ShowWindow(SW_SHOW);

	DetectorDlgHWND = p_DetectorsEditDlg->GetSafeHwnd();
}


// Нажатие на кнопку "Сохранить" из окна "Настроить Датчик"
LRESULT CDivisionEdit::OnDetectorEditSave( WPARAM wparam , LPARAM lparam )
{
	// 1 // По нажатию на кнопку "Сохранить" нам нужно в соответствие с новым строением вектора пересортировать связанный с ним вектор: theApp.DivDetectors  (theApp.DivSortDetectors формируется только в DetectorsEdit.cpp)
	// Это как выяснилось не требуцется, ибо это все возможные векторы, из XML-файла подходящие для данного участка, без дополнительного отсева по какому-то признаку

	// 2 // Пока мы только сохраняем всё в векторе, а не в файле .sou
		 // НО Список с датчиками при этом стоит Перезаполнить уже сейчас
	CString DetectorName(""); // Имя следующего Датчика

	m_ListDiv_Det.EnableWindow(TRUE);
	m_ListDiv_Det.DeleteAllItems(); // Предварительно опустошаем список

	//CRect rect;
	//m_ListDiv_Det.GetClientRect(rect);
	(void)m_ListDiv_Det.SetExtendedStyle( LVS_EX_FULLROWSELECT );
	//m_ListDiv_Det.SetHeadings( _T("№ места установки,		60;\
	//								Название датчика на графике,") + LintToCStr(rect.Width())
	//						 );
	//m_ListDiv_Det.LoadColumnInfo();

	//*
	// Заполняем список Названиями Участков используя названия файлов .sou из папки "Участки"
	long NumOfDet=0;
	long NumOfDetParams=0;
	if(theApp.FullDivision.size()>1)
	{ 
		NumOfDet = theApp.FullDivision.size() - 1;		// NumOfDet = Число датчиков (исключая первую запись с параметрами Участка) 
		NumOfDetParams = theApp.FullDivision[DIV_DET_HEAD].size();	// NumOfDetParams = Число параметров датчиков
	
		for(UINT i(DIV_DET_HEAD), j(DET_HEAD); j < NumOfDet; i++, j++)
		{
			/*
			m_ListDiv_Det.InsertItem(j, theApp.FullDivision[i][DIV_DET_NUMBER]); // в 1-ой колонке Имя Датчика в Системе // номер Датчика
			// так как нам нужны только:
			m_ListDiv_Det.SetItemText(j, 0, theApp.FullDivision[i][DIV_DET_NUMBER]); // в 1-ой колонке Имя Датчика в Системе // номер Датчика
			m_ListDiv_Det.SetItemText(j, 1, theApp.FullDivision[i][DIV_DET_NAME]); // во 2-ой колнке Название Датчика на Графике // Название Датчика
			*/

			(void)m_ListDiv_Det.AddItem(
										theApp.FullDivision[i][DIV_DET_NUMBER],
										theApp.FullDivision[i][DIV_DET_NAME]
									 );
		}
		m_ListDiv_Det.SetExtendedStyle( m_ListDiv_Det.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	}
	

	// 3 // Если пришло сообщение от "Сохранить новый датчик", то точно можно открывать все остальные кнопки.
	UINT nTestDivSortDetectorsNum = theApp.DivDetectors.size();		// Число датчиков, подходящих для данного участка
	UINT nCurDivisionDetectorsNum = theApp.FullDivision.size() - 1;	// Число датчиков установленных на участке (исключая первую запись с параметрами Участка) 

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
		ChecckForBtnSave(); // Проверяем можно ли активировать кнопку "Сохранить"

	return 0;
}


// Нажатие на кнопку "Выход" из окна "Настроить Датчик"
LRESULT CDivisionEdit::OnDetectorEditExit( WPARAM wparam , LPARAM lparam )
{
	// Если пришло сообщение от "Выход из датчика", то нужно проверить можно ли открывать все остальные кнопки.
	// Проверяем по числу элементов, находящихся в списке
	UINT nTestDivSortDetectorsNum = theApp.DivDetectors.size();		// Число датчиков, подходящих для данного участка
	UINT nCurDivisionDetectorsNum = theApp.FullDivision.size() - 1;	// Число датчиков установленных на участке (исключая первую запись с параметрами Участка) 

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

	// Однако есть ещё один уникальный случай, когда мы вошли в "Просмотрт Участка" -> "Просмотр Датчика" -> вышли из Датчика
	// В этом случае так как активен режим просмотра всё равно нужно блокировать всё кроме кнопок "Просмотр Датчика" и "Выход"
	if(theApp.ChangeDivBtnClicked == theApp.DIV_BTN_LOOK)
	{
		m_BtnDiv_DetAddAll.EnableWindow(FALSE);
		m_BtnDiv_DetAdd.EnableWindow(FALSE);
		m_BtnDiv_DetDel.EnableWindow(FALSE);
		m_BtnDiv_DetChange.EnableWindow(FALSE);
		m_BtnDiv_DetLook.EnableWindow(TRUE);
		
		m_BtnDivSave.EnableWindow(FALSE); // Так как сохранять нечего
		m_BtnDivExit.EnableWindow(TRUE);
	}
	else
	{
		if(bFirstDlg) 
			ChecckForBtnSave(); // Проверяем можно ли активировать кнопку "Сохранить"
	}

	return 0;
}



// кнопка "Сохранить Участок" ДОСТУПНА, когда: 1) Имеется Имя Участка 2) Имеется Продукт на Участке 3) Установлен "параметр" = "Давление" 3) На участке установлен хотябы 1 датчик
void CDivisionEdit::ChecckForBtnSave()
{
	CString EmptyStr("");
	CString CurDivisionFName("");
	CString CurDivisionName("");
	CString CurDivisionPipe("");
	CString CurDivisionProd("");
////	CString CurDivisionParam("");
	CString Preassure("Давление");
	long CurDivisionDet=0;


	m_EditDivFileName.GetWindowText(CurDivisionFName);
	m_EditDivName.GetWindowText(CurDivisionName);
	int curIndex(0);			// Индекс элемента выбранного в Combobx
	curIndex = m_CmBxDivProd.GetCurSel();
	if(curIndex != (-1))	m_CmBxDivProd.GetLBText( curIndex, CurDivisionProd );
	curIndex = m_CmBxDivPipe.GetCurSel();
	if(curIndex != (-1))	m_CmBxDivPipe.GetLBText( curIndex, CurDivisionPipe );


////	m_EditDivParam.GetWindowText(CurDivisionParam);
	int nCount=0;			// Число записей в Listbox
	nCount = m_ListDiv_Det.GetItemCount();
	// Тут же осуществим проверку на доступность выпадающего списка с Продуктом:
	//if(nCount>0)
	//	m_CmBxDivProd.EnableWindow(FALSE);
	//else
	//	m_CmBxDivProd.EnableWindow(FALSE); //m_CmBxDivProd.EnableWindow(TRUE);

//	лишь старания сделать кого то счастливым и будет становлением из незрелого мальчишки в более серьезного парня/мужчину.


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
//////////////////// ПРОЧИЕ МЕТОДЫ

// #include <io.h>
// Функция _findfirst возвращает информацию о первом файле, удовлетворяющем заданной маске поиска.
bool CDivisionEdit::FileExists(const wchar_t *fname)
{
  //_finddata_t data;
  _wfinddata_t data;
  //long nFind = _findfirst(fname, &data);
  long nFind = _wfindfirst(fname, &data);
  if (nFind != -1)
  {
    // Если этого не сделать, то произойдет утечка ресурсов
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
	// TODO: добавьте свой код обработчика уведомлений
	//if(theApp.ChangeDivBtnClicked == theApp.DIV_BTN_ADD) // нажата кнопка "Добавить Участок"
	//{FirstFileNameSFocus=false;}
}


void CDivisionEdit::OnEnKillfocusDivNameEdit()
{
	// TODO: добавьте свой код обработчика уведомлений
	//if(theApp.ChangeDivBtnClicked == theApp.DIV_BTN_ADD) // нажата кнопка "Добавить Участок"
	//{
	//	if(FirstFileNameSFocus)
	//	FirstFileNameKFocus=false;
	//}
}


void CDivisionEdit::OnEnSetfocusDivFileNameEdit()
{
	// TODO: добавьте свой код обработчика уведомлений
	//if(theApp.ChangeDivBtnClicked == theApp.DIV_BTN_ADD) // нажата кнопка "Добавить Участок"
	//{FirstNameSFocus=false;}
}


void CDivisionEdit::OnEnKillfocusDivFileNameEdit()
{
	// TODO: добавьте свой код обработчика уведомлений
	//if(theApp.ChangeDivBtnClicked == theApp.DIV_BTN_ADD) // нажата кнопка "Добавить Участок"
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
		case VK_TAB:// Нажата клавиша TAB.
			AfxMessageBox(_T("TAB"));
		case VK_RETURN:// Нажата клавиша ENTER.
			//AfxMessageBox(_T("ENTER"));
			pMsg->wParam = VK_TAB;
		break;
		case VK_UP: // Нажата стрелка вверх.
			AfxMessageBox(_T("UP"));
		break;
		case VK_DOWN: // Нажата стрелка вниз.
			AfxMessageBox(_T("DOWN"));
		break;
		/*
		case VK_LEFT: // Нажата стрелка влево.
		break;
		case VK_RIGHT: // Нажата стрелка враво.
		break;
		case VK_HOME: // Нажата клавиша HOME.
		break;
		case VK_END:// Нажата клавиша END.
		break;
		case VK_INSERT:// Нажата клавиша INS.
		break;
		case VK_DELETE:// Нажата клавиша DEL.
		break;
		case VK_F2:// Нажата клавиша F2.
		break;
		// Обработка других не-буквенных клавиш.
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


CString CDivisionEdit::DoubleToCStr(double x, int count) // x - число, count - число знаков после запятой
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
		{//Всё в порядке
			if(StrToCheck[i] == k10) // в случае если встретилиь 2 запятые, удаляем последнюю встретившуюся
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
	{return true;} // строка неизменилась
	else
	{return false;} // строка изменилась
}

// Написано до 100.000 копии, +нужно дописать используя рекурсию
bool CDivisionEdit::CheckFileNameCopyString(CString& StrToCheck, long Next)
{
	CString OrigString=StrToCheck;
	CString ResString("");		    // 123456789112
	CString CopyAdd(" - копия (1)");// _-_копия_(1)
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
		if(	( StrToCheck[StrToCheck.GetLength() - 1] == (CString)"я" ) &&
			( StrToCheck[StrToCheck.GetLength() - 2] == (CString)"и" ) &&
			( StrToCheck[StrToCheck.GetLength() - 3] == (CString)"п" ) &&
			( StrToCheck[StrToCheck.GetLength() - 4] == (CString)"о" ) &&
			( StrToCheck[StrToCheck.GetLength() - 5] == (CString)"к" ) &&
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
							( StrToCheck[StrToCheck.GetLength() - (j+4)] == (CString)"я" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+5)] == (CString)"и" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+6)] == (CString)"п" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+7)] == (CString)"о" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+8)] == (CString)"к" ) &&
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
							( StrToCheck[StrToCheck.GetLength() - (j+4)] == (CString)"я" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+5)] == (CString)"и" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+6)] == (CString)"п" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+7)] == (CString)"о" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+8)] == (CString)"к" ) &&
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
							( StrToCheck[StrToCheck.GetLength() - (j+4)] == (CString)"я" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+5)] == (CString)"и" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+6)] == (CString)"п" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+7)] == (CString)"о" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+8)] == (CString)"к" ) &&
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
							( StrToCheck[StrToCheck.GetLength() - (j+4)] == (CString)"я" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+5)] == (CString)"и" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+6)] == (CString)"п" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+7)] == (CString)"о" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+8)] == (CString)"к" ) &&
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
							( StrToCheck[StrToCheck.GetLength() - (j+4)] == (CString)"я" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+5)] == (CString)"и" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+6)] == (CString)"п" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+7)] == (CString)"о" ) &&
							( StrToCheck[StrToCheck.GetLength() - (j+8)] == (CString)"к" ) &&
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
			( StrToCheck[StrToCheck.GetLength() - 5] == 'я' ) &&
			( StrToCheck[StrToCheck.GetLength() - 6] == 'и' ) &&
			( StrToCheck[StrToCheck.GetLength() - 7] == 'п' ) &&
			( StrToCheck[StrToCheck.GetLength() - 8] == 'о' ) &&
			( StrToCheck[StrToCheck.GetLength() - 9] == 'к' ) &&
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
		{ResString = StrToCheck + _T(" - копия (") + LintToCStr(Next) + _T(")");}
	}

	StrToCheck = ResString;

	if(OrigString == ResString)
	{return true;} // строка неизменилась
	else
	{return false;} // строка изменилась
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
		CRect CurrentRect(NULL); // Текущий размер
		this->GetWindowRect(&CurrentRect);
		LONG CurW = CurrentRect.right - CurrentRect.left;
		LONG CurH = CurrentRect.bottom - CurrentRect.top;

		if( (CurW > OrigW) || (CurH > OrigH) )
		{
			LONG DeltaW = CurW - OrigW;
			LONG DeltaH = CurH - OrigH;

			CRect CurObjectRect(NULL);
			CWnd *pWnd = NULL;

			// Меняем размеры:	Edit-бокса с именем Участка
			pWnd = GetDlgItem(IDC_DIV_NAME_EDIT);
			pWnd->GetWindowRect(&CurObjectRect);
			ScreenToClient(&CurObjectRect);
			m_EditDivName.MoveWindow( CurObjectRect.left	, CurObjectRect.top		, formWidthArg - CurObjectRect.left - 15	, CurObjectRect.Height()	);
		
			// Меняем размеры:	Edit-бокса с именем Файла Участка
			pWnd = GetDlgItem(IDC_DIV_FILE_NAME_EDIT);
			pWnd->GetWindowRect(&CurObjectRect);
			ScreenToClient(&CurObjectRect);
			m_EditDivFileName.MoveWindow( CurObjectRect.left , CurObjectRect.top	, formWidthArg - CurObjectRect.left - 15	, CurObjectRect.Height()	);

			// Меняем размеры:	Static-бокса над List-боксом с Датчиками
			pWnd = GetDlgItem(IDC_DIV_DETECTORS_STATIC);
			pWnd->GetWindowRect(&CurObjectRect);
			ScreenToClient(&CurObjectRect);
			m_StaticDiv_Det.MoveWindow( CurObjectRect.left	, CurObjectRect.top		, formWidthArg - CurObjectRect.left - 15	, CurObjectRect.Height()	);
						
			// Меняем размеры:	List-бокса с Датчиками
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
			// Меняем размеры и позиции:	Кнопок под Листбоксом с Датчиками

			// Меняем позицию:
			pWnd = GetDlgItem(IDC_DIV_DET_ADD_ALL_BTN);
			pWnd->GetWindowRect(&CurObjectRect);
			ScreenToClient(&CurObjectRect);
			m_BtnDiv_DetAddAll.MoveWindow( CurObjectRect.left	, formHeightArg - 30, CurObjectRect.Width()	, CurObjectRect.Height()	);

			// Меняем позицию:
			pWnd = GetDlgItem(IDC_DIV_ADD_BTN);
			pWnd->GetWindowRect(&CurObjectRect);
			ScreenToClient(&CurObjectRect);
			m_BtnDiv_DetAdd.MoveWindow( CurObjectRect.left	, formHeightArg - 30, CurObjectRect.Width()	, CurObjectRect.Height()	);

			// Меняем позицию:
			pWnd = GetDlgItem(IDC_DIV_DET_DELL_BTN);
			pWnd->GetWindowRect(&CurObjectRect);
			ScreenToClient(&CurObjectRect);
			m_BtnDiv_DetDel.MoveWindow( CurObjectRect.left	, formHeightArg - 30, CurObjectRect.Width()	, CurObjectRect.Height()	);

			// Меняем позицию:
			pWnd = GetDlgItem(IDC_DIV_DET_CHANGE_BTN);
			pWnd->GetWindowRect(&CurObjectRect);
			ScreenToClient(&CurObjectRect);
			m_BtnDiv_DetChange.MoveWindow( CurObjectRect.left	, formHeightArg - 30, CurObjectRect.Width()	, CurObjectRect.Height()	);

			// Меняем позицию:
			pWnd = GetDlgItem(IDC_DIV_DET_LOOK_BTN);
			pWnd->GetWindowRect(&CurObjectRect);
			ScreenToClient(&CurObjectRect);
			m_BtnDiv_DetLook.MoveWindow( CurObjectRect.left	, formHeightArg - 30, CurObjectRect.Width()	, CurObjectRect.Height()	);

			int u=0;
		}
		else
		{
		} // Данный случай нас не интересует
	}
//#endif


#if 0

/*
template< typename T >
void sort( T array[], int size )   // объявление и определение
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
	return _T("Структура файла не соответствует соглашениям СОУ.");

	if(DescriptionEng == _T("No error") )
	{return _T("Нет ошибок");}
	else	if(DescriptionEng == _T("Error") )
	{return _T("Неопределённая ошибка");}
	else 	if(DescriptionEng == _T("Failed to open file") )
	{return _T("Ошибка при открытии файла");}
	else 	if(DescriptionEng == _T("Error parsing Element.") )
	{return _T("Ошибка при разборе (парсинге) Элемента");}
	else 	if(DescriptionEng == _T("Failed to read Element name") )
	{return _T("Ошибка при чтении имени Элемента");}
	else 	if(DescriptionEng == _T("Error reading Element value.") )
	{return _T("Ошибка при чтении значения Элемента");}
	else 	if(DescriptionEng == _T("Error reading Attributes.") )
	{return _T("Ошибка при чтении Атрибута");}
	else 	if(DescriptionEng == _T("Error: empty tag.") )
	{return _T("Ошибка - Пустой тег");}
	else 	if(DescriptionEng == _T("Error reading end tag.") )
	{return _T("Ошибка при чтении последнего тега");}
	else 	if(DescriptionEng == _T("Error parsing Unknown.") )
	{return _T("Неопределённая ошибка во время разбора (парсинга) файла");}
	else 	if(DescriptionEng == _T("Error parsing Comment.") )
	{return _T("Ошибка при чтении (парсинге) Комментария");}
	else 	if(DescriptionEng == _T("Error parsing Declaration.") )
	{return _T("Ошибка при чтении (парсинге) Объявления (заголовка) файла");}
	else 	if(DescriptionEng == _T("Error document empty.") )
	{return _T("Ошибка - файл пуст (или обнаружена пустая строка)");}
	else 	if(DescriptionEng == _T("Error null (0) or unexpected EOF found in input stream.") )
	{return _T("Ошибка NULL (0) или обнаружен непредвиденный конец файла во входящем потоке");}
	else 	if(DescriptionEng == _T("Error parsing CDATA.") )
	{return _T("Ошибка при чтении (парсинге) CDATA");}
	else 	if(DescriptionEng == _T("Error when TiXmlDocument added to document, because TiXmlDocument can only be at the root.") )
	{return _T("Error when TiXmlDocument added to document, because TiXmlDocument can only be at the root");}
}
*/




