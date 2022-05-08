#include "pch.h"

#include "TranspositionTableEntry.h"
#include "TranspositionTable.h"

namespace ChessEngine
{
    TranspositionTableEntry::TranspositionTableEntry(
        unsigned int hash,
        unsigned char depth,
        int eval,
        Move move):
        m_hash(hash),
        m_initialized(true),
        m_depth(depth),
        m_eval(eval),
        m_move(move)
    {}

    bool TranspositionTableEntry::operator==(const TranspositionTableEntry& other) const
    {
        return (
            m_hash == other.m_hash &&
            m_initialized == other.m_initialized &&
            m_depth == other.m_depth &&
            m_eval == other.m_eval &&
            m_move == other.m_move);
    }

    bool TranspositionTableEntry::operator!=(const TranspositionTableEntry& other) const
    { 
        return !(*this == other);
    }
}