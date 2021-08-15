#include "pch.h"

#include "Piece.h"

namespace ChessEngine
{
	Piece::Piece(const Type type, const bool isWhite)
	{
		m_piece = static_cast<int>(type);

		if (isWhite)
		{
			m_piece |= IsWhiteBitMap;
		}
	}

	Piece::Piece(const char ascii)
	{
		switch (ascii)
		{
		case 'P':
		case 'p':
			m_piece = static_cast<unsigned char>(Type::Pawn);
			break;
		case 'N':
		case 'n':
			m_piece = static_cast<unsigned char>(Type::Knight);
			break;
		case 'B':
		case 'b':
			m_piece = static_cast<unsigned char>(Type::Bishop);
			break;
		case 'R':
		case 'r':
			m_piece = static_cast<unsigned char>(Type::Rook);
			break;
		case 'Q':
		case 'q':
			m_piece = static_cast<unsigned char>(Type::Queen);
			break;
		case 'K':
		case 'k':
			m_piece = static_cast<unsigned char>(Type::King);
			break;
		default:
			std::string error = "Invalid ascii " + std::to_string(ascii) + ".";
			throw std::invalid_argument(error);
		}

		if (std::isupper(ascii))
		{
			m_piece |= IsWhiteBitMap;
		}
	}

	char Piece::GetAscii() const
	{
		if (IsEmpty())
		{
			return (IsWhite() ? ' ' : ':');
		}
		else if (IsPawn())
		{
			return (IsWhite() ? 'P' : 'p');
		}
		else if (IsKnight())
		{
			return (IsWhite() ? 'N' : 'n');
		}
		else if (IsBishop())
		{
			return (IsWhite() ? 'B' : 'b');
		}
		else if (IsRook())
		{
			return (IsWhite() ? 'R' : 'r');
		}
		else if (IsQueen())
		{
			return (IsWhite() ? 'Q' : 'q');
		}
		else if (IsKing())
		{
			return (IsWhite() ? 'K' : 'k');
		}
		else
		{
			std::string error = "Invalid Piece " + std::to_string(m_piece) + ".";
			throw std::invalid_argument(error);
		}
	}
}