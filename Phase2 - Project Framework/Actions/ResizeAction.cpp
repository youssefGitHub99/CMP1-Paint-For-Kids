#include "ResizeAction.h"



ResizeAction::ResizeAction(ApplicationManager * pApp, double factor) : Action(pApp)
{
	this->factor = factor;
}

void ResizeAction::ReadActionParameters()
{

}

void ResizeAction::Execute()
{
	CFigure* selectedFigure;
	if (pManager->aFigureMustBeSelectedFirst(selectedFigure)) {
		if (factor == 1) 
			selectedFigure->setFactor(1);
		else 
			selectedFigure->setFactor(
				selectedFigure->getFactor() * factor
			);
	}

	pManager->GetOutput()->ClearDrawArea();
	pManager->UpdateInterface();
}

ResizeAction::~ResizeAction()
{

}
