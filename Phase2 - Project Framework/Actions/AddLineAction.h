#pragma once
#include "Action.h"

class AddLineAction :public Action {
private:
	Point p1;
	Point p2;
	GfxInfo LineGFXInfo;
public:
	AddLineAction(ApplicationManager * pApp);

	virtual void ReadActionParameters();

	virtual void Execute();
	



};