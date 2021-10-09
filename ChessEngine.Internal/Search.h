#pragma once

#include "BoardEvaluator.h"

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

		BoardEvaluator m_evaluator; // The board evaluator used to evaluate positions during search
	};
}
