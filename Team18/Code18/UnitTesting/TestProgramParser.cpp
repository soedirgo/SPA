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

	};
}