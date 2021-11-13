#include "pch.h"

#include <optional>

#include "TranspositionTable.h"

namespace ChessEngine
{
	TranspositionTable::TranspositionTable(unsigned int length):
		m_length(length)
	{
	}

	TranspositionTableEntry& TranspositionTable::operator[](unsigned int hash)
	{
		return m_table[hash % m_length];
	}
}