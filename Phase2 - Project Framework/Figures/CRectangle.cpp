#include "CRectangle.h"

CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;

	//factor = 2;
}
	
void CRectangle::getTranslatedPoints(Point & p1, Point & p2)const {
	Point corner2Translated;
	corner2Translated.x = POINTFACTORTRANSLATED_X_SQRT(Corner1.x, Corner2.x, factor);
	corner2Translated.y = POINTFACTORTRANSLATED_Y_SQRT(Corner1.y, Corner2.y, factor);

	p1 = Corner1;
	p2 = corner2Translated;


}
void CRectangle::getOriginalPoints(Point & p1, Point & p2) const
{
	p1 = Corner1;
	p2 = Corner2;
}
void CRectangle::SetNewLocation(const Point &p1, const Point &p2) {

	Corner1 = p1;
	Corner2 = p2;


}

void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawRect(Corner1, Corner2, FigGfxInfo,IsCut,Selected,factor);
	pOut->DrawOrigin(Corner1);
}

bool CRectangle::isInside(Point click) {
	Point p1;
	Point p2;
	p1 = Corner1;
	p2 = Corner2;
	if (click.x >= min(p1.x, p2.x) && click.x <= max(p1.x, p2.x) && click.y >= min(p1.y, p2.y) && click.y <= max(p1.y, p2.y))
		return true;
	else
		return false;


}