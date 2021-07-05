#pragma once

#include <array>
#include <string>

#include "Definitions.h"

namespace ChessEngine
{
	class AsciiUI
	{
	public:
		// Get an ascii representation of the board
		std::string GetAscii();

		// Set the array representing the piece's locations on the board
		void SetPieces(const PieceArray& pieces) { m_pieces = pieces; }

		// Set the en passant square (if en passant is possible)
		void SetEnPassant(EnPassant enPassant) { m_enPassant = enPassant; }

		// Set whether it is white's turn to play
		void SetWhiteToPlay(bool whiteToPlay) { m_whiteToPlay = whiteToPlay; }

		// Set the castling rights (each of white kingside, white queenside, black kingside, black queenside)
		void SetCastling(bool whiteKingside, bool whiteQueenside, bool blackKingside, bool blackQueenside);

	private:
		PieceArray m_pieces;		// The pieces locations on the board

		EnPassant m_enPassant;		// The en passant square (if en passant is possible)

		bool m_whiteToPlay = true;	// Whether it is white's turn to play

		bool m_whiteKingside = true;	// Can white castle kingside
		bool m_blackKingside = true;	// Can black castle kingside
		bool m_whiteQueenside = true;	// Can white castle queenside
		bool m_blackQueenside = true;	// Can black castle queenside
	};
}