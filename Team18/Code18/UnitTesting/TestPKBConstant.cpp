#include "stdafx.h"
#include "CppUnitTest.h"
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

			PKBConstant PKB;
			PKB.clear();

			PKB.setConstant("4", "0");
			PKB.setConstant("5", "5");
			PKB.setConstant("7", "2");
			PKB.setConstant("9", "1");
			PKB.setConstant("14", "2");
			PKB.setConstant("13", "14");
			PKB.setConstant("12", "1");
			PKB.setConstant("16", "5");
		}

		TEST_METHOD(getAllConstantStmtByVal)
		{
			PKBConstant PKB;
			STMT_LIST actual = PKB.getAllConstantStmtByVal("0");
			STMT_LIST expected = { { "4" } };
			Assert::IsTrue(actual == expected);
		}
	};
};


