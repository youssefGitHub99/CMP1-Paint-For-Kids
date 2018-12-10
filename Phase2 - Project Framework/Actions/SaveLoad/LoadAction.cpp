#include "LoadAction.h"
#define CLF(lineCounter) getLineFormat(lineCounter)
#define INVALIDFILE(out) out->PrintMessage("Invalid File.")

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
	if (path.empty()) return; // If the user pressed cancel, it returns an empty string.

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
		const int maxLines = pManager->getMaxFigCount() + 2;
		int lineCounter;
		string line;
		for (lineCounter = 0; lineCounter < maxLines; lineCounter++) {
			if (!getline(*pInputFileStream, line)) break;
			
			//cout << '\n' << line << '\n';
			Output* pOut = pManager->GetOutput();

			istringstream iss(line);
			string word;
			int wordCounter = 0;
			while (iss >> word) {
				wordCounter++;

				if (CLF(lineCounter) == LINE_DRAWCOLOR_FILLCOLOR) {
					if (wordCounter > 2) {
						INVALIDFILE(pOut);
						return;
					}
				} else if (CLF(lineCounter) == LINE_FIGURES_COUNT) {
					if (wordCounter > 1) {
						INVALIDFILE(pOut);
						return;
					}
				}

				float wordFloat;
				try {
					wordFloat = stof(word);
				} catch (std::invalid_argument) {
					INVALIDFILE(pOut);
					return;
				}
				cout << wordFloat << ' ';
				//cout << word << ' ';
			}

			if (wordCounter == 0) {
				INVALIDFILE(pOut);
				return;
			}

			cout << '\n';
		}

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

FileLinesFormat LoadAction::getLineFormat(int i, WordType figureType) {
	if (i < 2)
		return FileLinesFormat(i);
	else if (LINE_FIG_TYPE_MIN_INDEX < figureType < LINE_FIG)
		return FileLinesFormat(2);
}