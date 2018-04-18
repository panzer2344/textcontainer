#define _CRT_SECURE_NO_WARNINGS

#include "TLink.h"


TLink::TLink(char *string, TLink *pN, TLink *pD) {
	pNext = pN;
	pDown = pD;
	if (string == NULL) str[0] = '\0';
	else strcpy(str, string);
}


std::ofstream& operator<<(std::ofstream& ofs, const TLink& link){
	ofs << link.str;

	return ofs;
}

std::ifstream& operator>>(std::ifstream& ifs, TLink& link){
	ifs >> link.str;

	return ifs;
}


char& TLink::operator[](size_t i){
	if( (i > STRMAX) && (i < 0)) throw "out of range in tlink::operator[]\n";
	return str[i]; 
}

char* TLink::getstr(){
	return str;
}

void TLink::setstr(char* string){
	strncpy_s(str, string, STRMAX);
}

TLink* TLink::getNext() {
	return pNext;
}

TLink* TLink::getDown() {
	return pDown;
}

void TLink::setNext(TLink* _next) {
	pNext = _next;
}

void TLink::setDown(TLink* _down) {
	pDown = _down;
}




