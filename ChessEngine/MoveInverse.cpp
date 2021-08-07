#include "MoveInverse.h"

#include "Board.h"

namespace ChessEngine
{
	MoveInverse::MoveInverse(const Board& board, const Move move) :
		m_move(move),
		m_enPassant(board.m_enPassant),
		m_whiteKingside(board.m_whiteKingside),
		m_whiteQueenside(board.m_whiteQueenside),
		m_blackKingside(board.m_blackKingside),
		m_blackQueenside(board.m_blackQueenside),
		m_halfMoves(board.m_halfMoves),
		m_capturedPiece(Piece::ee)
	{
		if (move.IsEnPassantCapture())
		{
			m_capturedPiece = (board.m_whiteToPlay ? Piece::bp : Piece::wp);
		}
		else if (move.IsCapture())
		{
			m_capturedPiece = board.m_pieces[move.GetDestSquare()];
		}
	}
}