#include "CLine.h"

CLine::CLine(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	corner1 = P1;
	corner2 = P2;

	//factor = 2;
}

void CLine::getTranslatedPoints(Point & p1, Point & p2)const {
	Point corner2Translated;
	corner2Translated.x = POINTFACTORTRANSLATED_X(corner1.x, corner2.x, factor);
	corner2Translated.y = POINTFACTORTRANSLATED_Y(corner1.y, corner2.y, factor);

	p1 = corner1;
	p2 = corner2Translated;
}

void CLine::getOriginalPoints(Point & p1, Point & p2) const
{
	p1 = corner1;
	p2 = corner2;
}

void CLine::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawLi(corner1, corner2, FigGfxInfo, Selected, factor);
	pOut->DrawOrigin(corner1);
}

bool CLine::isInside(Point click) {
	Point p1, p2;
	float d1 = getDistance(click, p1);
	float d2 = getDistance(click, p2);
	float d = getDistance(p1, p2);
	if ((d1 + d2) <= d * 1.0001)
		return true;
}