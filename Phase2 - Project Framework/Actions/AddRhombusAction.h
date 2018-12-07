#pragma once
#include "Action.h"
class AddRhombusAction :public Action
{
	Point center;
	GfxInfo RhombusGFXInfo;

public:
	AddRhombusAction(ApplicationManager * pApp);

	virtual void ReadActionParameters();
	virtual void Execute();

	~AddRhombusAction();
};

