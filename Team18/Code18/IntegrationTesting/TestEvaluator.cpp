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

            pkb.setProcedure("main");
            
            pkb.setStmt("1", "assign");
            pkb.setAssignPattern("1", "1");
            pkb.setVariable("x");
            pkb.setConstant("1", "1");
            pkb.setModifiesS("1", "x");

            pkb.setStmt("2", "assign");
            pkb.setAssignPattern("2", "x");
            pkb.setVariable("y");
            pkb.setUsesS("2", "x");
            pkb.setModifiesS("2", "y");
            pkb.setFollows("1", "2");
            pkb.setFollowsT("1", "2");

            pkb.setStmt("3", "if");
            //pkb.setIfPattern("3", "(x y ==)");
            pkb.setUsesS("3", "x");
            pkb.setUsesS("3", "y");
            pkb.setModifiesS("3", "z");
            pkb.setFollows("2", "3");
            pkb.setFollowsT("1", "3");
            pkb.setFollowsT("2", "3");

            pkb.setStmt("4", "assign");
            pkb.setAssignPattern("4", "0");
            pkb.setVariable("z");
            pkb.setConstant("4", "0");
            pkb.setModifiesS("4", "z");
            pkb.setParent("3", "4");
            pkb.setParentT("3", "4");

            pkb.setStmt("5", "assign");
            pkb.setAssignPattern("5", "1");
            pkb.setConstant("5", "1");
            pkb.setModifiesS("5", "z");
            pkb.setParent("3", "5");
            pkb.setParentT("3", "5");

            pkb.setStmt("6", "while");
            //pkb.setWhilePattern("6", "(x 0 >)");
            pkb.setUsesS("6", "x");
            pkb.setModifiesS("6", "x");
            pkb.setFollows("3", "6");
            pkb.setFollowsT("1", "6");
            pkb.setFollowsT("2", "6");
            pkb.setFollowsT("3", "6");

            pkb.setStmt("7", "read");
            pkb.setRead("7", "x");
            pkb.setModifiesS("7", "x");
            pkb.setParent("6", "7");
            pkb.setParentT("6", "7");

            pkb.setStmt("8", "print");
            pkb.setPrint("8", "x");
            pkb.setUsesS("8", "x");
            pkb.setParent("6", "8");
            pkb.setParentT("6", "8");
            pkb.setFollows("7", "8");
            pkb.setFollowsT("7", "8");
		}
        TEST_METHOD(evaluatorNoClause)
        {
            unordered_map<string, string> decl = { {"s", "stmt"},
                                                   {"r", "read"},
                                                   {"p", "print"},
                                                   {"w", "while"},
                                                   {"i", "if"},
                                                   {"a", "assign"},
                                                   {"v", "variable"},
                                                   {"C", "constant"},
                                                   {"P", "procedure"} };
            list<string> expected;
            list<string> actual;

            expected = { "1", "2", "3", "4", "5", "6", "7", "8" };
			actual = Evaluator::evaluate(Query(decl, "s", {}));
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = { "7" };
            actual = Evaluator::evaluate(Query(decl, "r", {}));
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = { "8" };
            actual = Evaluator::evaluate(Query(decl, "p", {}));
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = { "6" };
            actual = Evaluator::evaluate(Query(decl, "w", {}));
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = { "3" };
            actual = Evaluator::evaluate(Query(decl, "i", {}));
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = { "1", "2", "4", "5" };
            actual = Evaluator::evaluate(Query(decl, "a", {}));
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = { "x", "y", "z" };
            actual = Evaluator::evaluate(Query(decl, "v", {}));
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = { "0", "1" };
            actual = Evaluator::evaluate(Query(decl, "C", {}));
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = { "main" };
            actual = Evaluator::evaluate(Query(decl, "P", {}));
            actual.sort();
            Assert::IsTrue(expected == actual);
        }
        TEST_METHOD(evaluatorUsesModifies)
        {
            /**
               To test:
               1. Select s such that Uses(s, v);
               2. Select r such that Modifies(r, v);
               3. Select p such that Uses(p, v);
               4. Select w such that Uses(w, v);
               5. Select i such that Uses(i, "z");
               6. Select a such that Modifies(a, "x");
               7. Select v such that Uses(2, v);
               8. Select C such that Uses(2, "x");
               9. Select P such that Modifies(P, "z");
            */
            unordered_map<string, string> decl = { {"s", "stmt"},
                                                   {"r", "read"},
                                                   {"p", "print"},
                                                   {"w", "while"},
                                                   {"i", "if"},
                                                   {"a", "assign"},
                                                   {"v", "variable"},
                                                   {"C", "constant"},
                                                   {"P", "procedure"} };
            list<string> expected;
            list<string> actual;

            expected = {"2", "3", "6", "8"};
            actual = Evaluator::evaluate(Query(decl, "s",
                                                { Clause("such that", {"Uses", "s", "v"}) }));
            actual.sort();
            Assert::IsTrue(expected == actual);
 
            expected = {"7"};
			actual = Evaluator::evaluate(Query(decl, "r",
                                                { Clause("such that", {"Modifies", "r", "v"}) }));
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = {"8"};
			actual = Evaluator::evaluate(Query(decl, "p",
                                                { Clause("such that", {"Uses", "p", "v"}) }));
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = {"6"};
            actual = Evaluator::evaluate(Query(decl, "w",
                                                { Clause("such that", {"Uses", "w", "v"}) }));
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = {};
            actual = Evaluator::evaluate(Query(decl, "i",
                                                { Clause("such that", {"Uses", "i", "\"z\""}) }));
            actual.sort();
            Assert::IsTrue(expected == actual);
 
            expected = {"1"};
            actual = Evaluator::evaluate(Query(decl, "a",
                                                { Clause("such that", {"Modifies", "a", "\"x\""}) }));
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = {"x"};
            actual = Evaluator::evaluate(Query(decl, "v",
                                                { Clause("such that", {"Uses", "2", "v"}) }));
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = {"0", "1"};
            actual = Evaluator::evaluate(Query(decl, "C",
                                                { Clause("such that", {"Uses", "2", "\"x\""}) }));
            actual.sort();
            Assert::IsTrue(expected == actual);

            //expected = {"main"};
            //actual = Evaluator::evaluate(Query(decl, "P", { {"Modifies", {"P", "z"}} }));
            //Assert::IsTrue(expected == actual);
        }
        TEST_METHOD(evaluatorFollowsParent)
        {
            /**
               1. Select s such that Follows(1, s);
               2. Select s such that Follows(s, 6);
               3. Select s such that Follows*(1, s);
               4. Select r such that Follows(r, p);
               5. Select a such that Follows*(a, w);
               6. Select s such that Parent(3, s);
               7. Select a such that Parent(i, a);
               8. Select s such that Parent(4, s);
               9. Select p such that Parent*(w, p);
               10.Select a such that Parent*(s, a);
             */
            unordered_map<string, string> decl = { {"s", "stmt"},
                                                   {"r", "read"},
                                                   {"p", "print"},
                                                   {"w", "while"},
                                                   {"i", "if"},
                                                   {"a", "assign"},
                                                   {"v", "variable"},
                                                   {"C", "constant"},
                                                   {"P", "procedure"} };
            list<string> expected;
            list<string> actual;
            
            expected = {"2"};
            actual = Evaluator::evaluate(Query(decl, "s",
                                                { Clause("such that", {"Follows", "1", "s"}) }));
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = {"3"};
            actual = Evaluator::evaluate(Query(decl, "s",
                                                { Clause("such that", {"Follows", "s", "6"}) }));
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = {"2", "3", "6"};
            actual = Evaluator::evaluate(Query(decl, "s",
                                                { Clause("such that", {"Follows*", "1", "s"}) }));
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = {"7"};
            actual = Evaluator::evaluate(Query(decl, "r",
                                                { Clause("such that", {"Follows", "r", "p"}) }));
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = {"1", "2"};
            actual = Evaluator::evaluate(Query(decl, "a",
                                                { Clause("such that", {"Follows*", "a", "w"}) }));
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = {"4", "5"};
            actual = Evaluator::evaluate(Query(decl, "s",
                                                { Clause("such that", {"Parent", "3", "s"}) }));
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = {"4", "5"};
            actual = Evaluator::evaluate(Query(decl, "a",
                                                { Clause("such that", {"Parent", "i", "a"}) }));
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = {};
            actual = Evaluator::evaluate(Query(decl, "s",
                                                { Clause("such that", {"Parent", "4", "s"}) }));
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = {"8"};
            actual = Evaluator::evaluate(Query(decl, "p",
                                                { Clause("such that", {"Parent*", "w", "p"}) }));
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = {"4", "5"};
            actual = Evaluator::evaluate(Query(decl, "a",
                                                { Clause("such that", {"Parent*", "s", "a"}) }));
            actual.sort();
            Assert::IsTrue(expected == actual);
        }
        TEST_METHOD(evaluatorPattern)
        {
            /**
               1. Select a pattern a(_, _)
               2. Select a pattern a(x, _)
               3. Select a pattern a(_, 1)
               4. Select a pattern a(z, 0)
             */
            unordered_map<string, string> decl = { {"s", "stmt"},
                                                   {"r", "read"},
                                                   {"p", "print"},
                                                   {"w", "while"},
                                                   {"i", "if"},
                                                   {"a", "assign"},
                                                   {"v", "variable"},
                                                   {"C", "constant"},
                                                   {"P", "procedure"} };
            list<string> expected;
            list<string> actual;

            expected = {"1", "2", "4", "5"};
            actual = Evaluator::evaluate(Query(decl, "a",
                                                { Clause("pattern", {"a", "_", "_"}) }));
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = {"1"};
            actual = Evaluator::evaluate(Query(decl, "a",
                                                { Clause("pattern", {"a", "\"x\"", "_"}) }));
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = {"1", "5"};
            actual = Evaluator::evaluate(Query(decl, "a",
                                                { Clause("pattern", {"a", "_", "1"}) }));
            actual.sort();
            Assert::IsTrue(expected == actual);

            expected = {"4"};
            actual = Evaluator::evaluate(Query(decl, "a",
                                                { Clause("pattern", {"a", "\"z\"", "0"}) }));
            actual.sort();
            Assert::IsTrue(expected == actual);
        }
	};
}
