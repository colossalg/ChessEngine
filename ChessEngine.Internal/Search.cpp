#include "pch.h"

#include "Search.h"

#include <chrono>
#include <tuple>

#include "Board.h"
#include "BoardEvaluator.h"
#include "Definitions.h"
#include "Move.h"
#include "MoveGenerator.h"
#include "MoveInverse.h"

namespace ChessEngine
{
	std::pair<Move, int> Search::SearchPosition(Board& board, const unsigned char maxDepth)
	{
		Move bestMove;
		int  bestEval = -1000000;

		if (maxDepth == 0)
		{
			BoardEvaluator evaluator;

			bestMove = Move();
			bestEval = evaluator.Evaluate(board);
		}
		else
		{
			const MoveList moveList = MoveGenerator::GenerateMoves(board);
			for (auto& move : moveList)
			{
				MoveInverse moveInverse(board, move);

				board.MakeMove(move);

				std::pair<Move, int> moveResult = SearchPosition(board, maxDepth - 1);
				Move nextPositionMove = moveResult.first;
				int  nextPositionEval = moveResult.second * (-1);

				if (nextPositionEval > bestEval)
				{
					bestMove = move;
					bestEval = nextPositionEval;
				}

				board.UndoMove(moveInverse);
			}
		}

		return std::pair<Move, int>(bestMove, bestEval);
	}
}
