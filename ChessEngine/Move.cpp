#include "Move.h"

namespace ChessEngine
{
	Move::Move(Square init, Square dest, Type type)
	{
		m_move = 0;
		m_move |= (init << InitOffset);
		m_move |= (dest << DestOffset);
		m_move |= static_cast<short>(type);
	}
}