#pragma once
#include "Actions/Action.h"
class CopyItemAction :public Action
{
public:
	int mode;
public:
	CopyItemAction(ApplicationManager * pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	~CopyItemAction();
};

