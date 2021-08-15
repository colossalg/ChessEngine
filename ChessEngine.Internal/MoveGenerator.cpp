#include "pch.h"

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
		// The offsets from a square to all those whigh can be reached via a knight jump
		const char KnightJumps[8] = { +8, -8, +12, -12, +19, -19, +21, -21 };

		// The offsets from a square to those adjacent diagonally
		const char Diagonals[4] = { +9, -9, +11, -11 };

		// The offsets from a square to those adjacent along the rank or file
		const char RanksAndFiles[4] = { +1, -1, +10, -10 };

		// The offsets from a square to those adjacent diagonally or along the rank or file
		const char DiagonalsRanksAndFiles[8] = { +9, -9, +11, -11, +1, -1, +10, -10 };

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

		// Helper function checking whether a given square plus an offset from that square is on the board, returning
		// a boolean indicating whether it is or not, and setting the square passed as a reference if so.
		inline bool CheckMoveLandsOnBoard(const Square init, const char offset, Square& dest)
		{
			const char destIndex120 = Mailbox64[init] + offset;
			const char destIndex64 = Mailbox120[destIndex120];

			if (destIndex64 == -1)
			{
				return false;
			}
			else
			{
				dest = Square(destIndex64);
				return true;
			}
		}

		// Helper function returns the destination square which is the sum of a given initial square and offset.
		inline Square OffsetSquare(const Square init, const char offset)
		{
			return Square(static_cast<char>(init) + offset);
		}
	}

	MoveList MoveGenerator::GenerateMoves(const Board& board)
	{
		MoveList moveList;

		for (Square init = 0; Helper::IsValidSquare(init); init++)
		{
			Piece piece = board.m_pieces[init];

			if (piece.IsEmpty() || piece.IsWhite() != board.m_whiteToPlay)
			{
				continue;
			}
			else if (piece.IsPawn())
			{
				GeneratePawnMoves(moveList, board, init);
			}
			else if (piece.IsKnight())
			{
				GenerateKnightMoves(moveList, board, init);
			}
			else if (piece.IsBishop())
			{
				GenerateBishopMoves(moveList, board, init);
			}
			else if (piece.IsRook())
			{
				GenerateRookMoves(moveList, board, init);
			}
			else if (piece.IsQueen())
			{
				GenerateQueenMoves(moveList, board, init);
			}
			else if (piece.IsKing())
			{
				GenerateKingMoves(moveList, board, init);
			}
		}

		return moveList;
	}

	bool MoveGenerator::IsSquareAttacked(const Board& board, const Square init)
	{
		// NOTE:
		// A whole bunch of the conditionals here are relying upon their order. When calling
		// CheckMoveLandsOnBoard this returns true if the move lands on the board but it
		// also sets 'dest' to the square the move lands on if it does land on the board.
		// 'dest' is subsequently used to check what piece is on that square. Thus
		// CheckMoveLandsOnBoard must be the first check in these compound conditionals.

		Square dest;

		// Check knight jumps
		for (auto offset : KnightJumps)
		{
			if (CheckMoveLandsOnBoard(init, offset, dest))
			{
				const Piece piece = board.m_pieces[dest];

				if ((board.m_whiteToPlay && piece == Piece::bn) || 
					(!board.m_whiteToPlay && piece == Piece::wn))
				{
					return true;
				}
			}
		}

		// Check diagonals for bishops, queens and king
		for (auto offset : Diagonals)
		{
			for (char lineOffset = offset; CheckMoveLandsOnBoard(init, lineOffset, dest); lineOffset += offset)
			{
				const Piece piece = board.m_pieces[dest];

				if ((board.m_whiteToPlay && piece == Piece::bb) ||
					(board.m_whiteToPlay && piece == Piece::bq) ||
					(!board.m_whiteToPlay && piece == Piece::wb) ||
					(!board.m_whiteToPlay && piece == Piece::wq))
				{
					return true;
				}
				else if (piece != Piece::ee)
				{
					break;
				}
			}

			if (CheckMoveLandsOnBoard(init, offset, dest) &&
				((board.m_whiteToPlay && board.m_pieces[dest] == Piece::bk) || 
				(!board.m_whiteToPlay && board.m_pieces[dest] == Piece::wk)))
			{
				return true;
			}
		}

		// Check diagonals for pawns
		if (board.m_whiteToPlay)
		{
			if ((CheckMoveLandsOnBoard(init, 9, dest) && (board.m_pieces[dest] == Piece::bp)) ||
				(CheckMoveLandsOnBoard(init, 11, dest) && (board.m_pieces[dest] == Piece::bp)))
			{
				return true;
			}
		}
		else
		{
			if ((CheckMoveLandsOnBoard(init, -9, dest) && (board.m_pieces[dest] == Piece::wp)) ||
				(CheckMoveLandsOnBoard(init, -11, dest) && (board.m_pieces[dest] == Piece::wp)))
			{
				return true;
			}
		}

		// Check ranks and files for rooks, queens and king
		for (auto offset : RanksAndFiles)
		{
			for (char lineOffset = offset; CheckMoveLandsOnBoard(init, lineOffset, dest); lineOffset += offset)
			{
				const Piece piece = board.m_pieces[dest];

				if ((board.m_whiteToPlay && piece == Piece::br) ||
					(board.m_whiteToPlay && piece == Piece::bq) ||
					(!board.m_whiteToPlay && piece == Piece::wr) ||
					(!board.m_whiteToPlay && piece == Piece::wq))
				{
					return true;
				}
				else if (piece != Piece::ee)
				{
					break;
				}
			}

			if (CheckMoveLandsOnBoard(init, offset, dest) &&
				((board.m_whiteToPlay && board.m_pieces[dest] == Piece::bk) ||
				(!board.m_whiteToPlay && board.m_pieces[dest] == Piece::wk)))
			{
				return true;
			}
		}

		return false;
	}

	inline void MoveGenerator::GeneratePawnMoves(MoveList& moveList, const Board& board, const Square init)
	{
		const Row row = Helper::RowFromSquare(init);
		const bool onPlayersRank2 = ((board.m_whiteToPlay && row == 1) || (!board.m_whiteToPlay && row == 6));
		const bool onPlayersRank7 = ((board.m_whiteToPlay && row == 6) || (!board.m_whiteToPlay && row == 1));

		// Pushing one or two squares forwards, we don't need to check that these are on the board
		const Square oneForward = OffsetSquare(init, (board.m_whiteToPlay ? +8 : -8));
		const Square twoForward = OffsetSquare(init, (board.m_whiteToPlay ? +16 : -16));

		// Capturing left and right offsets, used to check whether these captures are on the board
		const char captureLftOffset = (board.m_whiteToPlay ? +9 : -9);
		const char captureRgtOffset = (board.m_whiteToPlay ? +11 : -11);

		// Handle promotions
		if (onPlayersRank7)
		{
			// Lambda for pushing all promotions on the the moveList
			auto addPromotionsToList = [&moveList, init](const Square dest, const bool isCapture) mutable -> void {
				moveList.push_back(Move(init, dest, isCapture, true, Piece::Type::Queen));
				moveList.push_back(Move(init, dest, isCapture, true, Piece::Type::Rook));
				moveList.push_back(Move(init, dest, isCapture, true, Piece::Type::Bishop));
				moveList.push_back(Move(init, dest, isCapture, true, Piece::Type::Knight));
			};

			// Push one square
			if (board.m_pieces[oneForward] == Piece::ee)
			{
				addPromotionsToList(oneForward, false);
			}

			Square dest;

			// Take left
			if (CheckMoveLandsOnBoard(init, captureLftOffset, dest))
			{
				const Piece piece = board.m_pieces[dest];

				if ((piece != Piece::ee) && (piece.IsWhite() != board.m_whiteToPlay))
				{
					addPromotionsToList(dest, true);
				}
			}

			// Take right
			if (CheckMoveLandsOnBoard(init, captureRgtOffset, dest))
			{
				const Piece piece = board.m_pieces[dest];

				if ((piece != Piece::ee) && (piece.IsWhite() != board.m_whiteToPlay))
				{
					addPromotionsToList(dest, true);
				}
			}
		}
		else
		{
			// Push one square
			if (board.m_pieces[oneForward] == Piece::ee)
			{
				moveList.push_back(Move(init, oneForward));

				// Push two squares
				if (onPlayersRank2 && board.m_pieces[twoForward] == Piece::ee)
				{
					moveList.push_back(Move(init, twoForward, Move::Special::DoublePawnPush));
				}
			}

			Square dest;

			// Take left
			if (CheckMoveLandsOnBoard(init, captureLftOffset, dest))
			{
				const Piece piece = board.m_pieces[dest];

				if ((piece != Piece::ee) && (piece.IsWhite() != board.m_whiteToPlay))
				{
					moveList.push_back(Move(init, dest, true));
				}
				else if (dest == board.m_enPassant)
				{
					moveList.push_back(Move(init, dest, Move::Special::EnPassantCapture));
				}
			}

			// Take right
			if (CheckMoveLandsOnBoard(init, captureRgtOffset, dest))
			{
				const Piece piece = board.m_pieces[dest];

				if ((piece != Piece::ee) && (piece.IsWhite() != board.m_whiteToPlay))
				{
					moveList.push_back(Move(init, dest, true));
				}
				else if (dest == board.m_enPassant)
				{
					moveList.push_back(Move(init, dest, Move::Special::EnPassantCapture));
				}
			}
		}
	}

	inline void MoveGenerator::GenerateKnightMoves(MoveList& moveList, const Board& board, const Square init)
	{
		for (auto offset : KnightJumps)
		{
			Square dest;

			if (CheckMoveLandsOnBoard(init, offset, dest))
			{
				if (board.m_pieces[dest] == Piece::ee)
				{
					// Move is not a capture
					moveList.push_back(Move(init, dest));
				}
				else if (board.m_pieces[dest].IsWhite() != board.m_whiteToPlay)
				{
					// Move is a capture
					moveList.push_back(Move(init, dest, true));
				}
			}
		}
	}

	inline void MoveGenerator::GenerateBishopMoves(MoveList& moveList, const Board& board, const Square init)
	{
		for (auto lineOffset : Diagonals)
		{
			GenerateMovesAlongLine(moveList, board, init, lineOffset);
		}
	}

	inline void MoveGenerator::GenerateRookMoves(MoveList& moveList, const Board& board, const Square init)
	{
		for (auto lineOffset : RanksAndFiles)
		{
			GenerateMovesAlongLine(moveList, board, init, lineOffset);
		}
	}

	inline void MoveGenerator::GenerateQueenMoves(MoveList& moveList, const Board& board, const Square init)
	{
		for (auto lineOffset : DiagonalsRanksAndFiles)
		{
			GenerateMovesAlongLine(moveList, board, init, lineOffset);
		}
	}

	inline void MoveGenerator::GenerateKingMoves(MoveList& moveList, const Board& board, const Square init)
	{
		Square dest;

		// Check for regular (quiet and capture) moves 1 square along each diagonal, rank and file
		for (char offset : DiagonalsRanksAndFiles)
		{
			if (CheckMoveLandsOnBoard(init, offset, dest))
			{
				if (board.m_pieces[dest] == Piece::ee)
				{
					// Move is not a capture
					moveList.push_back(Move(init, dest));
				}
				else if (board.m_pieces[dest].IsWhite() != board.m_whiteToPlay)
				{
					// Move is a capture
					moveList.push_back(Move(init, dest, true));
				}
			}
		}

		// Check for castling moves

		const bool canCastleKingside = (board.m_whiteToPlay ? board.m_whiteKingside : board.m_blackKingside);
		const bool canCastleQueenside = (board.m_whiteToPlay ? board.m_whiteQueenside : board.m_blackQueenside);

		const Square kingPosition = (board.m_whiteToPlay ? Helper::SquareFromRowAndCol(0, 4) : Helper::SquareFromRowAndCol(7, 4));

		if (IsSquareAttacked(board, kingPosition))
		{
			return;
		}

		if (canCastleKingside)
		{
			const Square oneKingside = OffsetSquare(kingPosition, 1);
			const Square twoKingside = OffsetSquare(kingPosition, 2);

			if (((board.m_pieces[oneKingside] == Piece::ee) && !IsSquareAttacked(board, oneKingside)) &&
				((board.m_pieces[twoKingside] == Piece::ee) && !IsSquareAttacked(board, twoKingside)))
			{
				moveList.push_back(Move(kingPosition, twoKingside, Move::Special::KingsideCastles));
			}
		}

		if (canCastleQueenside)
		{
			const Square oneQueenside = OffsetSquare(kingPosition, -1);
			const Square twoQueenside = OffsetSquare(kingPosition, -2);
			const Square threeQueenside = OffsetSquare(kingPosition, -3);

			if (((board.m_pieces[oneQueenside] == Piece::ee) && !IsSquareAttacked(board, oneQueenside)) &&
				((board.m_pieces[twoQueenside] == Piece::ee) && !IsSquareAttacked(board, twoQueenside)) &&
				((board.m_pieces[threeQueenside] == Piece::ee)))
			{
				moveList.push_back(Move(kingPosition, twoQueenside, Move::Special::QueensideCastles));
			}
		}
	}

	inline void MoveGenerator::GenerateMovesAlongLine(MoveList& moveList, const Board& board, const Square init, const char lineOffset)
	{
		// Search each square along the given line (diagonal, rank or file) starting at init until either the next square
		// is off the board or the next square is occupied. If the next square is occupied check whether we can capture.
		
		Square dest;

		for (char offset = lineOffset; CheckMoveLandsOnBoard(init, offset, dest); offset += lineOffset)
		{
			if (board.m_pieces[dest] == Piece::ee)
			{
				// Move is not a capture
				moveList.push_back(Move(init, dest));
			}
			else
			{
				if (board.m_pieces[dest].IsWhite() != board.m_whiteToPlay)
				{
					// Move is a capture
					moveList.push_back(Move(init, dest, true));
				}
				
				break;
			}
		}
	}
}