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
			PKBFollows PKBFollow;
			PKBFollow.clear();
			PKBFollow.setFollows(1, 2);
			//PKBFollows.setFollowedBy(1, 2);
			PKBFollow.setFollowsStar(1, 2);
		}
		/*
		TEST_METHOD(GetFollowedBy)
		{
			//Actual PKB Data
			unordered_set<int> stmtNoList = { 1 };
			Assert::IsTrue(PKBFollows().getFollowedByStmtList(2) == stmtNoList);
		}
		TEST_METHOD(GetFollow)
		{
			//Actual PKB Data
			int follow = 2;
			Assert::IsTrue(PKBFollows().getFollowStmt(1) == follow);
		}
		TEST_METHOD(GetFollowStar)
		{
			//Actual PKB Data
			unordered_set<int> stmtNoList = { 2 };
			Assert::IsTrue(PKBFollows().getFollowStarStmtList(1) == stmtNoList);
		}
		TEST_METHOD(FollowRelationship)
		{
			//Actual PKB Data
			Assert::IsTrue(PKBFollows().isFollowRelationship(1,2));
		}
		TEST_METHOD(FollowStarRelationship)
		{
			//Actual PKB Data
			Assert::IsTrue(PKBFollows().isFollowStarRelationship(1, 2));
		}
		*/
	};
};


