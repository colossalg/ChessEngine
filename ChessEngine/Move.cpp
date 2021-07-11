#include "Move.h"

#include <stdexcept>
#include <string>

namespace ChessEngine
{
	Move::Move(Square init, Square dest, bool isCapture, bool isPromotion, Piece::Type promotionType)
	{
		m_move = 0;
		m_move |= (init << InitOffset);
		m_move |= (dest << DestOffset);

		if (isCapture)
		{
			m_move |= Capture;
		}

		if (isPromotion)
		{
			m_move |= Promotion;

			switch (promotionType)
			{
			case Piece::Type::Knight:
				m_move |= KnightPromotion;
				break;
			case Piece::Type::Bishop:
				m_move |= BishopPromotion;
				break;
			case Piece::Type::Rook:
				m_move |= RookPromotion;
				break;
			case Piece::Type::Queen:
				m_move |= QueenPromotion;
				break;
			default:
				std::string error = "Invalid promotion type (" + std::to_string(static_cast<unsigned char>(promotionType)) + ").";
				throw std::invalid_argument(error);
			}
		}
	}

	Move::Move(Square init, Square dest, Special specialType)
	{
		m_move = 0;
		m_move |= (init << InitOffset);
		m_move |= (dest << DestOffset);
		m_move |= static_cast<unsigned short>(specialType);
	}

	Piece::Type Move::GetPromotionType() const
	{
		if (!IsPromotion())
		{
			std::string error = "Can not get promotion type of non-promotion move.";
			throw std::runtime_error(error);
		}

		const unsigned short promotionType = (m_move & TypeMask);
		switch (promotionType)
		{
		case KnightPromotion:
			return Piece::Type::Knight;
		case BishopPromotion:
			return Piece::Type::Bishop;
		case RookPromotion:
			return Piece::Type::Rook;
		case QueenPromotion:
			return Piece::Type::Queen;
		default:
			std::string error = "Invalid promotion type (" + std::to_string(promotionType) + ").";
			throw std::runtime_error(error);
		}
	}
}