#include "stdafx.h"
//#include "CppUnitTest.h"
//#include "Query.h"
//#include "Preprocessor.h"
//
//using namespace std;
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//
//namespace UnitTesting
//{
//    TEST_CLASS(TestPreprocessor)
//    {
//    public:
//        TEST_METHOD(validQueries)
//        {
//            string input;
//
//            input = "stmt s; Select s";
//            Assert::IsTrue(Preprocessor::isValid(input));
//
//            input = "stmt s123; Select s123";
//            Assert::IsTrue(Preprocessor::isValid(input));
//
//            input = "variable v; Select v such that Uses(1, v)";
//            Assert::IsTrue(Preprocessor::isValid(input));
//
//            input = "stmt s1,   s2; Select     s1 such that Follows  (s1   ,   s2)";
//            Assert::IsTrue(Preprocessor::isValid(input));
//
//            input = "stmt    s;   Select  s  such that  Modifies(  s, \"x\")";
//            Assert::IsTrue(Preprocessor::isValid(input));
//        }
//        TEST_METHOD(invalidQueries)
//        {
//            string input;
//
//            input = "";
//            Assert::IsFalse(Preprocessor::isValid(input));
//
//            input = "foo";
//            Assert::IsFalse(Preprocessor::isValid(input));
//
//            input = "Select";
//            Assert::IsFalse(Preprocessor::isValid(input));
//
//            input = "Select 1";
//            Assert::IsFalse(Preprocessor::isValid(input));
//
//            input = "Select s";
//            Assert::IsFalse(Preprocessor::isValid(input));
//
//            input = "stmt s; Selct s";
//            Assert::IsFalse(Preprocessor::isValid(input));
//
//            input = "stmt s; select s";
//            Assert::IsFalse(Preprocessor::isValid(input));
//
//            input = "stmt s Select s";
//            Assert::IsFalse(Preprocessor::isValid(input));
//
//            input = "foo s; Select s";
//            Assert::IsFalse(Preprocessor::isValid(input));
//
//            input = "stmt s 1; Select s";
//            Assert::IsFalse(Preprocessor::isValid(input));
//
//            input = "stmt s*; Select s*";
//            Assert::IsFalse(Preprocessor::isValid(input));
//
//            input = "stmt s, Select s";
//            Assert::IsFalse(Preprocessor::isValid(input));
//
//            input = "assign a; Select a such that Uses(a)";
//            Assert::IsFalse(Preprocessor::isValid(input));
//
//            input = "stmt s; Select s suchthat Uses(s, \"x\")";
//            Assert::IsFalse(Preprocessor::isValid(input));
//
//            input = "stmt s; variable v; Select s Uses(s, v)";
//            Assert::IsFalse(Preprocessor::isValid(input));
//
//            input = "stmt s1, s2; Select s such that Foo(s1, s2)";
//            Assert::IsFalse(Preprocessor::isValid(input));
//
//            input = "stmt s; variable v; Select s such that Uses(s, v) pattern (v, _)";
//            Assert::IsFalse(Preprocessor::isValid(input));
//
//            input = "assign a; variable v; Select a such that Uses(a, v) and pattern a(v, _)";
//            Assert::IsFalse(Preprocessor::isValid(input));
//
//            input = "stmt s; variable v; Select s such that Uses(_, v)";
//            Assert::IsFalse(Preprocessor::isValid(input));
//
//            input = "stmt s; variable v; Select s such that Uses(v, s)";
//            Assert::IsFalse(Preprocessor::isValid(input));
//        }
//    };
//}
