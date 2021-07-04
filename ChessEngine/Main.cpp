#include <array>
#include <iostream>

#include "AsciiBoard.h"
#include "Definitions.h"
#include "PieceHelper.h"

using namespace ChessEngine;

Piece u = PieceHelper::MakePiece(PieceHelper::PieceType::Empty, false);
Piece p = PieceHelper::MakePiece(PieceHelper::PieceType::Pawn, true);
Piece n = PieceHelper::MakePiece(PieceHelper::PieceType::Knight, true);
Piece b = PieceHelper::MakePiece(PieceHelper::PieceType::Bishop, true);
Piece r = PieceHelper::MakePiece(PieceHelper::PieceType::Rook, true);
Piece q = PieceHelper::MakePiece(PieceHelper::PieceType::Queen, true);
Piece k = PieceHelper::MakePiece(PieceHelper::PieceType::King, true);
Piece P = PieceHelper::MakePiece(PieceHelper::PieceType::Pawn, false);
Piece N = PieceHelper::MakePiece(PieceHelper::PieceType::Knight, false);
Piece B = PieceHelper::MakePiece(PieceHelper::PieceType::Bishop, false);
Piece R = PieceHelper::MakePiece(PieceHelper::PieceType::Rook, false);
Piece Q = PieceHelper::MakePiece(PieceHelper::PieceType::Queen, false);
Piece K = PieceHelper::MakePiece(PieceHelper::PieceType::King, false);

std::array<Piece, 64> defaultPieceArr{
	r, n, b, q, k, b, n, r,
	p, p, p, p, u, p, p, p,
	u, u, u, u, u, u, u, u,
	u, u, u, u, p, u, u, u,
	u, u, u, u, u, u, u, u,
	u, u, u, u, u, u, u, u,
	P, P, P, P, P, P, P, P,
	R, N, B, Q, K, B, N, R
};

int main()
{
	ChessEngine::AsciiBoard asciiBoard;
	asciiBoard.SetPieces(defaultPieceArr);
	asciiBoard.SetCastling(true, true, true, true);
	asciiBoard.SetEnPassant(false, 0);

	std::cout << asciiBoard.GetAscii() << std::endl;

	return 0;
}