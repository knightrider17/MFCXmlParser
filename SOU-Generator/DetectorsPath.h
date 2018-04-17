#pragma once
#include "afxwin.h"


// диалоговое окно CDetectorsPath

class CDetectorsPath : public CDialog
{
	DECLARE_DYNAMIC(CDetectorsPath)

public:
	CDetectorsPath(CWnd* pParent = NULL);   // стандартный конструктор
	//CString DocErrorGetErrorInRus(CString DescriptionEng);
	virtual ~CDetectorsPath();

	void readDetectorsFile(CString bstrXMLFile);

// Данные диалогового окна
	enum { IDD = IDD_DETECTORS_PATH_DLG };

protected:
	CString CurrentDetectorsPath; // то, что пришло из ini-файла, и то, что в TextBox-e
	CString NewDetectorsPath;	  // меняющееся каждый раз значение в EditBox-e

	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	CEdit m_EditDetectorsPath;
	CStatic m_TextDetectorsPath;
	CButton m_BtnSaveApplyPath;
	CButton m_BtnSearchXML;

	afx_msg void OnBnClickedSearchPath();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangePathEdit();
};
