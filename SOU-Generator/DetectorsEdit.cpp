// DetectorsEdit.cpp: файл реализации
//

#include "stdafx.h"
#include "SOU-Generator.h"
#include "DetectorsEdit.h"
#include "afxdialogex.h"


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


/*
#define DIV_DET_NAME	0
#define DIV_DET_NUMBER	1
#define DIV_DET_ACTIVE	2
#define DIV_DET_PATH	3
#define DIV_DET_PTFIX	4
#define DIV_DET_DIST	5
#define DIV_DET_DPRESS	6
#define DIV_DET_DTIIME	7

#define DET_NUMBER		0
#define DET_NAME		1
#define DET_POSTFIX		2
#define DET_DISTANCE	3
#define DET_FILE_PATH	4
#define DET_PROD_TYPE	5
#define DET_PROD_ID		6
#define DET_WAVE_SPEED	7
//*/

// диалоговое окно CDetectorsEdit

IMPLEMENT_DYNAMIC(CDetectorsEdit, CDialog)

CDetectorsEdit::CDetectorsEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CDetectorsEdit::IDD, pParent)
{

}

CDetectorsEdit::~CDetectorsEdit()
{
}

// m_CmBxDetNum // m_CmBxDetNum
void CDetectorsEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DET_NUM_CMBX, m_CmBxDetNum);
	DDX_Control(pDX, IDC_DET_NAME_GRAF_EDIT, m_EditDetGrafName);
	DDX_Control(pDX, IDC_DET_ACTIVE_EDIT, m_EditDetActive);
	DDX_Control(pDX, IDC_DET_PATH_EDIT, m_EditDetPath);
	DDX_Control(pDX, IDC_DET_PTFIX_EDIT, m_EditDetPostFix);
	DDX_Control(pDX, IDC_DET_DISTANCE_EDIT, m_EditDetDist);
	DDX_Control(pDX, IDC_DET_DPRESS_EDIT, m_EditDetDPress);
	DDX_Control(pDX, IDC_DET_DTIME_EDIT, m_EditDetDTime);
	DDX_Control(pDX, IDOK, m_BtnDetOK);
	DDX_Control(pDX, IDC_DET_SAVE_BTN, m_BtnDetSave);
	DDX_Control(pDX, IDCANCEL, m_BtnDetExit);
	DDX_Control(pDX, IDC_DET_NUM_EDIT, m_EditDetNum);
}


BEGIN_MESSAGE_MAP(CDetectorsEdit, CDialog)
	ON_BN_CLICKED(IDOK, &CDetectorsEdit::OnBnClickedOk)
	ON_BN_CLICKED(IDC_DET_SAVE_BTN, &CDetectorsEdit::OnBnClickedDetSaveBtn)
	ON_BN_CLICKED(IDCANCEL, &CDetectorsEdit::OnBnClickedCancel)
	//ON_CBN_SELCHANGE(IDC_DET_NUM_CMBX, &CDetectorsEdit::OnCbnSelchangeDetNumCmbx)
	ON_CBN_SELCHANGE(IDC_DET_NAME_CMBX, &CDetectorsEdit::OnCbnSelchangeDetNameCmbx)
	ON_EN_CHANGE(IDC_DET_NAME_GRAF_EDIT, &CDetectorsEdit::OnEnChangeDetGrafNameEdit)
	ON_EN_CHANGE(IDC_DET_DPRESS_EDIT, &CDetectorsEdit::OnEnChangeDetDpressEdit)
	ON_EN_CHANGE(IDC_DET_DTIME_EDIT, &CDetectorsEdit::OnEnChangeDetDtimeEdit)
	ON_MESSAGE(WM_DIV_DETECTOR_CHANGE, &CDetectorsEdit::OnDivDetectorChange)
	ON_EN_SETFOCUS(IDC_DET_DPRESS_EDIT, &CDetectorsEdit::OnEnSetfocusDetDpressEdit)
	ON_EN_KILLFOCUS(IDC_DET_DPRESS_EDIT, &CDetectorsEdit::OnEnKillfocusDetDpressEdit)
	ON_EN_SETFOCUS(IDC_DET_DTIME_EDIT, &CDetectorsEdit::OnEnSetfocusDetDtimeEdit)
	ON_EN_KILLFOCUS(IDC_DET_DTIME_EDIT, &CDetectorsEdit::OnEnKillfocusDetDtimeEdit)
END_MESSAGE_MAP()


// обработчики сообщений CDetectorsEdit

BOOL CDetectorsEdit::OnInitDialog()
{
	CDialog::OnInitDialog();


	m_BtnDetOK.ShowWindow(FALSE);

	CString EmptyStr("");

	// Есть неизменяющиеся параметры:
	// Для Датчика это "Активен", всегда и по умолчанию равен = "1"
	long NumOfDet(0), NumOfDetParams(0);
	bool DetNumFound(false);		// если "тру", то мы нашли номер выбранного датчика среди отсеянных из XML-файла по продукту
	bool DetectorFound(false);	// если "тру", то мы нашли датчик в .sou файле

	switch(theApp.EditDivDetBtnClicked)
	{
	case theApp.DET_BTN_ADD: // нажата кнопка "Добавить"
		// Заполним все значения для Датчика:
		// 1 // Заполним Выпадающий список номерами и именами всех датчиков, из вектора theApp.DivDetectors
		m_CmBxDetNum.Clear();									 // нр				// Только Выбор через Выпадающий список

		// Все участки у нас на данном этапе имеются сохранённые вот в этом векторе: theApp.FullDivision[1...n][0...m]
		// Не забываем, что первый векторный эелемент в нём содержит записи самого Участка, и только все остальные записи хранят информацию о датчиках
		// ИТАК заполним теперь уже последний вектор: theApp.DivDetectors[0...n][0...m], в котором будут находиться только те Датчики, 
		// которые могут быть установлены на данном участке. Так как на участке выбран продукт, мы сможем произвести отсев и сформировать такой вектор.

		// 1.1	Произведём предварительную сортировку по датчикам, чтобы получить все датчики, что могут 
		//		находиться на данном участке, согласно продукту, утсановленному на этом участке.
		
		// это мы уже сделали в предыдущем окне:
		/* Тут же по продукту на Участке заполним и вектор датчиков, которые будут соответсвовать установленному на участке продукту
		theApp.DivDetectors.clear();
		for(long v=0, t=0; v<theApp.AllDetectors.size(); v++)
		{
			if(theApp.AllDetectors[v][5] == theApp.FullDivision[0][1])
			{theApp.DivDetectors.push_back(theApp.AllDetectors[v]);}
			//theApp.DIVDET_NUM = theApp.DivDetectors.size();
		}
		*/

		// 1.2	Произведём дополнительную сортировку по датчикам, что уже установлены на участке
		//		чтобы в выпадающем списке были только неповторяющиеся датчики соответсвенно, ибо 2-ух одинаковых датчиков на участке быть не может
		//		Из  theApp.DivDetectors[0...n][]  достаточно удалить все  theApp.FullDivision[1...n][] 
		theApp.DivSortDetectors.clear();
		theApp.DivSortDetectors = theApp.DivDetectors; // ELSE // по этой причине ничего не делаем в ELSE
		if(theApp.FullDivision.size() > 1)
		{
			for(long j=1; j<theApp.FullDivision.size(); j++)
			{
				for(long i=0; i<theApp.DivSortDetectors.size(); i++)
				{
					//if(theApp.DivSortDetectors[i][0] == theApp.FullDivision[j][0])
					if(theApp.DivSortDetectors[i][DET_NUMBER] == theApp.FullDivision[j][DIV_DET_NUMBER])
					{
						theApp.DivSortDetectors.erase(theApp.DivSortDetectors.begin()+i); // удалить из вектора i-тый датчик (элемент)
						break;
					}
				}
			}
		}
		else // ELSE // В случае если на участке нет Датчиков, то просто заполняем отсортированные по Продукту датчики что получили из XML-файла
		{
			//for(long i=0; i<theApp.DivDetectors.size(); i++)
			//{
			//	theApp.DivSortDetectors.push_back(theApp.DivDetectors[i]);
			//}
		}

		/*
		for(long i=0; i<theApp.DivDetectors.size(); i++)
		{
			if(theApp.FullDivision.size() > 1)
			{
				for(long j=1; j<theApp.FullDivision.size(); j++)
				{
					if(theApp.DivDetectors[i][0] != theApp.FullDivision[j][0])
					{
						theApp.DivSortDetectors.push_back(theApp.DivDetectors[i]);
						//break;
					}
				}
			}
			else // В случае если на участке нет Датчиков, то просто заполняем отсортированные по Продукту датчики что получили из XML-файла
			{
				theApp.DivSortDetectors.push_back(theApp.DivDetectors[i]);
			}
		}
		*/

		if(theApp.DivSortDetectors.size() != 0)
		{
			for(long i=0; i<theApp.DivSortDetectors.size(); i++)
			{
				m_CmBxDetNum.EnableWindow(TRUE);
				CString NumPlusName = 
					theApp.DivSortDetectors[i][DET_NUMBER]
					+ _T(" - ")
					+ theApp.DivSortDetectors[i][DET_NAME];
				m_CmBxDetNum.AddString(NumPlusName);
				//m_CmBxDetNum.AddString(theApp.DivSortDetectors[i][DET_NUMBER]);
			}
		}
		else

		// 2 // Для случая с "Добавить" в списке остаётся ничего не выбранно
		// 3 // Наконец для "Добавить" заполним у Датчика все его параметры по умолчанию:
		/*
		m_EditDetGrafName.SetWindowText(EmptyStr);					 // имя				// НЕ МЕНЯЕТСЯ ПОЛЬЗОВАТЕЛЕМ
		m_EditDetActive.SetWindowText(_T("1"));						 // активен			// НЕ МЕНЯЕТСЯ ПОЛЬЗОВАТЕЛЕМ = "1" ВСЕГДА
		m_EditDetPath.SetWindowText(EmptyStr);						 // путь			// НЕ МЕНЯЕТСЯ ПОЛЬЗОВАТЕЛЕМ
		m_EditDetPostFix.SetWindowText(EmptyStr);					 // постфикс		// НЕ МЕНЯЕТСЯ ПОЛЬЗОВАТЕЛЕМ
		m_EditDetDist.SetWindowText(EmptyStr);			//км		 // удаление		// НЕ МЕНЯЕТСЯ ПОЛЬЗОВАТЕЛЕМ
		m_EditDetDPress.SetWindowText(_T("0.010"));		//кгс/(см^2) // дельта_давление	// РЕДАКТИРУЕМЫЙ			 = [По умолчанию = 0.010]
		m_EditDetDTime.SetWindowText(_T("0.5"));		//сек		 //	дельта_время	// РЕДАКТИРУЕМЫЙ			 = [По умолчанию = 0.5 ]
		*/

		m_EditDetGrafName.EnableWindow(FALSE);						 // имя				// РЕДАКТИРУЕМЫЙ			 = [По умолчанию = ИМЯ Датчика в системе]
		m_EditDetActive.EnableWindow(FALSE);						 // активен			// НЕ МЕНЯЕТСЯ ПОЛЬЗОВАТЕЛЕМ = "1" ВСЕГДА
		m_EditDetPath.EnableWindow(FALSE);							 // путь			// НЕ МЕНЯЕТСЯ ПОЛЬЗОВАТЕЛЕМ
		m_EditDetPostFix.EnableWindow(FALSE);						 // постфикс		// НЕ МЕНЯЕТСЯ ПОЛЬЗОВАТЕЛЕМ
		m_EditDetDist.EnableWindow(FALSE);				//км		 // удаление		// НЕ МЕНЯЕТСЯ ПОЛЬЗОВАТЕЛЕМ
		m_EditDetDPress.EnableWindow(FALSE);			//кгс/(см^2) // дельта_давление	// РЕДАКТИРУЕМЫЙ			 = [По умолчанию = 0.010]
		m_EditDetDTime.EnableWindow(FALSE);				//сек		 //	дельта_время	// РЕДАКТИРУЕМЫЙ			 = [По умолчанию = 0.5 ]
		
		m_BtnDetSave.EnableWindow(FALSE);

		break;
	case theApp.DET_BTN_CHANGE: //нажата кнопка "Изменить"
		// Заполним все значения для Датчика:
		// 1 // Заполним Выпадающий список номерами и именами всех датчиков, из вектора theApp.DivDetectors
		m_CmBxDetNum.Clear();

		// 1.1	Произведём дополнительную сортировку по датчикам, что уже установлены на участке
		//		чтобы в выпадающем списке были только неповторяющиеся датчики соответсвенно, ибо 2-ух одинаковых датчиков на участке быть не может
		//		Из  theApp.DivDetectors[0...n][]  достаточно удалить все  theApp.FullDivision[1...n][] 
		theApp.DivSortDetectors.clear();
		for(long i=0; i<theApp.DivDetectors.size(); i++)
		{
			for(long j=1; j<theApp.FullDivision.size(); j++)
			{
				if(theApp.DivDetectors[i][DET_NUMBER] != theApp.FullDivision[j][DIV_DET_NUMBER])
				{
					theApp.DivSortDetectors.push_back(theApp.DivDetectors[i]);
					break;
				}
			}
		}

		for(long i=0; i<theApp.DivSortDetectors.size(); i++)
		{
			//m_CmBxDetNum.AddString(theApp.DivSortDetectors[i][DET_NUMBER]);

			CString NumPlusName = 
				theApp.DivSortDetectors[i][DET_NUMBER]
				+ _T(" - ")
				+ theApp.DivSortDetectors[i][DET_NAME];
			m_CmBxDetNum.AddString(NumPlusName);
		}
		// 2 // В выпадающем же Списке выставим выбранным тот Датчик на который нажали в предыдущем окне
		// 1-ый вариант
		for(long k=0; k<theApp.DivSortDetectors.size(); k++)
		{
			//CString LBNumber;
			//m_CmBxDetNum.GetLBText(k,LBNumber);
			CString LBSysName;
			m_CmBxDetNum.GetLBText(k,LBSysName);
			//if( LBNumber == theApp.CurDetNum) //theApp.FullDivision[?][0])
			CString NumPlusName = 
				theApp.CurDetSysName
				+ _T(" - ")
				+ theApp.CurDetGrafName;

			//if( LBSysName == theApp.CurDetSysName) //theApp.FullDivision[?][0])
			if( LBSysName == NumPlusName) //theApp.FullDivision[?][0])
			{
				m_CmBxDetNum.SetCurSel(k); DetNumFound=true;
				break;
			}
		}
		// НЮАНС: Если в списке Датчиков не будет того датчика, что указан в .sou файле, то номер датчика так и останется незаполненным:
		/* 2-ой вариант
		for(long i=1; i < NumOfDet; i++)
		{
			if( (theApp.FullDivision[i][0] == theApp.CurDetNum) && (theApp.FullDivision[i][1] == theApp.CurDetName) ) // в 1-ой колонке номер Датчика // во 2-ой колнке Название Датчика
			{
				DetectorFound=true;
				m_EditDetGrafName.SetWindowText(theApp.FullDivision[i][0]);
				for(long k=0; k<theApp.DivSortDetectors.size(); k++)
				{
					CString LBNumber;
					m_CmBxDetNumber.GetLBText(k,LBNumber);
					if( LBNumber == theApp.FullDivision[i][0])
					{m_CmBxDetNumber.SetCurSel(k); break;}
				}
				break;
			}
		}
		//*/
		// 3 // Наконец по выставленному датчику и его номеру найдём его в векторе theApp.FullDivision и заполним все его параметры:
		NumOfDet=0;
		NumOfDetParams=0;
		if(theApp.FullDivision.size()>1)
		{
			NumOfDet = theApp.FullDivision.size() - 1;		// NumOfDet = Число датчиков (исключая первую запись с параметрами Участка) 
			NumOfDetParams = theApp.FullDivision[1].size();	// NumOfDetParams = Число параметров датчиков
		}
		
		for(long i=1; i < (NumOfDet+1); i++)
		{
			//if( (theApp.FullDivision[i][0] == theApp.CurDetNum) && (theApp.FullDivision[i][1] == theApp.CurDetName) ) // в 1-ой колонке номер Датчика // во 2-ой колнке Название Датчика
			if( (theApp.FullDivision[i][DIV_DET_NUMBER] == theApp.CurDetSysName) ) //&& (theApp.FullDivision[i][1] == theApp.CurDetName) ) // в 1-ой колонке номер Датчика // во 2-ой колнке Название Датчика
			{
				DetectorFound=true;
				//for(long j=0; j < NumOfDetParams; j++)
				//{
		// НЮАНС: Если в сипске Датчиков не будет того датчика, что указан в .sou файле, то номер дотчика так и останется незаполненным, поэтому:
		// мы решаем данную ситуацию так: берём номер из .sou файла и помещаем его в  конец выпадающего списка
				int curIndex=0;			// Индекс элемента выбранного в Combobx
				curIndex = m_CmBxDetNum.GetCurSel();
				//if( curIndex == (-1) )  return;

				if( (curIndex == -1) && (!DetNumFound) )
				{
					//m_CmBxDetNum.AddString(theApp.FullDivision[i][0]);

					CString NumPlusName =
						theApp.FullDivision[i][DIV_DET_NUMBER]
						+ _T(" - ")
						+ theApp.FullDivision[i][DIV_DET_NAME];
					m_CmBxDetNum.AddString(NumPlusName);
					//m_CmBxDetNum.AddString(theApp.FullDivision[i][DIV_DET_NUMBER]);
					m_CmBxDetNum.SetCurSel(m_CmBxDetNum.GetCount()-1);
				}
				if(theApp.FullDivision[i][DIV_DET_NAME] == EmptyStr)
				{theApp.FullDivision[i][DIV_DET_NAME] = theApp.FullDivision[i][DIV_DET_NUMBER];}

				m_EditDetNum.SetWindowText(		theApp.FullDivision[i][DIV_DET_NUMBER]);
				m_EditDetGrafName.SetWindowText(theApp.FullDivision[i][DIV_DET_NAME]);
				m_EditDetActive.SetWindowText(	theApp.FullDivision[i][DIV_DET_ACTIVE]);
				m_EditDetPath.SetWindowText(	theApp.FullDivision[i][DIV_DET_PATH]);
				m_EditDetPostFix.SetWindowText(	theApp.FullDivision[i][DIV_DET_PTFIX]);
				m_EditDetDist.SetWindowText(	theApp.FullDivision[i][DIV_DET_DIST]);
				m_EditDetDPress.SetWindowText(	theApp.FullDivision[i][DIV_DET_DPRESS]);
				m_EditDetDTime.SetWindowText(	theApp.FullDivision[i][DIV_DET_DTIIME]);
				//}
				break;
			}
		}

		// В случае с кнопкой "Изменить" заблокируем только: 1. Выпадающий список
		m_CmBxDetNum.EnableWindow(FALSE);
		//m_EditDetGrafName.EnableWindow(TRUE);

		break;
	case theApp.DET_BTN_LOOK: // нажата кнопка "Просмотр"
		// Заполним все значения для Датчика:
		// 1 // Заполним Выпадающий список номерами и именами всех датчиков, из вектора theApp.DivDetectors
		m_CmBxDetNum.Clear();
		for(long i=0; i<theApp.DivDetectors.size(); i++)
		{
			CString NumPlusName = 
				theApp.DivDetectors[i][DET_NUMBER]
				+ _T(" - ")
				+ theApp.DivDetectors[i][DET_NAME];
			m_CmBxDetNum.AddString(NumPlusName);

			//m_CmBxDetNum.AddString(theApp.DivDetectors[i][DET_NUMBER]);
		}
		// 2 // В выпадающем же Списке выставим выбранным тот Датчик на который нажали в предыдущем окне
		for(long k=0; k<theApp.DivDetectors.size(); k++)
		{
			//CString LBNumber;
			//m_CmBxDetNum.GetLBText(k,LBNumber);
			CString LBSysName;
			m_CmBxDetNum.GetLBText(k,LBSysName);

			CString NumPlusName = 
				theApp.CurDetSysName
				+ _T(" - ")
				+ theApp.CurDetGrafName;

			//if( LBNumber == theApp.CurDetNum) //theApp.FullDivision[?][0])
			//if( LBSysName == theApp.CurDetSysName) //theApp.FullDivision[?][0])
			if( LBSysName == NumPlusName) //theApp.FullDivision[?][0])
			{
				m_CmBxDetNum.SetCurSel(k); DetNumFound=true;
				break;
			}
		}
		// 3 // Наконец по выставленному датчику и его номеру найдём его в векторе theApp.FullDivision и заполним все его параметры:
		NumOfDet=0;
		NumOfDetParams=0;
		if(theApp.FullDivision.size()>1)
		{
			NumOfDet = theApp.FullDivision.size() - 1;		// NumOfDet = Число датчиков (исключая первую запись с параметрами Участка) 
			NumOfDetParams = theApp.FullDivision[1].size();	// NumOfDetParams = Число параметров датчиков
		}
		
		for(long i=1; i < (NumOfDet+1); i++)
		{
			//if( (theApp.FullDivision[i][0] == theApp.CurDetNum) && (theApp.FullDivision[i][1] == theApp.CurDetName) ) // в 1-ой колонке номер Датчика // во 2-ой колнке Название Датчика
			if( (theApp.FullDivision[i][DIV_DET_NUMBER] == theApp.CurDetSysName) ) //&& (theApp.FullDivision[i][1] == theApp.CurDetName) ) // в 1-ой колонке номер Датчика // во 2-ой колнке Название Датчика
			{
				DetectorFound=true;
				//for(long j=0; j < NumOfDetParams; j++)
				//{
				int curIndex=0;			// Индекс элемента выбранного в Combobx
				curIndex = m_CmBxDetNum.GetCurSel();
				//if( curIndex == (-1) )  return;

				if( (curIndex == -1) && (!DetNumFound) )
				{
					CString NumPlusName = 
						theApp.FullDivision[i][DIV_DET_NUMBER]
						+ _T(" - ")
						+ theApp.FullDivision[i][DIV_DET_NAME];
					m_CmBxDetNum.AddString(NumPlusName);
					
					//m_CmBxDetNum.AddString(theApp.FullDivision[i][DIV_DET_NUMBER]);
					//m_CmBxDetNum.AddString(theApp.FullDivision[i][0]);
					
					
					m_CmBxDetNum.SetCurSel(m_CmBxDetNum.GetCount()-1);
				}
				if(theApp.FullDivision[i][DIV_DET_NAME] == EmptyStr)
				{theApp.FullDivision[i][DIV_DET_NAME] = theApp.FullDivision[i][DIV_DET_NUMBER];}

				m_EditDetNum.SetWindowText(		theApp.FullDivision[i][DIV_DET_NUMBER]);
				m_EditDetGrafName.SetWindowText(theApp.FullDivision[i][DIV_DET_NAME]);
				m_EditDetActive.SetWindowText(	theApp.FullDivision[i][DIV_DET_ACTIVE]);
				m_EditDetPath.SetWindowText(	theApp.FullDivision[i][DIV_DET_PATH]);
				m_EditDetPostFix.SetWindowText(	theApp.FullDivision[i][DIV_DET_PTFIX]);
				m_EditDetDist.SetWindowText(	theApp.FullDivision[i][DIV_DET_DIST]);
				m_EditDetDPress.SetWindowText(	theApp.FullDivision[i][DIV_DET_DPRESS]);
				m_EditDetDTime.SetWindowText(	theApp.FullDivision[i][DIV_DET_DTIIME]);
				//}
				break;
			}
		}

		// В случае с кнопкой "Просмотр" заблокируем все элементы, которые имеет смысл заблокировать
		// Блокируем только: 1. Выпадающий список 2. Дельта Давление 3. Дельта время // Всё остальное итак заблокировано по умолчанию
		m_EditDetGrafName.EnableWindow(FALSE);
		m_CmBxDetNum.EnableWindow(FALSE);
		m_EditDetDPress.EnableWindow(FALSE);
		m_EditDetDTime.EnableWindow(FALSE);
		m_BtnDetSave.EnableWindow(FALSE);
		break;
	}

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}


void CDetectorsEdit::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	//CDialog::OnOK();
}

// кнопка "Сохранить" в Настройке Датчика
// кнопка "Сохранить Датчик" ДОСТУПНА, когда: 1) введены все параметры 2) Последние два параметра больше нуля
void CDetectorsEdit::OnBnClickedDetSaveBtn()
{
	// TODO: добавьте свой код обработчика уведомлений
	int curIndex( m_CmBxDetNum.GetCurSel() );
	if( curIndex == (-1) )  return;

	// 0.1 // Сначала проверяем параметр Дельта Давление
	CString EditDetDPress("");
	m_EditDetDPress.GetWindowText(EditDetDPress);

	double dDetDPress = _tstof(EditDetDPress);
	if(  ( ((dDetDPress <= 0.00) || (dDetDPress > 1)) )  && curIndex!=(-1) )
	{
		AfxMessageBox( _T("ВНИМАНИЕ: Параметр \"Дельта Давление\" должен быть задан больше 0 и не больше 1"), MB_ICONWARNING );
		int StartCh(0), EndCh(0);
		m_EditDetDPress.GetSel(StartCh, EndCh);
		m_EditDetDPress.SetSel(StartCh, EndCh, 0);
		m_EditDetDPress.SetFocus();

		return;
	}
	else
	{EditDetDPress = DoubleToCStr(dDetDPress,5);}

	// 0.2 // Далее проверяем параметр Время Обнаружения
	CString EditDetDTime("");
	m_EditDetDTime.GetWindowText(EditDetDTime);

	double dDetDTime = _tstof(EditDetDTime);
	if(  ( ((dDetDTime <= 0) || (dDetDTime > 10)) )  && curIndex!=(-1) )
	{
		AfxMessageBox( _T("ВНИМАНИЕ: Параметр \"Дельта Время\" должен быть задан больше 0 и не больше 10"), MB_ICONWARNING );
		int StartCh(0), EndCh(0);
		m_EditDetDTime.GetSel(StartCh, EndCh);
		m_EditDetDTime.SetSel(StartCh, EndCh, 0);
		m_EditDetDTime.SetFocus();

		return;
	}
	else
	{EditDetDTime = DoubleToCStr(dDetDTime,0);}



	// 1 // Сначала сохраняем причём сохраняем только в вектор строковых векторов  theApp.FullDivision
	CString EmptyStr("");
	CString DetectorParametr("");

	std::vector<CString> NewDetector;
	std::vector<CString> ReservVsector;
	NewDetector.clear();

	m_EditDetGrafName.GetWindowText(DetectorParametr);	NewDetector.push_back(DetectorParametr);	// имя
	//long curIndex = m_CmBxDetNum.GetCurSel();
	
	//CString DetectorSysName("");
	//m_CmBxDetNum.GetLBText( curIndex, DetectorSysName );
	//NewDetector.push_back(DetectorSysName);

	m_EditDetNum.GetWindowText(DetectorParametr);		NewDetector.push_back(DetectorParametr);	// нр
	m_EditDetActive.GetWindowText(DetectorParametr);	NewDetector.push_back(DetectorParametr);	// активен
	m_EditDetPath.GetWindowText(DetectorParametr);		NewDetector.push_back(DetectorParametr);	// путь
	m_EditDetPostFix.GetWindowText(DetectorParametr);	NewDetector.push_back(DetectorParametr);	// постфикс
	m_EditDetDist.GetWindowText(DetectorParametr);		NewDetector.push_back(DetectorParametr);	// удаление
	//m_EditDetDPress.GetWindowText(DetectorParametr);
	NewDetector.push_back(EditDetDPress);															// дельта_давление
	//m_EditDetDTime.GetWindowText(DetectorParametr);
	NewDetector.push_back(EditDetDTime);															// дельта_время
//	NewDetector.push_back(_T(""));																	// удалениеот_начала
//	NewDetector.push_back(_T(""));																	// удалениеот_конца


	// Если сохранение происходит по причине входа в окно по нажатию на "Добавить Датчик"
	// То датчик достаточно добавить в конец и потом произветсти сортировку
	if(theApp.EditDivDetBtnClicked == theApp.DET_BTN_ADD)
	{
		std::vector<std::vector<CString>> NewFullDivision = theApp.FullDivision;
		// Добавили новый Датчик в конец временной копии вектора с инфой об Участке и Датчиках на Участке
		NewFullDivision.push_back(NewDetector);

		if(NewFullDivision.size()>2) // запись о участке + более одного датчика
		{
			std::vector<long> AllDetectorsNums;
			std::vector<CString> AllDetectorsSysNames;
			for(long i=1, j=0; i<NewFullDivision.size(); i++)
			{
				for(j=0; j<theApp.AllDetectors.size();j++)
				{
					if(theApp.AllDetectors[j][DET_NUMBER] == NewFullDivision[i][DIV_DET_NUMBER]) // IMPORTANT
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
			theApp.FullDivision.insert( theApp.FullDivision.begin(), NewFullDivision[0] );
			for(long i=0; i<AllDetectorsNums.size(); i++)
			{
				for(long j=1; j<NewFullDivision.size(); j++)
				{
					//if( AllDetectorsSysNames[i] == NewFullDivision[j][DIV_DET_NAME] )	// IMPORTANT
					if( AllDetectorsNums[i] == _tstol(NewFullDivision[j][DIV_DET_NUMBER]) )
					{
						theApp.FullDivision.push_back( NewFullDivision[j] );
						//theApp.FullDivision.insert( theApp.FullDivision.begin()+i+1, NewFullDivision[j] );
					}
				}
			}

		}
		//else
		//{
		//}

		// Осталось произвести сортировку, чтобы добавленный в конец элемент встал на своё место
		/*
		if(theApp.FullDivision.size()>1)
		{	
			long i=1;
			for(i=1; i<(theApp.FullDivision.size()-1); i++)
			{
				//if(  _tstol(theApp.FullDivision[i][0]) > _tstol(NewDetector[0])  )
				if(  (theApp.FullDivision[i][0]) == _tstol(NewDetector[0])  )
				{
					theApp.FullDivision.insert( theApp.FullDivision.begin()+i+1, NewDetector);
					break;
				}

				//if(  (  _tstol(theApp.FullDivision[i][0]) < _tstol(NewDetector[0])  ) && (  _tstol(theApp.FullDivision[i+1][0]) > _tstol(NewDetector[0])  )  )
				if(  (  (theApp.FullDivision[i][0]) < _tstol(NewDetector[0])  ) && (  _tstol(theApp.FullDivision[i+1][0]) > _tstol(NewDetector[0])  )  )
				{
					theApp.FullDivision.insert( theApp.FullDivision.begin()+i, NewDetector);
					break;
				}
			}

			if(i==(theApp.FullDivision.size()-1))
			{theApp.FullDivision.push_back(NewDetector);}
		}
		*/
		//theApp.FullDivision.insert( theApp.FullDivision.begin()+i, 1 ); // НЕ ЗАБЫТЬ ПЕРЕПИСАТЬ С  ИТЕРАТОРАМИ  И ПОСМОТРЕТЬ ЛИШНИЙ РАЗ ПРО ИТЕРАТОРЫ

		if(theApp.FullDivision.size()==2)
		{
			//if(  _tstol(theApp.FullDivision[1][0]) < _tstol(NewDetector[0])  )
			//{
				theApp.FullDivision.push_back(NewDetector);
			//}
			//else
			//{
			//	ReservVsector = theApp.FullDivision[1];
			//	theApp.FullDivision.clear();
			//	theApp.FullDivision.push_back(NewDetector);
			//	theApp.FullDivision.push_back(ReservVsector);
			//}
		}

		if(theApp.FullDivision.size()==1)
		{theApp.FullDivision.push_back(NewDetector);}
	}

	// Если мы сохраняем по кнопке "Изменить", то необходимо не приписать, а переписать существующий элемент вектора
	if(theApp.EditDivDetBtnClicked == theApp.DET_BTN_CHANGE)	
	{
		for(long i=1; i<theApp.FullDivision.size(); i++)
		{
			// Нашли среди Датчиков, тот в ктором произошло изменение
			//if( theApp.FullDivision[i][0] == NewDetector[0] )
			if( theApp.FullDivision[i][DIV_DET_NUMBER] == NewDetector[DIV_DET_NUMBER] )
			{// Перезаписали найденный Датчик
				theApp.FullDivision[i] = NewDetector;
			}
		}
	}
//	if(theApp.EditDivDetBtnClicked == theApp.DET_BTN_LOOK)
//	{
//	}

	// 2 // Потом посылаем сообщение для разблокировки кнопок в родительском окне
	GetParent()->PostMessage(WM_DETECTOR_EDIT_SAVE,0,0);

	CDialog::OnOK();
}


// кнопка "Выход" в Настройке Датчика
void CDetectorsEdit::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений

	// НЕЗАБЫТЬ ДОПИСАТЬ !!!!!
	// По кнопке Выход можно зделсть "Сохранить изменения" => "Да"/"Нет", если таковые были сделаны

	GetParent()->PostMessage(WM_DETECTOR_EDIT_EXIT,0,0);

	CDialog::OnCancel();
}


void CDetectorsEdit::OnCbnSelchangeDetNameCmbx()
{
	//m_EditDetGrafName.SetWindowText(EmptyStr);				 // имя				// НЕ МЕНЯЕТСЯ ПОЛЬЗОВАТЕЛЕМ
	//m_EditDetActive.SetWindowText(_T("1"));					 // активен			// НЕ МЕНЯЕТСЯ ПОЛЬЗОВАТЕЛЕМ = "1" ВСЕГДА
	//m_EditDetPath.SetWindowText(EmptyStr);					 // путь			// НЕ МЕНЯЕТСЯ ПОЛЬЗОВАТЕЛЕМ
	//m_EditDetPostFix.SetWindowText(EmptyStr);					 // постфикс		// НЕ МЕНЯЕТСЯ ПОЛЬЗОВАТЕЛЕМ
	//m_EditDetDist.SetWindowText(EmptyStr);		//км		 // удаление		// НЕ МЕНЯЕТСЯ ПОЛЬЗОВАТЕЛЕМ
	//m_EditDetDPress.SetWindowText(_T("0.010"));	//кгс/(см^2) // дельта_давление	// РЕДАКТИРУЕМЫЙ			 = [По умолчанию = 0.010]
	//m_EditDetDTime.SetWindowText(_T("0.5"));		//сек		 //	дельта_время	// РЕДАКТИРУЕМЫЙ			 = [По умолчанию = 0.5 ] 


	// TODO: добавьте свой код обработчика уведомлений
	CString EmptyStr("");

	// НЕЗАБЫТЬ ДОПИСАТЬ !!!!!
	// По нажатию на номер датчика заполним его параметры, которые возьмём из нашего XML-файла со всеми датчиками
	int curIndex=0;			// Индекс элемента выбранного в Combobx
	curIndex = m_CmBxDetNum.GetCurSel();
	if( curIndex == (-1) )  return;

	//CString DetectorNumber("");
	//m_CmBxDetNum.GetLBText( curIndex, DetectorNumber );

	CString CurNumPlusName(""); 
	m_CmBxDetNum.GetLBText( curIndex, CurNumPlusName );

	//CString DetectorSysName("");
	//m_CmBxDetNum.GetLBText( curIndex, DetectorSysName );


	if(curIndex != -1)
	{
		// Извлекаем из XML-файла информацию по номеру датчика
		// Предварительно мы должны проверить не из-за нажатия ли в предыдущем окне кнопок "Просмотр" или "Изменить" вызвался Комбобокс
		// Ибо если это так, то все параметры для датчика итак уже занеслись в соответсвующие места из вектора theApp.FullDivision[1...n][]

		// Нас же интересует случай, после того как мы уже зашли в Добавление (Просмотр заблокирован) и по нажатию на комбобокс меняем номер датчика
		// А так как выбираем мы уже из всех доступных, а не только из доступных на данном участке, то мы вынуждены обращзаться к XML-файлу 
		// + по мере изменения парамтров для датчиков нам небходимо перезаписывать эти значения в вектор theApp.FullDivision

		// В зависимости от нажатой в предыдущем окне кнопки активируем соовтесвующие в текущем
		// "Добавить" - берём инфу о датчике из XML и по умолчанию берём ставим дефолтные дельты.

		switch(theApp.EditDivDetBtnClicked)
		{
		case theApp.DET_BTN_ADD: // нажата кнопка "Добавить"

			for(long i=0; i<theApp.AllDetectors.size(); i++)
			{
				//if(theApp.AllDetectors[i][DET_NUMBER] == DetectorNumber)
				//if(theApp.AllDetectors[i][DET_NUMBER] == DetectorSysName)
				CString NumPlusName = 
					theApp.AllDetectors[i][DET_NUMBER]
					+ _T(" - ")
					+ theApp.AllDetectors[i][DET_NAME];

				if(NumPlusName == CurNumPlusName)
				{
					//for(long j=0; j<theApp.AllDetectors[i].size(); j++)
					//{

						m_EditDetNum.SetWindowText(		theApp.AllDetectors[i][DET_NUMBER]);
						//if(theApp.AllDetectors[i][1] == EmptyStr)
						//{m_EditDetGrafName.SetWindowText(theApp.AllDetectors[i][1]);}
						//else
						{m_EditDetGrafName.SetWindowText(theApp.AllDetectors[i][DET_NAME]);}	 // имя				// НЕ МЕНЯЕТСЯ ПОЛЬЗОВАТЕЛЕМ

						m_EditDetActive.SetWindowText(_T("1"));									 // активен			// НЕ МЕНЯЕТСЯ ПОЛЬЗОВАТЕЛЕМ = "1" ВСЕГДА
						m_EditDetPath.SetWindowText(theApp.AllDetectors[i][DET_FILE_PATH]);		 // путь			// НЕ МЕНЯЕТСЯ ПОЛЬЗОВАТЕЛЕМ
						m_EditDetPostFix.SetWindowText(theApp.AllDetectors[i][DET_POSTFIX]);	 // постфикс		// НЕ МЕНЯЕТСЯ ПОЛЬЗОВАТЕЛЕМ
						m_EditDetDist.SetWindowText(theApp.AllDetectors[i][DET_DISTANCE]);		 // удаление		// НЕ МЕНЯЕТСЯ ПОЛЬЗОВАТЕЛЕМ
						//m_EditDetDPress.SetWindowText(theApp.AllDetectors[i][DET_PROD_TYPE]);	 // дельта_давление	// РЕДАКТИРУЕМЫЙ			 = [По умолчанию = 0.010]
						//if(theApp.AllDetectors[i][DET_PROD_TYPE] == EmptyStr)
						{m_EditDetDPress.SetWindowText(_T("0.010"));}
						//m_EditDetDTime.SetWindowText(theApp.AllDetectors[i][DET_PROD_ID]);	 //	дельта_время	// РЕДАКТИРУЕМЫЙ			 = [По умолчанию = 0.5 ] 
						//if(theApp.AllDetectors[i][DET_PROD_ID] == EmptyStr)
						{m_EditDetDTime.SetWindowText(_T("0.5"));}
					//}
					break;
				}
			}

			//m_EditDetGrafName.EnableWindow(TRUE);
			m_EditDetDPress.EnableWindow(TRUE);				//кгс/(см^2) // дельта_давление	// РЕДАКТИРУЕМЫЙ			 = [По умолчанию = 0.010]
			m_EditDetDTime.EnableWindow(TRUE);				//сек		 //	дельта_время	// РЕДАКТИРУЕМЫЙ			 = [По умолчанию = 0.5 ] 

			m_BtnDetSave.EnableWindow(TRUE);
			break;
		case theApp.DET_BTN_CHANGE: //нажата кнопка "Изменить"
			//m_EditDetGrafName.EnableWindow(TRUE);
			m_EditDetDPress.EnableWindow(TRUE);				//кгс/(см^2) // дельта_давление	// РЕДАКТИРУЕМЫЙ			 = [По умолчанию = 0.010]
			m_EditDetDTime.EnableWindow(TRUE);				//сек		 //	дельта_время	// РЕДАКТИРУЕМЫЙ			 = [По умолчанию = 0.5 ] 

			m_BtnDetSave.EnableWindow(TRUE);
			break;
		case theApp.DET_BTN_LOOK: // нажата кнопка "Просмотр"
			break;
		}
	}

}


// Изменяем Название Датчика на Графике
void CDetectorsEdit::OnEnChangeDetGrafNameEdit()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}


// Изменяем Дельта Давление
void CDetectorsEdit::OnEnChangeDetDpressEdit()
{
/*
	bool NoNeedToChange=true;
	CString EditDetDPress("");
	m_EditDetDPress.GetWindowText(EditDetDPress);
	NoNeedToChange = CheckString(EditDetDPress);

	int curIndex = m_CmBxDetNum.GetCurSel();
	double dDetDPress = _tstof(EditDetDPress);
	if(  ( ((dDetDPress < 0) || (dDetDPress > 1)) )  && curIndex!=(-1) )
	{
		AfxMessageBox( _T("ВНИМАНИЕ: Параметр \"Дельта Давление\" должен быть задан больше 0 и не больше 1"), MB_ICONWARNING );
		//if(dDetDPress <= 0)
		//{m_EditDetDPress.SetWindowText(_T("0.01"));}
		//if(dDetDPress > 1)
		//{m_EditDetDPress.SetWindowText(_T("1"));}
	}


	int StartCh=0, EndCh=0;
	m_EditDetDPress.GetSel(StartCh, EndCh);
	if(PressEdit && !NoNeedToChange)
	{
		PressEdit=false;
		//m_EditDetDPress.Undo();
		m_EditDetDPress.SetWindowText(EditDetDPress);
	}

	if(!NoNeedToChange)
	{m_EditDetDPress.SetSel(StartCh-1, EndCh-1, 0);}

	PressEdit=true;
*/
}

void CDetectorsEdit::OnEnSetfocusDetDpressEdit()
{	// TODO: добавьте свой код обработчика уведомлений
//	CString EditDetDPress("");
//	m_EditDetDPress.GetWindowText(EditDetDPress);
//	CheckString(EditDetDPress);
//	m_EditDetDPress.SetWindowText(EditDetDPress);
}
void CDetectorsEdit::OnEnKillfocusDetDpressEdit()
{	// TODO: добавьте свой код обработчика уведомлений
//	CString EditDetDPress("");
//	m_EditDetDPress.GetWindowText(EditDetDPress);
//	CheckString(EditDetDPress);
//	m_EditDetDPress.SetWindowText(EditDetDPress);
}


// Изменяем Дельта Время
void CDetectorsEdit::OnEnChangeDetDtimeEdit()
{
/*
	bool NoNeedToChange=true;
	CString EditDetDTime("");
	m_EditDetDTime.GetWindowText(EditDetDTime);
	NoNeedToChange = CheckString(EditDetDTime);

	int curIndex = m_CmBxDetNum.GetCurSel();
	double dDetDTime = _tstof(EditDetDTime);
	if(  ( ((dDetDTime <= 0) || (dDetDTime > 10)) )  && curIndex!=(-1) )
	{
		AfxMessageBox( _T("ВНИМАНИЕ: Параметр \"Дельта Время\" должен быть задан больше 0 и не больше 10"), MB_ICONWARNING );
		//if(dDetDTime <= 0)
		//{m_EditDetDTime.SetWindowText(_T("0.01"));}
		//if(dDetDTime > 10)
		//{m_EditDetDTime.SetWindowText(_T("10"));}
	}


	int StartCh=0, EndCh=0;
	m_EditDetDTime.GetSel(StartCh, EndCh);
	if(TimeEdit && !NoNeedToChange)
	{
		TimeEdit=false;
		//m_EditDetDPress.Undo();
		m_EditDetDTime.SetWindowText(EditDetDTime);
	}

	if(!NoNeedToChange)
	{m_EditDetDTime.SetSel(StartCh-1, EndCh-1, 0);}

	TimeEdit=true;
*/
}


void CDetectorsEdit::OnEnSetfocusDetDtimeEdit()
{	// TODO: добавьте свой код обработчика уведомлений
//	CString EditDetDTime("");
//	m_EditDetDTime.GetWindowText(EditDetDTime);
//	CheckString(EditDetDTime);
//	m_EditDetDTime.SetWindowText(EditDetDTime);
}
void CDetectorsEdit::OnEnKillfocusDetDtimeEdit()
{	// TODO: добавьте свой код обработчика уведомлений
//	CString EditDetDTime("");
//	m_EditDetDTime.GetWindowText(EditDetDTime);
//	CheckString(EditDetDTime);
//	m_EditDetDTime.SetWindowText(EditDetDTime);
}
 
// Нажатие на Датчик в списке Датчиков при нажатой кнопке "Просмотр"
LRESULT CDetectorsEdit::OnDivDetectorChange( WPARAM wparam , LPARAM lparam )
{
	//CString sChoosenDetectorNum("");
	//sChoosenDetectorNum = LintToCStr(lparam);

	CString tmpChoosenDetNumPlusName = LPCTSTR(wparam);
	//CString tmpChoosenDetSysName = LPCTSTR(wparam);


	CString EmptyStr("");

	// Есть неизменяющиеся параметры:
	// Для Датчика это "Активен", всегда и по умолчанию равен = "1"
	long NumOfDet=0, NumOfDetParams=0;
	bool DetNumFound=false;		// если "тру", то мы нашли номер выбранного датчика среди отсеянных из XML-файла по продукту
	bool DetectorFound=false;	// если "тру", то мы нашли датчик в .sou файле

	//m_CmBxDetNum.EnableWindow(TRUE);
	//case theApp.DET_BTN_LOOK: // нажата кнопка "Просмотр"

		// Заполним все значения для Датчика:
		// 1 // Заполним Выпадающий список номерами и именами всех датчиков, из вектора theApp.DivDetectors
		m_CmBxDetNum.Clear();
		m_CmBxDetNum.ResetContent();
		long check=0;
		for(long i=0; i<theApp.DivDetectors.size(); i++)
		{
			CString NumPlusName = 
				theApp.DivDetectors[i][DIV_DET_NUMBER]
				+ _T(" - ")
				+ theApp.DivDetectors[i][DIV_DET_NAME];

			m_CmBxDetNum.AddString(NumPlusName);

			//m_CmBxDetNum.AddString(theApp.DivDetectors[i][DIV_DET_NUMBER]);
			check++;
		}
		// 2 // В выпадающем же Списке выставим выбранным тот Датчик на который нажали в предыдущем окне
		for(long k=0; k<theApp.DivDetectors.size(); k++)
		{
			//CString LBNumber;
			//m_CmBxDetNum.GetLBText(k,LBNumber);
			CString LBSysName;
			m_CmBxDetNum.GetLBText(k,LBSysName);

			//if( LBNumber == sChoosenDetectorNum)
			if( LBSysName == tmpChoosenDetNumPlusName)
			{
				m_CmBxDetNum.SetCurSel(k); DetNumFound=true;
				break;
			}
		}
		// 3 // Наконец по выставленному датчику и его номеру найдём его в векторе theApp.FullDivision и заполним все его параметры:
		NumOfDet=0;
		NumOfDetParams=0;
		if(theApp.FullDivision.size()>1)
		{
			NumOfDet = theApp.FullDivision.size() - 1;		// NumOfDet = Число датчиков (исключая первую запись с параметрами Участка) 
			NumOfDetParams = theApp.FullDivision[1].size();	// NumOfDetParams = Число параметров датчиков
		}
		
		for(long i=1; i < (NumOfDet+1); i++)
		{
			//if( (theApp.FullDivision[i][0] == sChoosenDetectorNum) )//&& (theApp.FullDivision[i][1] == theApp.CurDetName) ) // в 1-ой колонке номер Датчика // во 2-ой колнке Название Датчика
		
			CString NumPlusName = 
				theApp.FullDivision[i][DIV_DET_NUMBER]
				+ _T(" - ")
				+ theApp.FullDivision[i][DIV_DET_NAME];

			//if( (theApp.FullDivision[i][DIV_DET_NUMBER] == tmpChoosenDetSysName) )//&& (theApp.FullDivision[i][1] == theApp.CurDetName) ) // в 1-ой колонке номер Датчика // во 2-ой колнке Название Датчика
			if( (NumPlusName == tmpChoosenDetNumPlusName) )//&& (theApp.FullDivision[i][1] == theApp.CurDetName) ) // в 1-ой колонке номер Датчика // во 2-ой колнке Название Датчика
			{
				DetectorFound=true;
				//for(long j=0; j < NumOfDetParams; j++)
				//{
				int curIndex=0;			// Индекс элемента выбранного в Combobx
				curIndex = m_CmBxDetNum.GetCurSel();
				//if( curIndex == (-1) )  return;

				if( (curIndex == -1) && (!DetNumFound) )
				{
					CString NumPlusName =
						theApp.FullDivision[i][DIV_DET_NUMBER]
						+ _T(" - ")
						+ theApp.FullDivision[i][DIV_DET_NAME];
					m_CmBxDetNum.AddString(NumPlusName);
					//m_CmBxDetNum.AddString(theApp.FullDivision[i][DIV_DET_NUMBER]);
					//m_CmBxDetNum.AddString(sChoosenDetectorNum);
					m_CmBxDetNum.SetCurSel(m_CmBxDetNum.GetCount()-1);
				}

				m_EditDetNum.SetWindowText(		theApp.FullDivision[i][DIV_DET_NUMBER]);
				m_EditDetGrafName.SetWindowText(theApp.FullDivision[i][DIV_DET_NAME]);
				m_EditDetActive.SetWindowText(	theApp.FullDivision[i][DIV_DET_ACTIVE]);
				m_EditDetPath.SetWindowText(	theApp.FullDivision[i][DIV_DET_PATH]);
				m_EditDetPostFix.SetWindowText(	theApp.FullDivision[i][DIV_DET_PTFIX]);
				m_EditDetDist.SetWindowText(	theApp.FullDivision[i][DIV_DET_DIST]);
				m_EditDetDPress.SetWindowText(	theApp.FullDivision[i][DIV_DET_DPRESS]);
				m_EditDetDTime.SetWindowText(	theApp.FullDivision[i][DIV_DET_DTIIME]);
				//}
				break;
			}
		}

		// В случае с кнопкой "Просмотр" заблокируем все элементы, которые имеет смысл заблокировать
		// Блокируем только: 1. Выпадающий список 2. Дельта Давление 3. Дельта время // Всё остальное итак заблокировано по умолчанию

	//	m_CmBxDetNumberm_CmBxDetNum.EnableWindow(TRUE);
		m_CmBxDetNum.EnableWindow(FALSE);
		m_EditDetDPress.EnableWindow(FALSE);
		m_EditDetDTime.EnableWindow(FALSE);
		m_BtnDetSave.EnableWindow(FALSE);
	//	break;
	//}

	return 0;
}



// Прочие методы для Конвертирования
CString CDetectorsEdit::LintToCStr(long int x)
{
	CString strX;
	strX.Format( _T("%i"), x ); //%i for int // %d for ?? // %l for long
	return strX;
}


CString CDetectorsEdit::DoubleToCStr(double x, int count) // x - число, count - число знаков после запятой
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


BOOL CDetectorsEdit::PreTranslateMessage(LPMSG pMsg)
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


bool CDetectorsEdit::CheckString(CString& StrToCheck)
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

