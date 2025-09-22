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

    // TODO - Consider removing these, they obfuscate the code somewhat with no real benefit.
    // A signed type is probably better to. It will allow safer application of offsets and
    // not require casting so much.
    using Row = unsigned char;
    using Col = unsigned char;
    using Square = unsigned char;

    using PieceArray = std::array<Piece, 64>;

    // TODO - Consider removing this, it obfuscates the code somewhat with no real benefit.
    using MoveList = std::list<Move>;

    // TODO - Consider removing this, it obfuscates the code somewhat with no real benefit.
    using EnPassant = std::optional<Square>;
}