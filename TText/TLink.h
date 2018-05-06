#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>

#include "TText.h"

class TLink;
class TText;

struct TMem {
	TLink *pFirst, *pFree, *pLast;
};

class TLink {
	static const int STRMAX = 80;
	char str[STRMAX];
	TLink *pNext, *pDown;
	static TMem mem;

public:
	TLink(char *string = NULL, TLink *pN = NULL, TLink *pD = NULL);

	char& operator[](size_t i);

	char* getstr();
	void setstr(char* string);
	void setstr(const char* string);

	TLink* getNext();
	TLink* getDown();

	void setNext(TLink*);
	void setDown(TLink*);

	friend std::ofstream& operator<<(std::ofstream& ofs, const TLink& link);
	friend std::ifstream& operator >> (std::ifstream& ifs, TLink& link);

	static void* operator new(size_t size);
	static void operator delete(void* p);

	static void InitMem(size_t s);
	static void MemClean(TText &txt);
	static void printFree();
};


