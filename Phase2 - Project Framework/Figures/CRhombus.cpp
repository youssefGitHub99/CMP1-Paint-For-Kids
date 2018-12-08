#include "CRhombus.h"

CRhombus::CRhombus(Point center,GfxInfo figGFXInfo):CFigure(figGFXInfo)
{
	this->center = center;
	factor = 4;
}

int CRhombus::getFactor() { return factor; }
void CRhombus::setFactor(int f) { factor = f; }
void CRhombus::Draw(Output * pOut)const {
	pOut->DrawRh(center, FigGfxInfo, false, factor);


}
void CRhombus::getPoints(Point & p1)const {
	p1 = center;
}

CRhombus::~CRhombus()
{
}
