#pragma once
#include "CFigure.h"

class CCircle :public CFigure {
private :
	Point center;

public:
	CCircle(Point P1, GfxInfo FigureGfxInfo);
	void getCenter(Point & p1) const;
	void Draw(Output* pOut) const;

};