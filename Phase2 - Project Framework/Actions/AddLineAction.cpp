#include "AddlineAction.h"


#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "..\Figures\CLine.h"
AddLineAction::AddLineAction(ApplicationManager * pApp) :Action(pApp) {

}

void AddLineAction::ReadActionParameters() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Line: Click at first point");

	
	pIn->GetPointClicked(p1.x, p1.y);

	pOut->PrintMessage("New Line: Click at second point");

	//Read 2nd corner and store in point P2
	pIn->GetPointClicked(p2.x, p2.y);

	LineGFXInfo.isFilled = false;	//default is not filled
	

	LineGFXInfo.DrawClr = pOut->getCrntDrawColor();
	LineGFXInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();
}


void AddLineAction::Execute() {
	ReadActionParameters();
	CLine * L = new CLine(p1, p2, LineGFXInfo);
	pManager->AddFigure(L);
}

