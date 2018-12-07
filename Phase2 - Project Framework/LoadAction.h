#pragma once
#include "Actions/Action.h"
#include "ApplicationManager.h"
#include "SaveLoadUtility.h"
#include <fstream>

class LoadAction : public Action
{
	
	ifstream* pInputFileStream;

public:
	LoadAction(ApplicationManager * pApp);
	~LoadAction();

	//Reads rectangle parameters
	virtual void ReadActionParameters();

	//Add rectangle to the ApplicationManager
	virtual void Execute();
};

