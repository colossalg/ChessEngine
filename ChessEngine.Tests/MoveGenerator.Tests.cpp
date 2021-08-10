#include "pch.h"
#include "CppUnitTest.h"

#include <set>
#include <vector>

#include "Board.h"
#include "Definitions.h"
#include "Helper.h"
#include "Move.h"
#include "MoveGenerator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChessEngineTests
{
	using namespace ChessEngine;

	TEST_CLASS(MoveGeneratorTests)
	{
	public:
		
		// Helper function testing whether a given move is contained within moveList
		void TestListContainsMove(const MoveList& moveList, const Move move, const bool shouldBeContained)
		{
			auto& moveLoc = std::find(moveList.begin(), moveList.end(), move);

			std::wstring moveWStr = Helper::StringToWString(move.GetString());

			if (shouldBeContained)
			{
				Assert::IsTrue(moveLoc != moveList.end(), moveWStr.c_str());
			}
			else
			{
				Assert::IsTrue(moveLoc == moveList.end(), moveWStr.c_str());
			}
		}

 		TEST_METHOD(TestIsSquareAttacked)
		{
			// Lambda for helping check that all squares that should be attacked are, and all others are not
			auto checkAttackedSquares = [](const std::string& FEN, const std::vector<std::string>& attackedSquares) -> void
			{
				std::set<Square> attackedSquareSet;

				for (const std::string& square : attackedSquares)
				{
					attackedSquareSet.emplace(Helper::SquareFromString(square));
				}

				const Board board(FEN);

				for (Square square = 0; Helper::IsValidSquare(square); square++)
				{
					std::wstring squareWStr = Helper::StringToWString(Helper::StringFromSquare(square));

					bool isAttacked = (attackedSquareSet.find(square) != attackedSquareSet.end());
					Assert::IsTrue((isAttacked == MoveGenerator::IsSquareAttacked(board, square)), squareWStr.c_str());
				}
			};

			// Test pawn attacks
			{
				const std::string whiteFEN = "8/8/8/p3p2p/P3P2P/8/8/8 b - - 0 1";
				const std::vector<std::string> whiteAttackedSquares{ "b5", "d5", "f5", "g5" };
				checkAttackedSquares(whiteFEN, whiteAttackedSquares);

				const std::string blackFEN = "8/8/8/p3p2p/P3P2P/8/8/8 w - - 0 1";
				const std::vector<std::string> blackAttackedSquares{ "b4", "d4", "f4", "g4" };
				checkAttackedSquares(blackFEN, blackAttackedSquares);
			}

			// Test knight attacks
			{
				const std::string whiteFEN = "n7/8/8/4n3/4N3/8/8/N7 b - - 0 1";
				const std::vector<std::string> whiteAttackedSquares{ "b3", "c2", "c3", "c5", "d2", "d6", "f2", "f6", "g3", "g5" };
				checkAttackedSquares(whiteFEN, whiteAttackedSquares);

				const std::string blackFEN = "n7/8/8/4n3/4N3/8/8/N7 w - - 0 1";
				const std::vector<std::string> blackAttackedSquares{ "b6", "c4", "c6", "c7", "d3", "d7", "f3", "f7", "g4", "g6" };
				checkAttackedSquares(blackFEN, blackAttackedSquares);
			}

			// Test bishop attacks (this should also test queens diagonally)
			{
				const std::string whiteFEN = "8/8/8/3bb3/3BB3/8/8/8 b - - 0 1";
				const std::vector<std::string> whiteAttackedSquares{
					"a1", "a7", "b2", "b6", "c3", "c5", "e3", "e5", "f2", "g1",		// Dark square bishop
					"b1", "c2", "d3", "d5", "f3", "f5", "g2", "g6", "h1", "h7"		// Light square bishop
				};
				checkAttackedSquares(whiteFEN, whiteAttackedSquares);

				const std::string blackFEN = "8/8/8/3bb3/3BB3/8/8/8 w - - 0 1";
				const std::vector<std::string> blackAttackedSquares{ 
					"a2", "a8", "b3", "b7", "c4", "c6", "e4", "e6", "f7", "g8",		// Light square bishop
					"b8", "c7", "d4", "d6", "f4", "f6", "g3", "g7", "h2", "h8"		// Dark square bishop
				};
				checkAttackedSquares(blackFEN, blackAttackedSquares);
			}

			// Test rook attacks (this should also test queens along ranks and files)
			{
				const std::string whiteFEN = "8/8/8/3rr3/3RR3/8/8/8 b - - 0 1";
				const std::vector<std::string> whiteAttackedSquares{
					"a4", "b4", "c4", "e4", "d1", "d2", "d3", "d5",
					"d4", "f4", "g4", "h4", "e1", "e2", "e3", "e5"
				};
				checkAttackedSquares(whiteFEN, whiteAttackedSquares);

				const std::string blackFEN = "8/8/8/3rr3/3RR3/8/8/8 w - - 0 1";
				const std::vector<std::string> AttackedSquares{
					"a5", "b5", "c5", "e5", "d4", "d6", "d7", "d8",
					"d5", "f5", "g5", "h5", "e4", "e6", "e7", "e8"
				};
				checkAttackedSquares(whiteFEN, whiteAttackedSquares);
			}

			// Test king attacks
			{
				const std::string whiteFEN = "8/8/2k5/8/8/5K2/8/8 b - - 0 1";
				const std::vector<std::string> whiteAttackedSquares{
					"e2", "e3", "e4", "f2", "f4", "g2", "g3", "g4"
				};
				checkAttackedSquares(whiteFEN, whiteAttackedSquares);

				const std::string blackFEN = "8/8/2k5/8/8/5K2/8/8 w - - 0 1";
				const std::vector<std::string> AttackedSquares{
					"b4", "b5", "b6", "c4", "c6", "d4", "d5", "d6"
				};
				checkAttackedSquares(whiteFEN, whiteAttackedSquares);
			}
		}

		TEST_METHOD(CastlingMoveGeneration)
		{
			// Lambda for helping generate and check the correctness of the castling moves in a given position
			auto generateAndCheckCastling = [this](const std::string& FEN, const bool isWhite, const bool canCastleKingside, const bool canCastleQueenside)
			{
				const Move kingsideCastles = (isWhite
					? Move("e1", "g1", Move::Special::KingsideCastles)
					: Move("e8", "g8", Move::Special::KingsideCastles));

				const Move queensideCastles = (isWhite
					? Move("e1", "c1", Move::Special::QueensideCastles)
					: Move("e8", "c8", Move::Special::QueensideCastles));
				
				const Board board(FEN);
				const MoveList moveList = std::move(MoveGenerator::GenerateMoves(board));

				TestListContainsMove(moveList, kingsideCastles, canCastleKingside);
				TestListContainsMove(moveList, queensideCastles, canCastleQueenside);
			};

			// Test that all castling moves are generated when they are all valid
			{
				const std::string whiteMoveFEN = "r3k2r/ppp2ppp/8/8/8/8/PPP2PPP/R3K2R w KQkq - 0 1";
				generateAndCheckCastling(whiteMoveFEN, true, true, true);

				const std::string blackMoveFEN = "r3k2r/ppp2ppp/8/8/8/8/PPP2PPP/R3K2R b KQkq - 0 1";
				generateAndCheckCastling(blackMoveFEN, false, true, true);
			}

			// Test that no castling moves are generated when they are invalid because rooks or king have moved before
			{
				const std::string whiteMoveFEN = "r3k2r/ppp2ppp/8/8/8/8/PPP2PPP/R3K2R w - - 0 1";
				generateAndCheckCastling(whiteMoveFEN, true, false, false);

				const std::string blackMoveFEN = "r3k2r/ppp2ppp/8/8/8/8/PPP2PPP/R3K2R b - - 0 1";
				generateAndCheckCastling(blackMoveFEN, false, false, false);
			}

			// Test that no castling moves are generated when the king is in check
			{
				const std::string whiteMoveFEN = "r3k2r/ppp2ppp/8/4Q3/4q3/8/PPP2PPP/R3K2R w KQkq - 0 1";
				generateAndCheckCastling(whiteMoveFEN, true, false, false);

				const std::string blackMoveFEN = "r3k2r/ppp2ppp/8/4Q3/4q3/8/PPP2PPP/R3K2R b KQkq - 0 1";
				generateAndCheckCastling(blackMoveFEN, false, false, false);
			}

			// Test that no castling moves are generated when the king must pass through or in to check
			{
				const std::string whiteMoveFEN = "r3k2r/ppp2ppp/8/1b4b1/1B4B1/8/PPP2PPP/R3K2R w KQkq - 0 1";
				generateAndCheckCastling(whiteMoveFEN, true, false, false);

				const std::string blackMoveFEN = "r3k2r/ppp2ppp/8/1b4b1/1B4B1/8/PPP2PPP/R3K2R b KQkq - 0 1";
				generateAndCheckCastling(blackMoveFEN, false, false, false);
			}

			// Test that no castling moves are generated when there is a piece between the king and rook
			{
				const std::string whiteMoveFEN = "r1b1kb1r/ppp2ppp/8/8/8/8/PPP2PPP/R1B1KB1R w KQkq - 0 1";
				generateAndCheckCastling(whiteMoveFEN, true, false, false);

				const std::string blackMoveFEN = "r1b1kb1r/ppp2ppp/8/8/8/8/PPP2PPP/R1B1KB1R b KQkq - 0 1";
				generateAndCheckCastling(blackMoveFEN, false, false, false);
			}
		}
	};
}
