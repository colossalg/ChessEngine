#include "pch.h"
#include "CppUnitTest.h"

#include "BoardHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChessEngineTests
{
	TEST_CLASS(BoardHelperTests)
	{
	public:

		TEST_METHOD(TestRowFromSquare)
		{
			using namespace ChessEngine;
			using namespace ChessEngine::BoardHelper;

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
			using namespace ChessEngine;
			using namespace ChessEngine::BoardHelper;

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
			using namespace ChessEngine;
			using namespace ChessEngine::BoardHelper;

			// Test that the SquareFromRowAndCol helper function works
			// No point in testing out of bounds cases as the function is inline
			// and does no checking for valid arguments as we can't throw
			Assert::AreEqual(SquareFromRowAndCol(0, 0), Square(0));
			Assert::AreEqual(SquareFromRowAndCol(0, 7), Square(7));
			Assert::AreEqual(SquareFromRowAndCol(7, 0), Square(56));
			Assert::AreEqual(SquareFromRowAndCol(7, 7), Square(63));
		}
	};
}