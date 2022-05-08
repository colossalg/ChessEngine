#include "pch.h"

#include <optional>

#include "TranspositionTable.h"

namespace ChessEngine
{
    std::function<bool(const TranspositionTableEntry&, const TranspositionTableEntry&)> TranspositionTable::ReplacementStrategy = 
            [](const TranspositionTableEntry& older, const TranspositionTableEntry& newer) -> bool
            {
                // TODO -- Come up with a better replacement strategy than this
                return newer.GetDepth() > older.GetDepth();
            };

    TranspositionTable::TranspositionTable(size_t maxEntries)
        : m_entries(maxEntries)
    {
    }

    TranspositionTableEntry* TranspositionTable::GetEntry(unsigned int hash)
    {
        const unsigned int index = hash % m_entries.size();

        return ((m_entries[index].GetHash() == hash) ? &m_entries[index] : nullptr);
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