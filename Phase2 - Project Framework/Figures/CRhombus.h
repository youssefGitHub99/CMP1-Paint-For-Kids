#pragma once
#include"CFigure.h"
class CRhombus:public CFigure 
{
	Point center;
public:
	CRhombus(Point center,GfxInfo figGFXInfo);
	void getCenter(Point & p1)const;
	virtual void Draw(Output * pOut)const;
	~CRhombus();
};

