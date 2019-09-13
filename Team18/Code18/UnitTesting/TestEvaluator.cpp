#include "stdafx.h"
#include "CppUnitTest.h"
#include "Query.h"
#include "Clause.h"
#include "Evaluator.h"
#include "TestEvaluatorPKB.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestEvaluator)
	{
    private:
        unordered_map<string, string> decl;
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

            decl = { {"s", "stmt"},
                     {"r", "read"},
                     {"p", "print"},
                     {"w", "while"},
                     {"i", "if"},
                     {"a", "assign"},
                     {"v", "variable"},
                     {"C", "constant"},
                     {"P", "procedure"} };
		}
        TEST_METHOD(evaluatorNoClause)
        {
			Query q = Query(decl, "s", {});
            Assert::AreEqual({"1", "2", "3", "4", "5", "6", "7", "8"},
                             Evaluator::evalQuery(q));

			q = Query(decl, "r", {});
            Assert::AreEqual({"7"}, Evaluator::evalQuery(q));

			q = Query(decl, "p", {});
            Assert::AreEqual({"8"}, Evaluator::evalQuery(q));

			q = Query(decl, "w", {});
            Assert::AreEqual({"6"}, Evaluator::evalQuery(q));

            q = Query(decl, "i", {});
            Assert::AreEqual({"3"}, Evaluator::evalQuery(q));

			q = Query(decl, "a", {});
            Assert::AreEqual({"1", "2", "4", "5"}, Evaluator::evalQuery(q));

			q = Query(decl, "v", {});
            Assert::AreEqual({"x", "y", "z"}, Evaluator::evalQuery(q));

			q = Query(decl, "C", {});
            Assert::AreEqual({"1", "0"}, Evaluator::evalQuery(q));

			q = Query(decl, "P", {});
            Assert::AreEqual({"main"}, Evaluator::evalQuery(q));
        }
        TEST_METHOD(evaluatorSuchThat)
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

            Query q = Query(decl, "s", { {"uses", {"s", "v"}} });
            Assert::AreEqual({"2", "3", "6", "8"}, Evaluator::evalQuery(q));

            q = Query(decl, "r", { {"modifies", {"r", "v"}} });
            Assert::AreEqual({"7"}, Evaluator::evalQuery(q));

            q = Query(decl, "p", { {"uses", {"p", "v"}} });
            Assert::AreEqual({"8"}, Evaluator::evalQuery(q));

            q = Query(decl, "w", { {"uses", {"w", "v"}} });
            Assert::AreEqual({"6"}, Evaluator::evalQuery(q));

            q = Query(decl, "i", { {"uses", {"i", "z"}} });
            Assert::AreEqual({""}, Evaluator::evalQuery(q));

            q = Query(decl, "a", { {"modifies", {"a", "x"}} });
            Assert::AreEqual({"1"}, Evaluator::evalQuery(q));

            q = Query(decl, "v", { {"uses", {"2", "v"}} });
            Assert::AreEqual({"x"}, Evaluator::evalQuery(q));

            q = Query(decl, "C", { {"uses", {"2", "x"}} });
            Assert::AreEqual({"1", "0"}, Evaluator::evalQuery(q));

            //q = Query(decl, "P", { {"modifies", {"P", "z"}} });
            //Assert::AreEqual({"main"}, Evaluator::evalQuery(q));
        }
        TEST_METHOD(evaluatorPattern)
        {
        }
        TEST_METHOD(evaluatorSuchThatPattern)
        {
        }
	};
}
