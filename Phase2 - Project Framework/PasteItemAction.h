#pragma once
#include "Actions/Action.h"
class PasteItemAction :public Action
{
	Point p;
	int mode;
public:
	PasteItemAction(ApplicationManager * pApp, int m);
	virtual void Execute();
	virtual void ReadActionParameters();
	~PasteItemAction();
};

