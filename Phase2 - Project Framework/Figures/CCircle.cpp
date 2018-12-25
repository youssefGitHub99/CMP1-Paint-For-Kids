#include "CCircle.h"

CCircle::CCircle(Point center, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo) {
	this->center = center;
}
void CCircle::getCenter(Point & p1)const {
	p1 = center;
}

void CCircle::Draw(Output * pOut)const {
	if (!Hidden)
	{
		pOut->DrawCir(center, FigGfxInfo, Selected, factor);
		pOut->DrawOrigin(center);
	}
}
bool CCircle::isInside(Point click){
	float D = getDistance(click, center);
	if (D > 16 * INITIALFACTOR * factor)
		return false;
	else true;




}

bool CCircle::sametype(CFigure* p)
{
	return (dynamic_cast<CCircle*>(p) != NULL);
}
string CCircle::String()
{
	return "Circle";
}