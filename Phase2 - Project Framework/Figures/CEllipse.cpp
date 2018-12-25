#include"CEllipse.h"

CEllipse::CEllipse(Point center, GfxInfo FigGFXInfo) :CFigure(FigGFXInfo) {
	this->center = center;
}


void CEllipse::Draw(Output * pOut) const {
	if (!Hidden)
	{
		pOut->DrawEl(center, FigGfxInfo, Selected, factor);
		pOut->DrawOrigin(center);
	}
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
bool CEllipse::sametype(CFigure* p)
{
	return (dynamic_cast<CEllipse*>(p) != NULL);
}
string CEllipse::String()
{
	return "Ellipse";
}
