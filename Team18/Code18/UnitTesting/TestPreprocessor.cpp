#include "stdafx.h"
#include "CppUnitTest.h"
#include "Query.h"
#include "Preprocessor.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
    TEST_CLASS(TestPreprocessor)
    {
    public:
        TEST_METHOD(validQueries)
        {
            //list<string> expected;
            //list<string> actual;

            //expected = { "1", "2", "3", "4", "5", "6", "7", "8" };
            //actual = QueryParser::parse("stmt s; Select s");
            //Assert::IsTrue(expected == actual);

            //expected = { "1", "2", "3", "4", "5", "6", "7", "8" };
            //actual = QueryParser::parse("stmt s123; Select s123");
            //Assert::IsTrue(expected == actual);

            //expected = {};
            //actual = QueryParser::parse("variable v; Select v such that Uses(1, v)");
            //Assert::IsTrue(expected == actual);

            //expected = { "1", "2", "3", "7" };
            //actual = QueryParser::parse("stmt s1,   s2; Select     s1 such that Follows  (s1   ,   s2)");
            //Assert::IsTrue(expected == actual);

            //expected = { "1", "6", "7" };
            //actual = QueryParser::parse("stmt    s;   Select  s  such that  Modifies(  s, _\"x\"_)");
            //Assert::IsTrue(expected == actual);
        }
        TEST_METHOD(invalidQueries)
        {
            //list<string> expected;
            //list<string> actual;

            //expected = { "Invalid" };
            //actual = QueryParser::parse("");
            //Assert::IsTrue(expected == actual);

            //expected = { "Invalid" };
            //actual = QueryParser::parse("foo");
            //Assert::IsTrue(expected == actual);

            //expected = { "Invalid" };
            //actual = QueryParser::parse("Select");
            //Assert::IsTrue(expected == actual);

            //expected = { "Invalid" };
            //actual = QueryParser::parse("Select 1");
            //Assert::IsTrue(expected == actual);

            //expected = { "Invalid" };
            //actual = QueryParser::parse("Select s");
            //Assert::IsTrue(expected == actual);

            //expected = { "Invalid" };
            //actual = QueryParser::parse("stmt s; Selct s");
            //Assert::IsTrue(expected == actual);

            //expected = { "Invalid" };
            //actual = QueryParser::parse("stmt s; select s");
            //Assert::IsTrue(expected == actual);

            //expected = { "Invalid" };
            //actual = QueryParser::parse("stmt s Select s");
            //Assert::IsTrue(expected == actual);

            //expected = { "Invalid" };
            //actual = QueryParser::parse("foo s; Select s");
            //Assert::IsTrue(expected == actual);

            //expected = { "Invalid" };
            //actual = QueryParser::parse("stmt s 1; Select s");
            //Assert::IsTrue(expected == actual);

            //expected = { "Invalid" };
            //actual = QueryParser::parse("stmt s*; Select s*");
            //Assert::IsTrue(expected == actual);

            //expected = { "Invalid" };
            //actual = QueryParser::parse("stmt s, Select s");
            //Assert::IsTrue(expected == actual);

            //expected = { "Invalid" };
            //actual = QueryParser::parse("assign a; Select a such that Uses(a)");
            //Assert::IsTrue(expected == actual);

            //expected = { "Invalid" };
            //actual = QueryParser::parse("stmt s; Select s suchthat Uses(s, \"x\")");
            //Assert::IsTrue(expected == actual);

            //expected = { "Invalid" };
            //actual = QueryParser::parse("stmt s; variable v; Select s Uses(s, v)");
            //Assert::IsTrue(expected == actual);

            //expected = { "Invalid" };
            //actual = QueryParser::parse("stmt s1, s2; Select s such that Foo(s1, s2)");
            //Assert::IsTrue(expected == actual);

            //expected = { "Invalid" };
            //actual = QueryParser::parse("stmt s; variable v; Select s such that Uses(s, v) pattern (v, _)");
            //Assert::IsTrue(expected == actual);

            //expected = { "Invalid" };
            //actual = QueryParser::parse("assign a; variable v; Select a such that Uses(a, v) and pattern a(v, _)");
            //Assert::IsTrue(expected == actual);

            //expected = { "Invalid" };
            //actual = QueryParser::parse("stmt s; variable v; Select s such that Uses(_, v)");
            //Assert::IsTrue(expected == actual);

            //expected = { "Invalid" };
            //actual = QueryParser::parse("stmt s; variable v; Select s such that Uses(v, s)");
            //Assert::IsTrue(expected == actual);
        }
    };
}
