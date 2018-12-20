#include "CRhombus.h"

CRhombus::CRhombus(Point center, GfxInfo figGFXInfo) :CFigure(figGFXInfo)
{
	this->center = center;
}

void CRhombus::Draw(Output * pOut)const {
	pOut->DrawRh(center, FigGfxInfo, Selected, factor);
	pOut->DrawOrigin(center);

}
void CRhombus::getCenter(Point & p1)const {
	p1 = center;
}

CRhombus::~CRhombus()
{
}
