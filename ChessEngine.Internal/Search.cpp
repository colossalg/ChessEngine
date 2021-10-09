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

namespace ChessEngine
{
	std::pair<Move, int> Search::SearchPosition(Board& board, const unsigned char maxDepth)
	{
		return SearchPositionPruned(
			board,
			maxDepth,
			std::numeric_limits<int>::min(),
			std::numeric_limits<int>::max());
	}

	// Implemented as per wikipedia description of alpha-beta pruning: https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning
	std::pair<Move, int> Search::SearchPositionPruned(
		Board& board, 
		const unsigned char maxDepth, 
		int alpha,
		int beta)
	{
		Move bestMove;
		int  bestEval;

		if (maxDepth == 0)
		{
			// Convert from symmetric scoring to +ve for white, -ve for black
			bestEval = m_evaluator.Evaluate(board) * (board.GetWhiteToPlay() ? +1 : -1);
			return std::pair<Move, int>(bestMove, bestEval);
		}

		if (board.GetWhiteToPlay())
		{
			bestEval = std::numeric_limits<int>::min();

			const MoveList moveList = MoveGenerator::GenerateMoves(board);
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

			const MoveList moveList = MoveGenerator::GenerateMoves(board);
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
}
