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
	};
}