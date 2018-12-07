#ifndef OUPTUT_H
#define OUPTUT_H
#include "Input.h"

class Output	//The application manager should have a pointer to this class
{
private:	
	window* pWind;	//Pointer to the Graphics Window
	string pathRed;
	string pathBlue;
	string pathWhite;
	string pathGreen;
	string pathBlack;
	string pathTriangle;
	string pathRectangle;
	string pathCircle;
	string pathEllipse;
	string pathRhombus;
	string pathLine;
	string pathExit;
	string pathMute;
	string pathUnmute;
	string pathBack;
	string pathResize;
	
public:
	Output();		

	window* CreateWind(int, int, int , int) const; //creates the application window
	void CreateDrawToolBar() const;	//creates Draw mode toolbar & menu
	void ClearToolBar() const;
	void CreatePlayToolBar() const;//creates Play mode toolbar & menu
	void CreateColorToolBar()const;
	void CreateResizeToolBar()const;
	void CreateSaveByTypeToolBar()const;
	void CreateStatusBar() const;	//create the status bar

	Input* CreateInput() const; //creates a pointer to the Input object	
	void ClearStatusBar() const;	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area
	
	// -- Figures Drawing functions
	void DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected=false) const;  //Draw a rectangle
	void DrawLi(Point P1, Point P2, GfxInfo LiGfxInfo, bool selected=false) const;  //Draw a line
	void DrawTri(Point P1, Point P2, Point P3, GfxInfo TriGfxInfo, bool selected=false) const;  //Draw a triangle
	void DrawRh(Point P1, GfxInfo RhGfxInfo, bool selected=false, double factor=1) const;  //Draw a rhombus
	void DrawEl(Point P1, GfxInfo ElGfxInfo, bool selected=false, double factor=1) const;  //Draw an ellipse
	void DrawCir(Point P1, GfxInfo ElGfxInfo, bool selected = false, double factor = 1) const;
	///Make similar functions for drawing all other figure types.
	
	void PrintMessage(string msg) const;	//Print a message on Status bar

	color getCrntDrawColor() const;	//get current drwawing color
	color getCrntFillColor() const;	//get current filling color
	int getCrntPenWidth() const;		//get current pen width

	
	~Output();
};

#endif
