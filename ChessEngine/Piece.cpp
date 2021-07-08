#include "Piece.h"

#include <stdexcept>
#include <string>

namespace ChessEngine
{
	Piece::Piece(Type type, bool isWhite, bool hasMoved)
	{
		m_piece = static_cast<int>(type);

		if (isWhite)
		{
			m_piece |= IsWhiteBitMap;
		}

		if (hasMoved)
		{
			m_piece |= HasMovedBitMap;
		}
	}

	char Piece::GetAscii() const
	{
		if (IsEmpty())
		{
			return ' ';
		}
		else if (IsPawn())
		{
			return (IsWhite() ? 'p' : 'P');
		}
		else if (IsKnight())
		{
			return (IsWhite() ? 'n' : 'N');
		}
		else if (IsBishop())
		{
			return (IsWhite() ? 'b' : 'B');
		}
		else if (IsRook())
		{
			return (IsWhite() ? 'r' : 'R');
		}
		else if (IsQueen())
		{
			return (IsWhite() ? 'q' : 'Q');
		}
		else if (IsKing())
		{
			return (IsWhite() ? 'k' : 'K');
		}
		else
		{
			std::string error = "Invalid Piece " + std::to_string(m_piece) + ".";
			throw std::invalid_argument(error);
		}
	}
}