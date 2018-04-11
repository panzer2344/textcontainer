#include "TText.h"
#include <Windows.h>


int main() {
	TText text;

	text.InsertNextLine("abcde");
	text.Print();

	text.InsertNextLine("fghi");
	text.Print();

	text.InsertDownLine("jklmnop");
	text.Print();

	text.InsertNextSection("arma3");
	text.Print();

	text.InsertDownSection("boris-britva");
	text.Print();

	int a;
	std::cin >> a;
	std::cout << a;

	return 0;
}