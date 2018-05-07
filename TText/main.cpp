#include "TText.h"
#include <Windows.h>

#include <iostream>

#include <string>

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

int main() {
	TText text;
	TLink::InitMem(2000);
	COORD coord = {0, 0};

	text.InsertNextLine("l1");
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

				if (GoNext(step)) {
					if (text.HaveNext()) { 
						text.goNextLink();
					}
					else {
						char tmpStr[80];
						int tmpStrLen = 0;

						std::cout << "print here(to undo input - write /back): ";
						std::cin >> tmpStr;

						tmpStrLen = strlen(tmpStr);

						if (!strcmp(tmpStr, "/back")) {
							MoveCursor(0, -1);
							std::cout << "                                              ";
							MoveCursor(-46, -step);
						}
						else {
							text.InsertNextLine(tmpStr);
							text.goNextLink();
							MoveCursor(0, -1);
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
				}

				Sleep(150);
			}

			if (GetAsyncKeyState(VK_UP)) {
				int step = 0;
				text.goPrevLink();
				step = - text.DownCount() - 1;

				GoNext(step);

				Sleep(150);
			}

			//if(GetAsyncKeyState(VK_UP))

			if (GetAsyncKeyState(VK_ESCAPE)) {
				exit = true;
				Sleep(50);
				break;
			}
		}

		if (exit) break;
	}

	return 0;
}