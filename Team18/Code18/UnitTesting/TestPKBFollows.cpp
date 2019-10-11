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
			PKB.setStmt("1", "read");
			PKB.setStmt("2", "read");
			PKB.setStmt("3", "call");
			PKB.setStmt("4", "assign");
			PKB.setStmt("5", "assign");
			PKB.setStmt("6", "while");
			PKB.setStmt("7", "assign");
			PKB.setStmt("8", "call");
			PKB.setStmt("9", "assign");
			PKB.setStmt("10", "if");
			PKB.setStmt("11", "assign");
			PKB.setStmt("12", "assign");
			PKB.setStmt("13", "assign");
			PKB.setStmt("14", "assign");
			PKB.setStmt("15", "assign");
			PKB.setStmt("16", "assign");
			PKB.setStmt("17", "assign");
			PKB.setStmt("18", "print");

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
			Assert::IsTrue(PKB.isFollows("1", "2"));
			Assert::IsTrue(PKB.isFollows("2", "3"));
			Assert::IsTrue(PKB.isFollows("4", "5"));
			Assert::IsTrue(PKB.isFollows("5", "6"));
			Assert::IsTrue(PKB.isFollows("6", "10"));
			Assert::IsTrue(PKB.isFollows("7", "8"));
			Assert::IsTrue(PKB.isFollows("8", "9"));
			Assert::IsTrue(PKB.isFollows("10", "13"));
			Assert::IsTrue(PKB.isFollows("13", "14"));
			Assert::IsTrue(PKB.isFollows("14", "15"));
			Assert::IsTrue(PKB.isFollows("16", "17"));
			Assert::IsTrue(PKB.isFollows("17", "18"));
		}
		TEST_METHOD(FollowsStarRelationship)
		{
			PKBFollows PKB;
			Assert::IsTrue(PKB.isFollowsT("1", "2"));
			Assert::IsTrue(PKB.isFollowsT("2", "3"));
			Assert::IsTrue(PKB.isFollowsT("4", "5"));
			Assert::IsTrue(PKB.isFollowsT("5", "6"));
			Assert::IsTrue(PKB.isFollowsT("6", "10"));
			Assert::IsTrue(PKB.isFollowsT("7", "8"));
			Assert::IsTrue(PKB.isFollowsT("8", "9"));
			Assert::IsTrue(PKB.isFollowsT("10", "13"));
			Assert::IsTrue(PKB.isFollowsT("13", "14"));
			Assert::IsTrue(PKB.isFollowsT("14", "15"));
			Assert::IsTrue(PKB.isFollowsT("16", "17"));
			Assert::IsTrue(PKB.isFollowsT("17", "18"));

			Assert::IsTrue(PKB.isFollowsT("1", "3"));
			Assert::IsTrue(PKB.isFollowsT("4", "6"));
			Assert::IsTrue(PKB.isFollowsT("7", "9"));
			Assert::IsTrue(PKB.isFollowsT("13", "15"));
			Assert::IsTrue(PKB.isFollowsT("16", "18"));
		}
		TEST_METHOD(FollowsGenericBoth)
		{
			PKBFollows PKB;
			TABLE actual, expected;
			
			actual = PKB.getFollows("assign", "print");
			expected = { {"17","18"} };
			Assert::IsTrue(actual == expected);
			
			actual = PKB.getFollows("assign", "read");
			Assert::IsTrue(actual.size() == 0);
			
			actual = PKB.getFollows("assign", "stmt");
			expected = { {"4","5"},{"5","6"},{"7","8"} ,{"13","14"},{"14","15"},{"16","17"},{"17","18"} };
			Assert::IsTrue(actual == expected);
			
		}
		TEST_METHOD(FollowsGenericLeft)
		{
			PKBFollows PKB;
			TABLE actual, expected;
			
			actual = PKB.getFollows("stmt", "18");
			expected = { {"17"} };
			Assert::IsTrue(actual == expected);
			
			actual = PKB.getFollows("assign", "2");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getFollows("assign", "5");
			expected = { {"4"} };
			Assert::IsTrue(actual == expected);
			
		}
		TEST_METHOD(FollowsGenericRight)
		{
			
			PKBFollows PKB;
			STMT_LIST actual, expected;

			actual = PKB.getFollows("13", "assign");
			expected = { {"14"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getFollows("2", "assign");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getFollows("5", "while");
			expected = { {"6"} };
			Assert::IsTrue(actual == expected);
			
		}
		TEST_METHOD(FollowsStarGenericBoth)
		{
			PKBFollows PKB;
			TABLE actual, expected;
			
			actual = PKB.getFollowsT("assign", "print");
			expected = { {"16","18"} ,{"17","18"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getFollowsT("assign", "read");
			Assert::IsTrue(actual.size() == 0);
			
			actual = PKB.getFollowsT("assign", "stmt");
			expected = { {"4","5"},{"4","6"},{"4","10"},{"4","13"},{"4","14"},{"4","15"},{"5","6"},{"5","10"},{"5","13"},{"5","14"},{"5","15"},{"7","8"},{"7","9"},{"13","14"},{"13","15"},{"14","15"},{"16","17"},{"16","18"},{"17","18"} };
			Assert::IsTrue(actual == expected);
			
			actual = PKB.getFollowsT("stmt", "stmt");
			expected = { {"1","2"},{"1","3"},{"2","3"},{"4","5"},{"4","6"},{"5","6"},{"7","8"},{"7","9"},{"8","9"},{"13","14"},
			{"13","15"},{"14","15"},{"16","17"},{"16","18"},{"17","18"},
			{"4","10"},{"4","13"},{"4","14"},{"4","15"},
			{"5","10"},{"5","13"},{"5","14"},{"5","15"},
			{"6","10"},{"6","13"},{"6","14"},{"6","15"},
			{"10","13"},{"10","14"},{"10","15"}
			};
			Assert::IsTrue(actual == expected);

			//actual = PKB.getAllFollowedByFollowsStarStmt("stmt", "stmt");
			//Assert::IsTrue(actual.size() == 0);
		}
		TEST_METHOD(FollowsStarGenericLeft)
		{
			PKBFollows PKB;
			STMT_LIST actual, expected;

			actual = PKB.getFollowsT("assign", "18");
			expected = { {"16"}, {"17"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getFollowsT("assign", "2");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getFollowsT("read", "3");
			expected = { {"1"}, {"2"} };
			Assert::IsTrue(actual == expected);

		}

		TEST_METHOD(FollowsStarGenericRight)
		{
			PKBFollows PKB;
			STMT_LIST actual, expected;

			actual = PKB.getFollowsT("13", "assign");
			expected = { {"14"},{"15"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getFollowsT("2", "assign");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getFollowsT("5", "while");
			expected = { {"6"} };
			Assert::IsTrue(actual == expected);
		}
	};
};


