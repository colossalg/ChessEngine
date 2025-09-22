#pragma once

namespace ChessEngine
{
    class Piece
    {
    public:
        // Pieces used to initialize boards, etc.
        const static Piece ee, wp, bp, wn, bn, wb, bb, wr, br, wq, bq, wk, bk;

        // Mask for extracting whether the piece is white.
        constexpr static uint8_t IsWhiteMask = 0b00'00'00'01;

        // Mask for extracting whether the piece's type.
        constexpr static uint8_t EmptyMask  = 0b00'00'00'10;
        constexpr static uint8_t PawnMask   = 0b00'00'01'00;
        constexpr static uint8_t KnightMask = 0b00'00'10'00;
        constexpr static uint8_t BishopMask = 0b00'01'00'00;
        constexpr static uint8_t RookMask   = 0b00'10'00'00;
        constexpr static uint8_t QueenMask  = 0b01'00'00'00;
        constexpr static uint8_t KingMask   = 0b10'00'00'00;
        constexpr static uint8_t PieceTypeMask = (
            EmptyMask | PawnMask | KnightMask | BishopMask | RookMask | QueenMask | KingMask
        );

        // The types of each piece, each has a value which is also a bitmap
        enum class Type : uint8_t
        {
            Empty  = EmptyMask,
            Pawn   = PawnMask,
            Knight = KnightMask,
            Bishop = BishopMask,
            Rook   = RookMask,
            Queen  = QueenMask,
            King   = KingMask,
        };

        // The array of all the piece types so we can iterate over them
        static const std::array<Type, 7> AllTypes;

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
        bool IsEmpty() const { return (m_piece & EmptyMask) != 0; }

        // Get whether the piece is a pawn
        bool IsPawn() const { return (m_piece & PawnMask) != 0; }

        // Get whether the piece is a knight
        bool IsKnight() const { return (m_piece & KnightMask) != 0; }

        // Get whether the piece is a bishop
        bool IsBishop() const { return (m_piece & BishopMask) != 0; }

        // Get whether the piece is a rook
        bool IsRook() const { return (m_piece & RookMask) != 0; }

        // Get whether the piece is a queen
        bool IsQueen() const { return (m_piece & QueenMask) != 0; }

        // Get whether the piece is a king
        bool IsKing() const { return (m_piece & KingMask) != 0; }

        // Get whether the piece is white
        bool IsWhite() const { return ((m_piece & IsWhiteMask) != 0); }

        // Get the type of the piece
        Type GetType() const { return Type(m_piece & PieceTypeMask); }

        // Get the value of the piece
        unsigned int GetValue() const { return m_piece; }

        // Get the ascii representation of the piece
        char GetAscii() const;

    private:
        uint8_t m_piece = 0; // Underlying bitmap
    };
}