#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKBVariable.h"
#include "DesignExtractor.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(PKBVariableTest)
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

			PKBVariable PKB;
			PKB.clear();

			PKB.setVar("x");
			PKB.setVar("z");
			PKB.setVar("i");
			PKB.setVar("y");
			PKB.setVar("v");

			//Extra insert test
			PKB.setVar("x");
			PKB.setVar("y");
			PKB.setVar("z");

		}

		TEST_METHOD(getAllVar)
		{
			PKBVariable PKB;
			VAR_LIST actual = PKB.getAllVar();
			VAR_LIST expected = { {"x"},{"z"},{"i"},{"y"},{"v"} };
			Assert::IsTrue(actual == expected);
		}
	};
};


