#pragma once

#include <array>
#include <list>
#include <optional>

#include "Piece.h"

namespace ChessEngine
{
	using Row = unsigned char;
	using Col = unsigned char;
	using Square = unsigned char;

	using PieceArray = std::array<Piece, 64>;
	using PieceList = std::list<std::pair<Piece, Square>>;

	using EnPassant = std::optional<Square>;
}