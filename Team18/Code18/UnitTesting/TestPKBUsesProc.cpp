#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKBUses.h"
#include "DesignExtractor.h"
#include "PKBStmt.h"
#include "PKBCall.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(PKBUsesProcTest)
	{
	public:
		TEST_METHOD_INITIALIZE(PKB_START)
		{
			/**	SIMPLE program:

				procedure First {
				1.	read x;
				2.	call Fourth;
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
				17.		call Fifth;
				18.		call Fourth; }

					procedure Fourth {
				19.		a = 5+a;
				20.		b = z+b;
				21.		call Fifth; }

					procedure Fifth {
				22.		c = 5+c;
				23.		d = d;
				24.		print c; }
		   */

			PKBUses PKB;
			PKBStmt Stmts;
			PKBCall Calls;
			PKB.clear();

			Stmts.setStmt("1", "read");
			Stmts.setStmt("2", "call");
			Stmts.setStmt("3", "call");
			Stmts.setStmt("4", "assign");
			Stmts.setStmt("5", "assign");
			Stmts.setStmt("6", "while");
			Stmts.setStmt("7", "assign");
			Stmts.setStmt("8", "call");
			Stmts.setStmt("9", "assign");
			Stmts.setStmt("10", "if");
			Stmts.setStmt("11", "assign");
			Stmts.setStmt("12", "assign");
			Stmts.setStmt("13", "assign");
			Stmts.setStmt("14", "assign");
			Stmts.setStmt("15", "assign");
			Stmts.setStmt("16", "assign");
			Stmts.setStmt("17", "call");
			Stmts.setStmt("18", "call");
			Stmts.setStmt("19", "assign");
			Stmts.setStmt("20", "assign");
			Stmts.setStmt("21", "call");
			Stmts.setStmt("22", "assign");
			Stmts.setStmt("23", "assign");
			Stmts.setStmt("24", "call");

			Calls.setCallProc("First", "Second");
			Calls.setCallProc("First", "Fourth");
			Calls.setCallProc("Second", "Third");
			Calls.setCallProc("Third", "Fourth");
			Calls.setCallProc("Third", "Fifth");
			Calls.setCallProc("Fourth", "Fifth");

			//Line #3 Calls Second
			PKB.setUsesS("3", "y");
			PKB.setUsesS("3", "i");
			PKB.setUsesS("3", "x");

			//Direct assignment stmts with var on RHS 
			PKB.setUsesS("6", "i");
			PKB.setUsesS("7", "x");
			PKB.setUsesS("7", "y");
			PKB.setUsesS("9", "i");
			PKB.setUsesS("6", "x");
			PKB.setUsesS("6", "y");
			PKB.setUsesS("6", "i");
			PKB.setUsesS("8", "z");
			PKB.setUsesS("8", "v");
			PKB.setUsesS("10", "x");
			PKB.setUsesS("11", "x");
			PKB.setUsesS("13", "z");
			PKB.setUsesS("13", "x");
			PKB.setUsesS("13", "i");
			PKB.setUsesS("14", "z");
			PKB.setUsesS("15", "x");
			PKB.setUsesS("15", "y");
			PKB.setUsesS("15", "z");
			PKB.setUsesS("19", "a");
			PKB.setUsesS("20", "b");
			PKB.setUsesS("20", "z");
			PKB.setUsesS("22", "c");
			PKB.setUsesS("23", "d");
			PKB.setUsesS("24", "c");

			PKB.setUsesP("Second", "i");
			PKB.setUsesP("Second", "x");
			PKB.setUsesP("Second", "y");
			PKB.setUsesP("Second", "z");
			PKB.setUsesP("Third", "z");

			PKB.setUsesP("Fourth", "a");
			PKB.setUsesP("Fourth", "b");
			PKB.setUsesP("Fifth", "c");
			PKB.setUsesP("Fifth", "d");


			
		}
		TEST_METHOD(isUsesSIdentAny) {
			PKBUses PKB;
			Assert::IsTrue(PKB.isUsesSIdentAny("6"));
			Assert::IsTrue(PKB.isUsesSIdentAny("7"));
			Assert::IsTrue(PKB.isUsesSIdentAny("9"));
			Assert::IsTrue(PKB.isUsesSIdentAny("6"));
			Assert::IsTrue(PKB.isUsesSIdentAny("10"));
			Assert::IsTrue(PKB.isUsesSIdentAny("11"));
			Assert::IsTrue(PKB.isUsesSIdentAny("13"));
			Assert::IsTrue(PKB.isUsesSIdentAny("13"));
			Assert::IsTrue(PKB.isUsesSIdentAny("14"));
			Assert::IsTrue(PKB.isUsesSIdentAny("15"));
			Assert::IsTrue(PKB.isUsesSIdentAny("18"));
		}
		TEST_METHOD(isUsesSIdentIdent)
		{
			PKBUses PKB;
			Assert::IsTrue(PKB.isUsesSIdentIdent("6", "i"));
			Assert::IsTrue(PKB.isUsesSIdentIdent("7", "x"));
			Assert::IsTrue(PKB.isUsesSIdentIdent("7", "y"));
			Assert::IsTrue(PKB.isUsesSIdentIdent("9", "i"));
			Assert::IsTrue(PKB.isUsesSIdentIdent("6", "x"));
			Assert::IsTrue(PKB.isUsesSIdentIdent("6", "y"));
			Assert::IsTrue(PKB.isUsesSIdentIdent("10", "x"));
			Assert::IsTrue(PKB.isUsesSIdentIdent("11", "x"));
			Assert::IsTrue(PKB.isUsesSIdentIdent("13", "z"));
			Assert::IsTrue(PKB.isUsesSIdentIdent("13", "x"));
			Assert::IsTrue(PKB.isUsesSIdentIdent("14", "z"));
			Assert::IsTrue(PKB.isUsesSIdentIdent("15", "x"));
			Assert::IsTrue(PKB.isUsesSIdentIdent("15", "y"));
			Assert::IsTrue(PKB.isUsesSIdentIdent("15", "z"));
			Assert::IsTrue(PKB.isUsesSIdentIdent("18", "v"));
		}


		TEST_METHOD(isUsesPIdentAny)
		{
			PKBUses PKB;
			Assert::IsTrue(PKB.isUsesPIdentAny("First"));
			Assert::IsTrue(PKB.isUsesPIdentAny("Second"));
			Assert::IsTrue(PKB.isUsesPIdentAny("Third"));

		}
		TEST_METHOD(isUsesPIdentIdent)
		{
			DesignExtractor DesignExtractor;
			DesignExtractor.extractDesign();

			PKBUses PKB;

			Assert::IsTrue(PKB.isUsesPIdentIdent("First", "a"));
			Assert::IsTrue(PKB.isUsesPIdentIdent("First", "b"));
			Assert::IsTrue(PKB.isUsesPIdentIdent("First", "c"));
			Assert::IsTrue(PKB.isUsesPIdentIdent("First", "d"));
			Assert::IsTrue(PKB.isUsesPIdentIdent("First", "x"));
			Assert::IsTrue(PKB.isUsesPIdentIdent("First", "y"));
			Assert::IsTrue(PKB.isUsesPIdentIdent("First", "z"));
			Assert::IsTrue(PKB.isUsesPIdentIdent("First", "i"));

			Assert::IsTrue(PKB.isUsesPIdentIdent("Second", "a"));
			Assert::IsTrue(PKB.isUsesPIdentIdent("Second", "b"));
			Assert::IsTrue(PKB.isUsesPIdentIdent("Second", "c"));
			Assert::IsTrue(PKB.isUsesPIdentIdent("Second", "d"));
			Assert::IsTrue(PKB.isUsesPIdentIdent("Second", "x"));
			Assert::IsTrue(PKB.isUsesPIdentIdent("Second", "y"));
			Assert::IsTrue(PKB.isUsesPIdentIdent("Second", "z"));
			Assert::IsTrue(PKB.isUsesPIdentIdent("Second", "i"));
			
			Assert::IsTrue(PKB.isUsesPIdentIdent("Third", "z"));
			Assert::IsTrue(PKB.isUsesPIdentIdent("Third", "a"));
			Assert::IsTrue(PKB.isUsesPIdentIdent("Third", "b"));
			Assert::IsTrue(PKB.isUsesPIdentIdent("Third", "c"));
			Assert::IsTrue(PKB.isUsesPIdentIdent("Third", "d"));
			
			Assert::IsTrue(PKB.isUsesPIdentIdent("Fourth", "a"));
			Assert::IsTrue(PKB.isUsesPIdentIdent("Fourth", "b"));
			Assert::IsTrue(PKB.isUsesPIdentIdent("Fourth", "c"));
			Assert::IsTrue(PKB.isUsesPIdentIdent("Fourth", "d"));
			
			Assert::IsTrue(PKB.isUsesPIdentIdent("Fifth", "c"));
			Assert::IsTrue(PKB.isUsesPIdentIdent("Fifth", "d"));

		}
	};
}


