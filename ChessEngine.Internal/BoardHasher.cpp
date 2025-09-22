#include "pch.h"

#include "BoardHasher.h"

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
    void BoardHasher::SetHash(const Board& board)
    {
        InitializeRandomNumbers();

        m_hash = 0;

        const PieceArray& pieces = board.GetPieces();
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

        if (board.GetEnPassant().has_value())
        {
            Row enPassantRow = Helper::RowFromSquare(board.GetEnPassant().value());
            m_hash ^= EnPassantRandNums[enPassantRow];
        }

        if (board.CanWhiteCastleKingside())
        {
            m_hash ^= WhiteKingsideCastlingRandNum;
        }
        if (board.CanWhiteCastleQueenside())
        {
            m_hash ^= WhiteQueensideCastlingRandNum;
        }
        if (board.CanBlackCastleKingside())
        {
            m_hash ^= BlackKingsideCastlingRandNum;
        }
        if (board.CanBlackCastleQueenside())
        {
            m_hash ^= BlackQueensideCastlingRandNum;
        }

        if (board.GetWhiteToPlay())
        {
            m_hash ^= WhiteToPlayRandNum;
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
                WhitePieceRandNums[type] = Helper::CreateZeroArray<64>();
                BlackPieceRandNums[type] = Helper::CreateZeroArray<64>();
            }

            WhitePieceRandNums[type] = Helper::CreateRandomArray<64>();
            BlackPieceRandNums[type] = Helper::CreateRandomArray<64>();
        }

        // TODO - This is currently broken, rand() only returns an integer value
        // in the range [0, 2^16) which will result in an incredible number of
        // collisions when each board state is hashed into this range.
        // The hashes should probably be 64-bit, apparently this is the standard.
        WhiteToPlayRandNum = static_cast<unsigned int>(rand());
        WhiteKingsideCastlingRandNum = static_cast<unsigned int>(rand());
        WhiteQueensideCastlingRandNum = static_cast<unsigned int>(rand());
        BlackKingsideCastlingRandNum = static_cast<unsigned int>(rand());
        BlackQueensideCastlingRandNum = static_cast<unsigned int>(rand());

        EnPassantRandNums = Helper::CreateRandomArray<8>();

        // Prevent initializing the random numbers more than once
        AreRandomNumbersInitialized = true;
    }
}
