#include "TLink.h"

TLink::TLink(char *string = NULL, TLink *pN = NULL, TLink *pD = NULL) {
	pNext = pN;
	pDown = pD;
	if (string == NULL) str[0] = '\0';
	else strcpy(str, string);
}