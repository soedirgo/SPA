#include "Evaluator.h"
#include "AbstractType.h"
#include "Clause.h"
#include "Dispatcher.h"
#include "Optim.h"
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
        unordered_map<int, string> selSynAttrMap;
        vector<Clause> clauses = q.getClauses();
        vector<Result> ungroupedResults;
        vector<Result> noSynGroup;
        vector<Result> selSynGroup;
        vector<vector<Result>> otherGroups;

        // separate attributes from select synonyms
        for (size_t i = 0; i < selSyns.size(); ++i) {
            string& syn = selSyns[i];
            size_t pos = syn.find('.');
            string attr;
            if (pos != string::npos) {
                attr = syn.substr(pos + 1, string::npos);
                syn = syn.substr(0, pos);
                selSynAttrMap[i] = attr;
            }
        }

        // evaluate select clause
        for (auto syn : selSyns) {
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
            ungroupedResults.push_back(Result(true, {{syn, 0}}, initTable));
        }

        // evaluate clauses
        for (auto& clause : clauses) {
            Result temp = dispatch(clause, declarations);
            if (!temp.hasResults()) {
                if (selSyns[0] == "BOOLEAN")
                    return { "FALSE" };
                else
                    return {};
            }
            ungroupedResults.push_back(temp);
        }

        // group the results into no synonym, select synonym group, and other groups
        vector<vector<Result>> allResults = group(ungroupedResults, selSyns);
        noSynGroup = allResults[0];
        selSynGroup = allResults[1];
        otherGroups = vector<vector<Result>>(allResults.begin() + 2, allResults.end());

        // merge no synonym group
        Result noSynResult = Result(true, {}, {});
        for (auto resultIt : noSynGroup) {
            noSynResult = Result::merge(noSynResult, resultIt);
            if (!noSynResult.hasResults()) {
                if (selSyns[0] == "BOOLEAN")
                    return { "FALSE" };
                else
                    return {};
            }
        }

        // merge other groups
        Result otherResult = Result(true, {}, {});
        for (auto& groupIt : otherGroups) {
            sort(groupIt);
            Result groupResult = Result(true, {}, {});
            for (auto& resultIt : groupIt) {
                groupResult = Result::merge(groupResult, resultIt);
                if (!groupResult.hasResults()) {
                    if (selSyns[0] == "BOOLEAN")
                        return { "FALSE" };
                    else
                        return {};
                }
            }
            otherResult = Result::merge(otherResult, groupResult);
            if (!otherResult.hasResults()) {
                if (selSyns[0] == "BOOLEAN")
                    return { "FALSE" };
                else
                    return {};
            }
        }

        // case Select BOOLEAN
        if (selSyns[0] == "BOOLEAN") {
            return { "TRUE" };
        }

        // merge select synonym group
        sort(selSynGroup);
        Result selectResult = Result(true, {}, {});
        for (auto& resultIt : selSynGroup) {
            selectResult = Result::merge(selectResult, resultIt);
            if (!selectResult.hasResults())
                return {};
        }

        // return results (projection)
        list<string> selectResults;
        TABLE finalResults = selectResult.getResults();
        unordered_map<string, int> finalResultSyns = selectResult.getSynonyms();
        for (auto res : finalResults) {
            string projectedResult;
            for (size_t i = 0; i < selSyns.size(); ++i) {
                if (i) projectedResult.append(" ");
                string syn = selSyns[i];
                projectedResult.append(selSynAttrMap.count(i)
                                       ? PKB::getAttribute(res[finalResultSyns[syn]],
                                                           declarations[syn],
                                                           selSynAttrMap[i])
                                       : res[finalResultSyns[syn]]);
            }
            selectResults.push_back(projectedResult);
        }
        selectResults.sort();
        selectResults.unique();
        return selectResults;
    }
} // namespace Evaluator
