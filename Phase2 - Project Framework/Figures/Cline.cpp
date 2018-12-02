#include "CLine.h"

CLine::CLine(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	corner1 = P1;
	corner2 = P2;
}

void CLine::getPoints(Point & p1, Point & p2)const {
	p1 = corner1;
	p2 = corner2;
}

void CLine::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawLi(corner1, corner2, FigGfxInfo, Selected);
}