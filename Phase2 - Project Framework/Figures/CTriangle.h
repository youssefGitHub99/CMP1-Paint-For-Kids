#pragma once
#include "CFigure.h"

class CTriangle : public CFigure {
private:
	Point p1, p2, p3;

public:
	CTriangle(Point p1, Point p2, Point p3,GfxInfo figGFXInfo);
	void Draw(Output * pOut)const ;
	void getPoints(Point & p1, Point & p2,Point & p3)const;

};

