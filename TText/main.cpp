#include "TText.h"
#include <Windows.h>

#include <string>

#define max 32
#define min 1

void UpMenu(int &flagBlue, short &pos) {
	if (flagBlue != min) {
		flagBlue = flagBlue >> 1;
		pos--;
	}
}

void DownMenu(int &flagBlue, short &pos) {
	if (flagBlue != max) {
		flagBlue = flagBlue << 1;
		pos++;
	}
}

void EnterMenu(int &flagBlue, TText &text, int &state) {
	char input[80];

	if (flagBlue & 1) {
		std::cin >> input;
		text.InsertNextLine(input);
		state = 1;
		text.Print();
	}

	if (flagBlue & 2) {
		std::cin >> input;
		text.InsertDownLine(input);
		state = 1;
		text.Print();
	}

	if (flagBlue & 4) {
		std::cin >> input;
		text.InsertNextSection(input);
		state = 1;
		text.Print();
	}

	if (flagBlue & 8) {
		std::cin >> input;
		text.InsertDownSection(input);
		state = 1;
		text.Print();
	}

	if (flagBlue & 16) {
		exit(0);
	}

	if (flagBlue & 32) {
		state = 0;
	}
}

void PrintMenu(int flag) {
	
	if (flag & 1) {
		std::cout << "0 - input next line" << std::endl;
	}

	if (flag & 2) {
		std::cout << "1 - input down line" << std::endl;
	}

	if (flag & 4) {
		std::cout << "2 - input next section" << std::endl;
	}

	if (flag & 8) {
		std::cout << "3 - input down section" << std::endl;
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

	int state = 1;
	int flagBlue = 1;
	short pos = 0;

	while (1) {

		SetConsoleTextAttribute(hndlOut, 15);
		PrintMenu(63);

		SetConsoleCursorPosition(hndlOut, { 0, pos });
		SetConsoleTextAttribute(hndlOut, FOREGROUND_RED | BACKGROUND_BLUE);
		PrintMenu(flagBlue);

		SetConsoleTextAttribute(hndlOut, 15);

		/*std::cout << std::endl << std::endl << "Print there: ";
		Input(state, input);*/

		while (1) {
		
			if (GetAsyncKeyState(VK_UP)) {
				UpMenu(flagBlue, pos);
				state = 0;
				Sleep(50);
				break;
			}

			if (GetAsyncKeyState(VK_DOWN)) {
				DownMenu(flagBlue, pos);
				state = 0;
				Sleep(50);
				break;
			}

			if (GetAsyncKeyState(VK_RETURN)) {
				SetConsoleCursorPosition(hndlOut, { 0, 5 });
				EnterMenu(flagBlue, text, state);
			}
		}

		if (!state) std::system("cls");
	}

	return 0;
}