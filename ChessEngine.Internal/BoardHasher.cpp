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
	BoardHasher::BoardHasher(const Board& board):
		m_board(board)
	{}

	void BoardHasher::ResetHash()
	{
		InitializeRandomNumbers();

		m_hash = 0;

		const PieceArray& pieces = m_board.GetPieces();
		for (Square square = 0; Helper::IsValidSquare(square); square++)
		{
			Piece piece = pieces[square];

			if (piece.IsWhite())
			{
				m_hash ^= WhitePieceRandNums[piece.GetType()][square];
			}
			else
			{
				m_hash ^= BlackPieceRandNums[piece.GetType()][square];
			}
		}

		if (m_board.GetWhiteToPlay())
		{
			m_hash ^= WhiteToPlayRandNum;
		}

		if (m_board.GetEnPassant().has_value())
		{
			Row enPassantRow = Helper::RowFromSquare(m_board.GetEnPassant().value());
			m_hash ^= EnPassantRandNums[enPassantRow];
		}
	}

	void BoardHasher::UpdatePiece(const Square square, const Piece oldPiece, const Piece newPiece)
	{
		m_hash ^= (oldPiece.IsWhite() ? WhitePieceRandNums : BlackPieceRandNums)[oldPiece.GetType()][square];
		m_hash ^= (newPiece.IsWhite() ? WhitePieceRandNums : BlackPieceRandNums)[newPiece.GetType()][square];
	}

	void BoardHasher::UpdateEnPassant(const EnPassant& oldEnPassant, const EnPassant& newEnPassant)
	{
		if (oldEnPassant.has_value())
		{
			m_hash ^= EnPassantRandNums[Helper::ColFromSquare(oldEnPassant.value())];
		}

		if (newEnPassant.has_value())
		{
			m_hash ^= EnPassantRandNums[Helper::ColFromSquare(newEnPassant.value())];
		}
	}

	void BoardHasher::UpdateCanWhiteCastleKingside(const bool oldCastlingRights, const bool newCastlingRights)
	{
		if (oldCastlingRights != newCastlingRights)
		{
			m_hash ^= WhiteKingsideCastlingRandNum;
		}
	}

	void BoardHasher::UpdateCanWhiteCastleQueenside(const bool oldCastlingRights, const bool newCastlingRights)
	{
		if (oldCastlingRights != newCastlingRights)
		{
			m_hash ^= WhiteQueensideCastlingRandNum;
		}
	}

	void BoardHasher::UpdateCanBlackCastleKingside(const bool oldCastlingRights, const bool newCastlingRights)
	{
		if (oldCastlingRights != newCastlingRights)
		{
			m_hash ^= BlackKingsideCastlingRandNum;
		}
	}

	void BoardHasher::UpdateCanBlackCastleQueenside(const bool oldCastlingRights, const bool newCastlingRights)
	{
		if (oldCastlingRights != newCastlingRights)
		{
			m_hash ^= BlackQueensideCastlingRandNum;
		}
	}

	void BoardHasher::UpdateWhiteToPlay(const bool oldWhiteToPlay, const bool newWhiteToPlay)
	{
		if (oldWhiteToPlay != newWhiteToPlay)
		{
			m_hash ^= WhiteToPlayRandNum;
		}
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
}
