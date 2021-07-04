#pragma once

#include <string>

#include "Definitions.h"

namespace ChessEngine
{
	class PortableNotation
	{
	public:
		~PortableNotation() = default;

		virtual void SetNotationString(const std::string& notationString) = 0;
		virtual const std::string& GetNotationString() = 0;

		virtual Piece GetPieceAt(Square square) const;
		virtual void SetPieceAt(Square square, Piece piece);

		virtual bool GetWhiteToPlay() const;
		virtual void SetWhiteToPlay(bool whiteToPlay);

		virtual Castling GetCastling() const;
		virtual void SetCastling(Castling castling);

		virtual EnPassan GetEnPassan() const;
		virtual void SetEnPassan(EnPassan enPassan);

	protected:
		virtual void ParseNotationString() = 0;
		virtual void UpdateNotationString() = 0;

		std::string m_notationString;
		bool m_outdated;

		std::array<Piece, 64> m_pieces{};

		bool m_whiteToPlay;

		Castling m_castling{ true, true, true, true };

		EnPassan m_enPassan{ false, 0, 0 };
	};

	class FEN : public PortableNotation
	{
	public:
		FEN(const std::string& notationString);

	private:
		void ParseNotationString() override;
		void UpdateNotationString() override;
	};

	class PGN : public PortableNotation
	{
	public:
		PGN(const std::string& notationString);

	private:
		void ParseNotationString() override;
		void UpdateNotationString() override;
	};
}