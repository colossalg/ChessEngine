#include "AsciiUI.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "Helper.h"
#include "Piece.h"

namespace ChessEngine
{
	std::string AsciiUI::GetAscii()
	{
		std::stringstream ss;

		// The metadata for the game (whose turn, castling rights, en passant, etc.)
		ss << "    ";
		ss << (m_whiteToPlay ? 'W' : 'B');
		ss << "    ";
		ss << (m_whiteKingside ? 'k' : ' ');
		ss << (m_whiteQueenside ? 'q' : ' ');
		ss << (m_blackKingside ? 'K' : ' ');
		ss << (m_blackQueenside ? 'Q' : ' ');
		ss << "    ";
		ss << (m_enPassant ? std::to_string(*m_enPassant) : "-");
		ss << std::endl;
		
		// The actual board (squares, pieces, rows/columns labels, etc.)
		ss << "   +---+---+---+---+---+---+---+---+  " << std::endl;
		for (unsigned int row = 7; Helper::IsValidRow(row); row--)
		{
			ss << " " << row + 1 << " |";
			for (unsigned int col = 0; Helper::IsValidCol(col); col++)
			{
				Square square = Helper::SquareFromRowAndCol(row, col);
				Piece piece = m_pieces[square];

				char squChar = (Helper::IsSquareWhite(square) ? ' ' : ':');
				char pceChar = piece.GetAscii();

				if (piece.IsEmpty())
				{
					// Empty square eg. "   " or ":::"
					ss << squChar << squChar << squChar;
				}
				else
				{
					// Piece square eg. " p " or ":p:"
					ss << squChar << pceChar << squChar;
				}
				ss <<  "|";
			}
			ss << std::endl;
			ss << "   +---+---+---+---+---+---+---+---+  " << std::endl;
		}
		ss << "     a   b   c   d   e   f   g   h    " << std::endl;

		return ss.str();
	}

	void AsciiUI::SetCastling(bool whiteKingside, bool whiteQueenside, bool blackKingside, bool blackQueenside)
	{
		m_whiteKingside = whiteKingside;
		m_whiteQueenside = whiteQueenside;
		m_blackKingside = blackKingside;
		m_blackQueenside = blackQueenside;
	}
}