#pragma once

#include <array>
#include <string>

#include "Definitions.h"

namespace ChessEngine
{
    class AsciiUI
    {
    public:

        // Get an ascii representation of the board
        static std::string GetAscii(const Board& board);
    };
}