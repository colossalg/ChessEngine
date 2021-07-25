#include <array>
#include <iostream>

#include "AsciiUI.h"
#include "Board.h"
#include "Definitions.h"
#include "Helper.h"
#include "Move.h"
#include "Piece.h"

using namespace ChessEngine;

int main()
{
	Board board("r1bqkb1r/1ppp1ppp/p1n2n2/4p3/B3P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 2 5");

	// board.MakeMove(Move(Helper::SquareFromString("e2"), Helper::SquareFromString("e4"), Move::Special::DoublePawnPush));
	// board.MakeMove(Move(Helper::SquareFromString("e2"), Helper::SquareFromString("e4"), Move::Special::DoublePawnPush));

	// board.MakeMove(Move(Helper::SquareFromString("g1"), Helper::SquareFromString("f3")));
	// board.MakeMove(Move(Helper::SquareFromString("g8"), Helper::SquareFromString("f6")));

	board.MakeMove(Move(0, 0, Move::Special::KingsideCastles));

	ChessEngine::AsciiUI asciiBoard;
	asciiBoard.SetPieces(board.GetPieces());

	std::cout << asciiBoard.GetAscii() << std::endl;

	return 0;
}