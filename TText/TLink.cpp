#pragma once
#include "TLink.h"

TMem TLink::mem;

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

void TLink::setstr(const char* string) {
	strncpy(str, string, STRMAX);
}

void* TLink::operator new(size_t s) {
	TLink *tmp = mem.pFree;
	
	if (mem.pFree != NULL) 
		mem.pFree = mem.pFree->pNext;
	
	return tmp;
}

void TLink::operator delete(void* p) {
	TLink *tmp = (TLink*)p;
	
	tmp->pNext = mem.pFree;
	mem.pFree = tmp;
}

void TLink::InitMem(size_t s) {
	mem.pFirst = (TLink*) new char[sizeof(TLink)*s];
	mem.pFree = mem.pFirst;
	mem.pLast = mem.pFirst + (s - 1);
	TLink *tmp = mem.pFree;
	for (int i = 0; i < s - 1; i++) {
		tmp->setstr("\\");
		tmp->pNext = tmp + 1;
		tmp++;
	}
	mem.pLast->pNext = NULL;
	mem.pLast->setstr("\\");
}

void TLink::MemClean(TText &txt) {
	if (txt.getFirst() == NULL) return;

	TLink* cur = txt.getCurr();
	std::stack<TLink* > tmpStack = txt.getStack();

	for (txt.Reset(); !txt.IsEnd(); txt.GoNext())
		strcat(txt.getCurr()->str, "*");
	TLink *tmp = mem.pFree;
	while (tmp != NULL) {
		strcpy(tmp->str, "*");
		tmp = tmp->pNext;
	}
	tmp = mem.pFirst;
	while (tmp != mem.pLast) {
		if (strlen(tmp->str) != 1)
			tmp->str[strlen(tmp->str) - 1] = '\0';
		tmp++;
	}

	txt.setCurr(cur);
	txt.setStack(tmpStack);
}

void TLink::printFree() {
	TLink *tmp = mem.pFree;
	while (tmp != NULL) {
		if (!strcmp(tmp->str, "\\")) { 
			break;
		}

		std::cout << tmp->str << std::endl;
		tmp = tmp->pNext;
	}
}

TLink* TLink::getNext() {
	return pNext;
}

TLink* TLink::getDown() {
return pDown;
}

void TLink::setNext(TLink* tlNext) {
	pNext = tlNext;
}

void TLink::setDown(TLink* tlDown) {
	pDown = tlDown;
}

void TLink::mark() {
	marked = true;
}

void TLink::unmark() {
	marked = false;
}

bool TLink::isMarked() {
	return marked;
}


