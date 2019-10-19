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
        vector<string> selSyns = q.getSelectSynonyms();
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
        if (declarations[selSyns[0]] == "stmt") {
            initTable = PKB::getStmts();
        } else if (declarations[selSyns[0]] == "read") {
            initTable = PKB::getReads();
        } else if (declarations[selSyns[0]] == "print") {
            initTable = PKB::getPrints();
        } else if (declarations[selSyns[0]] == "call") {
            initTable = PKB::getCalls();
        } else if (declarations[selSyns[0]] == "while") {
            initTable = PKB::getWhiles();
        } else if (declarations[selSyns[0]] == "if") {
            initTable = PKB::getIfs();
        } else if (declarations[selSyns[0]] == "assign") {
            initTable = PKB::getAssigns();
        } else if (declarations[selSyns[0]] == "variable") {
            initTable = PKB::getVariables();
        } else if (declarations[selSyns[0]] == "constant") {
            initTable = PKB::getConstants();
        } else if (declarations[selSyns[0]] == "prog_line") {
            initTable = PKB::getProgLines();
        } else if (declarations[selSyns[0]] == "procedure") {
            initTable = PKB::getProcedures();
        }        
        Result currentResult = Result(true, {{selSyns[0], 0}}, initTable);

        // merge everything in intermediateResults
        for (auto& otherResult : intermediateResults) {
            currentResult = Result::merge(currentResult, otherResult);
        }

        if (!currentResult.hasResults())
            return {};

        // return results (projection)
        TABLE finalResults = currentResult.getResults();
        set<string> selectResultsSet;
        int selSynIdx = currentResult.getSynonyms()[selSyns[0]];
        for (const auto& result : finalResults)
            selectResultsSet.insert(result[selSynIdx]);
        list<string> selectResults;
        for (const auto& result : selectResultsSet)
            selectResults.push_back(result);
        return (selectResults);
    }
} // namespace Evaluator
