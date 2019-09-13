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
            pkb.setConstant("1");
            pkb.setModifiesVarByStmt(1, "x");

            pkb.setStmt(2, Assign);
            pkb.setAssignStmt(2, "y");
            pkb.setVar("y");
            pkb.setUsesVarByStmt(2, "x");
            pkb.setModifiesVarByStmt(2, "y");

            pkb.setStmt(3, If);
            pkb.setIfStmt(3);
            pkb.setUsesVarByStmt(3, "x");
            pkb.setUsesVarByStmt(3, "y");
            pkb.setModifiesVarByStmt(3, "z");

            pkb.setStmt(4, Assign);
            pkb.setAssignStmt(4, "z");
            pkb.setVar("z");
            pkb.setConstant("0");
            pkb.setModifiesVarByStmt(4, "z");

            pkb.setStmt(5, Assign);
            pkb.setAssignStmt(5, "z");
            pkb.setModifiesVarByStmt(5, "z");

            pkb.setStmt(6, While);
            pkb.setWhileStmt(6);
            pkb.setUsesVarByStmt(6, "x");
            pkb.setModifiesVarByStmt(6, "x");

            pkb.setStmt(7, Read);
            pkb.setReadStmt(7, "x");
            pkb.setModifiesVarByStmt(7, "x");

            pkb.setStmt(8, Print);
            pkb.setPrintStmt(8, "x");
            pkb.setUsesVarByStmt(8, "x");
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
            Assert::AreEqual((string)"1, 2, 3, 4, 5, 6, 7, 8", Evaluator::evalQuery(q));

			q = Query(decl, "r", {});
            Assert::AreEqual((string)"7", Evaluator::evalQuery(q));

			q = Query(decl, "p", {});
            Assert::AreEqual((string)"8", Evaluator::evalQuery(q));

			q = Query(decl, "w", {});
            Assert::AreEqual((string)"6", Evaluator::evalQuery(q));

            q = Query(decl, "i", {});
            Assert::AreEqual((string)"3", Evaluator::evalQuery(q));

			q = Query(decl, "a", {});
            Assert::AreEqual((string)"1, 2, 4, 5", Evaluator::evalQuery(q));

			q = Query(decl, "v", {});
            Assert::AreEqual((string)"x, y, z", Evaluator::evalQuery(q));

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
               5. Select i such that Uses(i, "z");
               6. Select a such that Modifies(a, "x");
               6. Select v such that Uses(2, v);
               6. Select C such that Uses(2, "x");
               6. Select P such that Modifies(P, "z");
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
            Assert::AreEqual((string)"2, 3, 6, 8", Evaluator::evalQuery(q));

            q = Query(decl, "r", { {"modifies", {"r", "v"}} });
            Assert::AreEqual((string)"7", Evaluator::evalQuery(q));

            q = Query(decl, "p", { {"uses", {"p", "v"}} });
            Assert::AreEqual((string)"8", Evaluator::evalQuery(q));

            q = Query(decl, "w", { {"uses", {"w", "v"}} });
            Assert::AreEqual((string)"6", Evaluator::evalQuery(q));

            q = Query(decl, "i", { {"uses", {"i", "z"}} });
            Assert::AreEqual((string)"", Evaluator::evalQuery(q));

            q = Query(decl, "a", { {"modifies", {"a", "x"}} });
            Assert::AreEqual((string)"1", Evaluator::evalQuery(q));

            q = Query(decl, "v", { {"uses", {"2", "v"}} });
            Assert::AreEqual((string)"x", Evaluator::evalQuery(q));

            q = Query(decl, "C", { {"uses", {"2", "x"}} });
            Assert::AreEqual((string)"1, 0", Evaluator::evalQuery(q));

            //q = Query(decl, "P", { {"modifies", {"P", "z"}} });
            //Assert::AreEqual((string)"main", Evaluator::evalQuery(q));
        }
        TEST_METHOD(evaluatorPattern)
        {
        }
        TEST_METHOD(evaluatorSuchThatPattern)
        {
        }
	};
}
