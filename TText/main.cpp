#include "TText.h"
#include <Windows.h>

#include <string>

void PrintMenu(int flag) {
	
	if (flag & 1) {
		std::cout << "0 - write next line" << std::endl;
	}

	if (flag & 2) {
		std::cout << "1 - write down line" << std::endl;
	}

	if (flag & 4) {
		std::cout << "2 - write next section" << std::endl;
	}

	if (flag & 8) {
		std::cout << "3 - write down section" << std::endl;
	}
	
	if (flag & 16) {
		std::cout << "4 - exit program" << std::endl;
	}

	if (flag & 32) {
		std::cout << "5 - print menu" << std::endl;
	}
}

void Input(int &state, std::string &_in) {
	if (state == 1) {
		std::cin >> _in;
	}
	state = 0;
}

int main() {
	TText text;
	std::string input;

	HANDLE hndlOut;
	HANDLE hndlIn;
	HWND hwndConsole;

	hndlOut = GetStdHandle(STD_OUTPUT_HANDLE);
	hndlIn = GetStdHandle(STD_INPUT_HANDLE);

	hwndConsole = GetConsoleWindow();

	while (1) {
		int state = 1;

		SetConsoleTextAttribute(hndlOut, FOREGROUND_RED | BACKGROUND_BLUE);
		PrintMenu(1);

		SetConsoleTextAttribute(hndlOut, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
		SetConsoleTextAttribute(hndlOut, COMMON_LVB_REVERSE_VIDEO);
		SetConsoleTextAttribute(hndlOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		PrintMenu(62);

		std::cout << std::endl << std::endl << "Print there: ";
		Input(state, input);
		if (!state) std::system("cls");
	}

	return 0;
}