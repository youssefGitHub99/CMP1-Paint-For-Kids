#pragma once
#include "Action.h"
class AddEllipseAction :public Action
{
	Point center;
	GfxInfo EllipseGFXInfo;

public:
	AddEllipseAction(ApplicationManager * pApp);

	virtual void ReadActionParameters();
	virtual void Execute();

	~AddEllipseAction();
};

