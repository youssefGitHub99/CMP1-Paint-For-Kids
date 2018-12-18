#include "SelectItemAction.h"
#include "..\ApplicationManager.h"
#include<string>
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "..\Figures/CLine.h"
#include "..\Figures/CTriangle.h"
#include "..\Figures/CEllipse.h"
#include "..\Figures/CCircle.h"
#include "..\Figures/CRectangle.h"
#include "..\Figures/CRhombus.h"


SelectItemAction::SelectItemAction(ApplicationManager * pApp):Action(pApp)
{
}

void SelectItemAction::ReadActionParameters()
{

	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Please Select a Shape");

	pIn->GetPointClicked(p1.x, p1.y);


	pOut->ClearStatusBar();

}

void SelectItemAction::Execute() {
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	CFigure * c = pManager->GetFigure(p1.x,p1.y);
	if(c==NULL)
		pManager->removeSelection();
	else{
	if (c->IsSelected())
		pManager->removeSelection();
	else {
		pManager->removeSelection();
		c->SetSelected(true);
		//c->ChngDrawClr(MAGENTA);
		if (dynamic_cast<CLine *>(c) != NULL) {
			pOut->PrintMessage("A Line");
		}
		else if (dynamic_cast<CCircle *>(c) != NULL) {
			Point center;
			dynamic_cast<CCircle *>(c)->getPoints(center);
			int ID = c->getId();
			//string m = "a Circle , id : "+ ID + " center at : (" + center.x + "," + center.y + ")";
			pOut->PrintMessage("A Circle");
		}
		else if (dynamic_cast<CRectangle *>(c) != NULL) {
			pOut->PrintMessage("A Rectangle");
		
		}
		else if (dynamic_cast<CTriangle *>(c) != NULL) {
			pOut->PrintMessage("A Triangle");
		
		}
		else if (dynamic_cast<CRhombus *>(c) != NULL) {
			Point center;
			dynamic_cast<CRhombus *>(c)->getPoints(center);
			pOut->PrintMessage("A Rhombus");
		
		}
		//else if (dynamic_cast<CEllipse *>(c) != NULL) {}
	
	}
	}
}

SelectItemAction::~SelectItemAction()
{
}
