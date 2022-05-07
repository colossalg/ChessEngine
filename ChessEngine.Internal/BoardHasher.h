#pragma once

#include "Definitions.h"

namespace ChessEngine
{
    class BoardHasher
    {
    public:

        // Set the hash of the board this board hasher belongs to
        void SetHash(const Board& board);

        // Get the hash of the board this board hasher belongs to
        unsigned int GetHash() const { return m_hash; }

        // Update the hash by settign the piece at a given square
        void UpdatePiece(const Square square, const Piece oldPiece, const Piece newPiece);

        // Update the hash by setting the rank of the en passant square
        void UpdateEnPassant(const EnPassant& oldEnPassant, const EnPassant& newEnPassant);

        // Update the hash by setting whether white can castle kingside
        void UpdateCanWhiteCastleKingside(const bool oldCastlingRights, const bool newCastlingRights);

        // Update the hash by setting whether white can castle queenside
        void UpdateCanWhiteCastleQueenside(const bool oldCastlingRights, const bool newCastlingRights);

        // Update the hash by setting whether black can castle kingside
        void UpdateCanBlackCastleKingside(const bool oldCastlingRights, const bool newCastlingRights);

        // Update the hash by setting whether black can castle queenside
        void UpdateCanBlackCastleQueenside(const bool oldCastlingRights, const bool newCastlingRights);

        // Update the hash by setting whether it is white's turn to play
        void UpdateWhiteToPlay(const bool oldWhiteToPlay, const bool newWhiteToPlay);

    private:

        // Initialize the random numbers used for zobrist hashing
        static void InitializeRandomNumbers(unsigned int seed = 0);

        unsigned int m_hash = 0;    // The hash of the board that this board hasher belongs to
    };
}

