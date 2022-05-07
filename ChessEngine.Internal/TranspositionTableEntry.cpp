#include "pch.h"

#include "TranspositionTableEntry.h"
#include "TranspositionTable.h"

namespace ChessEngine
{
    TranspositionTableEntry::TranspositionTableEntry(
        unsigned int hash,
        unsigned char depthFromRoot,
        unsigned char depthToLeaves,
        int eval
    ):
        m_hash(hash),
        m_initialized(true),
        m_depthFromRoot(depthFromRoot),
        m_depthToLeaves(depthToLeaves),
        m_eval(eval)
    {}

    void TranspositionTableEntry::operator=(const TranspositionTableEntry& other)
    {
        if (!IsInitialized() || TranspositionTable::ReplacementStrategy(*this, other))
        {
            m_hash = other.m_hash;
            m_initialized = other.m_initialized;
            m_depthFromRoot = other.m_depthFromRoot;
            m_depthToLeaves = other.m_depthToLeaves;
            m_eval = other.m_eval;
        }
    }

    bool TranspositionTableEntry::operator==(const TranspositionTableEntry& other) const
    {
        return (
            m_hash == other.m_hash &&
            m_initialized == other.m_initialized &&
            m_depthFromRoot == other.m_depthFromRoot &&
            m_depthToLeaves == other.m_depthToLeaves &&
            m_eval == other.m_eval
            );
    }

    bool TranspositionTableEntry::operator!=(const TranspositionTableEntry& other) const
    { 
        return !(*this == other);
    }
}