#pragma once

#include <functional>
#include <unordered_map>

#include "TranspositionTableEntry.h"

namespace ChessEngine
{
	class TranspositionTable
	{
	public:

		// Replacement strategies are used to determine when to replace one table entry
		// with another in the instance where a hash collision occurs for two positions
		static std::function<bool(const TranspositionTableEntry&, const TranspositionTableEntry&)> ReplacementStrategy;

		// Create a new transposition table
		TranspositionTable(unsigned int length);

		// Gets the entry with a given hash
		TranspositionTableEntry& operator[](unsigned int hash);

	private:

		unsigned int m_length;												// The lenth of the underlying table/map
		std::unordered_map<unsigned int, TranspositionTableEntry> m_table;	// The underlying table/map
	};
}
