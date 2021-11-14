#include "pch.h"
#include "CppUnitTest.h"

#include "TranspositionTable.h"
#include "TranspositionTableEntry.h"

#include "TestHelpers.h"

using namespace ChessEngine;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChessEngineTests
{
	TEST_CLASS(TranspositionTableTests)
	{
	public:
		
		TEST_METHOD(TestUninitializedEntry)
		{
			TranspositionTable table(10);
			table[1] = TranspositionTableEntry(1, 0, 0, 0);

			// Assert that if you access an entry that has not been initialized, it reports that it is uninitialized
			Assert::IsFalse(table[0].IsInitialized());

			// Assert that if you access an entry that has been initialized, it reports that it is initialized
			Assert::IsTrue( table[1].IsInitialized());
		}

		TEST_METHOD(TestNumEntriesCantExceedMaxEntries)
		{
			TranspositionTable table(10);

			// Keep inserting entries, far above the max number of entries that can be in the table
			for (unsigned int i = 0; i < 100; i++)
			{
				table[i] = TranspositionTableEntry(i, 0, 0, 0);
			}

			// Assert that the max entries and number of entries are equal
			Assert::AreEqual(table.GetMaxEntries(), table.GetNumEntries());

			// Assert that the entries wrapped just as expected
			for (unsigned int i = 90; i < 100; i++)
			{
				Assert::AreEqual(TranspositionTableEntry(i, 0, 0, 0), table[i]);
			}
		}
	};
}