#pragma once

#include <array>
#include <tuple>

namespace ChessEngine
{
	using Row = unsigned char;
	using Col = unsigned char;
	using Square = unsigned char;

	using Piece = unsigned char;

	using Castling = std::array<bool, 4>;
	using EnPassan = std::tuple<bool, Row, Col>;
}