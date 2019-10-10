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

			PKB.setFollows("1", "2");
			PKB.setFollows("2", "3");
			PKB.setFollows("4", "5");
			PKB.setFollows("5", "6");
			PKB.setFollows("6", "10");
			PKB.setFollows("10", "13");
			PKB.setFollows("7", "8");
			PKB.setFollows("8", "9");
			PKB.setFollows("13", "14");
			PKB.setFollows("14", "15");
			PKB.setFollows("16", "17");
			PKB.setFollows("17", "18");

			DesignExtractor DesignExtractor;
			DesignExtractor.extractDesign();
		}
		TEST_METHOD(FollowsRelationship)
		{
			PKBFollows PKB;
			Assert::IsTrue(PKB.isFollowsS1StmtNoS2StmtNo("1", "2"));
			Assert::IsTrue(PKB.isFollowsS1StmtNoS2StmtNo("2", "3"));
			Assert::IsTrue(PKB.isFollowsS1StmtNoS2StmtNo("4", "5"));
			Assert::IsTrue(PKB.isFollowsS1StmtNoS2StmtNo("5", "6"));
			Assert::IsTrue(PKB.isFollowsS1StmtNoS2StmtNo("6", "10"));
			Assert::IsTrue(PKB.isFollowsS1StmtNoS2StmtNo("7", "8"));
			Assert::IsTrue(PKB.isFollowsS1StmtNoS2StmtNo("8", "9"));
			Assert::IsTrue(PKB.isFollowsS1StmtNoS2StmtNo("10", "13"));
			Assert::IsTrue(PKB.isFollowsS1StmtNoS2StmtNo("13", "14"));
			Assert::IsTrue(PKB.isFollowsS1StmtNoS2StmtNo("14", "15"));
			Assert::IsTrue(PKB.isFollowsS1StmtNoS2StmtNo("16", "17"));
			Assert::IsTrue(PKB.isFollowsS1StmtNoS2StmtNo("17", "18"));
		}
		TEST_METHOD(FollowsStarRelationship)
		{
			PKBFollows PKB;
			Assert::IsTrue(PKB.isFollowsStarRelationship("1", "2"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("2", "3"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("4", "5"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("5", "6"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("6", "10"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("7", "8"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("8", "9"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("10", "13"));
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
			
			actual = PKB.getFollowsS1S2("ASSIGN", "PRINT");
			expected = { {"17","18"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getFollowsS1S2("ASSIGN", "READ");
			Assert::IsTrue(actual.size() == 0);
			
			actual = PKB.getFollowsS1S2("ASSIGN", "STATEMENT");
			expected = { {"4","5"},{"5","6"},{"7","8"} ,{"13","14"},{"14","15"},{"16","17"},{"17","18"} };
			Assert::IsTrue(actual == expected);
			
			actual = PKB.getFollowsS1S2("_", "_");
			expected = { {"1","2"},{"2","3"} ,{"4","5"} ,{"5","6"},{"6","10"},{"7","8"},{"8","9"},{"10","13"},{"13","14"},{"14","15"},{"16","17"},{"17","18"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getFollowsS1S2("STATEMENT", "STATEMENT");
			Assert::IsTrue(actual.size() == 0);
		}
		TEST_METHOD(FollowsGenericLeft)
		{
			PKBFollows PKB;
			STMT_LIST actual, expected;

			actual = PKB.getFollowsS1WithS2StmtNo("ASSIGN", "18");
			expected = { {"17"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getFollowsS1WithS2StmtNo("ASSIGN", "2");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getFollowsS1WithS2StmtNo("ASSIGN", "5");
			expected = { {"4"} };
			Assert::IsTrue(actual == expected);
		}
		TEST_METHOD(FollowsGenericRight)
		{
			PKBFollows PKB;
			STMT_LIST actual, expected;

			actual = PKB.getFollowsS2WithS1StmtNo("13", "ASSIGN");
			expected = { {"14"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getFollowsS2WithS1StmtNo("2", "ASSIGN");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getFollowsS2WithS1StmtNo("5", "WHILE");
			expected = { {"6"} };
			Assert::IsTrue(actual == expected);
		}
		TEST_METHOD(FollowsSame)
		{
			PKBFollows PKB;
			TABLE actual, expected;

			actual = PKB.getFollowsS1S2Same("ASSIGN", "ASSIGN");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getFollowsS1S2Same("STATEMENT", "STATEMENT");
			Assert::IsTrue(actual.size() == 0);
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
			expected = { {"4","5"},{"4","6"},{"4","10"},{"4","13"},{"4","14"},{"4","15"},{"5","6"},{"5","10"},{"5","13"},{"5","14"},{"5","15"},{"7","8"},{"7","9"},{"13","14"},{"13","15"},{"14","15"},{"16","17"},{"16","18"},{"17","18"} };
			Assert::IsTrue(actual == expected);
			
			actual = PKB.getAllFollowedByFollowsStarStmt("_", "_");
			expected = { {"1","2"},{"1","3"},{"2","3"},{"4","5"},{"4","6"},{"5","6"},{"7","8"},{"7","9"},{"8","9"},{"13","14"},
			{"13","15"},{"14","15"},{"16","17"},{"16","18"},{"17","18"},
			{"4","10"},{"4","13"},{"4","14"},{"4","15"},
			{"5","10"},{"5","13"},{"5","14"},{"5","15"},
			{"6","10"},{"6","13"},{"6","14"},{"6","15"},
			{"10","13"},{"10","14"},{"10","15"}
			};
			Assert::IsTrue(actual == expected);

			//actual = PKB.getAllFollowedByFollowsStarStmt("STATEMENT", "STATEMENT");
			//Assert::IsTrue(actual.size() == 0);
		}
		TEST_METHOD(FollowsStarGenericLeft)
		{
			PKBFollows PKB;
			STMT_LIST actual, expected;

			actual = PKB.getAllFollowedByStarStmt("ASSIGN", "18");
			expected = { {"16"}, {"17"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getAllFollowedByStarStmt("ASSIGN", "2");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getAllFollowedByStarStmt("READ", "3");
			expected = { {"1"}, {"2"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getAllFollowedByStarStmt("_", "3");
			expected = { {"1"}, {"2"} };
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(FollowsStarGenericRight)
		{
			PKBFollows PKB;
			STMT_LIST actual, expected;

			actual = PKB.getAllFollowsStarStmt("13", "ASSIGN");
			expected = { {"14"},{"15"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getAllFollowsStarStmt("2", "ASSIGN");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getAllFollowsStarStmt("5", "WHILE");
			expected = { {"6"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getAllFollowsStarStmt("1", "_");
			expected = { {"3"}, {"2"} };
			Assert::IsTrue(actual == expected);
		}
	};
};


