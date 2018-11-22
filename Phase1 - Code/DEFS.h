#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

//This file contains some global constants and definitions to be used in the project.
enum ActionType //The actions supported (you can add more if needed)
{
	DRAW_RECT,		//Draw Rectangle
	DRAW_LINE,		//Draw Line
	DRAW_RHOMBUS,	//Draw Rhombus
	DRAW_ELLIPSE,	//Draw Ellipse
	DRAW_TRI,		//Draw Triangle
	DRAW_CIRCLE,	//Draw Ellipse
	CHNG_DRAW_CLR,	//Change the drawing color
	CHNG_FILL_CLR,	//Change the filling color
	RESIZE_SHAPE,
	SELECT_FIGURE,
	COPY,
	CUT,
	PASTE,
	PICK,
	FIGURE_PICK_BY_TYPE,
	FIGURE_PICK_BY_COLOR,
	COLOR_BLACK,
	COLOR_BLUE,
	COLOR_GREEN,
	COLOR_WHITE,
	COLOR_RED,
	BACK_TO_DRAW,
	MUTE,
	UNMUTE,
	SAVE_CIRCLE,
	SAVE_TRI,
	SAVE_RHOMBUS,
	SAVE_ELLISPE,
	SAVE_LINE,
	SAVE_RECT,
	SEND_BACK,
	BRING_FRONT,
	RESIZE_QUARTER,
	RESIZE_HALF,
	RESIZE_DOUBLE,
	RESIZE_FOUR_TIMES,
	
	DEL,			//Delete a figure(s)
	SAVE,			//Save the whole graph to a file
	SAVE_BY_TYPE,	//Save the all the figures that have a specific type
	LOAD,			//Load a graph from a file
	EXIT,			//Exit the application

	DRAWING_AREA,	//A click on the drawing area
	STATUS,			//A click on the status bar
	EMPTY,			//A click on empty place in the toolbar

	TO_DRAW,		//Switch interface to Draw mode
	TO_PLAY,			//Switch interface to Play mode

	///TODO: Add more action types (if needed)
};

enum SoundIcons {
	SOUND_MUTE, 
	SOUND_UNMUTE
};

struct Point	//To be used for figures points
{ int x,y; };

struct GfxInfo	//Graphical info of each figure (you may add more members)
{
	color DrawClr;	//Draw color of the figure
	color FillClr;	//Fill color of the figure
	bool isFilled;	//Figure Filled or not
	int BorderWdth;	//Width of figure borders

};

#endif