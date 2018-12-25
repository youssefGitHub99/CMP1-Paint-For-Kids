#pragma once
#include "CFigure.h"

class CTriangle : public CFigure {
private:
	Point p1, p2, p3;

public:
	CTriangle(Point p1, Point p2, Point p3,GfxInfo figGFXInfo);
	void getTranslatedPoints(Point & p1, Point & p2,Point & p3)const;
	void getOriginalPoints(Point & p1, Point & p2,Point & p3)const;
	virtual void Draw(Output * pOut)const ;
	virtual bool isInside(Point click);
	virtual bool sametype(CFigure* p);
	virtual string String();

};

