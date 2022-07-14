#include "pch.h"

#include "Search.h"

#include <chrono>
#include <limits>
#include <tuple>

#include "Board.h"
#include "Definitions.h"
#include "Move.h"
#include "MoveGenerator.h"
#include "MoveInverse.h"

namespace
{
    constexpr bool CollectMetrics = true;
}

namespace ChessEngine
{
    std::pair<Move, int> Search::SearchPosition(Board& board, const unsigned char maxDepth)
    {
        METRICS_SET_MAX_DEPTH(CollectMetrics, m_metrics, maxDepth);
        METRICS_SEARCH_START(CollectMetrics, m_metrics);

        std::pair<Move, int> searchResult = SearchPositionPruned(
            board,
            maxDepth,
            std::numeric_limits<int>::min(),
            std::numeric_limits<int>::max());

        METRICS_SEARCH_STOP(CollectMetrics, m_metrics);
        METRICS_PRINT(CollectMetrics, m_metrics);
        METRICS_WRITE(CollectMetrics, m_metrics);

        return searchResult;
    }

    // Implemented as per wikipedia description of alpha-beta pruning:
    // https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning
    std::pair<Move, int> Search::SearchPositionPruned(
        Board& board,
        const unsigned char maxDepth, 
        int alpha,
        int beta)
    {
        METRICS_SEARCH_INCREMENT(CollectMetrics, m_metrics, 1);

        if (maxDepth == 0)
        {
            METRICS_EVALUATION_START(CollectMetrics, m_metrics);

            // Convert from symmetric scoring to +ve for white, -ve for black
            int eval = m_evaluator.Evaluate(board) * (board.GetWhiteToPlay() ? +1 : -1);

            METRICS_EVALUATION_STOP(CollectMetrics, m_metrics);
            METRICS_EVALUATION_INCREMENT(CollectMetrics, m_metrics, 1);

            return std::pair<Move, int>(Move(), eval);
        }

        Move bestMove;
        int  bestEval;

        METRICS_GENERATION_START(CollectMetrics, m_metrics);

        const MoveList moveList = SortMoves(MoveGenerator::GenerateMoves(board));

        METRICS_GENERATION_STOP(CollectMetrics, m_metrics);
        METRICS_GENERATION_INCREMENT(CollectMetrics, m_metrics, static_cast<int>(moveList.size()));

        if (board.GetWhiteToPlay())
        {
            bestEval = std::numeric_limits<int>::min();

            for (const Move& move : moveList)
            {
                MoveInverse moveInverse(board, move);
                board.MakeMove(move);

                std::pair<Move, int> moveResult = SearchPositionPruned(board, maxDepth - 1, alpha, beta);

                if (moveResult.second > bestEval)
                {
                    bestMove = move;
                    bestEval = moveResult.second;
                }

                board.UndoMove(moveInverse);

                if (bestEval >= beta)
                    break;

                alpha = std::max(alpha, bestEval);
            }
        }
        else
        {
            bestEval = std::numeric_limits<int>::max();

            for (const Move& move : moveList)
            {
                MoveInverse moveInverse(board, move);
                board.MakeMove(move);

                std::pair<Move, int> moveResult = SearchPositionPruned(board, maxDepth - 1, alpha, beta);

                if (moveResult.second < bestEval)
                {
                    bestMove = move;
                    bestEval = moveResult.second;
                }

                board.UndoMove(moveInverse);

                if (bestEval <= alpha)
                    break;

                beta = std::min(beta, bestEval);
            }
        }

        return std::pair<Move, int>(bestMove, bestEval);
    }

    MoveList Search::SortMoves(const MoveList& moveList)
    {
        const auto& comp = [](const Move& move1, const Move& move2) -> bool
        {
            if (move1.IsPromotion() && !move2.IsPromotion())
            {
                return true;
            }

            if (move1.IsCapture() && !move2.IsCapture())
            {
                return true;
            }

            if ((move1.IsKingsideCastles() || move1.IsQueensideCastles()) &&
                !(move2.IsKingsideCastles() || move2.IsQueensideCastles()))
            {
                return true;
            }

            return false;
        };

        MoveList sorted;

        for (const auto& move : moveList)
        {
            sorted.insert(
                std::find_if(
                    sorted.cbegin(),
                    sorted.cend(),
                    [&comp, &move](const Move& curr) -> bool { return comp(move, curr); }),
                move);
        }

        return sorted;
    }
}
