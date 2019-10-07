#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKB.h"
#include "PKBFollow.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(PKBWrapperTest)
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
			pkb.setStmt(1, Assign);
			pkb.setStmt(2, Assign);
			pkb.setStmt(3, If);
			//pkb.setIfStmt(3);
			pkb.setStmt(4, Assign);
			pkb.setStmt(5, Assign);
			pkb.setStmt(6, While);
			//pkb.setWhileStmt(6); 
			pkb.setStmt(7, Read);
			pkb.setReadStmt(7, "x");
			pkb.setStmt(8, Print);
			pkb.setPrintStmt(8, "x");
			

			pkb.setVar("x");
			pkb.setVar("y");
			pkb.setVar("z");

			pkb.insertAssignRelation(1, "x", {}, {"1"});
			pkb.insertAssignRelation(2, "y", {"x"}, {} );
			pkb.insertAssignRelation(4, "z", { }, { "0" } );
			pkb.insertAssignRelation(5, "z", { }, { "1" });
			
			pkb.setUsesStmt(9, "x");
			pkb.setUsesVarByStmt(9, "x");

			pkb.setParentRelation(1, 2);
			pkb.setParentRelation(1, 3);
			pkb.setParentStarRelation(1, 3);

			pkb.setFollowsRelation(1, 2);
			pkb.setFollowsStarRelation(1, 2);
		}
		/*
		TEST_METHOD(GetModifiesVarByStmt)
		{
			//Test stmt #1 x=1
			unordered_set<string> varList = { "x" };
			Assert::IsTrue(PKB().getModifiesVarByStmt(1) == varList);
			//Test stmt #2 y=x
			varList = { "y" };
			Assert::IsTrue(PKB().getModifiesVarByStmt(2) == varList);
			//Test stmt #4 z=0 and #5 z=1
			varList = { "z" };
			Assert::IsTrue(PKB().getModifiesVarByStmt(4) == varList);
			Assert::IsTrue(PKB().getModifiesVarByStmt(5) == varList);
		}
		TEST_METHOD(GetModifiesStmtByVar)
		{
			unordered_set<int> stmtList = {1,8};
			unordered_set<int>  res;
			res = PKB().getModifiesStmtByVar("x"); 
			Assert::IsTrue(res == stmtList);
			
			unordered_set<int> stmtList2 = { 2 };
			res = PKB().getModifiesStmtByVar("y");
			Assert::IsTrue(  res == stmtList2);

			stmtList = { 4, 5 };
			res  = PKB().getModifiesStmtByVar("z");
			
			Assert::IsTrue(res == stmtList);	
		}
		*/
		TEST_METHOD(StmtByVar)
		{
			unordered_set<int> resX = { 1 };
			unordered_set<int> resY = { 2 };
			unordered_set<int> resZ = { 4,5 };

			Assert::IsTrue(PKB().getAssignStmtByVar("x") == resX);
			Assert::IsTrue(PKB().getAssignStmtByVar("y") == resY);
			Assert::IsTrue(PKB().getAssignStmtByVar("z") == resZ);
		}

		TEST_METHOD(getVarModifiedByAssignStmt)
		{
			//Test stmt #1 x=1
			string var = "x" ;
			Assert::IsTrue(PKB().getVarModifiedByAssignStmt(1) == var);
			//Test stmt #2 y=x
			var = "y"; 
			Assert::IsTrue(PKB().getVarModifiedByAssignStmt(2) == var);
			//Test stmt #4 z=0 and #5 z=1
			var = "z";
			Assert::IsTrue(PKB().getVarModifiedByAssignStmt(4) == var);
			Assert::IsTrue(PKB().getVarModifiedByAssignStmt(5) == var);
			
			
		};
		
		TEST_METHOD(isConstUsedInAssign){
			Assert::IsTrue(PKB().isConstUsedInAssign(1, "1"));
			Assert::IsTrue(PKB().isConstUsedInAssign(4, "0"));
			Assert::IsTrue(PKB().isConstUsedInAssign(5, "1"));
			
		};

		TEST_METHOD(isVarUsedInAssign){
			Assert::IsTrue(PKB().isVarUsedInAssign(2, "x"));
		};
		TEST_METHOD(ParentStarRelationship)
		{
			//Actual PKB Data
			Assert::IsTrue(PKB().isParentStarRelationship(1, 3));
		}
		
		
	};
};
		
		
