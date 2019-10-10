#include "stdafx.h"
#include "CppUnitTest.h"
#include "QueryParser.h"
#include "Query.h"
#include "Clause.h"
#include "PKB.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	/*
	TEST_CLASS(TestQueryParser)
	{
	public:
        TEST_METHOD_INITIALIZE(queryParserInit)
        {
            /**
               SIMPLE program:
               _   procedure main {
               1.      x = 1
               2.      y = x
               3.      if (x == y) then {
               4.          z = 0;
               _       } else {
               5.          z = 1;
               _       }
               6.      while (x > 0) {
               7.          read x;
               8.          print x;
			   9.		   x = x + 1;
               _       }
            */
			/*
            PKB pkb;

            pkb.clear();

            pkb.setProc("main");

            pkb.setStmt(1, Assign);
            pkb.setAssignStmt(1, "x");
            pkb.setVar("x");
            pkb.setConstant("1", 1);
            //pkb.setModifiesVarByStmt(1, "x");

            pkb.setStmt(2, Assign);
            pkb.setAssignStmt(2, "y");
            pkb.setVar("y");
            pkb.setUsesVarByStmt(2, "x");
            //pkb.setModifiesVarByStmt(2, "y");
            pkb.setFollows(1, 2);
            pkb.setFollowsT(1, 2);

            pkb.setStmt(3, If);
            //pkb.setIfStmt(3);
            pkb.setUsesVarByStmt(3, "x");
            pkb.setUsesVarByStmt(3, "y");
            //pkb.setModifiesVarByStmt(3, "z");
            pkb.setFollows(2, 3);
            pkb.setFollowsT(1, 3);
            pkb.setFollowsT(2, 3);

            pkb.setStmt(4, Assign);
            pkb.setAssignStmt(4, "z");
            pkb.setVar("z");
            pkb.setConstant("0", 4);
            //pkb.setModifiesVarByStmt(4, "z");
            pkb.setParent(3, 4);
            pkb.setParentT(3, 4);

            pkb.setStmt(5, Assign);
            pkb.setAssignStmt(5, "z");
            //pkb.setModifiesVarByStmt(5, "z");
            pkb.setParent(3, 5);
            pkb.setParentT(3, 5);

            pkb.setStmt(6, While);
            //pkb.setWhileStmt(6);
            pkb.setUsesVarByStmt(6, "x");
            //pkb.setModifiesVarByStmt(6, "x");
            pkb.setFollows(3, 6);
            pkb.setFollowsT(1, 6);
            pkb.setFollowsT(2, 6);
            pkb.setFollowsT(3, 6);

            pkb.setStmt(7, Read);
            pkb.setRead(7, "x");
            //pkb.setModifiesVarByStmt(7, "x");
            pkb.setParent(6, 7);
            pkb.setParentT(6, 7);

            pkb.setStmt(8, Print);
            pkb.setPrint(8, "x");
            pkb.setUsesVarByStmt(8, "x");
            pkb.setParent(6, 8);
            pkb.setParentT(6, 8);
            pkb.setFollows(7, 8);
            pkb.setFollowsT(7, 8);

			pkb.setStmt(9, Assign);
			pkb.setAssignStmt(9, "x");
			pkb.setVar("x");
			pkb.setUsesStmtRelation(9, "x");
			pkb.setModifiesStmt(9, "x");
			pkb.setFollows(8, 9);
			pkb.setFollowsT(8, 9);
			*/
		}
		/*
        TEST_METHOD(validQueries)
        {
            list<string> expected;
            list<string> actual;

            expected = { "1", "2", "3", "4", "5", "6", "7", "8" , "9"};
            actual = QueryParser::parse("stmt s; Select s");
            Assert::IsTrue(expected == actual);
            
            expected = { "1", "2", "3", "4", "5", "6", "7", "8" ,"9"};
            actual = QueryParser::parse("stmt s123; Select s123");
            Assert::IsTrue(expected == actual);
            
            expected = {};
            actual = QueryParser::parse("variable v; Select v such that Uses(1, v)");
            Assert::IsTrue(expected == actual);
            
            expected = { "1", "2", "3", "7" ,"8"};
            actual = QueryParser::parse("stmt s1,   s2; Select     s1 such that Follows  (s1   ,   s2)");
            Assert::IsTrue(expected == actual);

            expected = { "1", "6", "7","9" };
			actual = QueryParser::parse("stmt    s;   Select  s  such that  Modifies(  s, \"x\")");
			Assert::IsTrue(expected == actual);

			expected = { "1", "2", "3", "4", "5", "6", "7", "8" ,"9" };
			actual = QueryParser::parse("stmt s; assign a; Select s pattern a(_, _\"x\"_)");
			Assert::IsTrue(expected == actual);
        }
        TEST_METHOD(invalidQueries)
        {
            list<string> expected;
            list<string> actual;

            actual = QueryParser::parse("");
            Assert::IsTrue(expected == actual);

            actual = QueryParser::parse("foo");
            Assert::IsTrue(expected == actual);

            actual = QueryParser::parse("Select");
            Assert::IsTrue(expected == actual);

            actual = QueryParser::parse("Select 1");
            Assert::IsTrue(expected == actual);

            actual = QueryParser::parse("Select s");
            Assert::IsTrue(expected == actual);

            actual = QueryParser::parse("stmt s; Selct s");
            Assert::IsTrue(expected == actual);

            actual = QueryParser::parse("stmt s; select s");
            Assert::IsTrue(expected == actual);

            actual = QueryParser::parse("stmt s Select s");
            Assert::IsTrue(expected == actual);

            actual = QueryParser::parse("foo s; Select s");
            Assert::IsTrue(expected == actual);

            actual = QueryParser::parse("stmt s 1; Select s");
            Assert::IsTrue(expected == actual);

            actual = QueryParser::parse("stmt s*; Select s*");
            Assert::IsTrue(expected == actual);

            actual = QueryParser::parse("stmt s, Select s");
            Assert::IsTrue(expected == actual);

            actual = QueryParser::parse("assign a; Select a such that Uses(a)");
            Assert::IsTrue(expected == actual);

            actual = QueryParser::parse("stmt s; Select s suchthat Uses(s, \"x\")");
            Assert::IsTrue(expected == actual);

            actual = QueryParser::parse("stmt s; variable v; Select s Uses(s, v)");
            Assert::IsTrue(expected == actual);

            actual = QueryParser::parse("stmt s1, s2; Select s such that Foo(s1, s2)");
            Assert::IsTrue(expected == actual);

			actual = QueryParser::parse("stmt    s;   Select  s  such that  Modifies(  s, _\"x\"_)");
			Assert::IsTrue(expected == actual);

            //actual = QueryParser::parse("stmt s; variable v; Select s such that Uses(s, v) pattern (v, _)");
            //Assert::IsTrue(expected == actual);

            //actual = QueryParser::parse("assign a; variable v; Select a such that Uses(a, v) and pattern a(v, _)");
            //Assert::IsTrue(expected == actual);

            actual = QueryParser::parse("stmt s; variable v; Select s such that Uses(v, s)");
            Assert::IsTrue(expected == actual);

			actual = QueryParser::parse("stmt v; variable s; Select s such that Uses(s, v)");
			Assert::IsTrue(expected == actual);

			actual = QueryParser::parse("stmt s; variable v; Select s such that Modifies(v, v)");
			Assert::IsTrue(expected == actual);
        }

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
			vector<string> suchThatString = { "such that Modifies(2,\"x\")" };
			vector<pair<string, pair<string, string>>> actual = QueryParser::splitSuchThat(suchThatString);
			vector<pair<string, pair<string, string>>> expected = { {"Modifies", {"2","\"x\""}} };
			Assert::AreEqual(actual == expected, true);

			vector<string> suchThatString2 = { "such that Modifies(2,x)" };
			vector<pair<string, pair<string, string>>> actual2 = QueryParser::splitSuchThat(suchThatString2);
			vector<pair<string, pair<string, string>>> expected2 = { {"Modifies", {"2","x"}} };
			Assert::AreEqual(actual2 == expected2, true);
		}

		TEST_METHOD(splitPatternCondition)
		{
			vector<string> input = { "pattern a(_, _)" };
			vector<pair<string, pair<string, string>>> actual = QueryParser::splitPattern(input);
			vector<pair<string, pair<string, string>>> expected{ {"a", {"_", "_"}} };
			Assert::AreEqual(actual == expected, true);
			
			vector<string> input2 = { "pattern a(_, _\"a+b*c\"_)" };
			vector<pair<string, pair<string, string>>> actual2 = QueryParser::splitPattern(input2);
			vector<pair<string, pair<string, string>>> expected2{ {"a", {"_", "\"a+b*c\""}} };
			Assert::AreEqual(actual2 == expected2, true);
		}

		TEST_METHOD(initialValidation)
		{
			string expected = "Invalid";
			string actual = QueryParser::initialValidation("");
			Assert::AreEqual(actual == expected,true);
			
			string actual2 = QueryParser::initialValidation("Select v");
			string expected2 = "None";
			Assert::AreEqual(actual2 == expected2, true);

			string actual3 = QueryParser::initialValidation("variable v;");
			string expected3 = "Invalid";
			Assert::AreEqual(actual3 == expected3, true);
		}

		TEST_METHOD(declarationsValidation)
		{
			unordered_map<string, string> input{ {"1a2", "assign"},{"v", "variable"} };
			string actual = QueryParser::declarationsValidation(input);
			string expected = "Invalid";
			Assert::AreEqual(actual == expected, true);

			unordered_map<string, string> input2{ {"a1_", "assign"},{"v", "variable"} };
			string actual2 = QueryParser::declarationsValidation(input2);
			string expected2 = "Invalid";
			Assert::AreEqual(actual2 == expected2, true);
			
			unordered_map<string, string> input3{ {"a*", "assign"},{"v", "variable"} };
			string actual3 = QueryParser::declarationsValidation(input3);
			string expected3 = "Invalid";
			Assert::AreEqual(actual3 == expected3, true);

			unordered_map<string, string> input4{ {"a", "assign"},{"char", "c"} };
			string actual4 = QueryParser::declarationsValidation(input4);
			string expected4 = "Invalid";
			Assert::AreEqual(actual4 == expected4, true);
		
		}
		
	};
	
}*/
