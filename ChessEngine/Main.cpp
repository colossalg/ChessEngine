#include <array>
#include <iostream>

#include "Definitions.h"
#include "Helper.h"
#include "Piece.h"
#include "Board.h"
#include "AsciiUI.h"

using namespace ChessEngine;

int main()
{
	Board board;

	ChessEngine::AsciiUI asciiBoard;
	asciiBoard.SetPieces(board.GetPieces());

	std::cout << asciiBoard.GetAscii() << std::endl;

	return 0;
}