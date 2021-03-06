#include "GUI\Input.h"
#include "GUI\Output.h"

//This is a test code to test the Input and Output classes

int main()
{
	int x, y;

	//Create Input and Output objects to test
	Output *pOut = new Output();
	Input *pIn = pOut->CreateInput();

	//Starting the test
	pOut->PrintMessage("This demo is to test input and output classes, Click anywhere to start the test");
	pIn->GetPointClicked(x, y);	//Wait for any click


	/////////////////////////////////////////////////////////////////////////////////
	////TEST 1:	
				/*Create The FULL Tool bar, the drawing area and the status bar	
				This has already been done through the constrcutor of class Output*/
	/////////////////////////////////////////////////////////////////////////////////

	pOut->PrintMessage("TEST1: Drawing Tool bar and Status bar, Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click

	
	///////////////////////////////////////////////////////////////////////////////////
	// TEST 2:	
	//			Drawing all the Figures with all possible states: 
	//			Non-filled, Filled, and highlighted in both cases			
	///////////////////////////////////////////////////////////////////////////////////
	
	pOut->PrintMessage("TEST2: Now we will show that Output class can draw any figure in any state, Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click

	GfxInfo gfxInfo;//to be used with draw function of the class Ouput
	Point P1, P2, P3;

	/// 2.1- Rectangle Test ///
	/// =================== 
	pOut->PrintMessage("Drawing a Rectangle, filled/non-filled and Highlighted filled/non-filled,  Click to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click
	
	// 2.1.1 - Drawing non-filled rectangle
	pOut->PrintMessage("Drawing a Rectangle ==> non-filled,  Click two points");
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->GetPointClicked(P2.x, P2.y);

	gfxInfo.BorderWdth = 5;
	gfxInfo.DrawClr = BLACK;	//any color for border
	gfxInfo.isFilled = false;	//Figure is NOT filled
	pOut->DrawRect(P1, P2, gfxInfo, false);

	// 2.1.2 - Drawing highlighted non-filled rectangle
	pOut->PrintMessage("Drawing a Rectangle ==> Highlighted non-filled, Click to Highlight");
	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->DrawRect(P1, P2, gfxInfo, true);


	// 2.1.3 - Drawing a filled rectangle
	pOut->PrintMessage("Drawing a Rectangle ==> filled,  Click two points");
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->GetPointClicked(P2.x, P2.y);

	gfxInfo.BorderWdth = 6;
	gfxInfo.DrawClr = BLUE;	//any color for border
	gfxInfo.FillClr = GREEN;//any color for filling
	gfxInfo.isFilled = true;//Figure is filled
	pOut->DrawRect(P1, P2, gfxInfo, false);


	// 2.1.4 - Drawing a highlighted filled rectangle
	pOut->PrintMessage("Drawing a Rectangle ==> Highlighted filled, Click to Highlight");
	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->DrawRect(P1, P2, gfxInfo, true);



	pOut->PrintMessage("Drawing a Rectangle Test ==> OK,  Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->ClearDrawArea();

	/// 2.2- Line Test ///
	/// ============== 
	pOut->PrintMessage("Drawing a Line, normal and Highlighted, Click to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click

	///TODO: Add code to draw Line, Normal and Highlighted
	// 2.2.1 - Drawing normal line
	pOut->PrintMessage("Drawing a Line ==> Click two points");
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->GetPointClicked(P2.x, P2.y);

	gfxInfo.BorderWdth = 5;
	gfxInfo.DrawClr = BLACK;	//any color for border
	pOut->DrawLi(P1, P2, gfxInfo, false);

	// 2.2.2 - Drawing highlighted line
	pOut->PrintMessage("Drawing a Line ==> Highlighted, Click to Highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->DrawLi(P1, P2, gfxInfo, true);



	pOut->PrintMessage("Drawing a Line Test ==> OK,  Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->ClearDrawArea();

	/// 2.3- Triangle Test ///
	/// =================== 
	pOut->PrintMessage("Drawing a Triangle, filled/non-filled and Highlighted filled/non-filled,  Click to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click

	///TODO: Add code to draw Triangle in all possible states
	// 2.3.1 - Drawing non-filled triangle
	pOut->PrintMessage("Drawing a Triangle ==> non-filled,  Click three points");
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->GetPointClicked(P2.x, P2.y);
	pIn->GetPointClicked(P3.x, P3.y);

	gfxInfo.BorderWdth = 5;
	gfxInfo.DrawClr = BLACK;	//any color for border
	gfxInfo.isFilled = false;	//Figure is NOT filled
	pOut->DrawTri(P1, P2, P3, gfxInfo, false);

	// 2.3.2 - Drawing highlighted non-filled triangle
	pOut->PrintMessage("Drawing a Triangle ==> Highlighted non-filled, Click to Highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->DrawTri(P1, P2, P3, gfxInfo, true);


	// 2.3.3 - Drawing a filled triangle
	pOut->PrintMessage("Drawing a Triangle ==> filled,  Click three points");
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->GetPointClicked(P2.x, P2.y);
	pIn->GetPointClicked(P3.x, P3.y);

	gfxInfo.BorderWdth = 6;
	gfxInfo.DrawClr = BLUE;	//any color for border
	gfxInfo.FillClr = GREEN;//any color for filling
	gfxInfo.isFilled = true;//Figure is filled
	pOut->DrawTri(P1, P2, P3, gfxInfo, false);


	// 2.3.4 - Drawing a highlighted filled triangle
	pOut->PrintMessage("Drawing a Triangle ==> Highlighted filled, Click to Highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->DrawTri(P1, P2, P3, gfxInfo, true);



	pOut->PrintMessage("Drawing a Triangle Test ==> OK,  Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->ClearDrawArea();
	
	/// 2.4- Rhombus Test ///
	/// =================== 
	pOut->PrintMessage("Drawing a Rhombus, filled/non-filled and Highlighted filled/non-filled, 1/4th/4* default size, filled,  Click to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click

	///TODO: Add code to draw Rhombus in all possible states
	// 2.4.1 - Drawing non-filled rhombus
	pOut->PrintMessage("Drawing a rhombus ==> non-filled,  Click on one point");
	pIn->GetPointClicked(P1.x, P1.y);

	gfxInfo.BorderWdth = 5;
	gfxInfo.DrawClr = BLACK;	//any color for border
	gfxInfo.isFilled = false;	//Figure is NOT filled
	pOut->DrawRh(P1, gfxInfo, false);

	// 2.4.2 - Drawing highlighted non-filled rhombus
	pOut->PrintMessage("Drawing a Rhombus ==> Highlighted non-filled, Click to Highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->DrawRh(P1, gfxInfo, true);


	// 2.4.3 - Drawing a filled rhombus
	pOut->PrintMessage("Drawing a Rhombus ==> filled,  Click on one point");
	pIn->GetPointClicked(P1.x, P1.y);

	gfxInfo.BorderWdth = 6;
	gfxInfo.DrawClr = BLUE;	//any color for border
	gfxInfo.FillClr = GREEN;//any color for filling
	gfxInfo.isFilled = true;//Figure is filled
	pOut->DrawRh(P1, gfxInfo, false);


	// 2.4.4 - Drawing a highlighted filled rhombus
	pOut->PrintMessage("Drawing a Rhombus ==> Highlighted filled, Click to Highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->DrawRh(P1, gfxInfo, true);


	// 2.4.5 - Drawing filled rhombus 1/4th the default size
	pOut->PrintMessage("Drawing a Rhombus ==> filled 1/4th default size, Click one point");
	pIn->GetPointClicked(P1.x, P1.y);
	pOut->DrawRh(P1, gfxInfo, false, .25);


	// 2.4.6 - Drawing filled rhombus 4 times default size
	pOut->PrintMessage("Drawing a Rhombus ==> filled 4 times default size, Click one point");
	pIn->GetPointClicked(P1.x, P1.y);
	pOut->DrawRh(P1, gfxInfo, false, 4);


	pOut->PrintMessage("Drawing a Rhombus Test ==> OK,  Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->ClearDrawArea();
	
	/// 2.5- Ellipse Test ///
	/// =================== 
	pOut->PrintMessage("Drawing an Ellipse, filled/non-filled and Highlighted filled/non-filled, 1/4th/4* default size, filled,  Click to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click

	///TODO: Add code to draw Ellipse in all possible states
	// 2.5.1 - Drawing non-filled ellipse
	pOut->PrintMessage("Drawing an Ellipse ==> non-filled,  Click on one point");
	pIn->GetPointClicked(P1.x, P1.y);

	gfxInfo.BorderWdth = 5;
	gfxInfo.DrawClr = BLACK;	//any color for border
	gfxInfo.isFilled = false;	//Figure is NOT filled
	pOut->DrawEl(P1, gfxInfo, false);

	// 2.5.2 - Drawing highlighted non-filled ellipse
	pOut->PrintMessage("Drawing an Ellipse ==> Highlighted non-filled, Click to Highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->DrawEl(P1, gfxInfo, true);


	// 2.5.3 - Drawing a filled ellipse
	pOut->PrintMessage("Drawing an Ellipse ==> filled,  Click on one point");
	pIn->GetPointClicked(P1.x, P1.y);

	gfxInfo.BorderWdth = 6;
	gfxInfo.DrawClr = BLUE;	//any color for border
	gfxInfo.FillClr = GREEN;//any color for filling
	gfxInfo.isFilled = true;//Figure is filled
	pOut->DrawEl(P1, gfxInfo, false);


	// 2.5.4 - Drawing a highlighted filled ellipse
	pOut->PrintMessage("Drawing an Ellipse ==> Highlighted filled, Click to Highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->DrawEl(P1, gfxInfo, true);


	// 2.5.5 - Drawing ellipse 1/4th the default size
	pOut->PrintMessage("Drawing an Ellipse ==> non-filled 1/4th default size, Click one point");
	pIn->GetPointClicked(P1.x, P1.y); 
	pOut->DrawEl(P1, gfxInfo, false, .25);


	// 2.5.6 - Drawing ellipse 4 times default size
	pOut->PrintMessage("Drawing an Ellipse ==> non-filled 4 times default size, Click one point");
	pIn->GetPointClicked(P1.x, P1.y);
	pOut->DrawEl(P1, gfxInfo, false, 4);



	pOut->PrintMessage("Drawing a Ellipse Test ==> OK,  Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->ClearDrawArea();
	
	///////////////////////////////////////////////////////////////////////////////////
	// TEST 3: 
	//			Input Class: Read strings from the user
	///////////////////////////////////////////////////////////////////////////////////
	pOut->PrintMessage("TEST3: Now Time to test class Input, Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click
	
	pOut->PrintMessage("Testing Input ability to read strings");

	///TODO: Add code here to 
	// 1- Read a string from the user on the status bar
	string str = pIn->GetSrting(pOut);
	// 2- After reading the stirng clear the status bar
	pOut->ClearStatusBar();
	// 3- print on the status bar "You Entered" then print the string
	pOut->PrintMessage("You Entered : " + str);

	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->ClearDrawArea();

	///////////////////////////////////////////////////////////////////////////////////
	// TEST 4: 
	//			Input Class : Check for the user action
	///////////////////////////////////////////////////////////////////////////////////
	pOut->PrintMessage("TEST4: Testing Input ability to detect User Action, click anywhere");

	ActionType ActType;

	///TODO:  
	//You must add a case for each action (both Draw mode and Play mode actions)
	//Add cases for the missing actions below
	do
	{
		ActType = pIn->GetUserAction();

		switch (ActType)
		{
		case DRAW_RECT:
			pOut->PrintMessage("Action: Draw a Rectangle , Click anywhere");
			break;

		case DRAW_LINE:
			pOut->PrintMessage("Action: Draw a Line , Click anywhere");
			break;

		case DRAW_RHOMBUS:
			pOut->PrintMessage("Action: Draw a Rhombus , Click anywhere");
			break;

		case DRAW_ELLIPSE:
			pOut->PrintMessage("Action: Draw an Ellipse , Click anywhere");
			break;

		case DRAW_TRI:
			pOut->PrintMessage("Action: Draw a Triangle , Click anywhere");
			break;

		case DRAW_CIRCLE:
			pOut->PrintMessage("Actions: Draw a circle, Click anywhere");
			break;

		case CHNG_DRAW_CLR:
			pOut->PrintMessage("Action: Change Figure's drawing color , Click anywhere");
			pOut->CreateColorToolBar();
			break;

		case CHNG_FILL_CLR:
			pOut->PrintMessage("Action: Change Figure's Fill color , Click anywhere");
			pOut->CreateColorToolBar();
			break;
		case RESIZE_SHAPE:
			pOut->CreateResizeToolBar();
			break;
		case SELECT_FIGURE:
			pOut->PrintMessage("Actions: Select Figure, Click anywhere");
			break;

		case COPY:
			pOut->PrintMessage("Actions: Copy, Click anywhere");
			break;

		case CUT:
			pOut->PrintMessage("Actions: Cut, Click anywhere");
			break;

		case PASTE:
			pOut->PrintMessage("Actions: Paste, Click anywhere");
			break;

		case PICK:
			pOut->PrintMessage("Actions: Pick, Click anywhere");
			break;

		case FIGURE_PICK_BY_TYPE:
			pOut->PrintMessage("Actions: Pick By Type, Click anywhere");
			break;
		case BACK_TO_DRAW:
			pOut->CreateDrawToolBar();
			break;
		case FIGURE_PICK_BY_COLOR:
			pOut->PrintMessage("Actions: Pick By Color, Click anywhere");
			break;

		case COLOR_BLACK:
			pOut->PrintMessage("Actions: Black, Click anywhere");
			break;

		case COLOR_BLUE:
			pOut->PrintMessage("Actions: Blue, Click anywhere");
			break;

		case COLOR_GREEN:
			pOut->PrintMessage("Actions: Green, Click anywhere");
			break;

		case COLOR_WHITE:
			pOut->PrintMessage("Actions: White, Click anywhere");
			break;

		case COLOR_RED:
			pOut->PrintMessage("Actions: Red, Click anywhere");
			break;

		case MUTE:
			pOut->PrintMessage("Actions: Mute, Click anywhere");
			break;

		case UNMUTE:
			pOut->PrintMessage("Actions: UnMute, Click anywhere");
			break;

		case SAVE_CIRCLE:
			pOut->PrintMessage("Actions: Save Circle, Click anywhere");
			break;

		case SAVE_TRI:
			pOut->PrintMessage("Actions: Save Triangle, Click anywhere");
			break;

		case SAVE_RHOMBUS:
			pOut->PrintMessage("Actions: Save Rhombus, Click anywhere");
			break;

		case SAVE_ELLISPE:
			pOut->PrintMessage("Actions: Save Ellipse, Click anywhere");
			break;

		case SAVE_LINE:
			pOut->PrintMessage("Actions: Save Line, Click anywhere");
			break;

		case SAVE_RECT:
			pOut->PrintMessage("Actions: Save Rect, Click anywhere");
			break;

		case SEND_BACK:
			pOut->PrintMessage("Actions: Send To Back, Click anywhere");
			break;

		case BRING_FRONT:
			pOut->PrintMessage("Actions: Bring To Front, Click anywhere");
			break;

		case RESIZE_QUARTER:
			pOut->PrintMessage("Actions: Resize x1/4, Click anywhere");
			break;

		case RESIZE_HALF:
			pOut->PrintMessage("Actions: Resize x1/2, Click anywhere");
			break;

		case RESIZE_DOUBLE:
			pOut->PrintMessage("Actions: Resize x2, Click anywhere");
			break;

		case RESIZE_FOUR_TIMES:
			pOut->PrintMessage("Actions: Resize x4, Click anywhere");
			break;

		case DEL:
			pOut->PrintMessage("Actions: Delete, Click anywhere");
			break;

		case SAVE:
			pOut->PrintMessage("Actions: Save, Click anywhere");
			break;

		case SAVE_BY_TYPE:
			pOut->PrintMessage("Actions: Save By Type, Click anywhere");
			pOut->CreateSaveByTypeToolBar();
			break;

		case LOAD:
			pOut->PrintMessage("Actions: Load, Click anywhere");
			break;

		case STATUS:
			pOut->PrintMessage("Action: a click on the Status Bar, Click anywhere");
			break;

		case DRAWING_AREA:
			pOut->PrintMessage("Action: a click on the Drawing Area, Click anywhere");
			break;

		case EMPTY:
			pOut->PrintMessage("Action: a click on empty area in the Design Tool Bar, Click anywhere");
			break;

		case TO_DRAW:
			pOut->PrintMessage("Action: Switch to Draw Mode, creating simualtion tool bar");
			pOut->CreateDrawToolBar();
			break;

		case TO_PLAY:
			pOut->PrintMessage("Action: Switch to Play Mode, creating Design tool bar");
			pOut->CreatePlayToolBar();
			break;

		case EXIT:
			break;
		}
	} while (ActType != EXIT);


	/// Exiting
	pOut->PrintMessage("Action: EXIT, test is finished, click anywhere to exit");
	pIn->GetPointClicked(x, y);


	delete pIn;
	delete pOut;
	return 0;
}


