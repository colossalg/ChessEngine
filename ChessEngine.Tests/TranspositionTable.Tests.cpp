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
        
        TEST_METHOD(TestGetValidAndInvalidHashes)
        {
            TranspositionTable table(10);
            table.InsertEntry(TranspositionTableEntry(1U, 0, 0, Move()));

            // Assert that if you try to get an entry with a hash that does exist in the table it returns a valid pointer
            Assert::IsTrue(table.GetEntry(1U) != nullptr);

            // Assert that if you try to get an entry with a hash that does not exist in the table it returns nullptr
            Assert::IsTrue(table.GetEntry(2U) == nullptr);
        }

        TEST_METHOD(TestNumEntriesCantExceedMaxEntries)
        {
            TranspositionTable table(10);

            // Keep inserting entries, far above the max number of entries that can be in the table
            for (unsigned int i = 0; i < 100; i++)
            {
                table.InsertEntry(TranspositionTableEntry(i, 0, 0, Move()));
            }

            // Assert that the entries wrapped just as expected
            for (unsigned int i = 90; i < 100; i++)
            {
                TranspositionTableEntry* entry = table.GetEntry(i);
                Assert::IsTrue(entry != nullptr);
                Assert::AreEqual(TranspositionTableEntry(i, 0, 0, Move()), *entry);
            }
        }
    };
}