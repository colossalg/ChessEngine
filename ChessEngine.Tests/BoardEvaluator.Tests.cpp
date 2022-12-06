#include "pch.h"
#include "CppUnitTest.h"

#include "Board.h"
#include "BoardEvaluator.h"
#include "Helper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChessEngineTests
{
    using namespace ChessEngine;

    namespace
    {
        const std::string whiteStronglyWinningFEN = "RQ6/2k5/6K1/6Pp/p6r/8/8/8 b - - 0 60"; // White up a queen
        const std::string blackStronglyWinningFEN = "8/8/8/P6R/6pP/6k1/2K5/rq6 w - - 0 60"; // Black up a queen

        const std::string whiteWinningFEN = "r2qk2r/pp1n1ppp/2pBp3/3p4/2PP4/4P3/PP1NQPPP/R3K2R b KQkq - 0 12"; // White up a bishop
        const std::string blackWinningFEN = "r3k2r/pp1nqppp/4p3/2pp4/3P4/2PbP3/PP1N1PPP/R2QK2R w KQkq - 0 12"; // Black up a bishop

        const std::string whiteBetterFEN = "r1bq1rk1/ppp1npbp/3p1np1/3Pp3/2P1P3/2N2N2/PP2BPPP/R1BQ1RK1 w - - 1 9"; // King's indian
        const std::string blackBetterFEN = "r1bq1rk1/pp2bppp/2n2n2/2p1p3/3pP3/3P1NP1/PPP1NPBP/R1BQ1RK1 b - - 0 1"; // King's indian reversed

        const std::string whiteRoughlyEqualFEN = "r3r1k1/ppqn1pp1/2pb1n1p/3p3b/3P3B/2PB1N1P/PPQN1PP1/R3R1K1 w - - 4 14"; // French exchange
        const std::string blackRoughlyEqualFEN = "r3r1k1/ppqn1pp1/2pb1n1p/3p3b/3P3B/2PB1N1P/PPQN1PP1/R3R1K1 b - - 4 14"; // French exchange
    }

    TEST_CLASS(BoardEvaluatorTests)
    {
    public:

        // Test the evaluation of two test positions which are symmetric for the two colours.
        void TestSymmetric(const std::string & whiteFEN, const std::string& blackFEN)
        {
            const Board whiteBoard(whiteFEN);
            const Board blackBoard(blackFEN);

            BoardEvaluator evaluator;

            const int whiteEvaluation = evaluator.Evaluate(whiteBoard);
            const int blackEvaluation = evaluator.Evaluate(blackBoard);

            Assert::AreEqual(whiteEvaluation, blackEvaluation);
        }

        // Test the evaluation symmetry of the test positions. The evaluation should be the same for white and black.
        TEST_METHOD(TestSymmetry)
        {
            TestSymmetric(whiteStronglyWinningFEN, blackStronglyWinningFEN);
            TestSymmetric(whiteWinningFEN, blackWinningFEN);
            TestSymmetric(whiteBetterFEN, blackBetterFEN);
            TestSymmetric(whiteRoughlyEqualFEN, blackRoughlyEqualFEN);
        }

        // Test that the evaluation function correctly evaluates the positions relative to each other, in order of best to worst.
        void TestOrder(std::vector<std::pair<std::string, bool>> orderedFENs)
        {
            BoardEvaluator evaluator;

            auto it1 = orderedFENs.begin();
            auto it2 = orderedFENs.begin() + 1;
            while (it2 != orderedFENs.end())
            {
                const Board board1(it1->first);
                const Board board2(it2->first);

                // Get the evaluation, flipping the sign if the position is actually from black's perspective
                const int evaluation1 = evaluator.Evaluate(board1) * (it1->second ? 1 : -1);
                const int evaluation2 = evaluator.Evaluate(board2) * (it1->second ? 1 : -1);

                const std::string errorMessage = std::to_string(evaluation1) + " > " + std::to_string(evaluation2);
                Assert::IsTrue(evaluation1 > evaluation2, Helper::StringToWString(errorMessage).c_str());

                it1++;
                it2++;
            }
        }
    
        // Test the evaluation ordering of the test positions.
        TEST_METHOD(TestOrdering)
        {
            const std::vector<std::pair<std::string, bool>> whiteFENsOrdered = {
                { whiteStronglyWinningFEN, false },
                { whiteWinningFEN, false },
                { whiteBetterFEN, true },
                { whiteRoughlyEqualFEN, true }
            };

            TestOrder(whiteFENsOrdered);

            // No need to test the black positions as we already test for symmetry of evaluation.
        }
    };
}
