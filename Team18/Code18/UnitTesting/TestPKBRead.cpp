#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKBRead.h"
#include "PKB.h"
#include "DesignExtractor.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(PKBReadTest)
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

			PKB.setReadStmt("1", "x");
			PKB.setReadStmt("2", "z");

		}

		TEST_METHOD(getReadVar)
		{
			PKBRead PKB;
			VAR_NAME actual = PKB.getReadVar("1");
			VAR_NAME expected = "x";
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(getReadStmt)
		{
			PKBRead PKB;
			STMT_LIST actual = PKB.getReadStmt("x");
			STMT_LIST expected = { {"1"} };
			Assert::IsTrue(actual == expected);
		}
	};
};


