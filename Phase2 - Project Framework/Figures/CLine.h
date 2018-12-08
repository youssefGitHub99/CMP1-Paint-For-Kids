#pragma once
#include "CFigure.h"

class CLine :public CFigure {
	
	Point corner1;
	Point corner2;

public :
	void getPoints(Point & p1, Point & p2)const;
	CLine(Point, Point, GfxInfo FigureGfxInfo);
	virtual void Draw(Output* pOut) const;
};