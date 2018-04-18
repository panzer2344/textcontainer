//#define _WIN32_WINNT

#include "TText.h"
#include <Windows.h>
#include <conio.h>
#include <strsafe.h>
#include <tchar.h>

int main() {
	TText text;
	TCHAR szNewTitle[MAX_PATH];
	//HWND hndl;
	HANDLE hndl;
	_COORD coord = { 0, 0 };

	std::cout << " " << std::endl;

	//hndl = GetConsoleWindow();

	StringCchPrintf(szNewTitle, MAX_PATH, TEXT("Text Editor"));
	if (!SetConsoleTitle(szNewTitle)) {
		std::cout << "setConsoleTitle failed" << std::endl;
	}


	//hndl = FindWindow(NULL, szNewTitle);
	//hndl = GetConsoleWindow();
	
	hndl = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hndl == NULL) {
		std::cout << "getConsoleWindow error" << std::endl;
	}


	if (!SetConsoleTextAttribute(hndl,
		FOREGROUND_GREEN | BACKGROUND_BLUE)) {
		std::cout << "SetConsoleTextAttribute error" << std::endl;
	}

	SetConsoleCursorPosition(hndl, coord);

	text.InsertNextLine("abcde");
	text.Print();

	SetConsoleCursorPosition(hndl, coord);

	text.InsertNextLine("fghi");
	text.Print();

	SetConsoleCursorPosition(hndl, coord);

	text.InsertDownLine("jklmnop");
	text.Print();

	SetConsoleCursorPosition(hndl, coord);

	text.InsertNextSection("arma3");
	text.Print();

	SetConsoleCursorPosition(hndl, coord);

	text.InsertDownSection("boris-britva");
	text.Print();

	int a;
	std::cin >> a;
	std::cout << a;

	return 0;
}