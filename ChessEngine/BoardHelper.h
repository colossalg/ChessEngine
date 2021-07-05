#pragma once

#include "Definitions.h"
#include "PieceHelper.h"

namespace ChessEngine
{
	namespace BoardHelper
	{
		namespace
		{
			const Piece ee = MakePiece(PieceHelper::PieceType::Empty, true);
			const Piece wp = MakePiece(PieceHelper::PieceType::Pawn, true);
			const Piece bp = MakePiece(PieceHelper::PieceType::Pawn, false);
			const Piece wn = MakePiece(PieceHelper::PieceType::Knight, true);
			const Piece bn = MakePiece(PieceHelper::PieceType::Knight, false);
			const Piece wb = MakePiece(PieceHelper::PieceType::Bishop, true);
			const Piece bb = MakePiece(PieceHelper::PieceType::Bishop, false);
			const Piece wr = MakePiece(PieceHelper::PieceType::Rook, true);
			const Piece br = MakePiece(PieceHelper::PieceType::Rook, false);
			const Piece wq = MakePiece(PieceHelper::PieceType::Queen, true);
			const Piece bq = MakePiece(PieceHelper::PieceType::Queen, false);
			const Piece wk = MakePiece(PieceHelper::PieceType::King, true);
			const Piece bk = MakePiece(PieceHelper::PieceType::King, false);

			std::array<Piece, 64> StartingBoard{
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

		// Get the index of a square given the row and col: (0 to 63)
		inline Square SquareFromRowAndCol(Row r, Col c) { return r * 8 + c; }

		// Get the row of a square given the index: (0 to 7)
		inline Row RowFromSquare(Square s) { return s / 8; }

		// Get the col of a square given the index: (0 to 7)
		inline Col ColFromSquare(Square s) { return s % 8; }

		// Get whether a row of a square is valid
		inline bool IsValidRow(Row r) { return r < 8; }

		// Get whether a col of a square is valid
		inline bool IsValidCol(Col c) { return c < 8; }

		// Get whether an index of a square is valid
		inline bool IsValidSquare(Square s) { return s < 64; }

		// Get whether a square is white given the row and col of the square
		inline bool IsSquareWhite(Row r, Col c) { return (r % 2 == 0 ? c % 2 == 1 : c % 2 == 0); }

		// Get whether a square is white given the index of the square
		inline bool IsSquareWhite(Square s) { return IsSquareWhite(RowFromSquare(s), ColFromSquare(s)); }
	}
}
