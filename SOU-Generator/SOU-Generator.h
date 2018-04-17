
// SOU-Generator.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������
#include <vector>

#include <objsafe.h>
#include <objbase.h>
#include <atlbase.h>
#include <string>

#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#import <msxml6.dll>
#include <msxml6.h>

#include "stdio.h"


#include "TElem.h"


// CSOUGeneratorApp:
// � ���������� ������� ������ ��. SOU-Generator.cpp
//

class CSOUGeneratorApp : public CWinApp
{
public:
	CSOUGeneratorApp();


	CString GetErrorCSTRString(HRESULT hrErr);

	SYSTEMTIME m_CurTime;	//������� ��������� �����


	//MSXML2::IXMLDOMDocument2Ptr p_MAIN_XMLDoc;	


	enum DOMVer
	{
		XMLDOM,
		XMLDOM_0,
		XMLDOM_3,
		XMLDOM_4,
		XMLDOM_6
	} CurDomVer;

	_bstr_t validateDetFile(_bstr_t bstrXMLFile, bool &bValid);
	_bstr_t validateDivFile(_bstr_t bstrXMLFile, bool &bValid);
	//void dump_com_error(_com_error &e);
	CString dump_com_error(_com_error &e);


	int Version;			// SQL ��� XML ������ ���������
	enum ProgVer 
	{
		VER_SQL,
		VER_XML
	};

	int IniDBLoginTimeout;

	CString ConnectOrDB_Step;	// ����/��� �� ������� ��������� ������
	CString ConnectOrDB_Error;	// ������ ������������ � ���������� ���������� � ����� ������ / ���� ��� ���������� �������


	CString CurDivName;		// ��� �������
	CString CurDivPipe;		// ������������ �� ������� �����������
	CString CurDivProd;		// ������������ �� ������� �������
	CString CurDivParam;	// ������������ �� ������� ��������
	CString CurDivWatch;	// ������������ �� ������� �������
	CString CurDivWave;		// ������������ �� ������� �����
	CString CurDivTimedet;	// ������������ �� ������� �����_�����������
	enum DivBtn 
	{
		DIV_NOBTN,
		DIV_BTN_ADD,
		DIV_BTN_DEL,
		DIV_BTN_COPY,
		DIV_BTN_VALID,
		DIV_BTN_CHANGE,
		DIV_BTN_LOOK
	};

	CString CurDetNum;		// ����� ���������� ��� ���������/��������/��������� �������
	//CString CurDetName;	// ��������� ��� ���������/��������/��������� ������
	CString CurDetSysName;	// ��� ������� � ������� ���������� ��� ���������/��������/���������
	CString CurDetGrafName;	// ��� ������� �� �������, ������� ������� ��� ���������/��������/���������
	enum DetBtn 
	{
		DET_NOBTN,
		DET_BTN_ADD_ALL,
		DET_BTN_ADD,
		DET_BTN_CHANGE,
		DET_BTN_LOOK
	};

	DivBtn ChangeDivBtnClicked; // ��� �� ������ ������ � ���� "������ ��������"
	DetBtn EditDivDetBtnClicked; // ���� �� ������ ������ � ���� "�������� �������" ��� ���������� � ������ �������

	CString IniFileName; // ���� �� ini-�����, ���������� ��� ������ ����� � ���� ����
	CString IniFilePath; // ���� �� �����, � ������� ��������� ini-����

	CString IniDetectorsPath; // ���� � XML-����� �� ������� ��������, ���������� ��� ������ ����� � ���� ����, ������ �� ini-�����
	CString CurDetectorsPath;
	CString DetectorsFileName; // ��� XML-�����

	CString IniDivisionsPath; // ���� � ������ (*.sou) ��������, � ����� ���� �� ��������� ����������� "\�������", ������ �� ini-�����
	CString CurDivisionsPath;
	CString DivisionFileName; // ��� SOU-����� �������� ���������� ��� ���������/��������/��������� ����� ������� (.sou)
							  // ������� �� ��������� ��� ������� ���� "�������������� �������" � ������� ��� ���������� ���������

	std::vector<CString> AllDivisionsFileNames;
	long DivNextFileName;  // ����� ����� ��� ����� SOU-����� ��������� ��� ����������

	bool XMLDetectorsFound;	// ������ �� XML-���� � ��������� �� ���������� � ini-����� ����
	int MaxDetectors;		// ������������ ����� �������� �� ����� ������� (���� ������� ����, �� �� ����� ������������!)


	std::vector<std::vector<CString>> ErrDivisions; // ����� ��������, � ������� ���� ��������� ������ // �������� ��� ����� // �������� ������

	std::vector<std::vector<CString>> AllDetectors;
	//detnum //detname //detptfix //detdistance //detfilepath //detprodtype //detprodid

	std::vector<std::vector<CString>> AllDivisions;
	// ������ ��� �������� ���������� � ���� ���������� ������ �������� (��� �������� � ���), ������� �������� ����� �������

	std::vector<std::vector<CString>> FullDivision;
	// FullDivision[0] - 1-��� ������ �� ��������� ��������� ����� ��������� ��� ���������� � ��������� �������
	// FullDivision[1], ... , [n] - 2-�� � ��� ����������� ��������� ������� ����� ������� ������ �������� � �������

	// FullDivision[0] - 1-��� ������ �� ��������� ��������� ����� ��������� ��� ���������� � ��������� �������
	//divname //divprod //divparam //divwatch //divwave //divtimedet
	//���	//�������	//�������� //�������  //�����	// �����_�����������

	// FullDivision[1], ... , [n] - 2-�� � ��� ����������� ��������� ������� ����� ������� ������ �������� � �������
	//��� � �������:	//detnum //detname //detactive //detfilepath //detptfix //detdistance //detdpress //detdtime
	//��� � .sou �����:	//���	 //��	   //�������	//����		 //��������	//��������	  //������_��������	// ������_�����

	//<?xml version="1.0" encoding="windows-1251"?>
	//<�������_��� ���="������ ������ ���." �������="���.�������" ��������="��������" �������="0" �����="1.239" �����_�����������="10">
	//	<������ ���="�63 �����" ��="63" �������="1" ����="n:\Test\���-2" ��������="rnpz" ��������="171.1" ������_��������="0.010" ������_�����="3" />
	//	<������ ���="�66 ������" ��="66" �������="1" ����="n:\Test\���-2" ��������="zrnpz" ��������="0" ������_��������="0.010" ������_�����="2" />
	//</�������_���>

	std::vector<std::vector<CString>> DivDetectors; // ������� ���������� �� XML-�����, ������� �������� �������� �� ������� ����� ���������� �� ������� �������
	//long DIVDET_NUM; // ����� ��������, ������� �������� �������� �� ������� ����� ���������� �� ������ �������
	//detnum //detname //detptfix //detdistance //detfilepath //detprodtype //detprodid

	std::vector<std::vector<CString>> DivSortDetectors; // ������� ���������� �� XML-�����, ������� ������� �� �������� �� �������, � �� ���������� ��� ��������, ��� ��� ���� �� �������

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()

};

//////////////////////////////////////////////////////////////////
// �������� � ������ � �� �������:
// �: 14.11.2014 ������ ���������� ��������� � ������������� �������� XMLDomDocumetn 
// �: 18.11.2014 �� ������� ������: HRESULT hr = CoInitialize(NULL);

extern CSOUGeneratorApp theApp;

