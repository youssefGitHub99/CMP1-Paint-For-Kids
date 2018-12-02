#include"CTriangle.h"

CTriangle::CTriangle(Point p1, Point p2, Point p3, GfxInfo figGFXInfo):CFigure(figGFXInfo){
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
}
void CTriangle::getPoints(Point & p1, Point & p2,Point & p3)const {
	p1 = this->p1;
	p2 = this->p2;
	p3 = this->p3;

}
void CTriangle::Draw(Output * pOut)const {
	
	pOut->DrawTri(p1, p2, p3, FigGfxInfo, false);

}