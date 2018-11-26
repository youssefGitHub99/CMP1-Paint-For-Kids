#pragma once
#include "Actions/Action.h"
#include "SaveLoadUtility.h"
#include "ApplicationManager.h"
#include <fstream>

enum SaveType {
	SAVE_TYPE_ALL, 
	SAVE_TYPE_REC,
	SAVE_TYPE_LINE, 
	SAVE_TYPE_TRI, 
	SAVE_TYPE_RHOMBUS, 
	SAVE_TYPE_ELLIPSE, 
	SAVE_TYPE_CIRCLE
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
