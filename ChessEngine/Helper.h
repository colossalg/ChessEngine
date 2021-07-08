#pragma once

#include "Definitions.h"

namespace ChessEngine
{
	namespace Helper
	{
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
