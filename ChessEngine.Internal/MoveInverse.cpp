#include "pch.h"

#include "MoveInverse.h"

#include "Board.h"

namespace ChessEngine
{
	MoveInverse::MoveInverse(const Board& board, const Move move) :
		m_move(move),
		m_enPassant(board.GetEnPassant()),
		m_whiteKingside(board.CanWhiteCastleKingside()),
		m_whiteQueenside(board.CanWhiteCastleQueenside()),
		m_blackKingside(board.CanBlackCastleKingside()),
		m_blackQueenside(board.CanBlackCastleQueenside()),
		m_halfMoves(board.GetHalfMoves()),
		m_capturedPiece(Piece::ee)
	{
		if (move.IsEnPassantCapture())
		{
			m_capturedPiece = (board.GetWhiteToPlay() ? Piece::bp : Piece::wp);
		}
		else if (move.IsCapture())
		{
			m_capturedPiece = board.GetPieces()[move.GetDestSquare()];
		}
	}
}