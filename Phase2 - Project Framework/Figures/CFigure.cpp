#include "CFigure.h"

CFigure::CFigure(GfxInfo FigureGfxInfo)
{
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	Hidden = false;

	factor = 1;
}

int CFigure::getId() const { return ID; }

float CFigure::getDistance(Point p1, Point p2) {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

void CFigure::SetSelected(bool s)
{
	Selected = s;
}


float CFigure::TriangleArea(float x1, float y1, float x2, float y2, float x3, float y3) {
	return abs((x1*(y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
}

bool CFigure::IsSelected() const
{
	return Selected;
}

void CFigure::ChngDrawClr(color Dclr)
{
	FigGfxInfo.DrawClr = Dclr;
}

void CFigure::setId(int id) {
	ID = id;
}
void CFigure::ChngFillClr(color Fclr)
{
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr;
}

GfxInfo CFigure::getGfxInfo() const {
	return FigGfxInfo;
}

double CFigure::getFactor() {
	return factor;
}

void CFigure::setFactor(double factor) {
	this->factor = factor;
}

void CFigure::hide() {
	Hidden = true;
}
void CFigure::unhide() {
	Hidden = false;
}
bool CFigure::hidden(){
	return Hidden;
}


bool CFigure::sameFillClr(CFigure* p)
{
	return FigGfxInfo.FillClr == p->getGfxInfo().FillClr && FigGfxInfo.isFilled == p->getGfxInfo().isFilled ;
}
string CFigure::FillClr()
{
	bool filled = FigGfxInfo.isFilled;
	color c = FigGfxInfo.FillClr;
	if (!filled)
		return "Not filled";
	else
	{
		if (c == BLACK)
			return "Black";
		else if (c == WHITE)
			return "White";
		else if (c == RED)
			return "RED";
		else if (c == GREEN)
			return "GREEN";
		else 
			return "BLUE";

	}
}