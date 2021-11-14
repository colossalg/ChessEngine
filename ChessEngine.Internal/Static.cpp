// This file contains all of the static member definitions for all classes. They must be defined
// in this file as I found out the HARD way that the order of static initialization is undefined
// accross compilation units.

#include "pch.h"

#include "Piece.h"
#include "Board.h"

namespace ChessEngine
{
	// Static piece definitions, these make initializing boards, etc. much easier
	const Piece Piece::ee = Piece(Piece::Type::Empty, true);
	const Piece Piece::wp = Piece(Piece::Type::Pawn, true);
	const Piece Piece::wn = Piece(Piece::Type::Knight, true);
	const Piece Piece::wb = Piece(Piece::Type::Bishop, true);
	const Piece Piece::wr = Piece(Piece::Type::Rook, true);
	const Piece Piece::wq = Piece(Piece::Type::Queen, true);
	const Piece Piece::wk = Piece(Piece::Type::King, true);
	const Piece Piece::bp = Piece(Piece::Type::Pawn, false);
	const Piece Piece::bn = Piece(Piece::Type::Knight, false);
	const Piece Piece::bb = Piece(Piece::Type::Bishop, false);
	const Piece Piece::br = Piece(Piece::Type::Rook, false);
	const Piece Piece::bq = Piece(Piece::Type::Queen, false);
	const Piece Piece::bk = Piece(Piece::Type::King, false);

	// Starting piece array, representing the board setup at the start of a game
	const PieceArray Board::StartingPieces = PieceArray{
		Piece::wr, Piece::wn, Piece::wb, Piece::wq, Piece::wk, Piece::wb, Piece::wn, Piece::wr,
		Piece::wp, Piece::wp, Piece::wp, Piece::wp, Piece::wp, Piece::wp, Piece::wp, Piece::wp,
		Piece::ee, Piece::ee, Piece::ee, Piece::ee, Piece::ee, Piece::ee, Piece::ee, Piece::ee,
		Piece::ee, Piece::ee, Piece::ee, Piece::ee, Piece::ee, Piece::ee, Piece::ee, Piece::ee,
		Piece::ee, Piece::ee, Piece::ee, Piece::ee, Piece::ee, Piece::ee, Piece::ee, Piece::ee,
		Piece::ee, Piece::ee, Piece::ee, Piece::ee, Piece::ee, Piece::ee, Piece::ee, Piece::ee,
		Piece::bp, Piece::bp, Piece::bp, Piece::bp, Piece::bp, Piece::bp, Piece::bp, Piece::bp,
		Piece::br, Piece::bn, Piece::bb, Piece::bq, Piece::bk, Piece::bb, Piece::bn, Piece::br
	};

	// The array of all the piece types so we can iterate over them
	const std::array<Piece::Type, 7> Piece::AllTypes = {
		Piece::Type::Empty,
		Piece::Type::Pawn,
		Piece::Type::Knight,
		Piece::Type::Bishop,
		Piece::Type::Rook,
		Piece::Type::Queen,
		Piece::Type::King
	};
}