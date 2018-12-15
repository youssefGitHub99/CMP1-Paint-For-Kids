#include "SaveLoadUtility.h"


using namespace std;

SaveLoadUtility::SaveLoadUtility()
{

}

const WordType SaveLoadUtility::lineDrawColorFillColorDescription[] = { COLOR, COLOR };
const WordType SaveLoadUtility::lineFiguresCountDescription[] = { MAXFIGNUM };
const WordType SaveLoadUtility::lineLineDescription[] = { FIGURE, INTEGER, INTEGER, INTEGER, INTEGER, INTEGER, COLOR, RESIZE_FACTOR };
const WordType SaveLoadUtility::lineRectDescription[] = { FIGURE, INTEGER, INTEGER, INTEGER, INTEGER, INTEGER, COLOR, COLOR, RESIZE_FACTOR };
const WordType SaveLoadUtility::lineTriDescription[] = { FIGURE, INTEGER, INTEGER, INTEGER, INTEGER, INTEGER, INTEGER, INTEGER, COLOR, COLOR, RESIZE_FACTOR };
const WordType SaveLoadUtility::lineRhombusDescription[] = { FIGURE, INTEGER, INTEGER, INTEGER, COLOR, COLOR, RESIZE_FACTOR };
const WordType SaveLoadUtility::lineCircleDescription[] = { FIGURE, INTEGER, INTEGER, INTEGER, COLOR, COLOR, RESIZE_FACTOR };
const WordType SaveLoadUtility::lineEllipseDescription[] = { FIGURE, INTEGER, INTEGER, INTEGER, COLOR, COLOR, RESIZE_FACTOR };

string SaveLoadUtility::fileDialogOld(FileDialogType type) { // http://www.cplusplus.com/forum/windows/169960/
	const int BUFSIZE = 1024;
	char buffer[BUFSIZE] = { 0 };
	OPENFILENAME ofns = { 0 };
	ZeroMemory(&buffer, sizeof(buffer));
	ZeroMemory(&ofns, sizeof(ofns));
	ofns.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
	ofns.lStructSize = sizeof(ofns);
	ofns.lpstrFile = buffer;
	ofns.nMaxFile = BUFSIZE;
	ofns.lpstrFilter = "Text Files (*.txt)\0*.txt\0";
	ofns.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST | OFN_CREATEPROMPT;

	// A solution to the previous problem adressed in commit 59788d4267a2b73950dbb8d630eacaa13fa969ed https://stackoverflow.com/questions/50468051/how-to-prevent-getopenfilename-from-changing-the-current-directory-while-the-dia
	TCHAR g_BackupDir[MAX_PATH];
	GetCurrentDirectory(ARRAYSIZE(g_BackupDir), g_BackupDir);
	////////////////////////////

	if (type == DIALOG_OPEN) {
		ofns.lpstrTitle = "Open";
		GetOpenFileName(&ofns);
	} else {
		ofns.lpstrTitle = "Save";
		GetSaveFileName(&ofns);
	}

	SetCurrentDirectory(g_BackupDir);
	return buffer;
}

string SaveLoadUtility::fileDialog(FileDialogType type) { // https://www.github.com/Microsoft/Windows-classic-samples/blob/master/Samples/Win7Samples/winui/shell/appplatform/commonfiledialog/CommonFileDialogApp.cpp
	// CoCreate the File Open Dialog object.
	string path;
	IFileDialog *pfd = NULL;
	HRESULT hr;
	if (type == DIALOG_OPEN) hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));
	else hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));

	//pfd->SetOptions(OFN_NOCHANGEDIR); Does basically nothing;
	TCHAR g_BackupDir[MAX_PATH];
	GetCurrentDirectory(ARRAYSIZE(g_BackupDir), g_BackupDir);
	
	if (SUCCEEDED(hr))
	{
//		// Create an event handling object, and hook it up to the dialog.
//		IFileDialogEvents *pfde = NULL;
		//hr = CDialogEventHandler_CreateInstance(IID_PPV_ARGS(&pfde));
		//if (SUCCEEDED(hr))
		//{
//			// Hook up the event handler.
//			DWORD dwCookie;
//			hr = pfd->Advise(pfde, &dwCookie);
//			if (SUCCEEDED(hr))
//			{
//				// Set the options on the dialog.
//				DWORD dwFlags;
//
//				// Before setting, always get the options first in order not to override existing options.
//				hr = pfd->GetOptions(&dwFlags);
//				if (SUCCEEDED(hr))
//				{
//					// In this case, get shell items only for file system items.
//					hr = pfd->SetOptions(dwFlags | FOS_FORCEFILESYSTEM);
//					if (SUCCEEDED(hr))
//					{
//						// Set the file types to display only. Notice that, this is a 1-based array.
						hr = pfd->SetFileTypes(ARRAYSIZE(c_rgSaveTypes), c_rgSaveTypes);
						if (SUCCEEDED(hr))
						{
							// Set the selected file type index to Word Docs for this example.
							/*hr = pfd->SetFileTypeIndex(INDEX_WORDDOC);
							if (SUCCEEDED(hr))
							{*/
								// Set the default extension to be ".doc" file.
								/*hr = pfd->SetDefaultExtension(L"doc");
								if (SUCCEEDED(hr))
								{*/
									// Show the dialog
									hr = pfd->Show(NULL);
									if (SUCCEEDED(hr))
									{
										// Obtain the result, once the user clicks the 'Open' button.
										// The result is an IShellItem object.
										IShellItem *psiResult;
										hr = pfd->GetResult(&psiResult);
										if (SUCCEEDED(hr))
										{
											// We are just going to print out the name of the file for sample sake.
											PWSTR pszFilePath = NULL;
											hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
											path = wstrtostr(pszFilePath);
											/*if (SUCCEEDED(hr))
											{
												TaskDialog(NULL,
													NULL,
													L"CommonFileDialogApp",
													pszFilePath,
													NULL,
													TDCBF_OK_BUTTON,
													TD_INFORMATION_ICON,
													NULL);
												CoTaskMemFree(pszFilePath);
											}*/
											psiResult->Release();
										}
									}
								//}
							//}
						}
//					}
//				}
//				// Unhook the event handler.
//				pfd->Unadvise(dwCookie);
//			}
//			pfde->Release();
		//}
		pfd->Release();
	}
	SetCurrentDirectory(g_BackupDir);
	//return hr;
	return path;
}

bool SaveLoadUtility::is_empty(std::ifstream * pFile) //https://stackoverflow.com/questions/2390912/checking-for-an-empty-file-in-c
{
	return pFile->peek() == std::ifstream::traits_type::eof();
}

std::string SaveLoadUtility::wstrtostr(const std::wstring &wstr) // http://www.cplusplus.com/forum/windows/74644/
{
	std::string strTo;
	char *szTo = new char[wstr.length() + 1];
	szTo[wstr.size()] = '\0';
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, szTo, (int)wstr.length(), NULL, NULL);
	strTo = szTo;
	delete[] szTo;
	return strTo;
}

ReservedKeywords SaveLoadUtility::colorIntoKeyword(color c) {
	if (c == BLACK)
		return KEYWORD_BLACK;
	if (c == WHITE)
		return KEYWORD_WHITE;
	if (c == RED)
		return KEYWORD_RED;
	if (c == GREEN)
		return KEYWORD_GREEN;
	if (c == BLUE)
		return KEYWORD_BLUE;
	throw "The Color Must be BLACK, WHITE, RED, GREEN or BLUE.";
}

color SaveLoadUtility::keywordIntoColor(ReservedKeywords keyword) {
	if (keyword == KEYWORD_BLACK)
		return BLACK;
	if (keyword == KEYWORD_WHITE)
		return WHITE;
	if (keyword == KEYWORD_RED)
		return RED;
	if (keyword == KEYWORD_GREEN)
		return GREEN;
	if (keyword == KEYWORD_BLUE)
		return BLUE;
}

CheckExtensionProbabilities SaveLoadUtility::checkExtension(std::string& path) {
	int dotPosition = path.find_last_of('.');
	// If the string doesn't contain that char, it reterns the greatest possible value for an element of type size_t. this value is stored in "std::string::npos".

	if (dotPosition == std::string::npos)
		return NO_EXTENSION;
	else if (dotPosition + 1 != path.length() - 3)
		return NOT_TXT;
	else if (
		path.at(dotPosition + 1) != 't' |
		path.at(dotPosition + 2) != 'x' |
		path.at(dotPosition + 3) != 't'
		)
		return NOT_TXT;
	return TXT;
}
