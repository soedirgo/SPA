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
			PKB.setProcedure("First");
			PKB.setProcedure("Second");
			PKB.setProcedure("Third");

			PKB.setCallProc("First", "Second");
			PKB.setCallProc("Second", "Third");

			PKB.setCallStmt("3", "Second");
			PKB.setCallStmt("8", "Third");

			DesignExtractor DesignExtractor;
			DesignExtractor.extractDesign();
		}

		TEST_METHOD(CallRelationship)
		{
			PKBCall PKB;
			Assert::IsTrue(PKB.isCallsIdentIdent("First", "Second"));
			Assert::IsTrue(PKB.isCallsIdentIdent("Second", "Third"));
		}

		TEST_METHOD(CallStarRelationship)
		{
			PKBCall PKB;
			Assert::IsTrue(PKB.isCallsTIdentIdent("First", "Second"));
			Assert::IsTrue(PKB.isCallsTIdentIdent("Second", "Third"));
			Assert::IsTrue(PKB.isCallsTIdentIdent("First", "Third"));
		}

		TEST_METHOD(CallGenericBoth)
		{
			PKBCall PKB;
			TABLE actual, expected;

			actual = PKB.getCallsEntEnt();
			expected = { {"First","Second"} ,{"Second","Third"} };
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(CallGenericLeft)
		{
			PKBCall PKB;
			PROC_LIST actual, expected;

			actual = PKB.getCallsEntIdent("First");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getCallsEntIdent("Second");
			expected = { {"First"} };
			Assert::IsTrue(actual == expected);
		}
		TEST_METHOD(CallGenericRight)
		{
			PKBCall PKB;
			PROC_LIST actual, expected;

			actual = PKB.getCallsIdentEnt("Third");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getCallsIdentEnt("First");
			expected = { {"Second"} };
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(CallStarGenericBoth)
		{
			PKBCall PKB;
			TABLE actual, expected;

			actual = PKB.getCallsTEntEnt();
			expected = { {"First","Second"} ,{"Second","Third"}, {"First","Third"} };
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(CallStarGenericLeft)
		{
			PKBCall PKB;
			PROC_LIST actual, expected;

			actual = PKB.getCallsTEntIdent("First");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getCallsTEntIdent("Third");
			expected = { {"First"}, {"Second"} };
			Assert::IsTrue(actual == expected);
		}
		TEST_METHOD(CallStarGenericRight)
		{
			PKBCall PKB;
			PROC_LIST actual, expected;

			actual = PKB.getCallsIdentEnt("Third");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getCallsIdentEnt("First");
			expected = { {"Second"},{"Third"} };
			Assert::IsTrue(actual == expected);
		}
	};
};


