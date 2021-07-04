#pragma once

#include "Definitions.h"

namespace ChessEngine
{
	namespace BoardHelper
	{
		inline bool IsValidRow(Row r) { return r < 8; }
		inline bool IsValidCol(Col c) { return c < 8; }
		inline bool IsValidSquare(Square s) { return s < 64;  }

		inline Row RowFromSquare(Square s) { return s / 8; }
		inline Col ColFromSquare(Square s) { return s % 8; }
		inline Square SquareFromRowAndCol(Row r, Col c) { return r * 8 + c; }
	}
}
