#include"CEllipse.h"

CEllipse::CEllipse(Point center, GfxInfo FigGFXInfo) :CFigure(FigGFXInfo) {
	this->center = center;
}


void CEllipse::Draw(Output * pOut) const {
	pOut->DrawEl(center, FigGfxInfo,IsCut, Selected, factor);
	pOut->DrawOrigin(center);
}
void CEllipse::SetNewLocation(const Point &p) {

	center = p;

}
void CEllipse::getCenter(Point & p1) const {
	p1 = center;
}
bool CEllipse::isInside(Point click) {
	int a = factor * 32 * INITIALFACTOR;
	int b = factor * 16 * INITIALFACTOR;
	float p = (pow((center.x - click.x), 2) / pow(a, 2)) + (pow((center.y - click.y), 2) / pow(b, 2));
	if (p <= 1) {
		return true;
	}
	else
		false;



}

