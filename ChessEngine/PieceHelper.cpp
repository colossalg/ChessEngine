#include "PieceHelper.h"

#include <map>
#include <stdexcept>

namespace ChessEngine
{
	namespace PieceHelper
	{
		Piece MakePiece(PieceType type, bool isWhite, bool hasMoved)
		{
			Piece p = static_cast<int>(type);

			if (isWhite)
			{
				p |= IsWhiteBitMap;
			}

			if (hasMoved)
			{
				p |= HasMovedBitMap;
			}

			return p;
		}

		const std::string&& GetAscii(Piece p)
		{
			if (IsEmpty(p))
			{
				return " ";
			}
			else if (IsPawn(p))
			{
				return (IsWhite(p) ? "p" : "P");
			}
			else if (IsKnight(p))
			{
				return (IsWhite(p) ? "n" : "n");
			}
			else if (IsBishop(p))
			{
				return (IsWhite(p) ? "b" : "B");
			}
			else if (IsRook(p))
			{
				return (IsWhite(p) ? "r" : "R");
			}
			else if (IsQueen(p))
			{
				return (IsWhite(p) ? "q" : "Q");
			}
			else if (IsKing(p))
			{
				return (IsWhite(p) ? "k" : "K");
			}
			else
			{
				std::string error = "Invalid piece " + std::to_string(p) + ".";
				throw std::invalid_argument(error);
			}
		}
	}
}