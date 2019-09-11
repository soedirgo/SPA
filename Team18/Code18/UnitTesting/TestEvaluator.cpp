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
            PKB pkb;

            pkb.clear();
            pkb.setStmt(1, Assign);
            pkb.setVar("x");
            pkb.setConstant("1");
            pkb.setModifiesVarByStmt(1, "x");
		}
        TEST_METHOD(evalQueryStatement)
        {
			unordered_map<string, string> decl = { {"s", "stmt"},
									  {"v", "variable"},
									  {"c", "constant"} };
			Query q = Query::Query(decl, "s", {});
            string actual = Evaluator::evalQuery(q);
            string expected = "1";
            Assert::IsTrue(actual == expected);                
        }
        TEST_METHOD(evalQueryVariable)
        {
			unordered_map<string, string> decl = { {"s", "stmt"},
									  {"v", "variable"},
									  {"c", "constant"} };
			Query q = Query::Query(decl, "v", {});
            string actual = Evaluator::evalQuery(q);
            string expected = "x";
            Assert::IsTrue(actual == expected);                
        }
        TEST_METHOD(evalQueryConstant)
        {
			unordered_map<string, string> decl = { {"s", "stmt"},
									  {"v", "variable"},
									  {"c", "constant"} };
			Query q = Query::Query(decl, "c", {});
            string actual = Evaluator::evalQuery(q);
            string expected = "1";
            Assert::IsTrue(actual == expected);                
        }
	};
}
