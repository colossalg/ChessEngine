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
	using namespace ChessEngine;

	TEST_CLASS(PieceTests)
	{
	public:

		void TestPiece(ChessEngine::Piece::Type type, char whiteAscii, char blackAscii)
		{
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

		TEST_METHOD(TestConstructors)
		{
			// Test that the constructors result in equivalent pieces
			Assert::IsTrue(Piece(Piece::Type::Pawn, true) == Piece('P'));
			Assert::IsTrue(Piece(Piece::Type::Pawn, false) == Piece('p'));
			Assert::IsTrue(Piece(Piece::Type::Knight, true) == Piece('N'));
			Assert::IsTrue(Piece(Piece::Type::Knight, false) == Piece('n'));
			Assert::IsTrue(Piece(Piece::Type::Bishop, true) == Piece('B'));
			Assert::IsTrue(Piece(Piece::Type::Bishop, false) == Piece('b'));
			Assert::IsTrue(Piece(Piece::Type::Rook, true) == Piece('R'));
			Assert::IsTrue(Piece(Piece::Type::Rook, false) == Piece('r'));
			Assert::IsTrue(Piece(Piece::Type::Queen, true) == Piece('Q'));
			Assert::IsTrue(Piece(Piece::Type::Queen, false) == Piece('q'));
			Assert::IsTrue(Piece(Piece::Type::King, true) == Piece('K'));
			Assert::IsTrue(Piece(Piece::Type::King, false) == Piece('k'));
		}

		TEST_METHOD(TestAllPieces)
		{
			// Test each piece type
			TestPiece(Piece::Type::Empty, ' ', ' ');
			TestPiece(Piece::Type::Pawn, 'P', 'p');
			TestPiece(Piece::Type::Knight, 'N', 'n');
			TestPiece(Piece::Type::Bishop, 'B', 'b');
			TestPiece(Piece::Type::Rook, 'R', 'r');
			TestPiece(Piece::Type::Queen, 'Q', 'q');
			TestPiece(Piece::Type::King, 'K', 'k');
		}

		TEST_METHOD(TestIsWhite)
		{
			// Test the IsWhite helper function
			Piece p = Piece(Piece::Type::King, true);
			Assert::IsTrue(p.IsWhite());
			p = Piece(Piece::Type::King, false);
			Assert::IsFalse(p.IsWhite());
		}
	};
}
