#pragma once

#include "Definitions.h"

namespace ChessEngine
{
	class IPortableNotation
	{
	public:
		~IPortableNotation() = default;

		virtual Piece PieceAt(Square square) const = 0;
		virtual Piece PieceAt(Row row, Col col) const = 0;

		virtual bool CanCastle(bool isWhite, bool kingside) const = 0;
	};
}