#include <array>
#include <iostream>

#include "Definitions.h"
#include "BoardHelper.h"
#include "PieceHelper.h"
#include "AsciiUI.h"

using namespace ChessEngine;

int main()
{
	ChessEngine::AsciiUI asciiBoard;
	asciiBoard.SetPieces(BoardHelper::StartingBoard);
	asciiBoard.SetCastling(true, true, true, true);
	asciiBoard.SetEnPassant(false, 0);

	std::cout << asciiBoard.GetAscii() << std::endl;

	return 0;
}