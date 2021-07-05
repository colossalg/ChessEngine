#pragma once

#include <array>
#include <optional>

namespace ChessEngine
{
	using Row = unsigned char;
	using Col = unsigned char;
	using Square = unsigned char;

	using Piece = unsigned char;
	using PieceArray = std::array<Piece, 64>;

	using EnPassant = std::optional<Square>;
}