#include "CopyItemAction.h"
#include "ApplicationManager.h"
#include<string>
#include "GUI\input.h"
#include "GUI\Output.h"


CopyItemAction::CopyItemAction(ApplicationManager * pApp) :Action(pApp)
{
	mode = Copy;
}
void CopyItemAction::ReadActionParameters() {}
void CopyItemAction::Execute() {

	Output* pOut = pManager->GetOutput();
	CFigure * c = pManager->GetSelectedFigure();
	
	if (c == NULL)
	{

		pOut->PrintMessage("Please select a figure first. ");
	}
	else {

		//c->SetCut(false);
		pManager->SetClipboardData(c, mode);

	}



}



CopyItemAction::~CopyItemAction()
{
}
