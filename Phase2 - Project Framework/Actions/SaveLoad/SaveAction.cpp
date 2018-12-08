#include "SaveAction.h"

SaveAction::SaveAction(ApplicationManager * pApp, SaveType saveType) : Action(pApp), saveType(saveType)
{
	
}

SaveAction::~SaveAction()
{
	if (pOutputFileStream != NULL)
		delete pOutputFileStream;
}

void SaveAction::ReadActionParameters() {
	managedToOpen = false;
	//--------------------------------------------------------------------------------------------------------------------
	string path = SaveLoadUtility::fileDialog(DIALOG_SAVE);
	if (path.empty()) return;
	//--------------------------------------------------------------------------------------------------------------------
	/// Should check the extension first.
	CheckExtensionProbabilities checkExtension = SaveLoadUtility::checkExtension(path);
	if (checkExtension == NOT_TXT)
		pManager->GetOutput()->PrintMessage("Wrong Extension.");	/// If the user selects a file with the wrong extension, we should output an ERROR to the status bar.
	else if (checkExtension == NO_EXTENSION) {
		pManager->GetOutput()->PrintMessage("File Created And Saved.");
		path.append(".txt"); /// If the path doesn't end with an extension. we should add the proper extenstion to the end.
	} else {
		pManager->GetOutput()->PrintMessage("File Overwriten.");
	}
	cout << path;

	//--------------------------------------------------------------------------------------------------------------------
	pOutputFileStream = new ofstream(path);
	if (!pOutputFileStream->is_open() | checkExtension == NOT_TXT) 
		cout << "Unable to open file"; 
	else
		managedToOpen = true;
}

void SaveAction::Execute() {
	ReadActionParameters();

	if (!managedToOpen) return;

	/// DEPENDING ON THE SAVE_TYPE, translate all CFigures into text thatt follows the given format.
	int figCount = pManager->getFigCount();
	*pOutputFileStream << figCount << '\n';

	for (int i = 0; i < figCount; i++) {
		CFigure* figure = pManager->GetFigure(i);

		CLine*		line =	dynamic_cast<CLine*>(figure);
		CRectangle* rect =	dynamic_cast<CRectangle*>(figure);
		CTriangle*	tri  =	dynamic_cast<CTriangle*>(figure);
		CRhombus*	rho  =	dynamic_cast<CRhombus*>(figure);
		CCircle*	circ =	dynamic_cast<CCircle*>(figure);
		CEllipse*	elli =	dynamic_cast<CEllipse*>(figure);

		if		(line != NULL & (saveType == SAVE_TYPE_ALL | saveType == SAVE_TYPE_LINE))	*pOutputFileStream << *line;
		else if (rect != NULL & (saveType == SAVE_TYPE_ALL | saveType == SAVE_TYPE_RECT))	*pOutputFileStream << *rect;
		else if (tri  != NULL & (saveType == SAVE_TYPE_ALL | saveType == SAVE_TYPE_TRI))	*pOutputFileStream << *tri;
		else if (rho  != NULL & (saveType == SAVE_TYPE_ALL | saveType == SAVE_TYPE_RHOMBUS))*pOutputFileStream << *rho;
		else if (circ != NULL & (saveType == SAVE_TYPE_ALL | saveType == SAVE_TYPE_CIRCLE))	*pOutputFileStream << *circ;
		else if (elli != NULL & (saveType == SAVE_TYPE_ALL | saveType == SAVE_TYPE_ELLIPSE))*pOutputFileStream << *elli;
	}

	pOutputFileStream->close();
	delete pOutputFileStream;
}



