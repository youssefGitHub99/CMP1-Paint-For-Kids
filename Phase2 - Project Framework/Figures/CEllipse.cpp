#include"CEllipse.h"

CEllipse::CEllipse(Point center, GfxInfo FigGFXInfo):CFigure(FigGFXInfo) {
	this->center = center;
	factor = 4;
}


int CEllipse::getFactor() { return factor; }
void CEllipse::setFactor(int f) { factor = f; }


void CEllipse::Draw(Output * pOut)const{
	pOut->DrawEl(center, FigGfxInfo, false, factor);
}
void CEllipse::getPoints(Point & p1)const {
	p1 = center;
}