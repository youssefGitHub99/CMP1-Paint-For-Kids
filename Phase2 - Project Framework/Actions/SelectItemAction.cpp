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
			
			if (dynamic_cast<CLine *>(c) != NULL) {
				Point p1,p2;
				
				dynamic_cast<CLine *>(c)->getPoints(p1,p2);
				int ID = c->getId();
				string m = "a Line , id : " + to_string(ID) + " , first point : (" + to_string(p1.x) + "," + to_string(p1.y) + ")"
					+ " , Second point : (" + to_string(p2.x) + "," + to_string(p2.y) + ")";
				pOut->PrintMessage(m);
			}
			else if (dynamic_cast<CCircle *>(c) != NULL) {
				Point center;
				dynamic_cast<CCircle *>(c)->getPoints(center);
				int ID = c->getId();
				string m = "a Circle , id : "+ to_string(ID) + " , center at : (" + to_string(center.x) + "," + to_string(center.y) + ")";
				pOut->PrintMessage(m);
			}
			else if (dynamic_cast<CRectangle *>(c) != NULL) {
				int ID = c->getId();
				int width,height;
				Point p1, p2;
				dynamic_cast<CRectangle *>(c)->getPoints(p1,p2);
				width = abs(p1.x - p2.x);
				height = abs(p1.y - p2.y);
				string m = "a Circle , id : " + to_string(ID) + " , Width : " + to_string(width) + " , height :"+ to_string(height)
					+ " , Start point : (" + to_string(p1.x) + "," + to_string(p1.y) + ")"
					+ " , End point: (" + to_string(p2.x) + "," + to_string(p2.y) + ")"
					;
				pOut->PrintMessage(m);
		
			}
			else if (dynamic_cast<CTriangle *>(c) != NULL) {
				Point p1,p2,p3;
				dynamic_cast<CTriangle *>(c)->getPoints(p1,p2,p3);
				int ID = c->getId();
				string m = "a Triangle , id : " + to_string(ID)
					+ " , First point : (" + to_string(p1.x) + "," + to_string(p1.y) + ")"
					+ " , Second point : (" + to_string(p2.x) + "," + to_string(p2.y) + ")"
					+ " , Third point : (" + to_string(p3.x) + "," + to_string(p3.y) + ")";
				pOut->PrintMessage(m);
		
			}
			else if (dynamic_cast<CRhombus *>(c) != NULL) {
				Point center;
				dynamic_cast<CRhombus *>(c)->getPoints(center);
				int ID = c->getId();
				string m = "a Rhombus , id : " + to_string(ID) + " , center at : (" + to_string(center.x) + "," + to_string(center.y) + ")";
				pOut->PrintMessage(m);
		
			}
			else if (dynamic_cast<CEllipse *>(c) != NULL) {
				Point center;
				dynamic_cast<CEllipse *>(c)->getPoints(center);
				int ID = c->getId();
				string m = "an Ellipse , id : " + to_string(ID) + " , center at : (" + to_string(center.x) + "," + to_string(center.y) + ")";
				pOut->PrintMessage(m);
			}
	
		}
		}
}

SelectItemAction::~SelectItemAction()
{
}
