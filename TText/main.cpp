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
				text.DownCount(&step);

				if (GoNext(step)) {
					text.goNextLink();
				}

				std::cout << step << std::endl;

				Sleep(150);
			}

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