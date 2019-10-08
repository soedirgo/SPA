#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKBParent.h"
#include "DesignExtractor.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(PKBParentTest)
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

			PKBParent PKB;
			PKB.clear();

			PKB.setParent("6", "7");
			PKB.setParent("6", "8");
			PKB.setParent("6", "9");
			PKB.setParent("10", "11");
			PKB.setParent("10", "12");

			DesignExtractor DesignExtractor;
			DesignExtractor.extractDesign();
		}

		TEST_METHOD(ParentRelationship)
		{
			PKBParent PKB;
			Assert::IsTrue(PKB.isParentRelationship("6","7"));
			Assert::IsTrue(PKB.isParentRelationship("6", "8"));
			Assert::IsTrue(PKB.isParentRelationship("6", "9"));
			Assert::IsTrue(PKB.isParentRelationship("10", "11"));
			Assert::IsTrue(PKB.isParentRelationship("10", "12"));
		}

		TEST_METHOD(ParentStarRelationship)
		{
			PKBParent PKB;
			Assert::IsTrue(PKB.isParentStarRelationship("6", "7"));
			Assert::IsTrue(PKB.isParentStarRelationship("6", "8"));
			Assert::IsTrue(PKB.isParentStarRelationship("6", "9"));
			Assert::IsTrue(PKB.isParentStarRelationship("10", "11"));
			Assert::IsTrue(PKB.isParentStarRelationship("10", "12"));
		}
	};
};


