#pragma once

#include "Definitions.h"

namespace ChessEngine
{
	class MoveGenerator
	{
	public:

		// Generate and return a list of all the pseudo-legal moves for the position
		static std::list<Move> GenerateMoves(const Board& board);

		// Determine whether a square is attacked or not
		static bool IsSquareAttacked(const Board& board, const Square init);

	private:

		friend class MoveGeneratorTests;

		// Generate and return a list of all the pseudo-legal moves for the pawn at the given square on the board
		static void GeneratePawnMoves(MoveList& moveList, const Board& board, const Square init);

		// Generate and return a list of all the pseudo-legal moves for the knight at the given square on the board
		static void GenerateKnightMoves(MoveList& moveList, const Board& board, const Square init);

		// Generate and return a list of all the pseudo-legal moves for the bishop at the given square on the board
		static void GenerateBishopMoves(MoveList& moveList, const Board& board, const Square init);

		// Generate and return a list of all the pseudo-legal moves for the rook at the given square on the board
		static void GenerateRookMoves(MoveList& moveList, const Board& board, const Square init);

		// Generate and return a list of all the pseudo-legal moves for the queen at the given square on the board
		static void GenerateQueenMoves(MoveList& moveList, const Board& board, const Square init);

		// Generate and return a list of all the pseudo-legal moves for the king at the given square on the board
		static void GenerateKingMoves(MoveList& moveList, const Board& board, const Square init);

		// Helper function for generating all pseudo-legal moves moving the piece at init along a given line (diagonal, rank or file)
		static void GenerateMovesAlongLine(MoveList& moveList, const Board& board, const Square init, const char lineOffset);
	};
}
