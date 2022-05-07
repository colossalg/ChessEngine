#pragma once

/**************************************************************************************
* Acknowledgement:                                                                    *
*                                                                                     *
* I would like to acknowledge Tom Kerrigan. I have essentially copied the evaluation  *
* from his chess engine "Tom's Simple Chess Program" (TSCP). I hope to create my own  *
* evaluation function at some point, however, in the interest of progressing this     *
* project as fast as possible, I have used his for now.                               *
*                                                                                     *
* TSCP is a very nice engine for it's simplicity. It is only ~2000 lines of C code.   *
* I strongly advise anyone intending to build their own engine to give the source a   *
* look. It can be found at Tom's website here: http://www.tckerrigan.com/Chess/TSCP/  *
**************************************************************************************/

#include "Definitions.h"

namespace ChessEngine
{
    class BoardEvaluator
    {
    public:

        // Evaluate a board position from the perspective of the player to move
        int Evaluate(const Board& board);

    private:

        // Evaluate a white/black pawn for bonuses/penalties beyond its base value
        inline int EvaluateWhitePawn(const Board& board, const Square square);
        inline int EvaluateBlackPawn(const Board& board, const Square square);

        // Evaluate a white/black rook for bonuses/penalties beyond its base value
        inline int EvaluateWhiteRook(const Board& board, const Square square);
        inline int EvaluateBlackRook(const Board& board, const Square square);

        // Evaluate a white/black king for bonuses/penalties beyond its base value
        inline int EvaluateWhiteKing(const Board& board, const Square square);
        inline int EvaluateBlackKing(const Board& board, const Square square);

        // Evaluate the king cover for white/black on a given file
        inline int EvaluateWhiteKingCover(const Col col);
        inline int EvaluateBlackKingCover(const Col col);

        // Reset all member variables to their default values
        inline void Reset();

        int m_whitePawnValues = 0;  // The value of the white pawns
        int m_blackPawnValues = 0;  // The value of the black pawns

        // NOTE: These are padded with additional values to help make the logic easier
        int m_whiteForemostPawns[10] = { 0 };   // The foremost pawns for white
        int m_blackForemostPawns[10] = { 7 };   // The foremost pawns for black

        int m_whitePieceValues = 0; // The value of the white pieces
        int m_blackPieceValues = 0; // The value of the black pieces

        int m_whiteScore = 0;   // The total score for the white pieces/pawns
        int m_blackScore = 0;   // The total score for the black pieces/pawns
    };
}