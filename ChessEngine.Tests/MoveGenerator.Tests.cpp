#include "pch.h"
#include "CppUnitTest.h"

#include <set>
#include <sstream>
#include <string>
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
                    "a1", "a7", "b2", "b6", "c3", "c5", "e3", "e5", "f2", "g1", // Dark square bishop
                    "b1", "c2", "d3", "d5", "f3", "f5", "g2", "g6", "h1", "h7"  // Light square bishop
                };
                checkAttackedSquares(whiteFEN, whiteAttackedSquares);

                const std::string blackFEN = "8/8/8/3bb3/3BB3/8/8/8 w - - 0 1";
                const std::vector<std::string> blackAttackedSquares{ 
                    "a2", "a8", "b3", "b7", "c4", "c6", "e4", "e6", "f7", "g8", // Light square bishop
                    "b8", "c7", "d4", "d6", "f4", "f6", "g3", "g7", "h2", "h8"  // Dark square bishop
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

        // Helper function testing that for a given FEN, the moves generated in
        // that position match the moves which are expected to be generated
        void TestMoveGenerationForFEN(const std::string& FEN, MoveList expMoves)
        {
            const Board board(FEN);

            MoveList genMoves = MoveGenerator::GenerateMoves(board);

            // Assert sizes are equal
            Assert::AreEqual(expMoves.size(), genMoves.size());

            // Sort the moves in both lists by their actual move values (unsigned shorts)
            auto comparator = [](const Move& move1, const Move& move2) -> bool
            {
                return (move1.GetValue() > move2.GetValue());
            };
            expMoves.sort(comparator);
            genMoves.sort(comparator);

            // Assert contents are equal
            std::wostringstream listSS;
            auto expIt = expMoves.begin();
            auto genIt = genMoves.begin();
            while ((expIt != expMoves.end()) && (genIt != genMoves.end()))
            {
                listSS << expIt->GetStringExtended().c_str() << " , " << genIt->GetStringExtended().c_str() << std::endl;
                
                Assert::IsTrue(expIt->GetValue() == genIt->GetValue(), listSS.str().c_str());

                expIt++;
                genIt++;
            }
        }

        TEST_METHOD(TestPromotionMoveGeneration)
        {
            // Test that promotion moves are correctly generated for white
            {
                const std::string FEN = "2r1r3/3P4/8/8/8/8/8/8 w - - 0 1";
                const MoveList expectedMoves = {
                    {"d7", "c8", true, true, Piece::Type::Knight},
                    {"d7", "c8", true, true, Piece::Type::Bishop},
                    {"d7", "c8", true, true, Piece::Type::Rook},
                    {"d7", "c8", true, true, Piece::Type::Queen},
                    {"d7", "d8", false, true, Piece::Type::Knight},
                    {"d7", "d8", false, true, Piece::Type::Bishop},
                    {"d7", "d8", false, true, Piece::Type::Rook},
                    {"d7", "d8", false, true, Piece::Type::Queen},
                    {"d7", "e8", true, true, Piece::Type::Knight},
                    {"d7", "e8", true, true, Piece::Type::Bishop},
                    {"d7", "e8", true, true, Piece::Type::Rook},
                    {"d7", "e8", true, true, Piece::Type::Queen},
                };
                TestMoveGenerationForFEN(FEN, expectedMoves);
            }

            // Test that promotion moves are correctly generated for black
            {
                const std::string FEN = "8/8/8/8/8/8/3p4/2R1R3 b - - 0 1";
                const MoveList expectedMoves = {
                    {"d2", "c1", true, true, Piece::Type::Knight},
                    {"d2", "c1", true, true, Piece::Type::Bishop},
                    {"d2", "c1", true, true, Piece::Type::Rook},
                    {"d2", "c1", true, true, Piece::Type::Queen},
                    {"d2", "d1", false, true, Piece::Type::Knight},
                    {"d2", "d1", false, true, Piece::Type::Bishop},
                    {"d2", "d1", false, true, Piece::Type::Rook},
                    {"d2", "d1", false, true, Piece::Type::Queen},
                    {"d2", "e1", true, true, Piece::Type::Knight},
                    {"d2", "e1", true, true, Piece::Type::Bishop},
                    {"d2", "e1", true, true, Piece::Type::Rook},
                    {"d2", "e1", true, true, Piece::Type::Queen},
                };
                TestMoveGenerationForFEN(FEN, expectedMoves);
            }
        }

        TEST_METHOD(TestMoveGeneration)
        {
            // Test move generation in the opening position
            {
                const std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
                const MoveList expectedMoves = {
                    // Pawn moves
                    {"a2", "a3"}, {"a2", "a4", Move::Special::DoublePawnPush},
                    {"b2", "b3"}, {"b2", "b4", Move::Special::DoublePawnPush},
                    {"c2", "c3"}, {"c2", "c4", Move::Special::DoublePawnPush},
                    {"d2", "d3"}, {"d2", "d4", Move::Special::DoublePawnPush},
                    {"e2", "e3"}, {"e2", "e4", Move::Special::DoublePawnPush},
                    {"f2", "f3"}, {"f2", "f4", Move::Special::DoublePawnPush},
                    {"g2", "g3"}, {"g2", "g4", Move::Special::DoublePawnPush},
                    {"h2", "h3"}, {"h2", "h4", Move::Special::DoublePawnPush},
                    // Knight moves
                    {"b1", "a3"}, {"b1", "c3"},
                    {"g1", "f3"}, {"g1", "h3"}
                };
                TestMoveGenerationForFEN(FEN, expectedMoves);
            }

            // Test move generation for the Ruy Lopez
            {
                const std::string whiteFEN = "r1b2rk1/2q1bppp/p2p1n2/npp1p3/3PP3/2P2N1P/PPB2PP1/RNBQR1K1 w - - 1 12"; // After 11. ... Qc7
                const MoveList whiteExpectedMoves = {
                    // Pawn moves
                    {"a2", "a3"}, {"a2", "a4", Move::Special::DoublePawnPush},
                    {"b2", "b3"}, {"b2", "b4", Move::Special::DoublePawnPush},
                    {"c3", "c4"},
                    {"d4", "d5"}, {"d4", "c5", true}, {"d4", "e5", true},
                    {"g2", "g3"}, {"g2", "g4", Move::Special::DoublePawnPush},
                    {"h3", "h4"},
                    // Knight moves
                    {"b1", "a3"}, {"b1", "d2"},
                    {"f3", "d2"}, {"f3", "e5", true}, {"f3", "g5"}, {"f3", "h2"}, {"f3", "h4"},
                    // Bishop moves
                    {"c2", "a4"}, {"c2", "b3"}, {"c2", "d3"},
                    {"c1", "d2"}, {"c1", "e3"}, {"c1", "f4"}, {"c1", "g5"}, {"c1", "h6"},
                    // Rook moves
                    {"e1", "e2"}, {"e1", "e3"}, {"e1", "f1"},
                    // Queen moves
                    {"d1", "d2"}, {"d1", "d3"}, {"d1", "e2"},
                    // King moves
                    {"g1", "f1"}, {"g1", "h1"}, {"g1", "h2"}
                };
                TestMoveGenerationForFEN(whiteFEN, whiteExpectedMoves);

                const std::string blackFEN = "r1b2rk1/2q1bppp/p2p1n2/npp1p3/3PP3/2P2N1P/PPBN1PP1/R1BQR1K1 b - - 2 12"; // After 12. Nbd2
                const MoveList blackExpectedMoves = {
                    // Pawn moves
                    {"b5", "b4"},
                    {"c5", "c4"}, {"c5", "d4", true},
                    {"d6", "d5"},
                    {"e5", "d4", true},
                    {"g7", "g6"}, {"g7", "g5", Move::Special::DoublePawnPush},
                    {"h7", "h6"}, {"h7", "h5", Move::Special::DoublePawnPush},
                    // Knight moves
                    {"a5", "b3"}, {"a5", "b7"}, {"a5", "c4"}, {"a5", "c6"},
                    {"f6", "d5"}, {"f6", "d7"}, {"f6", "e4", true}, {"f6", "e8"}, {"f6", "g4"}, {"f6", "h5"},
                    // Bishop moves
                    {"c8", "b7"}, {"c8", "d7"}, {"c8", "e6"}, {"c8", "f5"}, {"c8", "g4"}, {"c8", "h3", true},
                    {"e7", "d8"},
                    // Rook moves
                    {"a8", "a7"}, {"a8", "b8"},
                    {"f8", "e8"}, {"f8", "d8"},
                    // Queen moves
                    {"c7", "a7"}, {"c7", "b6"}, {"c7", "b7"}, {"c7", "b8"}, {"c7", "c6"}, {"c7", "d7"}, {"c7", "d8"},
                    // King moves
                    {"g8", "h8"}
                };
                TestMoveGenerationForFEN(blackFEN, blackExpectedMoves);
            }

            // Test move generation for the deepest Najdorf line I could find
            {
                const std::string whiteFEN = "q3nr1k/4bppp/3p4/4nPP1/r2BP2P/Np2Q3/1P6/1K1R1B1R w - - 5 25";
                const MoveList whiteExpectedMoves = {
                    // Pawn moves
                    {"f5", "f6"},
                    {"g5", "g6"},
                    {"h4", "h5"},
                    // Knight moves
                    {"a3", "b5"}, {"a3", "c2"}, {"a3", "c4"},
                    // Bishop moves
                    {"f1", "a6"}, {"f1", "b5"}, {"f1", "c4"}, {"f1", "d3"}, {"f1", "e2"}, {"f1", "g2"}, {"f1", "h3"},
                    {"d4", "a7"}, {"d4", "b6"}, {"d4", "c3"}, {"d4" ,"c5"}, {"d4", "e5", true},
                    // Rook moves
                    {"d1", "c1"}, {"d1", "d2"}, {"d1", "d3"}, {"d1", "e1"},
                    {"h1", "g1"}, {"h1", "h2"}, {"h1", "h3"},
                    // Queen moves
                    {"e3", "b3", true}, {"e3", "c1"}, {"e3", "c3"}, {"e3", "d2"}, {"e3", "d3"}, {"e3", "e1"}, {"e3", "e2"}, 
                    {"e3", "f2"}, {"e3", "f3"}, {"e3", "f4"}, {"e3" ,"g1"}, {"e3", "g3"}, {"e3", "h3"},
                    // King moves
                    {"b1", "a1"}, {"b1", "a2"}, {"b1", "c1"}, {"b1", "c2"}
                };
                TestMoveGenerationForFEN(whiteFEN, whiteExpectedMoves);

                const std::string blackFEN = "q3nr1k/4bppp/3p4/1B2nPP1/r2BP2P/Np2Q3/1P6/1K1R3R b - - 6 25";
                const MoveList blackExpectedMoves = {
                    // Pawn moves
                    {"d6", "d5"},
                    {"f7", "f6"},
                    {"g7", "g6"},
                    {"h7", "h6"}, {"h7", "h5", Move::Special::DoublePawnPush},
                    // Knight moves
                    {"e5", "c4"}, {"e5", "c6"}, {"e5", "d3"} ,{"e5", "d7"}, {"e5", "f3"}, {"e5", "g4"}, {"e5", "g6"},
                    {"e8", "c7"}, {"e8", "f6"},
                    // Bishop moves
                    {"e7", "d8"}, {"e7", "f6"}, {"e7", "g5", true},
                    // Rook moves
                    {"a4", "a3", true}, {"a4", "a5"}, {"a4", "a6"}, {"a4", "a7"}, {"a4", "b4"}, {"a4", "c4"}, {"a4", "d4", true},
                    {"f8", "g8"},
                    // Queen moves
                    {"a8", "a5"}, {"a8", "a6"}, {"a8", "a7"}, {"a8", "b7"}, {"a8", "b8"}, {"a8", "c6"}, {"a8", "c8"},
                    {"a8", "d5"}, {"a8", "d8"}, {"a8", "e4", true},
                    // King moves
                    {"h8", "g8"}
                };
                TestMoveGenerationForFEN(blackFEN, blackExpectedMoves);
            }
        }
    };
}
