#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKBFollows.h"
#include "DesignExtractor.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(PKBFollowsTest)
	{
	public:
		TEST_METHOD_INITIALIZE(PKB_START)
		{
			/**	SIMPLE program:

				procedure First {
				1.	read x;
				2.	read z;
				3.	call Second; }

				procedure Second {
				4.		x = 0;
				5.		i = 5;
				6.		while (i!=0) {
				7.			x = x + 2*y;
				8.			call Third;
				9.			i = i - 1; }
				10.		if (x==1) then {
				11.			x = x+1; }
						else {
				12.			z = 1; }
				13.		z = z + x + i;
				14.		y = z + 2;
				15.		x = x * y + z; }

					procedure Third {
				16.		z = 5;
				17.		v = z;
				18.		print v; }
		   */

			PKBFollows PKB;
			PKB.clear();

			PKB.setFollows("1", "2");
			PKB.setFollows("2", "3");
			PKB.setFollows("4", "5");
			PKB.setFollows("5", "6");
			PKB.setFollows("7", "8");
			PKB.setFollows("8", "9");
			PKB.setFollows("13", "14");
			PKB.setFollows("14", "15");
			PKB.setFollows("16", "17");
			PKB.setFollows("17", "18");

			DesignExtractor DesignExtractor;
			DesignExtractor.extractDesign();
		}

		TEST_METHOD(FollowsRelationship)
		{
			PKBFollows PKB;
			Assert::IsTrue(PKB.isFollowsRelationship("1", "2"));
			Assert::IsTrue(PKB.isFollowsRelationship("2", "3"));
			Assert::IsTrue(PKB.isFollowsRelationship("4", "5"));
			Assert::IsTrue(PKB.isFollowsRelationship("5", "6"));
			Assert::IsTrue(PKB.isFollowsRelationship("7", "8"));
			Assert::IsTrue(PKB.isFollowsRelationship("8", "9"));
			Assert::IsTrue(PKB.isFollowsRelationship("13", "14"));
			Assert::IsTrue(PKB.isFollowsRelationship("14", "15"));
			Assert::IsTrue(PKB.isFollowsRelationship("16", "17"));
			Assert::IsTrue(PKB.isFollowsRelationship("17", "18"));
		}

		TEST_METHOD(FollowsStarRelationship)
		{
			PKBFollows PKB;
			Assert::IsTrue(PKB.isFollowsStarRelationship("1", "2"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("2", "3"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("4", "5"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("5", "6"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("7", "8"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("8", "9"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("13", "14"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("14", "15"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("16", "17"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("17", "18"));

			Assert::IsTrue(PKB.isFollowsStarRelationship("1", "3"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("4", "6"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("7", "9"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("13", "15"));
			Assert::IsTrue(PKB.isFollowsStarRelationship("16", "18"));
		}
	};
};


