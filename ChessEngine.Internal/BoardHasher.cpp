#include "pch.h"

#include "BoardHasher.h"

#include <array>
#include <cstdlib>
#include <map>

#include "Board.h"
#include "Definitions.h"
#include "Helper.h"
#include "Piece.h"

namespace
{
	std::map<ChessEngine::Piece::Type, std::array<unsigned int, 64>> WhitePieceRandNums;
	std::map<ChessEngine::Piece::Type, std::array<unsigned int, 64>> BlackPieceRandNums;
	unsigned int WhiteToPlayRandNum;
	unsigned int WhiteKingsideCastlingRandNum;
	unsigned int WhiteQueensideCastlingRandNum;
	unsigned int BlackKingsideCastlingRandNum;
	unsigned int BlackQueensideCastlingRandNum;
	std::array<unsigned int, 8> EnPassanRandNums;
	bool AreRandomNumbersInitialized = false;
}

namespace ChessEngine
{
	template<unsigned int N>
	std::array<unsigned int, N>&& CreateRandomNumberArray()
	{
		std::array<unsigned int, N> randomNumberArray;

		for (auto& number : randomNumberArray)
		{
			number = static_cast<unsigned int>(rand());
		}

		return std::move(randomNumberArray);
	}

	void BoardHasher::InitializeRandomNumbers(unsigned int seed)
	{
		srand(seed);

		for (const auto& type : Piece::AllTypes)
		{
			if (type == Piece::Type::Empty)
			{
				continue;
			}

			WhitePieceRandNums[type] = CreateRandomNumberArray<64>();
			BlackPieceRandNums[type] = CreateRandomNumberArray<64>();
		}

		unsigned int WhiteToMoveRandNum = static_cast<unsigned int>(rand());
		unsigned int WhiteKingsideCastlingRandNum = static_cast<unsigned int>(rand());
		unsigned int WhiteQueensideCastlingRandNum = static_cast<unsigned int>(rand());
		unsigned int BlackKingsideCastlingRandNum = static_cast<unsigned int>(rand());
		unsigned int BlackQueensideCastlingRandNum = static_cast<unsigned int>(rand());

		std::array<unsigned int, 8> EnPassanRandNums = CreateRandomNumberArray<8>();
	}

	unsigned int BoardHasher::Hash(const Board& board)
	{
		if (!AreRandomNumbersInitialized)
		{
			InitializeRandomNumbers();
		}

		unsigned int hash = 0;

		const PieceArray& pieces = board.GetPieces();
		for (Square square = 0; Helper::IsValidSquare(square); square++)
		{
			Piece piece = pieces[square];

			if (piece.IsWhite())
			{
				hash ^= WhitePieceRandNums[piece.GetType()][square];
			}
			else
			{
				hash ^= BlackPieceRandNums[piece.GetType()][square];
			}
		}

		if (board.GetWhiteToPlay())
		{
			hash ^= WhiteToPlayRandNum;
		}

		if (board.GetEnPassant().has_value())
		{
			Row enPassanRow = Helper::RowFromSquare(board.GetEnPassant().value());
			hash ^= EnPassanRandNums[enPassanRow];
		}

		return hash;
	}
}
