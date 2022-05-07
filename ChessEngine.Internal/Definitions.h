#pragma once

#include <array>
#include <list>
#include <optional>

namespace ChessEngine
{
    class Board;
    class Move;
    class MoveGenerator;
    class MoveInverse;
    class Piece;

    using Row = unsigned char;
    using Col = unsigned char;
    using Square = unsigned char;

    using PieceArray = std::array<Piece, 64>;

    using MoveList = std::list<Move>;

    using EnPassant = std::optional<Square>;
}