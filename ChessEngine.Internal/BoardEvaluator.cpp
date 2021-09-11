#include "pch.h"

#include "BoardEvaluator.h"

#include "Board.h"
#include "Helper.h"
#include "Piece.h"

namespace ChessEngine
{
	namespace
	{
		constexpr int PawnValue	  = 100;	// The base value of a pawn
		constexpr int KnightValue = 300;	// The base value of a knight
		constexpr int BishopValue = 325;	// The base value of a bishop
		constexpr int RookValue	  = 500;	// The base value of a rook
		constexpr int QueenValue  = 900;	// The base value of a queen
		constexpr int KingValue   = 10000;	// The base value of a king 

		constexpr int MaxMaterialValue =
			8 * PawnValue +
			2 * KnightValue +
			2 * BishopValue +
			2 * RookValue +
			1 * QueenValue;

		// An array of modifiers for pawn values based upon the pawn's position
		constexpr int PawnPositionModifiers[64] = {
			0,   0,   0,   0,   0,   0,   0,   0,
			5,  10,  15,  20,  20,  15,  10,   5,
			4,   8,  12,  16,  16,  12,   8,   4,
			3,   6,   9,  12,  12,   9,   6,   3,
			2,   4,   6,   8,   8,   6,   4,   2,
			1,   2,   3, -10, -10,   3,   2,   1,
			0,   0,   0, -40, -40,   0,   0,   0,
			0,   0,   0,   0,   0,   0,   0,   0
		};

		// An array of modifiers for knight values based upon the knight's position
		constexpr int KnightPositionModifiers[64] = {
			-10, -10, -10, -10, -10, -10, -10, -10,
			-10,   0,   0,   0,   0,   0,   0, -10,
			-10,   0,   5,   5,   5,   5,   0, -10,
			-10,   0,   5,  10,  10,   5,   0, -10,
			-10,   0,   5,  10,  10,   5,   0, -10,
			-10,   0,   5,   5,   5,   5,   0, -10,
			-10,   0,   0,   0,   0,   0,   0, -10,
			-10, -30, -10, -10, -10, -10, -30, -10
		};

		// An array of modifiers for bishop values based upon the bishop's position
		constexpr int BishopPositionModifiers[64] = {
			-10, -10, -10, -10, -10, -10, -10, -10,
			-10,   0,   0,   0,   0,   0,   0, -10,
			-10,   0,   5,   5,   5,   5,   0, -10,
			-10,   0,   5,  10,  10,   5,   0, -10,
			-10,   0,   5,  10,  10,   5,   0, -10,
			-10,   0,   5,   5,   5,   5,   0, -10,
			-10,   0,   0,   0,   0,   0,   0, -10,
			-10, -10, -20, -10, -10, -20, -10, -10
		};

		// An array of modifiers for king values based upon the king's position (in the opening/middle game)
		constexpr int KingPositionModifiers[64] = {
			-40, -40, -40, -40, -40, -40, -40, -40,
			-40, -40, -40, -40, -40, -40, -40, -40,
			-40, -40, -40, -40, -40, -40, -40, -40,
			-40, -40, -40, -40, -40, -40, -40, -40,
			-40, -40, -40, -40, -40, -40, -40, -40,
			-40, -40, -40, -40, -40, -40, -40, -40,
			-20, -20, -20, -20, -20, -20, -20, -20,
			  0,  20,  40, -20,   0, -20,  40,  20
		};

		// An array of modifiers for king values based upon the king's position (in the end game)
		constexpr int KingPositionEndgameModifiers[64] = {
			 0,  10,  20,  30,  30,  20,  10,   0,
			10,  20,  30,  40,  40,  30,  20,  10,
			20,  30,  40,  50,  50,  40,  30,  20,
			30,  40,  50,  60,  60,  50,  40,  30,
			30,  40,  50,  60,  60,  50,  40,  30,
			20,  30,  40,  50,  50,  40,  30,  20,
			10,  20,  30,  40,  40,  30,  20,  10,
			 0,  10,  20,  30,  30,  20,  10,   0
		};

		constexpr int DoubledPawnPenalty = 10;		// Penalty for doubled pawns
		constexpr int IsolatedPawnPenalty = 20;		// Penalty for isolated pawns
		constexpr int BackwardPawnPenalty = 10;		// Penalty for backward pawns
		constexpr int PassedPawnBonus = 20;			// Bonus for passed pawns

		constexpr int RookSemiOpenFileBonus = 10;	// Bonus for a rook placed on a semi open file
		constexpr int RookOpenFileBonus = 15;		// Bonus for a rook placed on an open file
		constexpr int RookOnSeventhRankBonus = 20;	// Bonus for a rook placed on the 7th rank

		// An array used to mirror the position about the center ranks so that the above
		// arrays may be used to evaluate the position from black's perspective
		constexpr Square Mirror[64] = {
			56,  57,  58,  59,  60,  61,  62,  63,
			48,  49,  50,  51,  52,  53,  54,  55,
			40,  41,  42,  43,  44,  45,  46,  47,
			32,  33,  34,  35,  36,  37,  38,  39,
			24,  25,  26,  27,  28,  29,  30,  31,
			16,  17,  18,  19,  20,  21,  22,  23,
			 8,   9,  10,  11,  12,  13,  14,  15,
			 0,   1,   2,   3,   4,   5,   6,   7
		};
	}

	int BoardEvaluator::Evaluate(const Board& board)
	{
		Reset();

		// First pass, get unmodified piece values and fill the foremost
		// and rearmost pawn arrays for both white and black
		for (Square square = 0; Helper::IsValidSquare(square); square++)
		{
			const Piece piece = board.m_pieces[square];

			if (piece == Piece::ee || piece == Piece::wk || piece == Piece::bk)
			{
				continue;
			}
			else if (piece == Piece::wp)
			{
				const Row row = Helper::RowFromSquare(square);
				const Col col = Helper::ColFromSquare(square);

				if (row > m_whiteForemostPawns[col + 1])
				{
					m_whiteForemostPawns[col + 1] = row;
				}

				m_whitePawnValues += PawnValue;
			}
			else if (piece == Piece::bp)
			{
				const Row row = Helper::RowFromSquare(square);
				const Col col = Helper::ColFromSquare(square);

				if (row < m_blackForemostPawns[col + 1])
				{
					m_blackForemostPawns[col + 1] = row;
				}

				m_blackPawnValues += PawnValue;
			}
			else
			{
				int pieceValue = 0;

				if (piece == Piece::wn || piece == Piece::bn) pieceValue = KnightValue;
				else if (piece == Piece::wb || piece == Piece::bb) pieceValue = BishopValue;
				else if (piece == Piece::wr || piece == Piece::br) pieceValue = RookValue;
				else if (piece == Piece::wq || piece == Piece::bq) pieceValue = QueenValue;
				else if (piece == Piece::wk || piece == Piece::bk) pieceValue = KingValue;

				if (piece.IsWhite())
				{
					m_whitePieceValues += pieceValue;
				}
				else
				{
					m_blackPieceValues += pieceValue;
				}
			}
		}

		m_whiteScore = m_whitePawnValues + m_whitePieceValues;
		m_blackScore = m_blackPawnValues + m_blackPieceValues;

		// Second pass, apply bonuses and penalties for piece placement, pawn structure, king safety etc.
		for (Square square = 0; Helper::IsValidSquare(square); square++)
		{
			const Piece piece = board.m_pieces[square];

			if (piece == Piece::ee)
			{
				continue;
			}
			else if (piece == Piece::wp)
			{
				m_whiteScore += EvaluateWhitePawn(board, square);
			}
			else if (piece == Piece::bp)
			{
				m_blackScore += EvaluateBlackPawn(board, square);
			}
			else if (piece == Piece::wn)
			{
				m_whiteScore += KnightPositionModifiers[square];
			}
			else if (piece == Piece::bn)
			{
				m_blackScore += KnightPositionModifiers[Mirror[square]];
			}
			else if (piece == Piece::wb)
			{
				m_whiteScore += BishopPositionModifiers[square];
			}
			else if (piece == Piece::bb)
			{
				m_blackScore += BishopPositionModifiers[Mirror[square]];
			}
			else if (piece == Piece::wr)
			{
				m_whiteScore += EvaluateWhiteRook(board, square);
			}
			else if (piece == Piece::br)
			{
				m_blackScore += EvaluateBlackRook(board, square);
			}
			else if (piece == Piece::wk)
			{
				m_whiteScore += EvaluateWhiteKing(board, square);
			}
			else if (piece == Piece::bk)
			{
				m_blackScore += EvaluateBlackKing(board, square);
			}
		}

		// Return the score from the perspective of the player whose turn it currently is
		return (board.m_whiteToPlay
			? (m_whiteScore - m_blackScore)
			: (m_blackScore - m_whiteScore)
			);
	}

	int BoardEvaluator::EvaluateWhitePawn(const Board& board, const Square square)
	{
		const Piece piece = board.m_pieces[square];

		const Row row = Helper::RowFromSquare(square);
		const Col col = Helper::ColFromSquare(square);

		const unsigned char index = col + 1;

		// Penalize the players for doubled, isolated, and backwards pawns
		// Reward the players for passed pawns

		int evaluation = 0;

		evaluation += PawnPositionModifiers[square];

		if (row < m_whiteForemostPawns[index])
		{
			evaluation -= DoubledPawnPenalty;
		}

		if ((m_whiteForemostPawns[index - 1] == 0) && (m_whiteForemostPawns[index + 1] == 0))
		{
			evaluation -= IsolatedPawnPenalty;
		}
		else if ((row < m_whiteForemostPawns[index - 1]) && (row < m_whiteForemostPawns[index + 1]))
		{
			evaluation -= BackwardPawnPenalty;
		}

		if ((row >= m_blackForemostPawns[index - 1]) &&
			(row >= m_blackForemostPawns[index + 1]) &&
			(row >= m_blackForemostPawns[index]))
		{
			evaluation += row * PassedPawnBonus;
		}

		return evaluation;
	}

	int BoardEvaluator::EvaluateBlackPawn(const Board& board, const Square square)
	{
		const Piece piece = board.m_pieces[square];

		const Row row = Helper::RowFromSquare(square);
		const Col col = Helper::ColFromSquare(square);

		const unsigned char index = col + 1;

		// Penalize the players for doubled, isolated, and backwards pawns
		// Reward the players for passed pawns

		int evaluation = 0;

		evaluation += PawnPositionModifiers[Mirror[square]];

		if (row > m_blackForemostPawns[index])
		{
			evaluation -= DoubledPawnPenalty;
		}

		if ((m_blackForemostPawns[index - 1] == 7) && (m_blackForemostPawns[index + 1] == 7))
		{
			evaluation -= IsolatedPawnPenalty;
		}
		else if ((row > m_blackForemostPawns[index - 1]) && (row > m_blackForemostPawns[index + 1]))
		{
			evaluation -= BackwardPawnPenalty;
		}

		if ((row <= m_whiteForemostPawns[index - 1]) &&
			(row <= m_whiteForemostPawns[index + 1]) &&
			(row <= m_whiteForemostPawns[index]))
		{
			evaluation += (7 - row) * PassedPawnBonus;
		}

		return evaluation;
	}

	int BoardEvaluator::EvaluateWhiteRook(const Board& board, const Square square)
	{
		const Piece piece = board.m_pieces[square];

		const Row row = Helper::RowFromSquare(square);
		const Col col = Helper::ColFromSquare(square);

		// Reward the players for rooks on open files, semi open files or the 7th rank

		int evaluation = 0;

		if (m_whiteForemostPawns[col + 1] == 0)
		{
			if (m_blackForemostPawns[col + 1] == 7)
			{
				evaluation += RookOpenFileBonus;
			}
			else
			{
				evaluation += RookSemiOpenFileBonus;
			}
		}

		if (row == 6)
		{
			evaluation += RookOnSeventhRankBonus;
		}

		return evaluation;
	}

	int BoardEvaluator::EvaluateBlackRook(const Board& board, const Square square)
	{
		const Piece piece = board.m_pieces[square];

		const Row row = Helper::RowFromSquare(square);
		const Col col = Helper::ColFromSquare(square);

		// Reward the players for rooks on open files, semi open files or the 7th rank

		int evaluation = 0;

		if (m_blackForemostPawns[col + 1] == 7)
		{
			if (m_whiteForemostPawns[col + 1] == 0)
			{
				evaluation += RookOpenFileBonus;
			}
			else
			{
				evaluation += RookSemiOpenFileBonus;
			}
		}

		if (row == 1)
		{
			evaluation += RookOnSeventhRankBonus;
		}

		return evaluation;
	}

	int BoardEvaluator::EvaluateWhiteKing(const Board& board, const Square square)
	{
		const Piece piece = board.m_pieces[square];

		const Row row = Helper::RowFromSquare(square);
		const Col col = Helper::ColFromSquare(square);

		// Reward/penalize the players based upon their king position and safety.
		// This is treated differently for the opening/middle game and end game.

		int evaluation = 0;

		if (m_blackPieceValues <= 1200)
		{
			evaluation += KingPositionEndgameModifiers[square];
		}
		else
		{
			evaluation += KingPositionModifiers[square];

			if (col > 4)
			{
				evaluation += EvaluateWhiteKingCover(5);
				evaluation += EvaluateWhiteKingCover(6);
				evaluation += EvaluateWhiteKingCover(7);
			}
			else if (col < 3)
			{
				evaluation += EvaluateWhiteKingCover(1);
				evaluation += EvaluateWhiteKingCover(2);
				evaluation += EvaluateWhiteKingCover(3);
			}
			else
			{
				for (Col c = col; c <= col + 2; c++)
				{
					if ((m_whiteForemostPawns[c] == 0) && (m_blackForemostPawns[c] == 7))
					{
						evaluation -= 10;
					}
				}
			}
		}

		return evaluation;
	}

	int BoardEvaluator::EvaluateBlackKing(const Board& board, const Square square)
	{
		const Piece piece = board.m_pieces[square];

		const Row row = Helper::RowFromSquare(square);
		const Col col = Helper::ColFromSquare(square);

		// Reward/penalize the players based upon their king position and safety.
		// This is treated differently for the opening/middle game and end game.

		int evaluation = 0;

		if (m_whitePieceValues <= 1200)
		{
			evaluation += KingPositionEndgameModifiers[Mirror[square]];
		}
		else
		{
			evaluation += KingPositionModifiers[Mirror[square]];

			if (col > 4)
			{
				evaluation += EvaluateBlackKingCover(5);
				evaluation += EvaluateBlackKingCover(6);
				evaluation += EvaluateBlackKingCover(7);
			}
			else if (col < 3)
			{
				evaluation += EvaluateBlackKingCover(1);
				evaluation += EvaluateBlackKingCover(2);
				evaluation += EvaluateBlackKingCover(3);
			}
			else
			{
				for (Col c = col; c <= col + 2; c++)
				{
					if ((m_blackForemostPawns[c] == 7) && (m_whiteForemostPawns[c] == 0))
					{
						evaluation -= 10;
					}
				}
			}
		}

		return evaluation;
	}

	int BoardEvaluator::EvaluateWhiteKingCover(const Col col)
	{
		const unsigned int index = col + 1;

		int evaluation = 0;

		if (m_whiteForemostPawns[index] == 1)
		{
		}
		else if (m_whiteForemostPawns[index] == 2)
		{
			evaluation -= 10;
		}
		else if (m_whiteForemostPawns[index] != 0)
		{
			evaluation -= 20;
		}
		else
		{
			evaluation -= 25;
		}

		if (m_blackForemostPawns[index] == 7)
		{
			evaluation -= 15;
		}
		else if (m_blackForemostPawns[index] == 2)
		{
			evaluation -= 10;
		}
		else if (m_blackForemostPawns[index] == 3)
		{
			evaluation -= 5;
		}

		return evaluation;
	}

	int BoardEvaluator::EvaluateBlackKingCover(const Col col)
	{
		const unsigned int index = col + 1;

		int evaluation = 0;

		if (m_blackForemostPawns[index] == 6)
		{
		}
		else if (m_blackForemostPawns[index] == 5)
		{
			evaluation -= 10;
		}
		else if (m_blackForemostPawns[index] != 7)
		{
			evaluation -= 20;
		}
		else
		{
			evaluation -= 25;
		}

		if (m_whiteForemostPawns[index] == 0)
		{
			evaluation -= 15;
		}
		else if (m_whiteForemostPawns[index] == 5)
		{
			evaluation -= 10;
		}
		else if (m_whiteForemostPawns[index] == 4)
		{
			evaluation -= 5;
		}

		return evaluation;
	}

	void BoardEvaluator::Reset()
	{
		m_whitePawnValues = 0;
		m_blackPawnValues = 0;

		for (int i = 0; i < 10; i++)
		{
			m_whiteForemostPawns[i] = 0;
			m_blackForemostPawns[i] = 7;
		}

		m_whitePieceValues = 0;
		m_blackPieceValues = 0;

		m_whiteScore = 0;
		m_blackScore = 0;
	}
}