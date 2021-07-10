#pragma once

#include <string>

#include "Definitions.h"
#include "Piece.h"

namespace ChessEngine
{
	class MoveGenerator; // Forward declaration

	class Board
	{
	public:
		// The starting pieces for a board
		const static PieceArray StartingPieces;

		// Create a new board
		Board();

		// Create a new board from a FEN string
		Board(const std::string& FEN);

		// Set the array representing the piece's locations on the board
		void SetPieces(const PieceArray& pieces) { m_pieces = pieces; }

		// Get the array representing the piece's locations on the board
		const PieceArray& GetPieces() const { return m_pieces; }

		// Set the en passant square (if en passant is possible)
		void SetEnPassant(EnPassant enPassant) { m_enPassant = enPassant; }

		// Get the en passant square (if en passant is possible)
		EnPassant GetEnPassant() const { return m_enPassant; }

		// Set whether white can castle kingside
		void SetWhiteCanCastleKingside(bool canCastle) { m_whiteKingside = canCastle; }

		// Get whether white can castle kingside
		bool GetWhiteCanCastleKingside() { return m_whiteKingside; }

		// Set whether white can castle kingside
		void SetWhiteCanCastleQueenside(bool canCastle) { m_whiteQueenside = canCastle; }

		// Get whether white can castle queenside
		bool GetWhiteCanCastleQueenside() { return m_whiteQueenside; }

		// Set whether black can castle kingside
		void SetBlackCanCastleKingside(bool canCastle) { m_blackKingside = canCastle; }

		// Get whether black can castle kingside
		bool GetBlackCanCastlekingside() { return m_blackKingside; }

		// Set whether black can castle queenside
		void SetBlackCanCastleQueenside(bool canCastle) { m_blackQueenside = canCastle; }

		// Get whether black can castle queenside
		bool GetBlackCanCastleQueenside() { return m_blackQueenside; }

		// Set whether it is white's turn to play
		void SetWhiteToPlay(bool whiteToPlay) { m_whiteToPlay = whiteToPlay; }

		// Get whether it is white's turn to play
		bool GetWhiteToPlay() const { return m_whiteToPlay; }

		// Get the FEN string for the board
		std::string GetFEN() const;

	private:
		// Helper function which updates the piece lists based upon the piece array
		void UpdatePieceLists();

		PieceArray m_pieces;		// The pieces locations on the board
		PieceList m_whitePieceList; // A list of each of the white pieces as well as their square on the board
		PieceList m_blackPieceList; // A list of each of the black pieces as well as their square on the board

		EnPassant m_enPassant;		// The en passant square (if en passant is possible)

		bool m_whiteKingside = true;	// Whether white can castle kingside
		bool m_whiteQueenside = true;	// Whether white can castle queenside
		bool m_blackKingside = true;	// Whether black can castle kingside
		bool m_blackQueenside = true;	// Whether black can castle queenside

		bool m_whiteToPlay = true;	// Whether it is white's turn to play

		unsigned char m_halfMoves = 0;	// Not really used
		unsigned char m_fullMoves = 0;	// Not really used
	};
}

