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
            TranspositionTableEntry entry(0, 0, 0, Move());
            Assert::IsTrue(entry.IsInitialized());
        }
    };
}