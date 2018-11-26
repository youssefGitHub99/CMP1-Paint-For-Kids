#include "SaveLoadUtility.h"

using namespace std;

SaveLoadUtility::SaveLoadUtility()
{

}

string SaveLoadUtility::fileDialog(FileDialogType type) {
	const int BUFSIZE = 1024;
	char buffer[BUFSIZE] = { 0 };
	OPENFILENAME ofns = { 0 };
	ofns.lStructSize = sizeof(ofns);
	ofns.lpstrFile = buffer;
	ofns.nMaxFile = BUFSIZE;
	if (type == DIALOG_OPEN) {
		ofns.lpstrTitle = "Open";
		GetOpenFileName(&ofns);
	} else {
		ofns.lpstrTitle = "Save";
		GetSaveFileName(&ofns);
	}
	return buffer;
}

