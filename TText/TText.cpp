#include "TText.h"

TText::TText() {
	pFirst = pCurrent = NULL;
}

void TText::goNextLink() {
	if (pCurrent->pNext != NULL) {
		st.push(pCurrent);
		pCurrent = pCurrent->pNext;
	}
}

void TText::goDownLink() {
	if (pCurrent->pDown != NULL) {
		st.push(pCurrent);
		pCurrent = pCurrent->pDown;
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
		NewLink = new TLink(line, pCurrent->pNext, NULL);
		pCurrent->pNext = NewLink;
	}
	else{
		NewLink = new TLink(line, NULL, NULL);
		pFirst = pCurrent = NewLink;
	}
}

void TText::InsertNextSection(char *line) {
	TLink *NewLink;
	if(pCurrent != NULL){
		NewLink = new TLink(line, NULL, pCurrent->pNext);
		pCurrent->pNext = NewLink;
	}
	else{
		NewLink = new TLink(line, NULL, NULL);
		pFirst = pCurrent = NewLink;
	}
}

void TText::InsertDownLine(char *line) {
	TLink *NewLink;
	if(pCurrent != NULL){
		NewLink = new TLink(line, pCurrent->pDown, NULL);
		pCurrent->pDown = NewLink;
	}
	else{
		NewLink = new TLink(line, NULL, NULL);
		pFirst = pCurrent = NewLink;
	}
}

void TText::InsertDownSection(char *line) {
	TLink *NewLink;
	if(pCurrent != NULL){
		NewLink = new TLink(line, NULL, pCurrent->pDown);
		pCurrent->pDown = NewLink;
	}
	else{
		NewLink = new TLink(line, NULL, NULL);
		pFirst = pCurrent = NewLink;
	}
}

void TText::DeleteNext() {
	if (pCurrent->pNext != NULL) {
		TLink *tmp = pCurrent->pNext;
		pCurrent->pNext = tmp->pNext;
		delete tmp;
	}
}

void TText::DeleteDown() {
	if (pCurrent->pDown != NULL) {
		TLink *tmp = pCurrent->pDown;
		pCurrent->pDown = tmp->pNext;
		delete tmp;
	}
}


TLink* TText::RecursiveRead(std::ifstream& file) {
	char buffer[80];
	TLink *tmp = NULL, *pFirst;
	
	while (!file.eof()) {
		file.getline(buffer, 80, '\n');

		if (buffer[0] == '}') {
			break;
		}
		else if (buffer[0] == '{') {
			tmp->pDown = RecursiveRead(file);
		}
		else {
			if (pFirst == NULL) {
				pFirst = new TLink(buffer);
				tmp = pFirst;
			}
			else {
				tmp->pNext = new TLink(buffer);
				tmp = tmp->pNext;
			}
		}
	}
	
	return pFirst;
}

void TText::Read(char *fn) {
	std::ifstream ifs(fn);
	pFirst = RecursiveRead(ifs);
}

void TText::RecursivePrint(TLink *tmp) {
	if(tmp != NULL){
		for(int i = 0; i < level; i++){
			std::cout << ' ';
		}
		std::cout << tmp->str << std::endl;
		level++;
		RecursivePrint(tmp->pDown);
		level--;
		RecursivePrint(tmp->pNext);
	}
}

void TText::Print() {
	level = 0;
	RecursivePrint(pFirst);
}

void TText::RecursiveSaveText(TLink *tmp, std::ofstream& ofs) {
	ofs << std::string(tmp->str) << std::endl;
	if(tmp->pDown != NULL){
		ofs << std::string("{") << std::endl;
		RecursiveSaveText(tmp->pDown, ofs);
		ofs << std::string("}") << std::endl;
	}

	if(tmp->pNext != NULL){
		RecursiveSaveText(tmp->pNext, ofs);
	}
}

void TText::SaveToFile(std::string filename) {
	std::ofstream ofs(filename);
	RecursiveSaveText(pFirst, ofs);
}


void TText::SetLine(const char* string){
	if(strcmp(string, "")){
		strcpy(pCurrent->str, string);
	}else{
		goPrevLink();
		DeleteNext();
	}
}

const char* TText::GetLine(){
	return pCurrent->str;
}




