#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

enum GUI_MODE	//Graphical user interface mode (Toolbars)
{
	MODE_DRAW,	//Drawing mode (startup mode)
	MODE_PLAY,  //Playing mode
	COLOR,
	RESIZE,
	SAVE_BY_TYBE_WINDOW
};

enum DrawMenuItem //The items of the Draw menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	ITM_RECT,
	ITM_LINE,
	ITM_TRI,
	ITM_RHOMBUS,
	ITM_ELLIPSE,
	ITM_CIRCLE,
	ITM_SELECT_FIUGRE,
	ITM_CHNG_DRAW_CLR,
	ITM_CHNG_FILL_CLR,
	ITM_RESIZE,
	ITM_COPY,
	ITM_CUT,
	ITM_PASTE,
	//ITM_PICK,
	//ITM_HIDE,
	ITM_MUTE,
	ITM_UNMUTE,
	
	ITM_SEND_BACK,
	ITM_BRING_FRONT,
	ITM_DEL,
	ITM_SAVE,
	ITM_SAVE_BY_TYPE,
	/*ITM_SAVE_CIRCLE,
	ITM_SAVE_TRI,
	ITM_SAVE_RHOMBUS,
	ITM_SAVE_ELLISPE,
	ITM_SAVE_LINE,
	ITM_SAVE_RECT,*/
	ITM_LOAD,
	ITM_TO_PLAY,
	
	//Recangle item in menu
	
	//TODO: Add more items names here

	ITM_EXIT,		//Exit item
	
	DRAW_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum
	
};

enum ColorItem {
	ITM_COLOR_RED,
	ITM_COLOR_BLUE,
	ITM_COLOR_GREEN,
	ITM_COLOR_BLACK,
	ITM_COLOR_WHITE,
	ITM_COLOR_BACK,
	COLOR_ITM_COUNT
};

enum ResizeItem {
	ITM_RESIZE_QUARTER,
	ITM_RESIZE_HALF,
	ITM_RESIZE_DOUBLE,
	ITM_RESIZE_FORTIMES,
	ITM_RESIZE_BACK,
	RESIZE_ITM_COUNT

};

enum SaveByTypeItem {
	ITM_SAVE_CIRCLE,
	ITM_SAVE_TRI,
	ITM_SAVE_RHOMBUS,
	ITM_SAVE_ELLISPE,
	ITM_SAVE_LINE,
	ITM_SAVE_RECT,
	ITM_SAVE_BACK,
	SAVE_BY_TYPE_ITM_COUNT
};

enum PlayMenuItem //The items of the Play menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	
	//TODO: Add more items names here
	ITM_PLAY_FIGURE_TYPE,
	ITM_PLAY_FIGURE_COLOR,
	/*ITM_PLAY_RECT,
	ITM_PLAY_LINE,
	ITM_PLAY_TRI,
	ITM_PLAY_RHOMBUS,
	ITM_PLAY_ELLIPSE,
	ITM_PLAY_CIRCLE,
	ITM_PLAY_COLOR_RED,
	ITM_PLAY_COLOR_BLUE,
	ITM_PLAY_COLOR_GREEN,
	ITM_PLAY_COLOR_BLACK,
	ITM_PLAY_COLOR_WHITE,*/
	ITM_PLAY_MUTE,
	ITM_PLAY_UNMUTE,
	ITM_TO_DRAW,

	ITM_PLAY_EXIT,

	PLAY_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum
	
};





__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	GUI_MODE InterfaceMode;
	
	int	width, height,	    //Window width and height
		wx , wy,			//Window starting coordinates
		StatusBarHeight,	//Status Bar Height
		ToolBarHeight,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		MenuItemWidth;		//Width of each item in toolbar menu
	

	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	int PenWidth;			//width of the pen that draws shapes

	/// Add more members if needed
	
}UI;	//create a global object UI

#endif