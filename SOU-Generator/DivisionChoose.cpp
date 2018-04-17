// DivisionChoose.cpp: файл реализации
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

// диалоговое окно CDivisionChoose

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


// обработчики сообщений CDivisionChoose

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

	CString DivisionFileName(""); // Имя Файла следующего Участка ()
	CString wStr(""); // Имя следующего Участка
	//CString wStr_DivName(""); // Имя следующего Участка
	//CString wStr_Product(""); // Продукт на данном участке
	CString EmptyStr("");
	theApp.AllDivisionsFileNames.clear();

	//for(int i = 0; i < 5; i++)
	//{
	//	cs.Format(_T("Участок № %d"), i+1);
	//	m_DivChangeList.InsertItem(i, cs);
	//}


	CRect rect;
	m_DivChangeList.GetClientRect(rect);
	m_DivChangeList.RedrawItems(0,0);

	bool badXml=false;		// Указывает на то, что была найдена хотябы один некорректный Участок 
	bool changeXml=false;	// Нужно для проверки поменялось ли что-то в каждом отдельно взятом участке (обнуляется)
	int  ichangeXml=0;		// Если больше чем 0, то изменения произошли хотяб в одном участке

	std::vector<CString> OneDivision;
	// Заполняем список Названиями Участков используя названия файлов .sou из папки "Участки"
	if(theApp.CurDivisionsPath != EmptyStr)
	{
		CString sPath = theApp.CurDivisionsPath;
		CFileFind hFile;
		bool bFound = false;
		bFound = hFile.FindFile( sPath + _T("\\*.sou") );

		(void)m_DivChangeList.SetExtendedStyle( LVS_EX_FULLROWSELECT );
		m_DivChangeList.SetHeadings( _T("Трубопровод,		110;\
										Продукт,			80;\
										Названия Участков,	300"
									   ) );
		m_DivChangeList.LoadColumnInfo();

		//m_DivChangeList.InsertColumn(0, _T("Трубопровод"), LVCFMT_LEFT, 90);
		//m_DivChangeList.InsertColumn(1, _T("Продукт"), LVCFMT_LEFT, 90);
		//m_DivChangeList.InsertColumn(2, _T("Названия Участков"), LVCFMT_LEFT, 400); //rect.Width() );
		
		long LBiter=0;
		while ( bFound )
		{
			bFound = hFile.FindNextFile();
			//if( (! hFile.IsDots()) && ( hFile.IsDirectory() ) )		
			if( ! hFile.IsDots() )
			{
				DivisionFileName = hFile.GetFileName();

				CString szExt = _tcsrchr(DivisionFileName, '.'); // получаем szExt = ".sou"
				if(szExt == _T(".sou"))
				{
					// Удаляем последние 4 символа из конца каждого файла
					DivisionFileName.Delete(DivisionFileName.GetLength() - szExt.GetLength(), 4);
					// Добавляем только в том случае, если встретился .sou файл
					//m_DivChangeList.InsertItem(LBiter, DivisionFileName);

/////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// Запросим из всех .SOU файлов значение Тэга "продукт"
					CString IniFileName = theApp.IniFileName;
					CString CurDivisionsPath = theApp.CurDivisionsPath;

					// НЕОБХОДИМО ДОПИСАТЬ ПРОВЕРКУ НАЛИЧЕСТВОВАНИЯ ФАЙЛОВ С РАСШИРЕНИЕМ .sou ПО ДАННОМУ ПУТИ !!!!!
					// http://www.rsdn.ru/article/qna/baseserv/fileexist.xml

					CString DivPathWithFiles("");
					CString DivPath("");
	
					DivPath = theApp.CurDivisionsPath;
					DivPathWithFiles = DivPathWithFiles + DivPath + _T("\\*.sou");

					//const wchar_t* _DivPathWithFiles = new wchar_t [_MAX_PATH];  // НЕЗАБЫТЬ delete[] в КОНЦЕ !!!
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


					// СРАЗУ прописываем название файла
					OneDivision.push_back(DivisionFileName);		// [0] - Название файла

					//theApp.ErrDivisions.push_back(OneDivision);
					theApp.AllDivisions.push_back(OneDivision);

					// 2 Запросить все парметры из .SOU файла Участка, если таковой существует и найден, и сохранить его 
					//	 параметры в соответсвующем векторе, в свойства theApp, для Изменения/Добавления/Просмотра этого Участка
					//	 только обновляя вектор и файл во время добавления или удаления соответствующих Датчиков или изменения 
					//	 остальных параметров Участка и при пересохраненинии этого файла 
	
					//CString FileName("Рязань Дизель.sou"); 
					CString DivisionFilePath("");
					DivisionFilePath =  CurDivisionsPath + _T("\\") + DivisionFileName + _T(".sou");
					//MessageBox(	DivisionFilePath, _T("PATH"), 0 );
					////CStringA p_FilePath(DivisionFilePath);

//*
					_bstr_t DivisionFilePathBstr = DivisionFilePath;
					_bstr_t bstrOutput("");
					bool validXml=false;
					//bool changeXml=false; // ничего не поменялось
					HRESULT hr = CoInitialize(NULL);
					if(SUCCEEDED(hr))
					{
						try{
							changeXml=false;
						// 1 Проверка // SOU-файла Участка. Внутрення структура, вложенность всех узлов, наличие всех тэгов/атрибутов
							bstrOutput = theApp.validateDivFile(DivisionFilePathBstr, validXml);
							//CString cstrOutput = (LPCTSTR)bstrOutput;
						// 2.1 Проверка // SOU-файла Участка. Проверка реквизитов. Сверка постфикс+проудкт у датчиков
										// SOU-файла Участка. Проверка продукта на Участке и равенство того же продукта у всех датчиков
							if(validXml)
							{
							bstrOutput = validateDivFileByDetKeyAndDetMaxNum(DivisionFilePath, validXml);
							}

							if(validXml)
							{
							// 2.3 Проверка // SOU-файла Участка. Проверка параметров датчиков: Если есть ошибки, исправляем автоматически
								bstrOutput = correctDivFileByDetParams(DivisionFilePath, DivisionFileName, changeXml);
							// Прописать в ЛОГ результаты изменения файлов если таковые были !!!
							// и опустошаем bstrOutput
								if(changeXml) // =true значит изменения в SOU-файл были внесены
								{
									if(ichangeXml==0)
									{ichangeXml++;}
							// 2.4 Занесение в ЛОГ информации об изменённых, но неудалённых файлах. !!!!!
									// Процесс занесения в ЛОГ информации о Некорректных файлах
									CString LogFileName("sougen_logfiles.txt");
									CString DotSOU(".sou");
									CString lLine;

									CStdioFile cfile_object_write;
									BOOL lOk = cfile_object_write.Open(LogFileName, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite);
									cfile_object_write.SeekToEnd();

									CString LogFiles("");
									CString LogPath("");


									GetLocalTime(&theApp.m_CurTime);	//Инициализируем системное время

									LogFiles += _T("*******************************************************************************************************************************\n");
									lLine.Format(_T("|SOU|%02i.%02i.%04i | %02i:%02i:%02i|******************************************************************************************\n"),
										theApp.m_CurTime.wDay, theApp.m_CurTime.wMonth, theApp.m_CurTime.wYear, theApp.m_CurTime.wHour, theApp.m_CurTime.wMinute, theApp.m_CurTime.wSecond);

									LogFiles += lLine;
									LogFiles += LPCTSTR(bstrOutput);

									LogPath = LogPath + theApp.IniFilePath + LogFileName;

									CStringA LogPathA(LogPath);
									CStringA LogFilesA(LogFiles);

									// Далее записываем всё в log-файл
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

					if(validXml) // случай, когда Файл "Валидный" и можно запросить шапку Участка
 					{
						readDivisionHeadFile(DivisionFilePath);
						//theApp.ErrDivisions.erase(  theApp.ErrDivisions.begin() + (theApp.ErrDivisions.size()-1)  );
					}
					else //if(!validXml)
					{
						badXml=true;

						// Не будем прерывать процесс загрузки файлов, если нашлись невалидные
						// Все предкпредительные сообщения запишем в лог. А пользователю в окне выдадим число невалидных файлов и их имена. 
						//MessageBox(bstrOutput, L"Ошибка в файле или его стрктуре", MB_OK);
						//return TRUE;
						//theApp.ErrDivisions.push_back(DivisionFileName)

						OneDivision.push_back( (LPCTSTR)bstrOutput );
						theApp.ErrDivisions.push_back( OneDivision );

						theApp.AllDivisions.erase(  theApp.AllDivisions.begin() + (theApp.AllDivisions.size()-1)  );


						// Перемещение некорректных файлов !

						// Предварительно создаём папку для их хранения, если таковой нет
						int CreationResult = CreateDirectory(theApp.CurDivisionsPath + _T("//Bad"), NULL);
						if(CreationResult!=0)
						{
							if( CreationResult == ERROR_ALREADY_EXISTS )//== GetLastError())
							{
								//AfxMessageBox(_T("Folder allready exists"));
							}
							else
							{// Failed to create directory.
								//AfxMessageBox(_T("Ошибка при создании папки с файлами участков."));
								// !!!!! ЭТУ ОШИБКУ НЕОБХОДИМО ЗАПРОТОКОЛИРОВАТЬ !!!!!
							}
						}

						// Сделаем это предварительно через WinAPI
						// MoveFile и DeleteFile также возвратят FALSE если операция не выполнилась.
						MoveFile(DivisionFilePath, CurDivisionsPath + _T("//Bad") + _T("\\") + DivisionFileName + _T(".sou") );
						DeleteFile(DivisionFilePath);
					}
					CoUninitialize();
//*/
////////////////////////////////////// Завершили запрос
					// Ранее отображалось имя файла участка: 
					//m_DivChangeList.InsertItem(LBiter, DivisionFileName);
					// так как нам нужны только:
					//m_DivChangeList.SetItemText(LBiter, 0, DivisionFileName);
					//m_DivChangeList.SetItemText(LBiter, 1, wStr_Product);



					//////// Теперь отображается название участка:
					//////// m_DivChangeList.InsertItem(LBiter, wStr_DivName);
					//////// так как нам нужны только:
					//////// m_DivChangeList.SetItemText(LBiter, 0, wStr_DivName);
					//////// m_DivChangeList.SetItemText(LBiter, 1, wStr_Product);

					/////////////////////////////////////////////////////////////////////////////
					// 1 // Поменияем и будем уже тут получать все параметры участка полностью
					//theApp.AllDivisionsFileNames.push_back(DivisionFileName);
				}
				//AfxMessageBox(DivisionFileName);
			}
			LBiter++;
			OneDivision.clear();
		}

		//////// m_DivChangeList.SetExtendedStyle( m_DivChangeList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	}


	// 2.5 Вывод сообщения об изменённых, но неудалённых файлах. !!!!!
	//if(changeXml) // =true значит изменения в SOU-файл были внесены
	if(ichangeXml>0) // >0 значит изменения в какой-то из SOU-файлов были внесены
	{
		CString LogPath("");
		CString MesFiles("");

		// Процесс занесения в ЛОГ информации о Некорректных файлах
		CString LogFileName("sougen_logfiles.txt");
		LogPath = LogPath + theApp.IniFilePath + LogFileName;
		CStringA LogPathA(LogPath);

		MesFiles += _T("При проверке файлов участков были найдены и автоматически исправлены ошибки.\n");
		MesFiles += _T("Ошибки связаны с несоответствием параметров в файлах участков значениям в БД.\n");
		MesFiles += _T("Файл с описанием изменений в файлах Участков находится в:\n");
		MesFiles = MesFiles + theApp.IniDivisionsPath + _T("\\") + LogFileName;

		// Выводим так же и сообщение, и так как LOG-файл точно создан, то и открываем его.
		int msgboxID = AfxMessageBox(MesFiles);
		//if(msgboxID == IDOK)
	}


	/////////////////////////////////////////////////////////////////////////////
	// 2 // После получения всех параметров участка, зная эти параметры отсортируем всё в векторе по названию Участков
	
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
	// 3 // И толкьо после сортировки внутри вектора наконец поместим всё в ListBox, чтобы было полное соответсвие элементов в списке и индексов в векторе !

	for(long i=0; i<theApp.AllDivisions.size(); i++)
	{
/*
		m_DivChangeList.InsertItem(i, theApp.AllDivisions[i][DIVALL_PIPE_NAME]);
		// так как нам нужны только:
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
// Особое изменение Стиля, которое было нужно для случая со старым  //CListCtrl m_DivChangeList;
////	m_DivChangeList.SetExtendedStyle( m_DivChangeList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);


	// Выставить первый элемент списка как "Выделенный"
////	if(m_DivChangeList.GetItemCount() > 0)
////	{m_DivChangeList.SetItemState(0, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);}


	// Если в векторе с Невалидными файлами участков и описаниями их ошибок есть записи, 
	// то выводим предупредительное сообщение, и прописываем все эти ошибки в ЛОГ.
	if(theApp.ErrDivisions.size() > 0)
	{
		CString LogErrFiles("");
		CString LogErrPath("");
		CString MesErrFiles("");
		bool bError=false;

		// Процесс занесения в ЛОГ информации о Некорректных файлах
		LogBadFiles( LogErrFiles, LogErrPath, MesErrFiles, bError);

		CStringA LogErrFilesA(LogErrFiles);
		CStringA LogErrPathA(LogErrPath);

		// Выводим так же и сообщение, и так как LOG-файл точно создан, то и открываем его.
		int msgboxID = AfxMessageBox(MesErrFiles);
		//if(msgboxID == IDOK)
		//{}
	}



	if( (ichangeXml>0) || badXml)
	{
		CString LogPath("");
		CString LogPathQuotes("");

		// Процесс занесения в ЛОГ информации о Некорректных файлах
		CString LogFileName("sougen_logfiles.txt");
		LogPath = LogPath + theApp.IniFilePath + LogFileName;
		LogPathQuotes = _T("\"")+ LogPath +_T("\"");
		// Предварительно смотрим есть ли символы пробела в строке, которую должен выполнять start
		// если пробелы есть, то строку нужно переделать следующим образом: start "строка с пробелами" 
		// но при этом если прорбелов в пути нету: start строка_без_пробелов
		bool WithQuotes=false;
		for(long k=0; k < LogPath.GetLength(); k++)
		{
			if(LogPath.Find(_T(" ")) != -1) // нашёлся пробел
			WithQuotes = true;
		}


		CStringA LogPathA(LogPath);
		CStringA LogPathQuotesA(LogPathQuotes);

		// 3) Осталось запустить программу:	
		// Вариант через  "system()"
		if(WithQuotes)
		{
			system("start " + LogPathQuotesA);
		}
		else
		{
			system("start " + LogPathA);
		}

		// ОДНАКО:
		// Надо Проверить привязан ли тип "txt" к варианты открытия по умолчанию какй-либо программой // Может быть, что привязка бывает сбита.
		// Если нет, то вызвать напрямую редактор, который предварительно помещаем в папку приложения на всякий случай.
////////////////
		//system("ВЫЗОВ_РЕДАКТОРА" + "start " + LogErrPathA);
/*
		// 3) Осталось запустить программу:	
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

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
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

		GetLocalTime(&theApp.m_CurTime);	//Инициализируем системное время

		CStdioFile cfile_object_write;
		BOOL lOk = cfile_object_write.Open(LogErrFileName, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite);
		//CFile cfile_object_write( LogFileName, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite);
		cfile_object_write.SeekToEnd();

		LogErrFiles = _T("*******************************************************************************************************************************\n");

		lLine.Format(_T("|SOU|%02i.%02i.%04i | %02i:%02i:%02i|******************************************************************************************\n"),
			theApp.m_CurTime.wDay, theApp.m_CurTime.wMonth, theApp.m_CurTime.wYear, theApp.m_CurTime.wHour, theApp.m_CurTime.wMinute, theApp.m_CurTime.wSecond);
		LogErrFiles += lLine;


		MesErrFiles += _T("При проверке файлов участков были обнаружены ошибки.\n");
		MesErrFiles += _T("Информация из файлов с ошибками не будет отображаться в следующем окне.\n");
		MesErrFiles += _T("Ошибки были найдены в  ") + LintToCStr(NumErrFiles) + _T("  файлах.\n\n");
		MesErrFiles += _T("Ошибки находятся в следующих файлах:\n");
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
		MesErrFiles += _T("Файл с подробным описанием Ошибок находится в:\n");
		MesErrFiles = MesErrFiles + theApp.IniDivisionsPath +_T("\\")+ LogErrFileName;
		MesErrFiles += _T("\n\nВсе файлы с ошибками были перенесены из папки \"Участки\" в папку \"Участки\\Bad\".");

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


		MesErrFiles += _T("При проверке файлов участков были обнаружены ошибки.\n");
		MesErrFiles += _T("Информация из файлов с ошибками не будет отображаться в следующем окне.\n");
		MesErrFiles += _T("Ошибки были найдены в  ") + LintToCStr(NumErrFiles) + _T("  файлах.\n\n");
		MesErrFiles += _T("Ошибки находятся в следующих файлах:\n");
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
		MesErrFiles += _T("Файл с подробным описанием Ошибок находится в:\n");
		MesErrFiles = MesErrFiles + theApp.IniDivisionsPath +_T("\\")+ LogErrFileName;
		MesErrFiles += _T("\n\nВсе файлы с ошибками были перенесены из папки \"Участки\" в папку \"Участки\\Bad\".");

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
	//TElem subroot = eroot.subnode(L"Участок_СОУ");
	wstring DivAtrs;
	std::vector<CString> DivisionHead;

	
	DivAtrs = eroot.attr(L"имя"				 );	theApp.AllDivisions[theApp.AllDivisions.size()-1].push_back(DivAtrs.c_str());	// [0] - Название Участка
	DivAtrs = eroot.attr(L"труба"			 );	theApp.AllDivisions[theApp.AllDivisions.size()-1].push_back(DivAtrs.c_str());	// [1] - Название трубопровода
	DivAtrs = eroot.attr(L"труба_код"		 );	theApp.AllDivisions[theApp.AllDivisions.size()-1].push_back(DivAtrs.c_str());	// [2] - ID трубопровода
	DivAtrs = eroot.attr(L"продукт"			 );	theApp.AllDivisions[theApp.AllDivisions.size()-1].push_back(DivAtrs.c_str());	// [3] - Название Продукта в Интерфейсе
	DivAtrs = eroot.attr(L"продукт_код"		 );	theApp.AllDivisions[theApp.AllDivisions.size()-1].push_back(DivAtrs.c_str());	// [4] - ID Продукта
	DivAtrs = eroot.attr(L"параметр"		 );	theApp.AllDivisions[theApp.AllDivisions.size()-1].push_back(DivAtrs.c_str());	// [5] - Параметр
	DivAtrs = eroot.attr(L"следить"			 );	theApp.AllDivisions[theApp.AllDivisions.size()-1].push_back(DivAtrs.c_str());	// [6] - Следить
	DivAtrs = eroot.attr(L"волна"			 );	theApp.AllDivisions[theApp.AllDivisions.size()-1].push_back(DivAtrs.c_str());	// [7] - Волна
	DivAtrs = eroot.attr(L"время_обнаружения");	theApp.AllDivisions[theApp.AllDivisions.size()-1].push_back(DivAtrs.c_str());	// [8] - Время_обнаружения
	DivAtrs = eroot.attr(L"труба_длина"		 );	theApp.AllDivisions[theApp.AllDivisions.size()-1].push_back(DivAtrs.c_str());	// [9] - Длина трубопровода
	DivAtrs = eroot.attr(L"имя_начала"		 );	theApp.AllDivisions[theApp.AllDivisions.size()-1].push_back(DivAtrs.c_str());	// [10] - Имя начала Участка
	DivAtrs = eroot.attr(L"имя_конца"		 );	theApp.AllDivisions[theApp.AllDivisions.size()-1].push_back(DivAtrs.c_str());	// [11] - Имя Конца Участка
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
		//DivAtrs = e.attr(L"удалениеот_начала");	OneDetector.push_back(DivAtrs.c_str());
		//DivAtrs = e.attr(L"удалениеот_конца");	OneDetector.push_back(DivAtrs.c_str());

		//имя //нр //активен //путь //постфикс //удаление //дельта_давление // дельта_время // удалениеот_начала // удалениеот_конца
		theApp.FullDivision.push_back(OneDetector);
		OneDetector.clear();
	}

	int u=0;
}



// 2.1 Проверка // SOU-файла Участка. Проверка реквизитов. Сверка постфикс+проудкт = нитка трубопровода у датчиков
// Просматриваем все "нитки" у всех датчиков на участке и ищем их среди "ниток" Датчиков, что получили из БД.
// Если на участке имеется такой Датчик, который не нашёлся среди тех, что пришли из БД, то отбраковать файл.
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

	// УЧАСТОК
	CString DivPIPEID("");	// ХРАНИМ ТУТ КОД ТРУБЫ С УЧАСТКА
	CString DivPRODNAME("");	// ХРАНИМ ТУТ ПРОДУКТ С УЧАСТКА
	CString DivPRODID("");	// ХРАНИМ ТУТ КОД ПРОДУКТА С УЧАСТКА
	// ДАТЧИК
	CString DivDetSYSN("");		// ХРАНИМ ТУТ ИМЯ В СИСТЕМЕ КАЖДОГО ДАТЧИКА
	CString DivDetPTFIX("");	// ХРАНИМ ТУТ ПОСТФИКС КАЖДОГО ДАТЧИКА

	TElem eroot(iRootElm);
	wstring DivAtrs;


//	DivAtrs = eroot.attr(L"имя");											// [1] - Название Участка
	DivAtrs = eroot.attr(L"труба_код");		DivPIPEID = DivAtrs.c_str();	// [3] - ID Трубы
	DivAtrs = eroot.attr(L"продукт");		DivPRODNAME = DivAtrs.c_str();	// [4] - Название Продукта
// ДЛЯ КЛЮЧА ПОНАДОБИТСЯ КОД ПРОДУКТА
	DivAtrs = eroot.attr(L"продукт_код");	DivPRODID = DivAtrs.c_str();	// [5] - ID Продукта
//	DivAtrs = eroot.attr(L"параметр");										// [6] - Параметр
//	DivAtrs = eroot.attr(L"следить");										// [7] - Следить
//	DivAtrs = eroot.attr(L"волна");											// [8] - Волна
//	DivAtrs = eroot.attr(L"время_обнаружения");								// [9] - Время_обнаружения

////////////////////////////////////////////////////////////////////////////////////////
	TElem subroot = eroot.subnode(L"Датчик");
// ОБЪЯВЛЯЕМ ПЕРЕМЕННУЮ ДЛЯ КЛЮЧА
	CString DivDetKey("");	// Так называемый "Ключ" = "Нитка трубопровода" = постфикс+продукт
	CString DetDetKey("");	// Так называемый "Ключ" = "Нитка трубопровода" = постфикс+продукт
	// Для случая проверки двух параметров "сцепленных" в один ключ
	bool DetFound=false;	// Указывает на то нашёлся ли датчик или нет.
	// Для случая проверки ключа, но двух его сосотавляющих по отдельности
	bool DetPRODFound=false;	// Указывает на то нашёлся ли датчик с нужным продуктом или нет.
	bool DetPTFIXFound=false;	// Указывает на то нашёлся ли датчик с нужным постфиксом или нет.

	TElem e = eroot.end();


	int eNumTest=1; // Для проверки числа датчиков на Участвке (если более 8-ми, то в папку "Bad")
	// Первая проверка на число Датчиков, установленных в файле Участка
	for(TElem e=eroot.begin(); e!=eroot.end(); e++, eNumTest++)
	{
		if(
			(theApp.MaxDetectors > 0) &&
			(eNumTest > theApp.MaxDetectors)
		  )
		{
			RetErrCString = RetErrCString + _T("Ошибка в фалйе Участка:") +_T("\"") + bstrXMLFile + _T("\"") + _T("\n") +
				_T("Число датчиков установленных в файле Участка больше чем ") + 
				LintToCStr(theApp.MaxDetectors) + 
				_T(" штук") + _T("\n");

			// Не забываем, что это случай, когда файл оказался НЕВАЛИДНЫЙ и его надо поместить в папку "Bad"
			bValid=false;
			return RetErrCString; 
		}
	}


	for(TElem e=eroot.begin(); e!=eroot.end(); e++)
	{
		DivDetKey.Empty();

		DivAtrs = e.attr(L"имя");		DivDetSYSN = DivAtrs.c_str();
//		DivAtrs = e.attr(L"нр");		// ЗАПРАШИВАЕМ ВХОЛОСТУЮ
//		DivAtrs = e.attr(L"активен");	// ЗАПРАШИВАЕМ ВХОЛОСТУЮ
//		DivAtrs = e.attr(L"путь");		// ЗАПРАШИВАЕМ ВХОЛОСТУЮ
		DivAtrs = e.attr(L"постфикс");	DivDetPTFIX = DivAtrs.c_str();

		CString DivDetPTFIXLower = DivDetPTFIX.MakeLower(); // перевели все символы постфикса в нижние регистры
// ПРОЦЕСС ПОСТРОЕНИЯ КЛЮЧА
// ДЛЯ КЛЮЧА ПОНАДОБИТСЯ ПОСТФИКС КАЖДОГО ДАТЧИКА
		//DivDetKey += DivDetPTFIX;
		DivDetKey += DivDetPTFIXLower; // !!! Внимание в ключе используем постфикс со всеми символами в нижнием регистре
// ДЛЯ КЛЮЧА ПОНАДОБИТСЯ ПРОДУКТ НА УЧАСТКЕ
		DivDetKey += DivPRODID;

// КЛЮЧ СФОРМИРОВАН, МОЖНО НАЧАТЬ ИСКАТЬ ЭТУ КОМБНАЦИЮ СРЕДИ ДАТЧИКОВ ЗВАРОШЕННЫХ ИЗ БД.
		// ОТСОРТИРУЕМ Список Датчиков по номерам:
		std::vector<CString> TitleDetector;
		TitleDetector = theApp.AllDetectors[0]; // сохраняем первый элемент с "шапкой", чтобы она не мешалась при сортировке
		theApp.AllDetectors.erase(theApp.AllDetectors.begin()+0); // удалить из вектора первый элемент в котором шапка инфы о датчиках

		DetFound=false;
		//DetPTFIXFound=false;
		//DetPRODFound=false;

		for (int i=0; i < theApp.AllDetectors.size(); i++)
		{
		// Для случая проверки двух параметров "сцепленных" в один ключ
			DetDetKey.Empty();

			CString DetDetPTFIXLower = theApp.AllDetectors[i][DET_POSTFIX];
			DetDetPTFIXLower = DetDetPTFIXLower.MakeLower(); // перевели все символы постфикса в нижние регистры

			DetDetKey += DetDetPTFIXLower;			// постфикс (преобразованный в нижние регистры)
			DetDetKey += theApp.AllDetectors[i][DET_PROD_VIEW]; // продукт ID

			if(DivDetKey == DetDetKey)
			{DetFound=true;}

		// Для случая проверки ключа, но двух его сосотавляющих по отдельности
		//	if( (DivDetPTFIX == theApp.AllDetectors[i][2] && DivPRODID == theApp.AllDetectors[i][6]) ) // постфикс // продукт ID
		//	{DetPTFIXFound=true; DetPRODFound=true;}

			DetDetKey.Empty();

			//if( DetFound || DetPTFIXFound || DetPRODFound)
			if( DetFound )
			{break;}
		}

		theApp.AllDetectors.insert(theApp.AllDetectors.begin(), TitleDetector); // добавляем шапку обратно в начало
		TitleDetector.clear();

		// Для случая проверки двух параметров "сцепленных" в один ключ
		if(!DetFound)
		{
		// В файле участка "путь" установленное на Датчике значение "тэг=значение" не найдено в базе данных. Файл удалён, а копия перенесена в папку Bad
			RetErrCString = RetErrCString + _T("Ошибка в фалйе Участка:") +_T("\"") + bstrXMLFile + _T("\"") + _T("\n") 
				+_T("установленные на Датчике") + _T(" ")+DivDetSYSN+_T(" ") + _T(" значения:") + _T("\n")
				+_T("\"постфикс\"") + _T(" = ") + DivDetPTFIX + _T(" ") + _T("\n")
				+_T("\"продукт\"") + _T(" = ") +  DivPRODNAME  + _T(" ") + _T("\n")
				+_T("не найдены в базе данных."); // Файл перенесён в папку Bad // Это выводится в сообщении ниже
			bValid=false;
			break;
		}

/*		// Для случая проверки ключа, но двух его сосотавляющих по отдельности
		if(!DetPRODFound && !DetPTFIXFound)
		{
		// В файле участка "путь" установленное на Датчике значение "тэг=значение" не найдено в базе данных. Файл удалён, а копия перенесена в папку Bad
			RetErrCString = RetErrCString + _T("Ошибка в фалйе Участка:") +_T("\"") + bstrXMLFile + _T("\"") + _T("\n") 
				+_T("установленные на Датчике") + _T(" ")+DivDetSYSN+_T(" ") + _T(" значения:") + _T("\n")
				+_T("\"постфикс\"") + _T(" = ") + DivDetPTFIX + _T(" ") + _T("\n")
				+_T("\"продукт\"") + _T(" = ") +  DivPRODNAME  + _T(" ")
				+_T("не найдены в базе данных."); // Файл перенесён в папку Bad // Это выводится в сообщении ниже
			bValid=false;
			break;
		}
		if(!DetPRODFound && DetPTFIXFound)
		{
			RetErrCString = RetErrCString + _T("Ошибка в фалйе Участка:") +_T("\"") + bstrXMLFile + _T("\"") + _T("\n") 
				+_T("установленные на Датчике") + _T(" ")+DivDetSYSN+_T(" ") + _T(" значения:") + _T("\n")
				+_T("\"продукт\"") + _T(" = ") +  DivPRODNAME  + _T(" ")
				+_T("не найдены в базе данных."); // Файл перенесён в папку Bad // Это выводится в сообщении ниже
			bValid=false;
			break;
		}
		if(!DetPTFIXFound && DetPRODFound)
		{
			RetErrCString = RetErrCString + _T("Ошибка в фалйе Участка:") +_T("\"") + bstrXMLFile + _T("\"") + _T("\n") 
				+_T("установленные на Датчике") + _T(" ")+DivDetSYSN+_T(" ") + _T(" значения:") + _T("\n")
				+_T("\"постфикс\"") + _T(" = ") + DivDetPTFIX + _T(" ") + _T("\n")
				+_T("не найдены в базе данных."); // Файл перенесён в папку Bad // Это выводится в сообщении ниже
			bValid=false;
			break;
		}
*/

//		DivAtrs = e.attr(L"удаление");			// ЗАПРАШИВАЕМ ВХОЛОСТУЮ
//		DivAtrs = e.attr(L"дельта_давление");	// ЗАПРАШИВАЕМ ВХОЛОСТУЮ
//		DivAtrs = e.attr(L"дельта_время");		// ЗАПРАШИВАЕМ ВХОЛОСТУЮ

		DivDetKey.Empty();
	}


	return RetErrCString;
}


// 2.2 Проверка // SOU-файла Участка. Проверка продукта на Участке и равенство того же продукта у всех датчиков


// 2.3 Проверка // SOU-файла Участка. Проверка параметров датчиков: Если есть ошибки, исправляем автоматически
// Проверить: 1) Путь к файлу (Сетевое имя)  2) Удаление  3) Имя Датчика в системе  
// Проверить: 4) Скорость волны [0.5 ; 1.5] + Маска 1.123 5) Время обнаружения [0 ; 200] + маска 123
// Проверить: 6) Все поля кроме "Удаление"  6.1) !=0  6.2) !=""  6.3) !=NULL  +"Удаление" 6.1) =0  6.2) != ""  6.3) != NULL
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

	CString DivNAME("");		// ХРАНИМ ТУТ ИМЯ УЧАСТКА
	CString DivPIPENAME("");	// ХРАНИМ ТУТ ИМЯ ТРУБОПРОВОДА
	CString DivPIPEID("");		// ХРАНИМ ТУТ ИД ТРУБОПРОВОДА
	CString DivPRODNAME("");	// ХРАНИМ ТУТ ПРОДУКТ С УЧАСТКА
	CString DivPRODID("");		// ХРАНИМ ТУТ ИД ПРОДУКТА С УЧАСТКА
	CString DivPARAM("");		// ХРАНИМ ТУТ ПАРАМЕТР УЧАСТКА
	CString DivWATCH("");		// ХРАНИМ ТУТ СЛЕДИТЬ УЧАСТКА
	CString DivWAVE("");		// ХРАНИМ ТУТ СКОР.ВОЛНЫ УЧАСТКА
	CString DivDETTIME("");		// ХРАНИМ ТУТ ВРЕМЯ.ОБНАР УЧАСТКА
	CString DivPIPELEN("");		// ХРАНИМ ТУТ ДЛИНА ТРУБЫ УЧАСТКА
	CString DivBEGINNAME("");	// ХРАНИМ ТУТ ИМЯ НАЧАЛА УЧАСТКА
	CString DivENDNAME("");		// ХРАНИМ ТУТ ИМЯ КОНЦА УЧАСТКА



	CString DivDetSYSN("");		// ХРАНИМ ТУТ ИМЯ В СИСТЕМЕ КАЖДОГО ДАТЧИКА
	//CString DivDetGRAN("");	// ХРАНИМ ТУТ ИМЯ НА ГРАФИКЕ КАЖДОГО ДАТЧИКА
	CString DivDetNUMBER("");	// ХРАНИМ ТУТ НР КАЖДОГО ДАТЧИКА
	CString DivDetPTFIX("");	// ХРАНИМ ТУТ ПОСТФИКС КАЖДОГО ДАТЧИКА
	CString DivDetACTIVE("");	// ХРАНИМ ТУТ АКТИВЕН КАЖДОГО ДАТЧИКА
	CString DivDetPATH("");		// ХРАНИМ ТУТ ПУТЬ КАЖДОГО ДАТЧИКА
	CString DivDetDIST("");		// ХРАНИМ ТУТ УДАЛЕНИЕ КАЖДОГО ДАТЧИКА
	CString DivDetDPRESS("");	// ХРАНИМ ТУТ ДЛТ.ДАВЛ. КАЖДОГО ДАТЧИКА
	CString DivDetDTIIME("");	// ХРАНИМ ТУТ ДЛТ.ВРЕМЯ КАЖДОГО ДАТЧИКА
	CString DivDetDISTBEGIN("");// ХРАНИМ ТУТ УДАЛЕНИЕ ОТ НАЧАЛА КАЖДОГО ДАТЧИКА
	CString DivDetDISTEND("");	// ХРАНИМ ТУТ УДАЛЕНИЕ ОТ КОНЦА КАЖДОГО ДАТЧИКА


	std::vector<CString> DivisionHead;
	std::vector<std::vector<CString>> OneDivision;
	std::vector<CString> OneDetector;

	TElem eroot(iRootElm);
	wstring DivAtrs;

// Уже на этом этапе подготавливаем строку для соощения об ошибке, если bChanged в конце будет false, то опустошаем эту строку
	RetErrCString = RetErrCString + _T("В фалйе Участка:") +_T("\"") + bstrXMLFile + _T("\"") + _T("\n");
	RetErrCString = RetErrCString + _T("Были найдены и автоматически исправлены ошибки в его параметрах.\n");
	
//	RetErrCString = RetErrCString + _T("Ошибка в фалйе Участка:") +_T("\"") + bstrXMLFile + _T("\"") + _T("\n")
//		+_T("установленные на Датчике") + _T(" ")+DivDetSYSN+_T(" ") + _T(" значения:") + _T("\n")
//		+_T("\"постфикс\"") + _T(" = ") + DivDetPTFIX + _T(" ") + _T("\n")
//		+_T("\"продукт\"") + _T(" = ") +  DivPROD  + _T(" ") + _T("\n")
//		+_T("не найдены в базе данных."); // Файл перенесён в папку Bad // Это выводится в сообщении ниже

// Проверить: Должно быть не пустое + не NULL => ИНАЧЕ => сделать равным Имени Файла
	DivAtrs = eroot.attr(L"имя");					// [1] - Название Участка
	DivNAME = DivAtrs.c_str();
	if(DivNAME.IsEmpty())
	{
		bChanged=true;
		DivNAME = XMLFileName;
		DivisionHead.push_back(DivNAME);
		RetErrCString = RetErrCString + _T("Было ") +_T("\"имя\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
									  + _T("Стало ") +_T("\"имя\"")+ _T(" = ") + DivNAME + _T("\n");
	}
	else
	{DivisionHead.push_back(DivAtrs.c_str());}

// Проверить: Должно быть не пустое + не NULL + равно одному из значений среди имеющися в наборе датчиков => ИНАЧЕ сообщить об ошибке
	DivAtrs = eroot.attr(L"труба");					// [1] - Название Участка
	DivPIPENAME = DivAtrs.c_str();
	DivisionHead.push_back(DivPIPENAME);

// Проверить: Должно быть не пустое + не NULL + равно одному из значений среди имеющися в наборе датчиков => ИНАЧЕ сообщить об ошибке
	DivAtrs = eroot.attr(L"труба_код");					// [1] - Название Участка
	DivPIPEID = DivAtrs.c_str();
	DivisionHead.push_back(DivPIPEID);

/*// ВСТРОИТЬ !!!!! : Считавшаяся строка - равна ли хоть одному значению из имён труб, что имеются среди всех датчиков

	if(DivNAME.IsEmpty())
	{

		DivisionHead.push_back(DivNAME);
		RetErrCString = RetErrCString + _T("Было ") +_T("\"имя\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
									  + _T("Стало ") +_T("\"имя\"")+ _T(" = ") + DivNAME + _T("\n");
	}
	else
	{DivisionHead.push_back(DivAtrs.c_str());}
	*/


	DivAtrs = eroot.attr(L"продукт");				// Продукт ID	//  [2] - Название Продукта
	DivPRODNAME = DivAtrs.c_str();
	DivisionHead.push_back(DivPRODNAME);

	DivAtrs = eroot.attr(L"продукт_код");			// Продукт ID	//  [2] - Название Продукта
	DivPRODID = DivAtrs.c_str();
	DivisionHead.push_back(DivPRODID);

/// ВСТРОИТЬ !!!!! : Считавшаяся строка - равна ли хоть одному значению из имён труб, что имеются среди всех датчиков


	// 5 detprodid
	// И вообще у меня везде и всюду боль пичаль изза 
/*
	if(DivAtrs==_T("Ав.топливо"))					// Продукт в Интерфейсе // [3] - Название Продукта
	DivAtrs = _T("Керосин");
	if(DivAtrs==_T("Диз.топливо"))
	DivAtrs = _T("Дизель");
	DivisionHead.push_back(DivAtrs.c_str());
	// 6 detprodtype
*/

// Проверить: Должно быть не пустое + не NULL + всегда "Давление" => ИНАЧЕ => Значение по умолчанию Давление.
	DivAtrs = eroot.attr(L"параметр");				// [4] - Параметр
	DivPARAM = DivAtrs.c_str();
	if( (!DivPARAM.IsEmpty()) && (DivPARAM==_T("Давление")) ) 
	{DivisionHead.push_back(DivAtrs.c_str());}
	else
	{
		bChanged=true;
		DivPARAM = _T("Давление");
		DivisionHead.push_back(DivPARAM);
		RetErrCString = RetErrCString + _T("Было ") +_T("\"параметр\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
									  + _T("Стало ") +_T("\"параметр\"")+ _T(" = ") + DivPARAM + _T("\n");
	}

// Проверить: Должно быть не пустое + не NULL + Быть либо 1 или 0 => ИНАЧЕ => Значение по умолчанию 1.
	DivAtrs = eroot.attr(L"следить");				// [5] - Следить
	DivWATCH = DivAtrs.c_str();
	if( (!DivWATCH.IsEmpty()) && (  (DivWATCH==_T("0")) || (DivWATCH==_T("1"))  ) )
	{DivisionHead.push_back(DivAtrs.c_str());}
	else
	{
		bChanged=true;
		DivWATCH = _T("1");
		DivisionHead.push_back(DivWATCH);
		RetErrCString = RetErrCString + _T("Было ") +_T("\"следить\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
									  + _T("Стало ") +_T("\"следить\"")+ _T(" = ") + DivWATCH + _T("\n");
	}

// Проверить: Должно быть не пустое + не NULL + Быть в заданных пределах: [0.5 ; 1.5] + Маска 1.123
	DivAtrs = eroot.attr(L"волна");					// [6] - Волна
	DivWAVE = DivAtrs.c_str();

	bool bDivWave=false;
	if( !CheckString(DivWAVE) ) // true - неизменилась
	{bDivWave=true;}

	double dWaveSpeed = _tstof(DivWAVE);
	if( (dWaveSpeed < 0.5) || (dWaveSpeed > 1.5) )
	{
		//AfxMessageBox( _T("ВНИМАНИЕ: Параметр \"Волна\" должен быть задан в следующем диапазоне значений от 0.5 до 1.5 (км/с)."), MB_ICONWARNING );
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
		RetErrCString = RetErrCString + _T("Было ") +_T("\"волна\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
									  + _T("Стало ") +_T("\"волна\"")+ _T(" = ") + DivWAVE + _T("\n");
	}

	// 8 detwavespeed

// Проверить: Должно быть не пустое + не NULL + Быть в заданных пределах: [0 ; 200] + Маска 123
	DivAtrs = eroot.attr(L"время_обнаружения");		// [7] - время_обнаружения
	DivDETTIME = DivAtrs.c_str();

	bool bDivDetTime=false;
	if( !CheckString(DivDETTIME) ) // true - неизменилась
	{bDivDetTime=true;}

	double dTimeDetect = _tstof(DivDETTIME);
	if(  ( dTimeDetect < 0) || (dTimeDetect > 200)  )
	{
		//AfxMessageBox( _T("ВНИМАНИЕ: Параметр \"Время обнаружения\" должен быть задан в следующем диапазоне значений от 0 до 200 (с)."), MB_ICONWARNING );
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
		RetErrCString = RetErrCString + _T("Было ") +_T("\"время_обнаружения\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
									  + _T("Стало ") +_T("\"время_обнаружения\"")+ _T(" = ") + DivDETTIME + _T("\n");
	}


// Проверить: Должно быть не пустое + не NULL 
	DivAtrs = eroot.attr(L"труба_длина");		// [7] - Время_обнаружения
	DivPIPELEN = DivAtrs.c_str();
	DivisionHead.push_back(DivPIPELEN);
/// ВСТРОИТЬ !!!!! : Считавшаяся строка - равна ли хоть одному значению из имён труб, что имеются среди всех датчиков

// Проверить: Должно быть не пустое + не NULL 
	DivAtrs = eroot.attr(L"имя_начала");		// [7] - Время_обнаружения
	DivBEGINNAME = DivAtrs.c_str();
	DivisionHead.push_back(DivBEGINNAME);
/// ВСТРОИТЬ !!!!! : Считавшаяся строка - равна ли хоть одному значению из имён труб, что имеются среди всех датчиков

// Проверить: Должно быть не пустое + не NULL 
	DivAtrs = eroot.attr(L"имя_конца");		// [7] - Время_обнаружения
	DivENDNAME = DivAtrs.c_str();
	DivisionHead.push_back(DivENDNAME);
/// ВСТРОИТЬ !!!!! : Считавшаяся строка - равна ли хоть одному значению из имён труб, что имеются среди всех датчиков


	OneDivision.clear();
	OneDivision.push_back(DivisionHead);
	DivisionHead.clear();


////////////////////////////////////////////////////////////////////////////////////////
	TElem subroot = eroot.subnode(L"Датчик");

// ОБЪЯВЛЯЕМ ПЕРЕМЕННые ДЛЯ КЛЮЧА (ПЕРВЫЙ ДЛЯ КЛЛЮЧА НА УЧАСТКЕ, ВТОРОЙ ДЛЯ ПРОХОДА ПО ВСЕМ ДАТЧИКАМ)
	CString DivDetKey("");	// Так называемый "Ключ" = "Нитка трубопровода" = постфикс+продукт
	CString DetDetKey("");	// Так называемый "Ключ" = "Нитка трубопровода" = постфикс+продукт

	TElem e = eroot.end();
	int elementsnumber=1;
	bool bDetChanged=false; // Индикатор того, что хоть какое-то изменение произошло с рассматриваемым датчиком.
	CString CurDetErrCString("");


	for(TElem e=eroot.begin(); e!=eroot.end(); e++, elementsnumber++)
	{
		bDetChanged=false;
		OneDetector.clear();
		DivDetKey.Empty();

// НЕ ПРОВЕРЯЕМ: Параметр является "КЛЮЧЕВОЙ" / ИДЕНТИФИКАЦИОННОЙ ИНФОРМАЦИЕЙ для Датчика
		DivAtrs = e.attr(L"постфикс");
		DivDetPTFIX = DivAtrs.c_str();

		CString DivDetPTFIXLower = DivDetPTFIX.MakeLower(); // перевели все символы постфикса в нижние регистры
// ПРОЦЕСС ПОСТРОЕНИЯ КЛЮЧА
// ДЛЯ КЛЮЧА ПОНАДОБИТСЯ ПОСТФИКС КАЖДОГО ДАТЧИКА
		//DivDetKey += DivDetPTFIX;
		DivDetKey += DivDetPTFIXLower; // !!! Внимание в ключе используем постфикс со всеми символами в нижнием регистре
// ДЛЯ КЛЮЧА ПОНАДОБИТСЯ ПРОДУКТ НА УЧАСТКЕ
		DivDetKey += DivPRODID;

// КЛЮЧ СФОРМИРОВАН, МОЖНО НАЧАТЬ ИСКАТЬ ЭТУ КОМБНАЦИЮ СРЕДИ ДАТЧИКОВ ЗАПРОШЕННЫХ ИЗ БД.
		// ОТСОРТИРУЕМ Список Датчиков по номерам:
		std::vector<CString> TitleDetector;
		TitleDetector = theApp.AllDetectors[0]; // сохраняем первый элемент с "шапкой", чтобы она не мешалась при сортировке
		theApp.AllDetectors.erase(theApp.AllDetectors.begin()+0); // удалить из вектора первый элемент в котором шапка инфы о датчиках

		int i(0);
		bool DivDetFound(false); // нашёлся ли по "ключу" нужный датчик
		for (i=0; i < theApp.AllDetectors.size(); i++)
		{
			bDetChanged=false;

			// Для случая проверки двух параметров "сцепленных" в один ключ
			DetDetKey.Empty();

			CString DetDetPTFIXLower = theApp.AllDetectors[i][DET_POSTFIX];
			DetDetPTFIXLower = DetDetPTFIXLower.MakeLower(); // перевели все символы постфикса в нижние регистры

			DetDetKey += DetDetPTFIXLower;			// постфикс (преобразованный в нижние регистры)
			DetDetKey += theApp.AllDetectors[i][DET_PROD_VIEW]; // продукт ID

			if(DivDetKey == DetDetKey)
			{DivDetFound = true; break;}
		}
		DetDetKey.Empty();


		theApp.AllDetectors.insert(theApp.AllDetectors.begin(), TitleDetector); // добавляем шапку обратно в начало
		TitleDetector.clear();
		i++; // !!!!!!!!!!!!!!!!!!!!!!!! САМАЯ ВАЖНАЯ ДЕТАЛЬ, ИБО МЫ СНОВА ДОБАВИЛИ В САМЫЙ ВЕРХ ВЕКТОРА ЭЛЕМЕНТ И СДВИНУЛИ ИНДЕКС


// Строка для фиксацйии ошибок на Датчиках: 
		CurDetErrCString.Empty();
		//CurDetErrCString = CurDetErrCString + _T("Датчик № ") + LintToCStr(elementsnumber) + _T("   "); // _T("\n");

// Проверить: СВЕРИТЬ СО ЗНАЧЕНИЕМ ИЗ БД через постфикс+продукт // Если в SOU-файле не совпадает с тем, что имеется в БД, заменить на БД-ное
		DivAtrs = e.attr(L"имя"); // Имя датчика в Системе
		DivDetSYSN = DivAtrs.c_str();
		// 2 detname
		if(DivDetSYSN != theApp.AllDetectors[i][DET_NAME])
		{
			bChanged=true; bDetChanged=true;
			DivDetSYSN = theApp.AllDetectors[i][DET_NAME];
		// Фиксируем в каком датчике (с уже точно правильным именем Датчика) могут быть далее найдены ошибки:
			CurDetErrCString = CurDetErrCString + DivDetSYSN + _T("\n"); //_T("   ");

			CurDetErrCString = CurDetErrCString + _T("Было ") +_T("\"имя\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
												+ _T("Стало ") +_T("\"имя\"")+ _T(" = ") + DivDetSYSN + _T("\n");
		}
		else
		{// Фиксируем в каком датчике (с уже точно правильным именем Датчика) могут быть далее найдены ошибки:
			CurDetErrCString = CurDetErrCString + DivDetSYSN + _T("\n"); //_T("   ");
		}

/*
// Проверяем: Должно быть Непустое и не NULL => ИНАЧЕ => сделать равным Имени Датчика в системе
		DivAtrs = e.attr(L"нр"); // Имя датчика на Графике
		DivDetGRAN = DivAtrs.c_str();
		// НЕТУ
		if(DivDetGRAN.IsEmpty())
		{
			bChanged=true; bDetChanged=true;
			// Если имя датчика пустое, то сделать равным Имени Датчика в системе + и приставить слово "Датчик - " в начало
			DivDetGRAN = _T("Датчик - ") + theApp.AllDetectors[i][1];
			CurDetErrCString = CurDetErrCString + _T("Было ") +_T("\"имя\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
												+ _T("Стало ") +_T("\"имя\"")+ _T(" = ") + DivDetGRAN + _T("\n");
		}
*/

		DivAtrs = e.attr(L"нр"); // Имя датчика на Графике
		DivDetNUMBER = DivAtrs.c_str();
		// 0 detnum
		if(DivDetNUMBER != theApp.AllDetectors[i][DET_NUMBER])
		{
			bChanged=true; bDetChanged=true;
			DivDetNUMBER = theApp.AllDetectors[i][DET_NUMBER];
		// Фиксируем в каком датчике (с уже точно правильным именем Датчика) могут быть далее найдены ошибки:
			CurDetErrCString = CurDetErrCString + DivDetNUMBER + _T("\n"); //_T("   ");

			CurDetErrCString = CurDetErrCString + _T("Было ") +_T("\"нр\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
												+ _T("Стало ") +_T("\"нр\"")+ _T(" = ") + DivDetNUMBER + _T("\n");
		}
		else
		{// Фиксируем в каком датчике (с уже точно правильным именем Датчика) могут быть далее найдены ошибки:
			CurDetErrCString = CurDetErrCString + DivDetNUMBER + _T("\n"); //_T("   ");
		}

/*
// Проверить: СВЕРИТЬ СО ЗНАЧЕНИЕМ ИЗ БД через постфикс+продукт // Если в SOU-файле не совпадает с тем, что имеется в БД, заменить на БД-ное
		DivAtrs = e.attr(L"нр"); // Имя датчика в Системе
		DivDetSYSN = DivAtrs.c_str();
		// 2 detname
		if(DivDetSYSN != theApp.AllDetectors[i][1])
		{
			bChanged=true; bDetChanged=true;
			DivDetSYSN = theApp.AllDetectors[i][1];
			CurDetErrCString = CurDetErrCString + _T("Было ") +_T("\"нр\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
												+ _T("Стало ") +_T("\"нр\"")+ _T(" = ") + DivDetSYSN + _T("\n");
		}

// Проверяем: Должно быть Непустое и не NULL => ИНАЧЕ => сделать равным Имени Датчика в системе
		DivAtrs = e.attr(L"имя"); // Имя датчика на Графике
		DivDetGRAN = DivAtrs.c_str();
		// НЕТУ
		if(DivDetGRAN.IsEmpty())
		{
			bChanged=true; bDetChanged=true;
			DivDetGRAN = theApp.AllDetectors[i][1];
			CurDetErrCString = CurDetErrCString + _T("Было ") +_T("\"имя\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
												+ _T("Стало ") +_T("\"имя\"")+ _T(" = ") + DivDetGRAN + _T("\n");
		}
//*/
// Проверить: Должно быть не пустое + не NULL + Быть либо 1 или 0 => ИНАЧЕ => Значение по умолчанию 1.
		DivAtrs = e.attr(L"активен");
		DivDetACTIVE = DivAtrs.c_str();
		if( (!DivDetACTIVE.IsEmpty()) && (  (DivDetACTIVE==_T("0")) || (DivDetACTIVE==_T("1"))  ) )
		{}
		else
		{
			bChanged=true; bDetChanged=true;
			DivDetACTIVE = _T("1");
			CurDetErrCString = CurDetErrCString + _T("Было ") +_T("\"активен\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
												+ _T("Стало ") +_T("\"активен\"")+ _T(" = ") + DivDetACTIVE + _T("\n");
		}

// Проверить: СВЕРИТЬ СО ЗНАЧЕНИЕМ ИЗ БД через постфикс+продукт // Если в SOU-файле не совпадает с тем, что имеется в БД, заменить на БД-ное
		DivAtrs = e.attr(L"путь");
		DivDetPATH = DivAtrs.c_str();
		CString DivDetPATHLower = DivDetPATH.MakeLower();
		CString DetDetPATHLower = theApp.AllDetectors[i][DET_FILE_PATH].MakeLower();

		// 5 detfilepath
		//if(DivDetPATH != theApp.AllDetectors[i][4])
		if(DivDetPATHLower != DetDetPATHLower) // Теперь проверка не различает старший/младший регистр в котором записаны буквы
		{
			bChanged=true; bDetChanged=true;
			DivDetPATH = theApp.AllDetectors[i][DET_FILE_PATH];
			CurDetErrCString = CurDetErrCString + _T("Было ") +_T("\"путь\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
												+ _T("Стало ") +_T("\"путь\"")+ _T(" = ") + DivDetPATH + _T("\n");
		}

// Проверить: СВЕРИТЬ СО ЗНАЧЕНИЕМ ИЗ БД через постфикс+продукт // Если в SOU-файле не совпадает с тем, что имеется в БД, заменить на БД-ное
		DivAtrs = e.attr(L"удаление");
		DivDetDIST = DivAtrs.c_str();
		double DivDetDISTDouble = _tstof(DivDetDIST);
		double DetDetDISTDouble = _tstof(theApp.AllDetectors[i][DET_DISTANCE]);
		
		// 4 detdistance
		//if(DivDetDIST != theApp.AllDetectors[i][3])
		if(DivDetDISTDouble != DetDetDISTDouble)
		{
			bChanged=true; bDetChanged=true;
			DivDetDIST = theApp.AllDetectors[i][DET_DISTANCE];
			CurDetErrCString = CurDetErrCString + _T("Было ") +_T("\"удаление\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
												+ _T("Стало ") +_T("\"удаление\"")+ _T(" = ") + DivDetDIST + _T("\n");
		}

// Проверить: Должно быть не пустое + не NULL + Быть в заданных пределах: [0 ; 100] + Маска 123
		DivAtrs = e.attr(L"дельта_давление");
		DivDetDPRESS = DivAtrs.c_str();

		bool bDPres=false;
		if( !CheckString(DivDetDPRESS) ) // true - неизменилась
		{bDPres=true;}

		double dDetDPress = _tstof(DivDetDPRESS);
		if(  (dDetDPress <= (double)0) || (dDetDPress > (double)100)  )
		{
			//AfxMessageBox( _T("ВНИМАНИЕ: Параметр \"Дельта Давление\" должен быть задан больше 0 и не больше 100"), MB_ICONWARNING );
			if(dDetDPress <= 0)
			{DivDetDPRESS = _T("0.01");}
			if(dDetDPress > 100)
			{DivDetDPRESS = _T("10");}
			bDPres=true;
		}

		if(bDPres)
		{
			bChanged=true; bDetChanged=true;
			CurDetErrCString = CurDetErrCString + _T("Было ") +_T("\"дельта_давление\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
												+ _T("Стало ") +_T("\"дельта_давление\"")+ _T(" = ") + DivDetDPRESS + _T("\n");
		}

// Проверить: Должно быть не пустое + не NULL + Быть в заданных пределах: [0 ; 200] + Маска 123
		DivAtrs = e.attr(L"дельта_время");
		DivDetDTIIME = DivAtrs.c_str();

		bool bDTime=false;
		if( !CheckString(DivDetDTIIME) ) // true - неизменилась
		{bDTime=true;}

		double dDetDTime = _tstof(DivDetDTIIME);
		if( (dDetDTime <= 0) || (dDetDTime > 10) )
		{
			//AfxMessageBox( _T("ВНИМАНИЕ: Параметр \"Дельта Время\" должен быть задан больше 0 и не больше 10"), MB_ICONWARNING );
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
			CurDetErrCString = CurDetErrCString + _T("Было ") +_T("\"дельта_время\"")+ _T(" = ") + DivAtrs.c_str() + _T(" --- ") 
												+ _T("Стало ") +_T("\"дельта_время\"")+ _T(" = ") + DivDetDTIIME + _T("\n");
		}


///////////////////////////////////////////////////////////////////
// !!!!!  УДАЛЕНИЕ ОТ НАЧАЛА И УДАЛЕНИЕ ОТ КОНЦА ДОБАВИТЬ ПРОВЕРКУ
///////////////////////////////////////////////////////////////////

//		DivAtrs = e.attr(L"удалениеот_начала");
//		DivDetDISTBEGIN = DivAtrs.c_str();

//		DivAtrs = e.attr(L"удалениеот_конца");
//		DivDetDISTEND = DivAtrs.c_str();




		if(bDetChanged) // Если какое-то изменение в Датчике произошло, то только этот Датчик и выводим вместе с изменением
		{
		// Строка для фиксацйии ошибок на конкретном датчике если таковая была: 
			//RetErrCString = _T("Датчик № ") + LintToCStr(elementsnumber) + _T("   ")+ RetErrCString + _T("   "); //_T("\n");
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
		// 2.1) Удаляем старый файл
		CFile::Remove(bstrXMLFile);
		// 2.2) Формируем новый файл
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
	pXMLRootElem->setAttribute(_T("имя"),				_variant_t( CurDivision[0][0] ));

	//if( CurDivision[0][1] == _T("Керосин") )
	//{pXMLRootElem->setAttribute(_T("продукт"),			_variant_t(_T("Ав.топливо")));}
	//else if( CurDivision[0][1] == _T("Дизель") )
	//{pXMLRootElem->setAttribute(_T("продукт"),			_variant_t(_T("Диз.топливо")));}
	//else
	//{pXMLRootElem->setAttribute(_T("продукт"),			_variant_t( CurDivision[0][1] ));}
	pXMLRootElem->setAttribute(_T("продукт"),			_variant_t( CurDivision[0][1] ));

	// "продукт", не ID									_variant_t( CurDivision[0][2] 
	pXMLRootElem->setAttribute(_T("параметр"),			_variant_t( CurDivision[0][3] ));
	pXMLRootElem->setAttribute(_T("следить"),			_variant_t( CurDivision[0][4] ));
	pXMLRootElem->setAttribute(_T("волна"),				_variant_t( CurDivision[0][5] ));
	pXMLRootElem->setAttribute(_T("время_обнаружения"),	_variant_t( CurDivision[0][6] ));


	if(CurDivision.size()>1)
	{
		long NumOfDet=0;
		NumOfDet = CurDivision.size() - 1;		// NumOfDet = Число датчиков (исключая первую запись с параметрами Участка) 

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

			pXMLChild->setAttribute(_T("имя"),				 _variant_t(CurDivision[i][DIV_DET_NAME]	));
			pXMLChild->setAttribute(_T("нр"),				 _variant_t(CurDivision[i][DIV_DET_NUMBER]	));
			pXMLChild->setAttribute(_T("активен"),			 _variant_t(CurDivision[i][DIV_DET_ACTIVE]	));
			pXMLChild->setAttribute(_T("путь"),				 _variant_t(CurDivision[i][DIV_DET_PATH]	));
			pXMLChild->setAttribute(_T("постфикс"),			 _variant_t(CurDivision[i][DIV_DET_PTFIX]	));
			pXMLChild->setAttribute(_T("удаление"),			 _variant_t(CurDivision[i][DIV_DET_DIST]	));
			pXMLChild->setAttribute(_T("дельта_давление"),	 _variant_t(CurDivision[i][DIV_DET_DPRESS]	));
			pXMLChild->setAttribute(_T("дельта_время"),		 _variant_t(CurDivision[i][DIV_DET_DTIIME]	));
//			pXMLChild->setAttribute(_T("удалениеот_начала"), _variant_t(CurDivision[i][DIV_DET_DISTBEG]	));
//			pXMLChild->setAttribute(_T("удалениеот_конца"),	 _variant_t(CurDivision[i][DIV_DET_DISTEND]	));

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


// Кнопка "Удалить" // Внимание при удалении Участка из Списка удаляется и соответсвующий файл .sou в папке "Участки"
void CDivisionChoose::OnBnClickedDivDelBtn()
{
	// TODO: добавьте свой код обработчика уведомлений
	CString EmptyStr("");
	long nCount=0;		// Число записей в Listbox
	long curIndex=0;	// Индекс элемента выбранного в Listbox
	POSITION pos=NULL;	// Номер выбранного элемента (pos = curIndex+1)

	nCount = m_DivChangeList.GetItemCount();
	//взять выделенный элемент из списка отображения
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

	// Непосредственно удаление записи из списка
	// СПИСОК ПОСЛЕ УДАЛЕНИЯ НЕ СОРТИРУЕТСЯ АВТОМАТИЧЕСКИ !!!! 
	// Кусок Кода ниже решает эту проблему:
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


	nCount = m_DivChangeList.GetItemCount();	// Запрос важен, ибо элементов стало на один меньше.


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

	// СПИСОК ПОСЛЕ УДАЛЕНИЯ НЕ СОРТИРУЕТСЯ АВТОМАТИЧЕСКИ !!!! 
	// (*) Придётся это сделать вручную
	//CString LowerName("");
	//nCount = m_DivChangeList.GetItemCount(); // После удаления число элементов станет меньше на 1-н
	//for(long i=curIndex; i<nCount; i++)
	//{
	//	LowerName = m_DivChangeList.GetItemText(i,0);
	//	m_DivChangeList.InsertItem(i, LowerName);
	//}

	//Задумка Выше (*) провалилась, так что мы сначала удалим файл, и потом просто повторно поместим все оставшивеся названия файлов в список:
	// 1) Удаленеие Файла:
	// Получаем полный путь до файла соответсвующнго Участка
	// Далее если путь до папки не пустой продолжаем (стоит проверить наличие папки)
	if(theApp.CurDivisionsPath != EmptyStr)
	{
		CString sPath = theApp.CurDivisionsPath;
		CFileFind hFile;
		CString DivisionFullPath("");				// Полный путь к файлу следующего Участка

		//DivisionFullPath = DivisionFullPath + sPath + _T("\\") + sDivName + _T(".sou");
		DivisionFullPath = DivisionFullPath + sPath + _T("\\") + sDivFileName + _T(".sou");
		bool bFound = false;
		bFound = hFile.FindFile( DivisionFullPath );
				
		if(bFound)
		{
			CFile::Remove(DivisionFullPath);// Полный путь содержится здесь
		}
	}

	// ПЕРЕД УДАЛЕНИЕМ МОЖНО НАПИСАТЬ ПОСЛЕДНЮЮ ПРОВЕРКУ НА ТО, ЕСТЬ ЛИ В ФАЙЛЕ
	// ПРОПИСАННЫЕ ДАТЧИКИ, ИБО ЕСЛИ НИ ОДНОГО НЕТ, ТО МОЖНО УДАЛЯТЬ 100%, А ЕСЛИ ЕСТЬ, ТО ВОПРОС....

	theApp.AllDivisions.erase(theApp.AllDivisions.begin() + curIndex);

/*
	// 2) Перезаполнение списка
	CString DivisionFileName(""); // Имя Файла следующего Участка
	CString wStr_DivName(""); // Имя следующего Участка
	CString wStr_Product(""); // Продукт на данном участке
	theApp.AllDivisionsFileNames.clear();


	CRect rect;
	m_DivChangeList.GetClientRect(rect);


	//m_DivChangeList.DeleteAllItems(); // Предварительно опустошаем список
	// Заполняем список Названиями Участков используя названия файлов .sou из папки "Участки"
	if(theApp.CurDivisionsPath != EmptyStr)
	{
		CString sPath = theApp.CurDivisionsPath;
		CFileFind hFile;
		bool bFound = false;
		bFound = hFile.FindFile( sPath + _T("\\*.sou") );
	
		//m_DivChangeList.InsertColumn(0, _T("Названия Участков"), LVCFMT_LEFT, 300);
		//m_DivChangeList.InsertColumn(1, _T("Продукт"), LVCFMT_LEFT, 100); //rect.Width() );

		long LBiter=0;
		while ( bFound )
		{
			bFound = hFile.FindNextFile();
			//if( (! hFile.IsDots()) && ( hFile.IsDirectory() ) )		
			if( ! hFile.IsDots() )
			{
				DivisionFileName = hFile.GetFileName();

				CString szExt = _tcsrchr(DivisionFileName, '.'); // получаем szExt = ".sou"
				if(szExt == _T(".sou"))
				{
					// Удаляем последние 4 символа из конца каждого файла
					DivisionFileName.Delete(DivisionFileName.GetLength() - szExt.GetLength(), 4);
					// Добавляем только в том случае, если встретился .sou файл
					//m_DivChangeList.InsertItem(LBiter, DivisionFileName);

/////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// Запросим из всех .SOU файлов значение Тэга "продукт"
					CString IniFileName = theApp.IniFileName;
					CString CurDivisionsPath = theApp.CurDivisionsPath;

					// НЕОБХОДИМО ДОПИСАТЬ ПРОВЕРКУ НАЛИЧЕСТВОВАНИЯ ФАЙЛОВ С РАСШИРЕНИЕМ .sou ПО ДАННОМУ ПУТИ !!!!!
					// http://www.rsdn.ru/article/qna/baseserv/fileexist.xml

					CString DivPathWithFiles("");
					CString DivPath("");
	
					DivPath = theApp.CurDivisionsPath;
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
						pRoot = doc.FirstChildElement("Участок_СОУ");
						if(pRoot)
						{
							CStringA AtributeToConvert("");
							CStringA RetConvert("");

							//AtributeToConvert = pRoot->Attribute("имя");
							//wStr = CA2W((LPCSTR)AtributeToConvert);

							AtributeToConvert = pRoot->Attribute("продукт");
							wStr_Product = CA2W((LPCSTR)AtributeToConvert);
							if(wStr_Product==_T("Ав.топливо"))
							wStr_Product = _T("Керосин");
							if(wStr_Product==_T("Диз.топливо"))
							wStr_Product = _T("Дизель");

						}
					}
					else
					{
						//MessageBox(	_T("Ошибка при открытии XML-файла."), ERROR_STR, MB_ICONERROR );
						if ( doc.Error() )
						{
							CStringA docErrorDescA = doc.ErrorDesc();
							CString docErrorDescW(docErrorDescA);
							CStringA docValueA;
							CString docValueW(docValueA);
							AfxMessageBox(_T("XML-Файл по заданному пути отсуствует.\nНомер ошибки: ") + docValueW + _T(" Описание:  ") + docErrorDescW);

						}
					}
////////////////////////////////////// Завершили запрос

					// Ранее отображалось имя файла участка: 
					//m_DivChangeList.InsertItem(LBiter, DivisionFileName);
					// так как нам нужны только:
					//m_DivChangeList.SetItemText(LBiter, 0, DivisionFileName);
					//m_DivChangeList.SetItemText(LBiter, 1, wStr_Product);

					// Теперь отображается название участка:
					m_DivChangeList.InsertItem(LBiter, wStr_DivName);
					// так как нам нужны только:
					m_DivChangeList.SetItemText(LBiter, 0, wStr_DivName);
					m_DivChangeList.SetItemText(LBiter, 1, wStr_Product);

					theApp.AllDivisionsFileNames.push_back(DivisionFileName);
				}
				//AfxMessageBox(DivisionFileName);
			}
			LBiter++;
		}

	
		//m_DivChangeList.SetExtendedStyle( m_DivChangeList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

		// Устанавливаем выделенный в ListControl-е элемент в соответствие с "соглашениями" в Windows
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
		// Устанавливаем выделенный в ListControl-е элемент в соответствие с "соглашениями" в Windows
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

// Кнопка "Добавить"
void CDivisionChoose::OnBnClickedDivAddBtn()
{
	// TODO: добавьте свой код обработчика уведомлений
	//iCtrListItem++;
	//m_DivChangeList.InsertItem(iCtrListItem, _T("Item ") + LintToCStr(iCtrListItem));

	// 0 // В случае с "Добавить" нам не нужно получать Имя выбранного Участка или проверять, что Участок выбран в принципе.
	/*
	// 1 // Сохраняем Имя выбранного участка, чтобы использовать его в окне редактирования участка
	CString EmptyStr("");
	long nCount=0;		// Число записей в Listbox
	long curIndex=0;	// Индекс элемента выбранного в Listbox
	POSITION pos=NULL;	// Номер выбранного элемента (pos = curIndex+1)

	nCount = m_DivChangeList.GetItemCount();
	//взять выделенный элемент из списка отображения
	pos = m_DivChangeList.GetFirstSelectedItemPosition();
	if(pos==NULL) return;	 // В случае, если ничего не выбрано:
							// 1) не открываем окно редактирования участка
							// 2) не блокируем ни одну из кнопок
	curIndex = m_DivChangeList.GetNextSelectedItem(pos);

	CString sDivName = m_DivChangeList.GetItemText(curIndex,0);

	// 1.1 // Теперь через этот параметр все прочие окна будут знать имя текущего Участка
	theApp.CurDivision = sDivName;
	*/
	// 1.2 // Теперь через этот параметр все прочие окна будут знать, что нажата кнопка "Добавить"
	theApp.ChangeDivBtnClicked = theApp.DIV_BTN_ADD;

	// 2 // Блокируем все кнопки до тех пор пока пользователь не закончит работать с вбранным участком
	HandleBtns();

	// 3 // Открываем окно для редктирования Участка
	CDivisionEdit* p_DivisionEditDlg = new CDivisionEdit;
	p_DivisionEditDlg->Create(IDD_EDIT_DIVISION_DLG, this);
	p_DivisionEditDlg->ShowWindow(SW_SHOW);
}


// Кнопка "Копировать"
void CDivisionChoose::OnBnClickedDivCopyBtn()
{
	// TODO: добавьте свой код обработчика уведомлений
	// 0 // В случае с "Изменить" нам важно получить Имя выбранного Участка и проверять, что Участок выбран в принципе.
	// 1 // Сохраняем Имя выбранного участка, чтобы использовать его в окне редактирования участка
	CString EmptyStr("");
	long nCount=0;		// Число записей в Listbox
	long curIndex=0;	// Индекс элемента выбранного в Listbox
	POSITION pos=NULL;	// Номер выбранного элемента (pos = curIndex+1)

	nCount = m_DivChangeList.GetItemCount();
	//взять выделенный элемент из списка отображения
	pos = m_DivChangeList.GetFirstSelectedItemPosition();
	if(pos==NULL) return;	 // В случае, если ничего не выбрано:
							// 1) не открываем окно редактирования участка
							// 2) не блокируем ни одну из кнопок
	curIndex = m_DivChangeList.GetNextSelectedItem(pos);
	if( curIndex == (-1) )  return;

	CString sDivName("");
	CString sDivName_Original("");

	//sDivName = m_DivChangeList.GetItemText(curIndex,0);
	//sDivName_Original = sDivName;
	sDivName = theApp.AllDivisions[curIndex][0];
	sDivName_Original = sDivName;
	theApp.DivisionFileName = sDivName;


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
		_bstr_t bstrOutput("");
		bool validXml=false;

		HRESULT hr = CoInitialize(NULL);
		if(SUCCEEDED(hr))
		{
			try{ bstrOutput = theApp.validateDivFile(DivisionFilePathBstr, validXml); }
			catch(_com_error &e)
			{ bstrOutput = theApp.dump_com_error(e); }
		}

		if(validXml) // случай, когда Файл "Валидный" и датчики можно запросить
		{
			readDivisionFile(DivisionFilePath);
		}
		else //if(!validXml)
		{
			if(bstrOutput.length()>0)
			MessageBox(bstrOutput, L"Ошибка в файле или его стрктуре", MB_OK);

			return ; // просто возвращаемся и ничего не делаем
		}
		CoUninitialize();

		//MessageBox(	_T("RETTRUE"), ERROR_STR, MB_ICONERROR );
	}




	// Алгоритм по нахождению следжующего номера "копии", что требуется добавить 
	long lNextName = 0;
	CString sNextName("");
	bool Original1=false;
	bool Original2=false;

	bool OriginalCheck1=false;
	bool OriginalCheck2=false;
	bool OriginalCheck3=false;
	CString k0("0"), k1("1"), k2("2"), k3("3"), k4("4"), k5("5"), k6("6"), k7("7"), k8("8"), k9("9");
	// 1 нужно выяснить первое - нет ли в имени оригинального файла " - копия (?)"
	CString CurCopyNum_Str("");
	long CurCopyNum_Int=0;
	std::map<long, bool> CopyMap;

	// если ЕСТЬ
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
				// Наконец останется проверить последние символы: " - копия ("
				if( sDivName.GetLength() > (CurCopyNum_Str.GetLength() + 11) )
				{
					if(	( sDivName[i-0] == (CString)"(" ) &&
						( sDivName[i-1] == (CString)" " ) &&
						( sDivName[i-2] == (CString)"я" ) &&
						( sDivName[i-3] == (CString)"и" ) &&
						( sDivName[i-4] == (CString)"п" ) &&
						( sDivName[i-5] == (CString)"о" ) &&
						( sDivName[i-6] == (CString)"к" ) &&
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

	// если НЕТ
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

			if( (eq_elem == sDivName.GetLength()) && (sNextName != sDivName) ) // значит можно проверять вторую часть с " - копия (?)"
			{
				OriginalCheck1=true;
				CString sDivNameCopy("");
				CString sDivNameCopyNum("");
				sDivNameCopy += _T(" - копия (");

				if(	( sNextName[sDivName.GetLength() + 0] == (CString)" " ) &&
					( sNextName[sDivName.GetLength() + 1] == (CString)"-" ) &&
					( sNextName[sDivName.GetLength() + 2] == (CString)" " ) &&
					( sNextName[sDivName.GetLength() + 3] == (CString)"к" ) &&
					( sNextName[sDivName.GetLength() + 4] == (CString)"о" ) &&
					( sNextName[sDivName.GetLength() + 5] == (CString)"п" ) &&
					( sNextName[sDivName.GetLength() + 6] == (CString)"и" ) &&
					( sNextName[sDivName.GetLength() + 7] == (CString)"я" ) &&
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
						{//Всё в порядке
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
						OriginalCheck3=true; // Если проверка дошла до сюда, значит копии имеются
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
			{// наш следующий доступный номер копии
				lNextName = i;
				break;
			}
		}
	}

	if(!Original1 && !Original2)
	sDivName = sDivName_Original;

	// 1.1 // Теперь через этот параметр все прочие окна будут знать имя ФАЙЛА текущего Участка
	theApp.DivisionFileName = sDivName;
	theApp.DivNextFileName = lNextName;
	// 1.2 // Теперь через этот параметр все прочие окна будут знать, что нажата кнопка "Изменить"
	theApp.ChangeDivBtnClicked = theApp.DIV_BTN_COPY;

	// 2 // Блокируем все кнопки до тех пор пока пользователь не закончит работать с выбранным участком
	HandleBtns();

	// 3 // Открываем окно для редктирования Участка
	CDivisionEdit* p_DivisionEditDlg = new CDivisionEdit;
	p_DivisionEditDlg->Create(IDD_EDIT_DIVISION_DLG, this);
	p_DivisionEditDlg->ShowWindow(SW_SHOW);
}



// Кнопка "Проверить"
void CDivisionChoose::OnBnClickedDivValidBtn()
{
	// TODO: добавьте свой код обработчика уведомлений
	// 0 // В случае с "Изменить" нам важно получить Имя выбранного Участка и проверять, что Участок выбран в принципе.
	// 1 // Сохраняем Имя выбранного участка, чтобы использовать его в окне редактирования участка
	CString EmptyStr("");
	long nCount=0;		// Число записей в Listbox
	long curIndex=0;	// Индекс элемента выбранного в Listbox
	POSITION pos=NULL;	// Номер выбранного элемента (pos = curIndex+1)

	nCount = m_DivChangeList.GetItemCount();
	//взять выделенный элемент из списка отображения
	pos = m_DivChangeList.GetFirstSelectedItemPosition();
	if(pos==NULL) return;	 // В случае, если ничего не выбрано:
							// 1) не открываем окно редактирования участка
							// 2) не блокируем ни одну из кнопок
	curIndex = m_DivChangeList.GetNextSelectedItem(pos);
	if( curIndex == (-1) )  return;

	//CString sDivName = m_DivChangeList.GetItemText(curIndex,0);
	CString sDivName = theApp.AllDivisions[curIndex][0];
	theApp.DivisionFileName = sDivName;


	// 0 // Необходимо получить из названия Файла участка, полноценный путь и файл в формате название_участка.sou и начать парсинг этого файла
	// 1 Проверяем указанный (если указан) в ini-файле путь к папке с Участками (файлами  *.sou)
	// Если есть перепроверяем где находится приложение в данный момент, есть ли в тойже папке, что и exe-шник папка "Участки"
	// и проверяем совпадает ли [путь, где находится наш exe-шник] + [/Участки] с тем, что указано в ini-файле, если нет перезаписываем, с предупредительным сообщением.

	CString IniFileName = theApp.IniFileName;			// ???
	CString CurDivisionsPath = theApp.CurDivisionsPath;	// ???

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
		_bstr_t bstrOutput("");
		bool validXml=false;
		HRESULT hr = CoInitialize(NULL);
		if(SUCCEEDED(hr))
		{
			try{ bstrOutput = theApp.validateDivFile(DivisionFilePathBstr, validXml); }
			catch(_com_error &e)
			{bstrOutput = theApp.dump_com_error(e);}
		}

		if(validXml) // случай, когда Файл "Валидный" и датчики можно запросить
		{
			readDivisionFile(DivisionFilePath);
		}
		else //if(!validXml)
		{
			if(bstrOutput.length()>0)
			MessageBox(bstrOutput, L"Ошибка в файле или его стрктуре", MB_OK);

			return ; // просто возвращаемся и ничего не делаем
		}
		CoUninitialize();

	}



	// 1.1 // Теперь через этот параметр все прочие окна будут знать имя ФАЙЛА текущего Участка
	theApp.DivisionFileName = sDivName;
	// 1.2 // Теперь через этот параметр все прочие окна будут знать, что нажата кнопка "Изменить"
	theApp.ChangeDivBtnClicked = theApp.DIV_BTN_VALID;

	// 2 // Блокируем все кнопки до тех пор пока пользователь не закончит работать с вбранным участком
	//m_BtnDiv_Add.EnableWindow(FALSE);
	//m_BtnDiv_Del.EnableWindow(FALSE);
	//m_BtnDiv_Copy.EnableWindow(FALSE);
	//m_BtnDiv_Valid.EnableWindow(FALSE);
	//m_BtnDiv_Change.EnableWindow(FALSE);
	//m_BtnDiv_Look.EnableWindow(FALSE);
	//m_BtnDiv_Exit.EnableWindow(FALSE);

	// 3 // Открываем окно для редактирования Участка
}



// Кнопка "Изменить"
void CDivisionChoose::OnBnClickedDivEditBtn()
{
	// TODO: добавьте свой код обработчика уведомлений
	// 0 // В случае с "Изменить" нам важно получить Имя выбранного Участка и проверять, что Участок выбран в принципе.
	// 1 // Сохраняем Имя выбранного участка, чтобы использовать его в окне редактирования участка
	CString EmptyStr("");
	long nCount=0;		// Число записей в Listbox
	long curIndex=0;	// Индекс элемента выбранного в Listbox
	POSITION pos=NULL;	// Номер выбранного элемента (pos = curIndex+1)

	nCount = m_DivChangeList.GetItemCount();
	//взять выделенный элемент из списка отображения
	pos = m_DivChangeList.GetFirstSelectedItemPosition();
	if(pos==NULL) return;	 // В случае, если ничего не выбрано:
							// 1) не открываем окно редактирования участка
							// 2) не блокируем ни одну из кнопок
	curIndex = m_DivChangeList.GetNextSelectedItem(pos);
	if( curIndex == (-1) )  return;

	//CString sDivName = m_DivChangeList.GetItemText(curIndex,0);
	CString sDivName = theApp.AllDivisions[curIndex][DIVALL_FILE_NAME];
	theApp.DivisionFileName = sDivName;


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

		if( !FileExists( DivPathWithFiles ) )
		{
			MessageBox( _T("В папке с Участками отсутствуют файлы Участков\n Убедитесь, что:\n")
						_T("1) Папка \"Участки\" находится в той же папке, что и утилита.\n")
						_T("2) В папке имеются файлы с расширением .sou"),
						_T("ОШИБКА"), MB_ICONERROR);
		}

		//delete [] _DivPathWithFiles;

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
		_bstr_t bstrOutput("");
		bool validXml=false;
		HRESULT hr = CoInitialize(NULL);
		if(SUCCEEDED(hr))
		{
			try{ bstrOutput = theApp.validateDivFile(DivisionFilePathBstr, validXml); }
			catch(_com_error &e)
			{bstrOutput = theApp.dump_com_error(e);}
		}

		if(validXml) // случай, когда Файл "Валидный" и датчики можно запросить
		{
			readDivisionFile(DivisionFilePath);
		}
		else //if(!validXml)
		{
			if(bstrOutput.length()>0)
			MessageBox(bstrOutput, L"Ошибка в файле или его стрктуре", MB_OK);

			return ; // просто возвращаемся и ничего не делаем
		}
		CoUninitialize();

	}



	// 1.1 // Теперь через этот параметр все прочие окна будут знать имя ФАЙЛА текущего Участка
	theApp.DivisionFileName = sDivName;
	// 1.2 // Теперь через этот параметр все прочие окна будут знать, что нажата кнопка "Изменить"
	theApp.ChangeDivBtnClicked = theApp.DIV_BTN_CHANGE;

	// 2 // Блокируем все кнопки до тех пор пока пользователь не закончит работать с вбранным участком
	HandleBtns();

	// 3 // Открываем окно для редктирования Участка
	CDivisionEdit* p_DivisionEditDlg = new CDivisionEdit;
	p_DivisionEditDlg->Create(IDD_EDIT_DIVISION_DLG, this);
	p_DivisionEditDlg->ShowWindow(SW_SHOW);
}

// Кнопка "Просмотр"
void CDivisionChoose::OnBnClickedDivLookBtn()
{
	// TODO: добавьте свой код обработчика уведомлений
	// 0 // В случае с "Просмотр" нам важно получить Имя выбранного Участка и проверять, что Участок выбран в принципе.
	// 1 // Сохраняем Имя выбранного участка, чтобы использовать его в окне редактирования участка
	CString EmptyStr("");
	long nCount=0;		// Число записей в Listbox
	long curIndex=0;	// Индекс элемента выбранного в Listbox
	POSITION pos=NULL;	// Номер выбранного элемента (pos = curIndex+1)

	nCount = m_DivChangeList.GetItemCount();
	//взять выделенный элемент из списка отображения
	pos = m_DivChangeList.GetFirstSelectedItemPosition();
	if(pos==NULL) return;	 // В случае, если ничего не выбрано:
							// 1) не открываем окно редактирования участка
							// 2) не блокируем ни одну из кнопок
	curIndex = m_DivChangeList.GetNextSelectedItem(pos);
	if( curIndex == (-1) )  return;

	//CString sDivName = m_DivChangeList.GetItemText(curIndex,0);
	CString sDivName = theApp.AllDivisions[curIndex][0];
	theApp.DivisionFileName = sDivName;


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
		_bstr_t bstrOutput("");
		bool validXml=false;
		HRESULT hr = CoInitialize(NULL);
		if(SUCCEEDED(hr))
		{
			try{ bstrOutput = theApp.validateDivFile(DivisionFilePathBstr, validXml); }
			catch(_com_error &e)
			{bstrOutput = theApp.dump_com_error(e);}
		}

		if(validXml) // случай, когда Файл "Валидный" и датчики можно запросить
		{
			readDivisionFile(DivisionFilePath);
		}
		else //if(!validXml)
		{
			if(bstrOutput.length()>0)
			MessageBox(bstrOutput, L"Ошибка в файле или его стрктуре", MB_OK);

			return ; // просто возвращаемся и ничего не делаем
		}
		CoUninitialize();

	}


	// 1.1 // Теперь через этот параметр все прочие окна будут знать имя ФАЙЛА выбранного Участка
	theApp.DivisionFileName = sDivName;
	// 1.2 // Теперь через этот параметр все прочие окна будут знать, что нажата кнопка "Просмотр"
	theApp.ChangeDivBtnClicked = theApp.DIV_BTN_LOOK;

	// 2 // Блокируем все кнопки до тех пор пока пользователь не закончит работать с вбранным участком


	// 3 // Открываем окно для редктирования Участка
	CDivisionEdit* p_DivisionEditDlg = new CDivisionEdit;
	p_DivisionEditDlg->Create(IDD_EDIT_DIVISION_DLG, this);
	p_DivisionEditDlg->ShowWindow(SW_SHOW);
}

// Кнопка "Выход"   из окна "НАСТРОИТЬ"
void CDivisionChoose::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений
	//HWND HwndSOUDlg=NULL;
	//::GetDlgItem(HwndSOUDlg, IDD_SOUGENERATOR_DIALOG);
	//::PostMessage(HwndSOUDlg, WM_DIVISION_CHOOSE_EXIT,0,0);
	theApp.ChangeDivBtnClicked = theApp.DIV_NOBTN;

	AfxGetMainWnd()->PostMessage(WM_DIVISION_CHOOSE_EXIT, 0, 0);

	CDialog::OnCancel();
}


// Нажатие на кнопку "Сохранить" из окна "Настроить Участок"
LRESULT CDivisionChoose::OnDivisionEditSave( WPARAM wparam , LPARAM lparam )
{
	long nCount=0;		// Число записей в Listbox
	long curIndex=0;	// Индекс элемента выбранного в Listbox
	POSITION pos=NULL;	// Номер выбранного элемента (pos = curIndex+1)

	nCount = m_DivChangeList.GetItemCount();
	//взять выделенный элемент из списка отображения
	pos = m_DivChangeList.GetFirstSelectedItemPosition();
	curIndex = m_DivChangeList.GetNextSelectedItem(pos);
	//if( curIndex == (-1) )  return;

	// Убрать выделение у того, на который мы нажали, иначе выделений в последствие будет 2 штуки.
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

	// Последнее, что нужно сделать по кнопке "Сохранить Участок" это обновить список Участков
	long AddedDivNumInt=0;
	bool AddedDivNumBl=false;
	CString DivisionNameInList("");	// Имя следующего Участка, находящегося в Списке типа ListControl
	CString DivisionFileName("");	// Имя следующего Файла Участка
	CString wStr("");				// Продукт на данном участке
	CString EmptyStr("");
	theApp.AllDivisionsFileNames.clear();

	std::vector<std::vector<CString>> NewDivisions; // Вновь запрошенные параметры у всех SOU файлов, причём не важно был ли добавлен/скопирован новый или были изменения
	std::vector<CString> OneDivision;


	//for(int i = 0; i < 5; i++)
	//{
	//	cs.Format(_T("Участок № %d"), i+1);
	//	m_DivChangeList.InsertItem(i, cs);
	//}

	CRect rect;
	m_DivChangeList.GetClientRect(rect);

////	m_DivChangeList.DeleteAllItems();

	// Заполняем список Названиями Участков используя названия файлов .sou из папки "Участки"
	//m_DivChangeList.DeleteAllItems();	// Предварительно очищаем список с Учыастками
	//m_DivChangeList.RemoveAllGroups();	// Предварительно очищаем список с Учыастками
	if(theApp.CurDivisionsPath != EmptyStr)
	{
		CString sPath = theApp.CurDivisionsPath;
		CFileFind hFile;
		bool bFound = false;
		bFound = hFile.FindFile( sPath + _T("\\*.sou") );

		//m_DivChangeList.InsertColumn(0, _T("Названия Участков"), LVCFMT_LEFT, 300);
		//m_DivChangeList.InsertColumn(1, _T("Продукт"), LVCFMT_LEFT, 100); //rect.Width() );

		long LBiter=0;
		while ( bFound )
		{
			bFound = hFile.FindNextFile();
			//if( (! hFile.IsDots()) && ( hFile.IsDirectory() ) )		
			if( ! hFile.IsDots() )
			{
				DivisionFileName = hFile.GetFileName();

				CString szExt = _tcsrchr(DivisionFileName, '.'); // получаем szExt = ".sou"
				if(szExt == _T(".sou"))
				{
					// Удаляем последние 4 символа из конца каждого файла
					DivisionFileName.Delete(DivisionFileName.GetLength() - szExt.GetLength(), 4);

					// !!! В ВЕКТОРЕ должны содержаться названия Файлов БЕЗ РАСШИРЕНИЙ !!!!
					OneDivision.push_back(DivisionFileName);		// [0] - Название файла

					// Добавляем только в том случае, если встретился .sou файл
					//m_DivChangeList.InsertItem(LBiter, DivisionFileName);

/////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// Запросим из всех .SOU файлов значение Тэга "продукт"
					CString IniFileName = theApp.IniFileName;
					CString CurDivisionsPath = theApp.CurDivisionsPath;

					// НЕОБХОДИМО ДОПИСАТЬ ПРОВЕРКУ НАЛИЧЕСТВОВАНИЯ ФАЙЛОВ С РАСШИРЕНИЕМ .sou ПО ДАННОМУ ПУТИ !!!!!
					// http://www.rsdn.ru/article/qna/baseserv/fileexist.xml

					CString DivPathWithFiles("");
					CString DivPath("");
	
					DivPath = theApp.CurDivisionsPath;
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

					if(validXml) // случай, когда Файл "Валидный" и датчики можно запросить
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
						//TElem subroot = eroot.subnode(L"Участок_СОУ");
						wstring DivAtrs;

						DivAtrs = eroot.attr(L"имя"			);		OneDivision.push_back(DivAtrs.c_str());	// [0] - Название Участка
						DivAtrs = eroot.attr(L"труба"		);		OneDivision.push_back(DivAtrs.c_str());	//// [1] - Название трубопровода
						DivAtrs = eroot.attr(L"труба_код"	);		OneDivision.push_back(DivAtrs.c_str());	//// [2] - ID трубопровода
						DivAtrs = eroot.attr(L"продукт"		);		OneDivision.push_back(DivAtrs.c_str());	// [3] - Название Продукта в Интерфейсе
						DivAtrs = eroot.attr(L"продукт_код"	);		OneDivision.push_back(DivAtrs.c_str());	//// [4] - ID Продукта
						DivAtrs = eroot.attr(L"параметр"	);		OneDivision.push_back(DivAtrs.c_str());	// [5] - Параметр
						DivAtrs = eroot.attr(L"следить"		);		OneDivision.push_back(DivAtrs.c_str());	// [6] - Следить
						DivAtrs = eroot.attr(L"волна"		);		OneDivision.push_back(DivAtrs.c_str());	// [7] - Волна
						DivAtrs = eroot.attr(L"время_обнаружения");	OneDivision.push_back(DivAtrs.c_str());	// [8] - Время_обнаружения
						DivAtrs = eroot.attr(L"труба_длина"	);		OneDivision.push_back(DivAtrs.c_str());	//// [9] - Длина трубопровода
						DivAtrs = eroot.attr(L"имя_начала"	);		OneDivision.push_back(DivAtrs.c_str());	//// [10] - Имя начала Участка
						DivAtrs = eroot.attr(L"имя_конца"	);		OneDivision.push_back(DivAtrs.c_str());	//// [11] - Имя Конца Участка

						NewDivisions.push_back(OneDivision);
						OneDivision.clear();

						int u=0;
					}
					else //if(!validXml)
					{
						if(bstrOutput.length()>0)
						MessageBox(bstrOutput, L"Ошибка в файле или его стрктуре", MB_OK);

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
	// 2 // После получения всех параметров всех участков, зная эти параметры отсортируем всё в векторе по названию Участков
	
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
	// 3 // Получив новый отсортированный список всех участков, выясним было ли что-то добавлено/откпировано или какой-то файл просто изменяли

	// Улучшим предыдущий алгоритм: В зависимости от нажатой кнопки МЫ
	// 1.1 Добав: В новом отсортированном списке (NewDivisions) находим по старому списку (theApp.AllDivisions)
	// новый участок, и запоминаем его индекс в новом. Сносим старый список, и помещаем новый в ЛистБокс, и выделяем соответстсвующий индекс
	// 1.2 Копир: ТО ЖЕ САМОЛЕ ЧТО И ДОБАВИТЬ 
	// 1.3 Измен: ничего 1.4 Просмотр: ничего

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
	case theApp.DIV_BTN_ADD:  // нажата кнопка "Добавить Участок"
	case theApp.DIV_BTN_COPY: // нажата кнопка "Копировать Участок"
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
			// Проскроллировать до нужной выбранной строки
			m_DivChangeList.EnsureVisible(nNewDivisionIndex, true);
			m_DivChangeList.SetItemState(nNewDivisionIndex, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
			m_DivChangeList.SetFocus();
		}
		break;

	//case theApp.DIV_BTN_CHANGE: //нажата кнопка "Изменить Участок"
	//case theApp.DIV_BTN_LOOK: // нажата кнопка "Просмотр Участка"
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
			// так как нам нужны только:
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
			// так как нам нужны только:
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
			// так как нам нужны только:
			m_DivChangeList.SetItemText(i, 0, theApp.AllDivisions[i][1]);
			m_DivChangeList.SetItemText(i, 1, theApp.AllDivisions[i][3]);
		}
	}
*/	

	theApp.AllDivisions = NewDivisions; // Новый и отсортированный список помещаем полностью в старый вектор

	//theApp.AllDetectors.clear();
	theApp.FullDivision.clear();
	//theApp.DivDetectors.clear();
	theApp.DivSortDetectors.clear();


	// Устанавливаем выделенный в ListControl-е элемент в соответствие с "соглашениями" в Windows
	if( (curIndex < nCount) && (m_DivChangeList.GetItemCount() > 0) )
	{
		if( (theApp.ChangeDivBtnClicked == theApp.DIV_BTN_COPY) || (theApp.ChangeDivBtnClicked == theApp.DIV_BTN_ADD) )
		{
			// Проскроллировать в до нужной выбранной строки
			//int Scrol_pos=0;	// Номер выбранного элемента (pos = curIndex+1)
			//Scrol_pos = m_DivChangeList.GetScrollPos(SB_VERT);
			//m_DivChangeList.SetScrollPos(SB_VERT,curIndex); // Скрол сам двигается, но в окне ничего не происходит
			//m_DivChangeList.ScrollWindow(SB_VERT,curIndex,0,0);
			//m_DivChangeList.SetHotItem(AddedDivNumInt);
			
			//m_DivChangeList.SetView(AddedDivNumInt);
			//m_DivChangeList.UpdateWindow();
			//m_DivChangeList.InsertItem(0, _T("1"));
			//m_DivChangeList.DeleteItem(0);
			
			// Проскроллировать до нужной выбранной строки
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

	theApp.AllDivisions = NewDivisions; // Новый и отсортированный список помещаем полностью в старый вектор

	theApp.FullDivision.clear();
	theApp.DivSortDetectors.clear();


	return 0;
}


// Нажатие на кнопку "Выход" из окна "Настроить Участок"
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
//////////////////// ПРОЧИЕ МЕТОДЫ

CString CDivisionChoose::LintToCStr(long int x)
{
	CString strX;
	strX.Format( _T("%i"), x ); // %d // %l
	return strX;
}


CString CDivisionChoose::DoubleToCStr(double x, int count) // x - число, count - число знаков после запятой
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
	// TODO: добавьте свой код обработчика уведомлений

	POSITION pos=NULL;	// Номер выбранного элемента (pos = curIndex+1)
	//взять выделенный элемент из списка отображения
	pos = m_DivChangeList.GetFirstSelectedItemPosition();
	iCtrChoosenListItem = m_DivChangeList.GetNextSelectedItem(pos);

	*pResult = 0;
}


void CDivisionChoose::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
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


// Функция _findfirst возвращает информацию о первом файле, удовлетворяющем заданной маске поиска.
bool CDivisionChoose::FileExists(const wchar_t *fname)
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






/*
CString CDivisionChoose::DocErrorGetErrorInRus(CString DescriptionEng)
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

			// Меняем размеры:	List-бокса с Датчиками
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
			// Меняем размеры и позиции:	Кнопок под Листбоксом с Датчиками

			// Меняем позицию:
			pWnd = GetDlgItem(IDC_DIV_ADD_BTN);
			pWnd->GetWindowRect(&CurObjectRect);
			ScreenToClient(&CurObjectRect);
			m_BtnDiv_Add.MoveWindow( CurObjectRect.left	, formHeightArg - 30, CurObjectRect.Width()	, CurObjectRect.Height()	);

			// Меняем позицию:
			pWnd = GetDlgItem(IDC_DIV_DEL_BTN);
			pWnd->GetWindowRect(&CurObjectRect);
			ScreenToClient(&CurObjectRect);
			m_BtnDiv_Del.MoveWindow( CurObjectRect.left	, formHeightArg - 30, CurObjectRect.Width()	, CurObjectRect.Height()	);

			// Меняем позицию:
			pWnd = GetDlgItem(IDC_DIV_COPY_BTN);
			pWnd->GetWindowRect(&CurObjectRect);
			ScreenToClient(&CurObjectRect);
			m_BtnDiv_Copy.MoveWindow( CurObjectRect.left	, formHeightArg - 30, CurObjectRect.Width()	, CurObjectRect.Height()	);

			// Меняем позицию:
			//pWnd = GetDlgItem(IDC_DIV_VALID_BTN);
			//pWnd->GetWindowRect(&CurObjectRect);
			//ScreenToClient(&CurObjectRect);
			//m_BtnDiv_Valid.MoveWindow( CurObjectRect.left	, formHeightArg - 30, CurObjectRect.Width()	, CurObjectRect.Height()	);

			// Меняем позицию:
			pWnd = GetDlgItem(IDC_DIV_EDIT_BTN);
			pWnd->GetWindowRect(&CurObjectRect);
			ScreenToClient(&CurObjectRect);
			m_BtnDiv_Change.MoveWindow( CurObjectRect.left	, formHeightArg - 30, CurObjectRect.Width()	, CurObjectRect.Height()	);

			// Меняем позицию:
			pWnd = GetDlgItem(IDC_DIV_LOOK_BTN);
			pWnd->GetWindowRect(&CurObjectRect);
			ScreenToClient(&CurObjectRect);
			m_BtnDiv_Look.MoveWindow( CurObjectRect.left	, formHeightArg - 30, CurObjectRect.Width()	, CurObjectRect.Height()	);

			// Меняем позицию:
			pWnd = GetDlgItem(IDCANCEL);
			pWnd->GetWindowRect(&CurObjectRect);
			ScreenToClient(&CurObjectRect);
			m_BtnDiv_Exit.MoveWindow( CurObjectRect.left	, formHeightArg - 30, CurObjectRect.Width()	, CurObjectRect.Height()	);

			int u=0;
		}
		else
		{
		} // Данный случай нас не интересует
	}
//#endif


	return;


} // OnSize()




