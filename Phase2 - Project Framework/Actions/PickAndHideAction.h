#pragma once
#include "Action.h"
#include "..\Figures\CFigure.h"


class PickAndHideAction : public Action
{
private:
	int right;
	int wrong;
	int max;
	Point P;
	CFigure* pfig;
	CFigure* preffig;
	ActionType act;
	ActionType Mode;


public:
	PickAndHideAction(ApplicationManager *pApp, ActionType mode);
	virtual void ReadActionParameters();
	virtual void Execute();
	void reset();
	void init();
	void score();
	~PickAndHideAction();


};

