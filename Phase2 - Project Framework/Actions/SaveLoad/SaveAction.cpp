#include "SaveAction.h"
#define RESIZEFACTOR 1

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

void SaveAction::ReadActionParameters() {
	managedToOpen = false;
	//--------------------------------------------------------------------------------------------------------------------
	
	setNumOfFiguresToSave();
	if (dontSaveCuzThereIsNoFigures()) return;
	
	//--------------------------------------------------------------------------------------------------------------------
	Output* pOut = pManager->GetOutput();

	string path;
	path = SaveLoadUtility::fileDialogOld(DIALOG_SAVE);
	//path = SaveLoadUtility::fileDialog(DIALOG_SAVE);

	//path = pManager->GetInput()->GetSrting(pOut);
	if (path.empty()) return; // If the user pressed cancel, it returns an empty string.
	cout << "\n-----------SAVE------------- " << path << " -----------SAVE-------------\n";

	//--------------------------------------------------------------------------------------------------------------------

	/// Should check the extension first.
	CheckExtensionProbabilities checkExtension = SaveLoadUtility::checkExtension(path);

	// The following extension checking isn't needed if we're using OPENFILENAME (with filters) or similar stuff that open a file dialogue.
	/*if (checkExtension == NOT_TXT) {
		pOut->PrintMessage("Wrong File Type."); /// If the user selects a file with the wrong extension, we should output an ERROR to the status bar.
		return;
	} else*/ if (checkExtension == NO_EXTENSION) {
		//pOut->PrintMessage("File Has Been Created And Saved.");
		path.append(".txt"); /// If the path doesn't end with an extension. we should add the proper extenstion to the end.
	} /*else {
		pOut->PrintMessage("File Has Been Overwriten.");
	}*/
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
		pManager->removeSelection();

		/// Draw color and fill color.
		ReservedKeywords drawColor = SaveLoadUtility::colorIntoKeyword(pManager->GetOutput()->getCrntDrawColor());
		ReservedKeywords fillColor = SaveLoadUtility::colorIntoKeyword(pManager->GetOutput()->getCrntFillColor());
		*pOutputFileStream << drawColor << ' ' << fillColor << '\n';

		/// FigCount
		*pOutputFileStream << numOfFiguresToSave << '\n';

		/// DEPENDING ON THE SAVE_TYPE, translate all CFigures into text thatt follows the given format.
		int figCount = pManager->getFigCount();
		for (int i = 0; i < figCount; i++) {
			CFigure* figure = pManager->GetFigure(i);

			CLine*		line = dynamic_cast<CLine*>(figure);
			CRectangle* rect = dynamic_cast<CRectangle*>(figure);
			CTriangle*	tri = dynamic_cast<CTriangle*>(figure);
			CRhombus*	rho = dynamic_cast<CRhombus*>(figure);
			CCircle*	circ = dynamic_cast<CCircle*>(figure);
			CEllipse*	elli = dynamic_cast<CEllipse*>(figure);

			if (line != NULL & (saveType == SAVE_TYPE_ALL | saveType == SAVE_TYPE_LINE))	*pOutputFileStream << *line << '\n';
			else if (rect != NULL & (saveType == SAVE_TYPE_ALL | saveType == SAVE_TYPE_RECT))	*pOutputFileStream << *rect << '\n';
			else if (tri != NULL & (saveType == SAVE_TYPE_ALL | saveType == SAVE_TYPE_TRI))	*pOutputFileStream << *tri << '\n';
			else if (rho != NULL & (saveType == SAVE_TYPE_ALL | saveType == SAVE_TYPE_RHOMBUS))*pOutputFileStream << *rho << '\n';
			else if (circ != NULL & (saveType == SAVE_TYPE_ALL | saveType == SAVE_TYPE_CIRCLE))	*pOutputFileStream << *circ << '\n';
			else if (elli != NULL & (saveType == SAVE_TYPE_ALL | saveType == SAVE_TYPE_ELLIPSE))*pOutputFileStream << *elli << '\n';
			/// The resize Factor (To be handled later)

		}
		

		pManager->GetOutput()->PrintMessage("File Has Been Saved.");
	}

	if (pOutputFileStream != NULL) {
		pOutputFileStream->close();
		delete pOutputFileStream;
		pOutputFileStream = NULL;
	}
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

ofstream& operator<<(ofstream& output, CLine& line) {
	Point p1;
	Point p2;
	line.getOriginalPoints(p1, p2);

	ReservedKeywords c = SaveLoadUtility::colorIntoKeyword(line.getGfxInfo().DrawClr);

	output
		<< KEYWORD_LINE << ' '
		<< line.getId() << ' '
		<< p1.x << ' '
		<< p1.y << ' '
		<< p2.x << ' '
		<< p2.y << ' '
		<< c << ' '
		<< line.getFactor();

	return output;
}

ofstream& operator<<(ofstream& output, CRectangle& rect) {
	Point p1, p2;
	rect.getOriginalPoints(p1, p2);

	ReservedKeywords drawColor, fillColor;
	SaveAction::colorsIntoKeywords(rect.getGfxInfo(), drawColor, fillColor);

	output
		<< KEYWORD_RECT << ' '
		<< rect.getId() << ' '
		<< p1.x << ' '
		<< p1.y << ' '
		<< p2.x << ' '
		<< p2.y << ' '
		<< drawColor << ' '
		<< fillColor << ' '
		<< rect.getFactor();

	return output;
}

ofstream& operator<<(ofstream& output, CTriangle& tri) {
	Point p1, p2, p3;
	tri.getOriginalPoints(p1, p2, p3);

	ReservedKeywords drawColor, fillColor;
	SaveAction::colorsIntoKeywords(tri.getGfxInfo(), drawColor, fillColor);

	output
		<< KEYWORD_TRI << ' '
		<< tri.getId() << ' '
		<< p1.x << ' '
		<< p1.y << ' '
		<< p2.x << ' '
		<< p2.y << ' '
		<< p3.x << ' '
		<< p3.y << ' '
		<< drawColor << ' '
		<< fillColor << ' '
		<< tri.getFactor();

	return output;
}

ofstream& operator<<(ofstream& output, CRhombus& rho) {
	Point p1;
	rho.getCenter(p1);

	ReservedKeywords drawColor, fillColor;
	SaveAction::colorsIntoKeywords(rho.getGfxInfo(), drawColor, fillColor);

	output
		<< KEYWORD_RHOMBUS << ' '
		<< rho.getId() << ' '
		<< p1.x << ' '
		<< p1.y << ' '
		<< drawColor << ' '
		<< fillColor << ' '
		<< rho.getFactor();

	return output;
}

ofstream& operator<<(ofstream& output, CCircle& circ) {
	Point p1;
	circ.getCenter(p1);

	ReservedKeywords drawColor, fillColor;
	SaveAction::colorsIntoKeywords(circ.getGfxInfo(), drawColor, fillColor);

	output
		<< KEYWORD_CIRCLE << ' '
		<< circ.getId() << ' '
		<< p1.x << ' '
		<< p1.y << ' '
		<< drawColor << ' '
		<< fillColor << ' '
		<< circ.getFactor();

	return output;
}

ofstream& operator<<(ofstream& output, CEllipse& elli) {
	Point p1;
	elli.getCenter(p1);

	ReservedKeywords drawColor, fillColor;
	SaveAction::colorsIntoKeywords(elli.getGfxInfo(), drawColor, fillColor);

	output
		<< KEYWORD_ELLIPSE << ' '
		<< elli.getId() << ' '
		<< p1.x << ' '
		<< p1.y << ' '
		<< drawColor << ' '
		<< fillColor << ' '
		<< elli.getFactor();

	return output;
}

void SaveAction::SaveAction::colorsIntoKeywords(GfxInfo gfxInfo, ReservedKeywords& drawColor, ReservedKeywords& fillColor) {
	drawColor = SaveLoadUtility::colorIntoKeyword(gfxInfo.DrawClr);
	fillColor = KEYWORD_NO_FILL;

	if (gfxInfo.isFilled)
		fillColor = SaveLoadUtility::colorIntoKeyword(gfxInfo.FillClr);
}

