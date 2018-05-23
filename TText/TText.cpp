#pragma once
#include "TText.h"

TText::TText() {
	pFirst = pCurrent = NULL;
}

void TText::goNextLink() {
	if (pCurrent->getNext() != NULL) {
		st.push(pCurrent);
		pCurrent = pCurrent->getNext();
	}
}

void TText::goDownLink() {
	if (pCurrent->getDown() != NULL) {
		st.push(pCurrent);
		pCurrent = pCurrent->getDown();
	}
}

void TText::goPrevLink() {
	if (!st.empty()) { 
		pCurrent = st.top();
		st.pop();
	}
}

void TText::InsertNextLine(char *line) {
	TLink *NewLink;
	if(pCurrent != NULL){
		NewLink = new TLink(line, pCurrent->getNext(), NULL);
		pCurrent->setNext(NewLink);
	}
	else{
		NewLink = new TLink(line, NULL, NULL);
		pFirst = pCurrent = NewLink;
	}
}

void TText::InsertNextSection(char *line) {
	TLink *NewLink;
	if(pCurrent != NULL){
		NewLink = new TLink(line, NULL, pCurrent->getNext());
		pCurrent->setNext(NewLink);
	}
	else{
		NewLink = new TLink(line, NULL, NULL);
		pFirst = pCurrent = NewLink;
	}
}

void TText::InsertDownLine(char *line) {
	TLink *NewLink;
	if(pCurrent != NULL){
		NewLink = new TLink(line, pCurrent->getDown(), NULL);
		pCurrent->setDown(NewLink);
	}
	else{
		NewLink = new TLink(line, NULL, NULL);
		pFirst = pCurrent = NewLink;
	}
}

void TText::InsertDownSection(char *line) {
	TLink *NewLink;
	if(pCurrent != NULL){
		NewLink = new TLink(line, NULL, pCurrent->getDown());
		pCurrent->setDown(NewLink);
	}
	else{
		NewLink = new TLink(line, NULL, NULL);
		pFirst = pCurrent = NewLink;
	}
}

void TText::DeleteNext() {
	if (pCurrent->getNext() != NULL) {
		TLink *tmp = pCurrent->getNext();
		pCurrent->setNext(tmp->getNext());
		delete tmp;
	}
}

void TText::DeleteDown() {
	if (pCurrent->getDown() != NULL) {
		TLink *tmp = pCurrent->getDown();
		pCurrent->setDown(tmp->getNext());
		delete tmp;
	}
}


TLink* TText::RecursiveRead(std::ifstream& file) {
	char buffer[80];
	TLink *tmp = NULL, *pFirst = NULL;
	
	while (!file.eof()) {
		file.getline(buffer, 80, '\n');

		if (buffer[0] == '}') {
			break;
		}
		else if (buffer[0] == '{') {
			tmp->setDown(RecursiveRead(file));
		}
		else {
			if (pFirst == NULL) {
				pFirst = new TLink(buffer);
				pCurrent = pFirst; // 06051018 1442
				tmp = pFirst;
			}
			else {
				TLink *tmpLink = new TLink(buffer);
				tmp->setNext(tmpLink);
				tmp = tmp->getNext();
				pCurrent = tmp;
			}
		}
	}
	
	return pFirst;
}

void TText::Read(char *fn) {
	std::ifstream ifs(fn);
	if (ifs.bad()) return;

	pFirst = RecursiveRead(ifs);
}

void TText::RecursivePrint(TLink *tmp) {
	if(tmp != NULL){
		for(int i = 0; i < level; i++){
			std::cout << ' ';
		}
		std::cout << tmp->getstr() << std::endl;
		level++;
		RecursivePrint(tmp->getDown());
		level--;
		RecursivePrint(tmp->getNext());
	}
}

void TText::Print() {
	level = 0;
	RecursivePrint(pFirst);
}

void TText::RecursiveSaveText(TLink *tmp, std::ofstream& ofs) {
	ofs << std::string(tmp->getstr()) << std::endl;
	if(tmp->getDown() != NULL){
		ofs << std::string("{") << std::endl;
		RecursiveSaveText(tmp->getDown(), ofs);
		ofs << std::string("}") << std::endl;
	}

	if(tmp->getNext() != NULL){
		RecursiveSaveText(tmp->getNext(), ofs);
	}
}

void TText::SaveToFile(std::string filename) {
	std::ofstream ofs(filename);
	RecursiveSaveText(pFirst, ofs);
}


void TText::SetLine(const char* string){
	if(strcmp(string, "")){
		//strcpy(pCurrent->str, string);
		pCurrent->setstr(string);
	}else{
		goPrevLink();
		DeleteNext();
	}
}

const char* TText::GetLine(){
	return pCurrent->getstr();
}

void TText::Reset() {
	pCurrent = pFirst;
	clearStack(st);
	st.push(pCurrent);
}


bool TText::IsEnd() {
	return st.empty();
}


void TText::GoNext() {
	pCurrent = st.top();
	st.pop();

	if (pCurrent != pFirst) {
		if (pCurrent->getDown())
			st.push(pCurrent->getDown());
		if (pCurrent->getNext())
			st.push(pCurrent->getNext());
	}
}

int TText::DownCount() {
	TLink *tmp = pCurrent;
	std::stack<TLink* > tmpStack;
	int tmpSize = 0;
	int count = 0;

	if (pCurrent->getDown() == NULL) return 0;
	pCurrent = pCurrent->getDown();

	tmpStack = st;
	clearStack(st);
	st.push(pCurrent);

	do {
		GoNext();
		pCurrent->unmark();
	} while (!IsEnd());

	pCurrent = tmp->getDown();
	st.push(pCurrent);

	do {
		GoNext();
		if (!pCurrent->isMarked()) {
			count++;
			pCurrent->mark();
		}
	} while (!IsEnd());

	st = tmpStack;
	pCurrent = tmp;

	return count;
}

void TText::clearStack(std::stack<TLink* >& stack) {
	while (!stack.empty()) {
		stack.pop();
	}
}

bool TText::HaveNext() {
	return (pCurrent->getNext() != NULL);
}

bool TText::HaveDown(){
	return (pCurrent->getDown() != NULL);
}

TLink* TText::getCurr() {
	return pCurrent;
}

void TText::setCurr(TLink* _pCurr) {
	pCurrent = _pCurr;
}

bool TText::isDownLevel() {
	TLink *tmp = st.top();
	st.pop();
	st.push(tmp);

	return tmp->getDown() == pCurrent;
}

int TText::GetLevel() {
	return level;
}

TLink* TText::getFirst() {
	return pFirst;
}

void TText::setFirst(TLink* _first) {
	pFirst = _first;
}





