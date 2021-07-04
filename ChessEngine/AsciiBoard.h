#pragma once

#include <array>
#include <string>

#include "Definitions.h"

namespace ChessEngine
{
	class AsciiBoard
	{
	public:
		/**
		* @return the board represented as an ascii string
		*/
		std::string GetAscii();

		/**
		* Set the pieces
		* @param pieces The pieces
		*/
		void SetPieces(std::array<Piece, 64>& pieces);

		/**
		* Set the castling
		* @param whiteKingside Whether white can castle kingside
		* @param blackKingside Whether black can castle kingside
		* @param whiteQueenside Whether white can castle queenside
		* @param blackQueenside Whether black can castle queenside
		*/
		void SetCastling(bool whiteKingside, bool blackKingside, bool whiteQueenside, bool blackQueenside);

		/**
		* Set the en passant
		* @param possible Whether an en passant capture is possible
		* @param square The square where the en passant capture is possible
		*/
		void SetEnPassant(bool possible, Square square);

	private:
		std::array<Piece, 64> m_pieces{};	///< The pieces

		bool m_whiteToPlay = true;		///< Whether it is white's turn to play

		bool m_whiteKingside = true;	///< Can white castle kingside
		bool m_blackKingside = true;	///< Can black castle kingside
		bool m_whiteQueenside = true;	///< Can white castle queenside
		bool m_blackQueenside = true;	///< Can black castle queenside

		bool m_enPassantPossible = false;		///< Whether an en passant capture is possible
		Square m_enPassantSquare = Square(0);	///< The square where the en passant capture is possible
	};
}