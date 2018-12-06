#include "AddRhombusAction.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "..\Figures\CRhombus.h"


AddRhombusAction::AddRhombusAction(ApplicationManager * pApp) :Action(pApp)
{
}

void AddRhombusAction::ReadActionParameters() {

	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Rhombus: Click at Center");


	pIn->GetPointClicked(center.x, center.y);


	RhombusGFXInfo.isFilled = false;	//default is not filled


	RhombusGFXInfo.DrawClr = pOut->getCrntDrawColor();
	RhombusGFXInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();
}
void AddRhombusAction::Execute() {
	ReadActionParameters();
	CRhombus * C = new CRhombus(center, RhombusGFXInfo);
	pManager->AddFigure(C);
}

AddRhombusAction::~AddRhombusAction()
{
}
