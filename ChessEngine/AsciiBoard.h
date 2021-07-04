#pragma once

#include <string>

#include "IPortableNotation.h"

namespace ChessEngine
{
	class AsciiBoard
	{
	public:
		AsciiBoard();
		AsciiBoard(const IPortableNotation& pn);

		void UpdateAscii(const IPortableNotation& pn);

		const std::string& GetAscii() const;

	private:
		std::string m_ascii;
	};
}