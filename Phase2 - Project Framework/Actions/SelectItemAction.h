#pragma once
#include "Action.h"
class SelectItemAction:public Action
{
	Point p1;

public:
	SelectItemAction(ApplicationManager * pApp);
	virtual void Execute();
	virtual void ReadActionParameters();
	
	~SelectItemAction();
};

