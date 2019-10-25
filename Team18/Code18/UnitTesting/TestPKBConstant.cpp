#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKB.h"
#include "PKBConstant.h"
#include "DesignExtractor.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(PKBConstantTest)
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

			PKB.setConstant("0");
			PKB.setConstant("5");
			PKB.setConstant("2");
			PKB.setConstant("1");
			PKB.setConstant("2");
			PKB.setConstant("14");
			PKB.setConstant("1");
			PKB.setConstant("5");
		}

		TEST_METHOD(getAllConstantStmtByVal)
		{
			PKBConstant PKB;
			STMT_LIST actual = PKB.getConstants();
			STMT_LIST expected = { { "0" },{ "5" },{ "2" },{ "1" },{ "2" },{ "14" }};
			Assert::IsTrue(actual == expected);
		}
	};
};


