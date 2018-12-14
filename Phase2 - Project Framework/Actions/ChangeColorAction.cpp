#include "ChangeColorAction.h"
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

ChangeColorAction::ChangeColorAction(ApplicationManager * pApp, int mode, int mcolor) :Action(pApp)
{
	this->mode = mode;
	this->mcolor = mcolor;
}

void ChangeColorAction::ReadActionParameters() {}
void ChangeColorAction::Execute() {
	CFigure * c = pManager->GetSelectedFigure();
	if (c == NULL) 
	{
		Output* pOut = pManager->GetOutput();
		pOut->PrintMessage("please select a figure first ");
	}
	else 
	{
		Output* pOut = pManager->GetOutput();
		
		if (mode == 0) 
		{
			switch (mcolor)
			{
			case 0:
				c->ChngFillClr(BLACK);
				soundPath = "Sounds\\Color_Black.wav";
				break;
			case 1:
				c->ChngFillClr(RED);
				soundPath = "Sounds\\Color_Red.wav";
				break;
			case 2:
				c->ChngFillClr(GREEN);
				soundPath = "Sounds\\Color_Green.wav";
				break;
			case 3:
				c->ChngFillClr(WHITE);
				soundPath = "Sounds\\Color_White.wav";
				break;
			case 4:
				c->ChngFillClr(BLUE);
				soundPath = "Sounds\\Color_Blue.wav";
				break;
			default:
				break;
			}
		}
		else if (mode == 1) 
		{
			switch (mcolor)
			{
			case 0:
				
				c->ChngDrawClr(BLACK);
				soundPath = "Sounds\\Color_Black.wav";
				break;
			case 1:
				c->ChngDrawClr(RED);
				soundPath = "Sounds\\Color_Red.wav";
				break;
			case 2:
				c->ChngDrawClr(GREEN);
				soundPath = "Sounds\\Color_Green.wav";
				break;
			case 3:
				c->ChngDrawClr(WHITE);
				soundPath = "Sounds\\Color_White.wav";
				break;
			case 4:
				c->ChngDrawClr(BLUE);
				soundPath = "Sounds\\Color_Blue.wav";
				break;
			default:
				break;
			}
		}

		}


	}




ChangeColorAction::~ChangeColorAction()
{
}
