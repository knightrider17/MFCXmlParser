#pragma once
#include "afxwin.h"
//#include "afxcmn.h"
#include <vector>

// Класс позволяющий сортировать элементы по нажатию на шапку колонки в ListCtrl
#include "SortListCtrl.h"


// диалоговое окно CDivisionChoose

class CDivisionChoose : public CDialog
{
	DECLARE_DYNAMIC(CDivisionChoose)

public:
	CString SelectedDivision;

	CDivisionChoose(CWnd* pParent = NULL);   // стандартный конструктор
	//CString DocErrorGetErrorInRus(CString DescriptionEng);
	virtual ~CDivisionChoose();

	void readDivisionHeadFile(CString bstrXMLFile);
	void readDivisionFile(CString bstrXMLFile);

	_bstr_t validateDivFileByDetKeyAndDetMaxNum(CString bstrXMLFile, bool &bValid);
	_bstr_t correctDivFileByDetParams(CString bstrXMLFile, CString XMLFileName, bool &bChanged);
	void writeCurDivisionFile(CString bstrXMLFile, std::vector<std::vector<CString>> CurDivision);

	bool CheckString(CString& StrToCheck);

	void LogBadFiles( CString& LogErrFiles, CString& LogErrPath, CString& MesErrFiles, bool bError);
	void LogChangedFiles( CString& LogFiles, CString& LogPath, CString& MesFiles);

// Данные диалогового окна
	enum { IDD = IDD_DIVISION_CHOOSE_DLG };

protected:
	CRect OriginalRect; // Исходный размер
	LONG OrigW, OrigH; // Размер окна Ширина и Высота

	bool bFirstDlg;

	//std::vector<std::vector<CString>> AllDivisions;
	CString LintToCStr(long int x);
	CString DoubleToCStr(double x, int count); // x - число, count - число знаков после запятой
	void DeleteLastSymbol(CString& Str);

	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	virtual BOOL OnInitDialog();
	BOOL PreTranslateMessage(LPMSG pMgs);
	bool FileExists(const wchar_t *fname);

	void HandleBtns();


	DECLARE_MESSAGE_MAP()

protected:
	long iCtrChoosenListItem;
	// DivisionFileName
	// theApp.AllDivisionsFileNames

public:
	CButton m_BtnOK; // блокируем

	CButton m_BtnDiv_Add;
	CButton m_BtnDiv_Del;
	CButton m_BtnDiv_Copy;
	CButton m_BtnDiv_Valid;
	CButton m_BtnDiv_Change;
	CButton m_BtnDiv_Look;
	CButton m_BtnDiv_Exit;

	//CListCtrl m_DivChangeList;
	CSortListCtrl m_DivChangeList;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedDivAddBtn();
	afx_msg void OnBnClickedDivDelBtn();
	afx_msg void OnBnClickedDivCopyBtn();
	afx_msg void OnBnClickedDivValidBtn();
	afx_msg void OnBnClickedDivEditBtn();
	afx_msg void OnBnClickedDivLookBtn();
	afx_msg void OnBnClickedCancel();

	afx_msg void OnLvnItemchangedDevChangeList(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg LRESULT OnDivisionEditSave( WPARAM wparam , LPARAM lparam );
	afx_msg LRESULT OnDivisionEditExit( WPARAM wparam , LPARAM lparam );
};
