#pragma once

#include "Definitions.h"

namespace ChessEngine
{
	class MoveGenerator
	{
	public:

		// Generate and return a list of all the pseudo-legal moves for the position
		static std::list<Move> GenerateMoves(const Board& board);

	private:

		// Generate and return a list of all the pseudo-legal moves for the pawn at the given square on the board
		static void GeneratePawnMoves(const MoveList& moveList, const Board& board, Square square);

		// Generate and return a list of all the pseudo-legal moves for the knight at the given square on the board
		static void GenerateKnightMoves(const MoveList& moveList, const Board& board, Square square);

		// Generate and return a list of all the pseudo-legal moves for the bishop at the given square on the board
		static void GenerateBishopMoves(const MoveList& moveList, const Board& board, Square square);

		// Generate and return a list of all the pseudo-legal moves for the rook at the given square on the board
		static void GenerateRookMoves(const MoveList& moveList, const Board& board, Square square);

		// Generate and return a list of all the pseudo-legal moves fo the queen at the given square on the board
		static void GenerateQueenMoves(const MoveList& moveList, const Board& board, Square square);

		// Generate and return a list of all the pseudo-legal moves fo the king at the given square on the board
		static void GenerateKingMoves(const MoveList& moveList, const Board& board, Square square);
	};
}
