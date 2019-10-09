#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKBFollows.h"
#include "DesignExtractor.h"
#include "PKB.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(PKBFollowsTest)
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
				9.			i = i - 1; }
				10.		if (x==1) then {
				11.			x = x+1; }
						else {
				12.			z = 1; }
				13.		z = z + x + i;
				14.		y = z + 2;
				15.		x = x * y + z; }

					procedure Third {
				16.		z = 5;
				17.		v = z;
				18.		print v; }
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
			PKB.setStmt("14", "ASSIGN");
			PKB.setStmt("15", "ASSIGN");
			PKB.setStmt("16", "ASSIGN");
			PKB.setStmt("17", "ASSIGN");
			PKB.setStmt("18", "PRINT");

			PKB.setFollowsRelation("1", "2");
			PKB.setFollowsRelation("2", "3");
			PKB.setFollowsRelation("4", "5");
			PKB.setFollowsRelation("5", "6");
			PKB.setFollowsRelation("7", "8");
			PKB.setFollowsRelation("8", "9");
			PKB.setFollowsRelation("13", "14");
			PKB.setFollowsRelation("14", "15");
			PKB.setFollowsRelation("16", "17");
			PKB.setFollowsRelation("17", "18");

			DesignExtractor DesignExtractor;
			DesignExtractor.extractDesign();
		}
		TEST_METHOD(FollowsRelationship)
		{
			PKB PKB;
			Assert::IsTrue(PKB.isFollowsRelationship("1", "2"));
			Assert::IsTrue(PKB.isFollowsRelationship("2", "3"));
			Assert::IsTrue(PKB.isFollowsRelationship("4", "5"));
			Assert::IsTrue(PKB.isFollowsRelationship("5", "6"));
			Assert::IsTrue(PKB.isFollowsRelationship("7", "8"));
			Assert::IsTrue(PKB.isFollowsRelationship("8", "9"));
			Assert::IsTrue(PKB.isFollowsRelationship("13", "14"));
			Assert::IsTrue(PKB.isFollowsRelationship("14", "15"));
			Assert::IsTrue(PKB.isFollowsRelationship("16", "17"));
			Assert::IsTrue(PKB.isFollowsRelationship("17", "18"));
		}
		TEST_METHOD(FollowsStarRelationship)
		{
			PKB PKB;
			Assert::IsTrue(PKB.isFollowsStarRelationship("1", "2"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("2", "3"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("4", "5"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("5", "6"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("7", "8"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("8", "9"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("13", "14"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("14", "15"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("16", "17"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("17", "18"));

			Assert::IsTrue(PKB.isFollowsStarRelationship("1", "3"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("4", "6"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("7", "9"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("13", "15"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("16", "18"));
		}
		TEST_METHOD(FollowsGenericBoth)
		{
			PKBFollows PKB;
			TABLE actual, expected;
			
			actual = PKB.getAllFollowedByFollowsStmt("ASSIGN", "PRINT");
			expected = { {"17","18"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getAllFollowedByFollowsStmt("ASSIGN", "READ");
			Assert::IsTrue(actual.size() == 0);
			
			actual = PKB.getAllFollowedByFollowsStmt("ASSIGN", "STATEMENT");
			expected = { {"4","5"},{"5","6"},{"7","8"} ,{"13","14"},{"14","15"},{"16","17"},{"17","18"} };
			Assert::IsTrue(actual == expected);
			
			actual = PKB.getAllFollowedByFollowsStmt("_", "_");
			expected = { {"1","2"},{"2","3"} ,{"4","5"} ,{"5","6"},{"7","8"},{"8","9"},{"13","14"},{"14","15"},{"16","17"},{"17","18"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getAllFollowedByFollowsStmt("STATEMENT", "STATEMENT");
			Assert::IsTrue(actual.size() == 0);
		}
		TEST_METHOD(FollowsGenericLeft)
		{
			PKBFollows PKB;
			TABLE actual, expected;

			actual = PKB.getAllFollowedByStmt("ASSIGN", "18");
			expected = { {"17","18"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getAllFollowedByStmt("ASSIGN", "2");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getAllFollowedByStmt("ASSIGN", "5");
			expected = { {"4","5"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getAllFollowedByStmt("_", "2");
			expected = { {"1","2"}};
			Assert::IsTrue(actual == expected);
		}
		TEST_METHOD(FollowsGenericRight)
		{
			PKBFollows PKB;
			TABLE actual, expected;

			actual = PKB.getAllFollowsStmt("13", "ASSIGN");
			expected = { {"13","14"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getAllFollowsStmt("2", "ASSIGN");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getAllFollowsStmt("5", "WHILE");
			expected = { {"5","6"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getAllFollowsStmt("2", "_");
			expected = { {"2","3"} };
			Assert::IsTrue(actual == expected);
		}
		TEST_METHOD(FollowsStarGenericBoth)
		{
			PKBFollows PKB;
			TABLE actual, expected;

			actual = PKB.getAllFollowedByFollowsStarStmt("ASSIGN", "PRINT");
			expected = { {"16","18"} ,{"17","18"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getAllFollowedByFollowsStarStmt("ASSIGN", "READ");
			Assert::IsTrue(actual.size() == 0);
			
			actual = PKB.getAllFollowedByFollowsStarStmt("ASSIGN", "STATEMENT");
			expected = { {"4","5"},{"4","6"},{"5","6"},{"7","8"},{"7","9"},{"13","14"},{"13","15"},{"14","15"},{"16","17"},{"16","18"},{"17","18"} };
			Assert::IsTrue(actual == expected);
			
			actual = PKB.getAllFollowedByFollowsStarStmt("_", "_");
			expected = { {"1","2"},{"1","3"},{"2","3"},{"4","5"},{"4","6"},{"5","6"},{"7","8"},{"7","9"},{"8","9"},{"13","14"},{"13","15"},{"14","15"},{"16","17"},{"16","18"},{"17","18"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getAllFollowedByFollowsStarStmt("STATEMENT", "STATEMENT");
			Assert::IsTrue(actual.size() == 0);
		}
		TEST_METHOD(FollowsStarGenericLeft)
		{
			PKBFollows PKB;
			TABLE actual, expected;

			actual = PKB.getAllFollowedByStarStmt("ASSIGN", "18");
			expected = { {"16","18"}, {"17","18"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getAllFollowedByStarStmt("ASSIGN", "2");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getAllFollowedByStarStmt("READ", "3");
			expected = { {"1","3"}, {"2","3"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getAllFollowedByStarStmt("_", "3");
			expected = { {"1","3"}, {"2","3"} };
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(FollowsStarGenericRight)
		{
			PKBFollows PKB;
			TABLE actual, expected;

			actual = PKB.getAllFollowsStarStmt("13", "ASSIGN");
			expected = { {"13","14"},{"13","15"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getAllFollowsStarStmt("2", "ASSIGN");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getAllFollowsStarStmt("5", "WHILE");
			expected = { {"5","6"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getAllFollowsStarStmt("1", "_");
			expected = { {"1","3"}, {"1","2"} };
			Assert::IsTrue(actual == expected);
		}
	};
};


