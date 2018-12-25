#include "SwitchtoDMAction.h"

#include "..\ApplicationManager.h"

#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

SwitchtoDMAction::SwitchtoDMAction(ApplicationManager * pApp) :Action(pApp) {}
void SwitchtoDMAction::ReadActionParameters() {}





void SwitchtoDMAction::Execute() {
	Output* pOut = pManager->GetOutput();
	pOut->CreateDrawToolBar();
	pOut->ClearStatusBar();
}

SwitchtoDMAction::~SwitchtoDMAction() {}