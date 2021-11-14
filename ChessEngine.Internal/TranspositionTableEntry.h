#pragma once

namespace ChessEngine
{
	class TranspositionTableEntry
	{
	public:

		// Create a new uninitialized/default constructed table entry
		TranspositionTableEntry() = default;

		// Create a new table entry
		TranspositionTableEntry(
			unsigned long long hash,
			unsigned char depthFromRoot,
			unsigned char depthToLeaves,
			int eval);

		// Copy assignment, this uses the TranspositionTable's replacement strategy to determine whether to replace the fields of this entry with
		// those of the other entry and will not do anything if the replacement strategy decides that the other entry should not replace this one
		void operator=(const TranspositionTableEntry& other);

		// Compare two table entries
		bool operator==(const TranspositionTableEntry& other) const;
		bool operator!=(const TranspositionTableEntry& other) const;

		// Get/Set the Zobrist hash for the position corresponding to this entry
		unsigned long long GetHash() const { return m_hash; }
		void SetHash(const unsigned long long hash) { m_hash = hash; }

		// Get whether this entry has been initialized yet or is still empty/default constructed
		bool IsInitialized() const { return m_initialized; }

		// Get/Set the depth from the root node the position corresponding to this entry was last searched at
		unsigned char GetDepthFromRoot() const { return m_depthFromRoot; }
		void SetDepthFromRoot(const unsigned char depthFromRoot) { m_depthFromRoot = depthFromRoot; }

		// Get/Set the depth to the leaf nodes the position corresponding to this entry was last searched at
		unsigned char GetDepthToLeaves() const { return m_depthToLeaves; }
		void SetDepthToLeaves(const unsigned char depthToLeaves) { m_depthToLeaves = depthToLeaves; }

		// Get/Set the value of the last evaluation of the position corresponding to this entry
		int GetEval() const { return m_eval; }
		void SetEval(const int eval) { m_eval = eval; }

	private:

		unsigned long long m_hash = 0ULL;	// The Zobrist hash for the position corresponding to this entry
		bool m_initialized = false;			// Whether this entry has been initialized yet or is still empty/default constructed
		unsigned char m_depthFromRoot = 0U;	// The depth from the root node the position corresponding to this entry was last searched at
		unsigned char m_depthToLeaves = 0U;	// The depth to the leaf nodes the position corresponding to this entry was last searched at
		int m_eval = 0;						// The value of the last evaluation of the position corresponding to this entry
	};
}
