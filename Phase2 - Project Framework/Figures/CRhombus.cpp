#include "CRhombus.h"
#include <cmath>
CRhombus::CRhombus(Point center, GfxInfo figGFXInfo) :CFigure(figGFXInfo)
{
	this->center = center;
}

void CRhombus::Draw(Output * pOut)const {
	if (!Hidden)
	{
		pOut->DrawRh(center, FigGfxInfo, Selected, factor);
		pOut->DrawOrigin(center);
	}

}
void CRhombus::getCenter(Point & p1)const {
	p1 = center;
}


bool CRhombus::isInside(Point click) {
	Point p1, p2, p3, p4;
	p1.x = center.x;
	p1.y = center.y + (int)16 * INITIALFACTOR *factor;
	p3.x = center.x;
	p3.y = center.y - (int)16 * INITIALFACTOR * factor;
	p2.y = center.y;
	p2.x = center.x + (int)16 * INITIALFACTOR * factor;
	p4.y = center.y;
	p4.x = center.x - (int)16 * INITIALFACTOR * factor;

	bool inside1 = false;
	bool inside2 = false;

	float A1 = TriangleArea(click.x, click.y, p1.x, p1.y, p2.x, p2.y);
	float A2 = TriangleArea(click.x, click.y, p2.x, p2.y, p4.x, p4.y);
	float A3 = TriangleArea(click.x, click.y, p1.x, p1.y, p4.x, p4.y);
	float A = TriangleArea(p4.x, p4.y, p1.x, p1.y, p2.x, p2.y);
	if (A == A1 + A2 + A3)
		inside1 = true;

	A1 = TriangleArea(click.x, click.y, p4.x, p4.y, p2.x, p2.y);
	A2 = TriangleArea(click.x, click.y, p2.x, p2.y, p3.x, p3.y);
	A3 = TriangleArea(click.x, click.y, p4.x, p4.y, p3.x, p3.y);
	A = TriangleArea(p3.x, p3.y, p4.x, p4.y, p2.x, p2.y);
	if (A == A1 + A2 + A3)
		inside2 = true;


	if (inside1 || inside2)
		return true;
	else
		return false;




}
bool CRhombus::sametype(CFigure* p)
{
	return (dynamic_cast<CRhombus*>(p) != NULL);
}
string CRhombus::String()
{
	return "Rhombus";
}



CRhombus::~CRhombus()
{
}

