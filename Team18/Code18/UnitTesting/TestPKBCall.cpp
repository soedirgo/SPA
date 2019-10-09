#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKB.h"
#include "PKBCall.h"
#include "DesignExtractor.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(PKBCallTest)
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

			PKB PKB;
			PKB.clear();

			PKB.setCallProcRelation("First", "Second");
			PKB.setCallProcRelation("Second", "Third");

			PKB.setCallStmt("3", "Second");
			PKB.setCallStmt("8", "Third");

			DesignExtractor DesignExtractor;
			DesignExtractor.extractDesign();
		}

		TEST_METHOD(CallRelationship)
		{
			PKB PKB;
			Assert::IsTrue(PKB.isCallRelationship("First", "Second"));
			Assert::IsTrue(PKB.isCallRelationship("Second", "Third"));
		}

		TEST_METHOD(CallStarRelationship)
		{
			PKB PKB;
			Assert::IsTrue(PKB.isCallStarRelationship("First", "Second"));
			Assert::IsTrue(PKB.isCallStarRelationship("Second", "Third"));
			Assert::IsTrue(PKB.isCallStarRelationship("First", "Third"));
		}
	};
};


