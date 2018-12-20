#include"CEllipse.h"

CEllipse::CEllipse(Point center, GfxInfo FigGFXInfo) :CFigure(FigGFXInfo) {
	this->center = center;
}


void CEllipse::Draw(Output * pOut) const {
	pOut->DrawEl(center, FigGfxInfo, Selected, factor);
	pOut->DrawOrigin(center);
}

void CEllipse::getCenter(Point & p1) const {
	p1 = center;
}