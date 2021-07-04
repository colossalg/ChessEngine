#include "pch.h"
#include "CppUnitTest.h"

#include "Definitions.h"
#include "PieceHelper.h"

#define IS_PIECE_CONDITIONAL(Piece, Type, ComparissonType, ComparissonFunc) \
	if (Type == PieceType::ComparissonType) \
	{ \
		Assert::IsTrue(ComparissonFunc(Piece), L#Type L" != " L#ComparissonType); \
	} \
	else \
	{ \
		Assert::IsFalse(ComparissonFunc(Piece), L#Type L" == " L#ComparissonType); \
	}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChessEngineTests
{
	TEST_CLASS(PieceHelperTests)
	{
	public:

		void TestPiece(ChessEngine::PieceHelper::PieceType type, char whiteAscii, char blackAscii)
		{
			using namespace ChessEngine;
			using namespace ChessEngine::PieceHelper;

			Piece p = MakePiece(type, true);

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

			p = MakePiece(type, true);
			asciiResult = GetAscii(p);
			wss << whiteAscii << " == " << asciiResult;
			Assert::AreEqual(whiteAscii, asciiResult, wss.str().c_str());

			wss.clear();

			p = MakePiece(type, false);
			asciiResult = GetAscii(p);
			wss << blackAscii << " == " << asciiResult;
			Assert::AreEqual(blackAscii, asciiResult, wss.str().c_str());
		}

		TEST_METHOD(TestAllPieces)
		{
			using namespace ChessEngine;
			using namespace ChessEngine::PieceHelper;

			// Test each piece type
			TestPiece(PieceType::Empty, ' ', ' ');
			TestPiece(PieceType::Pawn, 'p', 'P');
			TestPiece(PieceType::Knight, 'n', 'N');
			TestPiece(PieceType::Bishop, 'b', 'B');
			TestPiece(PieceType::Rook, 'r', 'R');
			TestPiece(PieceType::Queen, 'q', 'Q');
			TestPiece(PieceType::King, 'k', 'K');
		}

		TEST_METHOD(TestIsWhite)
		{
			using namespace ChessEngine;
			using namespace ChessEngine::PieceHelper;

			Piece p;

			// Test the IsWhite helper function
			p = MakePiece(PieceType::King, true);
			Assert::IsTrue(IsWhite(p));
			p = MakePiece(PieceType::King, false);
			Assert::IsFalse(IsWhite(p));
		}

		TEST_METHOD(TestHasmoved)
		{
			using namespace ChessEngine;
			using namespace ChessEngine::PieceHelper;

			Piece p;

			// Test the Hasmoved helper function
			p = MakePiece(PieceType::King, true, true);
			Assert::IsTrue(HasMoved(p));
			p = MakePiece(PieceType::King, true, false);
			Assert::IsFalse(HasMoved(p));
		}
	};
}
