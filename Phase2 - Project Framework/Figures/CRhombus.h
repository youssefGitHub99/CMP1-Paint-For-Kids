#pragma once
#include"CFigure.h"
class CRhombus:public CFigure 
{
	Point center;
	int factor;
public:
	int getFactor();
	void setFactor(int);
	CRhombus(Point center,GfxInfo figGFXInfo);
	virtual void Draw(Output * pOut)const;
	void getPoints(Point & p1)const;
	~CRhombus();
};

