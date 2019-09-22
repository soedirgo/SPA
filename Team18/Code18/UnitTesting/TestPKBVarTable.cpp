#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKB.h"

using namespace std;
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
			pkb.setStmt(7, Call);
			pkb.setStmt(10, Call);
			pkb.setStmt(11, Call);
			pkb.setStmt(12, Call);
			

			pkb.setVar("x");
			pkb.setVar("y");
			pkb.setVar("z");

			pkb.setConstant("1", 3);
			pkb.setConstant("1", 4);
			pkb.setConstant("1", 5);

			pkb.setModifiesVarByStmt(1, "x");
			pkb.setUsesVarByStmt(1, "x");

			pkb.setModifiesStmtByVar(1, "y");
			pkb.setUsesStmtByVar(1, "y");

			pkb.setAssignStmt(1, "x");
			pkb.setAssignStmt(3, "y");
			pkb.setAssignStmt(6, "z");
			pkb.setAssignStmt(7, "z");
			pkb.setAssignStmt(8, "x");

			pkb.setStmt(13, Assign);
			pkb.setStmt(14, Assign);
			pkb.setStmt(15, Assign);
			pkb.setAssignStmtByVar(1, "x");
			pkb.setAssignStmtByVar(3, "y");
			pkb.setAssignStmtByVar(6, "z");
			pkb.setAssignStmtByVar(7, "z");
			pkb.setAssignStmtByVar(8, "x");

			pkb.setWhileStmt(1); 
			pkb.setWhileStmt(6);
			pkb.setWhileStmt(9);

			pkb.setIfStmt(1);
			pkb.setIfStmt(9);
			pkb.setIfStmt(10);

			pkb.setPrintStmt(3, "x");
			pkb.setPrintStmt(5, "x");

			pkb.setReadStmt(4, "x");

			pkb.setProc("Proc1");
			pkb.setProc("Proc2");

			pkb.setCallStmt(7, "Proc1");
			pkb.setCallStmt(10, "Proc2");
			pkb.setCallStmt(11, "Proc3");
			pkb.setCallStmt(12, "Proc1");

		}
		TEST_METHOD(GetStmt)
		{
			//Actual PKB Data
			unordered_set<int> stmtNoList = { 1,2,3,4,7,10,11,12,13,14,15 };
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
			unordered_set<string> consList = { "1" };
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
			Assert::IsTrue(PKB().isModifiesStmtVar(1, "x"));
			Assert::IsFalse(PKB().isModifiesStmtVar(1, "y"));
		}
		TEST_METHOD(isUses)
		{
			Assert::IsTrue(PKB().isUsesStmtVar(1, "x"));
			Assert::IsFalse(PKB().isUsesStmtVar(1, "y"));
		};
		TEST_METHOD(getAllAssignStmt)
		{
			unordered_set<int> stmtNoList = {13,14,15};
			Assert::IsTrue(PKB().getAllAssignStmt() == stmtNoList);
		};

		TEST_METHOD(getVarModifiedByAssignStmt)
		{
			
			Assert::IsTrue(PKB().getVarModifiedByAssignStmt(1) == "x");
			Assert::IsTrue(PKB().getVarModifiedByAssignStmt(3) == "y");
			Assert::IsTrue(PKB().getVarModifiedByAssignStmt(6) == "z");
		}
		TEST_METHOD(getAssignStmtByVar)
		{
			unordered_set<int> resX = { 1,8 };
			unordered_set<int> resY = { 3 };
			unordered_set<int> resZ = { 6,7 };

			Assert::IsTrue(PKB().getAssignStmtByVar("x") == resX);
			Assert::IsTrue(PKB().getAssignStmtByVar("y") == resY);
			Assert::IsTrue(PKB().getAssignStmtByVar("z") == resZ);
		}
		
		TEST_METHOD(getAllWhileStmt)
		{
			unordered_set<int> stmtNoList = { 1,6,9 };
			Assert::IsTrue(PKB().getAllWhileStmt() == stmtNoList);
		};
		TEST_METHOD(getAllIfStmt)
		{
			unordered_set<int> stmtNoList = { 1, 2,9,10 };
			Assert::IsTrue(PKB().getAllIfStmt() == stmtNoList);
		};

		TEST_METHOD(getAllPrintStmt) {
			unordered_set<int> list = { 3 }; 
			Assert::IsTrue(PKB().getAllPrintStmt() == list);
		}

		TEST_METHOD(getPrintStmtByVar) {
			unordered_set<int> list = { 3,5 };
			Assert::IsTrue(PKB().getPrintStmtByVar("x") == list);
		}
		TEST_METHOD(getAllReadStmt) {
			unordered_set<int> list = { 4 };
			Assert::IsTrue(PKB().getAllReadStmt() == list);
		}

		TEST_METHOD(getReadStmtByVar) {
			unordered_set<int> list = { 4 };
			Assert::IsTrue(PKB().getReadStmtByVar("x") == list);
		}

		TEST_METHOD(getAllProc) {
			unordered_set<string> list = { "Proc1", "Proc2" };
			Assert::IsTrue( PKB().getAllProc() == list);
		
		}
		
		TEST_METHOD(getAllCallStmt) {
			unordered_set<int> list = { 7,10,11,12 };
			Assert::IsTrue(PKB().getAllCallStmt() == list);

		}

		TEST_METHOD(getCallStmtByVar) {
			unordered_set<int> list = { 7,12 };
			Assert::IsTrue(PKB().getCallStmtByVar("Proc1") == list);
		}
		
	};
};
		
		
