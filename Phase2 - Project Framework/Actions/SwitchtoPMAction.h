#pragma once
#include "Action.h"

class SwitchtoPMAction : public Action {
public:
	SwitchtoPMAction(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	~SwitchtoPMAction();
};
