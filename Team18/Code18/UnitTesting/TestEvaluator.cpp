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

            pkb.setProc("main");
            pkb.setStmt(1, Assign);
            pkb.setAssignStmt(1, "a");
            pkb.setVar("a");
            pkb.setConstant("1");
            pkb.setModifiesVarByStmt(1, "a");

            pkb.setStmt(2, Assign);
            pkb.setAssignStmt(2, "b");
            pkb.setVar("b");
            pkb.setUsesVarByStmt(2, "a");
            pkb.setModifiesVarByStmt(2, "b");

            pkb.setStmt(3, If);
            pkb.setIfStmt(3);
            pkb.setUsesVarByStmt(3, "a");
            pkb.setUsesVarByStmt(3, "b");

            pkb.setStmt(4, Assign);
            pkb.setAssignStmt(4, "c");
            pkb.setVar("c");
            pkb.setConstant("0");
            pkb.setModifiesVarByStmt(3, "c");
            pkb.setModifiesVarByStmt(4, "c");

            pkb.setStmt(5, Assign);
            pkb.setAssignStmt(5, "c");
            pkb.setModifiesVarByStmt(3, "c");
            pkb.setModifiesVarByStmt(5, "c");
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

			Query q = Query(decl, "s", {});
            Assert::AreEqual((string)"1, 2, 3, 4, 5", Evaluator::evalQuery(q));

			q = Query(decl, "r", {});
            Assert::AreEqual((string)"", Evaluator::evalQuery(q));

			q = Query(decl, "p", {});
            Assert::AreEqual((string)"", Evaluator::evalQuery(q));

			q = Query(decl, "w", {});
            Assert::AreEqual((string)"", Evaluator::evalQuery(q));

            q = Query(decl, "i", {});
            Assert::AreEqual((string)"3", Evaluator::evalQuery(q));

			q = Query(decl, "a", {});
            Assert::AreEqual((string)"1, 2, 4, 5", Evaluator::evalQuery(q));

			q = Query(decl, "v", {});
            Assert::AreEqual((string)"a, b, c", Evaluator::evalQuery(q));

			q = Query(decl, "C", {});
            Assert::AreEqual((string)"1, 0", Evaluator::evalQuery(q));

			q = Query(decl, "P", {});
            Assert::AreEqual((string)"main", Evaluator::evalQuery(q));
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
