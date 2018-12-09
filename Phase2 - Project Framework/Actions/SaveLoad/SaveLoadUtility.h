#pragma once
#include <windows.h>
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


enum ReservedKeywords {
	KEYWORD_RED, 
	KEYWORD_GREEN, 
	KEYWORD_BLUE, 
	KEYWORD_BLACK, 
	KEYWORD_WHITE, 
	KEYWORD_NO_FILL, 
	KEYWORD_LINE, 
	KEYWORD_RECT, 
	KEYWORD_TRI, 
	KEYWORD_RHOMBUS, 
	KEYWORD_CIRCLE, 
	KEYWORD_ELLIPSE
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

enum FileLinesFormat{
	DRAWCOLOR_FILLCOLOR, 
	FIGURES_COUNT, 
	FIGURES_DESCRIPTION
};

class SaveLoadUtility
{
	SaveLoadUtility(); // Creating an instance of this class makes no sense. (private constructor)

	static void colorsIntoKeywords(GfxInfo gfxInfo, ReservedKeywords& drawColor, ReservedKeywords& fillColor);

public:
	
	static std::string fileDialog(FileDialogType type);
	static CheckExtensionProbabilities checkExtension(std::string& path);
	static ReservedKeywords colorIntoKeyword(color c);

	friend ofstream& operator<<(ofstream& ouput, CLine& line);
	friend ofstream& operator<<(ofstream& ouput, CRectangle& rect);
	friend ofstream& operator<<(ofstream& ouput, CTriangle& tri);
	friend ofstream& operator<<(ofstream& ouput, CRhombus& rho);
	friend ofstream& operator<<(ofstream& ouput, CCircle& circ);
	friend ofstream& operator<<(ofstream& ouput, CEllipse& elli);

	static FileLinesFormat currentLineFormat(int i);
};
