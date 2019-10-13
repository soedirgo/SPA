#include <functional>
#include <set>
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
                bool resultExists = r1.hasResults() && r2.hasResults();
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
                    return Result(r1.hasResults() && r2.hasResults(),
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

                    return Result(resultExists, synonyms, results);
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
    }

    list<string> evalQuery(Query q) {
        // extract info from query object
        unordered_map<string, string> declarations = q.getDeclarations();
        string selectSyn = q.getSelectSynonym();
        vector<Clause> clauses = q.getClauses();
        vector<Result> intermediateResults;

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
        unordered_set<vector<string>> finalResults = currentResult.getResults();
        set<string> selectResultsSet;
        int selectSynIdx = currentResult.getSynonyms()[selectSyn];
        for (const auto& result : finalResults)
            selectResultsSet.insert(result[selectSynIdx]);
        list<string> selectResults;
        for (const auto& result : selectResultsSet)
            selectResults.push_back(result);
        return (selectResults);
    }
}
