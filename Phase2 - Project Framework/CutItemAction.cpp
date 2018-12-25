#include "CutItemAction.h"
#include "CutItemAction.h"
#include "ApplicationManager.h"
#include<string>
#include "GUI\input.h"
#include "GUI\Output.h"


CutItemAction::CutItemAction(ApplicationManager * pApp) :Action(pApp)
{
	mode = Cut;
}
void CutItemAction::ReadActionParameters() {}
void CutItemAction::Execute() {

	Output* pOut = pManager->GetOutput();
	CFigure * c = pManager->GetSelectedFigure();
	if (c == NULL)
	{
		pOut->PrintMessage("Please select a figure first. ");
	}
	else {
		pManager->SetClipboardData(c, mode);
	}



}


CutItemAction::~CutItemAction()
{
}
