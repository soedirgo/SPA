#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKBWith.h"
#include "PKBStmt.h"
#include "PKBCall.h"
#include "PKBRead.h"
#include "PKBPrint.h"
#include "PKBProcedure.h"
#include "PKBVariable.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(PKBWithTest)
	{
	public:
		TEST_METHOD_INITIALIZE(PKB_START)
		{
			/**	SIMPLE program:

				procedure First {
				1.	read x;
				2.	call Second;
				3.	call Third; }

				procedure Second {
				4.		while (i!=0) {
				5.			call Third;}
				6.		if (x==1) then {
				7.			x = x+1; }
						else {
				8.			z = 1; }}

					procedure Third {
				9.		print c; }
		   */

			PKBStmt PKBStmts;
			PKBCall PKBCalls;
			PKBProcedure PKBProcedure;
			PKBVariable PKBVariable;
			PKBPrint PKBPrint;
			PKBRead PKBRead;
			PKBStmts.clear();
			PKBCalls.clear();
			PKBProcedure.clear();
			PKBVariable.clear();
			PKBRead.clear();
			PKBPrint.clear();

			PKBProcedure.setProcedure("First","1", { {"3"} });
			PKBProcedure.setProcedure("Second","4", { {"7","8"} });
			PKBProcedure.setProcedure("Third","9", { {"9"} });

			PKBVariable.setVariable("x");
			PKBVariable.setVariable("i");
			PKBVariable.setVariable("c");

			PKBPrint.setPrint("9","c");
			PKBRead.setRead("1","x");

			PKBStmts.setStmt("1", "read");
			PKBStmts.setStmt("2", "call");
			PKBStmts.setStmt("3", "call");
			PKBStmts.setStmt("4", "while");
			PKBStmts.setStmt("5", "call");
			PKBStmts.setStmt("6", "if");
			PKBStmts.setStmt("7", "assign");
			PKBStmts.setStmt("8", "assign");
			PKBStmts.setStmt("9", "print");

			PKBCalls.setCallStmt("2", "Second");
			PKBCalls.setCallStmt("3", "Third");
			PKBCalls.setCallStmt("5", "Third");

		}
		TEST_METHOD(getWithIdentAttr) {
			PKBWith PKB;
			TABLE actual, expected;

			actual = PKB.getWithIdentAttr("1","stmt","stmt#");
			expected = { {"1"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getWithIdentAttr("1", "read", "stmt#");
			expected = { {"1"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getWithIdentAttr("9", "print", "stmt#");
			expected = { {"9"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getWithIdentAttr("4", "while", "stmt#");
			expected = { {"4"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getWithIdentAttr("6", "if", "stmt#");
			expected = { {"6"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getWithIdentAttr("3", "call", "stmt#");
			expected = { {"3"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getWithIdentAttr("First", "procedure", "procName");
			expected = { {"First"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getWithIdentAttr("Second", "call", "procName");
			expected = { {"2"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getWithIdentAttr("x", "variable", "varName");
			expected = { {"x"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getWithIdentAttr("x", "read", "varName");
			expected = { {"1"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getWithIdentAttr("c", "print", "varName");
			expected = { {"9"} };
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(getWithIdentLine) {
			PKBWith PKB;
			TABLE actual, expected;

			actual = PKB.getWithIdentLine("1");
			expected = { {"1"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getWithIdentLine("2");
			expected = { {"2"} };
			Assert::IsTrue(actual == expected);
		}
		TEST_METHOD(getWithAttrAttr) {
			PKBWith PKB;
			TABLE actual, expected;

			actual = PKB.getWithAttrAttr("procedure", "procName", "constant", "value");
			Assert::IsTrue(actual == expected);

			actual = PKB.getWithAttrAttr("procedure", "procName", "constant", "value");
			Assert::IsTrue(actual == expected);

			actual = PKB.getWithAttrAttr("procedure", "procName", "constant", "value");
			Assert::IsTrue(actual == expected);
			
			actual = PKB.getWithAttrAttr("print", "varName", "print", "varName");
			expected = { {"9","9"} };
			Assert::IsTrue(actual == expected);
			
			actual = PKB.getWithAttrAttr("read", "varName", "read", "varName");
			expected = { {"1","1"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getWithAttrAttr("variable", "varName", "read", "varName");
			expected = { {"x","1"} };
			Assert::IsTrue(actual == expected);
			
			actual = PKB.getWithAttrAttr("procedure", "procName", "call", "procName");
			expected = { {"Second","2"} ,  {"Third","3"}  ,  {"Third","5"} };
			Assert::IsTrue(actual == expected);
			
			actual = PKB.getWithAttrAttr("stmt", "stmt#", "call", "stmt#");
			expected = { {"2","2"} ,  {"3","3"} ,  {"5","5"} };
			Assert::IsTrue(actual == expected);
			
		}

		TEST_METHOD(getWithAttrLine) {
			PKBWith PKB;
			TABLE actual, expected;

			actual = PKB.getWithAttrLine("call", "stmt#");
			expected = { {"2","2"} ,  {"3","3"} ,  {"5","5"} };
			Assert::IsTrue(actual == expected);
			
			actual = PKB.getWithAttrLine("read", "stmt#");
			expected = { {"1","1"} };
			Assert::IsTrue(actual == expected);

			actual = PKB.getWithAttrLine("print", "stmt#");
			expected = { {"9","9"} };
			Assert::IsTrue(actual == expected);
			
		}

		TEST_METHOD(getWithLineLine) {
			PKBWith PKB;
			TABLE actual, expected;

			actual = PKB.getWithLineLine();
			expected = { 
			
			{"1","1"} , {"2","2"} , {"3","3"} , {"4","4"} , {"5","5"} , {"6","6"} ,
			{"7","7"} , {"8","8"} , {"9","9"} };
			Assert::IsTrue(actual == expected);

		}

	};
}