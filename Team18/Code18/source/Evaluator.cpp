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
        unordered_map<string, string> selSynAttrMap;
        vector<Clause> clauses = q.getClauses();
        vector<Result> intermediateResults;

        // for every clause, get results and store in intermediate
        // results
        for (auto& clause : clauses) {
            intermediateResults.push_back(dispatch(clause, declarations));
        }

        // evaluate select clause
        for (auto syn : selSyns) {
            size_t pos = syn.find('.');
            string attr;
            if (pos == string::npos) {
                attr = syn.substr(pos + 1, string::npos);
                syn = syn.substr(0, pos);
                selSynAttrMap[syn] = attr;
            }
            TABLE initTable;
            if (syn == "BOOLEAN") {}
            else if (declarations[syn] == "stmt")
                initTable = PKB::getStmts();
            else if (declarations[syn] == "read")
                initTable = PKB::getReads();
            else if (declarations[syn] == "print")
                initTable = PKB::getPrints();
            else if (declarations[syn] == "call")
                initTable = PKB::getCalls();
            else if (declarations[syn] == "while")
                initTable = PKB::getWhiles();
            else if (declarations[syn] == "if")
                initTable = PKB::getIfs();
            else if (declarations[syn] == "assign")
                initTable = PKB::getAssigns();
            else if (declarations[syn] == "variable")
                initTable = PKB::getVariables();
            else if (declarations[syn] == "constant")
                initTable = PKB::getConstants();
            else if (declarations[syn] == "prog_line")
                initTable = PKB::getProgLines();
            else if (declarations[syn] == "procedure")
                initTable = PKB::getProcedures();
            intermediateResults.push_back(Result(true, {{syn, 0}}, initTable));
        }

        // merge everything in intermediateResults
        Result currentResult = Result(true, {}, {});
        for (auto& otherResult : intermediateResults) {
            currentResult = Result::merge(currentResult, otherResult);
        }

        // return results (projection)
        list<string> selectResults;

        // case Select BOOLEAN
        if (selSyns[0] == "BOOLEAN") {
            selectResults.push_back(currentResult.hasResults() ? "TRUE" : "FALSE");
            return selectResults;
        }

        // otherwise project select synonyms
        if (!currentResult.hasResults())
            return {};

        TABLE finalResults = currentResult.getResults();
        unordered_map<string, int> finalResultSyns = currentResult.getSynonyms();
        for (auto res : finalResults) {
            string projectedResult;
            bool isFirstSyn = true;
            for (auto syn : selSyns) {
                if (isFirstSyn)
                    isFirstSyn = false;
                else
                    projectedResult.append(" ");
                projectedResult.append(selSynAttrMap.count(syn)
                                       ? PKB::getAttribute(res[finalResultSyns[syn]],
                                                           declarations[syn],
                                                           selSynAttrMap[syn])
                                       : res[finalResultSyns[syn]]);
            }
            selectResults.push_back(projectedResult);
        }
        selectResults.sort();
        selectResults.unique();
        return selectResults;
    }
} // namespace Evaluator 
