#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKBUses.h"
#include "DesignExtractor.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(PKBUsesTest)
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

			PKBUses PKB;
			PKB.clear();

			PKB.setUsesStmt("6", "i");
			PKB.setUsesStmt("7", "x");
			PKB.setUsesStmt("7", "y");
			PKB.setUsesStmt("9", "i");
			PKB.setUsesStmt("6", "x");
			PKB.setUsesStmt("6", "y");
			PKB.setUsesStmt("6", "i");
			PKB.setUsesStmt("10", "x");
			PKB.setUsesStmt("11", "x");
			PKB.setUsesStmt("13", "z");
			PKB.setUsesStmt("13", "x");
			PKB.setUsesStmt("14", "z");
			PKB.setUsesStmt("15", "x");
			PKB.setUsesStmt("15", "y");
			PKB.setUsesStmt("15", "z");
			PKB.setUsesStmt("17", "z");
			PKB.setUsesStmt("18", "v");

			PKB.setUsesProc("Second", "i");
			PKB.setUsesProc("Second", "x");
			PKB.setUsesProc("Second", "y");
			PKB.setUsesProc("Second", "z");
			PKB.setUsesProc("Third", "v");

			PKB.setUsesProc("Second", "v");
			PKB.setUsesProc("First", "i");
			PKB.setUsesProc("First", "x");
			PKB.setUsesProc("First", "y");
			PKB.setUsesProc("First", "z");
			PKB.setUsesProc("First", "v");
		}

		TEST_METHOD(UsesStmtRelationship)
		{
			PKBUses PKB;
			Assert::IsTrue(PKB.isUsesStmtRelationship("6", "i"));
			Assert::IsTrue(PKB.isUsesStmtRelationship("7", "x"));
			Assert::IsTrue(PKB.isUsesStmtRelationship("7", "y"));
			Assert::IsTrue(PKB.isUsesStmtRelationship("9", "i"));
			Assert::IsTrue(PKB.isUsesStmtRelationship("6", "x"));
			Assert::IsTrue(PKB.isUsesStmtRelationship("6", "y"));
			Assert::IsTrue(PKB.isUsesStmtRelationship("10", "x"));
			Assert::IsTrue(PKB.isUsesStmtRelationship("11", "x"));
			Assert::IsTrue(PKB.isUsesStmtRelationship("13", "z"));
			Assert::IsTrue(PKB.isUsesStmtRelationship("13", "x"));
			Assert::IsTrue(PKB.isUsesStmtRelationship("14", "z"));
			Assert::IsTrue(PKB.isUsesStmtRelationship("15", "x"));
			Assert::IsTrue(PKB.isUsesStmtRelationship("15", "y"));
			Assert::IsTrue(PKB.isUsesStmtRelationship("15", "z"));
			Assert::IsTrue(PKB.isUsesStmtRelationship("17", "z"));
			Assert::IsTrue(PKB.isUsesStmtRelationship("18", "v"));
		}
		TEST_METHOD(UsesProcRelationship)
		{
			PKBUses PKB;
			Assert::IsTrue(PKB.isUsesProcRelationship("Second", "x"));
			Assert::IsTrue(PKB.isUsesProcRelationship("Second", "y"));
			Assert::IsTrue(PKB.isUsesProcRelationship("Second", "z"));
		}
	};
};


