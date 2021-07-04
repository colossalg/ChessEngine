#include "AsciiBoard.h"

#include <stdexcept>

namespace ChessEngine
{
	const std::string DefaultAsciiBoard =
		"w kqKQ -                     \r\n"
		"  +------------------------+ \r\n"
		"8 |*R *N:*B *Q:*K *B:*N *R:| \r\n"
		"7 |*P:*P *P:*P *P:*P *P:*P | \r\n"
		"6 |   :::   :::   :::   :::| \r\n"
		"5 |:::   :::   :::   :::   | \r\n"
		"4 |   :::   :::   :::   :::| \r\n"
		"3 |:::   :::   :::   :::   | \r\n"
		"2 | P :P: P :P: P :P: P :P:| \r\n"
		"1 |:R: N :B: Q :K: B :N: R | \r\n"
		"  +------------------------+ \r\n"
		"    a  b  c  d  e  f  g  h   \r\n";

	AsciiBoard::AsciiBoard() :
		m_ascii(DefaultAsciiBoard)
	{
	}

	AsciiBoard::AsciiBoard(const PortableNotation& pn)
	{
		throw std::logic_error("Constructor not yet implemented.");
	}

	void AsciiBoard::UpdateAscii(const PortableNotation& pn)
	{
		throw std::logic_error("Method not yet implemented.");
	}

	const std::string& AsciiBoard::GetAscii() const
	{
		return m_ascii;
	}
}