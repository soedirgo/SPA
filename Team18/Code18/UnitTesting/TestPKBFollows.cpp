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
		//Follows (_,_)
		TEST_METHOD(isFollowsAnyAny)
		{
			PKBFollows PKB;
			Assert::IsTrue(PKB.isFollowsAnyAny());
		}
		//Follows (_,2)
		TEST_METHOD(isFollowsAnyIdent)
		{
			PKBFollows PKB;
			Assert::IsTrue(PKB.isFollowsAnyIdent("2"));
			Assert::IsTrue(PKB.isFollowsAnyIdent("3"));
			Assert::IsTrue(PKB.isFollowsAnyIdent("5"));
			Assert::IsTrue(PKB.isFollowsAnyIdent("6"));
			Assert::IsTrue(PKB.isFollowsAnyIdent("8"));
			Assert::IsTrue(PKB.isFollowsAnyIdent("9"));
			Assert::IsTrue(PKB.isFollowsAnyIdent("10"));
			Assert::IsTrue(PKB.isFollowsAnyIdent("13"));
			Assert::IsTrue(PKB.isFollowsAnyIdent("14"));
			Assert::IsTrue(PKB.isFollowsAnyIdent("15"));
			Assert::IsTrue(PKB.isFollowsAnyIdent("17"));
			Assert::IsTrue(PKB.isFollowsAnyIdent("18"));

			Assert::IsFalse(PKB.isFollowsAnyIdent("4"));
			Assert::IsFalse(PKB.isFollowsAnyIdent("7"));
			Assert::IsFalse(PKB.isFollowsAnyIdent("11"));
			Assert::IsFalse(PKB.isFollowsAnyIdent("12"));
			Assert::IsFalse(PKB.isFollowsAnyIdent("16"));
		}
		//Follows (1,_)
		TEST_METHOD(isFollowsIdentAny)
		{
			PKBFollows PKB;
			Assert::IsTrue(PKB.isFollowsIdentAny("1"));
			Assert::IsTrue(PKB.isFollowsIdentAny("2"));
			Assert::IsTrue(PKB.isFollowsIdentAny("4"));
			Assert::IsTrue(PKB.isFollowsIdentAny("5"));
			Assert::IsTrue(PKB.isFollowsIdentAny("6"));
			Assert::IsTrue(PKB.isFollowsIdentAny("10"));
			Assert::IsTrue(PKB.isFollowsIdentAny("7"));
			Assert::IsTrue(PKB.isFollowsIdentAny("8"));
			Assert::IsTrue(PKB.isFollowsIdentAny("13"));
			Assert::IsTrue(PKB.isFollowsIdentAny("14"));
			Assert::IsTrue(PKB.isFollowsIdentAny("16"));
			Assert::IsTrue(PKB.isFollowsIdentAny("17"));

			Assert::IsFalse(PKB.isFollowsIdentAny("3"));
			Assert::IsFalse(PKB.isFollowsIdentAny("9"));
			Assert::IsFalse(PKB.isFollowsIdentAny("11"));
			Assert::IsFalse(PKB.isFollowsIdentAny("12"));
			Assert::IsFalse(PKB.isFollowsIdentAny("15"));
			Assert::IsFalse(PKB.isFollowsIdentAny("18"));
		}
		//Follows (1,2)
		TEST_METHOD(isFollowsIdentIdent)
		{
			PKBFollows PKB;
			Assert::IsTrue(PKB.isFollowsIdentIdent("1", "2"));
			Assert::IsTrue(PKB.isFollowsIdentIdent("2", "3"));
			Assert::IsTrue(PKB.isFollowsIdentIdent("4", "5"));
			Assert::IsTrue(PKB.isFollowsIdentIdent("5", "6"));
			Assert::IsTrue(PKB.isFollowsIdentIdent("6", "10"));
			Assert::IsTrue(PKB.isFollowsIdentIdent("7", "8"));
			Assert::IsTrue(PKB.isFollowsIdentIdent("8", "9"));
			Assert::IsTrue(PKB.isFollowsIdentIdent("10", "13"));
			Assert::IsTrue(PKB.isFollowsIdentIdent("13", "14"));
			Assert::IsTrue(PKB.isFollowsIdentIdent("14", "15"));
			Assert::IsTrue(PKB.isFollowsIdentIdent("16", "17"));
			Assert::IsTrue(PKB.isFollowsIdentIdent("17", "18"));
		}
		//Follows* (_,_)
		TEST_METHOD(isFollowsTAnyAny)
		{
			PKBFollows PKB;
			Assert::IsTrue(PKB.isFollowsTAnyAny());
		}
		//Follows* (_,2)
		TEST_METHOD(isFollowsTAnyIdent)
		{
			PKBFollows PKB;
			Assert::IsTrue(PKB.isFollowsTAnyIdent("2"));
			Assert::IsTrue(PKB.isFollowsTAnyIdent("3"));
			Assert::IsTrue(PKB.isFollowsTAnyIdent("5"));
			Assert::IsTrue(PKB.isFollowsTAnyIdent("6"));
			Assert::IsTrue(PKB.isFollowsTAnyIdent("8"));
			Assert::IsTrue(PKB.isFollowsTAnyIdent("9"));
			Assert::IsTrue(PKB.isFollowsTAnyIdent("10"));
			Assert::IsTrue(PKB.isFollowsTAnyIdent("13"));
			Assert::IsTrue(PKB.isFollowsTAnyIdent("14"));
			Assert::IsTrue(PKB.isFollowsTAnyIdent("15"));
			Assert::IsTrue(PKB.isFollowsTAnyIdent("17"));
			Assert::IsTrue(PKB.isFollowsTAnyIdent("18"));

			Assert::IsFalse(PKB.isFollowsTAnyIdent("4"));
			Assert::IsFalse(PKB.isFollowsTAnyIdent("7"));
			Assert::IsFalse(PKB.isFollowsTAnyIdent("11"));
			Assert::IsFalse(PKB.isFollowsTAnyIdent("12"));
			Assert::IsFalse(PKB.isFollowsTAnyIdent("16"));
		}
		//Follows* (1,_)
		TEST_METHOD(isFollowsTIdentAny)
		{
			PKBFollows PKB;
			Assert::IsTrue(PKB.isFollowsTIdentAny("1"));
			Assert::IsTrue(PKB.isFollowsTIdentAny("2"));
			Assert::IsTrue(PKB.isFollowsTIdentAny("4"));
			Assert::IsTrue(PKB.isFollowsTIdentAny("5"));
			Assert::IsTrue(PKB.isFollowsTIdentAny("6"));
			Assert::IsTrue(PKB.isFollowsTIdentAny("10"));
			Assert::IsTrue(PKB.isFollowsTIdentAny("7"));
			Assert::IsTrue(PKB.isFollowsTIdentAny("8"));
			Assert::IsTrue(PKB.isFollowsTIdentAny("13"));
			Assert::IsTrue(PKB.isFollowsTIdentAny("14"));
			Assert::IsTrue(PKB.isFollowsTIdentAny("16"));
			Assert::IsTrue(PKB.isFollowsTIdentAny("17"));

			Assert::IsFalse(PKB.isFollowsTIdentAny("3"));
			Assert::IsFalse(PKB.isFollowsTIdentAny("9"));
			Assert::IsFalse(PKB.isFollowsTIdentAny("11"));
			Assert::IsFalse(PKB.isFollowsTIdentAny("12"));
			Assert::IsFalse(PKB.isFollowsTIdentAny("15"));
			Assert::IsFalse(PKB.isFollowsTIdentAny("18"));
		}
		//Follows*(1,2)
		TEST_METHOD(isFollowsTIdentIdent)
		{
			PKBFollows PKB;
			Assert::IsTrue(PKB.isFollowsTIdentIdent("1", "2"));
			Assert::IsTrue(PKB.isFollowsTIdentIdent("2", "3"));
			Assert::IsTrue(PKB.isFollowsTIdentIdent("4", "5"));
			Assert::IsTrue(PKB.isFollowsTIdentIdent("5", "6"));
			Assert::IsTrue(PKB.isFollowsTIdentIdent("6", "10"));
			Assert::IsTrue(PKB.isFollowsTIdentIdent("7", "8"));
			Assert::IsTrue(PKB.isFollowsTIdentIdent("8", "9"));
			Assert::IsTrue(PKB.isFollowsTIdentIdent("10", "13"));
			Assert::IsTrue(PKB.isFollowsTIdentIdent("13", "14"));
			Assert::IsTrue(PKB.isFollowsTIdentIdent("14", "15"));
			Assert::IsTrue(PKB.isFollowsTIdentIdent("16", "17"));
			Assert::IsTrue(PKB.isFollowsTIdentIdent("17", "18"));

			Assert::IsTrue(PKB.isFollowsTIdentIdent("1", "3"));
			Assert::IsTrue(PKB.isFollowsTIdentIdent("4", "6"));
			Assert::IsTrue(PKB.isFollowsTIdentIdent("7", "9"));
			Assert::IsTrue(PKB.isFollowsTIdentIdent("13", "15"));
			Assert::IsTrue(PKB.isFollowsTIdentIdent("16", "18"));
		}
		//Follows(_, s)
		TEST_METHOD(getFollowsAnyEnt)
		{
			PKBFollows PKB;
			TABLE actual, expected;

			actual = PKB.getFollowsAnyEnt("assign");
			expected = { {"5"},{"9"},{"13"},{"14"},{"15"},{"17"}};
			Assert::IsTrue(actual == expected);

			actual = PKB.getFollowsAnyEnt("print");
			expected = { {"18"} };
			Assert::IsTrue(actual == expected);

		}
		//Follows(_, s)
		TEST_METHOD(getFollowsEntAny)
		{
			PKBFollows PKB;
			TABLE actual, expected;

			actual = PKB.getFollowsEntAny("assign");
			expected = { {"4"},{"5"}, {"7"},{"13"},{"14"},{"16"} ,{"17"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getFollowsEntAny("print");
			Assert::IsTrue(actual.size() == 0);

		}
		//Follows(s,s)
		TEST_METHOD(getFollowsEntEnt)
		{
			PKBFollows PKB;
			TABLE actual, expected;
			
			actual = PKB.getFollowsEntEnt("assign", "print");
			expected = { {"17","18"} };
			Assert::IsTrue(actual == expected);
			
			actual = PKB.getFollowsEntEnt("assign", "read");
			Assert::IsTrue(actual.size() == 0);
			
			actual = PKB.getFollowsEntEnt("assign", "stmt");
			expected = { {"4","5"},{"5","6"},{"7","8"} ,{"13","14"},{"14","15"},{"16","17"},{"17","18"} };
			Assert::IsTrue(actual == expected);
			
		}
		//Follows(s,2)
		TEST_METHOD(getFollowsEntIdent)
		{
			PKBFollows PKB;
			TABLE actual, expected;
			
			actual = PKB.getFollowsEntIdent("stmt", "18");
			expected = { {"17"} };
			Assert::IsTrue(actual == expected);
			
			actual = PKB.getFollowsEntIdent("assign", "2");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getFollowsEntIdent("assign", "5");
			expected = { {"4"} };
			Assert::IsTrue(actual == expected);
			
		}
		//Follows(2,s)
		TEST_METHOD(getFollowsIdentEnt)
		{
			
			PKBFollows PKB;
			STMT_LIST actual, expected;

			actual = PKB.getFollowsIdentEnt("13", "assign");
			expected = { {"14"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getFollowsIdentEnt("2", "assign");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getFollowsIdentEnt("5", "while");
			expected = { {"6"} };
			Assert::IsTrue(actual == expected);
			
		}
		//Follows*(_, s)
		TEST_METHOD(getFollowsTAnyEnt)
		{
			PKBFollows PKB;
			TABLE actual, expected;

			actual = PKB.getFollowsTAnyEnt("assign");
			expected = { {"5"},{"9"},{"13"},{"14"},{"15"},{"17"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getFollowsTAnyEnt("print");
			expected = { {"18"} };
			Assert::IsTrue(actual == expected);

		}
		//Follows*(_, s)
		TEST_METHOD(getFollowsTEntAny)
		{
			PKBFollows PKB;
			TABLE actual, expected;

			actual = PKB.getFollowsTEntAny("assign");
			expected = { {"4"},{"5"}, {"7"},{"13"},{"14"},{"16"} ,{"17"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getFollowsTEntAny("print");
			Assert::IsTrue(actual.size() == 0);

		}
		//Follows*(s,s)
		TEST_METHOD(getFollowsTEntEnt)
		{
			PKBFollows PKB;
			TABLE actual, expected;
			
			actual = PKB.getFollowsTEntEnt("assign", "print");
			expected = { {"16","18"} ,{"17","18"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getFollowsTEntEnt("assign", "read");
			Assert::IsTrue(actual.size() == 0);
			
			actual = PKB.getFollowsTEntEnt("assign", "stmt");
			expected = { {"4","5"},{"4","6"},{"4","10"},{"4","13"},{"4","14"},{"4","15"},{"5","6"},{"5","10"},{"5","13"},{"5","14"},{"5","15"},{"7","8"},{"7","9"},{"13","14"},{"13","15"},{"14","15"},{"16","17"},{"16","18"},{"17","18"} };
			Assert::IsTrue(actual == expected);
			
			actual = PKB.getFollowsTEntEnt("stmt", "stmt");
			expected = { {"1","2"},{"1","3"},{"2","3"},{"4","5"},{"4","6"},{"5","6"},{"7","8"},{"7","9"},{"8","9"},{"13","14"},
			{"13","15"},{"14","15"},{"16","17"},{"16","18"},{"17","18"},
			{"4","10"},{"4","13"},{"4","14"},{"4","15"},
			{"5","10"},{"5","13"},{"5","14"},{"5","15"},
			{"6","10"},{"6","13"},{"6","14"},{"6","15"},
			{"10","13"},{"10","14"},{"10","15"}
			};

			Assert::IsTrue(actual == expected);
		}
		//Follows*(s,1)
		TEST_METHOD(getFollowsTEntIdent)
		{
			PKBFollows PKB;
			STMT_LIST actual, expected;

			actual = PKB.getFollowsTEntIdent("assign", "18");
			expected = { {"16"}, {"17"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getFollowsTEntIdent("assign", "2");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getFollowsTEntIdent("read", "3");
			expected = { {"1"}, {"2"} };
			Assert::IsTrue(actual == expected);

		}
		//Follows*(1,s)
		TEST_METHOD(getFollowsTIdentEnt)
		{
			PKBFollows PKB;
			STMT_LIST actual, expected;

			actual = PKB.getFollowsTIdentEnt("13", "assign");
			expected = { {"14"},{"15"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getFollowsTIdentEnt("2", "assign");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getFollowsTIdentEnt("5", "while");
			expected = { {"6"} };
			Assert::IsTrue(actual == expected);
		}
	};
};