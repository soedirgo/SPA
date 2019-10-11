#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKBUses.h"
#include "DesignExtractor.h"
#include "PKBStmt.h"
#include "PKBCall.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(PKBUsesTest)
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

			PKBUses PKB;
			PKBStmt Stmts;
			PKBCall Calls;
			PKB.clear();

			Stmts.setStmt("1", "read");
			Stmts.setStmt("2", "read");
			Stmts.setStmt("3", "call");
			Stmts.setStmt("4", "assign");
			Stmts.setStmt("5", "assign");
			Stmts.setStmt("6", "while");
			Stmts.setStmt("7", "assign");
			Stmts.setStmt("8", "call");
			Stmts.setStmt("9", "assign");
			Stmts.setStmt("10", "if");
			Stmts.setStmt("11", "assign");
			Stmts.setStmt("12", "assign");
			Stmts.setStmt("13", "assign");
			Stmts.setStmt("14", "assign");
			Stmts.setStmt("15", "assign");
			Stmts.setStmt("16", "assign");
			Stmts.setStmt("17", "assign");
			Stmts.setStmt("18", "print");

			//Direct assignment stmts with var on RHS 
			PKB.setUsesStmt("3", "y");
			PKB.setUsesStmt("6", "i");
			PKB.setUsesStmt("7", "x");
			PKB.setUsesStmt("7", "y");
			PKB.setUsesStmt("9", "i");
			PKB.setUsesStmt("6", "x");
			PKB.setUsesStmt("6", "y");
			PKB.setUsesStmt("6", "i");
			PKB.setUsesStmt("8", "z");
			PKB.setUsesStmt("8", "v");
			PKB.setUsesStmt("10", "x");
			PKB.setUsesStmt("11", "x");
			PKB.setUsesStmt("13", "z");
			PKB.setUsesStmt("13", "x");
			PKB.setUsesStmt("13", "i");
			PKB.setUsesStmt("14", "z");
			PKB.setUsesStmt("15", "x");
			PKB.setUsesStmt("15", "y");
			PKB.setUsesStmt("15", "z");
			PKB.setUsesStmt("17", "z");
			PKB.setUsesStmt("18", "v");

			//More complex uses 


			PKB.setUsesProc("Second", "i");
			PKB.setUsesProc("Second", "x");
			PKB.setUsesProc("Second", "y");
			PKB.setUsesProc("Second", "z");
			PKB.setUsesProc("Third", "v");
			PKB.setUsesProc("Third", "z");

			PKB.setUsesProc("Second", "v");
			PKB.setUsesProc("First", "i");
			PKB.setUsesProc("First", "x");
			PKB.setUsesProc("First", "y");
			PKB.setUsesProc("First", "z");
			PKB.setUsesProc("First", "v");

			Calls.setCallProc("3", "Second");
			Calls.setCallProc("8", "Third");

		}

		TEST_METHOD(UsesStmtRelationship)
		{
			PKBUses PKB;
			Assert::IsTrue(PKB.isUsesStmtRelationship("6", "i"));
			Assert::IsTrue(PKB.isUsesStmtRelationship("7", "x"));
			Assert::IsTrue(PKB.isUsesStmtRelationship("7", "y"));
			Assert::IsTrue(PKB.isUsesStmtRelationship("9", "i"));
			Assert::IsTrue(PKB.isUsesStmtRelationship("6", "x"));
			Assert::IsTrue(PKB.isUsesStmtRelationship("6", "y"));
			Assert::IsTrue(PKB.isUsesStmtRelationship("10", "x"));
			Assert::IsTrue(PKB.isUsesStmtRelationship("11", "x"));
			Assert::IsTrue(PKB.isUsesStmtRelationship("13", "z"));
			Assert::IsTrue(PKB.isUsesStmtRelationship("13", "x"));
			Assert::IsTrue(PKB.isUsesStmtRelationship("14", "z"));
			Assert::IsTrue(PKB.isUsesStmtRelationship("15", "x"));
			Assert::IsTrue(PKB.isUsesStmtRelationship("15", "y"));
			Assert::IsTrue(PKB.isUsesStmtRelationship("15", "z"));
			Assert::IsTrue(PKB.isUsesStmtRelationship("17", "z"));
			Assert::IsTrue(PKB.isUsesStmtRelationship("18", "v"));
		}
		TEST_METHOD(UsesProcRelationship)
		{
			PKBUses PKB;
			Assert::IsTrue(PKB.isUsesProcRelationship("Second", "x"));
			Assert::IsTrue(PKB.isUsesProcRelationship("Second", "y"));
			Assert::IsTrue(PKB.isUsesProcRelationship("Second", "z"));
		}

		TEST_METHOD(GetAllUsesStmt)
		{
			PKBUses PKB;
			STMT_LIST result = PKB.getAllUsesStmt();
			STMT_LIST expected = { {"3"} , {"6"},{"7"}, {"8"},{"9"},{"10"},{"11"},{"13"},{"14"},{"15"},{"17"},{"18"} };

			Assert::IsTrue(expected == result);
		}

		TEST_METHOD(getAllUsesStmtByType)
		{//LHS is either a print/if/while/assign/call 
			PKBUses PKB;
			STMT_LIST ifResult = PKB.getAllUsesStmtByType("if");
			STMT_LIST ifExpected = { {"10"} };
			Assert::IsTrue(ifExpected == ifResult);

			STMT_LIST printResult = PKB.getAllUsesStmtByType("print");
			STMT_LIST printExpected = { {"18"} };
			Assert::IsTrue(printExpected == printResult);

			STMT_LIST assignResult = PKB.getAllUsesStmtByType("assign");
			STMT_LIST assignExpected = { {"4"}, {"5"}, {"7"}, {"9"}, {"11"}, {"12"} , {"13"}, {"14"}, {"15"}, {"16"}, {"17"} };
			Assert::IsTrue(assignExpected == assignResult);

			STMT_LIST callResult = PKB.getAllUsesStmtByType("call");
			STMT_LIST callExpected = { {"3"}, {"8"} };
			Assert::IsTrue(callExpected == callResult);

			STMT_LIST whileResult = PKB.getAllUsesStmtByType("while");
			STMT_LIST whileExpected = { {"6"} };
			Assert::IsTrue(whileExpected == whileResult);
		}

		TEST_METHOD(getUsesStmtByTypeAndVar)
		{//LHS is either a print/if/while/assign/call 
			PKBUses PKB;
			STMT_LIST result = PKB.getUsesStmtByTypeAndVar("assign", "i");
			STMT_LIST expected = { {"9"}, {"13"} };
			Assert::IsTrue(result == expected);


			result = PKB.getUsesStmtByTypeAndVar("assign", "x");
			expected = { {"7"} , {"11"}  , {"13"} , {"15"} };
			Assert::IsTrue(result == expected);

			result = PKB.getUsesStmtByTypeAndVar("assign", "y");
			expected = { {"7"} ,  {"15"} };
			Assert::IsTrue(result == expected);

			result = PKB.getUsesStmtByTypeAndVar("assign", "z");
			expected = { {"13"} , {"14"} ,{"15"} ,{"17"} };
			Assert::IsTrue(result == expected);

			result = PKB.getUsesStmtByTypeAndVar("assign", "z");
			expected = { {"13"} , {"14"} ,{"15"} ,{"17"} };
			Assert::IsTrue(result == expected);

			result = PKB.getUsesStmtByTypeAndVar("print", "v");
			expected = { {"18"} };
			Assert::IsTrue(result == expected);

			result = PKB.getUsesStmtByTypeAndVar("if", "x");
			expected = { {"10"} };
			Assert::IsTrue(result == expected);

			result = PKB.getUsesStmtByTypeAndVar("while", "i");
			expected = { {"6"} };
			Assert::IsTrue(result == expected);

			result = PKB.getUsesStmtByTypeAndVar("call", "i");
			expected = { {"3"} };
			Assert::IsTrue(result == expected);

			result = PKB.getUsesStmtByTypeAndVar("call", "x");
			expected = { {"3"} };
			Assert::IsTrue(result == expected);

			result = PKB.getUsesStmtByTypeAndVar("call", "y");
			expected = { {"3"} };
			Assert::IsTrue(result == expected);

			result = PKB.getUsesStmtByTypeAndVar("call", "z");
			expected = { {"3"} , {"8"} };
			Assert::IsTrue(result == expected);

			result = PKB.getUsesStmtByTypeAndVar("call", "v");
			expected = { {"3"} , {"8"} };
			Assert::IsTrue(result == expected);


		}

		TEST_METHOD(getUsesStmtByVar) {
			PKBUses pkb;
			STMT_LIST expected = { {"6"} , {"7"} , {"10"} , {"11"} , {"13"} , {"15"} };
			STMT_LIST result = pkb.getUsesStmtByVar("x");
			Assert::IsTrue(result == expected);

			result = pkb.getUsesStmtByVar("i");
			expected = { {"6"} , {"9"} , {"13"} };
			Assert::IsTrue(result == expected);

			result = pkb.getUsesStmtByVar("v");
			expected = { {"8"},  {"18"} };
			Assert::IsTrue(result == expected);

			result = pkb.getUsesStmtByVar("y");
			expected = { {"3"} ,  {"6"} , {"7"} , {"15"} };
			Assert::IsTrue(result == expected);

			result = pkb.getUsesStmtByVar("z");
			expected = { {"8"} , {"13"} ,  {"14"} , {"15"} , {"17"} };
			Assert::IsTrue(result == expected);
		}

		TEST_METHOD(getUsesVarByStmt) {
			PKBUses pkb;

			//All empty result queries
			STMT_LIST expected = {};
			STMT_LIST result = pkb.getUsesVarByStmt("1");
			Assert::IsTrue(result == expected);
			result = pkb.getUsesVarByStmt("2");
			Assert::IsTrue(result == expected);
			result = pkb.getUsesVarByStmt("4");
			Assert::IsTrue(result == expected);
			result = pkb.getUsesVarByStmt("5");
			Assert::IsTrue(result == expected);

			//Special call stmt case
			//result = pkb.getUsesVarByStmt("3");
			//Assert::IsTrue(result == expected);

			//Other assignment cases etc. 
			expected = { {"i"}, {"x"} , {"y"} };
			result = pkb.getUsesVarByStmt("6");
			Assert::IsTrue(result == expected);

			//if
			expected = { {"x"} };
			result = pkb.getUsesVarByStmt("10");
			Assert::IsTrue(result == expected);

			//assignment
			expected = { {"x"}, {"y"}, {"z"} };
			result = pkb.getUsesVarByStmt("15");
			Assert::IsTrue(result == expected);
		}
		TEST_METHOD(getAllUsesProc) {
			PKBUses pkb; 
			PROC_LIST expected = { {"First"}, {"Second"}, {"Third"} };
			PROC_LIST result = pkb.getAllUsesProc();
			Assert::IsTrue(result == expected);
		}
		TEST_METHOD(getUsesProcByVar) {
			PKBUses pkb;
			PROC_LIST expected = { {"First"} , {"Second"}, {"Third"} };
			PROC_LIST result = pkb.getUsesProcByVar( "z" );
			Assert::IsTrue(result == expected);

			result = pkb.getUsesProcByVar("v");
			Assert::IsTrue(result == expected);

			result = pkb.getUsesProcByVar("x");
			expected = { {"First"} , {"Second"} };

			result = pkb.getUsesProcByVar("y");
			expected = { {"First"} , {"Second"} };

		}
		TEST_METHOD(getUsesVarByProc) {

		}



	};




}


