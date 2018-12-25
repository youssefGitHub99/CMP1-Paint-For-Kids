#pragma once
#include "Actions/Action.h"
class CutItemAction :public Action
{
	int mode;
public:
	CutItemAction(ApplicationManager * pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	~CutItemAction();
};

