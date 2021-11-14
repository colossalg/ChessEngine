#pragma once

namespace ChessEngine
{
	class Piece
	{
	public:
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

		// Create a new piece with the given properties (type, whether it is white)
		Piece(const Type type, const bool isWhite);

		// Create a new piece from the piece's ascii
		Piece(const char ascii);

		// Create a new piece from another piece
		Piece(const Piece& other) = default;

		// Copy one piece to another
		Piece& operator=(const Piece& other) = default;

		// Compare one piece to another
		bool operator==(const Piece& other) const { return (m_piece == other.GetValue()); }
		bool operator!=(const Piece& other) const { return (m_piece != other.GetValue()); }

		// Get whether the piece is an empty square
		bool IsEmpty() const { return ((m_piece & IsEmptyBitMap) == 0); }

		// Get whether the piece is a pawn
		bool IsPawn() const { return ((static_cast<int>(Type::Pawn) & m_piece) != 0); }

		// Get whether the piece is a knight
		bool IsKnight() const { return ((static_cast<int>(Type::Knight) & m_piece) != 0); }

		// Get whether the piece is a bishop
		bool IsBishop() const { return ((static_cast<int>(Type::Bishop) & m_piece) != 0); }

		// Get whether the piece is a rook
		bool IsRook() const { return ((static_cast<int>(Type::Rook) & m_piece) != 0); }

		// Get whether the piece is a queen
		bool IsQueen() const { return ((static_cast<int>(Type::Queen) & m_piece) != 0); }

		// Get whether the piece is a king
		bool IsKing() const { return ((static_cast<int>(Type::King) & m_piece) != 0); }

		// Get whether the piece is white
		bool IsWhite() const { return ((m_piece & IsWhiteBitMap) != 0); }

		// Get the value of the piece
		unsigned int GetValue() const { return m_piece; }

		// Get the ascii representation of the piece
		char GetAscii() const;

	private:
		const static unsigned char IsEmptyBitMap = 0b11111100;	// Bitmap used to determine whether a piece is empty
		const static unsigned char IsWhiteBitMap = 0b00000001;	// Bitmap used to determine whether a piece is white

		unsigned int m_piece = 0;	// Underlying bitmap
	};
}