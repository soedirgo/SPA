#include "Evaluator.h"
#include "AbstractType.h"
#include "Clause.h"
#include "Dispatcher.h"
#include "PKB.h"
#include "Query.h"
#include "Result.h"
#include <functional>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;
namespace Evaluator {
    list<string> evaluate(Query q) {
        // extract info from query object
        unordered_map<string, string> declarations = q.getDeclarations();
        string selectSyn = q.getSelectSynonym();
        vector<Clause> clauses = q.getClauses();
        vector<Result> intermediateResults;

        // for every clause, get results and store in
        // intermediate results
        for (auto& clause : clauses) {
            intermediateResults.push_back(dispatch(clause, declarations));
        }

        // select clause as the starting intermediate result
        vector<string> initResults;
        TABLE initTable;
        if (declarations[selectSyn] == "stmt") {
            initTable = PKB::getStmts();
        } else if (declarations[selectSyn] == "read") {
            initTable = PKB::getReads();
        } else if (declarations[selectSyn] == "print") {
            initTable = PKB::getPrints();
        } else if (declarations[selectSyn] == "call") {
            initTable = PKB::getCalls();
        } else if (declarations[selectSyn] == "while") {
            initTable = PKB::getWhiles();
        } else if (declarations[selectSyn] == "if") {
            initTable = PKB::getIfs();
        } else if (declarations[selectSyn] == "assign") {
            initTable = PKB::getAssigns();
        } else if (declarations[selectSyn] == "variable") {
            initTable = PKB::getVariables();
        } else if (declarations[selectSyn] == "constant") {
            initTable = PKB::getConstants();
        } else if (declarations[selectSyn] == "prog_line") {
            initTable = PKB::getProgLines();
        } else if (declarations[selectSyn] == "procedure") {
            initTable = PKB::getProcedures();
        }        
        Result currentResult = Result(true, {{selectSyn, 0}}, initTable);

        // merge everything in intermediateResults
        for (auto& otherResult : intermediateResults) {
            currentResult = Result::merge(currentResult, otherResult);
        }

        if (!currentResult.hasResults())
            return {};

        // return results (projection)
        TABLE finalResults = currentResult.getResults();
        set<string> selectResultsSet;
        int selectSynIdx = currentResult.getSynonyms()[selectSyn];
        for (const auto& result : finalResults)
            selectResultsSet.insert(result[selectSynIdx]);
        list<string> selectResults;
        for (const auto& result : selectResultsSet)
            selectResults.push_back(result);
        return (selectResults);
    }
} // namespace Evaluator
