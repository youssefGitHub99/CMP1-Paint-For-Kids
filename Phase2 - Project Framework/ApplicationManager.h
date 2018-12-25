#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures\CFigure.h"
#include "GUI\input.h"
#include "GUI\output.h"
#include "Actions/SaveLoad/SaveAction.h"
#include "Actions/SaveLoad/LoadAction.h"

#include <Mmsystem.h>
#include <mciapi.h>
//these two headers are already included in the <Windows.h> header
#pragma comment(lib, "Winmm.lib")

#define MAXFIGCOUNT 200

//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxFigCount = MAXFIGCOUNT };	//Max no of figures

private:
	int FigCount;		//Actual number of figures
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)

	CFigure* SelectedFig; //Pointer to the selected figure
	CFigure* Clipboard;   //Pointer to the copied/cut figure
	int mode;
	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;

	bool soundMuted;

public:	
	
	ApplicationManager(); 
	~ApplicationManager();
	
	// -- Action-Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	void ExecuteAction(ActionType) ; //Creates an action and executes it
	
	// -- Figures Management Functions
	void AddFigure(CFigure* pFig);        //Adds a new figure to the FigList
	int getFigCount() const;
	void setFigCount(int figCount);
	int getMaxFigCount() const;
	template<typename T> int getNumOf() const;
	CFigure* GetFigure(int index) const;
	CFigure* GetFigure(int x, int y) const; //Search for a figure given a point inside the figure
	CFigure* GetSelectedFigure() const;
	void SetClipboardData(CFigure*  pFig, int imode);
	CFigure* getClipboardData();
	void removeSelection();
	void deleteSelectedFigure();
	void deleteCutFigure();
	void setmode(int m);
	void playSound(Action* pAct);
	bool aFigureMustBeSelectedFirst(CFigure *& selectedFigure);
	void deleteFigure(int id);

	// -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window

};

// It looks like we'll always get a SHITTY LINKER ERROR unless we implement the functions that use templates in the header files.
template<typename T> int ApplicationManager::getNumOf() const {
	int count = 0;
	for (int i = 0; i < FigCount; i++) {
		if (dynamic_cast<T*>(FigList[i]) != NULL) count++;
	}
	return count;
}
#endif