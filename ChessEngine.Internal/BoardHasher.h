#pragma once

#include "Definitions.h"

namespace ChessEngine
{
	class BoardHasher
	{
	public:

		// Get the Zobrist hash for a given board
		static unsigned int Hash(const Board& board);

		// Update the hash by inserting the given piece at the given position
		static unsigned int InsertPiece(unsigned int hash, const Square square, const Piece piece);

		// Update the hash by removing the given piece at the given position
		static unsigned int RemovePiece(unsigned int hash, const Square square, const Piece piece);

		// Update the hash by setting the rank of the en passant square
		static unsigned int UpdateEnPassant(unsigned int hash, const EnPassant& oldEnPassant, const EnPassant& newEnPassant);

		// Update the hash by setting whether white can castle kingside
		static unsigned int UpdateWhiteCastleKingside(unsigned int hash);

		// Update the hash by setting whether white can castle queenside
		static unsigned int UpdateWhiteCastleQueenside(unsigned int hash);

		// Update the hash by setting whether black can castle kingside
		static unsigned int UpdateBlackCastleKingside(unsigned int hash);

		// Update the hash by setting whether white can castle queenside
		static unsigned int UpdateBlackCastleQueenside(unsigned int hash);

	private:

		// Initialize the random numbers used for zobrist hashing
		static void InitializeRandomNumbers(unsigned int seed = 0);
	};
}

