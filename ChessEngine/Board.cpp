#include "Board.h"

namespace ChessEngine
{
	using namespace PieceHelper;

	const PieceArray Board::StartingPieces{
		wr, wn, wb, wq, wk, wb, wn, wr,
		wp, wp, wp, wp, wp, wp, wp, wp,
		ee, ee, ee, ee, ee, ee, ee, ee,
		ee, ee, ee, ee, ee, ee, ee, ee,
		ee, ee, ee, ee, ee, ee, ee, ee,
		ee, ee, ee, ee, ee, ee, ee, ee,
		bp, bp, bp, bp, bp, bp, bp, bp,
		br, bn, bb, bq, bk, bb, bn, br
	};
}

namespace ChessEngine
{

}