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
	std::array<unsigned int, N> CreateZeroArray()
	{
		std::array<unsigned int, N> zeroArray;

		for (auto& number : zeroArray)
		{
			number = 0U;
		}

		return zeroArray;
	}

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
		// Prevent initializing the random numbers more than once
		if (AreRandomNumbersInitialized)
		{
			return;
		}

		srand(seed);

		for (const auto& type : Piece::AllTypes)
		{
			if (type == Piece::Type::Empty)
			{
				WhitePieceRandNums[type] = CreateZeroArray<64>();
				BlackPieceRandNums[type] = CreateZeroArray<64>();
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

		// Prevent initializing the random numbers more than once
		AreRandomNumbersInitialized = true;
	}

	unsigned int BoardHasher::Hash(const Board& board)
	{
		InitializeRandomNumbers();

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

	unsigned int BoardHasher::UpdatePiece(unsigned int hash, const Square square, const Piece oldPiece, const Piece newPiece)
	{
		hash ^= (oldPiece.IsWhite() ? WhitePieceRandNums : BlackPieceRandNums)[oldPiece.GetType()][square];
		hash ^= (newPiece.IsWhite() ? WhitePieceRandNums : BlackPieceRandNums)[newPiece.GetType()][square];

		return hash;
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

	unsigned int BoardHasher::UpdateCanWhiteCastleKingside(unsigned int hash, const bool oldCastlingRights, const bool newCastlingRights)
	{
		if (oldCastlingRights != newCastlingRights)
		{
			hash ^= WhiteKingsideCastlingRandNum;
		}

		return hash;
	}

	unsigned int BoardHasher::UpdateCanWhiteCastleQueenside(unsigned int hash, const bool oldCastlingRights, const bool newCastlingRights)
	{
		if (oldCastlingRights != newCastlingRights)
		{
			hash ^= WhiteQueensideCastlingRandNum;
		}

		return hash;
	}

	unsigned int BoardHasher::UpdateCanBlackCastleKingside(unsigned int hash, const bool oldCastlingRights, const bool newCastlingRights)
	{
		if (oldCastlingRights != newCastlingRights)
		{
			hash ^= BlackKingsideCastlingRandNum;
		}

		return hash;
	}

	unsigned int BoardHasher::UpdateCanBlackCastleQueenside(unsigned int hash, const bool oldCastlingRights, const bool newCastlingRights)
	{
		if (oldCastlingRights != newCastlingRights)
		{
			hash ^= BlackQueensideCastlingRandNum;
		}

		return hash;
	}

	unsigned int BoardHasher::UpdateWhiteToPlay(unsigned int hash, const bool oldWhiteToPlay, const bool newWhiteToPlay)
	{
		if (oldWhiteToPlay != newWhiteToPlay)
		{
			hash ^= WhiteToPlayRandNum;
		}

		return hash;
	}
}
