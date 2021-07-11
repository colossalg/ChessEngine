#pragma once

#include <string>

#include "Definitions.h"
#include "Helper.h"
#include "Move.h"
#include "Piece.h"

namespace ChessEngine
{
	class MoveGenerator; // Forward declaration

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

	private:
		// Helper function which resets the piece lists based upon the piece array
		void ResetPieceLists();

		// Helper function which updates the piece array and lists by moving a piece from 'init' to 'dest'
		void MovePiece(Square init, Square dest);

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

