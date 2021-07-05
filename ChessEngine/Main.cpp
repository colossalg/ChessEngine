#include <array>
#include <iostream>

#include "Definitions.h"
#include "PieceHelper.h"
#include "SquareHelper.h"
#include "AsciiUI.h"
#include "Board.h"

using namespace ChessEngine;

int main()
{
	ChessEngine::AsciiUI asciiBoard;
	asciiBoard.SetPieces(Board::StartingPieces);

	std::cout << asciiBoard.GetAscii() << std::endl;

	return 0;
}