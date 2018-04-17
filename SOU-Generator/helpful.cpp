//#ifdef WITH_MFC
#include "stdafx.h"
//#endif

#include "helpful.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <atlstr.h>

//#ifdef WITH_MFC
bool HexStringToByteChain(CString& sHex, BYTE* ByteChain, DWORD cbSize, DWORD& cbConverted)
{
	BYTE chByte=0;
	int i;		//индекс
	int cbHex=0;//счетчик тетрад
	
	for(i=0,cbConverted=0; i<sHex.GetLength(); i++)
	{
		TCHAR ch = sHex[i];
		if(isxdigit(ch))//hex digit
		{	TCHAR digit;
			if(ch>='0' && ch<='9') digit=ch-'0';
			if(ch>='a' && ch<='f') digit=ch-'a'+10;
			if(ch>='A' && ch<='F') digit=ch-'A'+10;
			cbHex++; chByte=((chByte<<4)&0xF0) + (digit&0xF);
		}
		if(cbHex==2)
		{//две тетрады - байт
			if(cbConverted < cbSize) ByteChain[cbConverted]=chByte;
			cbHex=0; chByte=0; cbConverted++;
		}
	}
	if(cbConverted>cbSize) return false;
	return true;
}
//#endif

char* DumpBuffer(LPBYTE pBuffer, DWORD cbBufLen)
{
	size_t cbOutBufLen = 3*cbBufLen;
	char* pStr = (char*)calloc( cbOutBufLen, sizeof(char) );
	if(pStr!=NULL)
	{
		char* pByteStr = pStr;
		size_t cbOutBufLen_rest = cbOutBufLen;
		for(DWORD dwI=0; dwI<cbBufLen; dwI++)
		{
			int cb = sprintf_s(	pByteStr, cbOutBufLen_rest,
						"%02X%c",
						pBuffer[dwI], dwI<cbBufLen-1? '.' : '\0' );
			//ASSERT(cb==3);
			if(cb>0)
			{
				pByteStr         += cb;
				cbOutBufLen_rest -= cb;
			}
			else
			{
				break;
			}
		}
	}

	return pStr;
}

void SwapBytes(PBYTE pBuf, int cbBufLen)
{
	if(pBuf!=NULL)
	{
		for(int i=0; i<cbBufLen/2; i++)
		{
			BYTE btTmp = pBuf[i];
			pBuf[i] = pBuf[(cbBufLen-1)-i];
			pBuf[(cbBufLen-1)-i] = btTmp;
		}
	}
}

bool FindInTokens(const wchar_t* source, const wchar_t* substring, const wchar_t* delimiters)
{
	wchar_t* token=NULL;
//	wchar_t* string = strdup(source);//т.к. дальнейший вызов strtok портит исходную строку
	wchar_t* string = wcsdup(source);//т.к. дальнейший вызов strtok портит исходную строку

	//разобъём строку на лексеммы в соответствии с разделителями:
//	token = strtok(string,delimiters);
	token = wcstok(string,delimiters);
	while(token)//очередная лексемма выделена
	{
//		if(!strcmp(token,substring)){ free(string); return true; }
		if(!wcscmp(token,substring)){ free(string); return true; }

		//выделить следующую лексемму:
//		token = strtok(NULL,delimiters);
		token = wcstok(NULL,delimiters);
	}
	
	free(string);//все в порядке, указатель не меняется
	return false;
}

/*	ParseFString: разбор строки в соответствии с форматом
 *	кодирование аргументов в строке формата:
 *	тип:
 *	l-signed,L-unsigned dword (32-bit)
 *	w-signed,W-unsigned word  (16-bit)
 *	b-signed,B-undigned byte  ( 8-bit)
 *	f-number with floating point
 *	s-string, S-"string"
 *	
 *	для l(L), w(W), b(B) - определен символ системы счисления:
 *	o - octal
 *	d - decimal
 *	h - hexadecimal
 *	отсутствие - с/сч определяется автоматически
 * 
 *	все остальные символы, найденные в форматной строке воспринимаются как разделители
 *
 *	Пример:
 *	void* arg_list[5] = {&cell,&cells,sComment,sType,sAccess};
 *	ParseFString(str,"Bh,Bd,S,s,s",arg_list);
 *
 *	Функция возвращает количество успешно распознанных аргументов.
*/
int ParseFString(
		LPTSTR  pszParsingString,	//строка  для разбора
		LPCTSTR format,				//форматная строка
		void* arg_list[]			//массив указателей на аргументы (количество аргументов определяется форматом!)
				)
{
	LPTSTR str_beg, string; str_beg = string = _tcsdup(pszParsingString);//strdup(pszParsingString);
	LPTSTR part = NULL;

	int idx = 0;
	int arg_count=0;

	TCHAR format_char = '\0', delim_char = '\0';
	int base=0;

	do
	{
		switch(format[idx])
		{
		//эти символы обозначают формат аргумента
		case 'l':
		case 'L':
		case 'w':
		case 'W':
		case 'b':
		case 'B':
		case 's':
		case 'S':
			format_char=format[idx]; break;
		case 'o': base = 8;	break;
		case 'd': base = 10;break;
		case 'h': base = 16;break;

		//все остальные воспринимаются как разделители
		default:
			delim_char=format[idx];
			//начало преобразования очередного аргумента
			
			//если строка, то берем только то, что внутри кавычек
			if(format_char=='S')
			{
				//игнорируем то, что перед открывающей кавычкой
				while(*string && *string!='"') string++;
				if(*string=='"') string++;//и ее тоже
			
				part=string;//начало строки

				while(*string && *string!='"') string++;//ищем закрывающую кавычку
				if(*string=='"'){ *string=0; string++; }
			}
			else
			{
				part=string;//начало строки
			}

			//ищем delim_char
			while(*string && *string!=delim_char) string++;
			
			if(*string)
			{//в анализируемой строке найден разделитель
				//string указывает на delim_char
				*string = 0; string++;
			}

			//part содержит нужную подстроку
			switch(format_char)
			{
			case 'l':
				*(long*)arg_list[arg_count] = _tcstol(part,NULL,base);//0 - автоопределение основания с/сч: 16/8/10
				arg_count++;
				break;
			case 'L':
				*(unsigned long*)arg_list[arg_count] = _tcstoul(part,NULL,base);
				arg_count++;
				break;
			case 'w':
				*(short*)arg_list[arg_count] = (short)_tcstol(part,NULL,base);
				arg_count++;
				break;
			case 'W':
				*(unsigned short*)arg_list[arg_count] = (unsigned short)_tcstoul(part,NULL,base);
				arg_count++;
				break;
			case 'b':
				*(char*)arg_list[arg_count] = (char)_tcstol(part,NULL,base);
				arg_count++;
				break;
			case 'B':
				*(unsigned char*)arg_list[arg_count] = (unsigned char)_tcstoul(part,NULL,base);
				arg_count++;
				break;
			case 'f':
//TODO: not supported yet
				*(double*)arg_list[arg_count] = 0.;//atof(part);
				arg_count++;
				break;
			case 's':
				//if(part[0]=='"' && part[strlen(part)-1]=='"') ++part, part[strlen(part)-1]=0;
			case 'S':
				_tcscpy((TCHAR*)arg_list[arg_count],part);
				arg_count++;
				break;
			}//switch(format_char)
			format_char=delim_char=0; base=0;
		}//switch(format[idx])
		//idx++;
	}while(format[idx++]);

	free(str_beg);

	return arg_count;
}

int PrintLastErrorMessage(LPCTSTR caption, LPCTSTR comment, DWORD dwErr, UINT msg_type/*=MB_TASKMODAL|MB_ICONERROR|MB_OK*/)
{
	if(!dwErr) dwErr=GetLastError();

	LPVOID lpErrorMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_ALLOCATE_BUFFER,
		NULL,
		dwErr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpErrorMsgBuf,
		0,
		NULL
		);

	LPVOID lpFullMsgBuf;
	LPVOID lpArgBuf[3] = { (LPVOID)comment, (LPVOID)dwErr, lpErrorMsgBuf };
	FormatMessage(
		FORMAT_MESSAGE_FROM_STRING|FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_ARGUMENT_ARRAY,
		_T("%1 (0x%2!08X!):\n\r%3"),
		dwErr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpFullMsgBuf,
		0,
		(va_list*)lpArgBuf
		);
/*
    // Display the error message and exit the process
	LPVOID lpDisplayBuf = (LPVOID)LocalAlloc(
		LMEM_ZEROINIT, 
		sizeof(TCHAR) * ( _tcslen((LPCTSTR)lpErrorMsgBuf) + _tcslen(comment) + 20 )
		); 
	StringCchPrintf(
		(LPTSTR)lpDisplayBuf, LocalSize(lpDisplayBuf),
		_T("%s failed with error %d: %s"), 
		comment, dw, lpMsgBuf
		); 
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
*/

	int msg_ret = MessageBox(NULL, (LPCTSTR)lpFullMsgBuf, caption, msg_type/*default: MB_TASKMODAL|MB_ICONERROR|MB_OK*/);

	LocalFree(lpErrorMsgBuf);
	LocalFree(lpFullMsgBuf);

	return msg_ret;
}

LPVOID MemoryAllocate(DWORD dwSize)
{  // MemoryAllocate
	HGLOBAL hMemory;
	LPVOID  lpMemory;
	
	hMemory = GlobalAlloc(GHND,dwSize);
	if(!hMemory) return NULL;
	
	lpMemory = GlobalLock(hMemory);
	if(!lpMemory) GlobalFree(hMemory);
	
	return lpMemory;
}  // MemoryAllocate


void MemoryFree(LPVOID lpMemory)
{  // MemoryFree
	HGLOBAL hMemory;
	
	if(!lpMemory) return;
	
	hMemory = GlobalHandle(lpMemory);
	if(hMemory)
	{  // if
		GlobalUnlock(hMemory);
		GlobalFree(hMemory);
	}  // if
}  // MemoryFree

//////////////////////////////////////////////////////////////////////////

WORD CRC16(PBYTE pBuf, int iBufSize)
{
	WORD CRC = 0xFFFF;

#if 0
	for(int i=0; i<iBufSize; i++)
	{
		CRC ^= pBuf[i];
		
		for(int j=0; j<8; j++)
		{
			if( CRC&1 )
			{//младший бит==1
				//CRC >>= 1;
				CRC ^= 0x1021;//0x8408;
			}
			else
			{//младший бит==0
				CRC >>= 1;
			}
		}
	}

	CRC ^= 0;//0xFFFF;
	
#else

	for(int i=0; i<iBufSize; i++)
	{
		CRC ^= pBuf[i];
		
		for(int j=0; j<8; j++)
		{ 
			bool bit0 = (CRC&1)!=0;
			CRC >>= 1;
			if(bit0)
				CRC ^= 0xA001;
		}
	}
#endif

	return CRC;
}


#define POLY_CRC16 0xA001
static BYTE TABLE1[256];
static BYTE TABLE2[256];

void crc_init(void)/*set crc table*/
{
	WORD mask, bit, crc, mem;

	for(mask=0; mask<256; mask++)
	{
		crc=mask;
		for(bit=0; bit<8; bit++)
		{
			mem = crc&0x0001;
			crc/=2;
			if(mem!=0) crc ^= POLY_CRC16;
		}

		TABLE2[mask] = crc &  0xFF;
		TABLE1[mask] = crc >> 8;
	}
}

void crc_make(WORD size, BYTE* pBuf, BYTE* hi, BYTE* lo)/*calculate crc*/
{
	BYTE car, i;
	BYTE crc[2];
	crc[0]=0xFF;
	crc[1]=0xFF;

	for(i=0; i<size; i++)
	{
		car  = pBuf[i];
		car ^= crc[0];

		crc[0] = crc[1] ^ TABLE2[car];
		crc[1] = TABLE1[car];
	}

	*hi=crc[0];
	*lo=crc[1];
}

void LCPUpdateCRC(BYTE Data, WORD& CRC)
{
	//combine the new data byte with the current CRC
	for(int i=7; i>=0; i--)
	{
		bool XORFlag = (CRC&0x8000)!=0x0000;
		CRC <<= 1;
		CRC  |= (WORD)((Data>>i) & 0x01);
		if(XORFlag) CRC ^= 0x1021;
	}
}

//////////////////////////////////////////////////////////////////////////
#include <string>

std::string wstring_to_string(const std::wstring& wstr)
{
    size_t wstrSize = wstr.size()+1;

	char* pszTmp = new char[wstrSize];

    DWORD dwError;

    // Convert to ANSI.
	if (0 == ::WideCharToMultiByte(
					CP_ACP, 0,
					wstr.c_str(), wstrSize,
					pszTmp, wstrSize,
					NULL, NULL))
    {
        dwError = GetLastError();
        return std::string();
    }

	std::string strTmp(pszTmp); delete pszTmp;

	return strTmp;
}

std::wstring string_to_wstring(const std::string& str)
{
    size_t strSize = str.size()+1;

	wchar_t* pwszTmp = new wchar_t[strSize];

    DWORD dwError;

    // Convert to UNICODE.
	if (0 == ::MultiByteToWideChar(
					CP_ACP, 0,
					str.c_str(), strSize,
					pwszTmp, strSize))
    {
        dwError = GetLastError();
        return std::wstring();
    }

	std::wstring wstrTmp(pwszTmp); delete pwszTmp;

	return wstrTmp;
}

//////////////////////////////////////////////////////////////////////////

/*
 * Алгоритм: Assaf Tzur-El, January 15, 2002 
 * http://www.codeguru.com/cpp/w-p/files/article.php/c4439/
 *
 * Переформатировал оформление кода, добавил версию с CString,
 * исправил ошибку else if(attr!=FILE_ATTRIBUTE_DIRECTORY)...
 */

bool CreatePath(std::wstring& wsPath)
{
	DWORD attr;
	int pos;
	bool result = true;

	// Check for trailing slash:
	pos = wsPath.find_last_of('\\');
	if( wsPath.length() == pos + 1 ) // last character is "\"
	{
		wsPath.resize(pos);
	}

	// Look for existing object:
	attr = ::GetFileAttributesW( wsPath.c_str() );
	if( attr==0xFFFFFFFF ) // doesn't exist yet - create it!
	{
		pos = wsPath.find_last_of('\\');
		if(pos>0)
		{
			// Create parent dirs:
			result = CreatePath(wsPath.substr(0, pos));
		}
		// Create node:
		result = result && ::CreateDirectoryW(wsPath.c_str(), NULL);
	} else
	if(!(attr&FILE_ATTRIBUTE_DIRECTORY))
	{	// object already exists, but is not a dir
		SetLastError(ERROR_FILE_EXISTS);
		result = false;
	}

	return result;
}

//#ifdef WITH_MFC
bool CreatePath(CString& sPath)
{
	DWORD attr;
	int pos;
	bool result = true;

	// Check for trailing slash:
	pos = sPath.ReverseFind('\\');
	if(sPath.GetLength() == pos + 1)  // last character is "\"
	{
		sPath = sPath.Left(pos);
	}

	// Look for existing object:
	attr = ::GetFileAttributes((LPCTSTR)sPath);
	if(attr==0xFFFFFFFF)  // doesn't exist yet - create it!
	{
		pos = sPath.ReverseFind('\\');
		if(pos>0)
		{
			// Create parent dirs:
			result = CreatePath(sPath.Left(pos));
		}
		// Create node:
		result = result && ::CreateDirectory((LPCTSTR)sPath, NULL);
	} else
	if(!(attr&FILE_ATTRIBUTE_DIRECTORY))
	{  // object already exists, but is not a dir
		SetLastError(ERROR_FILE_EXISTS);
		result = false;
	}

	return result;
}
//#endif

////////////////////////////////////////////////////////////////////////////////
#if 1
//нижеследующее взято и переделано из функции _AfxOleDateFromTm файла olevar.cpp исходников MFC
BOOL OleDateFromFileTime(CONST FILETIME *lpFileTime, DATE* pOleDate)
{
	if(lpFileTime==NULL || pOleDate==NULL) return FALSE;

	SYSTEMTIME st={0};
	if(!::FileTimeToSystemTime(lpFileTime,&st)) return FALSE;

	static const int MonthDays[13] =
	{0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

	//Определим, високосный ли год
	BOOL bLeapYear = ((st.wYear&3)==0) && ((st.wYear%100)!=0 || (st.wYear%400)==0);

	//Количество дней в месяце
	int nDaysInMonth = MonthDays[st.wMonth] - MonthDays[st.wMonth-1] +
						((bLeapYear && st.wDay==29 && st.wMonth==2) ? 1 : 0);
	
	long nDate;		//дата в днях
	double dblTime;	//время в долях суток

	//дата в днях относительно 1 января 1 года н.э.
	nDate = st.wYear*365L + st.wYear/4 - st.wYear/100 + st.wYear/400 + MonthDays[st.wMonth-1] + st.wDay;

	//если високосный год и до 1 марта, уменьшить на 1
	if(st.wMonth <= 2 && bLeapYear) --nDate;

	//привести дату относительно 30 декабря 1899 года н.э.
	nDate -= 693959L;

	#if 0
	//без учета миллисекунд
	dblTime = ( ((long)st.wHour * 3600L) +  // секунд в часе
				((long)st.wMinute * 60L) +  // секунд в минуте
				((long)st.wSecond)			) / 86400./*секунд в сутках*/;
	#else
	//с учетом миллисекунд
	dblTime = ( ((long)st.wHour * 3600000.) +  // миллисекунд в часе
				((long)st.wMinute * 60000.) +  // миллисекунд в минуте
				((long)st.wSecond *  1000.) +  // миллисекунд в секунде
				((long)st.wMilliseconds   )
				) / 86400000./*миллисекунд в сутках*/;
	#endif

	*pOleDate = (double) nDate + ((nDate >= 0) ? dblTime : -dblTime);

	return TRUE;
}
#else
//способ предложил Dervish из форума RSDN
BOOL OleDateFromFileTime(CONST FILETIME *lpFileTime, DATE* pOleDate)
{
	if(lpFileTime==NULL || pOleDate==NULL) return FALSE;

	// Преобразуем исходное значение к типу double
	*pOleDate = (double)lpFileTime->dwHighDateTime * 4294967296. /* 2^32 */ +
				(double)lpFileTime->dwLowDateTime;

	// Разделим на количество 100-наносекундных интервалов в сутках
	*pOleDate /= 864000000000.;

	// И отнимем количество дней между 31.12.1899 и 01.01.1601
	*pOleDate -= 109205.;

	return TRUE;
}
#endif

BOOL FileTimeToOleDate(CONST FILETIME *lpFileTime, DATE* pOleDate)
{
	if(lpFileTime==NULL || pOleDate==NULL) return FALSE;

	// Преобразуем исходное значение к типу double
	*pOleDate = (double)lpFileTime->dwHighDateTime * 4294967296. /* 2^32 */ +
				(double)lpFileTime->dwLowDateTime;

	// Разделим на количество 100-наносекундных интервалов в сутках
	*pOleDate /= 864000000000.;

	// И отнимем количество дней между 31.12.1899 и 01.01.1601
	*pOleDate -= 109205.;

	return TRUE;
}

BOOL OleDateToFileTime(CONST DATE* pOleDate, FILETIME *lpFileTime)
{
	if(lpFileTime==NULL || pOleDate==NULL) return FALSE;

	DATE dtTmp = *pOleDate;

	// Прибавим количество дней между 31.12.1899 и 01.01.1601
	dtTmp += 109205.;

	// Умножим на количество 100-наносекундных интервалов в сутках
	dtTmp *= 864000000000.;

	// Преобразуем исходное значение к типу FileTime
	const double dbl2pow32 = 4294967296.; // 2^32

	lpFileTime->dwHighDateTime = floor(dtTmp / dbl2pow32); // (дробная часть
	// автоматически отбрасывается при преобразовании)
	double dblTmp = dtTmp - floor(dtTmp / dbl2pow32) * dbl2pow32;
	lpFileTime->dwLowDateTime  = floor(dblTmp);

	double dblTmp2 = fmod(dtTmp, dbl2pow32);

	return TRUE;
}
	
//////////////////////////////////////////////////////////////////////////
//преобразование строки UNICODE в UTF-8
bool ConvertToUTF8W(const wchar_t* pwszSrc, char** ppszUTF8)
{
	if(pwszSrc==NULL || ppszUTF8==NULL)
	{
		return false;
	}

	//int nSrcSize = wcslen(pwszSrc);
	//if(!nSrcSize)
	//{
	//	(*ppszUTF8) = NULL;
	//	return true;
	//}

	int iReqSize = WideCharToMultiByte( CP_UTF8, 0,
						pwszSrc, -1 /*null-terminated string*/,
						NULL, 0,
						NULL, NULL );
	char* pTmp = new char[iReqSize];
	if(!pTmp)
	{
		(*ppszUTF8) = NULL;
		return false;
	}

	int iConvSize = WideCharToMultiByte( CP_UTF8, 0,
						pwszSrc, -1,
						pTmp, iReqSize,
						NULL, NULL );
	if(!iConvSize)
	{
		delete[] pTmp;
		(*ppszUTF8) = NULL;
		return false;
	}

	(*ppszUTF8) = pTmp;
	return true;
}

//преобразование строки ASCII в UTF-8
bool ConvertToUTF8A(const char* pszSrc, char** ppszUTF8)
{
	if(pszSrc==NULL || ppszUTF8==NULL)
	{
		return false;
	}

	//1) преобразование из ASCII (MultiByte) в Unicode (WideChar)
	//int nSrcSize = strlen(pszSrc);
	//if(!nSrcSize)
	//{
	//	(*ppszUTF8) = NULL;
	//	return true;
	//}

	int iReqSize = MultiByteToWideChar( CP_ACP, 0,
						 pszSrc, -1 /*null-terminated string*/,
						 NULL, 0
						);
	wchar_t* pTmp = new wchar_t[iReqSize];
	if(!pTmp)
	{
		(*ppszUTF8) = NULL;
		return false;
	}

	int iConvSize = MultiByteToWideChar( CP_ACP, 0,
						 pszSrc, -1,
						 pTmp, iReqSize
						);
	if(!iConvSize)
	{
		delete[] pTmp;
		(*ppszUTF8) = NULL;
		return false;
	}

	//2) преобразование из Unicode (WideChar) в UTF-8 (MultiByte)
	bool bRes = ConvertToUTF8W(pTmp,ppszUTF8);
	delete[] pTmp;
	return bRes;
}

//преобразование строки UTF-8 в UNICODE
bool ConvertFromUTF8W(const char* pszUTF8, wchar_t** ppwszDest)
{
	if(pszUTF8==NULL || ppwszDest==NULL)
	{
		return false;
	}

	int iReqSize = MultiByteToWideChar( CP_UTF8, 0,
					pszUTF8, -1 /*null-terminated string*/,
					NULL, 0);
	wchar_t* pTmp = new wchar_t[iReqSize];
	if(!pTmp)
	{
		(*ppwszDest) = NULL;
		return false;
	}

	int iConvSize = MultiByteToWideChar( CP_UTF8, 0,
					pszUTF8, -1,
					pTmp, iReqSize);
	if(!iConvSize)
	{
		delete[] pTmp;
		(*ppwszDest) = NULL;
		return false;
	}

	(*ppwszDest) = pTmp;
	return true;
}

//преобразование строки UTF-8 в ASCII
bool ConvertFromUTF8A(const char* pszUTF8, char** ppszDest)
{
	if(pszUTF8==NULL || ppszDest==NULL)
	{
		return false;
	}

	//1) преобразование из UTF8 (MultiByte) в Unicode (WideChar)
	wchar_t* pTmp = NULL;
	if(!ConvertFromUTF8W(pszUTF8,&pTmp))
	{
		(*ppszDest) = NULL;
		return false;
	}

	//2) преобразование из Unicode (WideChar) в ASCII(MultiByte)
	int iReqSize = WideCharToMultiByte( CP_ACP, 0,
						pTmp, -1 /*null-terminated string*/,
						NULL, 0,
						NULL, NULL );
	char* pTmp2 = new char[iReqSize];
	if(!pTmp2)
	{
		delete[] pTmp;
		(*ppszDest) = NULL;
		return false;
	}

	int iConvSize = WideCharToMultiByte( CP_ACP, 0,
						pTmp, -1,
						pTmp2, iReqSize,
						NULL, NULL );
	if(!iConvSize)
	{
		delete[] pTmp;
		(*ppszDest) = NULL;
		return false;
	}

	delete[] pTmp;
	(*ppszDest) = pTmp2;
	return true;
}


//преобразование цифры ('0'-'9','a'-'f') в соответствующий ей код (0-9,0xA-0xF)
BYTE Digit2Code(char ch)
{
	BYTE btCode = 0;

	switch(ch)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		btCode = ch - '0';
		break;
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
		btCode = ch - 'a' + 0x0A;
		break;
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
		btCode = ch - 'A' + 0x0A;
		break;
	}

	return btCode;
}

////////////////////////////////////////////////////////////////////////////////
//#ifdef WITH_MFC
CIniParam::CIniParam( LPCTSTR szFile, LPCTSTR szSection, LPCTSTR szKey, LPCTSTR szDefault )
	: m_sFile(szFile)
	, m_sSection(szSection)
	, m_sKey(szKey)
{
	ZeroMemory(m_Buffer,512);

	if( !::GetPrivateProfileString(m_sSection, m_sKey, NULL, m_Buffer, 512, m_sFile) && szDefault!=NULL)
	{
		_tcscpy_s(m_Buffer, 512, szDefault);
		Save();
	}
}

float CIniParam::AsFloat()
{
	return _ttof(m_Buffer);
}

int CIniParam::AsInt()
{
	return _ttoi(m_Buffer);
}

LPCTSTR CIniParam::AsString()
{
	return m_Buffer;
}

void CIniParam::Set( float f )
{
	_stprintf_s(m_Buffer, 512, _T("%f"), f);
}

void CIniParam::Set( int i )
{
	_stprintf_s(m_Buffer, 512, _T("%d"), i);
}

void CIniParam::Set( LPCTSTR s )
{
	_tcscpy_s(m_Buffer, 512, s);
}

void CIniParam::Save()
{
	::WritePrivateProfileString(m_sSection, m_sKey, m_Buffer, m_sFile);
}
bool CIniParam::SaveBool()
{
	if( ::WritePrivateProfileString(m_sSection, m_sKey, m_Buffer, m_sFile) )
	{return true;}
	else
	{return false;}

}

//#endif
