#include "pch.h"
#include "CppUnitTest.h"

#include "TranspositionTable.h"
#include "TranspositionTableEntry.h"

#include "TestHelpers.h"

using namespace ChessEngine;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChessEngineTests
{
    TEST_CLASS(TranspositionTableEntryTests)
    {
    public:

        TEST_METHOD(TestDefaultConstructor)
        {
            // Assert that entries created using the default constructor are considered as non-initialized
            TranspositionTableEntry entry;
            Assert::IsFalse(entry.IsInitialized());
        }

        TEST_METHOD(TestNonDefaultConstructor)
        {
            // Assert that entries created using the non-default constructor are considered as initialized
            TranspositionTableEntry entry(0, 0, 0, 0);
            Assert::IsTrue(entry.IsInitialized());
        }

        TEST_METHOD(TestCopyAssignment)
        {
            // Set the replacement strategy to never replace entries
            TranspositionTable::ReplacementStrategy = 
                [](const TranspositionTableEntry& entry1, const TranspositionTableEntry& entry2) -> bool
                {
                    return false;
                };

            // Test that uninitialized entries are always replaced
            TranspositionTableEntry entry1;
            TranspositionTableEntry entry2;
            entry1.SetHash(1);
            entry2.SetHash(2);
            entry1 = entry2;
            Assert::AreEqual(entry1, entry2);

            // Test that initialized entry is not replaced when using the 'never replace' strategy
            TranspositionTableEntry entry3(3, 0, 0, 0);
            TranspositionTableEntry entry4(4, 0, 0, 0);
            entry3 = entry4;
            Assert::AreNotEqual(entry3, entry4);

            // Set the replacement strategy to always replace entries
            TranspositionTable::ReplacementStrategy = 
                [](const TranspositionTableEntry& entry1, const TranspositionTableEntry& entry2) -> bool
                {
                    return true;
                };

            // Test that initialized entry is replaced when using the 'always replace' strategy
            entry3 = entry4;
            Assert::AreEqual(entry3, entry4);
        }
    };
}