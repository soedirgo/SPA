#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKBStmt.h"
#include "DesignExtractor.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(PKBStmtTest)
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

			PKBStmt PKB;
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
		}

		TEST_METHOD(getAllStmt)
		{
			PKBStmt PKB;
			STMT_LIST actual = PKB.getAllStmt();
			STMT_LIST expected = { {"1"},{"2"},{"3"},{"4"},{"5"},{"6"},{"7"},{"8"},{"9"},{"10"},{"11"},{"12"},{"13"},{"14"},{"15"},{"16"},{"17"},{"18"} };
			Assert::IsTrue(actual == expected);
		}
		TEST_METHOD(getAllReadStmt)
		{
			PKBStmt PKB;
			STMT_LIST actual = PKB.getAllStmtByType("READ");
			STMT_LIST expected = { {"1"},{"2"} };
			Assert::IsTrue(actual == expected);
		}
		TEST_METHOD(getAllPrintStmt)
		{
			PKBStmt PKB;
			STMT_LIST actual = PKB.getAllStmtByType("PRINT");
			STMT_LIST expected = { {"18"} };
			Assert::IsTrue(actual == expected);
		}
		TEST_METHOD(getAllCallStmt)
		{
			PKBStmt PKB;
			STMT_LIST actual = PKB.getAllStmtByType("CALL");
			STMT_LIST expected = { {"3"},{"8"} };
			Assert::IsTrue(actual == expected);
		}
		TEST_METHOD(getAllWhileStmt)
		{
			PKBStmt PKB;
			STMT_LIST actual = PKB.getAllStmtByType("WHILE");
			STMT_LIST expected = { {"6"} };
			Assert::IsTrue(actual == expected);
		}
		TEST_METHOD(getAllIfStmt)
		{
			PKBStmt PKB;
			STMT_LIST actual = PKB.getAllStmtByType("IF");
			STMT_LIST expected = { {"10"} };
			Assert::IsTrue(actual == expected);
		}
		TEST_METHOD(getAllIfAssign)
		{
			PKBStmt PKB;
			STMT_LIST actual = PKB.getAllStmtByType("ASSIGN");
			STMT_LIST expected = {{"4"},{"5"},{"7"},{"9"},{"11"},{"12"},{"13"},{"14"},{"15"},{"16"},{"17"}};
			Assert::IsTrue(actual == expected);
		}
	};
};


