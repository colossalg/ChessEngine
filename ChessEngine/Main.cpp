#include <array>
#include <chrono>
#include <iostream>

#include "AsciiUI.h"
#include "Board.h"
#include "Move.h"
#include "MoveGenerator.h"

using namespace ChessEngine;

int main()
{
	Board board("r1bqkb1r/1ppp1ppp/p1n2n2/4p3/B3P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 2 5");

	std::cout << AsciiUI::GetAscii(board) << std::endl;

	double averageTimeMS = 0.0;
	int numMoves = 10;

	for (int i = 0; i < numMoves; i++)
	{
		auto t1 = std::chrono::high_resolution_clock::now();

		auto moveList = std::move(MoveGenerator::GenerateMoves(board));
		board.MakeMove(moveList.front());

		auto t2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> time = t2 - t1;
		averageTimeMS += time.count() / numMoves;
	}

	std::cout << "Average move generation time (ms) over " << numMoves << " runs: " << averageTimeMS << std::endl;

	return 0;
}