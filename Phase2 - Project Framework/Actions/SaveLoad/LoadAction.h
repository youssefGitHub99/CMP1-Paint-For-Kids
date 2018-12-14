#pragma once
#include "../Action.h"
#include "SaveLoadUtility.h"
#include "../../ApplicationManager.h"
#include <fstream>
#include <algorithm>

class LoadAction : public Action
{
	
	ifstream* pInputFileStream;
	bool managedToOpen;

	FileLinesFormat getLineFormat(int lineCounter, float firstWordInLine); // Word should be validated first.
	FileLinesFormat getFigureFromLine(float firstWordInLine);
	void setLineDescription(FileLinesFormat lineFormat, const WordType*& descriptionArr, int& arrSize);
	bool getCorrectWordType(int wordCounter, const WordType* descriptionArr, int size, WordType& type);
	void getWordRangeExclusive(WordType type, int& min, int& max);
	bool validateWord(float currentWord, WordType correctType);

	void translateFigureWords(const float* figureWords, CFigure** loadedFigures, int& currentLoadedFiguresIndex);
	bool readAndValidateFile(CFigure** loadedFigures);
	void replaceOldFigsWithNew(CFigure** loadedFigures);
	//void keywordsIntoColors();

	/// Delete *loadedFiguers & *figureWords.

public:
	LoadAction(ApplicationManager * pApp);
	~LoadAction();

	//Reads rectangle parameters
	virtual void ReadActionParameters();

	//Add rectangle to the ApplicationManager
	virtual void Execute();
};

