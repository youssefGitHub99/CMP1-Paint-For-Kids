#pragma once
#include "Action.h"

class SwitchtoDMAction : public Action {
public:
	SwitchtoDMAction(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	~SwitchtoDMAction();
};
