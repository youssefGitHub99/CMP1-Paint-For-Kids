#include "SwitchtoPMAction.h"

#include "..\ApplicationManager.h"

#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

SwitchtoPMAction::SwitchtoPMAction(ApplicationManager * pApp) :Action(pApp) {}
void SwitchtoPMAction::ReadActionParameters(){}





void SwitchtoPMAction::Execute() {
	Output* pOut = pManager->GetOutput();
	pOut->CreatePlayToolBar();
}

SwitchtoPMAction::~SwitchtoPMAction(){}