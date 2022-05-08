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

        // Get a pointer to the entry with a given hash (returns nullptr if no such entry exists)
        TranspositionTableEntry* GetEntry(unsigned int hash);

        // Insert an entry in to the transposition table. In the case of a collision, then
        // the replacement strategy is used to determine which entry should be kept
        void InsertEntry(const TranspositionTableEntry& entry);

    private:

        std::vector<TranspositionTableEntry> m_entries;  // The underlying vector of entries
    };
}
