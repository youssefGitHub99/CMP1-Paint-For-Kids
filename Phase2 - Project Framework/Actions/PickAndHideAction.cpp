#include "PickAndHideAction.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <random>
#include <string>
#include <iostream>
using namespace std;

PickAndHideAction::PickAndHideAction(ApplicationManager *pApp, ActionType mode) :Action(pApp)
{
	right = 0;
	wrong = 0;
	Mode = mode;
	preffig = NULL;
	init();
	if (preffig != NULL)
		score();
	pfig = NULL;
	act = EMPTY;

}

void PickAndHideAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pIn->GetPointClicked(P.x, P.y);
	act = pIn->GetActionByPt(P.x, P.y);
	pfig = pManager->GetFigure(P.x, P.y);
	score();

}
void PickAndHideAction::Execute() 
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	while (act != EXIT && act != TO_DRAW && right != max)
	{
		ReadActionParameters();
		if (act == FIGURE_PICK_BY_TYPE && Mode == FIGURE_PICK_BY_COLOR)
		{
			Mode = act;
			reset();
			init();
		}
		else if (act == FIGURE_PICK_BY_TYPE)
		{
			reset();
		}
		else if (act == FIGURE_PICK_BY_COLOR && Mode == FIGURE_PICK_BY_TYPE)
		{
			Mode = act;
			reset();
			init();
		}
		else if (act == FIGURE_PICK_BY_COLOR)
		{
			reset();
		}
		else if (pfig)
		{
			if (Mode == FIGURE_PICK_BY_TYPE)
			{
				if (preffig->sametype(pfig))
					right++;
					
				else
					wrong++;
			}
			else
			{
				if (preffig->sameFillClr(pfig)) 
					right++;
				else
					wrong++;
			}
			pfig->hide();
			pfig = NULL;
			pManager->UpdateInterface();
		
		}
		else
			pOut->PrintMessage("");
		score();
	}
	if (right == max)
		pOut->PrintMessage("YOU WON! right:" + to_string(right) + " wrong:" + to_string(wrong));
	pManager->UnhideAll();
	pManager->UpdateInterface();
}

void PickAndHideAction::reset()
{
	right = 0;
	wrong = 0;
	pManager->UnhideAll();
	pManager->UpdateInterface();
}

void PickAndHideAction::init() 
{
	if (pManager->getFigCount() != 0) //problem otherwise with the dis parameters
	{
		random_device rd;  //Will be used to obtain a seed for the random number engine
		mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		uniform_int_distribution<> dis(0, pManager->getFigCount() - 1);
		preffig = pManager->GetFigure(dis(gen));
		max = (Mode == FIGURE_PICK_BY_TYPE) ? pManager->nmFigSameTypeAs(preffig) : pManager->numFigSameFillClrAs(preffig);
	}
	else max = 0;
}

void PickAndHideAction::score()
{
	Output* pOut = pManager->GetOutput();
	ostringstream outclr;
	outclr << "right:" << right << " " << "wrong:" << wrong << " " << "select all " << preffig->FillClr() << " " << "Click Draw or Exit to stop";
	ostringstream outtype;
	outtype << "right:" << right << " " << "wrong:" << wrong << " " << "select all " << preffig->String() << "s " << "Click Draw or Exit to stop";

	string out = (Mode == FIGURE_PICK_BY_TYPE) ? outtype.str() : outclr.str();
	pOut->PrintMessage(out);


}
PickAndHideAction::~PickAndHideAction(){}
