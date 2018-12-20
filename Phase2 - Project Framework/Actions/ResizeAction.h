#pragma once
#include "Action.h"
#include "../ApplicationManager.h"



class ResizeAction : public Action
{
	double factor;
public:
	ResizeAction(ApplicationManager * pApp, double factor);

	virtual void ReadActionParameters();
	virtual void Execute();

	~ResizeAction();
};

