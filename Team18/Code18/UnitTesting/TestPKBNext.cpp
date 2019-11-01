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

			PKB.setProcedure("First", "1", "2", "");
			PKB.setProcedure("Second", "4", "11", "15");
			PKB.setProcedure("Third", "16", "18", "");

			PKB.setCallStmt("3", "Second");
			PKB.setCallStmt("8", "Third");

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

		TEST_METHOD(NextBipRelationship)
		{
			PKBNext PKB;
			Assert::IsTrue(PKB.isNextBipIdentIdent("1", "2"));
			Assert::IsTrue(PKB.isNextBipIdentIdent("2", "3"));
			Assert::IsTrue(PKB.isNextBipIdentIdent("4", "5"));
			Assert::IsTrue(PKB.isNextBipIdentIdent("5", "6"));
			Assert::IsTrue(PKB.isNextBipIdentIdent("6", "7"));
			Assert::IsTrue(PKB.isNextBipIdentIdent("7", "8"));
			Assert::IsTrue(PKB.isNextBipIdentIdent("8", "9"));
			Assert::IsTrue(PKB.isNextBipIdentIdent("9", "6"));
			Assert::IsTrue(PKB.isNextBipIdentIdent("6", "10"));
			Assert::IsTrue(PKB.isNextBipIdentIdent("10", "11"));
			Assert::IsTrue(PKB.isNextBipIdentIdent("10", "12"));
			Assert::IsTrue(PKB.isNextBipIdentIdent("11", "13"));
			Assert::IsTrue(PKB.isNextBipIdentIdent("12", "13"));
			Assert::IsTrue(PKB.isNextBipIdentIdent("13", "14"));
			Assert::IsTrue(PKB.isNextBipIdentIdent("14", "15"));
			Assert::IsTrue(PKB.isNextBipIdentIdent("16", "17"));
			Assert::IsTrue(PKB.isNextBipIdentIdent("17", "18"));

			Assert::IsTrue(PKB.isNextBipIdentIdent("3", "4"));
			Assert::IsTrue(PKB.isNextBipIdentIdent("8", "16"));
			Assert::IsTrue(PKB.isNextBipIdentIdent("18", "9"));
		}

		TEST_METHOD(NextBipStarRelationship)
		{
			PKBNext PKB;

			Assert::IsTrue(PKB.isNextBipTIdentIdent("1", "2"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("1", "3"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("1", "4"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("1", "5"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("1", "6"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("1", "7"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("1", "8"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("1", "9"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("1", "10"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("1", "11"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("1", "12"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("1", "13"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("1", "14"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("1", "15"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("1", "16"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("1", "17"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("1", "18"));

			Assert::IsTrue(PKB.isNextBipTIdentIdent("2", "3"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("2", "4"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("2", "5"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("2", "6"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("2", "7"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("2", "8"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("2", "9"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("2", "10"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("2", "11"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("2", "12"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("2", "13"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("2", "14"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("2", "15"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("2", "16"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("2", "17"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("2", "18"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("3", "4"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("3", "5"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("3", "6"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("3", "7"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("3", "8"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("3", "9"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("3", "10"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("3", "11"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("3", "12"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("3", "13"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("3", "14"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("3", "15"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("3", "16"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("3", "17"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("3", "18"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("4", "5"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("4", "6"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("4", "7"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("4", "8"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("4", "9"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("4", "10"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("4", "11"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("4", "12"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("4", "13"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("4", "14"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("4", "15"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("4", "16"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("4", "17"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("4", "18"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("5", "6"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("5", "7"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("5", "8"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("5", "9"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("5", "10"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("5", "11"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("5", "12"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("5", "13"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("5", "14"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("5", "15"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("5", "16"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("5", "17"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("5", "18"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("6", "7"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("6", "8"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("6", "9"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("6", "10"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("6", "11"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("6", "12"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("6", "13"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("6", "14"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("6", "15"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("6", "16"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("6", "17"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("6", "18"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("7", "8"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("7", "9"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("7", "6"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("7", "11"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("7", "12"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("7", "13"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("7", "14"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("7", "15"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("7", "16"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("7", "17"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("7", "18"));

			Assert::IsTrue(PKB.isNextBipTIdentIdent("8", "9"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("9", "6"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("6", "10"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("10", "11"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("10", "12"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("11", "13"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("12", "13"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("13", "14"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("14", "15"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("16", "17"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("17", "18"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("8", "10"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("8", "11"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("8", "12"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("8", "13"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("8", "14"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("8", "15"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("8", "16"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("8", "17"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("8", "18"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("9", "11"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("9", "12"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("9", "13"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("9", "14"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("9", "15"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("9", "16"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("9", "17"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("9", "18"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("10", "12"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("10", "13"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("10", "14"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("10", "15"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("11", "13"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("11", "14"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("11", "15"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("12", "14"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("12", "15"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("13", "15"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("16", "18"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("6", "6"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("7", "7"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("8", "8"));
			Assert::IsTrue(PKB.isNextBipTIdentIdent("9", "9"));

			Assert::IsFalse(PKB.isNextBipTIdentIdent("10", "16"));
			Assert::IsFalse(PKB.isNextBipTIdentIdent("10", "17"));
			Assert::IsFalse(PKB.isNextBipTIdentIdent("10", "18"));
			Assert::IsFalse(PKB.isNextBipTIdentIdent("11", "16"));
			Assert::IsFalse(PKB.isNextBipTIdentIdent("11", "17"));
			Assert::IsFalse(PKB.isNextBipTIdentIdent("11", "18"));
			Assert::IsFalse(PKB.isNextBipTIdentIdent("12", "16"));
			Assert::IsFalse(PKB.isNextBipTIdentIdent("12", "17"));
			Assert::IsFalse(PKB.isNextBipTIdentIdent("12", "18"));

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


