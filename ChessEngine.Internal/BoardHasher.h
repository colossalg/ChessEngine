#pragma once

#include "Definitions.h"

namespace ChessEngine
{
	class BoardHasher
	{
	public:

		// Get the Zobrist hash for a given board
		static unsigned int Hash(const Board& board);

		// Update the hash by settign the piece at a given square
		static unsigned int UpdatePiece(unsigned int hash, const Square square, const Piece oldPiece, const Piece newPiece);

		// Update the hash by setting the rank of the en passant square
		static unsigned int UpdateEnPassant(unsigned int hash, const EnPassant& oldEnPassant, const EnPassant& newEnPassant);

		// Update the hash by setting whether white can castle kingside
		static unsigned int UpdateCanWhiteCastleKingside(unsigned int hash, const bool oldCastlingRights, const bool newCastlingRights);

		// Update the hash by setting whether white can castle queenside
		static unsigned int UpdateCanWhiteCastleQueenside(unsigned int hash, const bool oldCastlingRights, const bool newCastlingRights);

		// Update the hash by setting whether black can castle kingside
		static unsigned int UpdateCanBlackCastleKingside(unsigned int hash, const bool oldCastlingRights, const bool newCastlingRights);

		// Update the hash by setting whether black can castle queenside
		static unsigned int UpdateCanBlackCastleQueenside(unsigned int hash, const bool oldCastlingRights, const bool newCastlingRights);

		// Update the hash by setting whether it is white's turn to play
		static unsigned int UpdateWhiteToPlay(unsigned int hash, const bool oldWhiteToPlay, const bool newWhiteToPlay);

	private:

		// Initialize the random numbers used for zobrist hashing
		static void InitializeRandomNumbers(unsigned int seed = 0);
	};
}

