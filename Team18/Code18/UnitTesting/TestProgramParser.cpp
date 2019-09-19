#include <fstream>
#include <regex>
#include <algorithm>
#include "stdafx.h"
#include "CppUnitTest.h"
#include "Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{

	TEST_CLASS(TestProgramParser)
	{
	public:

		TEST_METHOD(ProcTest)
		{
			Parser parser = Parser();
			string input = "procedure main {";
			string expected = "main";
			string actual = parser.parseProc(input);
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(ReadTest)
		{
			Parser parser = Parser();
			string input = "read x;";
			string expected = "x";
			string actual = parser.parseRead(input);
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(PrintTest)
		{
			Parser parser = Parser();
			string input = "print x;";
			string expected = "x";
			string actual = parser.parsePrint(input);
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(AssignInitiTest)
		{
			Parser parser = Parser();
			string input = "x = a;";
			string expected = "x=a";
			string actual = parser.parseAssignInit(input);
			cout << actual;
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(AssignRHSTest)
		{
			Parser parser = Parser();
			string input = "a+b-c*d/e%2";
			vector<string> expected{ "a", "b", "c", "d", "e", "2" };
			vector<string> actual = parser.parseAssignRHS(input);
			Assert::AreEqual(expected == actual, true);
		}

		TEST_METHOD(ParseConditionTest1)
		{
			Parser parser = Parser();
			string input = "(x==1)";
			vector<string> expected{ "x", "1" };
			vector<string> actual = parser.parseCondition(input);
			Assert::AreEqual(expected == actual, true);
		}

		TEST_METHOD(ParseConditionTest2)
		{
			Parser parser = Parser();
			string input = "(x!=1)";
			vector<string> expected{ "x", "1" };
			vector<string> actual = parser.parseCondition(input);
			Assert::AreEqual(expected == actual, true);
		}

		TEST_METHOD(ParseConditionTest3)
		{
			Parser parser = Parser();
			string input = "(x<=1)";
			vector<string> expected{ "x", "1" };
			vector<string> actual = parser.parseCondition(input);
			Assert::AreEqual(expected == actual, true);
		}

		TEST_METHOD(ParseConditionTest4)
		{
			Parser parser = Parser();
			string input = "(x>=1)";
			vector<string> expected{ "x", "1" };
			vector<string> actual = parser.parseCondition(input);
			Assert::AreEqual(expected == actual, true);
		}

		TEST_METHOD(ParseConditionTest5)
		{
			Parser parser = Parser();
			string input = "(x<1)";
			vector<string> expected{ "x", "1" };
			vector<string> actual = parser.parseCondition(input);
			Assert::AreEqual(expected == actual, true);
		}

		TEST_METHOD(ParseConditionTest6)
		{
			Parser parser = Parser();
			string input = "(x>1)";
			vector<string> expected{ "x", "1" };
			vector<string> actual = parser.parseCondition(input);
			Assert::AreEqual(expected == actual, true);
		}

		TEST_METHOD(RemoveOuterBracketsTest)
		{
			Parser parser = Parser();
			string input = "(x>1abcdefg)))";
			string expected = "x>1abcdefg))";
			string actual = parser.removeOuterBrackets(input);
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(SimpleCondStmtTest)
		{
			Parser parser = Parser();
			string input = "if (x == 1) then {";
			vector<string> expected{ "x", "1" };
			vector<string> actual = parser.parseCondStmt(input);
			Assert::AreEqual(expected == actual, true);
		}

		TEST_METHOD(IfCondStmtTest1)
		{
			Parser parser = Parser();
			string input = "if ((x == 1) || (a != b) && (e < f)) then {";
			vector<string> expected{ "x", "1", "a", "b", "e", "f" };
			vector<string> actual = parser.parseCondStmt(input);
			Assert::AreEqual(expected == actual, true);
		}

		TEST_METHOD(IfCondStmtTest2)
		{
			Parser parser = Parser();
			string input = "if ((x == 1) || (a != b) && (c <= d) || (e >= f) || (g < h) && (i > j)) then {";
			vector<string> expected{ "x", "1", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j" };
			vector<string> actual = parser.parseCondStmt(input);
			Assert::AreEqual(expected == actual, true);
		}

		TEST_METHOD(WhileCondStmtTest1)
		{
			Parser parser = Parser();
			string input = "while ((x == 1) || (a != b) && (e < f)) {";
			vector<string> expected{ "x", "1", "a", "b", "e", "f" };
			vector<string> actual = parser.parseCondStmt(input);
			Assert::AreEqual(expected == actual, true);
		}

		TEST_METHOD(WhileCondStmtTest2)
		{
			Parser parser = Parser();
			string input = "while ((x == 1) || (a != b) && (c <= d) || (e >= f) || (g < h) && (i > j)) {";
			vector<string> expected{ "x", "1", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j" };
			vector<string> actual = parser.parseCondStmt(input);
			Assert::AreEqual(expected == actual, true);
		}
	};
}