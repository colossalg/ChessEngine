#pragma once

#include <string>

#include "Definitions.h"
#include "Helper.h"
#include "Move.h"
#include "Piece.h"

namespace ChessEngine
{
	class Board
	{
	public:
		const static Square WhiteKingStartingSquare = 4;			// The starting square of the white king (e1)
		const static Square BlackKingStartingSquare = 60;			// The starting square of the black king (e8)
		const static Square WhiteKingsideRookStartingSquare = 7;	// The starting square of the white kingside rook (h1)
		const static Square BlackKingsideRookStartingSquare = 63;	// The starting square of the black kingside rook (h8)
		const static Square WhiteQueensideRookStartingSquare = 0;	// The starting square of the white queenside rook (a1)
		const static Square BlackQueensideRookStartingSquare = 56;	// The starting square fo the black queenside rook (a8)

		const static PieceArray StartingPieces; // The starting pieces for a board

		// Create a new board
		Board();

		// Create a new board from a FEN string
		Board(const std::string& FEN);

		// Get the FEN string for the board
		std::string GetFEN() const;

		// Update the board as per the given move
		void MakeMove(Move move);

		// Get the array representing the piece's locations on the board
		const PieceArray& GetPieces() const { return m_pieces; }

		// Get the en passant square (if en passant is possible)
		EnPassant GetEnPassant() const { return m_enPassant; }

		// Get whether white can castle kingside
		bool GetWhiteCanCastleKingside() { return m_whiteKingside; }

		// Get whether white can castle queenside
		bool GetWhiteCanCastleQueenside() { return m_whiteQueenside; }

		// Get whether black can castle kingside
		bool GetBlackCanCastlekingside() { return m_blackKingside; }

		// Get whether black can castle queenside
		bool GetBlackCanCastleQueenside() { return m_blackQueenside; }

		// Get whether it is white's turn to play
		bool GetWhiteToPlay() const { return m_whiteToPlay; }

	private:

		// Helper function which updates the piece array by moving a piece from 'init' to 'dest'
		inline void MovePiece(Square init, Square dest);

		// Helper function for handling kingside castles
		inline void KCastles(Move move);

		// Helper function for handling queenside castles
		inline void QCastles(Move move);

		// Helper function for handling en passant capture
		inline void EPCapture(Move move);

		// Helper function for handling promotion
		void Promotion(Move move);

		PieceArray m_pieces;		// The pieces locations on the board

		EnPassant m_enPassant;		// The en passant square (if en passant is possible)

		bool m_whiteKingside = true;	// Whether white can castle kingside
		bool m_whiteQueenside = true;	// Whether white can castle queenside
		bool m_blackKingside = true;	// Whether black can castle kingside
		bool m_blackQueenside = true;	// Whether black can castle queenside

		bool m_whiteToPlay = true;	// Whether it is white's turn to play

		unsigned char m_halfMoves = 0;	// The number of half moves played since last irreversible move
		unsigned char m_fullMoves = 0;	// The number of full moves played
	};
}

