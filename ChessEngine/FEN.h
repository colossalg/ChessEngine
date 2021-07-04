#pragma once

#include <string>

#include "IPortableNotation.h"

namespace ChessEngine
{
	class FEN : public IPortableNotation
	{
	public:
		FEN(const std::string& str);

		Piece PieceAt(Square square) const override;
		Piece PieceAt(Row row, Col col) const override;

		bool CanCastle(bool isWhite, bool kingside) const override;
	};
}