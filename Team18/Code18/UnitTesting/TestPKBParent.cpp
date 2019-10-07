#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKBParent.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(PKBParentTest)
	{
	public:
		TEST_METHOD_INITIALIZE(PKB_START)
		{
			PKBParent PKBParent;
			PKBParent.clear();
			//PKBParent.setChildren(1,2);
			//PKBParent.setChildren(1,3);

			PKBParent.setParent(1, 2);
			PKBParent.setParent(1, 3);

			PKBParent.setParentStar(1, 3);
		}
		/*
		TEST_METHOD(GetChildren)
		{
			//Actual PKB Data
			unordered_set<int> stmtNoList = { 2,3 };
			Assert::IsTrue(PKBParent().getChildrenStmtList(1) == stmtNoList);
		}
		TEST_METHOD(GetParent)
		{
			//Actual PKB Data
			int parent = 1;
			Assert::IsTrue(PKBParent().getParentStmt(2) == parent);
		}

		TEST_METHOD(GetParentStar)
		{
			//Actual PKB Data
			unordered_set<int> stmtNoList = { 1 };
			Assert::IsTrue(PKBParent().getParentStarStmtList(3) == stmtNoList);
		}
		
		TEST_METHOD(ParentRelationship)
		{
			//Actual PKB Data
			Assert::IsTrue(PKBParent().isParentRelationship(1, 2));
		}
		TEST_METHOD(ParentStarRelationship)
		{
			//Actual PKB Data
			Assert::IsTrue(PKBParent().isParentStarRelationship(1, 3));
		}
		*/
	};
};


