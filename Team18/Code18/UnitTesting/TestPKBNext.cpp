#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKBNext.h"
#include "PKB.h"
#include "DesignExtractor.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(PKBNextTest)
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

			PKB.setNextRelation("1", "2");
			PKB.setNextRelation("2", "3");
			PKB.setNextRelation("4", "5");
			PKB.setNextRelation("5", "6");
			PKB.setNextRelation("6", "7");
			PKB.setNextRelation("7", "8");
			PKB.setNextRelation("8", "9");
			PKB.setNextRelation("9", "6");
			PKB.setNextRelation("6", "10");
			PKB.setNextRelation("10", "11");
			PKB.setNextRelation("10", "12");
			PKB.setNextRelation("11", "13");
			PKB.setNextRelation("12", "13");
			PKB.setNextRelation("13", "14");
			PKB.setNextRelation("14", "15");
			PKB.setNextRelation("16", "17");
			PKB.setNextRelation("17", "18");
			PKB.setNextRelation("18", "19");
		}
		TEST_METHOD(NextRelationship)
		{
			PKBNext PKB;
			Assert::IsTrue(PKB.isNextRelationship("1", "2"));
		}
	};
};


