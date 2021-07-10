#include "pch.h"
#include "CppUnitTest.h"

#include <string>
#include <vector>

#include "Board.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChessEngineTests
{
	using namespace ChessEngine;

	namespace
	{
		std::vector <std::string> FENVector{
			"r1bq1rk1/4bppp/p2p1n2/npp1p3/3PP3/2P2N1P/PPB2PP1/RNBQR1K1 b - - 0 11",	// Ruy Lopez
			"rnbqkb1r/pp2pp1p/3p1np1/8/3NP3/2N5/PPP2PPP/R1BQKB1R w KQkq - 0 6",		// Sicilian Dragon
			"rnbqkb1r/1p2pppp/p2p1n2/8/3NP3/2N5/PPP2PPP/R1BQKB1R w KQkq - 0 6",		// Sicilian Najdorf
		};
	}

	TEST_CLASS(BoardTests)
	{
	public:
		
		TEST_METHOD(TestFEN)
		{
			// Test that the FEN used to create a board is the same as the FEN output by the board
			for (const std::string& FEN : FENVector)
			{
				Board board(FEN);
				Assert::AreEqual(FEN, board.GetFEN());
			}
		}
	};
}