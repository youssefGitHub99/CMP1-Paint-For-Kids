#pragma once
#include "Action.h"
class AddCircleAction:public Action
{
	Point center;
	GfxInfo CircleGFXInfo;

public:
	AddCircleAction(ApplicationManager * pApp);
	
	virtual void ReadActionParameters();
	virtual void Execute();

	~AddCircleAction();
};

