#pragma once
#include "../Action.h"
#include "SaveLoadUtility.h"
#include "../../ApplicationManager.h"
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

