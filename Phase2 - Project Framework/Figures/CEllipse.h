#pragma once
#include "CFigure.h"

class CEllipse:public CFigure {
private:
	Point center;
public:
	CEllipse(Point center,GfxInfo FigGFXInfo);
	void getCenter(Point & p1)const;
	void Draw(Output * pOut)const;

};
