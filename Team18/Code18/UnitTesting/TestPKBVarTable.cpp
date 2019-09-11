#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKB.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(PKBTest)
	{
	public:
		TEST_METHOD_INITIALIZE(PKB_START)
		{
			PKB pkb;
			pkb.clear();
			pkb.setStmt(1, While);
			pkb.setStmt(2, If);
			pkb.setStmt(3, Print);
			pkb.setStmt(4, Read);

			pkb.setVar("x");
			pkb.setVar("y");
			pkb.setVar("z");

			pkb.setConstant("1");
			pkb.setConstant("1");
			pkb.setConstant("1");

			pkb.setModifiesVarByStmt(1, "x");
			pkb.setUsesVarByStmt(1, "x");

			pkb.setModifiesStmtByVar(1, "y");
			pkb.setUsesStmtByVar(1, "y");
		}
		TEST_METHOD(GetStmt)
		{
			//Actual PKB Data
			unordered_set<int> stmtNoList = { 1,2,3,4 };
			Assert::IsTrue(PKB().getAllStmt() == stmtNoList);
		}
		TEST_METHOD(GetVar)
		{
			//Actual PKB Data
			unordered_set<string> varList = { "x","y","z" };
			Assert::IsTrue(PKB().getAllVar() == varList);
		}
		TEST_METHOD(GetConstant)
		{
			//Actual PKB Data
			unordered_set<string> consList = {"1"};
			Assert::IsTrue(PKB().getAllConstant() == consList);
		}
		TEST_METHOD(GetModifiesStmtByVar)
		{
			//Actual PKB Data
			unordered_set<string> varList = { "x" };
			Assert::IsTrue(PKB().getModifiesVarByStmt(1) == varList);
			Assert::IsTrue(PKB().getUsesVarByStmt(1) == varList);
		}
		TEST_METHOD(GetModifiesVarByStmt)
		{
			//Actual PKB Data
			unordered_set<int> stmtList = { 1 };
			Assert::IsTrue(PKB().getModifiesStmtByVar("y") == stmtList);
			Assert::IsTrue(PKB().getUsesStmtByVar("y") == stmtList);
		}
		TEST_METHOD(isModifies)
		{
			Assert::IsTrue(PKB().isModifiesStmtVar(1,"x"));
			Assert::IsFalse(PKB().isModifiesStmtVar(1,"y"));
		}
		TEST_METHOD(isUses)
		{
			Assert::IsTrue(PKB().isUsesStmtVar(1, "x"));
			Assert::IsFalse(PKB().isUsesStmtVar(1, "y"));
		}
	};
}