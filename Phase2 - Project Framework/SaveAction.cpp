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
	string path = SaveLoadUtility::fileDialog(DIALOG_SAVE);
	cout << path;

	pOutputFileStream = new ofstream(path);
	/// Should check the extension first.
	/// If the user selects a file with the wrong extension, we should output an ERROR to the status bar.
	/// If the path doesn't end with an extension. we should add the proper extenstion to the end.
	if (!pOutputFileStream->is_open())
		cout << "Unable to open file";
	else {
		// If the file already exists, it overwrites it (Deletes everything in the file and write the new lines).  
		// If not, it creates a new one.
		/// DEPENDING ON THE SAVE_TYPE, translate all CFigures into text thatt follows the given format.
		*pOutputFileStream << "This is a line.\n";
		*pOutputFileStream << "This is another line.\n";
		pOutputFileStream->close();
	}
}

void SaveAction::Execute() {
	ReadActionParameters();

}