#include "stdafx.h"
#include "CppUnitTest.h"
#include "QueryParser.h"
#include "Query.h"
#include "Clause.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestQueryParser)
	{
	public:

		TEST_METHOD(findInitialDecleration)
		{
			vector<string> actual = QueryParser::findInitialDecleration("assign a; variable v;Select a such that Uses(a,v)");
			vector<string> expected{ "assign a", "variable v", "Select a such that Uses(a,v)" };
			Assert::AreEqual(actual == expected, true);
		}

		TEST_METHOD(splitVariablesInDeclerations)
		{
			vector<string> input = { "variable v1, v2", "while w1 ,w2", "Select v such that Follows(v,w)" };
			unordered_map<string, string> actual = QueryParser::splitVariablesInDeclerations(input);
			unordered_map<string, string> expected{ {"v1", "variable"}, {"v2", "variable"}, {"w1", "while"}, {"w2", "while"} };
			Assert::AreEqual(actual == expected, true);
		}


		TEST_METHOD(splitSelect)
		{
			string actual = QueryParser::splitSelect("Select v2");
			string expected{ "v2" };
			Assert::AreEqual(actual == expected, true);
		}

		TEST_METHOD(splitSuchThat)
		{
			vector<string> suchThatString = { "such that Modifies(2,v)" };
			vector<pair<string, pair<string, string>>> actual = QueryParser::splitSuchThat(suchThatString);
			vector<pair<string, pair<string, string>>> expected = { {"Modifies", {"2","v"}} };
			Assert::AreEqual(actual == expected, true);
		}

		TEST_METHOD(splitPatternCondition)
		{
			vector<string> input = { "pattern a(_, \"a+b*c\")" };
			vector<pair<string, pair<string, string>>> actual = QueryParser::splitPattern(input);
			vector<pair<string, pair<string, string>>> expected{ {"a", {"_", "\"a+b*c\""}} };
			Assert::AreEqual(actual == expected, true);
		}
	};
}
