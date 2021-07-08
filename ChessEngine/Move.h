#pragma once

#include "Definitions.h"

namespace ChessEngine
{
	class Move
	{
	public:
		const static unsigned char InitOffset = 10;				// The offset of the 6 bits for the initial move
		const static unsigned char DestOffset = 4;				// The offset of the 6 bits for the destination move
		const static unsigned short MoveBitMap = 0b00111111;	// The bitmap for extracting a move square
		const static unsigned short TypeBitMap = 0b00001111;	// The bitmat for extracting a move type

		enum class Type
		{
			Quiet = 0b0000,						// Bitmap for quiet
			Capture = 0b0001,					// Bitmap for capture
			DoublePawnPush = 0b0010,			// Bitmap for double pawn push
			EnPassantCapture = 0b011,			// Bitmap for en passant capture
			KingsideCastles = 0b0100,			// Bitmap for kingside castling
			QueensideCastles = 0b0101,			// Bitmap for queenside castling
			KnightPromotion = 0b0110,			// Bitmap for knight promotions
			BishopPromotion = 0b0111,			// Bitmap for bishop promotions
			RookPromotion = 0b1000,				// Bitmap for rook promotions
			QueenPromotion = 0b1001,			// Bitmap for queen promotions
			KnightPromotionCapture = 0b1010,	// Bitmap for knight promotions with capture
			BishopPromotionCapture = 0b1011,	// Bitmap for bishop promotions with capture
			RookPromotionCapture = 0b1100,		// Bitmap for rook promotions with capture
			QueenPromotionCapture = 0b1101		// Bitmap for queen promotions with capture
		};

		// Create a new move with the given properties (initial square, destination square and move type)
		Move(Square init, Square dest, Type type);

		// Create a new move from another move
		Move(const Move& other) = default;

		// Copy one move to another
		Move& operator=(const Move& other) = default;

		// Get the initial square of the move
		inline Square GetInitSquare() const { return static_cast<Square>((m_move >> InitOffset) & MoveBitMap); }

		// Get the destination square of the move
		inline Square GetDestSquare() const { return static_cast<Square>((m_move >> DestOffset) & MoveBitMap); }

		// Get whether the move is a quiet move
		inline bool IsQuiet() const { return IsXXX(Type::Quiet); }

		// Get whether the move is a capture
		inline bool IsCapture() const { return IsXXX(Type::Capture); }

		// Get whether the move is pushing a pawn two squares
		inline bool IsDoublePawnPush() const { return IsXXX(Type::DoublePawnPush); }

		// Get whether the move is an en passant capture
		inline bool IsEnPassantCapture() const { return IsXXX(Type::EnPassantCapture); }

		// Get whether the move is kingside castling
		inline bool IsKingsideCastles() const { return IsXXX(Type::KingsideCastles); }

		// Get whether the move is queenside castling
		inline bool IsQueensideCastles() const { return IsXXX(Type::QueensideCastles); }

		// Get whether the move is promoting to a knight
		inline bool IsKnightPromotion() const { return IsXXX(Type::KnightPromotion); }

		// Get whether the move is promoting to a bishop
		inline bool IsBishopPromotion() const { return IsXXX(Type::BishopPromotion); }

		// Get whether the move is promoting to a rook
		inline bool IsRookPromotion() const { return IsXXX(Type::RookPromotion); }

		// Get whether the move is promoting to a queen
		inline bool IsQueenPromotion() const { return IsXXX(Type::QueenPromotion); }

		// Get whether the move is promoting to a knight with a capture
		inline bool IsKnightPromotionCapture() const { return IsXXX(Type::KnightPromotionCapture); }

		// Get whether the move is promoting to a bishop with a capture
		inline bool IsBishopPromotionCapture() const { return IsXXX(Type::BishopPromotionCapture); }

		// Get whether the move is promoting to a rook with a capture
		inline bool IsRookPromotionCapture() const { return IsXXX(Type::RookPromotionCapture); }

		// Get whether the move is promoting to a queen with a capture
		inline bool IsQueenPromotionCapture() const { return IsXXX(Type::QueenPromotionCapture); }

	private:
		// Helper function for querying whether a move is XXX (capture, promotion, etc.)
		inline bool IsXXX(Type type) const { return (Type(m_move & TypeBitMap) == type); }

		unsigned short m_move;	// The underlying bitmap
	};
}