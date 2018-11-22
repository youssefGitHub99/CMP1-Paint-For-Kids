#include "Input.h"
#include "Output.h"


Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetSrting(Output *pO) const
{
	string Label;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if ((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() - 1);
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if (UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
				//case ITM_LINE: return DRAW_LINE;
			case ITM_TO_PLAY: return TO_PLAY;
			case ITM_LINE: return DRAW_LINE;
			case ITM_ELLIPSE: return DRAW_ELLIPSE;
			case ITM_RHOMBUS: return DRAW_RHOMBUS;
			case ITM_TRI: return DRAW_TRI;
			case ITM_RECT: return DRAW_RECT;
			case ITM_CIRCLE: return DRAW_CIRCLE;
			
			/*case ITM_RESIZE_HALF: return    RESIZE_HALF;
			case ITM_RESIZE_QUARTER: return   RESIZE_QUARTER;
			case ITM_RESIZE_DOUBLE: return        RESIZE_DOUBLE;
			case ITM_RESIZE_FORTIMES: return  RESIZE_FOUR_TIMES;
			*/

			case ITM_SELECT_FIUGRE:	return SELECT_FIGURE;
			case ITM_SAVE:			return SAVE;
			case ITM_SAVE_BY_TYPE:	return SAVE_BY_TYPE;
			case ITM_COPY:			return COPY;
			case ITM_CUT:			return CUT;
			case ITM_UNMUTE:		return UNMUTE;
			case ITM_MUTE:			return MUTE;
			/*case ITM_SAVE_CIRCLE:	return SAVE_CIRCLE;
			case ITM_SAVE_TRI:		return SAVE_TRI;
			case ITM_SAVE_RHOMBUS:	return SAVE_RHOMBUS;
			case ITM_SAVE_ELLISPE:	return SAVE_ELLISPE;
			case ITM_SAVE_LINE:		return SAVE_LINE;
			case ITM_SAVE_RECT:		return SAVE_RECT;*/
			case ITM_SEND_BACK:		return SEND_BACK;
			case ITM_BRING_FRONT:	return BRING_FRONT;
			case ITM_DEL:			return DEL;
			case ITM_PASTE:			return PASTE;
			case ITM_LOAD:			return LOAD;
			case ITM_CHNG_DRAW_CLR:	return CHNG_DRAW_CLR;
			case ITM_CHNG_FILL_CLR:	return CHNG_FILL_CLR;
			case ITM_RESIZE:		return RESIZE_SHAPE;
			case ITM_EXIT:			return EXIT;

			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}
	else if (UI.InterfaceMode==MODE_PLAY)	//GUI is in PLAY mode
	{
		///TODO:
		//perform checks similar to Draw mode checks above
		//and return the correspoding action


		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_PLAY_LINE: return DRAW_LINE;
			case ITM_PLAY_ELLIPSE: return DRAW_ELLIPSE;
			case ITM_PLAY_RHOMBUS: return DRAW_RHOMBUS;
			case ITM_PLAY_TRI: return DRAW_TRI;
			case ITM_PLAY_RECT: return DRAW_RECT;
			case ITM_PLAY_CIRCLE: return DRAW_CIRCLE;
			case ITM_PLAY_COLOR_BLACK: return COLOR_BLACK;
			case ITM_PLAY_COLOR_BLUE: return COLOR_BLUE;
			case ITM_PLAY_COLOR_GREEN: return COLOR_GREEN;
			case ITM_PLAY_COLOR_RED: return COLOR_RED;
			case ITM_PLAY_COLOR_WHITE: return COLOR_WHITE;
			case ITM_PLAY_UNMUTE:     return UNMUTE;
			case ITM_PLAY_MUTE:     return MUTE;
			case ITM_TO_DRAW: return TO_DRAW;
			case ITM_PLAY_FIGURE_COLOR: return FIGURE_PICK_BY_COLOR;
			case ITM_PLAY_FIGURE_TYPE: return FIGURE_PICK_BY_TYPE;
			case ITM_EXIT: return EXIT;

			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;

		//return TO_PLAY;	//just for now. This should be updated
	}
	else if (UI.InterfaceMode == COLOR) {
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (x / UI.MenuItemWidth);

			switch (ClickedItemOrder)
			{
				case ITM_COLOR_BLACK: return COLOR_BLACK;
				case ITM_COLOR_BLUE: return COLOR_BLUE;
				case ITM_COLOR_GREEN: return COLOR_GREEN;
				case ITM_COLOR_RED: return COLOR_RED;
				case ITM_COLOR_WHITE: return COLOR_WHITE;
				case ITM_COLOR_BACK: return BACK_TO_DRAW;
				default: return EMPTY;
			}

		}
	}
	else if (UI.InterfaceMode == RESIZE) {
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (x / UI.MenuItemWidth);

			switch (ClickedItemOrder)
			{
				case ITM_RESIZE_HALF:	  return RESIZE_HALF;
				case ITM_RESIZE_QUARTER:  return RESIZE_QUARTER;
				case ITM_RESIZE_DOUBLE:   return RESIZE_DOUBLE;
				case ITM_RESIZE_FORTIMES: return RESIZE_FOUR_TIMES;
				case ITM_RESIZE_BACK:	  return BACK_TO_DRAW;
				default: return EMPTY;
			}

		}
	}
	else if (UI.InterfaceMode == SAVE_BY_TYBE_WINDOW) {
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (x / UI.MenuItemWidth);

			switch (ClickedItemOrder)
			{
				case ITM_SAVE_CIRCLE:	return SAVE_CIRCLE;
				case ITM_SAVE_TRI:		return SAVE_TRI;
				case ITM_SAVE_RHOMBUS:	return SAVE_RHOMBUS;
				case ITM_SAVE_ELLISPE:	return SAVE_ELLISPE;
				case ITM_SAVE_LINE:		return SAVE_LINE;
				case ITM_SAVE_RECT:		return SAVE_RECT;
				case ITM_SAVE_BACK:		return BACK_TO_DRAW;
				default: return EMPTY;
			}

		}




	
	
	}

}
/////////////////////////////////

Input::~Input()
{
}
