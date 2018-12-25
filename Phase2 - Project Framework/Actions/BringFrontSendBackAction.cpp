#include "BringFrontSendBackAction.h"
#include "..\ApplicationManager.h"

BringFrontSendBackAction::BringFrontSendBackAction(ApplicationManager* pApp, int m): Action(pApp)
{
	mode = m;
}

void BringFrontSendBackAction::ReadActionParameters(){}

void BringFrontSendBackAction::Execute()
{	
	CFigure* fig;
	if (pManager->aFigureMustBeSelectedFirst(fig))
		if (mode == 0) //Bring to front
		{
			pManager->BringToFront(fig->getId());
			pManager->removeSelection();
		}


		else 
		{
			pManager->SendToBack(fig->getId());
			pManager->removeSelection();
		}

}
BringFrontSendBackAction::~BringFrontSendBackAction() {}