#pragma once
#include <cmath>

#include "ApplicationManager.h"
#include "Actions\AddRectAction.h"
#include "Actions\AddLineAction.h"
#include "Actions\AddCircleAction.h"
#include "Actions\AddEllipseAction.h"
#include "Actions\AddTriangleAction.h"
#include "Actions\AddRhombusAction.h"
#include "Actions/SelectItemAction.h"
#include "Actions/ChangeColorAction.h"
#include "Figures/CLine.h"
#include "Figures/CTriangle.h"
#include "Figures/CEllipse.h"
#include "Figures/CCircle.h"
#include "Figures/CRectangle.h"
#include "Figures/CRhombus.h"
using namespace std;

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();

	FigCount = 0;

	//Create an array of figure pointers and set them to NULL		
	for (int i = 0; i < MaxFigCount; i++)
		FigList[i] = NULL;
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;

	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
	case SELECT_FIGURE:
		pAct = new SelectItemAction(this);
		break;
	case DRAW_RHOMBUS:
		pAct = new AddRhombusAction(this);
		break;
	case DRAW_TRI:
		pAct = new AddTriangleAction(this);
		break;
	case DRAW_ELLIPSE:
		pAct = new AddEllipseAction(this);
		break;
	case DRAW_CIRCLE:
		pAct = new AddCircleAction(this);
		break;
	case LOAD:
		//pAct = new LoadAction(this);
		break;
	case SAVE:
		//pAct = new SaveAction(this, SAVE_TYPE_ALL);
		break;
	case DRAW_RECT:
		pAct = new AddRectAction(this);
		break;
	case CHNG_DRAW_CLR:
		pOut->CreateColorToolBar();
		UI.InterfaceMode = COLOR;
		UI.ColorInterface = DRAWING_COLOR;
		break;
	case CHNG_FILL_CLR:
		pOut->CreateColorToolBar();
		UI.InterfaceMode = COLOR;
		UI.ColorInterface = FILL_COLOR;
		break;
	case COLOR_BLACK:
		pAct = new ChangeColorAction(this, UI.ColorInterface,0);
		break;
	case COLOR_RED:
		pAct = new ChangeColorAction(this, UI.ColorInterface,1);
		break;
	case COLOR_GREEN:
		pAct = new ChangeColorAction(this, UI.ColorInterface,2);
		break;
	case COLOR_WHITE:
		pAct = new ChangeColorAction(this, UI.ColorInterface,3);
		break;
	case COLOR_BLUE:
		pAct = new ChangeColorAction(this, UI.ColorInterface,4);
		break;
	case BACK_TO_DRAW:
		pOut->CreateDrawToolBar();
		UI.InterfaceMode = MODE_DRAW;
		UI.ColorInterface =DRAWING_COLOR;
		break;
	case DRAW_LINE:
		///create AddLineAction here
		pAct = new AddLineAction(this);
		break;
	case DEL:
		deleteSelectedFigure();
		break;

	case EXIT:
		///create ExitAction here

		break;

	case STATUS:	//a click on the status bar ==> no action
		return;
	}

	//Execute the created action
	if (pAct != NULL)
	{
		pAct->Execute(); //Execute
		delete pAct;	 //Action is not needed any more ==> delete it
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if (FigCount < MaxFigCount){
		FigList[FigCount++] = pFig;
		FigList[FigCount - 1]->setId(FigCount - 1);
	}
}

void ApplicationManager::removeSelection() {
	Output * pOut = GetOutput();
	for (int i = 0; i<FigCount; i++)
		if (FigList[i]->IsSelected()) {
			FigList[i]->SetSelected(false);
		}
}

CFigure * ApplicationManager::GetSelectedFigure()const{
	for (int i = 0; i < FigCount; i++)
		if (FigList[i]->IsSelected())
			return FigList[i];

	return NULL;
}

void ApplicationManager::deleteSelectedFigure() {
	CFigure * c = GetSelectedFigure();
	if (c == NULL) {
		Output * pOut = GetOutput();
		pOut->PrintMessage("Please select a figure first ");
	
	}
	else {
		Output * pOut = GetOutput();
		int id = c->getId();
		delete FigList[id];
		FigList[id] = FigList[FigCount-1];
		FigList[FigCount - 1] = NULL;
		FigCount--;
		pOut->ClearDrawArea();
		UpdateInterface();

	}
}
////////////////////////////////////////////////////////////////////////////////////

float TriangleArea(float x1, float y1, float x2, float y2, float x3, float y3) {
	return abs((x1*(y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
}


float getDistance(Point p1, Point p2) {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}


CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL
	Point click;
	click.x = x;
	click.y = y;
	
	for (int i = FigCount; i >= 0; i--) {
		if (dynamic_cast<CLine *>(FigList[i]) != NULL){
			Point p1, p2;
			dynamic_cast<CLine *>(FigList[i])->getPoints(p1,p2);
			float d1 = getDistance(click,p1);
			float d2 = getDistance(click, p2);
			float d = getDistance(p1,p2);
			if ((d1 + d2) <= d*1.0001)
				return FigList[i];
		}
		
		
		else if (dynamic_cast<CCircle *>(FigList[i]) != NULL) {
			Point center;
			dynamic_cast<CCircle *>(FigList[i])->getPoints(center);
			int factor =dynamic_cast<CCircle *>(FigList[i])->getFactor();
			float D = getDistance(click,center);
			if (D > 16 * factor)
				continue;
			else
				return FigList[i];
			
		}
		
		
		else if (dynamic_cast<CRectangle *>(FigList[i]) != NULL) {
			Point p1;
			Point p2;
			dynamic_cast<CRectangle *>(FigList[i])->getPoints(p1, p2);
			if (click.x >= min(p1.x, p2.x) && click.x <= max(p1.x, p2.x) && click.y >= min(p1.y, p2.y) && click.y <= max(p1.y, p2.y))
				return FigList[i];
			else
				continue;
		}
		
		
		else if (dynamic_cast<CTriangle *>(FigList[i]) != NULL) {
			Point p1;
			Point p2;
			Point p3;
			dynamic_cast<CTriangle *>(FigList[i])->getPoints(p1, p2, p3);
			float D1, D2, D3;
			D1 = getDistance(click, p1);
			D2 = getDistance(click, p2);
			D3 = getDistance(click, p3);
			float L12,L13,L23;
			L12 = getDistance(p1, p2);
			L23 = getDistance(p2, p3);
			L13 = getDistance(p3, p1);
			

			float A1 = TriangleArea(click.x ,click.y , p1.x ,p1.y ,p2.x ,p2.y);
			float A2 = TriangleArea(click.x, click.y, p2.x, p2.y, p3.x, p3.y);
			float A3 = TriangleArea(click.x, click.y, p1.x, p1.y, p3.x, p3.y);
			float A = TriangleArea(p3.x, p3.y, p1.x, p1.y, p2.x, p2.y);
			if (A == A1 + A2 + A3)
				return FigList[i];
			else
				continue;
		}
		
		
		else if (dynamic_cast<CRhombus *>(FigList[i]) != NULL) {
			Point center;
			dynamic_cast<CRhombus *>(FigList[i])->getPoints(center);
			Point p1, p2, p3, p4;
			p1.x = center.x;
			p1.y = center.y + (int)16 * dynamic_cast<CRhombus *>(FigList[i])->getFactor();
			p3.x = center.x;
			p3.y = center.y - (int)16 * dynamic_cast<CRhombus *>(FigList[i])->getFactor();
			p2.y = center.y;
			p2.x = center.x + (int)16 * dynamic_cast<CRhombus *>(FigList[i])->getFactor();
			p4.y = center.y;
			p4.x = center.x - (int)16 * dynamic_cast<CRhombus *>(FigList[i])->getFactor();
			
			bool inside1 = false;
			bool inside2 = false;

			float A1 = TriangleArea(click.x, click.y, p1.x, p1.y, p2.x, p2.y);
			float A2 = TriangleArea(click.x, click.y, p2.x, p2.y, p4.x, p4.y);
			float A3 = TriangleArea(click.x, click.y, p1.x, p1.y, p4.x, p4.y);
			float A = TriangleArea(p4.x, p4.y, p1.x, p1.y, p2.x, p2.y);
			if (A == A1 + A2 + A3)
				inside1 = true;
			
			A1 = TriangleArea(click.x, click.y, p4.x, p4.y, p2.x, p2.y);
			A2 = TriangleArea(click.x, click.y, p2.x, p2.y, p3.x, p3.y);
			A3 = TriangleArea(click.x, click.y, p4.x, p4.y, p3.x, p3.y);
			A = TriangleArea(p3.x, p3.y, p4.x, p4.y, p2.x, p2.y);
			if (A == A1 + A2 + A3)
				inside2 = true;
			

			if (inside1 || inside2)
				return FigList[i];
			else
				continue;



		}
		
		
		
		//else if (dynamic_cast<CEllipse *>(FigList[i]) != NULL) {}

	
	}



	//Add your code here to search for a figure given a point x,y	
	//Remember that ApplicationManager only calls functions do NOT implement it.

	return NULL;
}



//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	for (int i = 0; i < FigCount; i++)
		FigList[i]->Draw(pOut);		//Call Draw function (virtual member fn)
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{
	return pIn;
}
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{
	return pOut;
}
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < FigCount; i++)
		delete FigList[i];
	delete pIn;
	delete pOut;

}

