#ifndef CFIGURE_H
#define CFIGURE_H
#pragma once
#include "..\defs.h"
#include "..\GUI\Output.h"
#include <string>
using namespace std;
class CFigure;
//Base class for all figures
class CFigure
{
protected:
	int ID;		//Each figure has an ID
	bool Selected;	//true if the figure is selected.
	GfxInfo FigGfxInfo;	//Figure graphis info
	bool IsCut;
	double factor;
	bool Hidden;

	// Add more parameters if needed.

public:
	CFigure(GfxInfo FigureGfxInfo);
	int getId()const;
	void setId(int id);
	void SetSelected(bool s);	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected
	void SetCut(bool Cut);
	bool IsFigureCut();
	GfxInfo getGfxInfo() const;
	float getDistance(Point , Point);
	double getFactor();
	void setFactor(double factor);
	void hide();
	void unhide();
	bool hidden();
	bool sameFillClr(CFigure* p);
	string FillClr();
	

	float TriangleArea(float x1, float y1, float x2, float y2, float x3, float y3);
	virtual void Draw(Output* pOut) const = 0 ;		//Draw the figure
	virtual bool isInside(Point click) = 0;
	virtual bool sametype(CFigure* p) = 0;
	virtual string String() = 0;

	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	void ChngFillClr(color Fclr);	//changes the figure's filling color

	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure

	///Decide the parameters that you should pass to each function	

	
	//virtual void Save(ofstream &OutFile) = 0;	//Save the figure parameters to the file
	//virtual void Load(ifstream &Infile) = 0;	//Load the figure parameters to the file
	
	//virtual void PrintInfo(Output* pOut) = 0;	//print all figure info on the status bar
};

#endif