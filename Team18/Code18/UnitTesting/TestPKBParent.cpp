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
			PKBParent.setChildrenByParent(1,2);
			PKBParent.setChildrenByParent(1,3);

			PKBParent.setParentByChild(1, 2);
			PKBParent.setParentByChild(1, 3);
		}
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
	

	};
};


