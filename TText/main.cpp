#include "TText.h"
#include <Windows.h>

#include <iostream>

#include <string>

void cls()
{
	COORD coordScreen = { 0, 0 }; 
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi)){
		return;
	}

	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	if (!FillConsoleOutputCharacter(hConsole, (TCHAR) ' ', dwConSize, coordScreen, &cCharsWritten)){
		return;
	}

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi)){
		return;
	}

	if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes,	dwConSize,coordScreen, &cCharsWritten)){
		return;
	}

	SetConsoleCursorPosition(hConsole, coordScreen);
}

bool WhereCursor(COORD &coord) {
	HANDLE hndlOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(hndlOut, &csbi)) {
		coord.X = csbi.dwCursorPosition.X;
		coord.Y = csbi.dwCursorPosition.Y;

		return true;
	}
	else return false;
}

bool MoveCursor(int deltaX, int deltaY) {
	HANDLE hndlOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = {0, 0};

	if(!WhereCursor(coord)) return false;
	
	coord.X += deltaX;
	coord.Y += deltaY;

	if ((coord.X < 0) || (coord.Y < 0)) return false;

	if(!SetConsoleCursorPosition(hndlOut, coord))
		return false;

	return true;
}

bool SetCursorPos(COORD coord) {
	HANDLE hndlOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if(!SetConsoleCursorPosition(hndlOut, coord))
		return false;
	else return true;
}

bool GoNext(int step) {
	if(!MoveCursor(0, step))
		return false;
	return true;
}

//int main() {
//	TText text;
//	TLink::InitMem(100);
//
//	text.InsertNextLine(" ");
//	text.InsertNextLine("l1");
//	text.goNextLink();
//	text.InsertDownLine("l1.1");
//	text.goDownLink();
//	text.InsertDownLine("l1.1.1");
//	text.goDownLink();
//	text.InsertNextLine("l1.2.1");
//	text.goNextLink();
//
//	text.goPrevLink();
//	text.goPrevLink();
//	text.goPrevLink();
//	
//	text.InsertNextLine("l2");
//	text.goNextLink();
//	text.InsertDownLine("l2.1");
//	text.goDownLink();
//	text.InsertDownLine("l2.1.1");
//	text.goDownLink();
//	text.InsertNextLine("l2.1.2");
//	text.goNextLink();
//
//	text.goPrevLink();
//	text.goPrevLink();
//	
//	text.InsertNextLine("l2.2");
//	text.goNextLink();
//
//	text.goPrevLink();
//	text.goPrevLink();
//	
//	text.Reset();
//
//	text.Print();
//
//	getchar();
//
//	return 0;
//}

int main() {
	TText text;
	TLink::InitMem(2000);
	COORD coord = {0, 0};

	text.InsertNextLine(" ");
	text.InsertNextLine("l1");
	text.goNextLink();
	text.InsertDownLine("l1.1");
	text.goDownLink();
	text.InsertDownLine("l1.1.1");
	text.InsertDownLine("l1.2.1");
	text.Reset();

	while (true) {
		bool exit = false;

		text.Print();
		SetCursorPos(coord);

		while (true) {
			if (GetAsyncKeyState(VK_DOWN)) {
				int step = 0;
				step = text.DownCount() + 1;

				if (text.HaveNext()) { 
					if (GoNext(step)) {
						text.goNextLink();
					}
				}
				else {
					char tmpStr[80];
					int tmpStrLen = 0;

					text.InsertNextLine(" ");
					text.goNextLink();
					WhereCursor(coord);
					cls();
					text.Print();
					SetCursorPos(coord);
					GoNext(step);
					WhereCursor(coord);

					std::cout << "print here(to undo input - write /back): ";
					std::cin >> tmpStr;

					tmpStrLen = strlen(tmpStr);

					if (!strcmp(tmpStr, "/back")) {
						MoveCursor(0, -1);
						std::cout << "                                              ";
						MoveCursor(-46, -step);
						text.goPrevLink();
						text.DeleteNext();
					}
					else {
						text.SetLine(tmpStr);
						SetCursorPos(coord);
						std::cout << "                                         ";

						for (int i = 0; i < tmpStrLen; i++) {
							std::cout << " ";
						}
						MoveCursor(-41, 0);
						MoveCursor(-tmpStrLen, 0);
								
						std::cout << tmpStr;
						MoveCursor(-tmpStrLen, 0);
					}
			}

				Sleep(150);
			}

			if (GetAsyncKeyState(VK_UP)) {
				int step = 0;
				TLink* tmplink = text.getCurr();

				WhereCursor(coord);

				if (coord.Y != 0) {

					text.goPrevLink();
					if (text.getCurr() != tmplink) {
						if (text.getCurr()->getDown() == tmplink) {
							if (coord.Y != 1) MoveCursor(-1, -1);
						}
						else {
							step = -text.DownCount() - 1;
							GoNext(step);
						}
					}
				}
				Sleep(150);
			}

			if (GetAsyncKeyState(VK_RIGHT)) {
				if (text.HaveDown()) {
					text.goDownLink();
					MoveCursor(1, 1);
				}
				else {
					char tmpStr[80];
					int tmpStrLen;

					text.InsertDownLine(" ");
					text.goDownLink();
					WhereCursor(coord);
					cls();
					text.Print();
					SetCursorPos(coord);
					MoveCursor(1, 1);
					WhereCursor(coord);
					std::cout << "input(to undo - write /back):";
					std::cin >> tmpStr;

					tmpStrLen = strlen(tmpStr);

					if (!strcmp(tmpStr, "/back")) {
						MoveCursor(0, -1);
						std::cout << "                                  ";
						MoveCursor(-36, -1);
						text.goPrevLink();
						text.DeleteDown();
					}
					else {
						text.SetLine(tmpStr);
						SetCursorPos(coord);
						
						std::cout << "                             ";
						for (int i = 0; i < tmpStrLen; i++) {
							std::cout << " ";
						}
						MoveCursor(-tmpStrLen - 29, 0);
						std::cout << tmpStr;
						MoveCursor(-tmpStrLen, 0);
					}
				}
				Sleep(150);
			}

			if (GetAsyncKeyState(VK_TAB) && !GetAsyncKeyState(VK_LCONTROL)) {
				char tmpStr[80];
				int tmpStrLen;

				text.InsertDownSection(" ");
				text.goDownLink();

				WhereCursor(coord);
				cls();
				text.Print();
				SetCursorPos(coord);
				MoveCursor(1, 1);
				WhereCursor(coord);
				std::cout << "input: ";
				std::cin >> tmpStr;

				tmpStrLen = strlen(tmpStr);

				text.SetLine(tmpStr);
				SetCursorPos(coord);

				MoveCursor(-8, 0);
				std::cout << "       ";
				for (int i = 0; i < tmpStrLen; i++) {
					std::cout << " ";
				}
				MoveCursor(-tmpStrLen - 7, 0);
				std::cout << tmpStr;
				MoveCursor(-tmpStrLen, 0);

				Sleep(150);
			}

			if (GetAsyncKeyState(VK_TAB) && GetAsyncKeyState(VK_LCONTROL)) {
				char tmpStr[80];
				int tmpStrLen;
				int step = text.DownCount() + 1;

				text.InsertNextSection(" ");
				text.goNextLink();

				WhereCursor(coord);
				cls();
				text.Print();
				SetCursorPos(coord);
				GoNext(step);
				WhereCursor(coord);
				std::cout << "input: ";
				std::cin >> tmpStr;

				tmpStrLen = strlen(tmpStr);

				text.SetLine(tmpStr);
				SetCursorPos(coord);

				MoveCursor(-8, 0);
				std::cout << "       ";
				for (int i = 0; i < tmpStrLen; i++) {
					std::cout << " ";
				}
				MoveCursor(-tmpStrLen - 7, 0);
				std::cout << tmpStr;
				MoveCursor(-tmpStrLen, 0);

				Sleep(150);
			}

			if (!GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(VK_DELETE)) {
				if (text.getCurr()->getstr() != " ") {
					TLink* tmpLink = text.getCurr();

					text.goPrevLink();
					if (text.getCurr() == tmpLink) {
						text.Reset();
					}
					if (text.getCurr()->getDown() == tmpLink) {
						text.DeleteDown();
						if(text.HaveDown()) text.goDownLink();
						else MoveCursor(-1, -1);
					}
					else {
						text.DeleteNext();
						if(text.HaveNext()) text.goNextLink();
						else MoveCursor(0, -1);
					}
					
					WhereCursor(coord);
					cls();
					text.Print();
					SetCursorPos(coord);
				}				

				TLink::MemClean(text);
				Sleep(150);
			}

			if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(VK_DELETE)) {
				cls();

				TLink::MemClean(text);
				TLink::printFree();

				Sleep(150);
			}

			if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(0x53)) {
				char filename[1024];

				WhereCursor(coord);
				cls();

				std::cout << "Enter the file name for record(or /back to return): ";
				std::cin >> filename;
				if (strcmp(filename, "/back")) {
					text.SaveToFile(filename);
				}

				cls();
				text.Print();
				SetCursorPos(coord);

				Sleep(150);
			}

			if (GetAsyncKeyState(VK_F1)) {
				char filename[1024];

				WhereCursor(coord);
				cls();

				std::cout << "Enter the file name for record(or /back to return): ";
				std::cin >> filename;
				if (strcmp(filename, "/back")) {
					if (GetFileAttributes(filename) != DWORD(-1)) {
						text.Read(filename);
					}
					coord = { 0, 0 };
					text.Reset();
				}

				cls();
				text.Print();
				SetCursorPos(coord);

				Sleep(150);
			}

			

			if (GetAsyncKeyState(VK_ESCAPE)) {
				exit = true;
				Sleep(50);
				break;
			}

			WhereCursor(coord);
			if (coord.Y = 0) coord.Y = 1;
		}

		if (exit) break;
	}

	return 0;
}