#include "AddCircleAction.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "..\Figures\CCircle.h"


AddCircleAction::AddCircleAction(ApplicationManager * pApp):Action(pApp)
{
	soundPath = "Sounds\\Figure_Circle.wav";
}

void AddCircleAction::ReadActionParameters() {

	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Circle: Click at Center");


	pIn->GetPointClicked(center.x, center.y);


	CircleGFXInfo.isFilled = false;	//default is not filled


	CircleGFXInfo.DrawClr = pOut->getCrntDrawColor();
	CircleGFXInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();
}
void AddCircleAction::Execute() {
	ReadActionParameters();
	CCircle * C = new CCircle(center, CircleGFXInfo);
	pManager->AddFigure(C);
}

AddCircleAction::~AddCircleAction()
{
}
