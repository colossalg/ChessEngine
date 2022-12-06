#pragma once

#include "Definitions.h"

namespace ChessEngine
{
    namespace Helper
    {
        // Get the index of a square given the row and col: (0 to 63)
        inline Square SquareFromRowAndCol(const Row r, const Col c) { return r * 8 + c; }

        // Get the row of a square given the index: (0 to 7)
        inline Row RowFromSquare(const Square s) { return s / 8; }

        // Get the col of a square given the index: (0 to 7)
        inline Col ColFromSquare(const Square s) { return s % 8; }

        // Get whether a row of a square is valid
        inline bool IsValidRow(const Row r) { return r < 8; }

        // Get whether a col of a square is valid
        inline bool IsValidCol(const Col c) { return c < 8; }

        // Get whether an index of a square is valid
        inline bool IsValidSquare(const Square s) { return s < 64; }

        // Get whether a square is white given the row and col of the square
        inline bool IsSquareWhite(const Row r, const Col c) { return (r % 2 == 0 ? c % 2 == 1 : c % 2 == 0); }

        // Get whether a square is white given the index of the square
        inline bool IsSquareWhite(const Square s) { return IsSquareWhite(RowFromSquare(s), ColFromSquare(s)); }

        // Get the square from a string (ex. h8 -> 63)
        Square SquareFromString(const std::string& s);

        // Get the string from a square (ex. 63 -> h8)
        std::string StringFromSquare(const Square s);

        // Convert a std::string to a std::wstring
        std::wstring StringToWString(const std::string& s);

        // Create an array with all zero entries
        template<unsigned int N> std::array<unsigned int, N> CreateZeroArray()
        {
            std::array<unsigned int, N> arr;

            for (auto& number : arr)
                number = 0U;

            return arr;
        }

        // Create an array with random entries
        template<unsigned int N> std::array<unsigned int, N> CreateRandomArray()
        {
            std::array<unsigned int, N> arr;

            for (auto& number : arr)
                number = static_cast<unsigned int>(rand());

            return arr;
        }
    }
}
