#include "stdafx.h"
#include "CppUnitTest.h"
#include "Query.h"
#include "Clause.h"
#include "Evaluator.h"
#include "PKB.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestEvaluator)
	{
	public:
        TEST_METHOD_INITIALIZE(evaluatorInit)
        {
            /**
               SIMPLE program:
               procedure main {
               1.  a = 1
               2.  b = a
               3.  if (a == b) then {
               4.      c = 0;
                   } else {
               5.      c = 1;}
                   }
              */
            PKB pkb;

            pkb.clear();

            pkb.setStmt(1, Assign);
            pkb.setVar("a");
            pkb.setConstant("1");
            pkb.setModifiesVarByStmt(1, "a");

            pkb.setStmt(2, Assign);
            pkb.setVar("b");
            pkb.setUsesVarByStmt(2, "a");
            pkb.setModifiesVarByStmt(2, "b");

            pkb.setStmt(3, If);
            pkb.setUsesVarByStmt(3, "a");
            pkb.setUsesVarByStmt(3, "b");

            pkb.setStmt(4, Assign);
            pkb.setVar("c");
            pkb.setModifiesVarByStmt(3, "c");
            pkb.setModifiesVarByStmt(4, "c");

            pkb.setStmt(5, Assign);
            pkb.setModifiesVarByStmt(3, "c");
            pkb.setModifiesVarByStmt(5, "c");
		}
        TEST_METHOD(evaluatorNoClause)
        {
			unordered_map<string, string> decl = {{"s", "stmt"},
                                                  {"r", "read"},
                                                  {"p", "print"},
                                                  {"w", "while"},
                                                  {"i", "if"},
                                                  {"a", "assign"},
                                                  {"v", "variable"},
                                                  {"C", "constant"},
                                                  {"P", "procedure"}}

			Query q = Query::Query(decl, "s", {});
            Assert::AreEqual(Evaluator::evalQuery(q), "1, 2, 3, 4, 5");

			q = Query::Query(decl, "r", {});
            Assert::AreEqual(Evaluator::evalQuery(q), "");

			q = Query::Query(decl, "p", {});
            Assert::AreEqual(Evaluator::evalQuery(q), "");

			q = Query::Query(decl, "w", {});
            Assert::AreEqual(Evaluator::evalQuery(q), "");

			q = Query::Query(decl, "i", {});
            Assert::AreEqual(Evaluator::evalQuery(q), "3");

			q = Query::Query(decl, "a", {});
            Assert::AreEqual(Evaluator::evalQuery(q), "1, 2, 4, 5");

			q = Query::Query(decl, "v", {});
            Assert::AreEqual(Evaluator::evalQuery(q), "a, b, c");

			q = Query::Query(decl, "C", {});
            Assert::AreEqual(Evaluator::evalQuery(q), "0, 1");

			q = Query::Query(decl, "P", {});
            Assert::AreEqual(Evaluator::evalQuery(q), "main");
        }
        TEST_METHOD(evaluatorSuchThat)
        {
            /**
               To test:
               1. Select s such that Uses(s, v);
               2. Select r such that Modifies(r, v);
               3. Select p such that Uses(p, v);
               4. Select w such that Uses(w, v);
               5. Select i such that Uses(i, v);
               6. Select a such that Modifies(1, "a");
               6. Select v such that Uses(2, v);
               6. Select C such that Uses(4, C);
               6. Select P such that Modifies(P, "c");
             */
        }
        TEST_METHOD(evaluatorPattern)
        {
        }
        TEST_METHOD(evaluatorSuchThatPattern)
        {
        }
	};
}
