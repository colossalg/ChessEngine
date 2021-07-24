#include "pch.h"
#include "CppUnitTest.h"

#include <vector>

#include "Definitions.h"
#include "Move.h"
#include "Piece.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChessEngineTests
{
	using namespace ChessEngine;

	TEST_CLASS(MoveTests)
	{
	public:

		void TestMove(
			Move move,
			Square initSquare,
			Square destSquare,
			bool isQuiet,
			bool isDoublePawnPush,
			bool isKingsideCastles,
			bool isQueensideCastles,
			bool isEnPassantCapture,
			bool isCapture,
			bool isPromotion
			)
		{
			Assert::AreEqual(initSquare, move.GetInitSquare());
			Assert::AreEqual(destSquare, move.GetDestSquare());
			Assert::AreEqual(isQuiet, move.IsQuiet());
			Assert::AreEqual(isDoublePawnPush, move.IsDoublePawnPush());
			Assert::AreEqual(isKingsideCastles, move.IsKingsideCastles());
			Assert::AreEqual(isQueensideCastles, move.IsQueensideCastles());
			Assert::AreEqual(isEnPassantCapture, move.IsEnPassantCapture());
			Assert::AreEqual(isCapture, move.IsCapture());
			Assert::AreEqual(isPromotion, move.IsPromotion());
		}

		TEST_METHOD(TestAllmoves)
		{
			// Test quiet moves
			TestMove(Move(0, 7), 0, 7, true, false, false, false, false, false, false);

			// Test double pawn push
			TestMove(Move(8, 15, Move::Special::DoublePawnPush), 8, 15, false, true, false, false, false, false, false);

			// Test kingside castles
			TestMove(Move(16, 23, Move::Special::KingsideCastles), 16, 23, false, false, true, false, false, false, false);

			// Test queenside castles
			TestMove(Move(24, 31, Move::Special::QueensideCastles), 24, 31, false, false, false, true, false, false, false);

			// Test en Passant capture
			TestMove(Move(32, 39, Move::Special::EnPassantCapture), 32, 39, false, false, false, false, true, true, false);

			// Test capture
			TestMove(Move(40, 47, true), 40, 47, false, false, false, false, false, true, false);

			// Test promotion
			TestMove(Move(48, 55, false, true), 48, 55, false, false, false, false, false, false, true);
		}

		TEST_METHOD(TestPromotion)
		{
			std::vector<Piece::Type> pieceTypes{
				Piece::Type::Knight,
				Piece::Type::Bishop,
				Piece::Type::Rook,
				Piece::Type::Queen
			};

			// Test that we can set and retrieve the promotion type
			for (Piece::Type pieceType : pieceTypes)
			{
				Move m(0, 63, true, true, pieceType);
				Assert::IsTrue(pieceType == m.GetPromotionType());
			}
		}
	};
}
