#pragma once
#include "../Action.h"
#include "SaveLoadUtility.h"
#include "../../ApplicationManager.h"
#include <fstream>

enum SaveType {
	SAVE_TYPE_ALL, 
	SAVE_TYPE_RECT,
	SAVE_TYPE_LINE, 
	SAVE_TYPE_TRI, 
	SAVE_TYPE_RHOMBUS, 
	SAVE_TYPE_ELLIPSE, 
	SAVE_TYPE_CIRCLE
};

class SaveAction : public Action
{
	SaveType saveType;
	ofstream* pOutputFileStream;
	bool managedToOpen;
	int numOfFiguresToSave;

	CheckExtensionProbabilities checkExtension(std::string& path);

	void setNumOfFiguresToSave();
	bool dontSaveCuzThereIsNoFigures();

	static void colorsIntoKeywords(GfxInfo gfxInfo, ReservedKeywords& drawColor, ReservedKeywords& fillColor);

public:
	SaveAction(ApplicationManager * pApp, SaveType saveType);
	~SaveAction();

	//Reads rectangle parameters
	virtual void ReadActionParameters();

	//Add rectangle to the ApplicationManager
	virtual void Execute();



	friend ofstream& operator<<(ofstream& ouput, CLine& line);
	friend ofstream& operator<<(ofstream& ouput, CRectangle& rect);
	friend ofstream& operator<<(ofstream& ouput, CTriangle& tri);
	friend ofstream& operator<<(ofstream& ouput, CRhombus& rho);
	friend ofstream& operator<<(ofstream& ouput, CCircle& circ);
	friend ofstream& operator<<(ofstream& ouput, CEllipse& elli);
};

