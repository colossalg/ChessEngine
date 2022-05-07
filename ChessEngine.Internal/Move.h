#pragma once

#include <string>

#include "Definitions.h"
#include "Piece.h"

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
        Move(
            const Square init,
            const Square dest,
            const bool isCapture = false,
            const bool isPromotion = false,
            const Piece::Type promotionType = Piece::Type::Queen);

        // Create a new move with the given properties (init/dest squares as strings, is a capture, is a promotion and to what piece)
        Move(
            const std::string& init,
            const std::string& dest,
            const bool isCapture = false,
            const bool isPromotion = false,
            const Piece::Type promotionType = Piece::Type::Queen);

        // Create a new move from one of the special move types (double pawn push, castling, en passant capture)
        Move(const Square init, const Square dest, const Special specialType);

        // Create a new move from one of the special move types (double pawn push, castling, en passant capture)
        Move(const std::string& init, const std::string& dest, const Special specialType);

        // Default constructor
        Move() = default;

        // Create a new move from another move
        Move(const Move& other) = default;

        // Copy one move to another
        Move& operator=(const Move& other) { m_move = other.m_move; return *this; }

        // Compare one move to another
        bool operator==(const Move& other) const { return (m_move == other.GetValue()); }
        bool operator!=(const Move& other) const { return (m_move != other.GetValue()); }

        // Get the initial square of the move
        Square GetInitSquare() const { return static_cast<Square>((m_move >> InitOffset) & MoveMask); }

        // Get the destination square of the move
        Square GetDestSquare() const { return static_cast<Square>((m_move >> DestOffset) & MoveMask); }

        // Get whether the move is a quiet move
        bool IsQuiet() const { return ((m_move & TypeMask) == 0); }

        // Get whether the move is a capture
        bool IsCapture() const { return ((m_move & Capture) == Capture); }

        // Get whether the move is a promotion
        bool IsPromotion() const { return ((m_move & Promotion) == Promotion); }

        // Get whether the move is pushing a pawn two squares
        bool IsDoublePawnPush() const { return IsSpecial(Special::DoublePawnPush); }

        // Get whether the move is an en passant capture
        bool IsEnPassantCapture() const { return IsSpecial(Special::EnPassantCapture); }

        // Get whether the move is kingside castling
        bool IsKingsideCastles() const { return IsSpecial(Special::KingsideCastles); }

        // Get whether the move is queenside castling
        bool IsQueensideCastles() const { return IsSpecial(Special::QueensideCastles); }

        // Get the type of the piece that the pawn is promoted to
        Piece::Type GetPromotionType() const;

        // Get the value of the move
        unsigned short GetValue() const { return m_move; }

        // Get the move represented as a string (start square, end square)
        std::string GetString() const;

        // Get the move represented as a string (raw value, start square, end square)
        std::string GetStringExtended() const;

    private:
        // Helper function for querying whether a move is XXX (capture, promotion, etc.)
        bool IsSpecial(Special specialType) const { return (Special(m_move & TypeMask) == specialType); }

        const static unsigned char InitOffset = 10; // The offset of the 6 bits for the initial move
        const static unsigned char DestOffset = 4;  // The offset of the 6 bits for the destination move

        const static unsigned short MoveMask = 0b00111111;  // The mask for extracting a move square
        const static unsigned short TypeMask = 0b00001111;  // The mask for extracting a move type
        const static unsigned short PromotionTypeMask = 0b1011; // The mask for extracting the piece type of a promotion move

        const static unsigned short Capture = 0b0100;   // The bitmap for whether a move is a capture

        const unsigned short Promotion = 0b1000;        // The bitmap for whether a move is a promotion

        unsigned short m_move = 0;  // The underlying bitmap for the move
    };
}