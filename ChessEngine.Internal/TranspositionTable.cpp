#include "pch.h"

#include "TranspositionTable.h"

namespace ChessEngine
{
    std::function<bool(const TranspositionTableEntry&, const TranspositionTableEntry&)> TranspositionTable::ReplacementStrategy = 
            [](const TranspositionTableEntry& older, const TranspositionTableEntry& newer) -> bool
            {
                // TODO -- Come up with a better replacement strategy than this
                return true;
            };

    TranspositionTable::TranspositionTable(size_t maxEntries)
        : m_entries(maxEntries)
    {
    }

    TranspositionTableEntry& TranspositionTable::GetEntry(unsigned int hash)
    {
        return m_entries[hash % m_entries.size()];
    }

    void TranspositionTable::InsertEntry(const TranspositionTableEntry& entry)
    {
        const unsigned int index = entry.GetHash() % m_entries.size();

        if (!m_entries[index].IsInitialized() || ReplacementStrategy(m_entries[index], entry))
        {
            m_entries[index] = entry;
        }
    }
}