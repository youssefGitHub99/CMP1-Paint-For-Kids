#pragma once
#include "CFigure.h"

class CCircle :public CFigure {
private :
	Point center;

public:
	CCircle(Point P1, GfxInfo FigureGfxInfo);
	void SetNewLocation(const Point &p);
	void getCenter(Point & p1) const;
	virtual void Draw(Output* pOut) const;
	virtual bool isInside(Point click);
	virtual bool sametype(CFigure* p);
	virtual string String();
};