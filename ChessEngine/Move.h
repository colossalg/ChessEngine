#pragma once

#include "Definitions.h"

namespace ChessEngine
{
	class Move
	{
	public:

		enum class Special
		{
			DoublePawnPush = 0b0001, 
			KingsideCastles = 0b0010, 
			QueensideCastles = 0b0011, 
			EnPassantCapture = 0b0101
		};

		// Create a new move with the given properties (init/dest squares, is a capture, is a promotion and to what piece)
		Move(Square init, Square dest, bool isCapture = false, bool isPromotion = false, Piece::Type promotionType = Piece::Type::Queen);

		// Create a new move from one of the special move types (double pawn push, castling, en passant capture)
		Move(Square init, Square dest, Special specialType);

		// Create a new move from another move
		Move(const Move& other) = default;

		// Copy one move to another
		Move& operator=(const Move& other) = default;

		// Get the initial square of the move
		inline Square GetInitSquare() const { return static_cast<Square>((m_move >> InitOffset) & MoveMask); }

		// Get the destination square of the move
		inline Square GetDestSquare() const { return static_cast<Square>((m_move >> DestOffset) & MoveMask); }

		// Get whether the move is a quiet move
		inline bool IsQuiet() const { return ((m_move & TypeMask) == 0); }

		// Get whether the move is a capture
		inline bool IsCapture() const { return ((m_move & Capture) == Capture); }

		// Get whether the move is a promotion
		inline bool IsPromotion() const { return ((m_move & Promotion) == Promotion); }

		// Get whether the move is pushing a pawn two squares
		inline bool IsDoublePawnPush() const { return IsSpecial(Special::DoublePawnPush); }

		// Get whether the move is an en passant capture
		inline bool IsEnPassantCapture() const { return IsSpecial(Special::EnPassantCapture); }

		// Get whether the move is kingside castling
		inline bool IsKingsideCastles() const { return IsSpecial(Special::KingsideCastles); }

		// Get whether the move is queenside castling
		inline bool IsQueensideCastles() const { return IsSpecial(Special::QueensideCastles); }

		// Get the type of the piece that the pawn is promoted to
		Piece::Type GetPromotionType() const;

	private:
		// Helper function for querying whether a move is XXX (capture, promotion, etc.)
		inline bool IsSpecial(Special specialType) const { return (Special(m_move & TypeMask) == specialType); }

		const static unsigned char InitOffset = 10;			// The offset of the 6 bits for the initial move
		const static unsigned char DestOffset = 4;			// The offset of the 6 bits for the destination move

		const static unsigned short MoveMask = 0b00111111;	// The mask for extracting a move square
		const static unsigned short TypeMask = 0b00001111;	// The mask for extracting a move type

		const static unsigned short Capture = 0b0100;		// The bitmap for whether a move is a capture
		
		const static unsigned short Promotion = 0b1000;			// The bitmap for whether a move is a promotion
		const static unsigned short KnightPromotion = 0b1000;	// The bitmap for knight promotions
		const static unsigned short BishopPromotion = 0b1001;	// The bitmap for bishop promotions
		const static unsigned short RookPromotion = 0b1010;		// The bitmap for rook promotions
		const static unsigned short QueenPromotion = 0b1011;	// The bitmap for queen promotions

		unsigned short m_move;	// The underlying bitmap for the move
	};
}