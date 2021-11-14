#include "pch.h"

#include "BoardHasher.h"

#include <cstdlib>
#include <map>

#include "Board.h"
#include "Helper.h"
#include "Move.h"
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

	std::array<unsigned int, 8> EnPassantRandNums;

	bool AreRandomNumbersInitialized = false;
}

namespace ChessEngine
{
	template<unsigned int N>
	std::array<unsigned int, N> CreateRandomNumberArray()
	{
		std::array<unsigned int, N> randomNumberArray;

		for (auto& number : randomNumberArray)
		{
			number = static_cast<unsigned int>(rand());
		}

		return randomNumberArray;
	}

	void BoardHasher::InitializeRandomNumbers(unsigned int seed)
	{
		srand(seed);

		for (const auto& type : Piece::AllTypes)
		{
			if (type == Piece::Type::Empty)
			{
				WhitePieceRandNums[type] = std::move(std::array<unsigned int, 64>());
			}

			WhitePieceRandNums[type] = CreateRandomNumberArray<64>();
			BlackPieceRandNums[type] = CreateRandomNumberArray<64>();
		}

		unsigned int WhiteToMoveRandNum = static_cast<unsigned int>(rand());
		unsigned int WhiteKingsideCastlingRandNum = static_cast<unsigned int>(rand());
		unsigned int WhiteQueensideCastlingRandNum = static_cast<unsigned int>(rand());
		unsigned int BlackKingsideCastlingRandNum = static_cast<unsigned int>(rand());
		unsigned int BlackQueensideCastlingRandNum = static_cast<unsigned int>(rand());

		std::array<unsigned int, 8> EnPassantRandNums = CreateRandomNumberArray<8>();
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
			Row enPassantRow = Helper::RowFromSquare(board.GetEnPassant().value());
			hash ^= EnPassantRandNums[enPassantRow];
		}

		return hash;
	}

	unsigned int BoardHasher::InsertPiece(unsigned int hash, const Square square, const Piece piece)
	{
		auto& pieceRandNums = (piece.IsWhite() ? WhitePieceRandNums : BlackPieceRandNums)[piece.GetType()];
		hash ^= pieceRandNums[square];

		return hash;
	}

	unsigned int BoardHasher::RemovePiece(unsigned int hash, const Square square, const Piece piece)
	{
		// As XOR is its own inverse, by inserting the piece at the same
		// position again it will have the same effect as removing it
		return InsertPiece(hash, square, piece);
	}

	unsigned int BoardHasher::UpdateEnPassant(unsigned int hash, const EnPassant& oldEnPassant, const EnPassant& newEnPassant)
	{
		if (oldEnPassant.has_value())
		{
			hash ^= EnPassantRandNums[Helper::ColFromSquare(oldEnPassant.value())];
		}

		if (newEnPassant.has_value())
		{
			hash ^= EnPassantRandNums[Helper::ColFromSquare(newEnPassant.value())];
		}

		return hash;
	}

	unsigned int BoardHasher::UpdateWhiteCastleKingside(unsigned int hash)
	{
		return (hash ^ WhiteKingsideCastlingRandNum);
	}

	unsigned int BoardHasher::UpdateWhiteCastleQueenside(unsigned int hash)
	{
		return (hash ^ WhiteQueensideCastlingRandNum);
	}

	unsigned int BoardHasher::UpdateBlackCastleKingside(unsigned int hash)
	{
		return (hash ^ BlackKingsideCastlingRandNum);
	}

	unsigned int BoardHasher::UpdateBlackCastleQueenside(unsigned int hash)
	{
		return (hash ^ BlackQueensideCastlingRandNum);
	}
}
