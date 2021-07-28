#include "MoveGenerator.h"

#include "Board.h"
#include "Definitions.h"
#include "Helper.h"
#include "Move.h"
#include "Piece.h"

namespace ChessEngine
{
	namespace
	{
		// The offsets from a square to those adjacent diagonally
		const char Diagonals[4] = { +9, -9, +11, -11 };

		// The offsets from a square to those adjacent along the rank or file
		const char RanksAndFiles[4] = { +1, -1, +10, -10 };

		// The 120 character mailbox for detecting whether a move will land on
		// the board or not. Each entry is either -1 denoting that the move is
		// not on the board, or, the valid square that the move will land on.
		const char Mailbox120[120] = {
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1,  0,  1,  2,  3,  4,  5,  6,  7, -1,
			-1,  8,  9, 10, 11, 12, 13, 14, 15, -1,
			-1, 16, 17, 18, 19, 20, 21, 22, 23, -1,
			-1, 24, 25, 26, 27, 28, 29, 30, 31, -1,
			-1, 32, 33, 34, 35, 36, 37, 38, 39, -1,
			-1, 40, 41, 42, 43, 44, 45, 46, 47, -1,
			-1, 48, 49, 50, 51, 52, 53, 54, 55, -1,
			-1, 56, 57, 58, 59, 60, 61, 62, 63, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		};

		// The 64 character mailbox which maps squares to the index of the
		// corresponding entry in Mailbox120.
		const char Mailbox64[64] = {
			21, 22, 23, 24, 25, 26, 27, 28,
			31, 32, 33, 34, 35, 36, 37, 38,
			41, 42, 43, 44, 45, 46, 47, 48,
			51, 52, 53, 54, 55, 56, 57, 58,
			61, 62, 63, 64, 65, 66, 67, 68,
			71, 72, 73, 74, 75, 76, 77, 78,
			81, 82, 83, 84, 85, 86, 87, 88,
			91, 92, 93, 94, 95, 96, 97, 98
		};
	}

	MoveList MoveGenerator::GenerateMoves(const Board& board)
	{
		MoveList moveList;

		for (Square square = 0; Helper::IsValidSquare(square); square++)
		{
			Piece piece = board.m_pieces[square];

			if (piece.IsEmpty())
			{
				continue;
			}
			else if (piece.IsPawn())
			{
				GeneratePawnMoves(moveList, board, square);
			}
			else if (piece.IsKnight())
			{
				GenerateKnightMoves(moveList, board, square);
			}
			else if (piece.IsBishop())
			{
				GenerateBishopMoves(moveList, board, square);
			}
			else if (piece.IsRook())
			{
				GenerateRookMoves(moveList, board, square);
			}
			else if (piece.IsQueen())
			{
				GenerateQueenMoves(moveList, board, square);
			}
			else if (piece.IsKing())
			{
				GenerateKingMoves(moveList, board, square);
			}
		}

		return MoveList();
	}

	// Generate and return a list of all the pseudo-legal moves for the knight at the given square on the board
	inline void MoveGenerator::GeneratePawnMoves(const MoveList& moveList, const Board& board, Square square)
	{
		const char oneForwards = square + (board.m_whiteToPlay ? +10 : -10);
		const char twoForwards = square + (board.m_whiteToPlay ? +20 : -20);
		const char captureLft = square + (board.m_whiteToPlay ? +9  : -9);
		const char captureRgt = square + (board.m_whiteToPlay ? +11 : -11);

		// TODO
	}

	// Generate and return a list of all the pseudo-legal moves for the knight at the given square on the board
	inline void MoveGenerator::GenerateKnightMoves(const MoveList& moveList, const Board& board, Square square)
	{
		const char knightJumps[8] = { +8, -8, +12, -12, +19, -19, +21, -21 };

		// TODO
	}

	// Generate and return a list of all the pseudo-legal moves for the bishop at the given square on the board
	inline void MoveGenerator::GenerateBishopMoves(const MoveList& moveList, const Board& board, Square square)
	{
		// TODO
	}

	// Generate and return a list of all the pseudo-legal moves for the rook at the given square on the board
	inline void MoveGenerator::GenerateRookMoves(const MoveList& moveList, const Board& board, Square square)
	{
		// TODO
	}

	// Generate and return a list of all the pseudo-legal moves for the queen at the given square on the board
	inline void MoveGenerator::GenerateQueenMoves(const MoveList& moveList, const Board& board, Square square)
	{
		// TODO
	}

	// Generate and return a list of all the pseudo-legal moves for the king at the given square on the board
	inline void MoveGenerator::GenerateKingMoves(const MoveList& moveList, const Board& board, Square square)
	{
		// TODO
	}
}