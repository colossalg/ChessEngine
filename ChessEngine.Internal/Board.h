#pragma once

#include <string>

#include "Definitions.h"
#include "Piece.h"

namespace ChessEngine
{
	class Board
	{
		friend class AsciiUI;
		friend class BoardEvaluator;
		friend class MoveGenerator;
		friend class MoveInverse;

	public:

		const static PieceArray StartingPieces; // The starting pieces for a board

		// Create a new board
		Board();

		// Create a new board from a FEN string
		Board(const std::string& FEN);

		// Get the FEN string for the board
		std::string GetFEN() const;

		// Update the board as per the given move
		void MakeMove(const Move move);

		// Update the board as per the given move inverse
		void UndoMove(const MoveInverse moveInverse);

	private:

		// Helper function which updates the piece array by moving a piece from 'init' to 'dest'
		void MovePiece(const Square init, const Square dest);

		// Helper function which updates the piece array bu 'undoing' MovePiece
		void MovePieceInverse(const Square init, const Square dest, const Piece capturedPiece = Piece::ee);

		// Helper function for handling kingside castles
		void KCastles();

		// Helper function for 'undoing' kingside castles
		void KCastlesInverse();

		// Helper function for handling queenside castles
		void QCastles();

		// Helper function for 'undoing' queenside castles
		void QCastlesInverse();

		// Helper function for handling en passant capture
		void EPCapture(const Square init, const Square dest);

		// Helper function for 'undoing' an en passant capture
		void EPCaptureInverse(const Square init, const Square dest);

		// Helper function for handling promotion
		void Promotion(const Square init, const Square dest, const Piece::Type type);

		// Helper function for 'undoing' a promotion
		void PromotionInverse(const Square init, const Square dest, const Piece capturedPiece = Piece::ee);

		constexpr static Square WhiteKingStartingSquare = 4;			// The starting square of the white king (e1)
		constexpr static Square BlackKingStartingSquare = 60;			// The starting square of the black king (e8)
		constexpr static Square WhiteKingsideRookStartingSquare = 7;	// The starting square of the white kingside rook (h1)
		constexpr static Square BlackKingsideRookStartingSquare = 63;	// The starting square of the black kingside rook (h8)
		constexpr static Square WhiteQueensideRookStartingSquare = 0;	// The starting square of the white queenside rook (a1)
		constexpr static Square BlackQueensideRookStartingSquare = 56;	// The starting square fo the black queenside rook (a8)

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

