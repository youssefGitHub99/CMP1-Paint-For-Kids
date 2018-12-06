#pragma once
#include "Action.h"

class ChangeColorAction:public Action
{
	int mode;
	int mcolor;

public:
	virtual void Execute();
	virtual void ReadActionParameters();

	ChangeColorAction(ApplicationManager * pApp,int mode, int mcolor);
	~ChangeColorAction();
};

