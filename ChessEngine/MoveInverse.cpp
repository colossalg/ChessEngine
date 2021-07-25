#include "MoveInverse.h"

namespace ChessEngine
{
	MoveInverse::MoveInverse(const Board& board, Move move) :
		m_move(move),
		m_enPassant(board.GetEnPassant()),
		m_whiteKingside(board.GetWhiteCanCastleKingside()),
		m_whiteQueenside(board.GetWhiteCanCastleQueenside()),
		m_blackKingside(board.GetBlackCanCastleKingside()),
		m_blackQueenside(board.GetBlackCanCastleQueenside()),
		m_halfMoves(board.GetHalfMoves()),
		m_capturedPiece(Piece::ee)
	{
		if (move.IsEnPassantCapture())
		{
			m_capturedPiece = (board.GetWhiteToPlay() ? Piece::bp : Piece::wp);
		}
		else if (move.IsCapture())
		{
			const PieceArray& pieces = board.GetPieces();

			m_capturedPiece = pieces[move.GetDestSquare()];
		}
	}
}