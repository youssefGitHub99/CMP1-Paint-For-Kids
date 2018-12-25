#pragma once
#include "Action.h"
class BringFrontSendBackAction :public Action
{
	int mode;
public:
	BringFrontSendBackAction(ApplicationManager * pApp, int m);

	virtual void ReadActionParameters();
	virtual void Execute();

	~BringFrontSendBackAction();
};