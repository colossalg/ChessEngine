#pragma once

#include <string>

#include "Definitions.h"

namespace ChessEngine
{
	namespace PieceHelper
	{
		namespace
		{
			const unsigned char IsEmptyBitMap = 0b11111100;
			const unsigned char IsWhiteBitMap = 0b00000001;
			const unsigned char HasMovedBitMap = 0b00000010;
		}

		enum class PieceType
		{
			Empty = 0b00000000,
			Pawn = 0b00000100,
			Knight = 0b00001000,
			Bishop = 0b00010000,
			Rook = 0b00100000,
			Queen = 0b01000000,
			King = 0b10000000
		};

		// Create a new piece with the given properties (type, whether it is white, whether it has moved)
		Piece MakePiece(PieceType type, bool isWhite, bool hasMoved = false);

		// Get the ascii representation of the piece
		char GetAscii(Piece p);

		// Get whether the piece is an empty square
		inline bool IsEmpty(Piece p) { return ((IsEmptyBitMap & p) == 0); }

		// Get whether the piece is a pawn
		inline bool IsPawn(Piece p) { return ((static_cast<int>(PieceType::Pawn) & p) != 0); }

		// Get whether the piece is a knight
		inline bool IsKnight(Piece p) { return ((static_cast<int>(PieceType::Knight) & p) != 0); }

		// Get whether the piece is a bishop
		inline bool IsBishop(Piece p) { return ((static_cast<int>(PieceType::Bishop) & p) != 0); }

		// Get whether the piece is a rook
		inline bool IsRook(Piece p) { return ((static_cast<int>(PieceType::Rook) & p) != 0); }

		// Get whether the piece is a queen
		inline bool IsQueen(Piece p) { return ((static_cast<int>(PieceType::Queen) & p) != 0); }

		// Get whether the piece is a king
		inline bool IsKing(Piece p) { return ((static_cast<int>(PieceType::King) & p) != 0); }
		
		// Get whether the piece is white
		inline bool IsWhite(Piece p) { return ((p & IsWhiteBitMap) != 0); }

		// Get whether the piece has moved
		inline bool HasMoved(Piece p) { return ((p & HasMovedBitMap) != 0); }

		// Set that the piece has moved
		inline bool SetHasMoved(Piece& p) { p &= (~HasMovedBitMap); }
	}
}