#include "pch.h"
#include "CppUnitTest.h"

#include "Definitions.h"
#include "Move.h"

#define IS_MOVE_CONDITIONAL(M, T, ComparissonType, ComparissonFunc) \
	if (T == Move::Type::ComparissonType) \
	{ \
		Assert::IsTrue(M.ComparissonFunc(), L#T L" != " L#ComparissonType); \
	} \
	else \
	{ \
		Assert::IsFalse(M.ComparissonFunc(), L#T L" == " L#ComparissonType); \
	}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChessEngineTests
{
	TEST_CLASS(MoveTests)
	{
	public:

		void TestMove(ChessEngine::Move::Type type)
		{
			using namespace ChessEngine;

			Move m(0, 0, type);

			// Test the Is**MoveType** functions
			IS_MOVE_CONDITIONAL(m, type, Quiet, IsQuiet);
			IS_MOVE_CONDITIONAL(m, type, Capture, IsCapture);
			IS_MOVE_CONDITIONAL(m, type, DoublePawnPush, IsDoublePawnPush);
			IS_MOVE_CONDITIONAL(m, type, EnPassantCapture, IsEnPassantCapture);
			IS_MOVE_CONDITIONAL(m, type, KingsideCastles, IsKingsideCastles);
			IS_MOVE_CONDITIONAL(m, type, QueensideCastles, IsQueensideCastles);
			IS_MOVE_CONDITIONAL(m, type, KnightPromotion, IsKnightPromotion);
			IS_MOVE_CONDITIONAL(m, type, BishopPromotion, IsBishopPromotion);
			IS_MOVE_CONDITIONAL(m, type, RookPromotion, IsRookPromotion);
			IS_MOVE_CONDITIONAL(m, type, QueenPromotion, IsQueenPromotion);
			IS_MOVE_CONDITIONAL(m, type, KnightPromotionCapture, IsKnightPromotionCapture);
			IS_MOVE_CONDITIONAL(m, type, BishopPromotionCapture, IsBishopPromotionCapture);
			IS_MOVE_CONDITIONAL(m, type, RookPromotionCapture, IsRookPromotionCapture);
			IS_MOVE_CONDITIONAL(m, type, QueenPromotionCapture, IsQueenPromotionCapture);
		}

		TEST_METHOD(TestAllMoves)
		{
			using namespace ChessEngine;

			// Test each move type
			TestMove(Move::Type::Quiet);
			TestMove(Move::Type::Capture);
			TestMove(Move::Type::DoublePawnPush);
			TestMove(Move::Type::EnPassantCapture);
			TestMove(Move::Type::KingsideCastles);
			TestMove(Move::Type::QueensideCastles);
			TestMove(Move::Type::KnightPromotion);
			TestMove(Move::Type::BishopPromotion);
			TestMove(Move::Type::RookPromotion);
			TestMove(Move::Type::QueenPromotion);
			TestMove(Move::Type::KnightPromotionCapture);
			TestMove(Move::Type::BishopPromotionCapture);
			TestMove(Move::Type::RookPromotionCapture);
			TestMove(Move::Type::QueenPromotionCapture);
		}

		TEST_METHOD(TestInitAndDestSquare)
		{
			using namespace ChessEngine;

			Move m(57, 63, Move::Type::Quiet);

			// Test that the initial and destination squares are set correctly
			Assert::AreEqual(Square(57), m.GetInitSquare());
			Assert::AreEqual(Square(63), m.GetDestSquare());
		}
	};
}
