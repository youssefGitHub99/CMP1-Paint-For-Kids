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