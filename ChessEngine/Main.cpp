#include <array>
#include <iostream>

#include "AsciiUI.h"
#include "Board.h"

using namespace ChessEngine;

int main()
{
	Board board("r1bqkb1r/1ppp1ppp/p1n2n2/4p3/B3P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 2 5");

	std::cout << AsciiUI::GetAscii(board) << std::endl;

	return 0;
}