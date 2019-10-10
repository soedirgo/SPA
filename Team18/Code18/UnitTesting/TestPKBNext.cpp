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

			PKB.setNextRelation("1", "2");
			PKB.setNextRelation("2", "3");
			PKB.setNextRelation("4", "5");
			PKB.setNextRelation("5", "6");
			PKB.setNextRelation("6", "7");
			PKB.setNextRelation("7", "8");
			PKB.setNextRelation("8", "9");
			
			PKB.setNextRelation("9", "6");
			
			PKB.setNextRelation("6", "10");
			PKB.setNextRelation("10", "11");
			PKB.setNextRelation("10", "12");
			PKB.setNextRelation("11", "13");
			PKB.setNextRelation("12", "13");
			PKB.setNextRelation("13", "14");
			PKB.setNextRelation("14", "15");
			PKB.setNextRelation("16", "17");
			PKB.setNextRelation("17", "18");

			DesignExtractor DesignExtractor;
			DesignExtractor.extractDesign();
		}
		TEST_METHOD(NextRelationship)
		{
			PKBNext PKB;
			Assert::IsTrue(PKB.isNextRelationship("1", "2"));
			Assert::IsTrue(PKB.isNextRelationship("2", "3"));
			Assert::IsTrue(PKB.isNextRelationship("4", "5"));
			Assert::IsTrue(PKB.isNextRelationship("5", "6"));
			Assert::IsTrue(PKB.isNextRelationship("6", "7"));
			Assert::IsTrue(PKB.isNextRelationship("7", "8"));
			Assert::IsTrue(PKB.isNextRelationship("8", "9"));
			Assert::IsTrue(PKB.isNextRelationship("9", "6"));
			Assert::IsTrue(PKB.isNextRelationship("6", "10"));
			Assert::IsTrue(PKB.isNextRelationship("10", "11"));
			Assert::IsTrue(PKB.isNextRelationship("10", "12"));
			Assert::IsTrue(PKB.isNextRelationship("11", "13"));
			Assert::IsTrue(PKB.isNextRelationship("12", "13"));
			Assert::IsTrue(PKB.isNextRelationship("13", "14"));
			Assert::IsTrue(PKB.isNextRelationship("14", "15"));
			Assert::IsTrue(PKB.isNextRelationship("16", "17"));
			Assert::IsTrue(PKB.isNextRelationship("17", "18"));
		}
		
		TEST_METHOD(NextStarRelationship)
		{
			PKBNext PKB;
			Assert::IsTrue(PKB.isNextStarRelationship("1", "2"));
			Assert::IsTrue(PKB.isNextStarRelationship("2", "3"));
			Assert::IsTrue(PKB.isNextStarRelationship("4", "5"));
			Assert::IsTrue(PKB.isNextStarRelationship("5", "6"));
			Assert::IsTrue(PKB.isNextStarRelationship("6", "7"));
			Assert::IsTrue(PKB.isNextStarRelationship("7", "8"));
			Assert::IsTrue(PKB.isNextStarRelationship("8", "9"));
			Assert::IsTrue(PKB.isNextStarRelationship("9", "6"));
			Assert::IsTrue(PKB.isNextStarRelationship("6", "10"));
			Assert::IsTrue(PKB.isNextStarRelationship("10", "11"));
			Assert::IsTrue(PKB.isNextStarRelationship("10", "12"));
			Assert::IsTrue(PKB.isNextStarRelationship("11", "13"));
			Assert::IsTrue(PKB.isNextStarRelationship("12", "13"));
			Assert::IsTrue(PKB.isNextStarRelationship("13", "14"));
			Assert::IsTrue(PKB.isNextStarRelationship("14", "15"));
			Assert::IsTrue(PKB.isNextStarRelationship("16", "17"));
			Assert::IsTrue(PKB.isNextStarRelationship("17", "18"));

			Assert::IsTrue(PKB.isNextStarRelationship("1", "3"));
			Assert::IsTrue(PKB.isNextStarRelationship("4", "6"));
			Assert::IsTrue(PKB.isNextStarRelationship("4", "7"));
			Assert::IsTrue(PKB.isNextStarRelationship("4", "8"));
			Assert::IsTrue(PKB.isNextStarRelationship("4", "9"));
			Assert::IsTrue(PKB.isNextStarRelationship("4", "10"));
			Assert::IsTrue(PKB.isNextStarRelationship("4", "11"));
			Assert::IsTrue(PKB.isNextStarRelationship("4", "12"));
			Assert::IsTrue(PKB.isNextStarRelationship("4", "13"));
			Assert::IsTrue(PKB.isNextStarRelationship("4", "14"));
			Assert::IsTrue(PKB.isNextStarRelationship("5", "7"));
			Assert::IsTrue(PKB.isNextStarRelationship("5", "8"));
			Assert::IsTrue(PKB.isNextStarRelationship("5", "9"));
			Assert::IsTrue(PKB.isNextStarRelationship("5", "10"));
			Assert::IsTrue(PKB.isNextStarRelationship("5", "11"));
			Assert::IsTrue(PKB.isNextStarRelationship("5", "12"));
			Assert::IsTrue(PKB.isNextStarRelationship("5", "13"));
			Assert::IsTrue(PKB.isNextStarRelationship("5", "14"));
			Assert::IsTrue(PKB.isNextStarRelationship("5", "15"));
			Assert::IsTrue(PKB.isNextStarRelationship("6", "8"));
			Assert::IsTrue(PKB.isNextStarRelationship("6", "9"));
			Assert::IsTrue(PKB.isNextStarRelationship("6", "10"));
			Assert::IsTrue(PKB.isNextStarRelationship("6", "11"));
			Assert::IsTrue(PKB.isNextStarRelationship("6", "12"));
			Assert::IsTrue(PKB.isNextStarRelationship("6", "13"));
			Assert::IsTrue(PKB.isNextStarRelationship("6", "14"));
			Assert::IsTrue(PKB.isNextStarRelationship("6", "15"));		
			Assert::IsTrue(PKB.isNextStarRelationship("7", "9"));
			/*
			Assert::IsTrue(PKB.isNextStarRelationship("7", "10"));
			Assert::IsTrue(PKB.isNextStarRelationship("7", "11"));
			Assert::IsTrue(PKB.isNextStarRelationship("7", "12"));
			Assert::IsTrue(PKB.isNextStarRelationship("7", "13"));
			Assert::IsTrue(PKB.isNextStarRelationship("7", "14"));
			Assert::IsTrue(PKB.isNextStarRelationship("7", "15"));
			Assert::IsTrue(PKB.isNextStarRelationship("8", "10"));
			Assert::IsTrue(PKB.isNextStarRelationship("8", "11"));
			Assert::IsTrue(PKB.isNextStarRelationship("8", "12"));
			Assert::IsTrue(PKB.isNextStarRelationship("8", "13"));
			Assert::IsTrue(PKB.isNextStarRelationship("8", "14"));
			Assert::IsTrue(PKB.isNextStarRelationship("8", "15"));
			Assert::IsTrue(PKB.isNextStarRelationship("9", "11"));
			Assert::IsTrue(PKB.isNextStarRelationship("9", "12"));
			Assert::IsTrue(PKB.isNextStarRelationship("9", "13"));
			Assert::IsTrue(PKB.isNextStarRelationship("9", "14"));
			Assert::IsTrue(PKB.isNextStarRelationship("9", "15"));
			*/
			Assert::IsTrue(PKB.isNextStarRelationship("10", "12"));
			Assert::IsTrue(PKB.isNextStarRelationship("10", "13"));
			Assert::IsTrue(PKB.isNextStarRelationship("10", "14"));
			Assert::IsTrue(PKB.isNextStarRelationship("10", "15"));
			Assert::IsTrue(PKB.isNextStarRelationship("11", "13"));
			Assert::IsTrue(PKB.isNextStarRelationship("11", "14"));
			Assert::IsTrue(PKB.isNextStarRelationship("11", "15"));
			Assert::IsTrue(PKB.isNextStarRelationship("12", "14"));
			Assert::IsTrue(PKB.isNextStarRelationship("12", "15"));
			Assert::IsTrue(PKB.isNextStarRelationship("13", "15"));
			Assert::IsTrue(PKB.isNextStarRelationship("16", "18"));
			
		}
		
		TEST_METHOD(NextGenericBoth)
		{
			PKBNext PKB;
			TABLE actual, expected;

			actual = PKB.getAllNextByLineNextLineStmt();
			expected = { {"1","2"},{"2","3"},{"4","5"},{"5","6"},{"6","7"},{"7","8"},{"8","9"},{"9","6"},{"6","10"},{"10","11"},{"10","12"},{"11","13"}
			,{"12","13"},{"13","14"},{"14","15"},{"16","17"},{"17","18"} };
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(NextGenericRight)
		{
			PKBNext PKB;
			TABLE actual, expected;

			actual = PKB.getAllNextByLineStmt("6");
			expected = { {"5","6"},{"9","6"} };
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(NextGenericLeft)
		{
			PKBNext PKB;
			TABLE actual, expected;

			actual = PKB.getAllNextLineStmt("6");
			expected = { {"6","7"},{"6","10"} };
			Assert::IsTrue(actual == expected);
		}
	};
};


