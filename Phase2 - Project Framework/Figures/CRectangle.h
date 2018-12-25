#ifndef CRECT_H
#define CRECT_H

#include "CFigure.h"

class CRectangle : public CFigure
{
private:
	Point Corner1;	
	Point Corner2;
public:
	CRectangle(Point , Point, GfxInfo FigureGfxInfo );
	void getTranslatedPoints(Point & p1, Point & p2)const ;
	void getOriginalPoints(Point & p1, Point & p2)const ;
	void SetNewLocation(const Point &p1, const Point &p2);
	virtual void Draw(Output* pOut) const;
	virtual bool isInside(Point click);
	virtual bool sametype(CFigure* p);
	virtual string String();
};

#endif