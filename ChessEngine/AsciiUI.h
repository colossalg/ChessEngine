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
		void SetPieces(std::array<Piece, 64>& pieces);

		// Set whether it is white's turn to play
		void SetWhiteToPlay(bool whiteToPlay);

		// Set the castling rights (each of white kingside, white queenside, black kingside, black queenside)
		void SetCastling(bool whiteKingside, bool whiteQueenside, bool blackKingside, bool blackQueenside);

		// Set the en passan (whether it is possible and on what square)
		void SetEnPassant(bool possible, Square square);

	private:
		std::array<Piece, 64> m_pieces{};	// The pieces locations on the board

		bool m_whiteToPlay = true;		// Whether it is white's turn to play

		bool m_whiteKingside = true;	// Can white castle kingside
		bool m_blackKingside = true;	// Can black castle kingside
		bool m_whiteQueenside = true;	// Can white castle queenside
		bool m_blackQueenside = true;	// Can black castle queenside

		bool m_enPassantPossible = false;		// Whether an en passant capture is possible
		Square m_enPassantSquare = Square(0);	// The square where the en passant capture is possible
	};
}