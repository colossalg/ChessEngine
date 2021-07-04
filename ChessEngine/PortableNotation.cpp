#include "PortableNotation.h"

#include <stdexcept>

#include "BoardHelper.h"

namespace ChessEngine
{
	void PortableNotation::SetNotationString(const std::string& notationString)
	{
		m_notationString = notationString;
		ParseNotationString();
	}

	const std::string& PortableNotation::GetNotationString()
	{
		if (m_outdated)
		{
			UpdateNotationString();
		}

		return m_notationString;
	}

	Piece PortableNotation::GetPieceAt(Square square) const
	{
		if (!BoardHelper::IsValidSquare(square))
		{
			std::string error = "Invalid Square " + std::to_string(square) + ".";
			throw std::invalid_argument(error);
		}

		return m_pieces[square];
	}

	void PortableNotation::SetPieceAt(Square square, Piece piece)
	{
		if (!BoardHelper::IsValidSquare(square))
		{
			std::string error = "Invalid Square " + std::to_string(square) + ".";
			throw std::invalid_argument(error);
		}

		m_outdated = true;
		m_pieces[square] = piece;
	}

	bool PortableNotation::GetWhiteToPlay() const
	{
		return m_whiteToPlay;
	}

	void PortableNotation::SetWhiteToPlay(bool whiteToPlay)
	{
		m_outdated = true;
		m_whiteToPlay = whiteToPlay;
	}

	Castling PortableNotation::GetCastling() const
	{
		return m_castling;
	}

	void PortableNotation::SetCastling(Castling castling)
	{
		m_outdated = true;
		m_castling = castling;
	}

	EnPassan PortableNotation::GetEnPassan() const
	{
		return m_enPassan;
	}

	void PortableNotation::SetEnPassan(EnPassan enPassan)
	{
		m_outdated = true;
		m_enPassan = enPassan;
	}

	FEN::FEN(const std::string& notationString)
	{
		m_notationString = notationString;
		ParseNotationString();
	}

	void FEN::ParseNotationString()
	{
		throw std::logic_error("Function not yet implemented.");
	}

	void FEN::UpdateNotationString()
	{
		throw std::logic_error("Function not yet implemented.");
	}

	PGN::PGN(const std::string& notationString)
	{
		m_notationString = notationString;
		ParseNotationString();
	}

	void PGN::ParseNotationString()
	{
		throw std::logic_error("Function not yet implemented.");
	}

	void PGN::UpdateNotationString()
	{
		throw std::logic_error("Function not yet implemented.");
	}
}