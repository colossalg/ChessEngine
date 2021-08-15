#include "pch.h"

#include "Helper.h"

namespace ChessEngine
{
	namespace Helper
	{
		Square SquareFromString(const std::string& s)
		{
			if (s.size() != 2)
			{
				std::string error = "Invalid string for square (" + s + ").";
				throw std::invalid_argument(error);
			}

			Row row = s[1] - '1';
			Col col = s[0] - 'a';

			if (!Helper::IsValidRow(row) || !Helper::IsValidCol(col))
			{
				std::string error = "Invalid row or col in string (" + s + ").";
				throw std::invalid_argument(error);
			}
			else
			{
				return SquareFromRowAndCol(row, col);
			}
		}

		std::string StringFromSquare(const Square s)
		{
			char row = static_cast<char>(RowFromSquare(s) + '1');
			char col = static_cast<char>(ColFromSquare(s) + 'a');

			std::ostringstream ss;
			ss << col << row;

			return ss.str();
		}

		std::wstring StringToWString(const std::string& s)
		{
			return std::wstring(s.begin(), s.end());
		}
	}
}