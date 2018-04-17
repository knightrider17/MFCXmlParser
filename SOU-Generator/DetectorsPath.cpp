// DetectorsPath.cpp: файл реализацииpath
//

#include "stdafx.h"
#include "SOU-Generator.h"
#include "SOU-GeneratorDlg.h"
#include "DetectorsPath.h"
#include "afxdialogex.h"

#include "helpful.h"

#include "TElem.h"

// диалоговое окно CDetectorsPath

IMPLEMENT_DYNAMIC(CDetectorsPath, CDialog)

CDetectorsPath::CDetectorsPath(CWnd* pParent /*=NULL*/)
	: CDialog(CDetectorsPath::IDD, pParent)
{

}

CDetectorsPath::~CDetectorsPath()
{
}

void CDetectorsPath::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PATH_EDIT, m_EditDetectorsPath);
	DDX_Control(pDX, IDC_PATH_TEXT, m_TextDetectorsPath);
	DDX_Control(pDX, IDOK, m_BtnSaveApplyPath);
	DDX_Control(pDX, IDC_SEARCH_PATH, m_BtnSearchXML);
}


BEGIN_MESSAGE_MAP(CDetectorsPath, CDialog)
	ON_BN_CLICKED(IDC_SEARCH_PATH, &CDetectorsPath::OnBnClickedSearchPath)
	ON_BN_CLICKED(IDOK, &CDetectorsPath::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDetectorsPath::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_PATH_EDIT, &CDetectorsPath::OnEnChangePathEdit)
END_MESSAGE_MAP()


// обработчики сообщений CDetectorsPath

BOOL CDetectorsPath::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString EmptyStr("");

	CurrentDetectorsPath = theApp.IniDetectorsPath;
	m_BtnSaveApplyPath.EnableWindow(FALSE);

	if(theApp.IniDetectorsPath == EmptyStr)
	{m_TextDetectorsPath.SetWindowText(EmptyStr);}
	else
	{
		m_EditDetectorsPath.SetWindowText(theApp.IniDetectorsPath);
		m_TextDetectorsPath.SetWindowText(theApp.IniDetectorsPath);
	}

// GetOpenFileName


	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// Кнопка "Найти"
void CDetectorsPath::OnBnClickedSearchPath()
{
	// TODO: добавьте свой код обработчика уведомлений

	//CFileDialog's constructor creates an instance of CFileDialog that sets or modifies values in 
	//the m_ofn structure. After initialization, calling DoModal would display the File Open DialogBox.
	//Following is a prototype for CFileDialog
	//CFileDialog( BOOL bOpenFileDialog, LPCTSTR lpszDefExt = NULL, LPCTSTR lpszFileName = NULL, 
	//DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, LPCTSTR lpszFilter = NULL, CWnd* pParentWnd = NULL );


	wchar_t szFilters[]= _T("XML файлы (*.xml)|*.xml|Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*||");
	// Create an Open dialog; the default file name extension is ".my".
	CFileDialog fileDlg(TRUE, _T("xml"), _T("*.xml"), OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this,0,0);

	//In case if you want CFileDialog to browse only certain types of files. Say jpg only. Following is example code:
	//CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_FILEMUSTEXIST, _T("JPG Files(*.jpg)|*.jpg||"),this);

	// Display the file dialog. When user clicks OK, fileDlg.DoModal() returns IDOK.
	if( fileDlg.DoModal() == IDOK )
	{
		CString m_strPathname = fileDlg.GetPathName();
		NewDetectorsPath = m_strPathname;
		m_EditDetectorsPath.SetWindowText(NewDetectorsPath);
		//m_TextDetectorsPath.SetWindowText(NewDetectorsPath);	
	}

	// Display the Open dialog box.


/*
	CFile theFile;
	char* szFileName = "c:\\test\\myfile.dat";
	BOOL bOpenOK;

	CFileStatus status;
	if( CFile::GetStatus( szFileName, status ) )
	{
		// Открываем файл не создавая его
		bOpenOK = theFile.Open( szFileName, 
						CFile::modeWrite );
	}
	else
	{
		// Создаём файл и открываем его
		bOpenOK = theFile.Open( szFileName, 
						CFile::modeCreate | CFile::modeWrite );
	}
*/

/*
	OPENFILENAME ofn;       // структура станд. блока диалога
	char szFile[260];       // буфер для имени файла
	HWND hwnd;              // окно-владелец
	HANDLE hf;              // дескриптор файла


	// Инициализация структуры OPENFILENAME
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = (LPWSTR)*(szFile);
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = _T("All\0*.*\0Text\0*.TXT\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Показываем на экране диалоговое окно Открыть (Open).

	if (GetOpenFileName(&ofn)==TRUE) 
		hf = CreateFile(ofn.lpstrFile, GENERIC_READ,
			0, (LPSECURITY_ATTRIBUTES) NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
			(HANDLE) NULL);
*/

/*
    // open a file name
	ZeroMemory( &ofn , sizeof( ofn));
	ofn.lStructSize = sizeof ( ofn );
	ofn.hwndOwner = NULL  ;
	ofn.lpstrFile = szFile ;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof( szFile );
	ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
	ofn.nFilterIndex =1;
	ofn.lpstrFileTitle = NULL ;
	ofn.nMaxFileTitle = 0 ;
	ofn.lpstrInitialDir=NULL ;
	ofn.Flags = OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST ;
	GetOpenFileName( &ofn );
	
	// Now simpley display the file name 
	MessageBox ( NULL , ofn.lpstrFile , "File Name" , MB_OK);
*/

}


// Кнопка "Сохранить" / "Заменить"
void CDetectorsPath::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	CString EmptyStr("");
	CString StaticDetPath("");
	//CString BtnSaveApplyPathCaption("");
	//m_BtnSaveApplyPath.GetWindowText(BtnSaveApplyPathCaption);
	
	//if(BtnSaveApplyPathCaption == _T("Сохранить"))
	if(CurrentDetectorsPath == NewDetectorsPath)
	{
		theApp.CurDetectorsPath = NewDetectorsPath;

		CIniParam AppDetectorsPath(theApp.IniFileName, _T("Program"), _T("DetectorPath"), EmptyStr);	 // Датчики
		AppDetectorsPath.Set(NewDetectorsPath);
		AppDetectorsPath.Save();

		theApp.IniDetectorsPath = NewDetectorsPath;
	}
	else // BtnSaveApplyPathCaption == _T("Заменить")
	{
		//CStringA p_DetFullPath(DetectorsFullPath);
		CString DetectorsFullPath("");
		DetectorsFullPath = theApp.CurDetectorsPath;
		_bstr_t DetectorsFullPathBstr = DetectorsFullPath;

		//CStringA p_DetFullPath(DetectorsFullPath);

		_bstr_t bstrOutput("");
		bool validXml=false;
		HRESULT hr = CoInitialize(NULL);
		if(SUCCEEDED(hr))
		{
			try{ bstrOutput = theApp.validateDetFile(DetectorsFullPathBstr, validXml); }
			catch(_com_error &e)
			{bstrOutput = theApp.dump_com_error(e);}
		}

		if(validXml) // случай, когда Файл "Валидный" и датчики можно запросить
		{
			m_TextDetectorsPath.SetWindowText(NewDetectorsPath);
			theApp.CurDetectorsPath = NewDetectorsPath;

			CIniParam AppDetectorsPath(theApp.IniFileName, _T("Program"), _T("DetectorPath"), EmptyStr);	 // Датчики
			AppDetectorsPath.Set(NewDetectorsPath);
			AppDetectorsPath.Save();

			theApp.IniDetectorsPath = NewDetectorsPath;
			theApp.CurDetectorsPath = NewDetectorsPath;
			CurrentDetectorsPath = NewDetectorsPath;

			m_BtnSaveApplyPath.EnableWindow(FALSE);

			if(theApp.AllDetectors.size() == 0)
			{
				//readDetectorsFile(L"U4ASTOK.sou");
				readDetectorsFile(DetectorsFullPath);
			}

			GetParent()->PostMessage(WM_DET_PATH_OK,0,0);
		}
		else //if(!validXml)
		{
			if(bstrOutput.length()>0)
			MessageBox(bstrOutput, L"Ошибка в файле или его стрктуре", MB_OK);

			m_TextDetectorsPath.GetWindowText(StaticDetPath);
			m_EditDetectorsPath.SetWindowText(StaticDetPath);

			return;
		}
		CoUninitialize();

	}

	// ДОДЕЛАТЬ !!!
	// Необходим PostMessage от сюда в главное окно, чтобы перезапросился список Участков и XML-ный файл
	// Он необходим для того, чтобы поменять текст с Файл "Не задан" на "Установлен"

	//CDialog::OnOK();
}


void CDetectorsPath::readDetectorsFile(CString bstrXMLFile)
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

	TElem eroot(iRootElm);
	TElem subroot = eroot.subnode(L"Detector");
	wstring DetAtrs;
	std::vector<CString> TitleDetector;
	std::vector<CString> OneDetector;

	for(TElem e=eroot.begin(); e!=eroot.end(); e++)
	{
		DetAtrs = e.attr(L"detnum");
		OneDetector.push_back(DetAtrs.c_str());
		//AfxMessageBox(DetAtrs.c_str(), 0, 0);

		DetAtrs = e.attr(L"detname");
		OneDetector.push_back(DetAtrs.c_str());

		DetAtrs = e.attr(L"detptfix");
		OneDetector.push_back(DetAtrs.c_str());

		DetAtrs = e.attr(L"detdistance");
		OneDetector.push_back(DetAtrs.c_str());

		DetAtrs = e.attr(L"detfilepath");
		OneDetector.push_back(DetAtrs.c_str());

		DetAtrs = e.attr(L"detprodtype");
		OneDetector.push_back(DetAtrs.c_str());

		DetAtrs = e.attr(L"detprodid");
		OneDetector.push_back(DetAtrs.c_str());

	//detnum //detname //detptfix //detdistance //detfilepath //detprodtype //detprodid
		theApp.AllDetectors.push_back(OneDetector);
		OneDetector.clear();
	}

	// ОТСОРТИРУЕМ Список Датчиков по номерам:
	TitleDetector = theApp.AllDetectors[0]; // сохраняем первый элемент с "шапкой", чтобы она не мешалась при сортировке
	theApp.AllDetectors.erase(theApp.AllDetectors.begin()+0); // удалить из вектора первый элемент в котором шапка инфы о датчиках
	for (int i=0; i < theApp.AllDetectors.size(); i++) // i начинается с 1-цы, так как первая строчка это не датчик
	{
		// Массив просматривается с конца до позиции i и "легкие элементы всплывают"
		for (int j = theApp.AllDetectors.size()-1; j > i; j--)
		{
			// Если соседние элементы расположены в неправильном порядке, то меняем их местами
			if ( _tstol(theApp.AllDetectors[j][0]) < _tstol(theApp.AllDetectors[j-1][0]))
			{
				//std::swap(tesr[j], tesr[j-1]);
				OneDetector.clear();
				OneDetector = theApp.AllDetectors[j];
				theApp.AllDetectors.erase(theApp.AllDetectors.begin()+j); // удалить из вектора j-тый датчик (элемент)
				theApp.AllDetectors.insert(theApp.AllDetectors.begin()+(j-1), OneDetector); // добавить j-тый датчик на своё место
			}
		}
	}
	theApp.AllDetectors.insert(theApp.AllDetectors.begin(), TitleDetector); // добавляем шапку обратно в начало
	TitleDetector.clear();

	int u=0;
}


// Кнопка "Выход"
void CDetectorsPath::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialog::OnCancel();
}


// Событие "Изменения" или редактирования в Edit-боксе указанного пути
void CDetectorsPath::OnEnChangePathEdit()
{
	// TODO:  Добавьте код элемента управления

	//CString NewDetectorsPath("");
	m_EditDetectorsPath.GetWindowText(NewDetectorsPath);// Editbox
	//m_PrisList.GetLBText(curIndex, NewPris);			// Listbox
	//GetDlgItemText(IDD_DETECTORS_PATH_DLG, NewDetectorsPath);
	
	theApp.CurDetectorsPath = NewDetectorsPath;

	if(CurrentDetectorsPath == NewDetectorsPath)
	{
		//m_BtnSaveApplyPath.SetWindowText(_T("Сохранить"));
		m_BtnSaveApplyPath.EnableWindow(FALSE);
	}
	else
	{
		//m_BtnSaveApplyPath.SetWindowText(_T("Заменить"));
		m_BtnSaveApplyPath.EnableWindow(TRUE);
	}
}

/*
CString CDetectorsPath::DocErrorGetErrorInRus(CString DescriptionEng)
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