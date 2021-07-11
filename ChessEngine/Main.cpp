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

	// board.MakeMove(Move(Helper::SquareFromString("e2"), Helper::SquareFromString("e4"), Move::Special::DoublePawnPush));
	// board.MakeMove(Move(Helper::SquareFromString("e2"), Helper::SquareFromString("e4"), Move::Special::DoublePawnPush));

	board.MakeMove(Move(Helper::SquareFromString("g1"), Helper::SquareFromString("f3")));
	board.MakeMove(Move(Helper::SquareFromString("g8"), Helper::SquareFromString("f6")));

	ChessEngine::AsciiUI asciiBoard;
	asciiBoard.SetPieces(board.GetPieces());

	std::cout << asciiBoard.GetAscii() << std::endl;

	return 0;
}