#include "LoadAction.h"


LoadAction::LoadAction(ApplicationManager * pApp) : Action(pApp)
{
}


LoadAction::~LoadAction()
{
	if (pInputFileStream != NULL)
		delete pInputFileStream;
}

void LoadAction::ReadActionParameters() {
	string path(SaveLoadUtility::fileDialog(DIALOG_OPEN));
	cout << path;

	pInputFileStream = new ifstream(path);
	if (!pInputFileStream->is_open()) {
		cout << "\ncannot open " << path << " for input" << endl;
		///Print To status bar that it couldn't open the file.
	} else {
		// The next alogrithm reads the file line by line.
		string line;
		while (getline(*pInputFileStream, line))
		{
			cout << '\n' << line;
		}
		pInputFileStream->close();
	}

	/// 1 - Translate the file into CFigures. [Check If the file follows the correct format ... If not Print "Invalid File" to the status bar]
	/// 2 - Delete All The existing CFigures as well as the clipboard (if != NULL).
	/// 3 - Initialize a new CFigures array and a new empty clipboard.
}

void LoadAction::Execute() {
	ReadActionParameters();

	/// 4 - if (currentMode == PLAY_MODE) switchToDrawMode();
	/// 5 - call load() located in each element of the newly created CFiguers Array [pManager->LoadAll()].
}