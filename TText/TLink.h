#pragma once
#include <iostream>
#include <fstream>
#include <string>

struct TMem {
	void *pFirst, *pFree, *pLast;
};

class TLink {
public:
	static const int STRMAX = 80;
	char str[STRMAX];
	TLink *pNext, *pDown;
	static TMem mem;

	TLink(char *string = NULL, TLink *pN = NULL, TLink *pD = NULL);

	char& operator[](size_t i);
	char* getstr();
	void setstr(char* string);

	friend std::ofstream& operator<<(std::ofstream& ofs, const TLink& link);
	friend std::ifstream& operator >> (std::ifstream& ifs, TLink& link);

	void* operator new(size_t size);
	void operator delete(void* p);

};


