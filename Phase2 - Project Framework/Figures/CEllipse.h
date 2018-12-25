#pragma once
#include "CFigure.h"

class CEllipse:public CFigure {
private:
	Point center;
public:
	CEllipse(Point center,GfxInfo FigGFXInfo);
	void SetNewLocation(const Point &);
	void getCenter(Point & p1)const;
	virtual void Draw(Output * pOut)const;
	virtual bool isInside(Point click);
};
