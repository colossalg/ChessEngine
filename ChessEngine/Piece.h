#pragma once

namespace ChessEngine
{
	class Piece
	{
	public:
		const static unsigned char HasMovedBitMap = 0b00000010;	// Bitmap used to determine whether a piece has moved
		const static unsigned char IsEmptyBitMap = 0b11111100;	// Bitmap used to determine whether a piece is empty
		const static unsigned char IsWhiteBitMap = 0b00000001;	// Bitmap used to determine whether a piece is white

		// Pieces used to initialize boards, etc.
		const static Piece ee, wp, bp, wn, bn, wb, bb, wr, br, wq, bq, wk, bk;

		// The types of each piece, each has a value which is also a bitmap
		enum class Type
		{
			Empty = 0b00000000,
			Pawn = 0b00000100,
			Knight = 0b00001000,
			Bishop = 0b00010000,
			Rook = 0b00100000,
			Queen = 0b01000000,
			King = 0b10000000
		};

		// Create a new piece
		Piece() = default;

		// Create a new piece from another piece
		Piece(const Piece& other) = default;

		// Create a new piece with the given properties (type, whether it is white, whether it has moved)
		Piece(Type type, bool isWhite, bool hasMoved = false);

		// Copy one piece to another
		Piece& operator=(const Piece& other) = default;

		// Get whether the piece is an empty square
		inline bool IsEmpty() const { return ((m_piece & IsEmptyBitMap) == 0); }

		// Get whether the piece is a pawn
		inline bool IsPawn() const { return ((static_cast<int>(Type::Pawn) & m_piece) != 0); }

		// Get whether the piece is a knight
		inline bool IsKnight() const { return ((static_cast<int>(Type::Knight) & m_piece) != 0); }

		// Get whether the piece is a bishop
		inline bool IsBishop() const { return ((static_cast<int>(Type::Bishop) & m_piece) != 0); }

		// Get whether the piece is a rook
		inline bool IsRook() const { return ((static_cast<int>(Type::Rook) & m_piece) != 0); }

		// Get whether the piece is a queen
		inline bool IsQueen() const { return ((static_cast<int>(Type::Queen) & m_piece) != 0); }

		// Get whether the piece is a king
		inline bool IsKing() const { return ((static_cast<int>(Type::King) & m_piece) != 0); }

		// Get whether the piece is white
		inline bool IsWhite() const { return ((m_piece & IsWhiteBitMap) != 0); }

		// Get whether the piece has moved
		inline bool HasMoved() const { return ((m_piece & HasMovedBitMap) != 0); }

		// Set that the piece has moved
		inline void SetHasMoved() { m_piece |= HasMovedBitMap; }

		// Get the value of the piece
		inline unsigned int GetValue() const { return m_piece; }

		// Get the ascii representation of the piece
		char GetAscii() const;

	private:
		unsigned int m_piece = 0;	// Underlying bitmap
	};
}