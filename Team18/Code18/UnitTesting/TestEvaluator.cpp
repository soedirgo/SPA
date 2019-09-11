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
        TEST_METHOD_INITIALIZE(initializePkb)
        {
            PKB pkb;
			// pkb.clear();
			// pkb.setStmt(1, While);
			// pkb.setStmt(2, If);
			// pkb.setStmt(3, Print);
			// pkb.setStmt(4, Read);

			// pkb.setVar("x");
			// pkb.setVar("y");
			// pkb.setVar("z");

			// pkb.setConstant("1");
			// pkb.setConstant("1");
			// pkb.setConstant("1");

			// pkb.setModifiesVarByStmt(1, "x");
			// pkb.setUsesVarByStmt(1, "x");

			// pkb.setModifiesStmtByVar(1, "y");
			// pkb.setUsesStmtByVar(1, "y");
            pkb.clear();
            pkb.setStmt(1, Assign);
            pkb.setVar("x");
            pkb.setConstant("1");
            pkb.setModifiesVarByStmt(1, "x");
        }
		TEST_METHOD(initializeQueries)
		{
            unordered_map<string, string> decl = {{"s", "stmt"},
                                                  {"v", "variable"},
                                                  {"c", "constant"}};
            Query q1 = Query::Query(decl, "s", {});
            Query q2 = Query::Query(decl, "v", {});
            Query q3 = Query::Query(decl, "c", {});
		}
        TEST_METHOD(evalQueryStatement)
        {
            /*string actual = Evaluator::evalQuery(q1);
            string expected = "1";
            Assert::IsTrue(actual == expected); 
			*/
        }
        TEST_METHOD(evalQueryVariable)
        {
            /*
			string actual = Evaluator::evalQuery(q2);
            string expected = "x";
            Assert::IsTrue(actual == expected);  
			*/
        }
        TEST_METHOD(evalQueryConstant)
        {
			/*
            string actual = Evaluator::evalQuery(q6);
            string expected = "1";
            Assert::IsTrue(actual == expected);     
			*/
        }
	};
}
