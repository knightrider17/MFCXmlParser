#pragma once
#include "afxwin.h"
//#include "afxcmn.h"

#include "DetectorsEdit.h"

#include "SortListCtrl.h"
#include "TooltipComboBox.h"
//#include "TooltipListCtrl.h"

// диалоговое окно CDivisionEdit

class CDivisionEdit : public CDialog
{
	DECLARE_DYNAMIC(CDivisionEdit)

public:
	HWND DetectorDlgHWND;

	CRect OriginalRect; // Исходный размер
	LONG OrigW, OrigH; // Размер окна Ширина и Высота
	CString sOriginalDivName; // Имя участка, которое было при заходе в файл с участком

	CDivisionEdit(CWnd* pParent = NULL);   // стандартный конструктор
	//CString DocErrorGetErrorInRus(CString DescriptionEng);
	virtual BOOL OnInitDialog();
	virtual ~CDivisionEdit();
	
	void readDivisionFile(CString bstrXMLFile);
	void writeDivisionFile(CString bstrXMLFile);

// Данные диалогового окна
	enum { IDD = IDD_EDIT_DIVISION_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	BOOL PreTranslateMessage(LPMSG pMgs);

	CString LintToCStr(long int x);
	CString DoubleToCStr(double x, int count); // x - число, count - число знаков после запятой
	bool CheckString(CString& StrToCheck); // проверка название файла 
	bool CheckFileNameCopyString(CString& StrToCheck, long Next);

	bool WaveEdit;
	bool TimeDetEdit;
	bool FirstNameEdit;
	bool FirstFileNameEdit;

	//bool FirstNameSFocus;
	//bool FirstNameKFocus;
	//bool FirstFileNameSFocus;
	//bool FirstFileNameKFocus;

	bool bFirstDlg;
	bool FileExists(const wchar_t *fname);
	void ChecckForBtnSave();

	void SetPipesToCmBx();
	void SetProdsToCmBx();

	DECLARE_MESSAGE_MAP()

public:
	CEdit m_EditDivName;
	CEdit m_EditDivFileName;
	//CComboBox m_CmBxDivPipe;
	CTooltipComboBox m_CmBxDivPipe;
	CComboBox m_CmBxDivProd;
//	CEdit m_EditDivParam;
//	CEdit m_EditDivWatch; //
//	CComboBox m_CmBxDivWatch;
	CEdit m_EditDivPipeLenght;
	CEdit m_EditDivBeginName;
	CEdit m_EditDivEndName;
	CEdit m_EditDivWave;
	CEdit m_EditDivTimeDetect;

	CStatic m_StaticDiv_Det;
	//CListCtrl m_ListDiv_Det;
	CSortListCtrl m_ListDiv_Det;
	CButton m_BtnDiv_DetAddAll;
	CButton m_BtnDiv_DetAdd;
	CButton m_BtnDiv_DetDel;
	CButton m_BtnDiv_DetChange;
	CButton m_BtnDiv_DetLook;

	CButton m_BtnDivOK;
	CButton m_BtnDivSave;
	CButton m_BtnDivExit;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeDivNameEdit();
	afx_msg void OnCbnSelchangeDivPipeCmbx();
	afx_msg void OnCbnSelchangeDivProdCmbx();
	afx_msg void OnEnChangeDivParamEdit();
	afx_msg void OnEnChangeDivPipeLenghtEdit();
	afx_msg void OnEnChangeDivBeginNameEdit();
	afx_msg void OnEnChangeDivEndNameEdit();
	//afx_msg void OnEnChangeDivWatchEdit();
	afx_msg void OnCbnSelchangeDivWatchCmbx();
	afx_msg void OnEnChangeDivWaveEdit();
	afx_msg void OnEnChangeDivTimedetectEdit();

	afx_msg void OnLvnItemchangedDivDetectorsList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedDivDetAddAllBtn();
	afx_msg void OnBnClickedDivDetAddBtn();
	afx_msg void OnBnClickedDivDetDellBtn();
	afx_msg void OnBnClickedDivDetChangeBtn();
	afx_msg void OnBnClickedDivDetLookBtn();

	afx_msg LRESULT OnDetectorEditSave( WPARAM wparam , LPARAM lparam );
	afx_msg LRESULT OnDetectorEditExit( WPARAM wparam , LPARAM lparam );
	afx_msg void OnEnChangeDivFileNameEdit();
	afx_msg void OnEnSetfocusDivNameEdit();
	afx_msg void OnEnKillfocusDivNameEdit();
	afx_msg void OnEnSetfocusDivFileNameEdit();
	afx_msg void OnEnKillfocusDivFileNameEdit();
	afx_msg void OnBnClickedDivSaveBtn();

	afx_msg void OnSize(UINT nType, int cx, int cy);
};
