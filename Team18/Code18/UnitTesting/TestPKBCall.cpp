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
			PKB.setProc("First");
			PKB.setProc("Second");
			PKB.setProc("Third");

			PKB.setCallProc("First", "Second");
			PKB.setCallProc("Second", "Third");

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

		TEST_METHOD(CallGenericBoth)
		{
			PKBCall PKB;
			TABLE actual, expected;

			actual = PKB.getAllCallerCalleeProc();
			expected = { {"First","Second"} ,{"Second","Third"} };
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(CallGenericLeft)
		{
			PKBCall PKB;
			PROC_LIST actual, expected;

			actual = PKB.getAllCallerProc("First");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getAllCallerProc("Second");
			expected = { {"First"} };
			Assert::IsTrue(actual == expected);
		}
		TEST_METHOD(CallGenericRight)
		{
			PKBCall PKB;
			PROC_LIST actual, expected;

			actual = PKB.getAllCalleProc("Third");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getAllCalleProc("First");
			expected = { {"Second"} };
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(CallStarGenericBoth)
		{
			PKBCall PKB;
			TABLE actual, expected;

			actual = PKB.getAllCallerCalleeStarProc();
			expected = { {"First","Second"} ,{"Second","Third"}, {"First","Third"} };
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(CallStarGenericLeft)
		{
			PKBCall PKB;
			PROC_LIST actual, expected;

			actual = PKB.getAllCallerStarProc("First");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getAllCallerStarProc("Third");
			expected = { {"First"}, {"Second"} };
			Assert::IsTrue(actual == expected);
		}
		TEST_METHOD(CallStarGenericRight)
		{
			PKBCall PKB;
			PROC_LIST actual, expected;

			actual = PKB.getAllCalleStarProc("Third");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getAllCalleStarProc("First");
			expected = { {"Second"},{"Third"} };
			Assert::IsTrue(actual == expected);
		}
	};
};


