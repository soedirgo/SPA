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
			PKB.setProcedure("First", "1", { {"3"} });
			PKB.setProcedure("Second","4", { {"15"} });
			PKB.setProcedure("Third","16", { {"18"} });

			PKB.setCallProc("First", "Second");
			PKB.setCallProc("Second", "Third");

			PKB.setCallStmt("3", "Second");
			PKB.setCallStmt("8", "Third");

			DesignExtractor DesignExtractor;
			DesignExtractor.extractDesign();
		}
		//Calls(_ , _)
		TEST_METHOD(isCallsAnyAny)
		{
			PKBCall PKB;
			Assert::IsTrue(PKB.isCallsAnyAny());
		}
		//Calls(_,"First")
		TEST_METHOD(isCallsAnyIdent)
		{
			PKBCall PKB;
			Assert::IsFalse(PKB.isCallsAnyIdent("First"));
			Assert::IsTrue(PKB.isCallsAnyIdent("Second"));
			Assert::IsTrue(PKB.isCallsAnyIdent("Third"));
		}
		//Calls("First",_)
		TEST_METHOD(isCallsIdentAny)
		{
			PKBCall PKB;
			Assert::IsTrue(PKB.isCallsIdentAny("First"));
			Assert::IsTrue(PKB.isCallsIdentAny("Second"));
			Assert::IsFalse(PKB.isCallsIdentAny("Third"));
		}
		//Calls("First","Second")
		TEST_METHOD(isCallsIdentIdent)
		{
			PKBCall PKB;
			Assert::IsTrue(PKB.isCallsIdentIdent("First", "Second"));
			Assert::IsTrue(PKB.isCallsIdentIdent("Second", "Third"));
		}
		//Calls(_,proc2)
		TEST_METHOD(getCallsAnyEnt)
		{
			PKBCall PKB;
			TABLE actual, expected;

			actual = PKB.getCallsAnyEnt();
			expected = { {"Second"} ,{"Third"} };
			Assert::IsTrue(actual == expected);
		}
		//Calls(proc1,_)
		TEST_METHOD(getCallsEntAny)
		{
			PKBCall PKB;
			TABLE actual, expected;

			actual = PKB.getCallsEntAny();
			expected = { {"First"} ,{"Second"} };
			Assert::IsTrue(actual == expected);
		}
		//Calls(proc1,proc2)
		TEST_METHOD(getCallsEntEnt)
		{
			PKBCall PKB;
			TABLE actual, expected;

			actual = PKB.getCallsEntEnt();
			expected = { {"First","Second"} ,{"Second","Third"} };
			Assert::IsTrue(actual == expected);
		}

		//Calls(proc,"First")
		TEST_METHOD(CallsEntIdent)
		{
			PKBCall PKB;
			LIST_OF_PROC_NAME actual, expected;

			actual = PKB.getCallsEntIdent("First");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getCallsEntIdent("Second");
			expected = { {"First"} };
			Assert::IsTrue(actual == expected);
		}
		//Calls("First",proc)
		TEST_METHOD(CallsIdentEnt)
		{
			PKBCall PKB;
			LIST_OF_PROC_NAME actual, expected;

			actual = PKB.getCallsIdentEnt("Third");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getCallsIdentEnt("First");
			expected = { {"Second"} };
			Assert::IsTrue(actual == expected);
		}
		//Calls*(_,_)
		TEST_METHOD(isCallsTAnyAny)
		{
			PKBCall PKB;
			Assert::IsTrue(PKB.isCallsTAnyAny());
		}
		//Calls*(_,"First")
		TEST_METHOD(isCallsTAnyIdent)
		{
			PKBCall PKB;
			Assert::IsFalse(PKB.isCallsTAnyIdent("First"));
			Assert::IsTrue(PKB.isCallsTAnyIdent("Second"));
			Assert::IsTrue(PKB.isCallsTAnyIdent("Third"));
		}
		//Calls*("First",_)
		TEST_METHOD(isCallsTIdentAny)
		{
			PKBCall PKB;
			Assert::IsTrue(PKB.isCallsTIdentAny("First"));
			Assert::IsTrue(PKB.isCallsTIdentAny("Second"));
			Assert::IsFalse(PKB.isCallsTIdentAny("Third"));
		}

		//Calls*("First","Second")
		TEST_METHOD(CallStarRelationship)
		{
			PKBCall PKB;
			Assert::IsTrue(PKB.isCallsTIdentIdent("First", "Second"));
			Assert::IsTrue(PKB.isCallsTIdentIdent("Second", "Third"));
			Assert::IsTrue(PKB.isCallsTIdentIdent("First", "Third"));
		}
		//Calls*(_,proc2)
		TEST_METHOD(getCallsTAnyEnt)
		{
			PKBCall PKB;
			TABLE actual, expected;

			actual = PKB.getCallsTAnyEnt();
			expected = { {"Second"} ,{"Third"} };
			Assert::IsTrue(actual == expected);
		}
		//Calls*(proc1,_)
		TEST_METHOD(getCallsTEntAny)
		{
			PKBCall PKB;
			TABLE actual, expected;

			actual = PKB.getCallsTEntAny();
			expected = { {"First"} ,{"Second"} };
			Assert::IsTrue(actual == expected);
		}
		//Calls*(proc1,proc2)
		TEST_METHOD(getCallsTEntEnt)
		{
			PKBCall PKB;
			TABLE actual, expected;

			actual = PKB.getCallsTEntEnt();
			expected = { {"First","Second"} ,{"Second","Third"}, {"First","Third"} };
			Assert::IsTrue(actual == expected);

			Assert::IsTrue(PKB.isCallsTAnyAny());
		}

		//Calls*(proc,"First")
		TEST_METHOD(getCallsTEntIdent)
		{
			PKBCall PKB;
			LIST_OF_PROC_NAME actual, expected;

			actual = PKB.getCallsTEntIdent("First");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getCallsTEntIdent("Third");
			expected = { {"First"}, {"Second"} };
			Assert::IsTrue(actual == expected);
		}
		//Calls*("First",proc)
		TEST_METHOD(getCallsTIdentEnt)
		{
			PKBCall PKB;
			LIST_OF_PROC_NAME actual, expected;

			actual = PKB.getCallsTIdentEnt("Third");
			Assert::IsTrue(actual.size() == 0);

			actual = PKB.getCallsTIdentEnt("First");
			expected = { {"Second"},{"Third"} };
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(getCallProcedure)
		{
			PKBCall PKB;
			PROC_NAME actual = PKB.getCallProcByStmt("3");
			PROC_NAME expected = "Second";
			Assert::IsTrue(actual == expected);
		}
	};
};