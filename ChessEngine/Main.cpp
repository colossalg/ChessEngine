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
	std::string FEN = "r1bq1rk1/4bppp/p2p1n2/npp1p3/3PP3/2P2N1P/PPB2PP1/RNBQR1K1 b - a3 0 11";

	Board board(FEN);

	ChessEngine::AsciiUI asciiBoard;
	asciiBoard.SetPieces(board.GetPieces());

	std::cout << asciiBoard.GetAscii() << std::endl;

	return 0;
}