#pragma once

#include <string>

#include "IPortableNotation.h"

namespace ChessEngine
{
	class PGN : public IPortableNotation
	{
	public:
		PGN(const std::string& str);

		Piece PieceAt(Square square) const override;
		Piece PieceAt(Row row, Col col) const override;

		bool CanCastle(bool isWhite, bool kingside) const override;
	};
}