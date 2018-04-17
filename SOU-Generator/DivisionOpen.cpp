// DivisionOpen.cpp: файл реализации
//

#include "stdafx.h"
#include "SOU-Generator.h"
#include "SOU-GeneratorDlg.h"
#include "DivisionOpen.h"
#include "afxdialogex.h"

// диалоговое окно CDivisionOpen

IMPLEMENT_DYNAMIC(CDivisionOpen, CDialog)

CDivisionOpen::CDivisionOpen(CWnd* pParent /*=NULL*/)
	: CDialog(CDivisionOpen::IDD, pParent)
{

}

CDivisionOpen::~CDivisionOpen()
{
}

void CDivisionOpen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_DEV_OPEN_LIST, m_DivOpenList);
	DDX_Control(pDX, IDC_DEV_OPEN_LIST, m_DivOpenListCtrl);
	DDX_Control(pDX, IDOK, m_BtnDivOpen);
	DDX_Control(pDX, IDCANCEL, m_BtnDiv_Exit);
}


BEGIN_MESSAGE_MAP(CDivisionOpen, CDialog)
	ON_BN_CLICKED(IDOK, &CDivisionOpen::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDivisionOpen::OnBnClickedCancel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_DEV_OPEN_LIST, &CDivisionOpen::OnLvnItemchangedDevOpenList)
END_MESSAGE_MAP()


// обработчики сообщений CDivisionOpen

BOOL CDivisionOpen::OnInitDialog()
{
	CDialog::OnInitDialog();
	//m_BtnDivOpen.ShowWindow(FALSE);

//LVS_EX_FULLROWSELECT;
	/*
	CRect rect;
	m_DivOpenList.GetClientRect(rect);
	m_DivOpenList.InsertColumn(0, _T("Названия Участков"), LVCFMT_LEFT);//, rect.Width() - 230);

	CString cs(_T(""));
	for(int i = 0; i < 5; i++)
	{
		cs.Format(_T("Участок № %d"), i+1);
		m_DivOpenList.InsertItem(i, cs);
	}
	*/

	CString DivisionName(""); // Имя следующего Участка
	CString EmptyStr("");

	CRect rect;
	//m_DivOpenList.GetClientRect(rect);
	m_DivOpenListCtrl.GetClientRect(rect);

	// Заполняем список Названиями Участков используя названия файлов .sou из папки "Участки"
	if(theApp.CurDivisionsPath != EmptyStr)
	{
		CString sPath = theApp.CurDivisionsPath;
		CFileFind hFile;
		bool bFound = false;
		bFound = hFile.FindFile( sPath + _T("\\*.sou") );
		
		long LBiter=0;

		m_DivOpenListCtrl.InsertColumn(0, _T("Названия Участков"), LVCFMT_LEFT, 430);

		while ( bFound )
		{
			bFound = hFile.FindNextFile();
			//if( (! hFile.IsDots()) && ( hFile.IsDirectory() ) )		
			if( ! hFile.IsDots() )
			{
				DivisionName = hFile.GetFileName();

				CString szExt = _tcsrchr(DivisionName, '.'); // получаем szExt = ".sou"
				if(szExt == _T(".sou"))
				{
					// Удаляем последние 4 символа из конца каждого файла
					DivisionName.Delete(DivisionName.GetLength() - szExt.GetLength(), 4);
					// Добавляем только в том случае, если встретился .sou файл
					//m_DivOpenList.InsertItem(LBiter, DivisionName);
					m_DivOpenListCtrl.InsertItem(LBiter, DivisionName);
					LBiter++;

					// параллельно заполняем вектор из bool-ых элементов (false = флаг снят)
					AllDivisions.push_back(false);
				}
				//AfxMessageBox(DivisionName);

				// Сдесь и выдаются последовательно Пути к файлам сохраняющиеся в DivisionName


			}
		}
	}
	//m_DivOpenList.SetExtendedStyle(m_DivOpenList.GetExtendedStyle() | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT);
	//m_DivOpenListCtrl.SetExtendedStyle(m_DivOpenListCtrl.GetExtendedStyle() | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT);
	m_DivOpenListCtrl.SetExtendedStyle(m_DivOpenListCtrl.GetExtendedStyle() | LVS_EX_CHECKBOXES);
	m_DivOpenListCtrl.Init();

/*	CRect rect;
	m_DivOpenList.GetClientRect(rect);
	m_DivOpenList.InsertColumn(0, _T("No."), LVCFMT_LEFT, 30);
	//m_DivOpenList.InsertColumn(1, _T("Progress"), LVCFMT_LEFT, 150);
	//m_DivOpenList.InsertColumn(2, _T("Description"), LVCFMT_LEFT, rect.Width() - 230);
	m_DivOpenList.InsertColumn(1, _T("Названия Участков"), LVCFMT_LEFT, rect.Width() - 230);

	CString cs(_T(""));
	for(int i = 0; i < 5; i++)
	{
		cs.Format(_T("%d"), i+1);
		m_DivOpenList.InsertItem(i, cs);
		cs.Format(_T("Участок № %d"), i+1);
		m_DivOpenList.SetItemText(i, 1, cs);
	}

	m_DivOpenList.SetExtendedStyle(m_DivOpenList.GetExtendedStyle() | LVS_EX_CHECKBOXES);
	//m_DivOpenList.SetExtendedStyle(LVS_EX_CHECKBOXES);
	//m_DivOpenList.SetExtendedStyle(LVS_EX_TRACKSELECT);
	
	//m_DivOpenList.Init();
*/

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// кнопка "Открыть" в окне "ОТКРЫТЬ"
void CDivisionOpen::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	long i=0;
	CString EmptyStr("");

	// вектор для хранения нужных нам путей, которые пользователь выбрал для открытия Участков
	std::vector<CString> vSOUpathsToOpen;

	//long nCount=m_DivOpenList.GetItemCount();	// Число записей в Listbox
	long nCount=m_DivOpenListCtrl.GetItemCount();	// Число записей в Listbox

	// По кнопке "Открыть" для Участков, у которых мы взвели флажки в Списке с названиями Участков, получаем полные пути до файлов соответсвующих Участков
	for(i=0; i<AllDivisions.size(); i++)
	{
		if(AllDivisions[i]) // Если флаг установлен, то i будет указывать на этот элемент
		{
			// Далее если путь до папки не пустой продолжаем (стоит проверить наличие папки)
			if(theApp.CurDivisionsPath != EmptyStr)
			{
				CString sPath = theApp.CurDivisionsPath;
				CFileFind hFile;
				CString DivisionFullPath("");				// Полный путь к файлу следующего Участка
				//CString DivisionFullPathQuotes("");		// Полный путь к файлу следующего Участка с названием файла участка в кавычках

				//CString sDivName = m_DivOpenList.GetItemText( i , 0 );
				CString sDivName = m_DivOpenListCtrl.GetItemText( i , 0 );

			// Предварительно проверяем есть ли в имени фала пробелы
			// и если пробелы имеются, то обрамляем всё имя включая расширение кавычками: "Имя Участка.sou"
				bool WithQuotes=false;
				//for(long k=0; k < sDivName.GetLength(); k++)
				//{
				//	if(sDivName.Find(_T(" ")) != -1) // нашёлся пробел
				//		WithQuotes = true;
				//}

				DivisionFullPath = DivisionFullPath + sPath + _T("\\") + sDivName + _T(".sou");
				//DivisionFullPathQuotes = _T("\"")+DivisionFullPath+_T("\"");

				for(long k=0; k < DivisionFullPath.GetLength(); k++)
				{
					if(DivisionFullPath.Find(_T(" ")) != -1) // нашёлся пробел
						WithQuotes = true;
				}


				bool bFound = false;
				bFound = hFile.FindFile( DivisionFullPath );
				
				if(bFound)
				{	
					//if(WithQuotes)
					//{
						//AfxMessageBox(DivisionFullPathQuotes); // Полный путь содержится здесь
					//	vSOUpathsToOpen.push_back(DivisionFullPathQuotes);
					//}
					//else
					//{
						//AfxMessageBox(DivisionFullPath); // Полный путь содержится здесь
						vSOUpathsToOpen.push_back(DivisionFullPath);
					//}
				}
			}
		}
	}


	// 2.1) Получаем путь для сохранения Файла:
	TCHAR _FilesToOpenPathName[_MAX_PATH];
	::GetModuleFileName(AfxGetApp()->m_hInstance, _FilesToOpenPathName, MAX_PATH);
	TCHAR* szExtbsfto = _tcsrchr(_FilesToOpenPathName, '\\');
	if(szExtbsfto) *(szExtbsfto+1) = 0;
	//приставить конец пути, который должен заканчиваться папкой "Участки"
	_tcscat_s(_FilesToOpenPathName, _MAX_PATH, _T("SOU-Generator.sou"));

	CString FilesToOpenPathName("");			// Полный путь к файлу с путями Участков для открытия в основной программе ГрафСОУ
	CString FilesToOpenPathNameQuotes("");		// Полный путь к файлу с путями Участков для открытия в основной программе ГрафСОУ в кавычках
	FilesToOpenPathName = _FilesToOpenPathName;
	FilesToOpenPathNameQuotes = _T("\"")+FilesToOpenPathNameQuotes+_T("\"");

	CStringA FilesToOpenPathNameA(FilesToOpenPathName);

	// 2.2) Формируем новый файл .SOU - SOUFilesToOpen.sou
	// Структура такова: 
	//	корневой тэг: <Участки_СОУ>
	//		дочерние тэги: <Участок путь="полный_путь.sou"/Участок>
	//				  </Участки_СОУ>

/////////////////////////////////////////////////////////////////////////////////
/////  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  /////
/*	TiXmlDocument doc;
	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "windows-1251", "" );
	doc.LinkEndChild( decl );

	TiXmlElement* element = new TiXmlElement( "Участки_СОУ" );
	TiXmlText* text = new TiXmlText("");

	//element->SetAttribute(,);

	doc.LinkEndChild( element );
	element->LinkEndChild( text );

	if(vSOUpathsToOpen.size()>0)
	{
		for(long i=0; i<vSOUpathsToOpen.size(); i++)
		{
			TiXmlElement* element2 = new TiXmlElement( "Участок" );
			TiXmlText* text2 = new TiXmlText( "" );
			CStringA SOUPath(vSOUpathsToOpen[i]);
			element2->SetAttribute("путь",SOUPath);

			element->LinkEndChild( element2 );
			element2->LinkEndChild( text2 );
		}

		// Наконец сохраняем .sou файл, содержащий все пути
		doc.SaveFile( FilesToOpenPathNameA );
	}
*/

	// Предварительно проверяем есть ли в имени фала пробелы
	// и если пробелы имеются, то обрамляем всё имя включая расширение кавычками: "Имя Участка.sou"
	bool WithQuotes=false;
	for(long k=0; k < FilesToOpenPathName.GetLength(); k++)
	{
		if(FilesToOpenPathName.Find(_T(" ")) != -1) // нашёлся пробел
		WithQuotes = true;
	}

	CFileFind hFile;
	bool bFound = false;
	bFound = hFile.FindFile( FilesToOpenPathName );
				
	if(bFound)
	{	

		// 3) Осталось запустить программу:	
		SHELLEXECUTEINFO lpExecInfo;
		lpExecInfo.cbSize  = sizeof(SHELLEXECUTEINFO);
		lpExecInfo.lpFile = L"GraphSOU.exe";
		lpExecInfo.fMask = SEE_MASK_DOENVSUBST|SEE_MASK_NOCLOSEPROCESS;
		lpExecInfo.hwnd = NULL;  
		lpExecInfo.lpVerb = L"open";
		//lpExecInfo.lpParameters = L"-cf test.xml";


		if(WithQuotes)
		{lpExecInfo.lpParameters = FilesToOpenPathNameQuotes;}
		else
		{lpExecInfo.lpParameters = FilesToOpenPathName;}

		lpExecInfo.lpDirectory = NULL;
		//lpExecInfo.nShow = SW_HIDE; // hide shell during execution
		lpExecInfo.nShow = SW_SHOW; // show shell during execution
		lpExecInfo.hInstApp = (HINSTANCE) SE_ERR_DDEFAIL;
		ShellExecuteEx(&lpExecInfo);

		// wait until the process is finished
		if (lpExecInfo.hProcess != NULL)
		{
			::WaitForSingleObject(lpExecInfo.hProcess, INFINITE);
			::CloseHandle(lpExecInfo.hProcess);
			AfxMessageBox( _T("Process finished") );
		}

	}

	// ПОСЛЕДГНИЙ ВОПРОС ЧТО ДЕЛАТЬ, КОГДА ПРОЦЕДУРА ОТРАБОТАЛА !!!!!
	// СНИМАТЬ ЛИ ВСЕ УТСНОВЛЕННЫЕ ФЛАЖКИ ИЛИ ЗАКРЫВАТЬ ДАННОЕ ОКНО !!!!!

	//CDialog::OnOK(); // Есил оставить эту строчку, то нужно не забыть добавть Postmessage (для разблокироки кнопок основного окна)
}

// Кнопка "Выход"   из окна "ОТКРЫТЬ"
void CDivisionOpen::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений
	//HWND HwndSOUDlg=NULL;
	//::GetDlgItem(HwndSOUDlg, IDD_SOUGENERATOR_DIALOG);
	//::PostMessage(HwndSOUDlg, WM_DIVISION_OPEN_EXIT,0,0);
	AfxGetMainWnd()->PostMessage(WM_DIVISION_OPEN_EXIT, 0, 0);

	CDialog::OnCancel();
}


// http://forums.codeguru.com/showthread.php?475929-MFC-ListView-Control-How-CListCtrl-notifies-quot-checkbox-status-changed-quot
// How CListCtrl notifies "checkbox status changed" ?
// The "magic" constants are replaced with LVIS_STATEIMAGEMASK and
// INDEXTOSTATEIMAGEMASK macros defined in commctrl.h.
// Credits: VictorN
void CDivisionOpen::OnLvnItemchangedDevOpenList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: добавьте свой код обработчика уведомлений
    if(pNMLV->uChanged & LVIF_STATE) // item state has been changed
    {
        switch(pNMLV->uNewState & LVIS_STATEIMAGEMASK)
        {
        case INDEXTOSTATEIMAGEMASK(BST_CHECKED + 1): // new state: checked
            TRACE1("\n Item %d has been checked", pNMLV->iItem);
			AllDivisions[pNMLV->iItem] = true;
            break;
        case INDEXTOSTATEIMAGEMASK(BST_UNCHECKED + 1): // new state: unchecked
            TRACE1("\n Item %d has been unchecked", pNMLV->iItem);
			AllDivisions[pNMLV->iItem] = false;
            break; 
        }
    }

	*pResult = 0;
}
