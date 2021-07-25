#pragma once

#include "Definitions.h"
#include "Move.h"

namespace ChessEngine
{
	class Board;

	class MoveInverse
	{
	public:

		// Create a new move inverse for a given board and move
		MoveInverse(const Board& board, Move move);

		// Get the move which this is the inverse move for
		Move GetMove() const { return m_move; }

		// Get the en passant square (if en passant is possible) prior to the move which this is the inverse move for
		EnPassant GetEnPassant() const { return m_enPassant; }

		// Get whether white can castle kingside prior to the move which this is the inverse move for
		bool GetWhiteKingside() const { return m_whiteKingside; }

		// Get whether white can castle queenside prior to the move which this is the inverse move for
		bool GetWhiteQueenside() const { return m_whiteQueenside; }

		// Get whether black can castle kingside prior to the move which this is the inverse move for
		bool GetBlackKingside() const { return m_blackKingside; }

		// Get whether black can castle queenside prior to the move which this is the inverse move for
		bool GetBlackQueenside() const { return m_blackQueenside; }

		// Get the number of half moves prior to the move which this is the inverse move for
		unsigned char GetHalfMoves() const { return m_halfMoves; }

		// Get the piece that was captured in the move which this is the inverse move for
		Piece GetCapturedPiece() const { return m_capturedPiece; }

	private:

		const Move m_move;				// The move which this is the inverse move for

		const EnPassant m_enPassant;	// The en passant square (if en passant is possible)

		const bool m_whiteKingside;		// Whether white can castle kingside
		const bool m_whiteQueenside;	// Whether white can castle queenside
		const bool m_blackKingside;		// Whether black can castle kingside
		const bool m_blackQueenside;	// Whether black can castle queenside

		const unsigned char m_halfMoves;	// The number of half moves played since last irreversible move

		Piece m_capturedPiece;	// The piece that was captured (if any)
	};
}