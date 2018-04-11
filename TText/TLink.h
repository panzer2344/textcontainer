#pragma once
#include <iostream>
#include <fstream>
#include <string>

struct TMem{
	TLink* pFirst, pFree, pLast;
}

class TLink {
private:
	const int STRMAX = 80;
	char str[STRMAX];
	TLink *pNext, *pDown;
	static TMem mem;

public:
	TLink(char *string = NULL, TLink *pN = NULL, TLink *pD = NULL);

	char& operator[](size_t i);
	char* getstr();
	void setstr(char* string);

	friend std::ofstream& operator<<(std::ofstream& ofs, const TLink& link);
	friend std::ifstream& operator>>(std::ifstream& ifs, TLink& link);
};
