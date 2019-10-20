#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKBNext.h"
#include "PKB.h"
#include "DesignExtractor.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(PKBNextTest)
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

			PKB.setNext("1", "2");
			PKB.setNext("2", "3");
			PKB.setNext("4", "5");
			PKB.setNext("5", "6");
			PKB.setNext("6", "7");
			PKB.setNext("7", "8");
			PKB.setNext("8", "9");
			
			PKB.setNext("9", "6");
			
			PKB.setNext("6", "10");
			PKB.setNext("10", "11");
			PKB.setNext("10", "12");
			PKB.setNext("11", "13");
			PKB.setNext("12", "13");
			PKB.setNext("13", "14");
			PKB.setNext("14", "15");
			PKB.setNext("16", "17");
			PKB.setNext("17", "18");

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
		TEST_METHOD(NextRelationship)
		{
			PKBNext PKB;
			Assert::IsTrue(PKB.isNextIdentIdent("1", "2"));
			Assert::IsTrue(PKB.isNextIdentIdent("2", "3"));
			Assert::IsTrue(PKB.isNextIdentIdent("4", "5"));
			Assert::IsTrue(PKB.isNextIdentIdent("5", "6"));
			Assert::IsTrue(PKB.isNextIdentIdent("6", "7"));
			Assert::IsTrue(PKB.isNextIdentIdent("7", "8"));
			Assert::IsTrue(PKB.isNextIdentIdent("8", "9"));
			Assert::IsTrue(PKB.isNextIdentIdent("9", "6"));
			Assert::IsTrue(PKB.isNextIdentIdent("6", "10"));
			Assert::IsTrue(PKB.isNextIdentIdent("10", "11"));
			Assert::IsTrue(PKB.isNextIdentIdent("10", "12"));
			Assert::IsTrue(PKB.isNextIdentIdent("11", "13"));
			Assert::IsTrue(PKB.isNextIdentIdent("12", "13"));
			Assert::IsTrue(PKB.isNextIdentIdent("13", "14"));
			Assert::IsTrue(PKB.isNextIdentIdent("14", "15"));
			Assert::IsTrue(PKB.isNextIdentIdent("16", "17"));
			Assert::IsTrue(PKB.isNextIdentIdent("17", "18"));
		}
		
		TEST_METHOD(NextStarRelationship)
		{
			PKBNext PKB;
			Assert::IsTrue(PKB.isNextTIdentIdent("1", "2"));
			Assert::IsTrue(PKB.isNextTIdentIdent("2", "3"));
			Assert::IsTrue(PKB.isNextTIdentIdent("4", "5"));
			Assert::IsTrue(PKB.isNextTIdentIdent("5", "6"));
			Assert::IsTrue(PKB.isNextTIdentIdent("6", "7"));
			Assert::IsTrue(PKB.isNextTIdentIdent("7", "8"));
			Assert::IsTrue(PKB.isNextTIdentIdent("8", "9"));
			Assert::IsTrue(PKB.isNextTIdentIdent("9", "6"));
			Assert::IsTrue(PKB.isNextTIdentIdent("6", "10"));
			Assert::IsTrue(PKB.isNextTIdentIdent("10", "11"));
			Assert::IsTrue(PKB.isNextTIdentIdent("10", "12"));
			Assert::IsTrue(PKB.isNextTIdentIdent("11", "13"));
			Assert::IsTrue(PKB.isNextTIdentIdent("12", "13"));
			Assert::IsTrue(PKB.isNextTIdentIdent("13", "14"));
			Assert::IsTrue(PKB.isNextTIdentIdent("14", "15"));
			Assert::IsTrue(PKB.isNextTIdentIdent("16", "17"));
			Assert::IsTrue(PKB.isNextTIdentIdent("17", "18"));

			Assert::IsTrue(PKB.isNextTIdentIdent("1", "3"));
			Assert::IsTrue(PKB.isNextTIdentIdent("4", "6"));
			Assert::IsTrue(PKB.isNextTIdentIdent("4", "7"));
			Assert::IsTrue(PKB.isNextTIdentIdent("4", "8"));
			Assert::IsTrue(PKB.isNextTIdentIdent("4", "9"));
			Assert::IsTrue(PKB.isNextTIdentIdent("4", "10"));
			Assert::IsTrue(PKB.isNextTIdentIdent("4", "11"));
			Assert::IsTrue(PKB.isNextTIdentIdent("4", "12"));
			Assert::IsTrue(PKB.isNextTIdentIdent("4", "13"));
			Assert::IsTrue(PKB.isNextTIdentIdent("4", "14"));
			Assert::IsTrue(PKB.isNextTIdentIdent("5", "7"));
			Assert::IsTrue(PKB.isNextTIdentIdent("5", "8"));
			Assert::IsTrue(PKB.isNextTIdentIdent("5", "9"));
			Assert::IsTrue(PKB.isNextTIdentIdent("5", "10"));
			Assert::IsTrue(PKB.isNextTIdentIdent("5", "11"));
			Assert::IsTrue(PKB.isNextTIdentIdent("5", "12"));
			Assert::IsTrue(PKB.isNextTIdentIdent("5", "13"));
			Assert::IsTrue(PKB.isNextTIdentIdent("5", "14"));
			Assert::IsTrue(PKB.isNextTIdentIdent("5", "15"));
			Assert::IsTrue(PKB.isNextTIdentIdent("6", "8"));
			Assert::IsTrue(PKB.isNextTIdentIdent("6", "9"));
			Assert::IsTrue(PKB.isNextTIdentIdent("6", "10"));
			Assert::IsTrue(PKB.isNextTIdentIdent("6", "11"));
			Assert::IsTrue(PKB.isNextTIdentIdent("6", "12"));
			Assert::IsTrue(PKB.isNextTIdentIdent("6", "13"));
			Assert::IsTrue(PKB.isNextTIdentIdent("6", "14"));
			Assert::IsTrue(PKB.isNextTIdentIdent("6", "15"));	
			Assert::IsTrue(PKB.isNextTIdentIdent("7", "9"));
			Assert::IsTrue(PKB.isNextTIdentIdent("7", "6"));
			Assert::IsTrue(PKB.isNextTIdentIdent("7", "11"));
			Assert::IsTrue(PKB.isNextTIdentIdent("7", "12"));
			Assert::IsTrue(PKB.isNextTIdentIdent("7", "13"));
			Assert::IsTrue(PKB.isNextTIdentIdent("7", "14"));
			Assert::IsTrue(PKB.isNextTIdentIdent("7", "15"));
			Assert::IsTrue(PKB.isNextTIdentIdent("8", "10"));
			Assert::IsTrue(PKB.isNextTIdentIdent("8", "11"));
			Assert::IsTrue(PKB.isNextTIdentIdent("8", "12"));
			Assert::IsTrue(PKB.isNextTIdentIdent("8", "13"));
			Assert::IsTrue(PKB.isNextTIdentIdent("8", "14"));
			Assert::IsTrue(PKB.isNextTIdentIdent("8", "15"));
			Assert::IsTrue(PKB.isNextTIdentIdent("9", "11"));
			Assert::IsTrue(PKB.isNextTIdentIdent("9", "12"));
			Assert::IsTrue(PKB.isNextTIdentIdent("9", "13"));
			Assert::IsTrue(PKB.isNextTIdentIdent("9", "14"));
			Assert::IsTrue(PKB.isNextTIdentIdent("9", "15"));
			Assert::IsTrue(PKB.isNextTIdentIdent("10", "12"));
			Assert::IsTrue(PKB.isNextTIdentIdent("10", "13"));
			Assert::IsTrue(PKB.isNextTIdentIdent("10", "14"));
			Assert::IsTrue(PKB.isNextTIdentIdent("10", "15"));
			Assert::IsTrue(PKB.isNextTIdentIdent("11", "13"));
			Assert::IsTrue(PKB.isNextTIdentIdent("11", "14"));
			Assert::IsTrue(PKB.isNextTIdentIdent("11", "15"));
			Assert::IsTrue(PKB.isNextTIdentIdent("12", "14"));
			Assert::IsTrue(PKB.isNextTIdentIdent("12", "15"));
			Assert::IsTrue(PKB.isNextTIdentIdent("13", "15"));
			Assert::IsTrue(PKB.isNextTIdentIdent("16", "18"));

			Assert::IsTrue(PKB.isNextTIdentIdent("6", "6"));
			Assert::IsTrue(PKB.isNextTIdentIdent("7", "7"));
			Assert::IsTrue(PKB.isNextTIdentIdent("8", "8"));
			Assert::IsTrue(PKB.isNextTIdentIdent("9", "9"));
			
		}
		
		TEST_METHOD(NextGenericBoth)
		{
			PKBNext PKB;
			TABLE actual, expected;

			actual = PKB.getNextEntEnt("stmt","stmt");
			expected = { {"1","2"},{"2","3"},{"4","5"},{"5","6"},{"6","7"},{"7","8"},{"8","9"},{"9","6"},{"6","10"},{"10","11"},{"10","12"},{"11","13"}
			,{"12","13"},{"13","14"},{"14","15"},{"16","17"},{"17","18"} };
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(NextGenericRight)
		{
			PKBNext PKB;
			LINE_LIST actual, expected;

			actual = PKB.getNextEntIdent("stmt","6");
			expected = { {"5"},{"9"} };
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(NextGenericLeft)
		{
			PKBNext PKB;
			LINE_LIST actual, expected;

			actual = PKB.getNextIdentEnt("6", "stmt");
			expected = { {"7"},{"10"} };
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(NextTSelf)
		{
			PKBNext PKB;
			LINE_LIST actual, expected;

			actual = PKB.getNextTSelf("stmt");
			expected = { {"6"},{"7"},{"8"},{"9"} };
			Assert::IsTrue(actual == expected);
		}
	};
};


