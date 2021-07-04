#include <iostream>

#include "AsciiBoard.h"

int main()
{
	ChessEngine::AsciiBoard asciiBoard;
	std::cout << asciiBoard.GetAscii() << std::endl;

	return 0;
}