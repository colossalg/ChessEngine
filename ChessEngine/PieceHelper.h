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

		Piece MakePiece(PieceType type, bool isWhite, bool hasMoved = false);

		char GetAscii(Piece p);

		inline bool IsEmpty(Piece p) { return ((IsEmptyBitMap & p) == 0); }
		inline bool IsPawn(Piece p) { return ((static_cast<int>(PieceType::Pawn) & p) != 0); }
		inline bool IsKnight(Piece p) { return ((static_cast<int>(PieceType::Knight) & p) != 0); }
		inline bool IsBishop(Piece p) { return ((static_cast<int>(PieceType::Bishop) & p) != 0); }
		inline bool IsRook(Piece p) { return ((static_cast<int>(PieceType::Rook) & p) != 0); }
		inline bool IsQueen(Piece p) { return ((static_cast<int>(PieceType::Queen) & p) != 0); }
		inline bool IsKing(Piece p) { return ((static_cast<int>(PieceType::King) & p) != 0); }
		
		inline bool IsWhite(Piece p) { return ((p & IsWhiteBitMap) != 0); }

		inline bool HasMoved(Piece p) { return ((p & HasMovedBitMap) != 0); }

		inline bool SetHasMoved(Piece& p, bool moved)
		{
			if (moved)
			{
				p |= HasMovedBitMap;
			}
			else
			{
				p &= (~HasMovedBitMap);
			}
		}
	}
}