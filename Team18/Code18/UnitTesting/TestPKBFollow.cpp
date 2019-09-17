#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKBFollow.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(PKBFollowTest)
	{
	public:
		TEST_METHOD_INITIALIZE(PKB_START)
		{
			PKBFollow PKBFollow;
			PKBFollow.clear();
			PKBFollow.setFollow(1, 2);
			PKBFollow.setFollowedBy(1, 2);
		}
		TEST_METHOD(GetFollowedBy)
		{
			//Actual PKB Data
			unordered_set<int> stmtNoList = { 1 };
			Assert::IsTrue(PKBFollow().getFollowedByStmtList(2) == stmtNoList);
		}
		TEST_METHOD(GetFollow)
		{
			//Actual PKB Data
			int follow = 2;
			Assert::IsTrue(PKBFollow().getFollow(1) == follow);
		}


	};
};


