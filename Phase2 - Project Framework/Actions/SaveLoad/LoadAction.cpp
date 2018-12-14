#include "LoadAction.h"
#define CLF(lineCounter) getLineFormat(lineCounter)

#define DELETEFIGUREWORDS(figureWords) {\
	if (figureWords != NULL)\
		delete[] figureWords;\
}

#define INVALIDFILE(out, figureWords); {\
	out->PrintMessage("Invalid File.");\
	DELETEFIGUREWORDS(figureWords)\
	return false;\
}

#define IFINVALIDWORDINVALIDFILE(wordFloat, type, out, figureWords) {\
	if (!validateWord(wordFloat, type)){\
		INVALIDFILE(out, figureWords);\
	}\
}

LoadAction::LoadAction(ApplicationManager * pApp) : Action(pApp)
{
	pInputFileStream = NULL;
}


LoadAction::~LoadAction()
{
	if (pInputFileStream != NULL)
		delete pInputFileStream;
}

void LoadAction::ReadActionParameters() {
	managedToOpen = false;
	//--------------------------------------------------------------------------------------------------------------------

	string path(SaveLoadUtility::fileDialogOld(DIALOG_OPEN));
	//string path(SaveLoadUtility::fileDialog(DIALOG_OPEN));
	if (path.empty()) return; // If the user pressed cancel, it returns an empty string.
	cout << "\n------------LOAD------------ " << path << " ------------LOAD------------\n";

	//--------------------------------------------------------------------------------------------------------------------
	/// Should check the extension first.
	CheckExtensionProbabilities checkExtension = SaveLoadUtility::checkExtension(path);
	if (checkExtension != TXT) {
		pManager->GetOutput()->PrintMessage("Wrong File Type."); /// If the user selects a file with the wrong extension, we should output an ERROR to the status bar.
		return;
	}
	//--------------------------------------------------------------------------------------------------------------------

	pInputFileStream = new ifstream(path);
	if (!pInputFileStream->is_open())
		cout << "\ncannot open " << path << " for input." << endl;
	else 
		managedToOpen = true;
}

void LoadAction::Execute() {
	ReadActionParameters();

	/// 1 - Translate the file into CFigures. [Check If the file follows the correct format ... If not Print "Invalid File" to the status bar]
	/// 2 - Delete All The existing CFigures as well as the clipboard (if != NULL).
	/// 3 - Initialize a new CFigures array and a new empty clipboard.
	/// 4 - if (currentMode == PLAY_MODE) switchToDrawMode();
	/// 5 - call load() located in each element of the newly created CFiguers Array [pManager->LoadAll()].

	if (managedToOpen) {

		CFigure* loadedFigures[MAXFIGCOUNT];
		for (int i = 0; i < MAXFIGCOUNT; i++) {
			loadedFigures[i] = NULL;
		}


		if (!readAndValidateFile(loadedFigures))
			return;

		replaceOldFigsWithNew(loadedFigures);

		/*string word;
		while (*pInputFileStream >> word) {
			
			cout << word << ' ';
		}*/
	}

	if (pInputFileStream != NULL) {				  
		pInputFileStream->close();				  
		delete pInputFileStream;				  
		pInputFileStream = NULL;				  
	}
}

FileLinesFormat LoadAction::getLineFormat(int lineCounter, float firstWordInLine) {
	if (lineCounter < LINE_FIG_TYPE_MIN_INDEX)
		return FileLinesFormat(lineCounter);
	else
		return getFigureFromLine(firstWordInLine);
}

FileLinesFormat LoadAction::getFigureFromLine(float firstWordInLine) {
	//if (validateWord(firstWordInLine, FIGURE)) {
	if (firstWordInLine == KEYWORD_LINE) return LINE_LINE;
	if (firstWordInLine == KEYWORD_RECT) return LINE_RECT;
	if (firstWordInLine == KEYWORD_TRI) return LINE_TRI;
	if (firstWordInLine == KEYWORD_RHOMBUS) return LINE_RHOMBUS;
	if (firstWordInLine == KEYWORD_CIRCLE) return LINE_CIRCLE;
	if (firstWordInLine == KEYWORD_ELLIPSE) return LINE_ELLIPSE;
	//}
}

bool LoadAction::validateWord(float currentWord, WordType correctType) {
	if (correctType == RESIZE_FACTOR) {
		if (currentWord == 0.25 |
			currentWord == 0.5 |
			currentWord == 1 |
			currentWord == 2 |
			currentWord == 4)
			return true;
		else {
			cout << "ERROR : RESIZE_FACTOR isn't supported.";
			return false;
		}
	}


	int min, max;
	getWordRangeExclusive(correctType, min, max);
	
	if (currentWord > min && currentWord < max)
		return true;

	cout << endl << "ERROR : Word out of range.";
	return false;
}

void LoadAction::setLineDescription(FileLinesFormat lineFormat, const WordType*& descriptionArr, int& arrSize) {
	if (lineFormat == LINE_DRAWCOLOR_FILLCOLOR) {
		descriptionArr = &SaveLoadUtility::lineDrawColorFillColorDescription[0];
		arrSize = LDCFCDS;
		cout << "(LINE_DRAWCOLOR_FILLCOLOR) ";
	}
	else if (lineFormat == LINE_FIGURES_COUNT) {
		descriptionArr = &SaveLoadUtility::lineFiguresCountDescription[0];
		arrSize = LFCDS;
		cout << "(LINE_FIGURES_COUNT) ";
	}
	else if (lineFormat == LINE_LINE) {
		descriptionArr = &SaveLoadUtility::lineLineDescription[0];
		arrSize = LLDS;
		cout << "(LINE_LINE) ";
	}
	else if (lineFormat == LINE_RECT) {
		descriptionArr = &SaveLoadUtility::lineRectDescription[0];
		arrSize = LRectDS;
		cout << "(LINE_RECT) ";
	}
	else if (lineFormat == LINE_TRI) {
		descriptionArr = &SaveLoadUtility::lineTriDescription[0];
		arrSize = LTDS;
		cout << "(LINE_TRI) ";
	}
	else if (lineFormat == LINE_RHOMBUS) {
		descriptionArr = &SaveLoadUtility::lineRhombusDescription[0];
		arrSize = LRhoDS;
		cout << "(LINE_RHOMBUS) ";
	}
	else if (lineFormat == LINE_CIRCLE) {
		descriptionArr = &SaveLoadUtility::lineCircleDescription[0];
		arrSize = LCDS;
		cout << "(LINE_CIRCLE) ";
	}
	else if (lineFormat == LINE_ELLIPSE) {
		descriptionArr = &SaveLoadUtility::lineEllipseDescription[0];
		arrSize = LEDS;
		cout << "(LINE_ELLIPSE) ";
	}
}

void LoadAction::getWordRangeExclusive(WordType type, int& min, int& max) {
	if (type == INTEGER) {
		min = -1; // Exclusive
		max = INT16_MAX + 1;
	}
	else if (type == COLOR) {
		min = KEYWORD_COLOR_MIN_INDEX;
		max = KEYWORD_COLOR_MAX_INDEX;
	}
	else if (type == FIGURE) {
		min = KEYWORD_SHAPES_MIN_INDEX;
		max = KEYWORD_SHAPES_MAX_INDEX;
	}
	else if (type == MAXFIGNUM) {
		min = 0;
		max = MAXFIGCOUNT + 1;
	}
}

bool LoadAction::getCorrectWordType(int wordCounter, const WordType* descriptionArr, int size, WordType& type) {
	if (wordCounter < size) {
		type = descriptionArr[wordCounter];
		return true;
	}
	else {
		cout << endl << "ERROR : Num of words in this line is more than expected.";
		return false;
	}

}

void LoadAction::translateFigureWords(const float* figureWords, CFigure** loadedFigures, int& currentLoadedFiguresIndex) {
	Point p1, p2, p3;
	GfxInfo info;

	if (figureWords[0] == KEYWORD_LINE) {
		p1.x = figureWords[2];
		p1.y = figureWords[3];
		p2.x = figureWords[4];
		p2.y = figureWords[5];

		info.isFilled = false;
		info.DrawClr = SaveLoadUtility::keywordIntoColor((ReservedKeywords) (int) figureWords[6]);
		/// TODO : Add Resize Factor

		CLine* line = new CLine(p1, p2, info);
		loadedFigures[currentLoadedFiguresIndex] = line;
	}
	else if (figureWords[0] == KEYWORD_RECT) {
		p1.x = figureWords[2];
		p1.y = figureWords[3];
		p2.x = figureWords[4];
		p2.y = figureWords[5];

		info.isFilled = true ? (figureWords[7] != KEYWORD_NO_FILL) : false;
		info.DrawClr = SaveLoadUtility::keywordIntoColor((ReservedKeywords) (int) figureWords[6]);;
		if (info.isFilled) info.FillClr = SaveLoadUtility::keywordIntoColor((ReservedKeywords) (int) figureWords[7]);;
		/// TODO : Add Resize Factor

		CRectangle* rect = new CRectangle(p1, p2, info);
		loadedFigures[currentLoadedFiguresIndex] = rect;
	}
	else if (figureWords[0] == KEYWORD_TRI) {
		p1.x = figureWords[2];
		p1.y = figureWords[3];
		p2.x = figureWords[4];
		p2.y = figureWords[5];
		p3.x = figureWords[6];
		p3.y = figureWords[7];


		info.isFilled = true ? (figureWords[9] != KEYWORD_NO_FILL) : false;
		info.DrawClr = SaveLoadUtility::keywordIntoColor((ReservedKeywords) (int) figureWords[8]);;
		if (info.isFilled) info.FillClr = SaveLoadUtility::keywordIntoColor((ReservedKeywords) (int) figureWords[9]);;
		/// TODO : Add Resize Factor

		CTriangle* tri = new CTriangle(p1, p2, p3, info);
		loadedFigures[currentLoadedFiguresIndex] = tri;
	}
	else if (figureWords[0] == KEYWORD_RHOMBUS) {
		p1.x = figureWords[2];
		p1.y = figureWords[3];

		info.isFilled = true ? (figureWords[5] != KEYWORD_NO_FILL) : false;
		info.DrawClr = SaveLoadUtility::keywordIntoColor((ReservedKeywords) (int) figureWords[4]);;
		if (info.isFilled) info.FillClr = SaveLoadUtility::keywordIntoColor((ReservedKeywords) (int) figureWords[5]);;
		/// TODO : Add Resize Factor

		CRhombus* rho = new CRhombus(p1, info);
		loadedFigures[currentLoadedFiguresIndex] = rho;
	}
	else if (figureWords[0] == KEYWORD_CIRCLE) {
		p1.x = figureWords[2];
		p1.y = figureWords[3];

		info.isFilled = true ? (figureWords[5] != KEYWORD_NO_FILL) : false;
		info.DrawClr = SaveLoadUtility::keywordIntoColor((ReservedKeywords) (int) figureWords[4]);;
		if (info.isFilled) info.FillClr = SaveLoadUtility::keywordIntoColor((ReservedKeywords) (int) figureWords[5]);;
		/// TODO : Add Resize Factor

		CCircle* circ = new CCircle(p1, info);
		loadedFigures[currentLoadedFiguresIndex] = circ;
	}
	else if (figureWords[0] == KEYWORD_ELLIPSE) {
		p1.x = figureWords[2];
		p1.y = figureWords[3];

		info.isFilled = true ? (figureWords[5] != KEYWORD_NO_FILL) : false;
		info.DrawClr = SaveLoadUtility::keywordIntoColor((ReservedKeywords) (int) figureWords[4]);;
		if (info.isFilled) info.FillClr = SaveLoadUtility::keywordIntoColor((ReservedKeywords) (int) figureWords[5]);;
		/// TODO : Add Resize Factor

		CRhombus* elli = new CRhombus(p1, info);
		loadedFigures[currentLoadedFiguresIndex] = elli;
	}
	
	currentLoadedFiguresIndex++;
}

void LoadAction::replaceOldFigsWithNew(CFigure** loadedFigures) {
	pManager->setFigCount(0);
	for (int j = 0; j < MAXFIGCOUNT; j++) {
		CFigure* oldFigure = pManager->GetFigure(j);
		if (oldFigure != NULL) {
			delete oldFigure;
			oldFigure = NULL;
		}

		CFigure* loadedFig = loadedFigures[j];
		if (loadedFig != NULL)
			pManager->AddFigure(loadedFig);
	}
	pManager->GetOutput()->ClearDrawArea();
}

bool LoadAction::readAndValidateFile(CFigure** loadedFigures) {	
	Output* pOut = pManager->GetOutput();

	const int maxLines = pManager->getMaxFigCount() + LINE_FIG_TYPE_MIN_INDEX;
	int lineCounter;
	string line;

	FileLinesFormat lineFormat;
	const WordType* lineDescription = NULL;
	int lineDescriptionSize = 0;

	int theNumberOfFiguresThatFileSays = 0;
	int currentLoadedFiguresIndex = 0;

	float* figureWords = NULL;

	for (lineCounter = 0; lineCounter < maxLines; lineCounter++) {
		if (!getline(*pInputFileStream, line)) break;

		//cout << '\n' << line << '\n';

		istringstream iss;
		iss.str(line);
		string word;
		int wordCounter = -1;

		while (iss >> word) {
			wordCounter++;

			float wordFloat;
			try {
				wordFloat = stof(word);
			}
			catch (std::invalid_argument) {
				cout << endl << "ERROR : There's an illegal charachter (Not a number).";
				INVALIDFILE(pOut, figureWords);
			}

			bool firstWordTested = false;
			if (wordCounter == 0) {
				if (lineCounter >= LINE_FIG_TYPE_MIN_INDEX) {
					firstWordTested = true;
					IFINVALIDWORDINVALIDFILE(wordFloat, FIGURE, pOut, figureWords);
				}

				lineFormat = getLineFormat(lineCounter, wordFloat);
				setLineDescription(lineFormat, lineDescription, lineDescriptionSize);

				if (lineFormat == LINE_FIGURES_COUNT) {
					loadedFigures;
					theNumberOfFiguresThatFileSays = wordFloat;
				}
				else if (lineFormat > LINE_FIG_TYPE_MIN_INDEX && lineFormat < LINE_FIG_TYPE_MAX_INDEX) {
					figureWords = new float[lineDescriptionSize];
				}
			}
			else if (wordCounter > lineDescriptionSize - 1) {
				cout << endl << "ERROR : Num of words in this line is more than expected.";
				INVALIDFILE(pOut, figureWords);
			}

			WordType type;
			if (!getCorrectWordType(wordCounter, &lineDescription[0], lineDescriptionSize, type)) {
				INVALIDFILE(pOut, figureWords);
			}

			if (!firstWordTested) {
				IFINVALIDWORDINVALIDFILE(wordFloat, type, pOut, figureWords);
			}

			if (lineFormat > LINE_FIG_TYPE_MIN_INDEX)
				figureWords[wordCounter] = wordFloat;

			cout << word << ' ';
			//cout << wordFloat << ' ';
		}

		if (wordCounter == -1) {
			//INVALIDFILE(pOut, figureWords);
			cout << "____________________ Empty line ____________________";
			lineCounter--;
		}
		else if (wordCounter < lineDescriptionSize - 1) {
			cout << endl << "ERROR : Num of words in this line is fewer than expected.";
			INVALIDFILE(pOut, figureWords);
		}

		if (lineFormat > LINE_FIG_TYPE_MIN_INDEX)
			translateFigureWords(figureWords, loadedFigures, currentLoadedFiguresIndex);

		cout << '\n';
	}

	if (lineCounter - LINE_FIG_TYPE_MIN_INDEX > theNumberOfFiguresThatFileSays) {
		cout << "ERROR : The read figures is more than what the file says.";
		INVALIDFILE(pOut, figureWords);
	}
	else if (lineCounter - LINE_FIG_TYPE_MIN_INDEX < theNumberOfFiguresThatFileSays) {
		cout << "ERROR : The read figures is fewer than what the file says.";
		INVALIDFILE(pOut, figureWords);
	}

	DELETEFIGUREWORDS(figureWords);
}