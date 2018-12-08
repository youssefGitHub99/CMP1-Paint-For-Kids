#pragma once
#include "CFigure.h"

class CEllipse:public CFigure {
private:
	Point center;
	int factor;
public:
	int getFactor();
	void setFactor(int);
	void getPoints(Point & p1)const;
	CEllipse(Point center,GfxInfo FigGFXInfo);
	void Draw(Output * pOut)const;

};
