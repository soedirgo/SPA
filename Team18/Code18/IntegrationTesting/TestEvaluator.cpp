#include "stdafx.h"
#include "CppUnitTest.h"
#include "Query.h"
#include "Clause.h"
#include "Evaluator.h"
#include "PKB.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTesting
{
	TEST_CLASS(TestEvaluator)
	{
	public:
        TEST_METHOD_INITIALIZE(evaluatorInit)
        {
            /**
             * SIMPLE source:
             *     procedure main {
             *  1.   a = 1;
             *  2.   if (b == 2) {
             *  3.     while (c == 3) {
             *  4.       while (d == 4) {
             *  5.         if (e == 5) {
             *  6.           if (f == 6) {
             *  7.             read g; }
             *               else {
             *  8.             while (h == 7) {
             *  9.               call sub; } } }
             *             else {
             * 10.           read i; } } } }
             *       else {
             * 11.     print j; }
             *     }
             *
             *     procedure sub {
             * 12.   a = 8;
             * 13.   b = a;
             *     }
             */

            PKB pkb;

            pkb.clear();

            pkb.setProcedure("main");
            pkb.setProcedure("sub");

            pkb.setVariable("a");
            pkb.setVariable("b");
            pkb.setVariable("c");
            pkb.setVariable("d");
            pkb.setVariable("e");
            pkb.setVariable("f");
            pkb.setVariable("g");
            pkb.setVariable("h");
            pkb.setVariable("i");
            pkb.setVariable("j");

            pkb.setConstant("1", "1");
            pkb.setConstant("2", "2");
            pkb.setConstant("3", "3");
            pkb.setConstant("4", "4");
            pkb.setConstant("5", "5");
            pkb.setConstant("6", "6");
            pkb.setConstant("8", "7");
            pkb.setConstant("12", "8");

            pkb.setStmt("1", "assign");
            pkb.setStmt("2", "if");
            pkb.setStmt("3", "while");
            pkb.setStmt("4", "while");
            pkb.setStmt("5", "if");
            pkb.setStmt("6", "if");
            pkb.setStmt("7", "read");
            pkb.setStmt("8", "while");
            pkb.setStmt("9", "call");
            pkb.setStmt("10", "read");
            pkb.setStmt("11", "print");
            pkb.setStmt("12", "assign");
            pkb.setStmt("13", "assign");

            pkb.setCallStmt("9", "sub");

            pkb.setRead("7", "g");
            pkb.setRead("10", "i");

            pkb.setPrint("11", "j");

            pkb.setUsesP("main", "a");
            pkb.setUsesP("main", "b");
            pkb.setUsesP("main", "c");
            pkb.setUsesP("main", "d");
            pkb.setUsesP("main", "e");
            pkb.setUsesP("main", "f");
            pkb.setUsesP("main", "h");
            pkb.setUsesP("main", "j");
            pkb.setUsesP("sub", "a");

            pkb.setUsesS("2", "a");
            pkb.setUsesS("2", "b");
            pkb.setUsesS("2", "c");
            pkb.setUsesS("2", "d");
            pkb.setUsesS("2", "e");
            pkb.setUsesS("2", "f");
            pkb.setUsesS("2", "h");
            pkb.setUsesS("2", "j");
            pkb.setUsesS("3", "a");
            pkb.setUsesS("3", "c");
            pkb.setUsesS("3", "d");
            pkb.setUsesS("3", "e");
            pkb.setUsesS("3", "f");
            pkb.setUsesS("3", "h");
            pkb.setUsesS("4", "a");
            pkb.setUsesS("4", "d");
            pkb.setUsesS("4", "e");
            pkb.setUsesS("4", "f");
            pkb.setUsesS("4", "h");
            pkb.setUsesS("5", "a");
            pkb.setUsesS("5", "e");
            pkb.setUsesS("5", "f");
            pkb.setUsesS("5", "h");
            pkb.setUsesS("6", "a");
            pkb.setUsesS("6", "f");
            pkb.setUsesS("6", "g");
            pkb.setUsesS("8", "a");
            pkb.setUsesS("8", "h");
            pkb.setUsesS("9", "a");
            pkb.setUsesS("11", "j");
            pkb.setUsesS("13", "a");

            pkb.setModifiesP("main", "a");
            pkb.setModifiesP("main", "g");
            pkb.setModifiesP("main", "i");
            pkb.setModifiesP("sub", "a");
            pkb.setModifiesP("sub", "b");

            pkb.setModifiesS("1", "a");
            pkb.setModifiesS("2", "a");
            pkb.setModifiesS("2", "b");
            pkb.setModifiesS("2", "g");
            pkb.setModifiesS("2", "i");
            pkb.setModifiesS("3", "a");
            pkb.setModifiesS("3", "b");
            pkb.setModifiesS("3", "g");
            pkb.setModifiesS("3", "i");
            pkb.setModifiesS("4", "a");
            pkb.setModifiesS("4", "b");
            pkb.setModifiesS("4", "g");
            pkb.setModifiesS("4", "i");
            pkb.setModifiesS("5", "a");
            pkb.setModifiesS("5", "b");
            pkb.setModifiesS("5", "g");
            pkb.setModifiesS("5", "i");
            pkb.setModifiesS("6", "a");
            pkb.setModifiesS("6", "b");
            pkb.setModifiesS("6", "g");
            pkb.setModifiesS("7", "g");
            pkb.setModifiesS("8", "a");
            pkb.setModifiesS("8", "b");
            pkb.setModifiesS("9", "a");
            pkb.setModifiesS("9", "b");
            pkb.setModifiesS("10", "i");
            pkb.setModifiesS("12", "a");
            pkb.setModifiesS("13", "b");

            pkb.setCallProc("main", "sub");

            pkb.setCallT("main", "sub");

            pkb.setFollows("1", "2");
            pkb.setFollows("12", "13");

            pkb.setFollowsT("1", "2");
            pkb.setFollowsT("12", "13");

            pkb.setParent("2", "3");
            pkb.setParent("2", "11");
            pkb.setParent("3", "4");
            pkb.setParent("4", "5");
            pkb.setParent("5", "6");
            pkb.setParent("5", "10");
            pkb.setParent("6", "7");
            pkb.setParent("6", "8");
            pkb.setParent("8", "9");

            pkb.setParentT("2", "3");
            pkb.setParentT("2", "4");
            pkb.setParentT("2", "5");
            pkb.setParentT("2", "6");
            pkb.setParentT("2", "7");
            pkb.setParentT("2", "8");
            pkb.setParentT("2", "9");
            pkb.setParentT("2", "10");
            pkb.setParentT("2", "11");
            pkb.setParentT("3", "4");
            pkb.setParentT("3", "5");
            pkb.setParentT("3", "6");
            pkb.setParentT("3", "7");
            pkb.setParentT("3", "8");
            pkb.setParentT("3", "9");
            pkb.setParentT("3", "10");
            pkb.setParentT("4", "5");
            pkb.setParentT("4", "6");
            pkb.setParentT("4", "7");
            pkb.setParentT("4", "8");
            pkb.setParentT("4", "9");
            pkb.setParentT("4", "10");
            pkb.setParentT("5", "6");
            pkb.setParentT("5", "7");
            pkb.setParentT("5", "8");
            pkb.setParentT("5", "9");
            pkb.setParentT("5", "10");
            pkb.setParentT("6", "7");
            pkb.setParentT("6", "8");
            pkb.setParentT("6", "9");
            pkb.setParentT("8", "9");

            pkb.setNext("1", "2");
            pkb.setNext("2", "3");
            pkb.setNext("2", "11");
            pkb.setNext("3", "4");
            pkb.setNext("4", "5");
            pkb.setNext("5", "6");
            pkb.setNext("5", "10");
            pkb.setNext("6", "7");
            pkb.setNext("6", "8");
            pkb.setNext("8", "9");
            pkb.setNext("12", "13");

            pkb.setAssignPattern("1", " 1 ");
            pkb.setAssignPattern("12", " 8 ");
            pkb.setAssignPattern("13", " a ");

            pkb.setIfPattern("2", " b 2 == ");
            pkb.setIfPattern("5", " e 5 == ");
            pkb.setIfPattern("6", " f 6 == ");

            pkb.setWhilePattern("3", " c 3 == ");
            pkb.setWhilePattern("4", " d 4 == ");
            pkb.setWhilePattern("8", " h 7 == ");
		}
        TEST_METHOD(testNoClause)
        {
            unordered_map<string, string> decl = { {"s", "stmt"},
                                                   {"r", "read"},
                                                   {"p", "print"},
                                                   {"c", "call"},
                                                   {"w", "while"},
                                                   {"i", "if"},
                                                   {"a", "assign"},
                                                   {"v", "variable"},
                                                   {"cons", "constant"},
                                                   {"n", "prog_line"},
                                                   {"proc", "procedure"} };
            list<string> expected;
            list<string> actual;

            expected = { "1", "2", "3", "4", "5", "6", "7",
                         "8", "9", "10", "11", "12", "13" };
            actual = Evaluator::evaluate(Query(decl, "s", {}));
            expected.sort();
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = { "7", "10" };
            actual = Evaluator::evaluate(Query(decl, "r", {}));
            expected.sort();
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = { "11" };
            actual = Evaluator::evaluate(Query(decl, "p", {}));
            expected.sort();
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = { "9" };
            actual = Evaluator::evaluate(Query(decl, "c", {}));
            expected.sort();
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = { "3", "4", "8" };
            actual = Evaluator::evaluate(Query(decl, "w", {}));
            expected.sort();
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = { "2", "5", "6" };
            actual = Evaluator::evaluate(Query(decl, "i", {}));
            expected.sort();
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = { "1", "12", "13" };
            actual = Evaluator::evaluate(Query(decl, "a", {}));
            expected.sort();
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j" };
            actual = Evaluator::evaluate(Query(decl, "v", {}));
            expected.sort();
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = { "1", "2", "3", "4", "5", "6", "7", "8" };
            actual = Evaluator::evaluate(Query(decl, "cons", {}));
            expected.sort();
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = { "1", "2", "3", "4", "5", "6", "7",
                         "8", "9", "10", "11", "12", "13" };
            actual = Evaluator::evaluate(Query(decl, "n", {}));
            expected.sort();
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = { "main", "sub" };
            actual = Evaluator::evaluate(Query(decl, "proc", {}));
            expected.sort();
            actual.sort();
            Assert::IsTrue(expected == actual);
        }
        TEST_METHOD(testOneSuchThatClause)
        {
            unordered_map<string, string> decl = { {"s", "stmt"},
                                                   {"r", "read"},
                                                   {"p", "print"},
                                                   {"c", "call"},
                                                   {"w", "while"},
                                                   {"i", "if"},
                                                   {"a", "assign"},
                                                   {"v", "variable"},
                                                   {"cons", "constant"},
                                                   {"n", "prog_line"},
                                                   {"proc", "procedure"} };
            list<string> expected;
            list<string> actual;

            /**
             * Select s such that UsesS(s, v)
             * Select cons such that UsesP("main", _)
             * Select v such that ModifiesS(2, v)
             * Select c such that ModifiesP(("sub", "b")
             * Select n such that Calls("main", "main")
             * Select c such that CallsT("main", c)
             * Select p such that Follows(2, _)
             * Select s such that FollowsT(s, 2)
             * Select r such that Parent(9, _)
             * Select i such that ParentT(i, w)
             * Select proc such that Next(9, _)
             * Select a such that NextT(n, 11)
             */
        }
        TEST_METHOD(testOnePatternClause)
        {
            unordered_map<string, string> decl = { {"s", "stmt"},
                                                   {"r", "read"},
                                                   {"p", "print"},
                                                   {"c", "call"},
                                                   {"w", "while"},
                                                   {"i", "if"},
                                                   {"a", "assign"},
                                                   {"v", "variable"},
                                                   {"cons", "constant"},
                                                   {"n", "prog_line"},
                                                   {"proc", "procedure"} };
            list<string> expected;
            list<string> actual;

            /**
             * Select a pattern a(_, 8)
             * Select a pattern a("b", " a ")
             * Select i pattern i(v, _, _)
             * Select w pattern w(_, _)
             */
        }
        TEST_METHOD(testOneWithClause)
        {
            unordered_map<string, string> decl = { {"s", "stmt"},
                                                   {"r", "read"},
                                                   {"p", "print"},
                                                   {"c", "call"},
                                                   {"w", "while"},
                                                   {"i", "if"},
                                                   {"a", "assign"},
                                                   {"v", "variable"},
                                                   {"cons", "constant"},
                                                   {"n", "prog_line"},
                                                   {"proc", "procedure"} };
            list<string> expected;
            list<string> actual;

            /**
             * Select c with c.procName = cons.value
             * Select v with v.varName = "h"
             * Select n with n = cons.value
             * Select cons with 1 = 2
             */
        }
        TEST_METHOD(testMultiClauses)
        {
            unordered_map<string, string> decl = { {"s", "stmt"},
                                                   {"r", "read"},
                                                   {"p", "print"},
                                                   {"c", "call"},
                                                   {"w", "while"},
                                                   {"i", "if"},
                                                   {"a", "assign"},
                                                   {"v", "variable"},
                                                   {"cons", "constant"},
                                                   {"n", "prog_line"},
                                                   {"proc", "procedure"} };
            list<string> expected;
            list<string> actual;

            /**
             * TODO:
             * multi same type syn
             * overlapping syn
             * 5
             */
        }
        TEST_METHOD(testBooleanTuple)
        {
            unordered_map<string, string> decl = { {"s", "stmt"},
                                                   {"r", "read"},
                                                   {"p", "print"},
                                                   {"c", "call"},
                                                   {"w", "while"},
                                                   {"i", "if"},
                                                   {"a", "assign"},
                                                   {"v", "variable"},
                                                   {"cons", "constant"},
                                                   {"n", "prog_line"},
                                                   {"proc", "procedure"} };
            list<string> expected;
            list<string> actual;

            /**
             * TODO:
             * multi same type syn
             * overlapping syn
             * 5
             */
        }
	};
}
