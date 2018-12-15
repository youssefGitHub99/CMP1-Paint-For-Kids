#pragma once
#include "CFigure.h"

class CLine :public CFigure {
	
	Point corner1;
	Point corner2;

public :
	CLine(Point, Point, GfxInfo FigureGfxInfo);
	void getTranslatedPoints(Point & p1, Point & p2)const;
	void getOriginalPoints(Point & p1, Point & p2)const;
	virtual void Draw(Output* pOut) const;
};