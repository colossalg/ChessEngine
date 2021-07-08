#include "pch.h"
#include "CppUnitTest.h"

#include "Definitions.h"
#include "Piece.h"

#define IS_PIECE_CONDITIONAL(P, T, ComparissonType, ComparissonFunc) \
	if (T == Piece::Type::ComparissonType) \
	{ \
		Assert::IsTrue(P.ComparissonFunc(), L#T L" != " L#ComparissonType); \
	} \
	else \
	{ \
		Assert::IsFalse(P.ComparissonFunc(), L#T L" == " L#ComparissonType); \
	}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChessEngineTests
{
	TEST_CLASS(PieceTests)
	{
	public:

		void TestPiece(ChessEngine::Piece::Type type, char whiteAscii, char blackAscii)
		{
			using namespace ChessEngine;

			Piece p(type, true);

			// Test the Is**Piece** functions
			IS_PIECE_CONDITIONAL(p, type, Empty, IsEmpty);
			IS_PIECE_CONDITIONAL(p, type, Pawn, IsPawn);
			IS_PIECE_CONDITIONAL(p, type, Knight, IsKnight);
			IS_PIECE_CONDITIONAL(p, type, Bishop, IsBishop);
			IS_PIECE_CONDITIONAL(p, type, Rook, IsRook);
			IS_PIECE_CONDITIONAL(p, type, Queen, IsQueen);
			IS_PIECE_CONDITIONAL(p, type, King, IsKing);

			// Test the GetAscii function
			char asciiResult;
			std::wstringstream wss;

			p = Piece(type, true);
			asciiResult = p.GetAscii();
			wss << whiteAscii << " == " << asciiResult;
			Assert::AreEqual(whiteAscii, asciiResult, wss.str().c_str());

			wss.clear();

			p = Piece(type, false);
			asciiResult = p.GetAscii();
			wss << blackAscii << " == " << asciiResult;
			Assert::AreEqual(blackAscii, asciiResult, wss.str().c_str());
		}

		TEST_METHOD(TestAllPieces)
		{
			using namespace ChessEngine;

			// Test each piece type
			TestPiece(Piece::Type::Empty, ' ', ' ');
			TestPiece(Piece::Type::Pawn, 'p', 'P');
			TestPiece(Piece::Type::Knight, 'n', 'N');
			TestPiece(Piece::Type::Bishop, 'b', 'B');
			TestPiece(Piece::Type::Rook, 'r', 'R');
			TestPiece(Piece::Type::Queen, 'q', 'Q');
			TestPiece(Piece::Type::King, 'k', 'K');
		}

		TEST_METHOD(TestIsWhite)
		{
			using namespace ChessEngine;

			// Test the IsWhite helper function
			Piece p = Piece(Piece::Type::King, true);
			Assert::IsTrue(p.IsWhite());
			p = Piece(Piece::Type::King, false);
			Assert::IsFalse(p.IsWhite());
		}

		TEST_METHOD(TestHasmoved)
		{
			using namespace ChessEngine;

			// Test the Hasmoved helper function
			Piece p = Piece(Piece::Type::King, true, true);
			Assert::IsTrue(p.HasMoved());
			p = Piece(Piece::Type::King, true, false);
			Assert::IsFalse(p.HasMoved());
		}
	};
}
