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
			STMT_LIST actual = PKB.getAllStmtByType("read");
			STMT_LIST expected = { {"1"},{"2"} };
			Assert::IsTrue(actual == expected);
		}
		TEST_METHOD(getAllPrintStmt)
		{
			PKBStmt PKB;
			STMT_LIST actual = PKB.getAllStmtByType("print");
			STMT_LIST expected = { {"18"} };
			Assert::IsTrue(actual == expected);
		}
		TEST_METHOD(getAllCallStmt)
		{
			PKBStmt PKB;
			STMT_LIST actual = PKB.getAllStmtByType("call");
			STMT_LIST expected = { {"3"},{"8"} };
			Assert::IsTrue(actual == expected);
		}
		TEST_METHOD(getAllWhileStmt)
		{
			PKBStmt PKB;
			STMT_LIST actual = PKB.getAllStmtByType("while");
			STMT_LIST expected = { {"6"} };
			Assert::IsTrue(actual == expected);
		}
		TEST_METHOD(getAllIfStmt)
		{
			PKBStmt PKB;
			STMT_LIST actual = PKB.getAllStmtByType("if");
			STMT_LIST expected = { {"10"} };
			Assert::IsTrue(actual == expected);
		}
		TEST_METHOD(getAllIfAssign)
		{
			PKBStmt PKB;
			STMT_LIST actual = PKB.getAllStmtByType("assign");
			STMT_LIST expected = {{"4"},{"5"},{"7"},{"9"},{"11"},{"12"},{"13"},{"14"},{"15"},{"16"},{"17"}};
			Assert::IsTrue(actual == expected);
		}
	};
};


