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
		TranspositionTable(size_t maxEntries);

		// Gets the entry with a given hash
		TranspositionTableEntry& operator[](unsigned long long hash);

		// Get the max entries in the underlying table/map
		size_t GetMaxEntries() const { return m_maxEntries; }

		// Get the num entries in the underlying table/map
		size_t GetNumEntries() const { return m_table.size(); }

	private:

		size_t m_maxEntries;														// The max entries in the underlying table/map
		std::unordered_map<unsigned long long, TranspositionTableEntry> m_table;	// The underlying table/map
	};
}
