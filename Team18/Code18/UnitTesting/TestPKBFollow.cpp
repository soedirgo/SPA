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
			PKBFollow.setFollowStar(1, 2);
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
			Assert::IsTrue(PKBFollow().getFollowStmt(1) == follow);
		}
		TEST_METHOD(GetFollowStar)
		{
			//Actual PKB Data
			unordered_set<int> stmtNoList = { 2 };
			Assert::IsTrue(PKBFollow().getFollowStarStmtList(1) == stmtNoList);
		}
		TEST_METHOD(FollowRelationship)
		{
			//Actual PKB Data
			Assert::IsTrue(PKBFollow().isFollowRelationship(1,2));
		}
		TEST_METHOD(FollowStarRelationship)
		{
			//Actual PKB Data
			Assert::IsTrue(PKBFollow().isFollowStarRelationship(1, 2));
		}
	};
};


