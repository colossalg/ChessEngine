#include "FEN.h"

#include <stdexcept>

namespace ChessEngine
{
	FEN::FEN(const std::string& str)
	{
		throw std::logic_error("Method not yet implemented.");
	}

	Piece FEN::PieceAt(Square square) const
	{

	}

	Piece FEN::PieceAt(Row row, Col col) const
	{

	}

	bool FEN::CanCastle(bool isWhite, bool kingside) const
	{

	}
}