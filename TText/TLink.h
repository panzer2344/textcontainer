#pragma once
#include <iostream>


class TLink {
public:
	char str[80];
	TLink *pNext, *pDown;

	TLink(char *string = NULL, TLink *pN = NULL, TLink *pD = NULL);
	// todo: write input - output functions
};
