#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>


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

class SaveLoadUtility
{
	SaveLoadUtility(); // Making an instance of this class makes no sense. (private constructor)

public:
	
	static std::string fileDialog(FileDialogType type);
	
};
