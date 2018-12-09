#include "SaveLoadUtility.h"


using namespace std;

SaveLoadUtility::SaveLoadUtility()
{

}

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
	if (type == DIALOG_OPEN) {
		ofns.lpstrTitle = "Open";
		GetOpenFileName(&ofns);
	} else {
		ofns.lpstrTitle = "Save";
		GetSaveFileName(&ofns);
	}
	return buffer;
}

string SaveLoadUtility::fileDialog(FileDialogType type) { // https://www.github.com/Microsoft/Windows-classic-samples/blob/master/Samples/Win7Samples/winui/shell/appplatform/commonfiledialog/CommonFileDialogApp.cpp
	// CoCreate the File Open Dialog object.
	string path;
	IFileDialog *pfd = NULL;
	HRESULT hr;
	if (type == DIALOG_OPEN) hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));
	else hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));
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
	//return hr;
	return path;
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

void SaveLoadUtility::colorsIntoKeywords(GfxInfo gfxInfo, ReservedKeywords& drawColor, ReservedKeywords& fillColor) {
	drawColor = SaveLoadUtility::colorIntoKeyword(gfxInfo.DrawClr);
	fillColor = KEYWORD_NO_FILL;

	if (gfxInfo.isFilled)
		fillColor = SaveLoadUtility::colorIntoKeyword(gfxInfo.FillClr);
}

ofstream& operator<<(ofstream& output, CLine& line) {
	Point p1;
	Point p2;
	line.getPoints(p1, p2);

	ReservedKeywords c = SaveLoadUtility::colorIntoKeyword(line.getGfxInfo().DrawClr);

	output
		<< KEYWORD_LINE << ' '
		<< line.getId() << ' '
		<< p1.x << ' '
		<< p1.y << ' '
		<< p2.x << ' '
		<< p2.y << ' '
		<< c
		<< '\n';

	return output;
}

ofstream& operator<<(ofstream& output, CRectangle& rect) {
	Point p1, p2;
	rect.getPoints(p1, p2);

	ReservedKeywords drawColor, fillColor;
	SaveLoadUtility::colorsIntoKeywords(rect.getGfxInfo(), drawColor, fillColor);

	output
		<< KEYWORD_RECT << ' '
		<< rect.getId() << ' '
		<< p1.x << ' '
		<< p1.y << ' '
		<< p2.x << ' '
		<< p2.y << ' '
		<< drawColor << ' '
		<< fillColor
		<< '\n';

	return output;
}

ofstream& operator<<(ofstream& output, CTriangle& tri) {
	Point p1, p2, p3;
	tri.getPoints(p1, p2, p3);

	ReservedKeywords drawColor, fillColor;
	SaveLoadUtility::colorsIntoKeywords(tri.getGfxInfo(), drawColor, fillColor);

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
		<< fillColor
		<< '\n';

	return output;
}

ofstream& operator<<(ofstream& output, CRhombus& rho) {
	Point p1;
	rho.getPoints(p1);

	ReservedKeywords drawColor, fillColor;
	SaveLoadUtility::colorsIntoKeywords(rho.getGfxInfo(), drawColor, fillColor);

	output
		<< KEYWORD_RHOMBUS << ' '
		<< rho.getId() << ' '
		<< p1.x << ' '
		<< p1.y << ' '
		<< drawColor << ' '
		<< fillColor
		<< '\n';

	return output;
}

ofstream& operator<<(ofstream& output, CCircle& circ) {
	Point p1;
	circ.getPoints(p1);

	ReservedKeywords drawColor, fillColor;
	SaveLoadUtility::colorsIntoKeywords(circ.getGfxInfo(), drawColor, fillColor);

	output
		<< KEYWORD_CIRCLE << ' '
		<< circ.getId() << ' '
		<< p1.x << ' '
		<< p1.y << ' '
		<< drawColor << ' '
		<< fillColor
		<< '\n';

	return output;
}

ofstream& operator<<(ofstream& output, CEllipse& elli) {
	Point p1;
	elli.getPoints(p1);

	ReservedKeywords drawColor, fillColor;
	SaveLoadUtility::colorsIntoKeywords(elli.getGfxInfo(), drawColor, fillColor);

	output
		<< KEYWORD_ELLIPSE << ' '
		<< elli.getId() << ' '
		<< p1.x << ' '
		<< p1.y << ' '
		<< drawColor << ' '
		<< fillColor
		<< '\n';

	return output;
}

FileLinesFormat SaveLoadUtility::currentLineFormat(int i) {
	if (i < 2)
		return FileLinesFormat(i);
	else
		return FileLinesFormat(2);
}