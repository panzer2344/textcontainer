#include "TText.h"

TText::TText() {
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
	TLink *NewLink = new TLink(line, pCurrent->pNext, NULL);
	pCurrent->pNext = NewLink;
}

void TText::InsertNextSection(char *line) {
	TLink *NewLink = new TLink(line, NULL, pCurrent->pNext);
	pCurrent->pNext = NewLink;
}

void TText::InsertDownLine(char *line) {
	TLink *NewLink = new TLink(line, pCurrent->pDown, NULL);
	pCurrent->pDown = NewLink;
}

void TText::InsertDownSection(char *line) {
	TLink *NewLink = new TLink(line, NULL, pCurrent->pDown);
	pCurrent->pDown = NewLink;
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
}

void RecursivePrint(TLink *tmp) {
}

void Print() {
}

void RecursiveSaveText(TLink *tmp, std::ofstream& ofs) {
}

void SaveToFile(std::string filename) {
}


