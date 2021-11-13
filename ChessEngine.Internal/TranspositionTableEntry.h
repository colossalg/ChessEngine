#pragma once

namespace ChessEngine
{
	class TranspositionTableEntry
	{
	public:

		TranspositionTableEntry(
			unsigned int hash,
			unsigned int depthFromRoot,
			unsigned int depthToLeaves,
			int eval);

		void operator=(const TranspositionTableEntry& other);

	private:

		unsigned int m_hash;			// The Zobrist hash for the position corresponding to this entry
		unsigned int m_depthFromRoot;	// The depth from the root node the position corresponding to this entry was last searched at
		unsigned int m_depthToLeaves;	// The depth to the leaf nodes the position corresponding to this entry was last searched at
		int m_eval;						// The evaluation of the position corresponding to this entry
	};
}
