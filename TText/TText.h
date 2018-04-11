// todo: write tests
#pragma once
#include "TLink.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <string>

class TText {
	TLink *pFirst, *pCurrent;
	std::stack<TLink*> st;
	int level;

public:
	TText();
	void goNextLink();
	void goDownLink();
	void goPrevLink();
	void InsertNextLine(char *line);
	void InsertNextSection(char *line);
	void InsertDownLine(char *line);
	void InsertDownSection(char *line);
	void DeleteNext();
	void DeleteDown();
	void SetLine(const char* string); 
	const char* GetLine(); 

	TLink* RecursiveRead(std::ifstream& file);
	void Read(char *fn);
	void RecursivePrint(TLink *tmp);
	void Print();
	void RecursiveSaveText(TLink *tmp, std::ofstream& ofs);
	void SaveToFile(std::string filename);
}; 