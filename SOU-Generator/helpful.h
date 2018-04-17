#ifndef _HELPFUL_H_52D3C5CB_23A7_4F22_A51E_55C34190E2BB_INCLUDED_
#define _HELPFUL_H_52D3C5CB_23A7_4F22_A51E_55C34190E2BB_INCLUDED_

////////////////////////////////////////////////////////////////////////////////

// Если данный модуль используется в проектах, не использующих библиотеки MFC,
// например, в проектах ATL, в настройках компилятора для него определить макрос WITHOUT_MFC.
//
////////////////////////////////////////////////////////////////////////////////

#pragma message ("If this module is used in MFC-projects, add the WITH_MFC macro to preprocessor definitions for this file.")

////////////////////////////////////////////////////////////////////////////////

union BYTE_BY_BITS {
	struct {
		bool b0:1;
		bool b1:1;
		bool b2:1;
		bool b3:1;
		bool b4:1;
		bool b5:1;
		bool b6:1;
		bool b7:1;
	};
	BYTE val;

	BYTE_BY_BITS() : val(0) {}
};

#pragma pack(push,1)
union DWORD_BY_BYTES {
	struct {
		BYTE bt0;
		BYTE bt1;
		BYTE bt2;
		BYTE bt3;
	};
	DWORD val;

	DWORD_BY_BYTES() : val(0l) {}
};
#pragma pack(pop)

////////////////////////////////////////////////////////////////////////////////

//#ifdef WITH_MFC
//                        !!!!!!!
bool HexStringToByteChain(CString& sHex, BYTE* ByteChain, DWORD cbSize, DWORD& cbConverted);
//                        !!!!!!!
//#endif//WITH_MFC

char* DumpBuffer(LPBYTE pBuffer, DWORD cbBufLen);
void SwapBytes(PBYTE pBuf, int cbBufLen);

//bool FindInTokens(const char* source, const char* substring, const char* delimiters);
bool FindInTokens(const wchar_t* source, const wchar_t* substring, const wchar_t* delimiters);
int ParseFString(LPTSTR pszParsingString, LPCTSTR format, void* arg_list[]);

int PrintLastErrorMessage(LPCTSTR caption, LPCTSTR comment, DWORD dwErr=0, UINT msg_type=MB_TASKMODAL|MB_ICONERROR|MB_OK);

LPVOID MemoryAllocate(DWORD dwSize);
void MemoryFree(LPVOID lpMemory);

WORD CRC16(PBYTE pBuf, int iBufSize);
void crc_init(void);
void crc_make(WORD size, BYTE* pBuf, BYTE* hi, BYTE* lo);

void LCPUpdateCRC(BYTE Data, WORD& CRC);

//////////////////////////////////////////////////////////////////////////
BOOL OleDateFromFileTime(CONST FILETIME *lpFileTime, DATE* pOleDate);

BOOL FileTimeToOleDate(CONST FILETIME *lpFileTime, DATE* pOleDate);
BOOL OleDateToFileTime(CONST DATE* pOleDate, FILETIME *lpFileTime);

////////////////////////////////////////////////////////////////////////////////

#include <string>
//#include <iostream>
//#include <sstream>

typedef std::basic_string< TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> > _tstring;
std::string wstring_to_string(const std::wstring& wstr);
std::wstring string_to_wstring(const std::string& str);

#ifdef _UNICODE
 #define _FROM_ANSI(x) string_to_wstring( std::string ( ( x ) ) ).c_str()
 #define   _TO_ANSI(x) wstring_to_string( std::wstring( ( x ) ) ).c_str()
#else
 #define _FROM_ANSI(x) ( x )
 #define   _TO_ANSI(x) ( x )
#endif

bool CreatePath(std::wstring& wsPath);
//#ifdef WITH_MFC
//              !!!!!!!
bool CreatePath(CString& sPath);
//              !!!!!!!
//#endif //WITH_MFC

//////////////////////////////////////////////////////////////////////////

bool ConvertToUTF8A(const char* pszSrc, char** ppszUTF8);
bool ConvertToUTF8W(const wchar_t* pwszSrc, char** ppszUTF8);

bool ConvertFromUTF8A(const char* pszUTF8, char** ppszDest);
bool ConvertFromUTF8W(const char* pszUTF8, wchar_t** ppwszDest);

#ifdef _UNICODE
	#define ConvertToUTF8 ConvertToUTF8W
	#define ConvertFromUTF8 ConvertFromUTF8W
#else
	#define ConvertToUTF8 ConvertToUTF8A
	#define ConvertFromUTF8 ConvertFromUTF8A
#endif // !UNICODE

///////////////////////////////////////////////////////////////////////////

BYTE Digit2Code(char ch);

////////////////////////////////////////////////////////////////////////////////

//#ifdef WITH_MFC
class CIniParam
{
public:
	CIniParam(LPCTSTR szFile, LPCTSTR szSection, LPCTSTR szKey, LPCTSTR szDefault=NULL);

	float   AsFloat();
	int     AsInt();
	LPCTSTR AsString();

	void Set(float f);
	void Set(int i);
	void Set(LPCTSTR s);

	void Save();
	bool SaveBool();

private:
	CString m_sFile;
	CString m_sSection;
	CString m_sKey;

	TCHAR m_Buffer[512];
};
//#endif //WITH_MFC
////////////////////////////////////////////////////////////////////////////////

#endif //_HELPFUL_H_52D3C5CB_23A7_4F22_A51E_55C34190E2BB_INCLUDED_