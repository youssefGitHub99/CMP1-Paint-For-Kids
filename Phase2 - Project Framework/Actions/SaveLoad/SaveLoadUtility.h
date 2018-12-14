#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include "../../Figures/CLine.h"
#include "../../Figures/CRectangle.h"
#include "../../Figures/CTriangle.h"
#include "../../Figures/CRhombus.h"
#include "../../Figures/CCircle.h"
#include "../../Figures/CEllipse.h"

// The following inclusions and definitions are from :
/////////////////// https://www.github.com/Microsoft/Windows-classic-samples/blob/master/Samples/Win7Samples/winui/shell/appplatform/commonfiledialog/CommonFileDialogApp.cpp ///////////////////
/////////////////// https://www.github.com/Microsoft/Windows-classic-samples/blob/master/Samples/Win7Samples/winui/shell/appplatform/commonfiledialog/CommonFileDialogApp.cpp ///////////////////

#include <windows.h>      // For common windows data types and function headers
#define STRICT_TYPED_ITEMIDS
#include <shlobj.h>
#include <objbase.h>      // For COM headers
#include <shobjidl.h>     // for IFileDialogEvents and IFileDialogControlEvents
#include <shlwapi.h>
#include <knownfolders.h> // for KnownFolder APIs/datatypes/function headers
#include <propvarutil.h>  // for PROPVAR-related functions
#include <propkey.h>      // for the Property key APIs/datatypes
#include <propidl.h>      // for the Property System APIs
#include <strsafe.h>      // for StringCchPrintfW
#include <shtypes.h>      // for COMDLG_FILTERSPEC
#include <new>

const COMDLG_FILTERSPEC c_rgSaveTypes[] =
{
	//{L"Word Document (*.doc)",       L"*.doc"},
	//{L"Web Page (*.htm; *.html)",    L"*.htm;*.html"},
	{L"Text Document (*.txt)",       L"*.txt"},
	//{L"All Documents (*.*)",         L"*.*"}
};

//// Indices of file types
//#define INDEX_WORDDOC 1
//#define INDEX_WEBPAGE 2
//#define INDEX_TEXTDOC 3
//
//// Controls
//#define CONTROL_GROUP           2000
//#define CONTROL_RADIOBUTTONLIST 2
//#define CONTROL_RADIOBUTTON1    1
//#define CONTROL_RADIOBUTTON2    2       // It is OK for this to have the same ID as CONTROL_RADIOBUTTONLIST,
//										// because it is a child control under CONTROL_RADIOBUTTONLIST
//
//// IDs for the Task Dialog Buttons
//#define IDC_BASICFILEOPEN                       100
//#define IDC_ADDITEMSTOCUSTOMPLACES              101
//#define IDC_ADDCUSTOMCONTROLS                   102
//#define IDC_SETDEFAULTVALUESFORPROPERTIES       103
//#define IDC_WRITEPROPERTIESUSINGHANDLERS        104
//#define IDC_WRITEPROPERTIESWITHOUTUSINGHANDLERS 105

enum ReservedKeywords {
	KEYWORD_COLOR_MIN_INDEX, 

	KEYWORD_RED, 
	KEYWORD_GREEN, 
	KEYWORD_BLUE, 
	KEYWORD_BLACK, 
	KEYWORD_WHITE, 
	KEYWORD_NO_FILL, 

	KEYWORD_COLOR_MAX_INDEX, 

	KEYWORD_SHAPES_MIN_INDEX, 

	KEYWORD_LINE, 
	KEYWORD_RECT, 
	KEYWORD_TRI, 
	KEYWORD_RHOMBUS, 
	KEYWORD_CIRCLE, 
	KEYWORD_ELLIPSE, 

	KEYWORD_SHAPES_MAX_INDEX, 
};

enum FileDialogType {
	DIALOG_OPEN, 
	DIALOG_SAVE
};

enum CheckExtensionProbabilities {
	NO_EXTENSION,
	NOT_TXT, 
	TXT
};


///////////////////////////////////////////////////////
enum FileLinesFormat{
	LINE_DRAWCOLOR_FILLCOLOR, 
	LINE_FIGURES_COUNT, 

	LINE_FIG_TYPE_MIN_INDEX,

	LINE_LINE,
	LINE_RECT,
	LINE_TRI,
	LINE_RHOMBUS,
	LINE_CIRCLE,
	LINE_ELLIPSE, 

	LINE_FIG_TYPE_MAX_INDEX
};

enum WordType {
	MAXFIGNUM, 
	INTEGER, // Position
	COLOR, 
	FIGURE, 
	RESIZE_FACTOR
};
///////////////////////////////////////////////////////

//lineDrawColorFillColorDescription Size
#define LDCFCDS 2
//lineFiguresCountDescription Size
#define LFCDS 1
//lineLineDescription Size
#define LLDS 8
//lineRectDescription Size
#define LRectDS 9
//lineTriDescription Size
#define LTDS 11
//lineRhombusDescription Size
#define LRhoDS 7
//lineCircleDescription Size
#define LCDS 7
//lineEllipseDescription Size
#define LEDS 7

class SaveLoadUtility
{
	SaveLoadUtility(); // Creating an instance of this class makes no sense. (private constructor)

	static std::string wstrtostr(const std::wstring &wstr); 

public:

	static const WordType lineDrawColorFillColorDescription[LDCFCDS];
	static const WordType lineFiguresCountDescription[LFCDS];
	static const WordType lineLineDescription[LLDS];
	static const WordType lineRectDescription[LRectDS];
	static const WordType lineTriDescription[LTDS];
	static const WordType lineRhombusDescription[LRhoDS];
	static const WordType lineCircleDescription[LCDS];
	static const WordType lineEllipseDescription[LEDS];

	
	static std::string fileDialogOld(FileDialogType type);
	static string fileDialog(FileDialogType type);
	static ReservedKeywords colorIntoKeyword(color c);
	static color keywordIntoColor(ReservedKeywords keyword);
	static CheckExtensionProbabilities checkExtension(std::string& path);
};
