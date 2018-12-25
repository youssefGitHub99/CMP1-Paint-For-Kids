#include"CTriangle.h"
#include <iostream>

CTriangle::CTriangle(Point p1, Point p2, Point p3, GfxInfo figGFXInfo):CFigure(figGFXInfo){
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;

	//factor = 2;
}
void CTriangle::getTranslatedPoints(Point & p1, Point & p2, Point & p3) const {
	Point corner2Translated;
	corner2Translated.x = POINTFACTORTRANSLATED_X_SQRT(this->p1.x, this->p2.x, factor);
	corner2Translated.y = POINTFACTORTRANSLATED_Y_SQRT(this->p1.y, this->p2.y, factor);

	Point corner3Translated;
	corner3Translated.x = POINTFACTORTRANSLATED_X_SQRT(this->p1.x, this->p3.x, factor);
	corner3Translated.y = POINTFACTORTRANSLATED_Y_SQRT(this->p1.y, this->p3.y, factor);

	p1 = this->p1;
	p2 = corner2Translated;
	p3 = corner3Translated;

	/*std::cout << "p2  = (" << this->p2.x << ", " << this->p2.y << ")\n";
	std::cout << "p2T = (" << corner2Translated.x << ", " << corner2Translated.y << ")\n";

	std::cout << "p3  = (" << this->p3.x << ", " << this->p3.y << ")\n";
	std::cout << "p3T = (" << corner3Translated.x << ", " << corner3Translated.y << ")\n";*/

}
void CTriangle::getOriginalPoints(Point & p1, Point & p2, Point & p3) const
{
	p1 = this->p1;
	p2 = this->p2;
	p3 = this->p3;
}
void CTriangle::Draw(Output * pOut)const {
	
	if (!Hidden)
	{
		pOut->DrawTri(p1, p2, p3, FigGfxInfo, Selected, factor);
		pOut->DrawOrigin(p1);
	}
}


bool CTriangle::isInside(Point click) {
	float A1 = TriangleArea(click.x, click.y, p1.x, p1.y, p2.x, p2.y);
	float A2 = TriangleArea(click.x, click.y, p2.x, p2.y, p3.x, p3.y);
	float A3 = TriangleArea(click.x, click.y, p1.x, p1.y, p3.x, p3.y);
	float A = TriangleArea(p3.x, p3.y, p1.x, p1.y, p2.x, p2.y);
	if (A == A1 + A2 + A3)
		return true;
	else
		return false;
}

bool CTriangle::sametype(CFigure* p)
{
	return (dynamic_cast<CTriangle*>(p) != NULL);
}
string CTriangle::String()
{
	return "Triangle";
}

