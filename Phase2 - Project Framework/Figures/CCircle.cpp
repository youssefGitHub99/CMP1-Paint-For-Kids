#include "CCircle.h"

CCircle::CCircle(Point center, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo) {
	this->center = center;
	factor = 4;
}
void CCircle::getPoints(Point & p1)const {
	p1 = center;
}

int CCircle::getFactor() { return factor; }
void CCircle::setFactor(int f) { factor = f; }

void CCircle::Draw(Output * pOut)const{

	pOut->DrawCir(center, FigGfxInfo,Selected,factor);

}