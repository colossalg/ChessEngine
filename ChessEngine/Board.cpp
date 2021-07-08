#include "Board.h"

#include "Helper.h"

namespace ChessEngine
{
	Board::Board():
		m_pieces(StartingPieces)
	{
		for (Square square = 0; Helper::IsValidSquare(square); square++)
		{
			const Piece& piece = m_pieces[square];

			if (!piece.IsEmpty())
			{
				if (piece.IsWhite())
				{
					m_whitePieceList.push_back(std::make_pair(piece, square));
				}
				else
				{
					m_blackPieceList.push_back(std::make_pair(piece, square));
				}
			}
		}
	}
}