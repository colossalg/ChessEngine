#pragma once

#include "BoardEvaluator.h"
#include "SearchMetrics.h"
#include "TranspositionTable.h"

namespace ChessEngine
{
    class Board;
    class Move;

    class Search
    {
    public:

        // Search a position to a given depth for the 'best move' in the position
        std::pair<Move, int> SearchPosition(Board& board, const unsigned char maxDepth);

    private:

        // Search a position to a given depth using an 'alpha-beta' style pruning search algorithm
        std::pair<Move, int> SearchPositionPruned(
            Board& board,
            const unsigned char maxDepth,
            int alpha,
            int beta);

        // Sort a list of moves based upon which look the most appealing for the given board
        MoveList SortMoves(const MoveList& moveList);

        BoardEvaluator m_evaluator; // The board evaluator used to evaluate positions during search

        SearchMetrics m_metrics;    // The metrics collected during the search
    };
}
