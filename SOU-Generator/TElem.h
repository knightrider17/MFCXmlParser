#pragma once
#include "afxwin.h"

//#include "XML-Msxml6.h"
//#include "XML-Msxml6.xsd"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif
// Единственный объект приложения
//CWinApp theApp;

#include <objsafe.h>
#include <objbase.h>
#include <atlbase.h>
#include <string>

#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#import <msxml6.dll>
#include <msxml6.h>

#include <vector>

#include "stdio.h"

//#import <msxml3.dll>
using namespace std;
//using namespace MSXML2;

// Macro that calls a COM method returning HRESULT value.
#define CHK_HR(stmt)        do { hr=(stmt); if (FAILED(hr)) goto CleanUp; } while(0)

// 1 // http://www.codeproject.com/Articles/4285/Using-MSXML-to-read-XML-documents
// TElem -- a simple class to wrap up IXMLDomElement and iterat its children.
//   name()    - in <item>stuff</item> it returns "item"
//   val()     - in <item>stuff</item> it returns "stuff"
//   attr(s)   - in <item s=L"hello">stuff</item> it returns "hello"
//   subnode(b)- in <item><a>hello</a><b>there</b></item> it returns the TElem <b>there</b>
//   subval(b) - in <item><a>hello</a><b>there</b></item> it returns "there"
//   for (TElem c=e.begin(); c!=e.end(); c++) {...} - iterators over the subnodes
struct TElem
{
	CComPtr<IXMLDOMElement> elem;
	CComPtr<IXMLDOMNodeList> nlist; int pos; long clen;
  //
  TElem() : elem(0), nlist(0), pos(-1), clen(0) {}
  TElem(int _clen) : elem(0), nlist(0), pos(-1), clen(_clen) {}
  TElem(CComPtr<IXMLDOMElement> _elem) : elem(_elem), nlist(0), pos(-1), clen(0) {get();}
  TElem(CComPtr<IXMLDOMNodeList> _nlist) : elem(0), nlist(_nlist), pos(0), clen(0) {get();}

  void get()
  {
	  if (pos!=-1)
    {
		elem=0;
      CComPtr<IXMLDOMNode> inode;
      nlist->get_item(pos,&inode);
      if (inode==0) return;
      DOMNodeType type; inode->get_nodeType(&type);
      if (type!=NODE_ELEMENT) return;
      CComQIPtr<IXMLDOMElement> e(inode);
      elem=e;
    }
    clen=0; 
	
	if (elem!=0)
    {
		CComPtr<IXMLDOMNodeList> iNodeList;
      elem->get_childNodes(&iNodeList);
      iNodeList->get_length(&clen);  
    }
  }
  //
  wstring name() const
  {
	  if (!elem) return L"";
    CComBSTR bn;
	elem->get_tagName(&bn);
    return wstring(bn);
  }
  wstring attr(const wstring name) const
  {
	  if (!elem) return L"";
    CComBSTR bname(name.c_str());
    CComVariant val(VT_EMPTY);
    elem->getAttribute(bname,&val);
    if (val.vt==VT_BSTR)
		return val.bstrVal;
    return L"";
  }
  bool attrBool(const wstring name,bool def) const
  {
	  wstring a = attr(name);
    if (a==L"true" || a==L"TRUE")
		return true;
    else if (a==L"false" || a==L"FALSE")
		return false;
    else
		return def;
  }
  int attrInt(const wstring name, int def) const
  {
	  wstring a = attr(name);
    int i, res=swscanf(a.c_str(),L"%i",&i);
    if (res==1) return i;
	else return def;
  }

  wstring val() const
  { if (!elem) return L"";
    CComVariant val(VT_EMPTY);
    elem->get_nodeTypedValue(&val);
    if (val.vt==VT_BSTR) return val.bstrVal;
    return L"";
  }

  TElem subnode(const wstring name) const
  {
	  if (!elem) return TElem();
    for (TElem c=begin(); c!=end(); c++)
    {
		if (c.name()==name)
			return c;
    }
    return TElem();
  }

  wstring subval(const wstring name) const
  {
	  if (!elem) return L"";
    TElem c=subnode(name);
    return c.val();
  }

  TElem begin() const
  { if (!elem) return TElem();
    CComPtr<IXMLDOMNodeList> iNodeList;
    elem->get_childNodes(&iNodeList);
    return TElem(iNodeList);
  }

  TElem end() const
  { return TElem(clen); }

  TElem operator++(int)
  {
	  if (pos!=-1) {pos++; get();}
    return *this;
  }

  bool operator!=(const TElem &e) const
  { return pos!=e.clen; }
};


