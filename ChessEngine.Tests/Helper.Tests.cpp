#include "pch.h"
#include "CppUnitTest.h"

#include "Helper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChessEngineTests
{
    using namespace ChessEngine;
    using namespace ChessEngine::Helper;

    TEST_CLASS(HelperTests)
    {
    public:

        TEST_METHOD(TestRowFromSquare)
        {
            // Test that the RowFromSquare helper function works
            // No point in testing out of bounds cases as the function is inline
            // and does no checking for valid arguments as we can't throw
            Assert::AreEqual(RowFromSquare(0), Row(0));
            Assert::AreEqual(RowFromSquare(7), Row(0));
            Assert::AreEqual(RowFromSquare(56), Row(7));
            Assert::AreEqual(RowFromSquare(63), Row(7));
        }

        TEST_METHOD(TestColFromSquare)
        {
            // Test that the ColFromSquare helper function works
            // No point in testing out of bounds cases as the function is inline
            // and does no checking for valid arguments as we can't throw
            Assert::AreEqual(ColFromSquare(0), Row(0));
            Assert::AreEqual(ColFromSquare(7), Row(7));
            Assert::AreEqual(ColFromSquare(56), Row(0));
            Assert::AreEqual(ColFromSquare(63), Row(7));
        }

        TEST_METHOD(TestSquareFromRowAndCol)
        {
            // Test that the SquareFromRowAndCol helper function works
            // No point in testing out of bounds cases as the function is inline
            // and does no checking for valid arguments as we can't throw
            Assert::AreEqual(SquareFromRowAndCol(0, 0), Square(0));
            Assert::AreEqual(SquareFromRowAndCol(0, 7), Square(7));
            Assert::AreEqual(SquareFromRowAndCol(7, 0), Square(56));
            Assert::AreEqual(SquareFromRowAndCol(7, 7), Square(63));
        }

        TEST_METHOD(TestIsSquareWhite)
        {
            // Test that the IsSquareWhite helper function works
            Assert::IsFalse(IsSquareWhite(0));
            Assert::IsFalse(IsSquareWhite(63));
            Assert::IsTrue(IsSquareWhite(7));
            Assert::IsTrue(IsSquareWhite(56));

            Assert::IsFalse(IsSquareWhite(0, 0));
            Assert::IsFalse(IsSquareWhite(7, 7));
            Assert::IsTrue(IsSquareWhite(0, 7));
            Assert::IsTrue(IsSquareWhite(7, 0));
        }

        TEST_METHOD(TestSquareFromString)
        {
            // Test that the SquareFromString helper function works
            Assert::AreEqual(Square(0), SquareFromString("a1"));
            Assert::AreEqual(Square(56), SquareFromString("a8"));
            Assert::AreEqual(Square(7), SquareFromString("h1"));
            Assert::AreEqual(Square(63), SquareFromString("h8"));
            Assert::AreEqual(Square(27), SquareFromString("d4"));
            Assert::AreEqual(Square(28), SquareFromString("e4"));
            Assert::AreEqual(Square(35), SquareFromString("d5"));
            Assert::AreEqual(Square(36), SquareFromString("e5"));
        }

        TEST_METHOD(TestStringFromSquare)
        {
            // Test that the SquareFromString helper function works
            Assert::AreEqual(std::string("a1"), StringFromSquare(Square(0)));
            Assert::AreEqual(std::string("a8"), StringFromSquare(Square(56)));
            Assert::AreEqual(std::string("h1"), StringFromSquare(Square(7)));
            Assert::AreEqual(std::string("h8"), StringFromSquare(Square(63)));
            Assert::AreEqual(std::string("d4"), StringFromSquare(Square(27)));
            Assert::AreEqual(std::string("e4"), StringFromSquare(Square(28)));
            Assert::AreEqual(std::string("d5"), StringFromSquare(Square(35)));
            Assert::AreEqual(std::string("e5"), StringFromSquare(Square(36)));
        }
    };
}