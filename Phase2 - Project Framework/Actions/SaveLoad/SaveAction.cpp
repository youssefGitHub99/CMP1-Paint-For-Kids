#include "SaveAction.h"

SaveAction::SaveAction(ApplicationManager * pApp, SaveType saveType) : Action(pApp), saveType(saveType)
{
	numOfFiguresToSave = 0;
	pOutputFileStream = NULL;
}

SaveAction::~SaveAction()
{
	if (pOutputFileStream != NULL)
		delete pOutputFileStream;
}

void SaveAction::setNumOfFiguresToSave() {
	if (saveType == SAVE_TYPE_ALL)				numOfFiguresToSave = pManager->getFigCount();
	else if (saveType == SAVE_TYPE_LINE)		numOfFiguresToSave = pManager->getNumOf<CLine>();
	else if (saveType == SAVE_TYPE_RECT)		numOfFiguresToSave = pManager->getNumOf<CRectangle>();
	else if (saveType == SAVE_TYPE_TRI)			numOfFiguresToSave = pManager->getNumOf<CTriangle>();
	else if (saveType == SAVE_TYPE_RHOMBUS)		numOfFiguresToSave = pManager->getNumOf<CRhombus>();
	else if (saveType == SAVE_TYPE_CIRCLE)		numOfFiguresToSave = pManager->getNumOf<CCircle>();
	else if (saveType == SAVE_TYPE_ELLIPSE)		numOfFiguresToSave = pManager->getNumOf<CEllipse>();
}

bool SaveAction::dontSaveCuzThereIsNoFigures() {
	Output* pOut = pManager->GetOutput();
	if (numOfFiguresToSave == 0) {
		if (saveType == SAVE_TYPE_ALL) pOut->PrintMessage("There're No Figures To Save.");
		else if (saveType == SAVE_TYPE_LINE) pOut->PrintMessage("There're No Lines To Save.");
		else if (saveType == SAVE_TYPE_RECT) pOut->PrintMessage("There're No Rectangles To Save.");
		else if (saveType == SAVE_TYPE_TRI) pOut->PrintMessage("There're No Triangles To Save.");
		else if (saveType == SAVE_TYPE_RHOMBUS) pOut->PrintMessage("There're No Rhombuses To Save.");
		else if (saveType == SAVE_TYPE_CIRCLE) pOut->PrintMessage("There're No Circles To Save.");
		else if (saveType == SAVE_TYPE_ELLIPSE) pOut->PrintMessage("There're No Ellipses To Save.");
		return true;
	}
	return false;
}

void SaveAction::ReadActionParameters() {
	managedToOpen = false;
	//--------------------------------------------------------------------------------------------------------------------
	
	setNumOfFiguresToSave();
	if (dontSaveCuzThereIsNoFigures()) return;
	
	//--------------------------------------------------------------------------------------------------------------------

	string path = SaveLoadUtility::fileDialog(DIALOG_SAVE);
	if (path.empty()) return; // If the user pressed cancel, it returns an empty string.

	//--------------------------------------------------------------------------------------------------------------------

	/// Should check the extension first.
	Output* pOut = pManager->GetOutput();
	CheckExtensionProbabilities checkExtension = SaveLoadUtility::checkExtension(path);
	if (checkExtension == NOT_TXT) {
		pOut->PrintMessage("Wrong File Type."); /// If the user selects a file with the wrong extension, we should output an ERROR to the status bar.
		return;
	} else if (checkExtension == NO_EXTENSION) {
		pOut->PrintMessage("File Has Been Created And Saved.");
		path.append(".txt"); /// If the path doesn't end with an extension. we should add the proper extenstion to the end.
	} else {
		pOut->PrintMessage("File Has Been Overwriten.");
	}
	cout << path;

	//--------------------------------------------------------------------------------------------------------------------
	pOutputFileStream = new ofstream(path);
	if (!pOutputFileStream->is_open()) 
		cout << "Unable to open file"; 
	else
		managedToOpen = true;
}

void SaveAction::Execute() {
	ReadActionParameters();

	if (managedToOpen) {
		/// Draw color and fill color.
		ReservedKeywords drawColor = SaveLoadUtility::colorIntoKeyword(pManager->GetOutput()->getCrntDrawColor());
		ReservedKeywords fillColor = SaveLoadUtility::colorIntoKeyword(pManager->GetOutput()->getCrntFillColor());
		*pOutputFileStream << drawColor << ' ' << fillColor << '\n';

		/// FigCount
		*pOutputFileStream << numOfFiguresToSave << '\n';

		/// DEPENDING ON THE SAVE_TYPE, translate all CFigures into text thatt follows the given format.
		for (int i = 0; i < numOfFiguresToSave; i++) {
			CFigure* figure = pManager->GetFigure(i);

			CLine*		line = dynamic_cast<CLine*>(figure);
			CRectangle* rect = dynamic_cast<CRectangle*>(figure);
			CTriangle*	tri = dynamic_cast<CTriangle*>(figure);
			CRhombus*	rho = dynamic_cast<CRhombus*>(figure);
			CCircle*	circ = dynamic_cast<CCircle*>(figure);
			CEllipse*	elli = dynamic_cast<CEllipse*>(figure);

			if (line != NULL & (saveType == SAVE_TYPE_ALL | saveType == SAVE_TYPE_LINE))	*pOutputFileStream << *line;
			else if (rect != NULL & (saveType == SAVE_TYPE_ALL | saveType == SAVE_TYPE_RECT))	*pOutputFileStream << *rect;
			else if (tri != NULL & (saveType == SAVE_TYPE_ALL | saveType == SAVE_TYPE_TRI))	*pOutputFileStream << *tri;
			else if (rho != NULL & (saveType == SAVE_TYPE_ALL | saveType == SAVE_TYPE_RHOMBUS))*pOutputFileStream << *rho;
			else if (circ != NULL & (saveType == SAVE_TYPE_ALL | saveType == SAVE_TYPE_CIRCLE))	*pOutputFileStream << *circ;
			else if (elli != NULL & (saveType == SAVE_TYPE_ALL | saveType == SAVE_TYPE_ELLIPSE))*pOutputFileStream << *elli;
		}
	}

	if (pOutputFileStream != NULL) {
		pOutputFileStream->close();
		delete pOutputFileStream;
		pOutputFileStream = NULL;
	}
}



