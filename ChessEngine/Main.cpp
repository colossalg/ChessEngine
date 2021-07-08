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
	Piece p1(Piece::Type::Pawn, true, false);

	Piece p2 = p1;
	p2.SetHasMoved();

	Board board;

	ChessEngine::AsciiUI asciiBoard;
	asciiBoard.SetPieces(board.GetPieces());

	std::cout << asciiBoard.GetAscii() << std::endl;

	return 0;
}