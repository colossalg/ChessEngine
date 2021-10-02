#include "pch.h"

#include "AsciiUI.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "Board.h"
#include "Helper.h"
#include "Piece.h"

namespace ChessEngine
{
	std::string AsciiUI::GetAscii(const Board& board)
	{
		std::stringstream ss;

		// The metadata for the game (whose turn, castling rights, en passant, etc.)
		ss << "    ";
		ss << (board.GetWhiteToPlay() ? 'W' : 'B');
		ss << "    ";
		ss << (board.CanWhiteCastleKingside() ? 'K' : ' ');
		ss << (board.CanWhiteCastleQueenside() ? 'Q' : ' ');
		ss << (board.CanBlackCastleKingside() ? 'k' : ' ');
		ss << (board.CanBlackCastleQueenside() ? 'q' : ' ');
		ss << "    ";
		ss << (board.GetEnPassant() ? std::to_string(*(board.GetEnPassant())) : "-");
		ss << std::endl;
		
		// The actual board (squares, pieces, rows/columns labels, etc.)
		ss << "   +---+---+---+---+---+---+---+---+  " << std::endl;
		for (unsigned int row = 7; Helper::IsValidRow(row); row--)
		{
			ss << " " << row + 1 << " |";
			for (unsigned int col = 0; Helper::IsValidCol(col); col++)
			{
				Square square = Helper::SquareFromRowAndCol(row, col);
				Piece piece = board.GetPieces()[square];

				char squChar = (Helper::IsSquareWhite(square) ? ' ' : ':');
				char pceChar = piece.GetAscii();

				if (piece.IsEmpty())
				{
					// Empty square eg. "   " or ":::"
					ss << squChar << squChar << squChar;
				}
				else
				{
					// Piece square eg. " P " or ":P:"
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
}