#pragma once

#include <string>

#include "Definitions.h"
#include "Helper.h"

namespace ChessEngine
{
	class Move;
	class MoveInverse;
	class Piece;

	class Board
	{
	public:

		const static PieceArray StartingPieces; // The starting pieces for a board

		// Create a new board
		Board();

		// Create a new board from a FEN string
		Board(const std::string& FEN);

		// Get the FEN string for the board
		std::string GetFEN() const;

		// Update the board as per the given move
		void MakeMove(Move move);

		// Update the board as per the given move inverse
		void UndoMove(MoveInverse moveInverse);

		// Get the array representing the piece's locations on the board
		const PieceArray& GetPieces() const { return m_pieces; }

		// Get the en passant square (if en passant is possible)
		EnPassant GetEnPassant() const { return m_enPassant; }

		// Get whether white can castle kingside
		bool GetWhiteCanCastleKingside() const { return m_whiteKingside; }

		// Get whether white can castle queenside
		bool GetWhiteCanCastleQueenside() const { return m_whiteQueenside; }

		// Get whether black can castle kingside
		bool GetBlackCanCastleKingside() const { return m_blackKingside; }

		// Get whether black can castle queenside
		bool GetBlackCanCastleQueenside() const { return m_blackQueenside; }

		// Get whether it is white's turn to play
		bool GetWhiteToPlay() const { return m_whiteToPlay; }

		// Get the number of half moves played since the lase irreversible move
		unsigned char GetHalfMoves() const { return m_halfMoves; }

		// Get the number of full moves played
		unsigned char GetFullMoves() const { return m_fullMoves; }

	private:

		// Helper function which updates the piece array by moving a piece from 'init' to 'dest'
		inline void MovePiece(const Square init, const Square dest);

		// Helper function which updates the piece array bu 'undoing' MovePiece
		inline void MovePieceInverse(const Square init, const Square dest, const Piece capturedPiece = Piece::ee);

		// Helper function for handling kingside castles
		inline void KCastles();

		// Helper function for 'undoing' kingside castles
		inline void KCastlesInverse();

		// Helper function for handling queenside castles
		inline void QCastles();

		// Helper function for 'undoing' queenside castles
		inline void QCastlesInverse();

		// Helper function for handling en passant capture
		inline void EPCapture(const Square init, const Square dest);

		// Helper function for 'undoing' an en passant capture
		inline void EPCaptureInverse(const Square init, const Square dest);

		// Helper function for handling promotion
		void Promotion(const Square init, const Square dest, const Piece::Type type);

		// Helper function for 'undoing' a promotion
		void PromotionInverse(const Square init, const Square dest, const Piece capturedPiece = Piece::ee);

		const static Square WhiteKingStartingSquare = 4;			// The starting square of the white king (e1)
		const static Square BlackKingStartingSquare = 60;			// The starting square of the black king (e8)
		const static Square WhiteKingsideRookStartingSquare = 7;	// The starting square of the white kingside rook (h1)
		const static Square BlackKingsideRookStartingSquare = 63;	// The starting square of the black kingside rook (h8)
		const static Square WhiteQueensideRookStartingSquare = 0;	// The starting square of the white queenside rook (a1)
		const static Square BlackQueensideRookStartingSquare = 56;	// The starting square fo the black queenside rook (a8)

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

