#include "pch.h"

#include "TranspositionTableEntry.h"
#include "TranspositionTable.h"

namespace ChessEngine
{
	TranspositionTableEntry::TranspositionTableEntry(
		unsigned int hash,
		unsigned int depthFromRoot,
		unsigned int depthToLeaves,
		int eval
	):
		m_hash(hash),
		m_depthFromRoot(depthFromRoot),
		m_depthToLeaves(depthToLeaves),
		m_eval(eval)
	{}

	void TranspositionTableEntry::operator=(const TranspositionTableEntry& other)
	{
		if (TranspositionTable::ReplacementStrategy(*this, other))
		{
			m_hash = other.m_hash;
			m_depthFromRoot = other.m_depthFromRoot;
			m_depthToLeaves = other.m_depthToLeaves;
			m_eval = other.m_eval;
		}
	}
}