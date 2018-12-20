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
#include "Actions/ResizeAction.h"
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

	soundMuted = false;

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
	case DRAW_LINE:
		///create AddLineAction here
		pAct = new AddLineAction(this);
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
		pAct = new LoadAction(this);
		break;
	case SAVE:
		pAct = new SaveAction(this, SAVE_TYPE_ALL);
		break;
	case SAVE_BY_TYPE:
		pOut->CreateSaveByTypeToolBar();
		break;
	case SAVE_LINE:
		pAct = new SaveAction(this, SAVE_TYPE_LINE);
		break;
	case SAVE_RECT:
		pAct = new SaveAction(this, SAVE_TYPE_RECT);
		break;
	case SAVE_TRI:
		pAct = new SaveAction(this, SAVE_TYPE_TRI);
		break;
	case SAVE_RHOMBUS:
		pAct = new SaveAction(this, SAVE_TYPE_RHOMBUS);
		break;
	case SAVE_CIRCLE:
		pAct = new SaveAction(this, SAVE_TYPE_CIRCLE);
		break;
	case SAVE_ELLISPE:
		pAct = new SaveAction(this, SAVE_TYPE_ELLIPSE);
		break;
	case DRAW_RECT:
		pAct = new AddRectAction(this);
		break;
	case CHNG_DRAW_CLR:
		pOut->CreateColorToolBar();
		UI.ColorInterface = DRAWING_COLOR;
		break;
	case CHNG_FILL_CLR:
		pOut->CreateColorToolBar();
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
	case RESIZE_SHAPE:
		pOut->CreateResizeToolBar();
		break;
	case RESIZE_QUARTER:
		pAct = new ResizeAction(this, 0.25);
		break;
	case RESIZE_HALF:
		pAct = new ResizeAction(this, 0.5);
		break;
	case RESIZE_ORIGINAL:
		pAct = new ResizeAction(this, 1);
		break;
	case RESIZE_DOUBLE:
		pAct = new ResizeAction(this, 2);
		break;
	case RESIZE_FOUR_TIMES:
		pAct = new ResizeAction(this, 4);
		break;
	case DEL:
		deleteSelectedFigure();
		break;
	case MUTE:
		soundMuted = true;
		pOut->PrintMessage("Sound is now muted.");
		break;
	case UNMUTE:
		soundMuted = false;
		pOut->PrintMessage("Sound is now working.");
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
		
		playSound(pAct);

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

int ApplicationManager::getFigCount() const {
	return FigCount;
}

void ApplicationManager::setFigCount(int figCount) {
	this->FigCount = figCount;
}

int ApplicationManager::getMaxFigCount() const {
	return MaxFigCount;
}

CFigure* ApplicationManager::GetFigure(int index) const {
	return FigList[index];
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
		for (int i = id; i < FigCount-1;i++) {
			FigList[i] = FigList[i+1];
		}
		FigList[FigCount - 1] = NULL;
		FigCount--;
		for (int i = 0; i < FigCount; i++) {
			FigList[i]->setId(i);
		}
		pOut->ClearDrawArea();
		UpdateInterface();
	}
}

void ApplicationManager::playSound(Action* pAct) {
	if (soundMuted) return;

	if (pAct->getSoundPath() != NULL)
		sndPlaySound(*pAct->getSoundPath(), SND_FILENAME | SND_ASYNC);
}

bool ApplicationManager::aFigureMustBeSelectedFirst(CFigure *& selectedFigure)
{
	if (GetSelectedFigure() == NULL) {
		pOut->PrintMessage("Please select a figure first.");
		return false;
	}

	selectedFigure = GetSelectedFigure();
	return true;
}
////////////////////////////////////////////////////////////////////////////////////



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
	
	for (int i = FigCount-1; i >= 0; i--) {
		bool check = FigList[i]->isInside(click);
		if (check)
			return FigList[i];
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

