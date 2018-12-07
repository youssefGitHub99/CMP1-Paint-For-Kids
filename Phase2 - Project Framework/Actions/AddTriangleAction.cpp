#include "AddTriangleAction.h"
#include "..\Figures\CTriangle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"



AddTriangleAction::AddTriangleAction(ApplicationManager * pApp):Action(pApp)
{
}
void AddTriangleAction::ReadActionParameters()
{
	
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Triangle: Click at first corner");

	pIn->GetPointClicked(p1.x, p1.y);

	pOut->PrintMessage("New Triangle: Click at second corner");

	pIn->GetPointClicked(p2.x, p2.y);

	pOut->PrintMessage("New Triangle: Click at third corner");

	pIn->GetPointClicked(p3.x, p3.y);

	TriangleGfxInfo.isFilled = false;	
	
	TriangleGfxInfo.DrawClr = pOut->getCrntDrawColor();
	TriangleGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

void AddTriangleAction::Execute(){
	ReadActionParameters();

	CTriangle * T = new CTriangle(p1, p2, p3, TriangleGfxInfo);
	pManager->AddFigure(T);

}