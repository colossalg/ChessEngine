#pragma once

#include "Move.h"

namespace ChessEngine
{
    class TranspositionTableEntry
    {
    public:

        // Create a new uninitialized/default constructed table entry
        TranspositionTableEntry() = default;

        // Create a new table entry
        TranspositionTableEntry(
            unsigned int hash,
            unsigned char depth,
            int eval,
            Move move);

        // Compare two table entries
        bool operator==(const TranspositionTableEntry& other) const;
        bool operator!=(const TranspositionTableEntry& other) const;

        // Get/Set the Zobrist hash for the position corresponding to this entry
        unsigned int GetHash() const { return m_hash; }
        void SetHash(const unsigned int hash) { m_hash = hash; }

        // Get whether this entry has been initialized yet or is still empty/default constructed
        bool IsInitialized() const { return m_initialized; }

        // Get/Set the depth of the last evaluation of the position corresponding to this entry
        unsigned char GetDepth() const { return m_depth; }
        void SetDepth(const unsigned char depth) { m_depth = depth; }

        // Get/Set the value of the last evaluation of the position corresponding to this entry
        int GetEval() const { return m_eval; }
        void SetEval(const int eval) { m_eval = eval; }

        // Get/Set the value of the move corresponding to eval
        Move GetMove() const { return m_move; }
        void SetMove(const Move move) { m_move = move; }

    private:

        unsigned int m_hash = 0U;   // The Zobrist hash for the position corresponding to this entry
        bool m_initialized = false; // Whether this entry has been initialized yet or is still empty/default constructed
        unsigned char m_depth = 0U; // The depth of the last evaluation of the position corresponding to this entry
        int m_eval = 0;             // The value of the last evaluation of the position corresponding to this entry
        Move m_move;                // The move corresponding to eval
    };
}
