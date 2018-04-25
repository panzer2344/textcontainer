#include "TLink.h"

TLink::TLink(char *string, TLink *pN, TLink *pD) {
	pNext = pN;
	pDown = pD;
	if (string == NULL) str[0] = '\0';
	else strcpy(str, string);
}


std::ofstream& operator<<(std::ofstream &ofs, const TLink &link){
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
	strncpy(str, string, STRMAX);
}

void* TLink::operator new(size_t size) {
	TLink* tmp = (TLink*)mem.pFree;
	if (mem.pFree != NULL) {
		mem.pFree = ((TLink*)mem.pFree)->pNext;
	}

	return tmp;
}

void TLink::operator delete(void* p) {
	TLink* tmp = (TLink*)p;

	tmp->pNext = (TLink*)mem.pFree;
	str = "";
	mem.pFree = tmp;
}


