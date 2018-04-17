
// SOU-Generator.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы
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
// О реализации данного класса см. SOU-Generator.cpp
//

class CSOUGeneratorApp : public CWinApp
{
public:
	CSOUGeneratorApp();


	CString GetErrorCSTRString(HRESULT hrErr);

	SYSTEMTIME m_CurTime;	//текущее системное время


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


	int Version;			// SQL или XML версия программы
	enum ProgVer 
	{
		VER_SQL,
		VER_XML
	};

	int IniDBLoginTimeout;

	CString ConnectOrDB_Step;	// этап/шаг на котором произошла ошибка
	CString ConnectOrDB_Error;	// ошибка произошедшая в результате соединения с Базой данных / либо при выполнении запроса


	CString CurDivName;		// Имя участка
	CString CurDivPipe;		// Выставленный на Участке трубопровод
	CString CurDivProd;		// Выставленный на Участке продукт
	CString CurDivParam;	// Выставленный на Участке параметр
	CString CurDivWatch;	// Выставленный на Участке следить
	CString CurDivWave;		// Выставленный на Участке волна
	CString CurDivTimedet;	// Выставленный на Участке Время_обнаружения
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

	CString CurDetNum;		// Номер выбранного для Изменения/Удаления/Просмотра Датчика
	//CString CurDetName;	// Выбранный для Изменения/Удаления/Просмотра Датчик
	CString CurDetSysName;	// Имя Датчика в системе выбранного для Изменения/Удаления/Просмотра
	CString CurDetGrafName;	// Имя Датчика на графике, который выбрали для Изменения/Удаления/Просмотра
	enum DetBtn 
	{
		DET_NOBTN,
		DET_BTN_ADD_ALL,
		DET_BTN_ADD,
		DET_BTN_CHANGE,
		DET_BTN_LOOK
	};

	DivBtn ChangeDivBtnClicked; // Что за кнопку нажали в окне "Список Участков"
	DetBtn EditDivDetBtnClicked; // Чтот за кнопку нажали в окне "Свойства Участка" для выбранного в списке Датчика

	CString IniFileName; // Путь до ini-файла, включающий имя самого файла в этом пути
	CString IniFilePath; // Путь до папки, в которой находится ini-файл

	CString IniDetectorsPath; // Путь к XML-файлу со списком Датчиков, включающий имя самого файла в этом пути, ВЗЯТЫЙ из ini-файла
	CString CurDetectorsPath;
	CString DetectorsFileName; // Имя XML-файла

	CString IniDivisionsPath; // Путь к файлам (*.sou) Участков, в конце пути по умолчанию установлено "\Участки", ВЗЯТЫЙ из ini-файла
	CString CurDivisionsPath;
	CString DivisionFileName; // Имя SOU-файла Название Выбранного для Изменения/Удаления/Просмотра ФАЙЛА Участка (.sou)
							  // Который мы распарсим при окрытии окна "Редактирования Участка" и вставим все полученные параметры

	std::vector<CString> AllDivisionsFileNames;
	long DivNextFileName;  // номер копии для имени SOU-файла доступное для добавления

	bool XMLDetectorsFound;	// Найден ли XML-файл с Датчиками по указанному в ini-файле пути
	int MaxDetectors;		// Максимальное число Датчиков на одном участке (если указать ноль, то их число неограничено!)


	std::vector<std::vector<CString>> ErrDivisions; // Файлы Участков, в которых были обнаружен ошибки // содержит ИМЯ файла // Содержит Ошибку

	std::vector<std::vector<CString>> AllDetectors;
	//detnum //detname //detptfix //detdistance //detfilepath //detprodtype //detprodid

	std::vector<std::vector<CString>> AllDivisions;
	// вектор для хранения информации о всех параметрах только участков (без датчиков в них), включая название файла Участка

	std::vector<std::vector<CString>> FullDivision;
	// FullDivision[0] - 1-вый вектор из строковых элементов будет содержать всю ифнормацию о выбранном Участке
	// FullDivision[1], ... , [n] - 2-ой и все последующие строковые векторы будут хранить данные Датчиков с Участка

	// FullDivision[0] - 1-вый вектор из строковых элементов будет содержать всю ифнормацию о выбранном Участке
	//divname //divprod //divparam //divwatch //divwave //divtimedet
	//имя	//продукт	//параметр //следить  //волна	// Время_обнаружения

	// FullDivision[1], ... , [n] - 2-ой и все последующие строковые векторы будут хранить данные Датчиков с Участка
	//так в векторе:	//detnum //detname //detactive //detfilepath //detptfix //detdistance //detdpress //detdtime
	//так в .sou файле:	//имя	 //нр	   //активен	//путь		 //постфикс	//удаление	  //дельта_давление	// дельта_время

	//<?xml version="1.0" encoding="windows-1251"?>
	//<Участок_СОУ имя="Рязань Дизель Дин." продукт="Диз.топливо" параметр="Давление" следить="0" волна="1.239" Время_обнаружения="10">
	//	<Датчик имя="№63 ВЛПДС" нр="63" активен="1" путь="n:\Test\СОУ-2" постфикс="rnpz" удаление="171.1" дельта_давление="0.010" дельта_время="3" />
	//	<Датчик имя="№66 Рязань" нр="66" активен="1" путь="n:\Test\СОУ-2" постфикс="zrnpz" удаление="0" дельта_давление="0.010" дельта_время="2" />
	//</Участок_СОУ>

	std::vector<std::vector<CString>> DivDetectors; // Датчики полученные из XML-файла, которые согласно продукту на Участке можно установить на текущий участок
	//long DIVDET_NUM; // число Датчиков, которые согласно продукту на Участке можно установить на данный участок
	//detnum //detname //detptfix //detdistance //detfilepath //detprodtype //detprodid

	std::vector<std::vector<CString>> DivSortDetectors; // Датчики полученные из XML-файла, которые отсеяны по продукту на Участке, и не содержащие тех датчиков, что уже есть на участке

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()

};

//////////////////////////////////////////////////////////////////
// Проблемы и ошибки и их решения:
// П: 14.11.2014 Нвчало выводиться сообщение о невозможности создания XMLDomDocumetn 
// Р: 18.11.2014 Не хватало вызова: HRESULT hr = CoInitialize(NULL);

extern CSOUGeneratorApp theApp;

