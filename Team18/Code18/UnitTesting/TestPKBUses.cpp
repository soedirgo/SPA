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

			
			//Line #3 Calls Second
			PKB.setUsesS("3", "y");
			PKB.setUsesS("3", "i");
			PKB.setUsesS("3", "x");
			PKB.setUsesS("3", "z"); 
			PKB.setUsesS("3", "v"); //#3 Calls Second, which calls Third

			//Direct assignment stmts with var on RHS 
			PKB.setUsesS("6", "i");
			PKB.setUsesS("7", "x");
			PKB.setUsesS("7", "y");
			PKB.setUsesS("9", "i");
			PKB.setUsesS("6", "x");
			PKB.setUsesS("6", "y");
			PKB.setUsesS("6", "i");
			PKB.setUsesS("8", "z");
			PKB.setUsesS("8", "v");
			PKB.setUsesS("10", "x");
			PKB.setUsesS("11", "x");
			PKB.setUsesS("13", "z");
			PKB.setUsesS("13", "x");
			PKB.setUsesS("13", "i");
			PKB.setUsesS("14", "z");
			PKB.setUsesS("15", "x");
			PKB.setUsesS("15", "y");
			PKB.setUsesS("15", "z");
			PKB.setUsesS("17", "z");
			PKB.setUsesS("18", "v");

			//More complex uses 


			PKB.setUsesP("Second", "i");
			PKB.setUsesP("Second", "x");
			PKB.setUsesP("Second", "y");
			PKB.setUsesP("Second", "z");
			PKB.setUsesP("Third", "v");
			PKB.setUsesP("Third", "z");

			PKB.setUsesP("Second", "v");
			PKB.setUsesP("First", "i");
			PKB.setUsesP("First", "x");
			PKB.setUsesP("First", "y");
			PKB.setUsesP("First", "z");
			PKB.setUsesP("First", "v");

			Calls.setCallProc("3", "Second");
			Calls.setCallProc("8", "Third");

		}

		TEST_METHOD(isUsesS)
		{
			PKBUses PKB;
			Assert::IsTrue(PKB.isUsesS("6", "i"));
			Assert::IsTrue(PKB.isUsesS("7", "x"));
			Assert::IsTrue(PKB.isUsesS("7", "y"));
			Assert::IsTrue(PKB.isUsesS("9", "i"));
			Assert::IsTrue(PKB.isUsesS("6", "x"));
			Assert::IsTrue(PKB.isUsesS("6", "y"));
			Assert::IsTrue(PKB.isUsesS("10", "x"));
			Assert::IsTrue(PKB.isUsesS("11", "x"));
			Assert::IsTrue(PKB.isUsesS("13", "z"));
			Assert::IsTrue(PKB.isUsesS("13", "x"));
			Assert::IsTrue(PKB.isUsesS("14", "z"));
			Assert::IsTrue(PKB.isUsesS("15", "x"));
			Assert::IsTrue(PKB.isUsesS("15", "y"));
			Assert::IsTrue(PKB.isUsesS("15", "z"));
			Assert::IsTrue(PKB.isUsesS("17", "z"));
			Assert::IsTrue(PKB.isUsesS("18", "v"));

			Assert::IsTrue(PKB.isUsesS("6", "_"));
			Assert::IsTrue(PKB.isUsesS("7", "_"));
			Assert::IsTrue(PKB.isUsesS("7", "_"));
			Assert::IsTrue(PKB.isUsesS("9", "_"));
			Assert::IsTrue(PKB.isUsesS("6", "_"));
			Assert::IsTrue(PKB.isUsesS("6", "_"));
			Assert::IsTrue(PKB.isUsesS("10", "_"));
			Assert::IsTrue(PKB.isUsesS("11", "_"));
			Assert::IsTrue(PKB.isUsesS("13", "_"));
			Assert::IsTrue(PKB.isUsesS("13", "_"));
			Assert::IsTrue(PKB.isUsesS("14", "_"));
			Assert::IsTrue(PKB.isUsesS("15", "_"));
			Assert::IsTrue(PKB.isUsesS("15", "_"));
			Assert::IsTrue(PKB.isUsesS("15", "_"));
			Assert::IsTrue(PKB.isUsesS("17", "_"));
			Assert::IsTrue(PKB.isUsesS("18", "_"));
			
		}
		TEST_METHOD(isUsesP)
		{
			PKBUses PKB;
			Assert::IsTrue(PKB.isUsesP("Second", "x"));
			Assert::IsTrue(PKB.isUsesP("Second", "y"));
			Assert::IsTrue(PKB.isUsesP("Second", "z"));

			Assert::IsTrue(PKB.isUsesP("First", "_"));
			Assert::IsTrue(PKB.isUsesP("Second", "_"));
			Assert::IsTrue(PKB.isUsesP("Third", "_"));
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
			STMT_LIST assignExpected = { {"7"}, {"9"}, {"11"}, {"13"}, {"14"}, {"15"}, {"17"} };
			Assert::IsTrue(assignExpected == assignResult);

			STMT_LIST callResult = PKB.getAllUsesStmtByType("call");//Second third firs
			STMT_LIST callExpected = { {"3"}, {"8"} }; 
			Assert::IsTrue(callExpected == callResult);

			STMT_LIST whileResult = PKB.getAllUsesStmtByType("while");
			STMT_LIST whileExpected = { {"6"} };
			Assert::IsTrue(whileExpected == whileResult);

			STMT_LIST allUsesResults = PKB.getAllUsesStmtByType("stmt");
			STMT_LIST allUsesExpected = { {"3"} , {"6"},{"7"}, {"8"},{"9"},{"10"},{"11"},{"13"},{"14"},{"15"},{"17"},{"18"} };
		

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

			result = PKB.getUsesStmtByTypeAndVar("stmt", "v");
			expected = { {"3"} , {"8"} , {"18"}  };
			Assert::IsTrue(result == expected);

			result = PKB.getUsesStmtByTypeAndVar("stmt", "z");
			expected = { {"3"} , {"8"} , {"13"}, {"14"}, {"15"} , {"17"} };
			Assert::IsTrue(result == expected);

			result = PKB.getUsesStmtByTypeAndVar("stmt", "x");
			expected = { {"3"} , {"6"} ,{"7"} , {"10"}, {"11"}, {"13"} , {"15"} };
			Assert::IsTrue(result == expected);

			result = PKB.getUsesStmtByTypeAndVar("stmt", "y");
			expected = { {"3"} , {"6"} ,{"7"} , {"15"} };
			Assert::IsTrue(result == expected);

			result = PKB.getUsesStmtByTypeAndVar("stmt", "i");
			expected = { {"3"} , {"6"} ,{"9"} , {"13"} };
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

			expected = { {"x"} , {"y"}, {"z"}, {"v"}, {"i"} };
			result = pkb.getUsesVarByStmt("3");//Special call stmt case
			Assert::IsTrue(result == expected);

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
		
		TEST_METHOD(getAllUsesStmtPair) {
			PKBUses pkb; 
			DOUBLE_COL_TABLE result = pkb.getAllUsesStmtPair("if");
			DOUBLE_COL_TABLE expected =
			{ { {"10"} , {"x"} } };
			Assert::IsTrue(result == expected);

			result = pkb.getAllUsesStmtPair("while");
			expected =
			{ { {"6"} , {"i"} }
			,{ {"6"} , {"x"} } 
			,{ {"6"} , {"y"} } };
			Assert::IsTrue(result == expected);

			result = pkb.getAllUsesStmtPair("print");
			expected =
			{ { {"18"} , {"v"} } };
			Assert::IsTrue(result == expected);

			result = pkb.getAllUsesStmtPair("assign");
			expected =
			{ { {"7"} , {"x"} }
			,{ {"7"} , {"y"} }
			,{ {"9"} , {"i"} }
			,{ {"11"} , {"x"} } 
			,{ {"13"} , {"z"} } 
			,{ {"13"} , {"x"} } 
			,{ {"13"} , {"i"} } 
			,{ {"14"} , {"z"} } 
			,{ {"15"} , {"x"} }
			,{ {"15"} , {"y"} }
			,{ {"15"} , {"z"} }
			,{ {"17"} , {"z"} } };
			Assert::IsTrue(result == expected);

			result = pkb.getAllUsesStmtPair("call");
			expected =
			{ { {"3"} , {"x"} }
			,{ {"3"} , {"y"} }
			,{ {"3"} , {"i"} }
			,{ {"3"} , {"z"} }
			,{ {"3"} , {"v"} }
			,{ {"8"} , {"z"}}
			,{ {"8"} , {"v"} } };

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
			PKBUses pkb;
			PROC_LIST expected = { {"x"}, {"y"},{"z"}, {"i"}, {"v"} };
			PROC_LIST result = pkb.getUsesVarByProc("First");
			Assert::IsTrue(result == expected);

			result = pkb.getUsesVarByProc("Second");
			Assert::IsTrue(result == expected);

			expected = { {"z"}, {"v"} };
			result = pkb.getUsesVarByProc("Third");
			Assert::IsTrue(result == expected);
		}

		TEST_METHOD(getAllUsesProcPair) {
			PKBUses pkb; 
			DOUBLE_COL_TABLE expected = 
			{ { {"First"} , {"x"} }
			, { {"First"} , {"y"} }
			, { {"First"} , {"z"} } 
			, { {"First"} , {"i"} } 
			, { {"First"} , {"v"} }
			, { {"Second"} , {"x"} }
			, { {"Second"} , {"y"} }
			, { {"Second"} , {"z"} }
			, { {"Second"} , {"i"} }
			, { {"Second"} , {"v"} }
			, { {"Third"} , {"z"} }
			, { {"Third"} , {"v"} } };

			DOUBLE_COL_TABLE result = pkb.getAllUsesProcPair(); 
			Assert::IsTrue(result == expected);
		}

	};




}


