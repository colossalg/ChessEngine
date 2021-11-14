#pragma once

#include "BoardHasher.h"
#include "Definitions.h"
#include "Piece.h"

namespace ChessEngine
{
	class Board
	{
	public:

		constexpr static Square WhiteKingStartingSquare = 4;			// The starting square of the white king (e1)
		constexpr static Square BlackKingStartingSquare = 60;			// The starting square of the black king (e8)
		constexpr static Square WhiteKingsideRookStartingSquare = 7;	// The starting square of the white kingside rook (h1)
		constexpr static Square BlackKingsideRookStartingSquare = 63;	// The starting square of the black kingside rook (h8)
		constexpr static Square WhiteQueensideRookStartingSquare = 0;	// The starting square of the white queenside rook (a1)
		constexpr static Square BlackQueensideRookStartingSquare = 56;	// The starting square fo the black queenside rook (a8)

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

		// Get the pieces locations on the board
		const PieceArray& GetPieces() const { return m_pieces; }

		// Get the en passant square (if en passant is possible)
		const EnPassant& GetEnPassant() const { return m_enPassant; }

		bool CanWhiteCastleKingside() const { return m_whiteKingside; }		// Get whether white can castle kingside
		bool CanWhiteCastleQueenside() const { return m_whiteQueenside; }	// Get whether white can castle queenside
		bool CanBlackCastleKingside() const { return m_blackKingside; }		// Get whether black can castle kingside
		bool CanBlackCastleQueenside() const { return m_blackQueenside; }	// Get whether black can castle queenside

		// Get whether it is white's turn to play
		bool GetWhiteToPlay() const { return m_whiteToPlay; }

		// Get the number of half moves played since the last irreversible move
		unsigned char GetHalfMoves() const { return m_halfMoves; }

		// Get the number of full moves played
		unsigned char GetFullMoves() const { return m_fullMoves; }

		// Get the Zobrist hash for the position
		unsigned int GetHash() const { return m_boardHasher.GetHash(); }

	private:

		// NOTE: Some of the helper functions below should be used for setting the 

		// Helper function for setting the piece on a given square (also updates the hash)
		void SetPiece(const Square square, const Piece piece);

		// Helper function for setting the en passant square (also updates the hash)
		void SetEnPassant(const EnPassant& enPassant);

		// Helper functions for setting the castling rights (also updates the hash)
		void SetCanWhiteCastleKingside(const bool canCastle);
		void SetCanWhiteCastleQueenside(const bool canCastle);
		void SetCanBlackCastleKingside(const bool canCastle);
		void SetCanBlackCastleQueenside(const bool canCastle);

		// Helper function for setting whether it is white's turn to play (also updates the hash)
		void SetWhiteToPlay(bool whiteToPlay);

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

		PieceArray m_pieces;		// The pieces locations on the board

		EnPassant m_enPassant;		// The en passant square (if en passant is possible)

		bool m_whiteKingside = true;	// Whether white can castle kingside
		bool m_whiteQueenside = true;	// Whether white can castle queenside
		bool m_blackKingside = true;	// Whether black can castle kingside
		bool m_blackQueenside = true;	// Whether black can castle queenside

		bool m_whiteToPlay = true;	// Whether it is white's turn to play

		unsigned char m_halfMoves = 0;	// The number of half moves played since last irreversible move
		unsigned char m_fullMoves = 0;	// The number of full moves played

		BoardHasher m_boardHasher;	// The hasher for this board
	};
}

