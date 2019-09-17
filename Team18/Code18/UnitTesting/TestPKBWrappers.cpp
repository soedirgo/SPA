#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKB.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(PKBWrapperTest)
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
			pkb.setStmt(13, Assign);
			pkb.setStmt(14, Assign);
			pkb.setStmt(15, Assign);

			pkb.setVar("x");
			pkb.setVar("y");
			pkb.setVar("z");

			pkb.setConstant("1");
			pkb.setConstant("1");
			pkb.setConstant("1");

			pkb.insertModifiesRelation(1, "x");
			pkb.insertModifiesRelation(1, "y");
			pkb.insertUsesRelation(1, "x");
			pkb.insertUsesRelation(1, "y");

			pkb.insertAssignRelation(1, "x");
			pkb.insertAssignRelation(1, "y");
			pkb.insertAssignRelation(3, "y");
			pkb.insertAssignRelation(6, "z");
			pkb.insertAssignRelation(7, "z");
			pkb.insertAssignRelation(8, "x");

			pkb.insertParentRelation(1, 2);
			pkb.insertParentRelation(1, 3);

			pkb.insertFollowRelation(1, 2);

		}
		TEST_METHOD(GetModifiesStmtByVar)
		{
			//Actual PKB Data
			unordered_set<string> varList = { "x" ,"y" };
			Assert::IsTrue(PKB().getModifiesVarByStmt(1) == varList);
			Assert::IsTrue(PKB().getUsesVarByStmt(1) == varList);
		}
		TEST_METHOD(GetModifiesVarByStmt)
		{
			//Actual PKB Data
			unordered_set<int> stmtList = { 1 };
			Assert::IsTrue(PKB().getModifiesStmtByVar("y") == stmtList);
			Assert::IsTrue(PKB().getUsesStmtByVar("y") == stmtList);
			Assert::IsTrue(PKB().getUsesStmtByVar("x") == stmtList);
			Assert::IsTrue(PKB().getUsesStmtByVar("x") == stmtList);
		}
		
		TEST_METHOD(getVarModifiedByAssignStmt)
		{

			Assert::IsTrue(PKB().getVarModifiedByAssignStmt(1) == "x");
			Assert::IsTrue(PKB().getVarModifiedByAssignStmt(3) == "y");
			Assert::IsTrue(PKB().getVarModifiedByAssignStmt(6) == "z");
		}
		TEST_METHOD(getAssignStmtByVar)
		{
			unordered_set<int> resX = { 1,8 };
			unordered_set<int> resY = { 1,3 };
			unordered_set<int> resZ = { 6,7 };

			Assert::IsTrue(PKB().getAssignStmtByVar("x") == resX);
			Assert::IsTrue(PKB().getAssignStmtByVar("y") == resY);
			Assert::IsTrue(PKB().getAssignStmtByVar("z") == resZ);
		}
		TEST_METHOD(getAllStmtByType)
		{
			unordered_set<int> stmtNoList = { 13,14,15 };
			Assert::IsTrue(PKB().getAllStmtByType("assign") == stmtNoList);
			stmtNoList = { 1,6,9 };
			Assert::IsTrue(PKB().getAllStmtByType("while") == stmtNoList);
			stmtNoList = { 1,9,10 };
			Assert::IsTrue(PKB().getAllStmtByType("if") == stmtNoList);
			stmtNoList = { 3 };
			Assert::IsTrue(PKB().getAllStmtByType("print") == stmtNoList);
			stmtNoList = { 4 };
			Assert::IsTrue(PKB().getAllStmtByType("read") == stmtNoList);
			stmtNoList = { 7,10,11,12 };
			Assert::IsTrue(PKB().getAllStmtByType("call") == stmtNoList);
		
		};

		TEST_METHOD(GetChildren)
		{
			//Actual PKB Data
			unordered_set<int> stmtNoList = { 2,3 };
			Assert::IsTrue(PKB().getChildrenStmtList(1) == stmtNoList);
		}
		TEST_METHOD(GetParent)
		{
			//Actual PKB Data
			int parent = 1;
			Assert::IsTrue(PKB().getParentStmt(2) == parent);
		}
		TEST_METHOD(GetFollowedBy)
		{
			//Actual PKB Data
			unordered_set<int> stmtNoList = { 1 };
			Assert::IsTrue(PKB().getFollowedByStmtList(2) == stmtNoList);
		}
		TEST_METHOD(GetFollow)
		{
			//Actual PKB Data
			int follow = 2;
			Assert::IsTrue(PKB().getFollow(1) == follow);
		}
		
	};
};
		
		
