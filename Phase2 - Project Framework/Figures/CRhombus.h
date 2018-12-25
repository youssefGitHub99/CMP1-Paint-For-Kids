#pragma once
#include"CFigure.h"
class CRhombus:public CFigure 
{
	Point center;
public:
	CRhombus(Point center,GfxInfo figGFXInfo);
	void getCenter(Point & p1)const;
	void SetNewLocation(const Point & p1);
	virtual void Draw(Output * pOut)const;
	virtual bool isInside(Point click);
	virtual bool sametype(CFigure* p);
	virtual string String();
	~CRhombus();
};

