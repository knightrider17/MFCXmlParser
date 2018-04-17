#pragma once
#include "afxwin.h"


// ���������� ���� CDetectorsPath

class CDetectorsPath : public CDialog
{
	DECLARE_DYNAMIC(CDetectorsPath)

public:
	CDetectorsPath(CWnd* pParent = NULL);   // ����������� �����������
	//CString DocErrorGetErrorInRus(CString DescriptionEng);
	virtual ~CDetectorsPath();

	void readDetectorsFile(CString bstrXMLFile);

// ������ ����������� ����
	enum { IDD = IDD_DETECTORS_PATH_DLG };

protected:
	CString CurrentDetectorsPath; // ��, ��� ������ �� ini-�����, � ��, ��� � TextBox-e
	CString NewDetectorsPath;	  // ���������� ������ ��� �������� � EditBox-e

	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV
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
