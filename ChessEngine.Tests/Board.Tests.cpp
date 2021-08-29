#include "pch.h"
#include "CppUnitTest.h"

#include <string>
#include <vector>

#include "Board.h"
#include "Move.h"
#include "MoveInverse.h"
#include "Piece.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChessEngineTests
{
	using namespace ChessEngine;

	namespace
	{
		const std::vector <std::string> FENVector{
			"rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq e3 0 2",		// 1. e4 e5
			"r1bq1rk1/4bppp/p2p1n2/npp1p3/3PP3/2P2N1P/PPB2PP1/RNBQR1K1 b - - 0 11",	// Ruy Lopez
			"rnbqkb1r/pp2pp1p/3p1np1/8/3NP3/2N5/PPP2PPP/R1BQKB1R w KQkq - 0 6",		// Sicilian Dragon
			"rnbqkb1r/1p2pppp/p2p1n2/8/3NP3/2N5/PPP2PPP/R1BQKB1R w KQkq - 0 6",		// Sicilian Najdorf
		};
	}

	TEST_CLASS(BoardTests)
	{
	public:

		// Test that the FEN used to create a board is the same as the FEN output by the board
		TEST_METHOD(TestFEN)
		{
			for (const std::string& FEN : FENVector)
			{
				Board board(FEN);
				Assert::AreEqual(FEN, board.GetFEN());
			}
		}

		// Test making and unmaking a move for white and a move for black
		void TestMoveUnMove(
			const std::string& startingFEN,
			const std::string& whiteMoveFEN,
			const std::string& blackMoveFEN,
			Move whiteMove,
			Move blackMove
		)
		{
			Board board(startingFEN);

			MoveInverse whiteMoveInverse(board, whiteMove);

			board.MakeMove(whiteMove);
			Assert::AreEqual(whiteMoveFEN, board.GetFEN());

			MoveInverse blackMoveInverse(board, blackMove);

			board.MakeMove(blackMove);
			Assert::AreEqual(blackMoveFEN, board.GetFEN());

			board.UndoMove(blackMoveInverse);
			Assert::AreEqual(whiteMoveFEN, board.GetFEN());

			board.UndoMove(whiteMoveInverse);
			Assert::AreEqual(startingFEN, board.GetFEN());
		}

		// Test making and unmaking a move
		void TestMoveUnMove(
			const std::string& startingFEN,
			const std::string& endingFEN,
			Move move
		)
		{
			Board board(startingFEN);

			MoveInverse moveInverse(board, move);

			board.MakeMove(move);
			Assert::AreEqual(endingFEN, board.GetFEN());

			board.UndoMove(moveInverse);
			Assert::AreEqual(startingFEN, board.GetFEN());
		}

		// Test that quiet moves update the state of the board correctly
		TEST_METHOD(TestMoveUnMoveQuiet)
		{
			// Queen's Gambit
			const std::string startingFEN = "rnbqkb1r/ppp2ppp/4pn2/3p4/2PP4/2N5/PP2PPPP/R1BQKBNR w KQkq - 2 4";
			const std::string whiteMoveFEN = "rnbqkb1r/ppp2ppp/4pn2/3p2B1/2PP4/2N5/PP2PPPP/R2QKBNR b KQkq - 3 4"; // After 4. bg5
			const std::string blackMoveFEN = "rnbqk2r/ppp1bppp/4pn2/3p2B1/2PP4/2N5/PP2PPPP/R2QKBNR w KQkq - 4 5"; // After 4. --- be7

			Move whiteMove("c1", "g5");	// 4. bg5
			Move blackMove("f8", "e7"); // 4. --- be7

			TestMoveUnMove(startingFEN, whiteMoveFEN, blackMoveFEN, whiteMove, blackMove);
		}

		// Test that capture moves update the state of the board correctly
		TEST_METHOD(TestMoveUnMoveCapture)
		{
			// Queen's Gambit
			const std::string startingFEN = "rnbqkb1r/ppp2ppp/4pn2/3p4/2PP4/2N5/PP2PPPP/R1BQKBNR w KQkq - 2 4";
			const std::string whiteMoveFEN = "rnbqkb1r/ppp2ppp/4pn2/3P4/3P4/2N5/PP2PPPP/R1BQKBNR b KQkq - 0 4"; // After 4. cxd5
			const std::string blackMoveFEN = "rnbqkb1r/ppp2ppp/5n2/3p4/3P4/2N5/PP2PPPP/R1BQKBNR w KQkq - 0 5";	// After 4. --- exd5

			Move whiteMove("c4", "d5", true); // 4. csd5
			Move blackMove("e6", "d5", true); // 4. --- exd5

			TestMoveUnMove(startingFEN, whiteMoveFEN, blackMoveFEN, whiteMove, blackMove);
		}

		// Test that promotion moves update the state of the board correctly
		TEST_METHOD(TestMoveUnMovePromotion)
		{
			// Some artificial position
			const std::string startingQuietFEN = "8/P7/4k3/8/8/4K3/p7/8 w - - 0 1";
			const std::string startingCaptureFEN = "r7/1P6/4k3/8/8/4K3/1p6/R7 w - - 0 1";

			auto quietPromotionList = std::vector<std::tuple<std::string, std::string, Piece::Type>>
			{
				{ "Q7/8/4k3/8/8/4K3/p7/8 b - - 0 1", "Q7/8/4k3/8/8/4K3/8/q7 w - - 0 2", Piece::Type::Queen },
				{ "R7/8/4k3/8/8/4K3/p7/8 b - - 0 1", "R7/8/4k3/8/8/4K3/8/r7 w - - 0 2", Piece::Type::Rook },
				{ "B7/8/4k3/8/8/4K3/p7/8 b - - 0 1", "B7/8/4k3/8/8/4K3/8/b7 w - - 0 2", Piece::Type::Bishop },
				{ "N7/8/4k3/8/8/4K3/p7/8 b - - 0 1", "N7/8/4k3/8/8/4K3/8/n7 w - - 0 2", Piece::Type::Knight }
			};

			auto capturePromotionList = std::vector<std::tuple<std::string, std::string, Piece::Type>>
			{
				{ "Q7/8/4k3/8/8/4K3/1p6/R7 b - - 0 1", "Q7/8/4k3/8/8/4K3/8/q7 w - - 0 2", Piece::Type::Queen },
				{ "R7/8/4k3/8/8/4K3/1p6/R7 b - - 0 1", "R7/8/4k3/8/8/4K3/8/r7 w - - 0 2", Piece::Type::Rook },
				{ "B7/8/4k3/8/8/4K3/1p6/R7 b - - 0 1", "B7/8/4k3/8/8/4K3/8/b7 w - - 0 2", Piece::Type::Bishop },
				{ "N7/8/4k3/8/8/4K3/1p6/R7 b - - 0 1", "N7/8/4k3/8/8/4K3/8/n7 w - - 0 2", Piece::Type::Knight }
			};
			
			// Test promotions for each piece type (without capture)
			for (auto& [whiteMoveFEN, blackMoveFEN, promotionType] : quietPromotionList)
			{
				Move whiteMove("a7", "a8", false, true, promotionType);
				Move blackMove("a2", "a1", false, true, promotionType);

				TestMoveUnMove(startingQuietFEN, whiteMoveFEN, blackMoveFEN, whiteMove, blackMove);
			}

			// Test promotions for each piece type (with capture)
			for (auto& [whiteMoveFEN, blackMoveFEN, promotionType] : capturePromotionList)
			{
				Move whiteMove("b7", "a8", true, true, promotionType);
				Move blackMove("b2", "a1", true, true, promotionType);

				TestMoveUnMove(startingCaptureFEN, whiteMoveFEN, blackMoveFEN, whiteMove, blackMove);
			}
		}

		// Test that kingside castling moves update the state of the board correctly
		TEST_METHOD(TestMoveUnMoveKingsideCastling)
		{
			// French exchange
			const std::string startingFEN = "rnbqk2r/ppp2ppp/3b1n2/3p4/3P4/3B1N2/PPP2PPP/RNBQK2R w KQkq - 4 6";
			const std::string whiteMoveFEN = "rnbqk2r/ppp2ppp/3b1n2/3p4/3P4/3B1N2/PPP2PPP/RNBQ1RK1 b kq - 5 6"; // After 6. O-O
			const std::string blackMoveFEN = "rnbq1rk1/ppp2ppp/3b1n2/3p4/3P4/3B1N2/PPP2PPP/RNBQ1RK1 w - - 6 7"; // After 6. --- O-O

			Move whiteMove("e1", "g1", Move::Special::KingsideCastles); // 6. O-O
			Move blackMove("e8", "g8", Move::Special::KingsideCastles); // 6. --- O-O

			TestMoveUnMove(startingFEN, whiteMoveFEN, blackMoveFEN, whiteMove, blackMove);
		}

		// Test that queenside castling moves update the state of the board correctly
		TEST_METHOD(TestMoveunMoveQueensideCastling)
		{
			// Some random opening
			const std::string startingFEN = "r3k2r/ppp1qppp/2np1n2/1B2p1B1/1b2P1b1/2NP1N2/PPP1QPPP/R3K2R w KQkq - 4 8";
			const std::string whiteMoveFEN = "r3k2r/ppp1qppp/2np1n2/1B2p1B1/1b2P1b1/2NP1N2/PPP1QPPP/2KR3R b kq - 5 8";
			const std::string blackMoveFEN = "2kr3r/ppp1qppp/2np1n2/1B2p1B1/1b2P1b1/2NP1N2/PPP1QPPP/2KR3R w - - 6 9";

			Move whiteMove("e1", "c1", Move::Special::QueensideCastles);
			Move blackMove("e8", "c8", Move::Special::QueensideCastles);

			TestMoveUnMove(startingFEN, whiteMoveFEN, blackMoveFEN, whiteMove, blackMove);
		}

		// Test that double pawn push moves update the state of the board correctly
		TEST_METHOD(TestMoveUnMoveDoublePawnPush)
		{
			// e4/e5 opening
			const std::string startingFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
			const std::string whiteMoveFEN = "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1";		// After 1. e4
			const std::string blackMoveFEN = "rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq e6 0 2";	// After 1. --- e5

			Move whiteMove("e2", "e4", Move::Special::DoublePawnPush);
			Move blackMove("e7", "e5", Move::Special::DoublePawnPush);

			TestMoveUnMove(startingFEN, whiteMoveFEN, blackMoveFEN, whiteMove, blackMove);
		}

		// Test that en passant moves update the state of the board correctly
		TEST_METHOD(TestMoveUnMoveEnPassantCapture)
		{
			// White en passant capture
			{
				const std::string startingFEN = "4k3/8/8/3Pp3/8/8/8/4K3 w - e6 0 1";
				const std::string endingFEN = "4k3/8/4P3/8/8/8/8/4K3 b - - 0 1";

				Move move("d5", "e6", Move::Special::EnPassantCapture);

				TestMoveUnMove(startingFEN, endingFEN, move);
			}

			// Black en passant capture
			{
				const std::string startingFEN = "4k3/8/8/8/3pP3/8/8/4K3 b - e3 0 1";
				const std::string endingFEN = "4k3/8/8/8/8/4p3/8/4K3 w - - 0 2";

				Move move("d4", "e3", Move::Special::EnPassantCapture);

				TestMoveUnMove(startingFEN, endingFEN, move);
			}
		}
	};
}