#include "CLine.h"

CLine::CLine(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	point1 = P1;
	point2 = P2;

	//factor = 2;
}

void CLine::getTranslatedPoints(Point & p1, Point & p2)const {
	Point corner2Translated;
	corner2Translated.x = POINTFACTORTRANSLATED_X(point1.x, point2.x, factor);
	corner2Translated.y = POINTFACTORTRANSLATED_Y(point1.y, point2.y, factor);

	p1 = point1;
	p2 = corner2Translated;
}

void CLine::getOriginalPoints(Point & p1, Point & p2) const
{
	p1 = point1;
	p2 = point2;
}

void CLine::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	if (!Hidden)
	{
		pOut->DrawLi(point1, point2, FigGfxInfo, Selected, factor);
		pOut->DrawOrigin(point1);
	}
}

bool CLine::isInside(Point click) {
	Point p1 = point1;
	Point p2 = point2;
	float d1 = getDistance(click, p1);
	float d2 = getDistance(click, p2);
	float d = getDistance(p1, p2);
	if ((d1 + d2) <= d * 1.0001)
		return true;
	return false;
}

bool CLine::sametype(CFigure* p)
{
	return (dynamic_cast<CLine*>(p) != NULL);
}
string CLine::String()
{
	return "Line";
}