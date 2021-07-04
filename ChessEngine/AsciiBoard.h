#pragma once

#include <string>

#include "PortableNotation.h"

namespace ChessEngine
{
	class AsciiBoard
	{
	public:
		AsciiBoard();
		AsciiBoard(const PortableNotation& pn);

		void UpdateAscii(const PortableNotation& pn);

		const std::string& GetAscii() const;

	private:
		std::string m_ascii;
	};
}