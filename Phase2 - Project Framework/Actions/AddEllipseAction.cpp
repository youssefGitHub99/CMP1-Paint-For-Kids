#include "AddEllipseAction.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "..\Figures\CEllipse.h"


AddEllipseAction::AddEllipseAction(ApplicationManager * pApp) :Action(pApp)
{
}

void AddEllipseAction::ReadActionParameters() {

	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Ellipse: Click at Center");


	pIn->GetPointClicked(center.x, center.y);

	
	EllipseGFXInfo.isFilled = false;	//default is not filled


	EllipseGFXInfo.DrawClr = pOut->getCrntDrawColor();
	EllipseGFXInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();
}
void AddEllipseAction::Execute() {
	ReadActionParameters();
	CEllipse * E = new CEllipse(center, EllipseGFXInfo);
	pManager->AddFigure(E);
}

AddEllipseAction::~AddEllipseAction()
{
}
