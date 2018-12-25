#include "PasteItemAction.h"
#include "ApplicationManager.h"
#include<string>
#include "GUI\input.h"
#include "GUI\Output.h"
#include "Figures\CCircle.h"
#include "Figures\CRhombus.h"
#include "Figures/CTriangle.h"
#include "Figures\CRectangle.h"
#include "Figures/CLine.h"
#include "Figures/CEllipse.h"


PasteItemAction::PasteItemAction(ApplicationManager * pApp, int m) :Action(pApp)
{
	mode = m;
}
void PasteItemAction::ReadActionParameters() {

	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Please click point to paste figure.");
	pIn->GetPointClicked(p.x, p.y);
	pOut->ClearStatusBar();

}
void PasteItemAction::Execute() {

	Output* pOut;
	CFigure* c =pManager->getClipboardData();
	Point p1, p2, p3, center;
	if (mode == NonSelect) {

		pOut = pManager->GetOutput();
		pOut->PrintMessage("Please click select figure then copy or cut.");
	}

	else if (mode == Copy || mode==Cut) {

		ReadActionParameters();

		if (dynamic_cast<CCircle*>(c) != NULL) {


			dynamic_cast<CCircle*>(c)->SetNewLocation(p);
			c->SetSelected(false);
			pManager->AddFigure(c);
			if (mode == Cut) {
				c->SetCut(false);
				pManager->deleteCutFigure();
				pManager->setmode(NonSelect);
				
			}
			else if (mode == Copy) {

				pManager->SetClipboardData(c, mode);
			}


		}
		else if (dynamic_cast<CRectangle*>(c) != NULL) {

			dynamic_cast<CRectangle*>(c)->getOriginalPoints(p1, p2);
			center.x = (p1.x + p2.x) / 2;
			center.y = (p1.y + p2.y) / 2;
			p1.x += (p.x - center.x);
			p1.y += (p.y - center.y);
			p2.x += (p.x - center.x);
			p2.y += (p.y - center.y);
			dynamic_cast<CRectangle*>(c)->SetNewLocation (p1, p2);
			c->SetSelected(false);
			pManager->AddFigure(c);
			if (mode == Cut) {
				c->SetCut(false);
				pManager->deleteCutFigure();
				pManager->setmode(NonSelect);
			}
			else if (mode == Copy) {

				pManager->SetClipboardData(c, mode);
			}

		}
		else if (dynamic_cast<CTriangle*>(c) != NULL) {

			dynamic_cast<CTriangle*>(c)->getOriginalPoints(p1, p2, p3);
			center.x = (p1.x + p2.x + p3.x) / 3;
			center.y = (p1.y + p2.y + p3.y) / 3;
			p1.x += (p.x - center.x);
			p1.y += (p.y - center.y);
			p2.x += (p.x - center.x);
			p2.y += (p.y - center.y);
			p3.x += (p.x - center.x);
			p3.y += (p.y - center.y);
			dynamic_cast<CTriangle*>(c)->SetNewLocation(p1, p2, p3);
			c->SetSelected(false);
			pManager->AddFigure(c);
			if (mode == Cut) {
				c->SetCut(false);
				pManager->deleteCutFigure();
				pManager->setmode(NonSelect);
			}
			else if (mode == Copy) {

				pManager->SetClipboardData(c, mode);
				pManager->setmode(NonSelect);
			}
			
		}
		else if (dynamic_cast<CRhombus*>(c) != NULL) {


			dynamic_cast<CRhombus*>(c)->SetNewLocation(p);
			c->SetSelected(false);
			pManager->AddFigure(c);
			if (mode == Cut) {
				c->SetCut(false);
				pManager->deleteCutFigure();
			}
			else if (mode == Copy) {

				pManager->SetClipboardData(c, mode);
			}


		}
		else if (dynamic_cast<CEllipse*>(c) != NULL) {

			dynamic_cast<CEllipse*>(c)->SetNewLocation(p);
			c->SetSelected(false);
			pManager->AddFigure(c);
			if (mode == Cut) {
				c->SetCut(false);
				pManager->deleteCutFigure();
				pManager->setmode(NonSelect);
			}
			else if (mode == Copy) {

				pManager->SetClipboardData(c, mode);
			}
		}
		else if (dynamic_cast<CLine*>(c) != NULL) {

			dynamic_cast<CLine*>(c)->getOriginalPoints(p1,p2);
			center.x = (p1.x + p2.x) / 2;
			center.y = (p1.y + p2.y) / 2;
			p1.x += (p.x - center.x);
			p1.y += (p.y - center.y);
			p2.x += (p.x - center.x);
			p2.y += (p.y - center.y);
			dynamic_cast<CLine*>(c)->SetNewLocation(p1,p2);
			c->SetSelected(false);
			pManager->AddFigure(c);
			if (mode == Cut) {
				c->SetCut(false);
				pManager->deleteCutFigure();
				pManager->setmode(NonSelect);
			}
			else if (mode == Copy) {

				pManager->SetClipboardData(c, mode);
			}


		}



	}

	else if (mode == NotReadyTopaste) {

		pOut = pManager->GetOutput();
		pOut->PrintMessage("Please click copy or cut.");

	}
}

PasteItemAction::~PasteItemAction()
{
}
