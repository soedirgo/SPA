#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKB.h"
#include "PKBPattern.h"
#include "PKBModifies.h"
#include "PKBStmt.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(PKBPatternTest)
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
			PKBStmt PKBStmt;
			PKBStmt.clear();

			PKBStmt.setStmt("1", "read");
			PKBStmt.setStmt("2", "read");
			PKBStmt.setStmt("3", "call");
			PKBStmt.setStmt("4", "assign");
			PKBStmt.setStmt("5", "assign");
			PKBStmt.setStmt("6", "while");
			PKBStmt.setStmt("7", "assign");
			PKBStmt.setStmt("8", "call");
			PKBStmt.setStmt("9", "assign");
			PKBStmt.setStmt("10", "if");
			PKBStmt.setStmt("11", "assign");
			PKBStmt.setStmt("12", "assign");
			PKBStmt.setStmt("13", "assign");
			PKBStmt.setStmt("14", "assign");
			PKBStmt.setStmt("15", "assign");
			PKBStmt.setStmt("16", "assign");
			PKBStmt.setStmt("17", "assign");
			PKBStmt.setStmt("18", "print");

			PKBPattern PKB;
			PKB.clear();

			PKBModifies PKBModifies;
			PKBModifies.clear();
			PKBModifies.setModifiesS("1","x");
			PKBModifies.setModifiesS("2", "y");

			PKBModifies.setModifiesS("4", "x");
			PKBModifies.setModifiesS("5", "i");
			PKBModifies.setModifiesS("7", "x");
			PKBModifies.setModifiesS("9", "i");
			PKBModifies.setModifiesS("11", "x");
			PKBModifies.setModifiesS("12", "z");
			PKBModifies.setModifiesS("13", "z");
			PKBModifies.setModifiesS("14", "y");
			PKBModifies.setModifiesS("15", "x");

			PKB.setAssignPattern("4", "0");
			PKB.setAssignPattern("5", "5");
			PKB.setAssignPattern("7", "x2y*+");
			PKB.setAssignPattern("9", "i1-");
			PKB.setAssignPattern("11", "x1+");
			PKB.setAssignPattern("12", "1");
			PKB.setAssignPattern("13", "zxi++");
			PKB.setAssignPattern("14", "z2+");
			PKB.setAssignPattern("15", "xyz*+");

			PKB.setWhilePattern("6", "i");
			PKB.setIfPattern("10", "x");
		}
		//pattern a(_, _)
		TEST_METHOD(getPatternAssignAnyAny)
		{
			PKBPattern PKB;
			TABLE actual, expected;

			actual = PKB.getPatternAssignAnyAny();
			expected = { {"4"},{"5"},{"7"},{"9"},{"11"},{"12"},{"13"},{"14"},{"15"} };
			Assert::IsTrue(actual == expected);
		}
		//pattern a(_, “a+b”)
		TEST_METHOD(getPatternAssignAnyFull)
		{
			PKBPattern PKB;
			TABLE actual, expected;

			actual = PKB.getPatternAssignAnyFull("x2y*+");
			expected = { {"7"} };
			Assert::IsTrue(actual == expected);
		}
		//pattern a(_, _“a+b”_)
		TEST_METHOD(getPatternAssignAnyPartial)
		{
			PKBPattern PKB;
			TABLE actual, expected;

			actual = PKB.getPatternAssignAnyPartial("2y*");
			expected = { {"7"} };
			Assert::IsTrue(actual == expected);
		}
		//pattern a(“x”, _)
		TEST_METHOD(getPatternAssignIdentAny)
		{
			PKBPattern PKB;
			TABLE actual, expected;

			actual = PKB.getPatternAssignIdentAny("x");
			expected = { {"4"},{"7"},{"11"},{"15"} };
			Assert::IsTrue(actual == expected);
		}
		//pattern a(“x”, “a+b”)
		TEST_METHOD(getPatternAssignIdentFull)
		{
			PKBPattern PKB;
			TABLE actual, expected;

			actual = PKB.getPatternAssignIdentFull("x", "xyz*+");
			expected = { {"15"} };
			Assert::IsTrue(actual == expected);
		}
		//pattern a(“x”, _“a+b”_)
		TEST_METHOD(getPatternAssignIdentPartial)
		{
			PKBPattern PKB;
			TABLE actual, expected;

			actual = PKB.getPatternAssignIdentPartial("x", "2y*");
			expected = { {"7"} };
			Assert::IsTrue(actual == expected);
		}
		//pattern a(v, _)
		TEST_METHOD(getPatternAssignEntAny)
		{
			PKBPattern PKB;
			TABLE actual, expected;

			actual = PKB.getPatternAssignEntAny();
			expected = { {"4","x"},{"5","i"},{"7","x"},{"9","i"},{"11","x"},{"12","z"},{"13","z"},{"14","y"},{"15","x"} };
			Assert::IsTrue(actual == expected);
		}
		//pattern a(v, “a+b”)
		TEST_METHOD(getPatternAssignEntFull)
		{
			PKBPattern PKB;
			TABLE actual, expected;

			actual = PKB.getPatternAssignEntFull("xyz*+");
			expected = { {"15","x"} };
			Assert::IsTrue(actual == expected);
		}

		//pattern pattern a(v, _“a+b”_)
		TEST_METHOD(getPatternAssignEntPartial)
		{
			PKBPattern PKB;
			TABLE actual, expected;

			actual = PKB.getPatternAssignEntPartial("2y*");
			expected = { {"7","x"} };
			Assert::IsTrue(actual == expected);
		}
		//pattern w(_, _)
		TEST_METHOD(getPatternWhileAny)
		{
			PKBPattern PKB;
			TABLE actual, expected;

			actual = PKB.getPatternWhileAny();
			expected = { {"6"} };
			Assert::IsTrue(actual == expected);
		}
		//pattern w(“x”, _)
		TEST_METHOD(getPatternWhileIdent)
		{
			PKBPattern PKB;
			TABLE actual, expected;

			actual = PKB.getPatternWhileIdent("i");
			expected = { {"6"} };
			Assert::IsTrue(actual == expected);
		}
		//pattern w(v, _)
		TEST_METHOD(getPatternWhileEnt)
		{
			PKBPattern PKB;
			TABLE actual, expected;

			actual = PKB.getPatternWhileEnt();
			expected = { {"6", "i"} };
			Assert::IsTrue(actual == expected);
		}
		//pattern ifs(_, _, _)
		TEST_METHOD(getPatternIfAny)
		{
			PKBPattern PKB;
			TABLE actual, expected;

			actual = PKB.getPatternIfAny();
			expected = { {"10"} };
			Assert::IsTrue(actual == expected);
		}
		//pattern ifs(“x”, _, _)
		TEST_METHOD(getPatternIfIdent)
		{
			PKBPattern PKB;
			TABLE actual, expected;

			actual = PKB.getPatternIfIdent("x");
			expected = { {"10"} };
			Assert::IsTrue(actual == expected);
		}
		//pattern ifs(v, _, _)
		TEST_METHOD(getPatternIfEnt)
		{
			PKBPattern PKB;
			TABLE actual, expected;

			actual = PKB.getPatternIfEnt();
			expected = { {"10","x"} };
			Assert::IsTrue(actual == expected);
		}
	};
};