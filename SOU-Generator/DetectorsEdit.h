#pragma once
#include "afxwin.h"


// диалоговое окно CDetectorsEdit

class CDetectorsEdit : public CDialog
{
	DECLARE_DYNAMIC(CDetectorsEdit)

public:
	CDetectorsEdit(CWnd* pParent = NULL);   // стандартный конструктор
	virtual BOOL OnInitDialog();
	virtual ~CDetectorsEdit();

// ƒанные диалогового окна
	enum { IDD = IDD_EDIT_DETECTOR_DLG };

protected:
	bool PressEdit;
	bool TimeEdit;

	CString LintToCStr(long int x);
	CString DoubleToCStr(double x, int count); // x - число, count - число знаков после зап€той
	bool CheckString(CString& StrToCheck);

	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	BOOL PreTranslateMessage(LPMSG pMgs);

	DECLARE_MESSAGE_MAP()

public:
	//CComboBox m_CmBxDetNumber;
	CComboBox m_CmBxDetNum;
	CEdit m_EditDetNum;
	CEdit m_EditDetGrafName;
	CEdit m_EditDetActive;
	CEdit m_EditDetPath;
	CEdit m_EditDetPostFix;
	CEdit m_EditDetDist;
	CEdit m_EditDetDPress;
	CEdit m_EditDetDTime;

	CButton m_BtnDetOK;
	CButton m_BtnDetSave;
	CButton m_BtnDetExit;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	//afx_msg void OnCbnSelchangeDetNumCmbx();
	afx_msg void OnCbnSelchangeDetNameCmbx();
	afx_msg void OnEnChangeDetGrafNameEdit();
	afx_msg void OnEnChangeDetDpressEdit();
	afx_msg void OnEnChangeDetDtimeEdit();

	afx_msg LRESULT OnDivDetectorChange( WPARAM wparam , LPARAM lparam );
	afx_msg void OnEnSetfocusDetDpressEdit();
	afx_msg void OnEnKillfocusDetDpressEdit();
	afx_msg void OnEnSetfocusDetDtimeEdit();
	afx_msg void OnEnKillfocusDetDtimeEdit();
	afx_msg void OnBnClickedDetSaveBtn();
};
