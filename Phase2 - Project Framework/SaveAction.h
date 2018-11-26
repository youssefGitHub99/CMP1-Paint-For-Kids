#pragma once
#include "Actions/Action.h"
#include "SaveLoadUtility.h"
#include "ApplicationManager.h"
#include <fstream>

enum SaveType {
	SAVE_ALL, 
	SAVE_REC,
	SAVE_LINE, 
	SAVE_TRI, 
	SAVE_RHOMBUS, 
	SAVE_ELLIPSE, 
	SAVE_CIRCLE
};

class SaveAction : public Action
{

	SaveType saveType;
	ofstream* pOutputFileStream;

public:
	SaveAction(ApplicationManager * pApp, SaveType saveType);
	~SaveAction();

	//Reads rectangle parameters
	virtual void ReadActionParameters();

	//Add rectangle to the ApplicationManager
	virtual void Execute();
};

