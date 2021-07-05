#pragma once

#include "Definitions.h"
#include "PieceHelper.h"

namespace ChessEngine
{
	class Board
	{
	public:
		// The starting pieces for a board
		const static PieceArray StartingPieces;

		// Set the array representing the piece's locations on the board
		void SetPieces(const PieceArray& pieces) { m_pieces = pieces; }

		// Get the array representing the piece's locations on the board
		const PieceArray& GetPieces() const { return m_pieces; }

		// Set the en passant square (if en passant is possible)
		void SetEnPassant(EnPassant enPassant) { m_enPassant = enPassant; }

		// Get the en passant square (if en passant is possible)
		EnPassant GetEnPassant() const { return m_enPassant; }

		// Set whether it is white's turn to play
		void SetWhiteToPlay(bool whiteToPlay) { m_whiteToPlay = whiteToPlay; }

		// Get whether it is white's turn to play
		bool GetWhiteToPlay() const { return m_whiteToPlay; }

	private:
		PieceArray m_pieces;		// The pieces locations on the board

		EnPassant m_enPassant;		// The en passant square (if en passant is possible)

		bool m_whiteToPlay = true;	// Whether it is white's turn to play
	};
}

