#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKB.h"
#include "PKBParent.h"
#include "DesignExtractor.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(PKBParentTest)
	{
	public:
		TEST_METHOD_INITIALIZE(PKB_START)
		{
			/**	SIMPLE program:

				procedure First {
				1.	read x;
				2.	read z;
				3.	call Second; }

				procedure Second {
				4.		x = 0;
				5.		i = 5;
				6.		while (i!=0) {
				7.			x = x + 2*y;
				8.			call Third;
				10.			if (x==1) then {
				11.				x = x +1; }
							else {
				12.				z = 2;}
				13.			i = i - 1; }
				14.		if (x==1) then {
				15.			x = x+1; }
						else {
				16.			z = 1; }
				17.		z = z + x + i;
				18.		y = z + 2;
				19.		x = x * y + z; }

					procedure Third {
				20.		z = 5;
				21.		v = z;
				22.		print v; }
		   */

			PKB PKB;
			PKB.clear();
			PKB.setStmt("1", "READ");
			PKB.setStmt("2", "READ");
			PKB.setStmt("3", "CALL");
			PKB.setStmt("4", "ASSIGN");
			PKB.setStmt("5", "ASSIGN");
			PKB.setStmt("6", "WHILE");
			PKB.setStmt("7", "ASSIGN");
			PKB.setStmt("8", "CALL");
			PKB.setStmt("9", "ASSIGN");
			PKB.setStmt("10", "IF");
			PKB.setStmt("11", "ASSIGN");
			PKB.setStmt("12", "ASSIGN");
			PKB.setStmt("13", "ASSIGN");
			PKB.setStmt("14", "IF");
			PKB.setStmt("15", "ASSIGN");
			PKB.setStmt("16", "ASSIGN");
			PKB.setStmt("17", "ASSIGN");
			PKB.setStmt("18", "ASSIGN");
			PKB.setStmt("19", "ASSIGN");
			PKB.setStmt("20", "ASSIGN");
			PKB.setStmt("21", "ASSIGN");
			PKB.setStmt("22", "PRINT");

			PKB.setParentRelation("6", "7");
			PKB.setParentRelation("6", "8");
			PKB.setParentRelation("6", "9");
			PKB.setParentRelation("6", "10");
			PKB.setParentRelation("10", "11");
			PKB.setParentRelation("10", "12");
			PKB.setParentRelation("14", "15");
			PKB.setParentRelation("14", "16");

			DesignExtractor DesignExtractor;
			DesignExtractor.extractDesign();
		}

		TEST_METHOD(ParentRelationship)
		{
			PKBParent PKB;
			Assert::IsTrue(PKB.isParentRelationship("6","7"));
			Assert::IsTrue(PKB.isParentRelationship("6", "8"));
			Assert::IsTrue(PKB.isParentRelationship("6", "9"));
			Assert::IsTrue(PKB.isParentRelationship("6", "10"));
			Assert::IsTrue(PKB.isParentRelationship("10", "11"));
			Assert::IsTrue(PKB.isParentRelationship("10", "12"));
			Assert::IsTrue(PKB.isParentRelationship("14", "15"));
			Assert::IsTrue(PKB.isParentRelationship("14", "16"));
		}

		TEST_METHOD(ParentStarRelationship)
		{
			PKBParent PKB;
			Assert::IsTrue(PKB.isParentStarRelationship("6", "7"));
			Assert::IsTrue(PKB.isParentStarRelationship("6", "8"));
			Assert::IsTrue(PKB.isParentStarRelationship("6", "9"));
			Assert::IsTrue(PKB.isParentStarRelationship("6", "10"));
			Assert::IsTrue(PKB.isParentStarRelationship("6", "11"));
			Assert::IsTrue(PKB.isParentStarRelationship("6", "12"));
			Assert::IsTrue(PKB.isParentStarRelationship("10", "11"));
			Assert::IsTrue(PKB.isParentStarRelationship("10", "12"));
			Assert::IsTrue(PKB.isParentStarRelationship("14", "15"));
			Assert::IsTrue(PKB.isParentStarRelationship("14", "16"));
		}

		TEST_METHOD(isParentExist)
		{
			PKBParent PKB;
			Assert::IsTrue(PKB.isParentExist("7"));
			Assert::IsTrue(PKB.isParentExist("8"));
			Assert::IsTrue(PKB.isParentExist("9"));
			Assert::IsTrue(PKB.isParentExist("11"));
			Assert::IsTrue(PKB.isParentExist("12"));
		}

		TEST_METHOD(ParentGenericBoth)
		{
			PKBParent PKB;
			TABLE actual, expected;

			actual = PKB.getAllParentChildStmt("IF", "ASSIGN");
			expected = { {"10","11"},{"10","12"},{"14","15"},{"14","16"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getAllParentChildStmt("ASSIGN", "READ");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getAllParentChildStmt("IF", "STATEMENT");
			expected = { {"10","11"},{"10","12"},{"14","15"},{"14","16"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getAllParentChildStmt("_", "_");
			expected = { {"6","7"},{"6","8"},{"6","9"},{"6","10"},{"10","11"},{"10","12"},{"14","15"},{"14","16"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getAllParentChildStmt("STATEMENT", "STATEMENT");
			Assert::IsTrue(actual.size() == 0);
		}

		TEST_METHOD(ParentGenericLeft)
		{
			PKBParent PKB;
			STMT_LIST actual, expected;

			actual = PKB.getAllParentStmt("IF", "15");
			expected = { {"14"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getAllParentStmt("ASSIGN", "2");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getAllParentStmt("WHILE", "9");
			expected = { {"6"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getAllParentStmt("_", "9");
			expected = { {"6"} };
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(ParentGenericRight)
		{
			PKBParent PKB;
			STMT_LIST actual, expected;

			actual = PKB.getAllChildStmt("14", "ASSIGN");
			expected = { {"15"}, {"16"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getAllChildStmt("2", "ASSIGN");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getAllChildStmt("6", "IF");
			expected = { {"10"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getAllChildStmt("6", "_");
			expected = { {"7"}, {"8"}, {"9"}, {"10"} };
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(ParentStarGenericBoth)
		{
			PKBParent PKB;
			TABLE actual, expected;

			actual = PKB.getAllParentChildStarStmt("WHILE", "ASSIGN");
			expected = { {"6","7"},{"6","9"},{"6","11"},{"6","12"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getAllParentChildStarStmt("ASSIGN", "READ");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getAllParentChildStarStmt("IF", "STATEMENT");
			expected = { {"10","11"},{"10","12"},{"14","15"},{"14","16"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getAllParentChildStarStmt("_", "_");
			expected = { {"6","7"},{"6","8"},{"6","9"},{"6","10"},{"6","11"},{"6","12"},{"10","11"},{"10","12"},{"14","15"},{"14","16"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getAllParentChildStarStmt("STATEMENT", "STATEMENT");
			Assert::IsTrue(actual.size() == 0);
		}

		TEST_METHOD(ParentStarGenericLeft)
		{
			PKBParent PKB;
			STMT_LIST actual, expected;

			actual = PKB.getAllParentStarStmt("IF", "15");
			expected = { {"14"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getAllParentStarStmt("ASSIGN", "2");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getAllParentStarStmt("WHILE", "9");
			expected = { {"6"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getAllParentStarStmt("_", "9");
			expected = { {"6"} };
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(ParentStarGenericRight)
		{
			PKBParent PKB;
			STMT_LIST actual, expected;

			actual = PKB.getAllChildStarStmt("14", "ASSIGN");
			expected = { {"15"}, {"16"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getAllChildStarStmt("2", "ASSIGN");
			Assert::IsTrue(actual.size() == 0);
			
			actual = PKB.getAllChildStarStmt("6", "ASSIGN");
			expected = { {"7"},{"9"},{"11"},{"12"} };
			Assert::IsTrue(actual == expected);
			
			actual = PKB.getAllChildStarStmt("6", "_");
			expected = { {"7"}, {"8"}, {"9"}, {"10"},  {"11"}, {"12"} };
			Assert::IsTrue(actual == expected);
			
		}
	};
};


