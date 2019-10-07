#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKB.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(PKBUses)
	{
	public:
		TEST_METHOD_INITIALIZE(PKB_START)
		{
			/**
			   SIMPLE program:
			   _   procedure main {
			   1.      x = 1
			   2.      y = x
			   3.      if (x == y) then {
			   4.          z = 0;
			   _       } else {
			   5.          z = 1;
			   _       }
			   6.      while (x > 0) {
			   7.          read x;
			   8.          print x;
			   _       }
			*/

			PKB pkb;

			pkb.clear();

			pkb.setProc("main");

			pkb.setStmt(1, Assign);
			pkb.setAssignStmt(1, "x");
			pkb.setVar("x");
			pkb.setConstant("1", 1);
			pkb.insertModifiesRelation(1, "x");

			pkb.setStmt(2, Assign);
			pkb.setAssignStmt(2, "y");
			pkb.setVar("y");
			pkb.insertUsesRelation(2, "x");
			pkb.insertModifiesRelation(2, "y");
			pkb.insertFollowsRelation(1, 2);
			pkb.insertFollowsStarRelation(1, 2);

			pkb.setStmt(3, If);
			//pkb.setIfStmt(3);
			pkb.insertUsesRelation(3, "x");
			pkb.insertUsesRelation(3, "y");
			pkb.insertModifiesRelation(3, "z");
			pkb.insertFollowsRelation(2, 3);
			pkb.insertFollowsStarRelation(1, 3);
			pkb.insertFollowsStarRelation(2, 3);

			pkb.setStmt(4, Assign);
			pkb.setAssignStmt(4, "z");
			pkb.setVar("z");
			pkb.setConstant("0", 4);
			pkb.insertModifiesRelation(4, "z");
			pkb.insertParentRelation(3, 4);
			pkb.insertParentStarRelation(3, 4);

			pkb.setStmt(5, Assign);
			pkb.setAssignStmt(5, "z");
			pkb.insertModifiesRelation(5, "z");
			pkb.setConstant("1", 5);
			pkb.insertParentRelation(3, 5);
			pkb.insertParentStarRelation(3, 5);

			pkb.setStmt(6, While);
			//pkb.setWhileStmt(6);
			pkb.insertUsesRelation(6, "x");
			pkb.insertModifiesRelation(6, "x");
			pkb.insertFollowsRelation(3, 6);
			pkb.insertFollowsStarRelation(1, 6);
			pkb.insertFollowsStarRelation(2, 6);
			pkb.insertFollowsStarRelation(3, 6);

			pkb.setStmt(7, Read);
			pkb.setReadStmt(7, "x");
			pkb.insertModifiesRelation(7, "x");
			pkb.insertParentRelation(6, 7);
			pkb.insertParentStarRelation(6, 7);

			pkb.setStmt(8, Print);
			pkb.setPrintStmt(8, "x");
			pkb.insertUsesRelation(8, "x");
			pkb.insertParentRelation(6, 8);
			pkb.insertParentStarRelation(6, 8);
			pkb.insertFollowsRelation(7, 8);
			pkb.insertFollowsStarRelation(7, 8);

		}
		TEST_METHOD(GetUsesStmtByVariable)
		{
			//Actual PKB Data
			unordered_set<int> stmtNoList = { 2, 3, 6, 8 };
			Assert::IsTrue(PKB().getUsesStmtByVar("x") == stmtNoList);
		}
	};
};


