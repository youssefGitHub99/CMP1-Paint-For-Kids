#include "ApplicationManager.h"

int main()
{

	ActionType ActType;
	//Create an object of ApplicationManager
	ApplicationManager AppManager;

	do {		
		//Read user action
		ActType = AppManager.GetUserAction();

		//Exexute the action
		AppManager.ExecuteAction(ActType);

		//Update the interface
		AppManager.UpdateInterface();	

	} while (ActType != EXIT);
	
	return 0;
}

bool operator==(color a, color b) {
	return
		a.ucRed == b.ucRed &
		a.ucGreen == b.ucGreen &
		a.ucBlue == b.ucBlue;
}

bool operator!=(color a, color b) {
	return !(a == b);
}
