#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKB.h"
#include "PKBModifies.h"
#include "DesignExtractor.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(PKBModifiesTest)
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

			PKB.setModifiesStmtRelation("1", "x");
			PKB.setModifiesStmtRelation("2", "z");
			PKB.setModifiesStmtRelation("4", "x");
			PKB.setModifiesStmtRelation("5", "i");
			PKB.setModifiesStmtRelation("7", "x");
			PKB.setModifiesStmtRelation("9", "i");
			PKB.setModifiesStmtRelation("11", "x");
			PKB.setModifiesStmtRelation("12", "z");
			PKB.setModifiesStmtRelation("13", "z");
			PKB.setModifiesStmtRelation("14", "y");
			PKB.setModifiesStmtRelation("15", "x");
			PKB.setModifiesStmtRelation("16", "z");
			PKB.setModifiesStmtRelation("17", "v");
			PKB.setModifiesStmtRelation("6", "x");
			PKB.setModifiesStmtRelation("6", "z");
			PKB.setModifiesStmtRelation("10", "x");
			PKB.setModifiesStmtRelation("10", "z");
			
			PKB.setModifiesProcRelation("First", "x");
			PKB.setModifiesProcRelation("First", "z");

			PKB.setModifiesProcRelation("Second", "x");
			PKB.setModifiesProcRelation("Second", "i");
			PKB.setModifiesProcRelation("Second", "y");
			PKB.setModifiesProcRelation("Second", "z");

			PKB.setModifiesProcRelation("Third", "z");
			PKB.setModifiesProcRelation("Third", "v");

			PKB.setModifiesProcRelation("Second", "z");
			PKB.setModifiesProcRelation("Second", "v");

			PKB.setModifiesProcRelation("First", "z");
			PKB.setModifiesProcRelation("First", "v");
			PKB.setModifiesProcRelation("First", "x");
			PKB.setModifiesProcRelation("First", "i");
			PKB.setModifiesProcRelation("First", "y");
			PKB.setModifiesProcRelation("First", "z");

		}

		TEST_METHOD(ModifiesStmtRelationship)
		{
			PKB PKB;
			Assert::IsTrue(PKB.isModifiesStmtRelationship("1", "x"));
			Assert::IsTrue(PKB.isModifiesStmtRelationship("2", "z"));
			Assert::IsTrue(PKB.isModifiesStmtRelationship("4", "x"));
			Assert::IsTrue(PKB.isModifiesStmtRelationship("5", "i"));
			Assert::IsTrue(PKB.isModifiesStmtRelationship("7", "x"));
			Assert::IsTrue(PKB.isModifiesStmtRelationship("9", "i"));
			Assert::IsTrue(PKB.isModifiesStmtRelationship("11", "x"));
			Assert::IsTrue(PKB.isModifiesStmtRelationship("12", "z"));
			Assert::IsTrue(PKB.isModifiesStmtRelationship("13", "z"));
			Assert::IsTrue(PKB.isModifiesStmtRelationship("14", "y"));
			Assert::IsTrue(PKB.isModifiesStmtRelationship("15", "x"));
			Assert::IsTrue(PKB.isModifiesStmtRelationship("16", "z"));
			Assert::IsTrue(PKB.isModifiesStmtRelationship("17", "v"));
			Assert::IsTrue(PKB.isModifiesStmtRelationship("6", "x"));
			Assert::IsTrue(PKB.isModifiesStmtRelationship("6", "z"));
			Assert::IsTrue(PKB.isModifiesStmtRelationship("10", "x"));
			Assert::IsTrue(PKB.isModifiesStmtRelationship("10", "z"));

		}

		TEST_METHOD(ModifiesProcRelationship)
		{
			PKB PKB;
			Assert::IsTrue(PKB.isModifiesProcRelationship("First", "x"));
			Assert::IsTrue(PKB.isModifiesProcRelationship("First", "z"));
			Assert::IsTrue(PKB.isModifiesProcRelationship("Second", "x"));
			Assert::IsTrue(PKB.isModifiesProcRelationship("Second", "i"));
			Assert::IsTrue(PKB.isModifiesProcRelationship("Second", "y"));
			Assert::IsTrue(PKB.isModifiesProcRelationship("Second", "z"));
			Assert::IsTrue(PKB.isModifiesProcRelationship("Third", "z"));
			Assert::IsTrue(PKB.isModifiesProcRelationship("Third", "v"));

			Assert::IsTrue(PKB.isModifiesProcRelationship("Second", "z"));
			Assert::IsTrue(PKB.isModifiesProcRelationship("Second", "v"));
			Assert::IsTrue(PKB.isModifiesProcRelationship("First", "z"));
			Assert::IsTrue(PKB.isModifiesProcRelationship("First", "v"));
			Assert::IsTrue(PKB.isModifiesProcRelationship("First", "x"));
			Assert::IsTrue(PKB.isModifiesProcRelationship("First", "i"));
			Assert::IsTrue(PKB.isModifiesProcRelationship("First", "y"));
			Assert::IsTrue(PKB.isModifiesProcRelationship("First", "z"));

		}
	};
};


