#pragma once
#include "Action.h"

//Add Rectangle Action class
class AddTriangleAction : public Action
{
private:
	Point p1, p2,p3; //Rectangle Corners
	GfxInfo TriangleGfxInfo;
public:
	AddTriangleAction(ApplicationManager *pApp);

	//Reads rectangle parameters
	virtual void ReadActionParameters();

	//Add rectangle to the ApplicationManager
	virtual void Execute();

};

