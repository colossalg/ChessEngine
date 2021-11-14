#pragma once

namespace ChessEngine
{
	class Board;

	class BoardHasher
	{
	public:

		// Get the Zobrist hash for a given board
		static unsigned int Hash(const Board& board);

	private:

		// Initialize the random numbers used for zobrist hashing
		static void InitializeRandomNumbers(unsigned int seed = 0);
	};
}

