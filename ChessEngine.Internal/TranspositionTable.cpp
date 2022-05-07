#include "pch.h"

#include <optional>

#include "TranspositionTable.h"

namespace ChessEngine
{
    std::function<bool(const TranspositionTableEntry&, const TranspositionTableEntry&)> TranspositionTable::ReplacementStrategy = 
            [](const TranspositionTableEntry& entry1, const TranspositionTableEntry& entry2) -> bool
            {
                // TODO -- Come up with a better replacement strategy than this
                return true;
            };

    TranspositionTable::TranspositionTable(size_t maxEntries):
        m_maxEntries(maxEntries)
    {
    }

    TranspositionTableEntry& TranspositionTable::operator[](unsigned int hash)
    {
        return m_table[hash % m_maxEntries];
    }
}