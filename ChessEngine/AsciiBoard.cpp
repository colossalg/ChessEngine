#include "AsciiBoard.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "BoardHelper.h"
#include "PieceHelper.h"

namespace ChessEngine
{
	std::string AsciiBoard::GetAscii()
	{
		std::stringstream ss;

		ss << "    ";
		ss << (m_whiteToPlay ? 'W' : 'B');
		ss << "    ";
		ss << (m_whiteKingside ? 'k' : ' ');
		ss << (m_blackKingside ? 'K' : ' ');
		ss << (m_whiteQueenside ? 'q' : ' ');
		ss << (m_blackQueenside ? 'Q' : ' ');
		ss << "    ";
		ss << (m_enPassantPossible ? std::to_string(m_enPassantSquare) : "-");
		ss << std::endl;
		
		ss << "   +---+---+---+---+---+---+---+---+  " << std::endl;
		for (unsigned int row = 7; BoardHelper::IsValidRow(row); row--)
		{
			ss << " " << row + 1 << " |";
			for (unsigned int col = 0; BoardHelper::IsValidCol(col); col++)
			{
				Square square = BoardHelper::SquareFromRowAndCol(row, col);
				Piece piece = m_pieces[square];

				char squareChar = (BoardHelper::IsSquareWhite(square) ? ' ' : ':');
				char pieceChar = PieceHelper::GetAscii(piece);

				if (PieceHelper::IsEmpty(piece))
				{
					ss << squareChar << squareChar << squareChar;
				}
				else
				{
					ss << squareChar << pieceChar << squareChar;
				}
				ss <<  "|";
			}
			ss << std::endl;
			ss << "   +---+---+---+---+---+---+---+---+  " << std::endl;
		}

		ss << "     a   b   c   d   e   f   g   h    " << std::endl;

		return ss.str();
	}

	void AsciiBoard::SetPieces(std::array<Piece, 64>& pieces)
	{
		m_pieces = pieces;
	}

	void AsciiBoard::SetCastling(bool whiteKingside, bool blackKingside, bool whiteQueenside, bool blackQueenside)
	{
		m_whiteKingside = whiteKingside;
		m_blackKingside = blackKingside;
		m_whiteQueenside = whiteQueenside;
		m_blackQueenside = blackQueenside;
	}

	void AsciiBoard::SetEnPassant(bool possible, Square square)
	{
		m_enPassantPossible = possible;
		m_enPassantSquare = square;
	}
}