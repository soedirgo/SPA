#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKB.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(PKBComplexMethodTest)
	{
	public:
		TEST_METHOD_INITIALIZE(PKB_START)
		{
			PKB pkb2;
			pkb2.clear();
			pkb2.setStmt(1, Assign);
			pkb2.setStmt(2, If);
			pkb2.setStmt(3, Assign);
			pkb2.setStmt(4, Call);
			pkb2.setStmt(5, Assign);
			pkb2.setStmt(6, Assign);
			pkb2.setStmt(7, Read);
			pkb2.setStmt(8, Assign);
			pkb2.setStmt(9, Print);

			pkb2.setVar("x");
			pkb2.setVar("y");
			pkb2.setVar("z");
			pkb2.setVar("i");

			pkb2.setConstant("1");

			pkb2.setUsesStmtByVar(1, "y");
			pkb2.setUsesStmtByVar(1, "x");
			pkb2.setUsesVarByStmt(1, "y");
			pkb2.setUsesVarByStmt(1, "x");
			pkb2.setModifiesStmtByVar(1, "x");
			pkb2.setModifiesVarByStmt(1, "x");

			pkb2.setUsesStmtByVar(2, "i");
			pkb2.setUsesVarByStmt(2, "i");

			pkb2.setUsesStmtByVar(2, "i");
			pkb2.setUsesVarByStmt(2, "i");
			pkb2.setModifiesStmtByVar(3, "y");
			pkb2.setModifiesVarByStmt(3, "y");
			pkb2.setUsesVarByStmt(2, "x"); //since within while loop
			//pkb.setUsesVarByProcedure(P, "y"); Don't handle procedure call for now
			pkb2.setUsesStmtByVar(5, "x");
			pkb2.setUsesVarByStmt(5, "x");
			pkb2.setUsesStmtByVar(5, "z");
			pkb2.setUsesVarByStmt(5, "z");
			pkb2.setModifiesStmtByVar(5, "z");
			pkb2.setModifiesVarByStmt(5, "z");


			pkb2.setUsesStmtByVar(6, "x");
			pkb2.setUsesVarByStmt(6, "x");
			pkb2.setModifiesStmtByVar(6, "x");
			pkb2.setModifiesVarByStmt(6, "x");

			//pkb.setUsesVarByProcedureCall(read, "y"); Don't handle procedure call for now
			pkb2.setUsesStmtByVar(8, "y");
			pkb2.setUsesVarByStmt(8, "y");
			pkb2.setModifiesStmtByVar(8, "y");
			pkb2.setModifiesVarByStmt(8, "y");
		}
		

		//Test using tutorial 2 sample program 
		/*procedure Main{
			1 x = y + (x + 1);
			2 if (i == 1) then {
			3 y = x + 1;
			4 call P;
			5 z = x + z; }
			else {
			6 x = x + 3;
			7 read y;
			} }
			procedure P{
			8 y = y + 5;
			9 print y; }*/

		TEST_METHOD(getStmtsThatModVarByAssign)
		{
			unordered_set<int>stmtList = { 1,6 };
			Assert::IsTrue(PKB().getStmtsThatModVarByAssign("x") == stmtList);
		}
	};
}