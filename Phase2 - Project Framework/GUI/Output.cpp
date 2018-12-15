#include "Output.h"
#include <iostream>

#define ORIGINCOLOR CYAN
#define ORIGINFACTOR 0.05

Output::Output()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;

	UI.width = 1600;
	UI.height = 650;
	UI.wx = 5;
	UI.wy = 5;

	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = /*50*/35;
	UI.MenuItemWidth = /*80*/70;

	UI.DrawColor = BLUE;	//Drawing color
	UI.FillColor = GREEN;	//Filling color
	UI.MsgColor = RED;		//Messages color
	UI.BkGrndColor = LIGHTGOLDENRODYELLOW;	//Background color
	UI.HighlightColor = MAGENTA;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = TURQUOISE;
	UI.PenWidth = 3;	//width of the figures frames

	pathBlack = "images\\MenuItems\\Menu_Color_Black.jpg";
	pathBlue = "images\\MenuItems\\Menu_Color_Blue.jpg";
	pathGreen = "images\\MenuItems\\Menu_Color_Green.jpg";
	pathRed = "images\\MenuItems\\Menu_Color_Red.jpg";
	pathWhite = "images\\MenuItems\\Menu_Color_White.jpg";
	pathLine = "images\\MenuItems\\Menu_Line.jpg";
	pathEllipse = "images\\MenuItems\\Menu_Ellipse.jpg";
	pathRhombus = "images\\MenuItems\\Menu_Rhombus.jpg";
	pathTriangle = "images\\MenuItems\\Menu_Triangle.jpg";
	pathRectangle = "images\\MenuItems\\Menu_Rect.jpg";
	pathCircle = "images\\MenuItems\\Menu_Circ.jpg";
	pathExit = "images\\MenuItems\\Menu_Exit.jpg";
	pathMute = "images\\MenuItems\\Menu_Mute.jpg";
	pathUnmute = "images\\MenuItems\\Menu_Unmute.jpg";
	pathBack = "images\\MenuItems\\Menu_Back_To_Draw.jpg";
	pathResize = "images\\MenuItems\\Menu_Resize.jpg";

	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");

	CreateDrawToolBar();
	CreateStatusBar();
}


Input* Output::CreateInput() const
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearToolBar() const {
	Point P1;
	P1.x = 0;
	P1.y = 0;

	Point P2;
	P2.x = pWind->GetWidth();
	P2.y = UI.ToolBarHeight;

	GfxInfo gfxInfo;
	gfxInfo.BorderWdth = 1;
	gfxInfo.DrawClr = WHITE;
	gfxInfo.FillClr = WHITE;
	gfxInfo.isFilled = true;
	this->DrawRect(P1, P2, gfxInfo, false, 1);
}

void Output::CreateDrawToolBar() const
{
	ClearToolBar();

	UI.InterfaceMode = MODE_DRAW;

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_SELECT_FIUGRE] = "images\\MenuItems\\Menu_Select.jpg";
	MenuItemImages[ITM_SAVE] = "images\\MenuItems\\Menu_Save.jpg";
	MenuItemImages[ITM_SAVE_BY_TYPE] = "images\\MenuItems\\Menu_Save_By_Type.jpg";
	MenuItemImages[ITM_COPY] = "images\\MenuItems\\Menu_Copy.jpg";
	MenuItemImages[ITM_CUT] = "images\\MenuItems\\Menu_Cut.jpg";
	MenuItemImages[ITM_UNMUTE] = pathUnmute;
	/*MenuItemImages[ITM_SAVE_CIRCLE] = "images\\MenuItems\\Menu_Save_Circle.jpg";
	MenuItemImages[ITM_SAVE_TRI] = "images\\MenuItems\\Menu_Save_Triangle.jpg";
	MenuItemImages[ITM_SAVE_RHOMBUS] = "images\\MenuItems\\Menu_Save_Rhombus.jpg";
	MenuItemImages[ITM_SAVE_ELLISPE] = "images\\MenuItems\\Menu_Save_Ellipse.jpg";
	MenuItemImages[ITM_SAVE_LINE] = "images\\MenuItems\\Menu_Save_Line.jpg";
	MenuItemImages[ITM_SAVE_RECT] = "images\\MenuItems\\Menu_Save_Rectangle.jpg";*/
	MenuItemImages[ITM_SEND_BACK] = "images\\MenuItems\\Menu_Back.jpg";
	MenuItemImages[ITM_BRING_FRONT] = "images\\MenuItems\\Menu_Front.jpg";
	MenuItemImages[ITM_PASTE] = "images\\MenuItems\\Menu_Paste.jpg";
	MenuItemImages[ITM_LOAD] = "images\\MenuItems\\Menu_Load.jpg";
	MenuItemImages[ITM_MUTE] = pathMute;
	MenuItemImages[ITM_RESIZE] = pathResize;
	/*MenuItemImages[ITM_COLOR_BLACK] = pathBlack;
	MenuItemImages[ITM_COLOR_BLUE] = pathBlue;
	MenuItemImages[ITM_COLOR_GREEN] = pathGreen;
	MenuItemImages[ITM_COLOR_RED] = pathRed;
	MenuItemImages[ITM_COLOR_WHITE] = pathWhite;*/
	MenuItemImages[ITM_LINE] = pathLine;
	MenuItemImages[ITM_ELLIPSE] = pathEllipse;
	MenuItemImages[ITM_RHOMBUS] = pathRhombus;
	MenuItemImages[ITM_TRI] = pathTriangle;
	MenuItemImages[ITM_RECT] = pathRectangle;
	MenuItemImages[ITM_CIRCLE] = pathCircle;
	MenuItemImages[ITM_TO_PLAY] = "images\\MenuItems\\Menu_Switch_To_Play_Mode.jpg";
	MenuItemImages[ITM_DEL] = "images\\MenuItems\\Menu_Delete.jpg";
	/*MenuItemImages[ITM_RESIZE_HALF] = "images\\MenuItems\\Menu_x0.5.jpg";
	MenuItemImages[ITM_RESIZE_QUARTER] = "images\\MenuItems\\Menu_x0.25.jpg";
	MenuItemImages[ITM_RESIZE_DOUBLE] = "images\\MenuItems\\Menu_x2.jpg";
	MenuItemImages[ITM_RESIZE_FORTIMES] = "images\\MenuItems\\Menu_x4.jpg";*/
	MenuItemImages[ITM_CHNG_DRAW_CLR] = "images\\MenuItems\\Menu_Change_Color.jpg";
	MenuItemImages[ITM_CHNG_FILL_CLR] = "images\\MenuItems\\Menu_Change_FILL_Color.jpg";
	MenuItemImages[ITM_EXIT] = pathExit;
	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for (int i = 0; i < DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreatePlayToolBar() const
{
	ClearToolBar();

	UI.InterfaceMode = MODE_PLAY;
	///TODO: write code to create Play mode menu
	string MenuItemImages[PLAY_ITM_COUNT];

	/*MenuItemImages[ITM_PLAY_LINE] = pathLine;
	MenuItemImages[ITM_PLAY_ELLIPSE] = pathEllipse;
	MenuItemImages[ITM_PLAY_RHOMBUS] = pathRhombus;
	MenuItemImages[ITM_PLAY_TRI] = pathTriangle;
	MenuItemImages[ITM_PLAY_RECT] = pathRectangle;
	MenuItemImages[ITM_PLAY_CIRCLE] = pathCircle;*/
	MenuItemImages[ITM_PLAY_MUTE] = pathMute;
	MenuItemImages[ITM_PLAY_UNMUTE] = pathUnmute;
	/*MenuItemImages[ITM_PLAY_COLOR_BLACK] = pathBlack;
	MenuItemImages[ITM_PLAY_COLOR_BLUE] = pathBlue;
	MenuItemImages[ITM_PLAY_COLOR_GREEN] = pathGreen;
	MenuItemImages[ITM_PLAY_COLOR_RED] = pathRed;
	MenuItemImages[ITM_PLAY_COLOR_WHITE] = pathWhite;*/
	MenuItemImages[ITM_TO_DRAW] = "images\\MenuItems\\Menu_Switch_To_Draw_Mode.jpg";
	MenuItemImages[ITM_PLAY_FIGURE_TYPE] = "images\\MenuItems\\Menu_Pick_By_Type.jpg";
	MenuItemImages[ITM_PLAY_FIGURE_COLOR] = "images\\MenuItems\\Menu_Pick_By_Color.jpg";
	MenuItemImages[ITM_PLAY_EXIT] = pathExit;

	//Draw menu item one image at a time
	for (int i = 0; i < PLAY_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);


	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreateColorToolBar()const {
	ClearToolBar();
	UI.InterfaceMode = COLOR_TOOLBAR;
	string ColorItemImages[COLOR_ITM_COUNT];
	ColorItemImages[ITM_COLOR_BLACK] = pathBlack;
	ColorItemImages[ITM_COLOR_BLUE] = pathBlue;
	ColorItemImages[ITM_COLOR_GREEN] = pathGreen;
	ColorItemImages[ITM_COLOR_RED] = pathRed;
	ColorItemImages[ITM_COLOR_WHITE] = pathWhite;
	ColorItemImages[ITM_COLOR_BACK] = pathBack;

	for (int i = 0; i < COLOR_ITM_COUNT; i++)
		pWind->DrawImage(ColorItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}

void Output::CreateResizeToolBar()const {
	ClearToolBar();
	UI.InterfaceMode = RESIZE_TOOLBAR;
	string ResizeItemImages[RESIZE_ITM_COUNT];
	ResizeItemImages[ITM_RESIZE_HALF] = "images\\MenuItems\\Menu_x0.5.jpg";
	ResizeItemImages[ITM_RESIZE_QUARTER] = "images\\MenuItems\\Menu_x0.25.jpg";
	ResizeItemImages[ITM_RESIZE_ORIGINAL] = "images\\MenuItems\\Menu_x1.jpg";
	ResizeItemImages[ITM_RESIZE_DOUBLE] = "images\\MenuItems\\Menu_x2.jpg";
	ResizeItemImages[ITM_RESIZE_FORTIMES] = "images\\MenuItems\\Menu_x4.jpg";
	ResizeItemImages[ITM_RESIZE_BACK] = pathBack;
	for (int i = 0; i < RESIZE_ITM_COUNT; i++)
		pWind->DrawImage(ResizeItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}

void Output::CreateSaveByTypeToolBar()const {
	ClearToolBar();
	UI.InterfaceMode = SAVE_BY_TYBE_TOOLBAR;
	string SaveByTypeItemImages[SAVE_BY_TYPE_ITM_COUNT];
	SaveByTypeItemImages[ITM_SAVE_CIRCLE] = "images\\MenuItems\\Menu_Save_Circle.jpg";
	SaveByTypeItemImages[ITM_SAVE_TRI] = "images\\MenuItems\\Menu_Save_Triangle.jpg";
	SaveByTypeItemImages[ITM_SAVE_RHOMBUS] = "images\\MenuItems\\Menu_Save_Rhombus.jpg";
	SaveByTypeItemImages[ITM_SAVE_ELLISPE] = "images\\MenuItems\\Menu_Save_Ellipse.jpg";
	SaveByTypeItemImages[ITM_SAVE_LINE] = "images\\MenuItems\\Menu_Save_Line.jpg";
	SaveByTypeItemImages[ITM_SAVE_RECT] = "images\\MenuItems\\Menu_Save_Rectangle.jpg";
	SaveByTypeItemImages[ITM_SAVE_BACK] = pathBack;
	for (int i = 0; i < SAVE_BY_TYPE_ITM_COUNT; i++)
		pWind->DrawImage(SaveByTypeItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
void Output::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar

	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight / 1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntDrawColor() const	//get current drawing color
{
	return UI.DrawColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntFillColor() const	//get current filling color
{
	return UI.FillColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

int Output::getCrntPenWidth() const		//get current pen width
{
	return UI.PenWidth;
}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void Output::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected, double factor) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);
	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawRectangle(
		P1.x, 
		P1.y, 
		POINTFACTORTRANSLATED_X_SQRT(P1.x, P2.x, factor),
		POINTFACTORTRANSLATED_Y_SQRT(P1.y, P2.y, factor),
		style
	);

}

void Output::DrawLi(Point P1, Point P2, GfxInfo LiGfxInfo, bool selected, double factor) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = LiGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);
	drawstyle style;
	style = FRAME;


	pWind->DrawLine(
		P1.x,
		P1.y,
		POINTFACTORTRANSLATED_X(P1.x, P2.x, factor),
		POINTFACTORTRANSLATED_Y(P1.y, P2.y, factor),
		style
	);
}

void Output::DrawTri(Point P1, Point P2, Point P3, GfxInfo TriGfxInfo, bool selected, double factor) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = TriGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);
	drawstyle style;
	if (TriGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(TriGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawTriangle(
		P1.x,
		P1.y,
		POINTFACTORTRANSLATED_X_SQRT(P1.x, P2.x, factor),
		POINTFACTORTRANSLATED_Y_SQRT(P1.y, P2.y, factor),
		POINTFACTORTRANSLATED_X_SQRT(P1.x, P3.x, factor),
		POINTFACTORTRANSLATED_Y_SQRT(P1.y, P3.y, factor),
		style
	);
}

void Output::DrawRh(Point P1, GfxInfo RhGfxInfo, bool selected, double factor) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RhGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);
	drawstyle style;
	if (RhGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RhGfxInfo.FillClr);
	}
	else
		style = FRAME;
	//Defining coordinate arrays for the 4 points starting from the uppermost point and going clockwise
	int iX[4] = { P1.x, P1.x + (int)(16 * INITIALFACTOR) * factor, P1.x, P1.x - (int)(16 * INITIALFACTOR) * factor };
	int iY[4] = { P1.y + (int)(16 * INITIALFACTOR) * factor, P1.y, P1.y - (int)(16 * INITIALFACTOR) * factor, P1.y };
	pWind->DrawPolygon(iX, iY, 4, style);
}

void Output::DrawEl(Point P1, GfxInfo ElGfxInfo, bool selected, double factor) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = ElGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);
	drawstyle style;
	if (ElGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(ElGfxInfo.FillClr);
	}
	else
		style = FRAME;
	int iX1, iX2, iY1, iY2;
	iX1 = P1.x - (int)(32 * INITIALFACTOR) * factor;
	iY1 = P1.y - (int)(16 * INITIALFACTOR) * factor;
	iX2 = P1.x + (int)(32 * INITIALFACTOR) * factor;
	iY2 = P1.y + (int)(16 * INITIALFACTOR) * factor;

	pWind->DrawEllipse(iX1, iY1, iX2, iY2, style);
}

void Output::DrawCir(Point P1, GfxInfo ElGfxInfo, bool selected, double factor) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = ElGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);
	drawstyle style;
	if (ElGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(ElGfxInfo.FillClr);
	}
	else
		style = FRAME;
	int iX1, iX2, iY1, iY2;
	iX1 = P1.x - (int)(16 * INITIALFACTOR) * factor;
	iY1 = P1.y - (int)(16 * INITIALFACTOR) * factor;
	iX2 = P1.x + (int)(16 * INITIALFACTOR) * factor;
	iY2 = P1.y + (int)(16 * INITIALFACTOR) * factor;

	pWind->DrawEllipse(iX1, iY1, iX2, iY2, style);
}
void Output::DrawOrigin(Point p)
{
	GfxInfo info;
	info.DrawClr = ORIGINCOLOR;
	info.FillClr = ORIGINCOLOR;
	info.isFilled = true;

	DrawCir(p, info, false, ORIGINFACTOR);
}
//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}

