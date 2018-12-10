#pragma once
#include "../Action.h"
#include "SaveLoadUtility.h"
#include "../../ApplicationManager.h"
#include <fstream>

class LoadAction : public Action
{
	
	ifstream* pInputFileStream;
	bool managedToOpen;

	FileLinesFormat getLineFormat(int i, WordType figureType);
	WordType getWordType(int lineCounter, int wordCounter);
	void getWordRange(int& min, int& max);

public:
	LoadAction(ApplicationManager * pApp);
	~LoadAction();

	//Reads rectangle parameters
	virtual void ReadActionParameters();

	//Add rectangle to the ApplicationManager
	virtual void Execute();
};

