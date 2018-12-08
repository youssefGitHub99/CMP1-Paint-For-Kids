#pragma once
#include "CFigure.h"

class CCircle :public CFigure {
private :
	Point center;
	int factor;

public:
	int getFactor();
	void setFactor(int);
	CCircle(Point P1, GfxInfo FigureGfxInfo);
	void getPoints(Point & p1)const;
	void Draw(Output* pOut) const;




};