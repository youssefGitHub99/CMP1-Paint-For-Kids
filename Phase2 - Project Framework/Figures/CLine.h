#pragma once
#include "CFigure.h"

class CLine :public CFigure {
	
	Point point1;
	Point point2;

public :
	CLine(Point, Point, GfxInfo FigureGfxInfo);
	void getTranslatedPoints(Point & p1, Point & p2)const;
	void getOriginalPoints(Point & p1, Point & p2)const;
	virtual void Draw(Output* pOut) const;
	virtual bool isInside(Point click);
};