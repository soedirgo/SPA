#include <functional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include "Clause.h"
#include "Dispatcher.h"
#include "Evaluator.h"
#include "PKB.h"
#include "PKBHash.h"
#include "Query.h"
using namespace std;

namespace Evaluator {
    namespace {
        class Result {
        public:
            Result() {}

            Result(bool resExists,
                   unordered_map<string, int> syn,
                   unordered_set<vector<string>> res)
                : resultExists(resExists),
                  synonyms(syn),
                  results(res) {}

            static Result merge(Result& r1, Result& r2) {
                bool resultExists = r1.hasResults() || r2.hasResults();
                if (!r1.getResults().size()) {
                    if (!r2.getResults().size()) {
                        // both empty
                        return Result(resultExists, {}, {});
                    } else {
                        // only r1 empty
                        return Result(resultExists, r2.getSynonyms(), r2.getResults());
                    }
                } else if (!r2.getResults().size()) {
                    // only r2 empty
                    return Result(r1.hasResults() || r2.hasResults(),
                                  r1.getSynonyms(), r1.getResults());
                } else {
                    // both non-empty
                    unordered_map<string, int> r1Synonyms = r1.getSynonyms();
                    unordered_map<string, int> r2Synonyms = r2.getSynonyms();
                    unordered_map<string, int> synonyms = r1Synonyms;
                    vector<string> overlappingSynonyms;
                    vector<string> newSynonyms;
                    for (const auto& it : r2Synonyms) {
                        if (r1Synonyms.count(it.first)) {
                            overlappingSynonyms.push_back(it.first);
                        } else {
                            newSynonyms.push_back(it.first);
                            synonyms[it.first] = synonyms.size();
                        }
                    }

                    unordered_set<vector<string>> results;
                    for (auto r1e : r1.getResults()) {
                        for (auto r2e : r2.getResults()) {
                            // if overlaps don't match, continue
                            bool overlapMatches = true;
                            for (const auto& syn : overlappingSynonyms) {
                                if (r1e[r1Synonyms[syn]] != r2e[r2Synonyms[syn]]) {
                                    overlapMatches = false;
                                    break;
                                }
                            }
                            if (!overlapMatches) {
                                continue;
                            }

                            // cross-product new synonyms
                            vector<string>& mergedResult = r1e;
                            for (const auto& syn : newSynonyms) {
                                mergedResult.push_back(r2e[r2Synonyms[syn]]);
                            }
                            results.insert(mergedResult);
                        }
                    }

                    return Result(r1.hasResults() || r2.hasResults(),
                                  synonyms, results);
                }
            }

            bool hasResults() const {
                return this->resultExists;
            }

            unordered_map<string, int> getSynonyms() const {
                return this->synonyms;
            }

            unordered_set<vector<string>> getResults() const {
                return this->results;
            }
        private:
            bool resultExists;
            unordered_map<string, int> synonyms;
            unordered_set<vector<string>> results;
        };

        unordered_map<string, string> declarations;
        vector<Clause> clauses;
        string selectSyn;
        vector<Result> intermediateResults;
    }

    list<string> evalQuery(Query q) {
        // extract info from query object
        declarations = q.getDeclarations();
        selectSyn = q.getSelectSynonym();
        clauses = q.getClauses();

        // for every clause, get results and store in
        // intermediate results
        bool resultExists;
        unordered_map<string, int> synonyms;
        unordered_set<vector<string>> results;
        for (auto& clause : clauses) {
            resultExists = false;
            synonyms = {};
            results = {};
            Dispatcher::dispatch(clause,
                                 declarations,
                                 resultExists,
                                 synonyms,
                                 results);
            intermediateResults.push_back(Result(resultExists, synonyms, results));
        }

        // select clause as the starting intermediate result
        vector<string> initResults;
        unordered_set<vector<string>> initTable;
        if (declarations[selectSyn] == "stmt") {
            for (const auto& elem : PKB::getStmts()) {
                initTable.insert(vector<string>({elem}));
            }
        } else if (declarations[selectSyn] == "read") {
            for (const auto& elem : PKB::getReads()) {
                initTable.insert(vector<string>({elem}));
            }
        } else if (declarations[selectSyn] == "print") {
            for (const auto& elem : PKB::getPrints()) {
                initTable.insert(vector<string>({elem}));
            }
        } else if (declarations[selectSyn] == "call") {
            for (const auto& elem : PKB::getCalls()) {
                initTable.insert(vector<string>({elem}));
            }
        } else if (declarations[selectSyn] == "while") {
            for (const auto& elem : PKB::getWhiles()) {
                initTable.insert(vector<string>({elem}));
            }
        } else if (declarations[selectSyn] == "if") {
            for (const auto& elem : PKB::getIfs()) {
                initTable.insert(vector<string>({elem}));
            }
        } else if (declarations[selectSyn] == "assign") {
            for (const auto& elem : PKB::getAssigns()) {
                initTable.insert(vector<string>({elem}));
            }
        } else if (declarations[selectSyn] == "variable") {
            for (const auto& elem : PKB::getVariables()) {
                initTable.insert(vector<string>({elem}));
            }
        } else if (declarations[selectSyn] == "constant") {
            for (const auto& elem : PKB::getConstants()) {
                initTable.insert(vector<string>({elem}));
            }
        } else if (declarations[selectSyn] == "prog_line") {
            for (const auto& elem : PKB::getProgLines()) {
                initTable.insert(vector<string>({elem}));
            }
        } else if (declarations[selectSyn] == "procedure") {
            for (const auto& elem : PKB::getProcedures()) {
                initTable.insert(vector<string>({elem}));
            }
        }        
        Result currentResult = Result(true, {{selectSyn, 0}}, initTable);

        // merge everything in intermediateResults
        for (auto& otherResult : intermediateResults) {
            currentResult = Result::merge(currentResult, otherResult);
        }

        // return results (projection)
        unordered_set<vector<string>> finalResults = currentResult.getResults();
        list<string> selectResults = {};
        int selectSynIdx = currentResult.getSynonyms()[selectSyn];
        for (const auto& result : results) {
            selectResults.push_back(result[selectSynIdx]);
        }
        return selectResults;
    }
}
