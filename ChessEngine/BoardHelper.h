#pragma once

#include "Definitions.h"

namespace ChessEngine
{
	namespace BoardHelper
	{
		inline Square SquareFromRowAndCol(Row r, Col c) { return r * 8 + c; }
		inline Row RowFromSquare(Square s) { return s / 8; }
		inline Col ColFromSquare(Square s) { return s % 8; }

		inline bool IsValidRow(Row r) { return r < 8; }
		inline bool IsValidCol(Col c) { return c < 8; }
		inline bool IsValidSquare(Square s) { return s < 64; }

		inline bool IsSquareWhite(Row r, Col c) { return (r % 2 == 0 ? c % 2 == 1 : c % 2 == 0); }
		inline bool IsSquareWhite(Square s) { return IsSquareWhite(RowFromSquare(s), ColFromSquare(s)); }
	}
}
