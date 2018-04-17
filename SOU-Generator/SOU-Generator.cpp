
// SOU-Generator.cpp : ���������� ��������� ������� ��� ����������.
//

#include "stdafx.h"
#include "SOU-Generator.h"
#include "SOU-GeneratorDlg.h"


//#include "TElem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSOUGeneratorApp

BEGIN_MESSAGE_MAP(CSOUGeneratorApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// �������� CSOUGeneratorApp

CSOUGeneratorApp::CSOUGeneratorApp()
{
	// ��������� ���������� ������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �������� ��� ��������,
	// ��������� ���� ������ ��� ������������� � InitInstance
}


// ������������ ������ CSOUGeneratorApp

CSOUGeneratorApp theApp;


// ������������� CSOUGeneratorApp

BOOL CSOUGeneratorApp::InitInstance()
{

	//double aDoubles[100] = {-DBL_MAX};

	// InitCommonControlsEx() ��������� ��� Windows XP, ���� ��������
	// ���������� ���������� ComCtl32.dll ������ 6 ��� ����� ������� ������ ��� ���������
	// ������ �����������. � ��������� ������ ����� ��������� ���� ��� �������� ������ ����.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// �������� ���� �������� ��� ��������� ���� ����� ������� ����������, ������� ���������� ������������
	// � ����� ����������.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ������� ��������� ��������, � ������, ���� ���������� ���� ��������
	// ������������� ������ �������� ��� �����-���� ��� �������� ����������.
	CShellManager *pShellManager = new CShellManager;

	// ����������� �������������
	// ���� ��� ����������� �� ������������ � ���������� ��������� ������
	// ��������� ������������ �����, ���������� ������� �� ���������
	// ���������� �������� �������������, ������� �� ���������
	// �������� ������ �������, � ������� �������� ���������
	// TODO: ������� �������� ��� ������ �� ���-������ ����������,
	// �������� �� �������� �����������
	SetRegistryKey(_T("��������� ����������, ��������� � ������� ������� ����������"));

	CSOUGeneratorDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ������� ��� ��� ��������� �������� ����������� ����
		//  � ������� ������ "��"
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ������� ��� ��� ��������� �������� ����������� ����
		//  � ������� ������ "������"
	}

	// ������� ��������� ��������, ��������� ����.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ��������� ���������� ���� �������, ���������� �������� FALSE, ����� ����� ���� ����� ��
	//  ���������� ������ ������� ���������� ��������� ����������.
	return FALSE;
}


//void CSOUGeneratorApp::dump_com_error(_com_error &e)
CString CSOUGeneratorApp::dump_com_error(_com_error &e)
{
    _bstr_t bstrSource(e.Source());
    _bstr_t bstrDescription(e.Description());
/*
    printf("Error\n");
    printf("\a\tCode = %08lx\n", e.Error());
    printf("\a\tCode meaning = %s", e.ErrorMessage());
    printf("\a\tSource = %s\n", (LPCSTR) bstrSource);
    printf("\a\tDescription = %s\n", (LPCSTR) bstrDescription);
//*/

	CString strError;
    //strError += _T("Error\n");
    strError.Format(_T("��� ������ = %08lx"), e.Error());
    strError += _T("\n������� ������ = ");
    strError += (BSTR)e.ErrorMessage();
    strError += _T("\n�������� = ");
    strError += (BSTR)bstrSource;
    strError += _T("\n�������� = ");
    strError += (BSTR)bstrDescription;

	//AfxMessageBox(strError);
	return strError;

	//system("pause");
}


_bstr_t CSOUGeneratorApp::validateDetFile(_bstr_t bstrXMLFile, bool &bValid)
{
	HRESULT hr = NULL;

	// Initialize objects and variables.
	//*
	// 2 // http://stackoverflow.com/questions/1048764/validate-xml-schema-using-msxml-parser
	MSXML2::IXMLDOMSchemaCollectionPtr	pXS;
	MSXML2::IXMLDOMDocument2Ptr			pXD = NULL;
	//MSXML2::IXMLDOMParseErrorPtr		pError;
	MSXML2::IXMLDOMParseErrorPtr		pErr = NULL;
	_bstr_t								bstrResult = "";

	hr = pXS.CreateInstance(__uuidof(XMLSchemaCache60));
	//hr = pXS->add("urn:namespace", "myschema.xsd");
	//hr = pXS->add("urn:book", "sl.xsd");

	CString Schema_CStr("");
	Schema_CStr += _T("<?xml version=\"1.0\" encoding=\"windows-1251\"?>");
	Schema_CStr += _T("\n<xs:schema xmlns:xs=\"http://www.w3.org/2001/XMLSchema\" elementFormDefault=\"qualified\">");
	Schema_CStr += _T("\n\t<xs:element name=\"DetectorsList\">");
	Schema_CStr += _T("\n\t\t<xs:complexType>");
	Schema_CStr += _T("\n\t\t\t<xs:sequence>");
	Schema_CStr += _T("\n\t\t\t\t<xs:element minOccurs=\"1\" maxOccurs=\"1\" ref=\"Title\"/>");
	Schema_CStr += _T("\n\t\t\t\t<xs:element minOccurs=\"60\" maxOccurs=\"unbounded\" ref=\"Detector\"/>");
	Schema_CStr += _T("\n\t\t\t</xs:sequence>");
//	Schema_CStr += _T("\n\t\t\t<xs:attribute name=\"Name\" use=\"required\"/>");
	Schema_CStr += _T("\n\t\t</xs:complexType>");
	Schema_CStr += _T("\n\t</xs:element>");
	Schema_CStr += _T("\n\t<xs:element name=\"Title\">");
	Schema_CStr += _T("\n\t\t<xs:complexType>");
	Schema_CStr += _T("\n\t\t\t<xs:attribute name=\"detnum\"		  use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xs:attribute name=\"detname\"		  use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xs:attribute name=\"detptfix\"		  use=\"required\" type=\"xs:NCName\"/> ");
	Schema_CStr += _T("\n\t\t\t<xs:attribute name=\"detdistance\"	  use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xs:attribute name=\"detfilepath\"	  use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xs:attribute name=\"detprodtype\"	  use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xs:attribute name=\"detprodid\"		  use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xs:attribute name=\"detprodview\"	  use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xs:attribute name=\"detwavespeed\"	  use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xs:attribute name=\"detpipeid\"		  use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xs:attribute name=\"detpipeshrtname\" use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xs:attribute name=\"detpipelenght\"	  use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xs:attribute name=\"detbeginname\"	  use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xs:attribute name=\"detendname\"	  use=\"required\"/>");
	Schema_CStr += _T("\n\t\t</xs:complexType>");
	Schema_CStr += _T("\n\t</xs:element>");
	Schema_CStr += _T("\n\t<xs:element name=\"Detector\">");
	Schema_CStr += _T("\n\t\t<xs:complexType>");
	Schema_CStr += _T("\n\t\t\t<xs:attribute name=\"detnum\"		  use=\"required\" type=\"xs:integer\"/>");
	Schema_CStr += _T("\n\t\t\t<xs:attribute name=\"detname\"		  use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xs:attribute name=\"detptfix\"		  use=\"required\" type=\"xs:NMTOKEN\"/>");
	Schema_CStr += _T("\n\t\t\t<xs:attribute name=\"detdistance\"	  use=\"required\" type=\"xs:decimal\"/>");
	Schema_CStr += _T("\n\t\t\t<xs:attribute name=\"detfilepath\"	  use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xs:attribute name=\"detprodtype\"	  use=\"required\" type=\"xs:NCName\"/>");
	Schema_CStr += _T("\n\t\t\t<xs:attribute name=\"detprodid\"		  use=\"required\" type=\"xs:NCName\"/>");
	Schema_CStr += _T("\n\t\t\t<xs:attribute name=\"detprodview\"	  use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xs:attribute name=\"detwavespeed\"	  use=\"required\" type=\"xs:decimal\"/>");
	Schema_CStr += _T("\n\t\t\t<xs:attribute name=\"detpipeid\"		  use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xs:attribute name=\"detpipeshrtname\" use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xs:attribute name=\"detpipelenght\"	  use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xs:attribute name=\"detbeginname\"	  use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xs:attribute name=\"detendname\"	  use=\"required\"/>");
	Schema_CStr += _T("\n\t\t</xs:complexType>");
	Schema_CStr += _T("\n\t</xs:element>");
	Schema_CStr += _T("\n</xs:schema>");


/*
<?xml version="1.0" encoding="windows-1251"?>
<xs:schema xmlns:xs="http://www.w3.org/2001/XMLSchema" elementFormDefault="qualified">
	<xs:element name="DetectorsList">
		<xs:complexType>
			<xs:sequence>
				<xs:element minOccurs="1" maxOccurs="1" ref="Title"/>
				<xs:element minOccurs="60" maxOccurs="unbounded" ref="Detector"/>
			</xs:sequence>
//			<xs:attribute name="Name" use="required"/>
		</xs:complexType>
	</xs:element>
	<xs:element name="Title">
		<xs:complexType>
			<xs:attribute name="detdistance" use="required"/>
			<xs:attribute name="detfilepath" use="required"/>
			<xs:attribute name="detname" use="required"/>
			<xs:attribute name="detnum" use="required"/>
			<xs:attribute name="detprodid" use="required"/>
			<xs:attribute name="detprodtype" use="required"/>
            <xs:attribute name="detwavespeed" use="required" />
			<xs:attribute name="detptfix" use="required" type="xs:NCName"/>
		</xs:complexType>
	</xs:element>
	<xs:element name="Detector">
		<xs:complexType>
			<xs:attribute name="detdistance" use="required" type="xs:decimal"/>
			<xs:attribute name="detfilepath" use="required"/>
			<xs:attribute name="detname" use="required"/>
			<xs:attribute name="detnum" use="required" type="xs:integer"/>
			<xs:attribute name="detprodid" use="required" type="xs:NCName"/>
			<xs:attribute name="detprodtype" use="required" type="xs:NCName"/>
            <xs:attribute name="detwavespeed" use="required" type="xs:decimal"/>
			<xs:attribute name="detptfix" use="required" type="xs:NMTOKEN"/>
		</xs:complexType>
	</xs:element>
</xs:schema>
*/


/*
	CString Schema_CStr("");
	Schema_CStr += _T("<?xml version=\"1.0\" encoding=\"windows-1251\"?>");
	Schema_CStr += _T("\n<xs:schema attributeFormDefault=\"unqualified\" elementFormDefault=\"qualified\" xmlns:xs=\"http://www.w3.org/2001/XMLSchema\">");
	Schema_CStr += _T("\n\t<xs:element name=\"DetectorsList\">");
	Schema_CStr += _T("\n\t\t<xs:complexType>");
	Schema_CStr += _T("\n\t\t\t<xs:sequence>");
	Schema_CStr += _T("\n\t\t\t\t<xs:element maxOccurs=\"unbounded\" name=\"Detector\">");
	Schema_CStr += _T("\n\t\t\t\t\t<xs:complexType>");
	Schema_CStr += _T("\n\t\t\t\t\t\t<xs:attribute name=\"detnum\" type=\"xs:string\" use=\"required\" />");
	Schema_CStr += _T("\n\t\t\t\t\t\t<xs:attribute name=\"detname\" type=\"xs:string\" use=\"required\" />");
	Schema_CStr += _T("\n\t\t\t\t\t\t<xs:attribute name=\"detptfix\" type=\"xs:string\" use=\"required\" />");
	Schema_CStr += _T("\n\t\t\t\t\t\t<xs:attribute name=\"detdistance\" type=\"xs:string\" use=\"required\" />");
	Schema_CStr += _T("\n\t\t\t\t\t\t<xs:attribute name=\"detfilepath\" type=\"xs:string\" use=\"required\" />");
	Schema_CStr += _T("\n\t\t\t\t\t\t<xs:attribute name=\"detprodtype\" type=\"xs:string\" use=\"required\" />");
	Schema_CStr += _T("\n\t\t\t\t\t\t<xs:attribute name=\"detprodid\" type=\"xs:string\" use=\"required\" />");
	Schema_CStr += _T("\n\t\t\t\t\t\t</xs:complexType>");
	Schema_CStr += _T("\n\t\t\t\t\t</xs:element>");
	Schema_CStr += _T("\n\t\t\t\t</xs:sequence>");
	Schema_CStr += _T("\n\t\t\t<xs:attribute name=\"Name\" type=\"xs:string\" use=\"required\" />");
	Schema_CStr += _T("\n\t\t</xs:complexType>");
	Schema_CStr += _T("\n\t</xs:element>");
	Schema_CStr += _T("\n</xs:schema>");
//*/
/*
<?xml version="1.0" encoding="windows-1251"?>
<xs:schema attributeFormDefault="unqualified" elementFormDefault="qualified" xmlns:xs="http://www.w3.org/2001/XMLSchema">
  <xs:element name="DetectorsList">
    <xs:complexType>
      <xs:sequence>
        <xs:element maxOccurs="unbounded" name="Detector">
          <xs:complexType>
            <xs:attribute name="detnum" type="xs:string" use="required" />
            <xs:attribute name="detname" type="xs:string" use="required" />
            <xs:attribute name="detptfix" type="xs:string" use="required" />
            <xs:attribute name="detdistance" type="xs:string" use="required" />
            <xs:attribute name="detfilepath" type="xs:string" use="required" />
            <xs:attribute name="detprodtype" type="xs:string" use="required" />
            <xs:attribute name="detprodid" type="xs:string" use="required" />
          </xs:complexType>
        </xs:element>
      </xs:sequence>
      <xs:attribute name="Name" type="xs:string" use="required" />
    </xs:complexType>
  </xs:element>
</xs:schema>
//*/

	CString EmptyCStr("");
	TCHAR XSDFile[_MAX_PATH];
	::GetModuleFileName(AfxGetApp()->m_hInstance, XSDFile, MAX_PATH);
	TCHAR* szExt = _tcsrchr(XSDFile, '\\');
	if(szExt) *(szExt+1) = 0;
	//���������
	_tcscat_s(XSDFile, _MAX_PATH, _T("TmpDetectorsFileWithSchemaForSouGenerator.xsd"));
	
	CFile CfileObjWrite(XSDFile, CFile::modeCreate|CFile:: modeReadWrite);
	CStringA Schema_CStrA(Schema_CStr);
	CfileObjWrite.Write( Schema_CStrA, Schema_CStrA.GetLength());
	CfileObjWrite.Close();

	_bstr_t Schema_bstr_t(_T(""));
	Schema_bstr_t = XSDFile;

	_bstr_t bstrSchemNameSpaceFile(_T(""));

	////hr = pXS->add(bstrSchemNameSpaceFile, bstrSchemFile);
	hr = pXS->add(bstrSchemNameSpaceFile, Schema_bstr_t);

	// Create a DOMDocument and set its properties.
	hr = pXD.CreateInstance(__uuidof(DOMDocument60));

	// Assign the schema cache to the DOMDocument's
	// schemas collection.
	pXD->schemas = pXS.GetInterfacePtr();

	// Load books.xml as the DOM document.
	pXD->async = VARIANT_FALSE;
	pXD->validateOnParse = VARIANT_TRUE;
	pXD->resolveExternals = VARIANT_TRUE;
	//hr = pXD->load("sl-notValid.xml");

	// 1) ��������� �����:
	if(XSDFile != EmptyCStr)
	{
		CFileFind hFile;
		bool bFound = false;
		bFound = hFile.FindFile( XSDFile );
			
		if(bFound)	{CFile::Remove(XSDFile);} // ������ ���� ���������� �����
	}

	//delete[] XSDFile;
	//free(XSDFile);
	//free(szExt);

	// check hr and pXD->errorCode here
    if(pXD->load(bstrXMLFile) != VARIANT_TRUE)
    {
        pErr = pXD->parseError;

		// ��������� ����� �� ������������� ����������� ���.
        bstrResult = _bstr_t(L"������: ��������� ����� ") +
			_T("\"")+ bstrXMLFile +_T("\"") + _T("\n") +
			_T("�� ������������� ����������� ���.") +
            _bstr_t(L"\n==========================================") +
            _bstr_t(L"\n�������: ") + _bstr_t(pErr->Getline()) +
            _bstr_t(L"\n�������: ") + _bstr_t(pErr->GetsrcText()) +
            _bstr_t(L"\n�������: ") + _bstr_t(pErr->Getreason());// +
//            _bstr_t(L"\n");

		//AfxMessageBox( bstrResult );
		bValid=false;
		return bstrResult;
    }
    else
    {
		bstrResult = _bstr_t(L"��������� ����� ") +
			_T("\"")+ bstrXMLFile +_T("\"") +
			_T(" ������������� ����������� ���.");// +
			//_bstr_t(L"\n===========================================\n") +
            //_bstr_t(pXD->xml) + _bstr_t(L"\n");

		//AfxMessageBox( bstrResult );
		bValid=true;
		return bstrResult;
	}
}


_bstr_t CSOUGeneratorApp::validateDivFile(_bstr_t bstrXMLFile, bool &bValid)
{
	HRESULT hr = NULL;

	// Initialize objects and variables.
	//*
	// 2 // http://stackoverflow.com/questions/1048764/validate-xml-schema-using-msxml-parser
	MSXML2::IXMLDOMSchemaCollectionPtr	pXS;
	MSXML2::IXMLDOMDocument2Ptr			pXD = NULL;
	//MSXML2::IXMLDOMParseErrorPtr		pError;
	MSXML2::IXMLDOMParseErrorPtr		pErr = NULL;
	_bstr_t								bstrResult = "";

	hr = pXS.CreateInstance(__uuidof(XMLSchemaCache60));
	//hr = pXS->add("urn:namespace", "myschema.xsd");
	//hr = pXS->add("urn:book", "sl.xsd");

	CString Schema_CStr("");
	Schema_CStr += _T("<?xml version=\"1.0\" encoding=\"windows-1251\"?>");
	Schema_CStr += _T("\n<xsd:schema xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" elementFormDefault=\"qualified\">");
	Schema_CStr += _T("\n\t<xsd:element name=\"�������_���\">");
	Schema_CStr += _T("\n\t\t<xsd:complexType>");
	Schema_CStr += _T("\n\t\t\t<xsd:sequence>");
	Schema_CStr += _T("\n\t\t\t\t<xsd:element ref=\"������\" minOccurs=\"1\" maxOccurs=\"unbounded\"/>");
	Schema_CStr += _T("\n\t\t\t</xsd:sequence>");
	Schema_CStr += _T("\n\t\t\t<xsd:attribute name=\"���\"				 type=\"xsd:string\" use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xsd:attribute name=\"�����\"			 type=\"xsd:string\" use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xsd:attribute name=\"�����_���\"		 type=\"xsd:string\" use=\"required\"/>");
//	Schema_CStr += _T("\n\t\t\t<xsd:attribute name=\"�������\"			 type=\"enumSensor\" use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xsd:attribute name=\"�������\"			 type=\"xsd:string\" use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xsd:attribute name=\"�������_���\"		 type=\"xsd:string\" use=\"required\"/>");
//	Schema_CStr += _T("\n\t\t\t<xsd:attribute name=\"��������\"			 type=\"enumParam\" use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xsd:attribute name=\"��������\"			 type=\"xsd:string\" use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xsd:attribute name=\"�������\"			 type=\"xsd:string\" use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xsd:attribute name=\"�����\"			 type=\"xsd:string\" use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xsd:attribute name=\"�����_�����������\" type=\"xsd:string\" use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xsd:attribute name=\"�����_�����\"		 type=\"xsd:string\" use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xsd:attribute name=\"���_������\"		 type=\"xsd:string\" use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xsd:attribute name=\"���_�����\"		 type=\"xsd:string\" use=\"required\"/>");
	Schema_CStr += _T("\n\t\t</xsd:complexType>");
	Schema_CStr += _T("\n\t</xsd:element>");
	Schema_CStr += _T("\n\t<xsd:element name=\"������\">");
	Schema_CStr += _T("\n\t\t<xsd:complexType>");
	Schema_CStr += _T("\n\t\t\t<xsd:attribute name=\"���\"				 type=\"xsd:string\" use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xsd:attribute name=\"��\"				 type=\"xsd:string\" use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xsd:attribute name=\"�������\"			 type=\"xsd:string\" use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xsd:attribute name=\"����\"				 type=\"xsd:string\" use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xsd:attribute name=\"��������\"			 type=\"xsd:string\" use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xsd:attribute name=\"��������\"			 type=\"xsd:string\" use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xsd:attribute name=\"������_��������\"	 type=\"xsd:string\" use=\"required\"/>");
	Schema_CStr += _T("\n\t\t\t<xsd:attribute name=\"������_�����\"		 type=\"xsd:string\" use=\"required\"/>");
//	Schema_CStr += _T("\n\t\t\t<xsd:attribute name=\"����������_������\" type=\"xsd:string\" use=\"required\"/>");
//	Schema_CStr += _T("\n\t\t\t<xsd:attribute name=\"����������_�����\"	 type=\"xsd:string\" use=\"required\"/>");
	Schema_CStr += _T("\n\t\t</xsd:complexType>");
	Schema_CStr += _T("\n\t</xsd:element>");
//	Schema_CStr += _T("\n\t<xsd:simpleType name=\"enumSensor\">");
//	Schema_CStr += _T("\n\t\t<xsd:restriction base=\"xsd:string\">");
//	Schema_CStr += _T("\n\t\t\t<xsd:enumeration value=\"������\"/>");
//	Schema_CStr += _T("\n\t\t\t<xsd:enumeration value=\"���.�������\"/>");
//	Schema_CStr += _T("\n\t\t\t<xsd:enumeration value=\"��.�������\"/>");
//	Schema_CStr += _T("\n\t\t</xsd:restriction>");
//	Schema_CStr += _T("\n\t</xsd:simpleType>");
//	Schema_CStr += _T("\n\t<xsd:simpleType name=\"enumParam\">");
//	Schema_CStr += _T("\n\t\t<xsd:restriction base=\"xsd:string\">");
//	Schema_CStr += _T("\n\t\t\t<xsd:enumeration value=\"��������\"/>");
//	Schema_CStr += _T("\n\t\t\t<xsd:enumeration value=\"������\"/>");
//	Schema_CStr += _T("\n\t\t</xsd:restriction>");
//	Schema_CStr += _T("\n\t</xsd:simpleType>");
	Schema_CStr += _T("\n</xsd:schema>");


/*
<?xml version="1.0" encoding="windows-1251"?>
<xsd:schema xmlns:xsd="http://www.w3.org/2001/XMLSchema" elementFormDefault="qualified">
	<xsd:element name="�������_���">
		<xsd:complexType>
			<xsd:sequence>
				<xsd:element ref="������" minOccurs="1" maxOccurs="unbounded"/>
			</xsd:sequence>
			<xsd:attribute name="���" type="xsd:string" use="required"/>
			<xsd:attribute name="�������" type="enumSensor" use="required"/>
			<xsd:attribute name="��������" type="enumParam" use="required"/>
			<xsd:attribute name="�������" type="xsd:string" use="required"/>
			<xsd:attribute name="�����" type="xsd:string" use="required"/>
			<xsd:attribute name="�����_�����������" type="xsd:string" use="required"/>
		</xsd:complexType>
	</xsd:element>
	<xsd:element name="������">
		<xsd:complexType>
			<xsd:attribute name="���" type="xsd:string" use="required"/>
			<xsd:attribute name="��" type="xsd:string" use="required"/>
			<xsd:attribute name="�������" type="xsd:string" use="required"/>
			<xsd:attribute name="����" type="xsd:string" use="required"/>
			<xsd:attribute name="��������" type="xsd:string" use="required"/>
			<xsd:attribute name="��������" type="xsd:string" use="required"/>
			<xsd:attribute name="������_��������" type="xsd:string" use="required"/>
			<xsd:attribute name="������_�����" type="xsd:string" use="required"/>
		</xsd:complexType>
	</xsd:element>
	<xsd:simpleType name="enumSensor">
		<xsd:restriction base="xsd:string">
			<xsd:enumeration value="������"/>
			<xsd:enumeration value="���.�������"/>
			<xsd:enumeration value="��.�������"/>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="enumParam">
		<xsd:restriction base="xsd:string">
			<xsd:enumeration value="��������"/>
			<xsd:enumeration value="������"/>
		</xsd:restriction>
	</xsd:simpleType>
</xsd:schema>
*/

	CString EmptyCStr("");
	TCHAR XSDFile[_MAX_PATH];
	::GetModuleFileName(AfxGetApp()->m_hInstance, XSDFile, MAX_PATH);
	TCHAR* szExt = _tcsrchr(XSDFile, '\\');
	if(szExt) *(szExt+1) = 0;
	//���������
	_tcscat_s(XSDFile, _MAX_PATH, _T("TmpDivisionsFileWithSchemaForSouGenerator.xsd"));
	
	CFile CfileObjWrite(XSDFile, CFile::modeCreate|CFile:: modeReadWrite);
	CStringA Schema_CStrA(Schema_CStr);
	CfileObjWrite.Write( Schema_CStrA, Schema_CStrA.GetLength());
	CfileObjWrite.Close();

	_bstr_t Schema_bstr_t(_T(""));
	Schema_bstr_t = XSDFile;

	_bstr_t bstrSchemNameSpaceFile(_T(""));

	////hr = pXS->add(bstrSchemNameSpaceFile, bstrSchemFile);
	hr = pXS->add(bstrSchemNameSpaceFile, Schema_bstr_t);

	// Create a DOMDocument and set its properties.
	hr = pXD.CreateInstance(__uuidof(DOMDocument60));

	// Assign the schema cache to the DOMDocument's
	// schemas collection.
	pXD->schemas = pXS.GetInterfacePtr();

	// Load books.xml as the DOM document.
	pXD->async = VARIANT_FALSE;
	pXD->validateOnParse = VARIANT_TRUE;
	pXD->resolveExternals = VARIANT_TRUE;
	//hr = pXD->load("sl-notValid.xml");

	// 1) ��������� �����:
	if(XSDFile != EmptyCStr)
	{
		CFileFind hFile;
		bool bFound = false;
		bFound = hFile.FindFile( XSDFile );
			
		if(bFound)	{CFile::Remove(XSDFile);} // ������ ���� ���������� �����
	}

	//delete[] XSDFile;
	//free(XSDFile);
	//free(szExt);

	// check hr and pXD->errorCode here
    if(pXD->load(bstrXMLFile) != VARIANT_TRUE)
    {
        pErr = pXD->parseError;

        bstrResult = _bstr_t(L"������: ��������� ����� ") +
			_T("\"")+ bstrXMLFile +_T("\"") + _T("\n") +
			_T("�� ������������� ����������� ���.") +
            _bstr_t(L"\n==========================================") +
            _bstr_t(L"\n�������: ") + _bstr_t(pErr->Getline()) +
            _bstr_t(L"\n�������: ") + _bstr_t(pErr->GetsrcText()) +
            _bstr_t(L"\n�������: ") + _bstr_t(pErr->Getreason());// +
//            _bstr_t(L"\n");
		//AfxMessageBox( bstrResult );
		bValid=false;
		return bstrResult;
    }
    else
    {
		bstrResult = _bstr_t(L"��������� ����� ") +
			_T("\"")+ bstrXMLFile +_T("\"") +
			_T(" ������������� ����������� ���.");// +
			//_bstr_t(L"\n===========================================\n") +
            //_bstr_t(pXD->xml) + _bstr_t(L"\n");

		//AfxMessageBox( bstrResult );
		bValid=true;
		return bstrResult;
	}
}



CString CSOUGeneratorApp::GetErrorCSTRString(HRESULT hrErr)
{

	CString str;
	HRESULT hr_scode=HRESULT_CODE(hrErr);
	HRESULT hr_facility=HRESULT_FACILITY(hrErr);
	HRESULT hr_severity=HRESULT_SEVERITY(hrErr);
//	if(hr_facility!=FACILITY_SYMBOL_OPC)
//	{
//		if(!pIOPCServer)
//		{
			LPVOID lpMsgBuf=0;
			if (!FormatMessage( 
				FORMAT_MESSAGE_ALLOCATE_BUFFER | 
				FORMAT_MESSAGE_FROM_SYSTEM | 
				FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				hrErr,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
				(LPTSTR) &lpMsgBuf,
				0,
				NULL ))
			{
				// Handle the error.
				return _T("����������� ������  ");
			}
			// Process any inserts in lpMsgBuf.
			// ...
			// Display the string.
			if(lpMsgBuf)
			{
				str = (LPCTSTR)lpMsgBuf;
				LocalFree( lpMsgBuf );
			}
			else
				str=_T("����������� ������  ");

			return str;
//		}


		LPWSTR pwStr=NULL;
		HRESULT hrT=MAKE_HRESULT(hr_severity,hr_facility,hr_scode);

	return str;
}

