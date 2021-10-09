#pragma once

namespace ChessEngine
{
	class Board;
	class Move;

	class Search
	{
	public:

		// Search a position to a given depth for the 'best move' in the position
		std::pair<Move, int> SearchPosition(Board& board, const unsigned char maxDepth);

		// Search a position for a given time for the 'best move' in the position
		// void SearchPosition(Board& board, std::chrono::duration<std::chrono::seconds> maxTime);
	};
}
