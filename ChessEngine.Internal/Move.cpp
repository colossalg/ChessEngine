#include "pch.h"

#include "Move.h"

#include "Helper.h"
#include "Piece.h"

namespace ChessEngine
{
	namespace
	{
		const unsigned short KnightPromotion = 0b1000;	// The bitmap for knight promotions
		const unsigned short BishopPromotion = 0b1001;	// The bitmap for bishop promotions
		const unsigned short RookPromotion = 0b1010;	// The bitmap for rook promotions
		const unsigned short QueenPromotion = 0b1011;	// The bitmap for queen promotions
	}

	Move::Move(const Square init, const Square dest, const bool isCapture, const bool isPromotion, const Piece::Type promotionType)
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

	Move::Move(const std::string& init, const std::string& dest, const bool isCapture, const bool isPromotion, const Piece::Type promotionType) :
		Move(
			Helper::SquareFromString(init),
			Helper::SquareFromString(dest),
			isCapture,
			isPromotion,
			promotionType
		)
	{
	}

	Move::Move(const Square init, const Square dest, const Special specialType)
	{
		m_move = 0;
		m_move |= (init << InitOffset);
		m_move |= (dest << DestOffset);
		m_move |= static_cast<unsigned short>(specialType);
	}

	Move::Move(const std::string& init, const std::string& dest, const Special specialType) :
		Move(
			Helper::SquareFromString(init), 
			Helper::SquareFromString(dest),
			specialType
		)
	{
	}

	Piece::Type Move::GetPromotionType() const
	{
		if (!IsPromotion())
		{
			std::string error = "Can not get promotion type of non-promotion move.";
			throw std::runtime_error(error);
		}

		const unsigned short promotionType = (m_move & PromotionTypeMask);
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

	std::string Move::GetString() const
	{
		return ("(" + Helper::StringFromSquare(GetInitSquare()) + "," + Helper::StringFromSquare(GetDestSquare()) + ")");
	}

	std::string Move::GetStringExtended() const
	{
		return ("(" + std::to_string(m_move) + "," + Helper::StringFromSquare(GetInitSquare()) + "," + Helper::StringFromSquare(GetDestSquare()) + ")");
	}
}