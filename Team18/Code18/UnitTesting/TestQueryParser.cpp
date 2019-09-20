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
               _       }
            */

            PKB pkb;

            pkb.clear();

            pkb.setProc("main");

            pkb.setStmt(1, Assign);
            pkb.setAssignStmt(1, "x");
            pkb.setVar("x");
            pkb.setConstant("1", 1);
            pkb.setModifiesVarByStmt(1, "x");

            pkb.setStmt(2, Assign);
            pkb.setAssignStmt(2, "y");
            pkb.setVar("y");
            pkb.setUsesVarByStmt(2, "x");
            pkb.setModifiesVarByStmt(2, "y");
            pkb.insertFollowRelation(1, 2);
            pkb.insertFollowStarRelation(1, 2);

            pkb.setStmt(3, If);
            pkb.setIfStmt(3);
            pkb.setUsesVarByStmt(3, "x");
            pkb.setUsesVarByStmt(3, "y");
            pkb.setModifiesVarByStmt(3, "z");
            pkb.insertFollowRelation(2, 3);
            pkb.insertFollowStarRelation(1, 3);
            pkb.insertFollowStarRelation(2, 3);

            pkb.setStmt(4, Assign);
            pkb.setAssignStmt(4, "z");
            pkb.setVar("z");
            pkb.setConstant("0", 4);
            pkb.setModifiesVarByStmt(4, "z");
            pkb.insertParentRelation(3, 4);
            pkb.insertParentStarRelation(3, 4);

            pkb.setStmt(5, Assign);
            pkb.setAssignStmt(5, "z");
            pkb.setModifiesVarByStmt(5, "z");
            pkb.insertParentRelation(3, 5);
            pkb.insertParentStarRelation(3, 5);

            pkb.setStmt(6, While);
            pkb.setWhileStmt(6);
            pkb.setUsesVarByStmt(6, "x");
            pkb.setModifiesVarByStmt(6, "x");
            pkb.insertFollowRelation(3, 6);
            pkb.insertFollowStarRelation(1, 6);
            pkb.insertFollowStarRelation(2, 6);
            pkb.insertFollowStarRelation(3, 6);

            pkb.setStmt(7, Read);
            pkb.setReadStmt(7, "x");
            pkb.setModifiesVarByStmt(7, "x");
            pkb.insertParentRelation(6, 7);
            pkb.insertParentStarRelation(6, 7);

            pkb.setStmt(8, Print);
            pkb.setPrintStmt(8, "x");
            pkb.setUsesVarByStmt(8, "x");
            pkb.insertParentRelation(6, 8);
            pkb.insertParentStarRelation(6, 8);
            pkb.insertFollowRelation(7, 8);
            pkb.insertFollowStarRelation(7, 8);
		}
        TEST_METHOD(validQueries)
        {
            list<string> expected;
            list<string> actual;

            expected = { "1", "2", "3", "4", "5", "6", "7", "8" };
            actual = QueryParser::parse("stmt s; Select s");
            Assert::IsTrue(expected == actual);
            
            expected = { "1", "2", "3", "4", "5", "6", "7", "8" };
            actual = QueryParser::parse("stmt s123; Select s123");
            Assert::IsTrue(expected == actual);
            
            expected = {};
            actual = QueryParser::parse("variable v; Select v such that Uses(1, v)");
            Assert::IsTrue(expected == actual);
            
            expected = { "1", "2", "3", "7" };
            actual = QueryParser::parse("stmt s1, s2; Select s1 such that Follows(s1, s2)");
            Assert::IsTrue(expected == actual);
            
            expected = { "1", "7" };
            actual = QueryParser::parse("stmt  \n s; Select \t   s such that\n Modifies(s,   \t \"x\")");
            Assert::IsTrue(expected == actual);
        }
        TEST_METHOD(invalidQueries)
        {
            list<string> expected;
            list<string> actual;

            expected = { "Invalid" };
            actual = QueryParser::parse("");
            Assert::IsTrue(expected == actual);

            expected = { "Invalid" };
            actual = QueryParser::parse("foo");
            Assert::IsTrue(expected == actual);

            expected = { "Invalid" };
            actual = QueryParser::parse("Select");
            Assert::IsTrue(expected == actual);

            expected = { "Invalid" };
            actual = QueryParser::parse("Select 1");
            Assert::IsTrue(expected == actual);

            expected = { "Invalid" };
            actual = QueryParser::parse("Select s");
            Assert::IsTrue(expected == actual);

            expected = { "Invalid" };
            actual = QueryParser::parse("stmt s; Selct s");
            Assert::IsTrue(expected == actual);

            expected = { "Invalid" };
            actual = QueryParser::parse("stmt s; select s");
            Assert::IsTrue(expected == actual);

            expected = { "Invalid" };
            actual = QueryParser::parse("stmt s Select s");
            Assert::IsTrue(expected == actual);

            expected = { "Invalid" };
            actual = QueryParser::parse("foo s; Select s");
            Assert::IsTrue(expected == actual);

            expected = { "Invalid" };
            actual = QueryParser::parse("stmt s 1; Select s");
            Assert::IsTrue(expected == actual);

            expected = { "Invalid" };
            actual = QueryParser::parse("stmt s*; Select s*");
            Assert::IsTrue(expected == actual);

            expected = { "Invalid" };
            actual = QueryParser::parse("stmt s, Select s");
            Assert::IsTrue(expected == actual);

            expected = { "Invalid" };
            actual = QueryParser::parse("assign a; Select a such that Uses(a)");
            Assert::IsTrue(expected == actual);

            expected = { "Invalid" };
            actual = QueryParser::parse("stmt s; Select s suchthat Uses(s, \"x\")");
            Assert::IsTrue(expected == actual);

            expected = { "Invalid" };
            actual = QueryParser::parse("stmt s; variable v; Select s Uses(s, v)");
            Assert::IsTrue(expected == actual);

            expected = { "Invalid" };
            actual = QueryParser::parse("stmt s1, s2; Select s such that Foo(s1, s2)");
            Assert::IsTrue(expected == actual);

            expected = { "Invalid" };
            actual = QueryParser::parse("stmt s; variable v; Select s such that Uses(s, v) pattern (v, _)");
            Assert::IsTrue(expected == actual);

            expected = { "Invalid" };
            actual = QueryParser::parse("assign a; variable v; Select a such that Uses(a, v) and pattern a(v, _)");
            Assert::IsTrue(expected == actual);

            expected = { "Invalid" };
            actual = QueryParser::parse("stmt s; variable v; Select s such that Uses(_, v)");
            Assert::IsTrue(expected == actual);

            expected = { "Invalid" };
            actual = QueryParser::parse("stmt s; variable v; Select s such that Uses(v, s)");
            Assert::IsTrue(expected == actual);
        }
	};
}
