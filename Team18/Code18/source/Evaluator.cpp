#include <functional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include "Clause.h"
#include "Entity.h"
#include "Evaluator.h"
#include "PKB.h"
#include "Query.h"
using namespace std;

namespace Evaluator {
    namespace {
        class Result {
        public:
            Result() {}

            Result(bool resEx,
                   unordered_map<string, int> syn,
                   unordered_set<vector<string>> res)
                : resultExists(resEx),
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

        Result evalSuchThat(Clause clause) {
            vector<string> fields = clause.getFields();
            string& rel = fields[0];
            string& lhs = fields[1];
            string& rhs = fields[2];
            if (rel == "Uses" || rel == "Modifies") {
                if (lhs.front() == '\"' && lhs.back() == '\"') {
                    rel += isdigit(lhs[1]) ? "P" : "S";
                } else {
                    rel += declarations[lhs] == "procedure" ? "P" : "S";
                }
            }

            unordered_map<string, function<bool(string, string)>> boolApiMap =
                {{"UsesS", PKB::isUsesS},
                 {"UsesP", PKB::isUsesP},
                 {"ModifiesS", PKB::isModifiesS},
                 {"ModifiesP", PKB::isModifiesP},
                 {"Calls", PKB::isCalls},
                 {"Follows", PKB::isFollows},
                 {"Follows*", PKB::isFollowsT},
                 {"Parent", PKB::isParent},
                 {"Parent*", PKB::isParentT},
                 {"Next", PKB::isNext},
                 {"Next*", PKB::isNextT}};

            unordered_map<string,
                          function<unordered_set<vector<string>>
                                   (string, string)>> tableApiMap =
                {{"UsesS", PKB::getUsesS},
                 {"UsesP", PKB::getUsesP},
                 {"ModifiesS", PKB::getModifiesS},
                 {"ModifiesP", PKB::getModifiesP},
                 {"Calls", PKB::getCalls},
                 {"Follows", PKB::getFollows},
                 {"Follows*", PKB::getFollowsT},
                 {"Parent", PKB::getParent},
                 {"Parent*", PKB::getParentT},
                 {"Next", PKB::getNext},
                 {"Next*", PKB::getNextT}};

            unordered_map<string,
                          function<unordered_set<vector<string>>
                                   (string)>> tableIdentApiMap =
                {{"Calls", PKB::getCallsIdent},
                 {"Follows", PKB::getFollowsIdent},
                 {"Follows*", PKB::getFollowsTIdent},
                 {"Parent", PKB::getParentIdent},
                 {"Parent*", PKB::getParentTIdent},
                 {"Next", PKB::getNextIdent},
                 {"Next*", PKB::getNextTIdent}};

            bool resultExists;
            unordered_map<string, int> synonyms;
            unordered_set<vector<string>> results;
            /**
             * Cases:
             * - (_, _)
             * - (_, "1")
             * - (_, s)
             * - ("1", _)
             * - ("1", "1")
             * - ("1", s)
             * - (s, _)
             * - (s, "1")
             * - (s, s)
             */
            if (lhs == "_"
                || (lhs.front() == '\"' && lhs.back() == '\"')) {
                if (rhs == "_"
                    || (rhs.front() == '\"' && rhs.back() == '\"')) {
                    resultExists = boolApiMap[rel](lhs, rhs);
                } else {
                    synonyms[rhs] = 0;
                    results = tableApiMap[rel](lhs, declarations[rhs]);
                    resultExists = results.size();
                }
            } else {
                synonyms[lhs] = 0;
                if (rhs == "_"
                    || rhs.front() == '\"' && rhs.back() == '\"') {
                    results = tableApiMap[rel](declarations[lhs], rhs);
                } else if (lhs == rhs) {
                    results = tableIdentApiMap[rel](declarations[lhs]);
                } else {
                    synonyms[rhs] = 1;
                    results = tableApiMap[rel](declarations[lhs],
                                               declarations[rhs]);
                }
                resultExists = results.size();
            }

            return Result(resultExists, synonyms, results);
        }

        Result evalPattern(Clause clause) {
            vector<string> fields = clause.getFields();
            string& syn = fields[0];
            string& lhs = fields[1];
            string& rhs = fields[2];

            bool resultExists;
            unordered_map<string, int> synonyms;
            unordered_set<vector<string>> results;
            /**
             * Cases:
             * - pattern a(_, _)
             * - pattern a(_, _"1"_)
             * - pattern a("x", _)
             * - pattern a("x", _"1"_)
             * - pattern a(v, _)
             * - pattern a(v, _"1"_)
             */
            synonyms[syn] = 0;
            if (lhs == "_"
                || (lhs.front() == '\"' && lhs.back() == '\"')) {
                results = PKB::getPattern(declarations[syn], lhs, rhs);
            } else {
                synonyms[lhs] = 1;
                results = PKB::getPattern(declarations[syn],
                                          declarations[lhs],
                                          rhs);
            }
            resultExists = results.size();

            return Result(resultExists, synonyms, results);
        }
    }

    list<string> evalQuery(Query q) {
        // extract info from query object
        declarations = q.getDeclarations();
        selectSyn = q.getSelectSynonym();
        clauses = q.getClauses();

        // for every clause, get results and store in
        // intermediate results
        for (const auto& clause : clauses) {
            clause.getType() == "pattern"
                ? intermediateResults.push_back(evalPattern(clause))
                : intermediateResults.push_back(evalSuchThat(clause));
        }

        // select clause as the starting intermediate result
        vector<string> initResults;
        unordered_set<vector<string>> initTable;
        if (declarations[selectSyn] == "stmt") {
            for (const auto& elem : PKB::getStmt()) {
                initTable.insert(vector<string>(elem));
            }
        } else if (declarations[selectSyn] == "read") {
            for (const auto& elem : PKB::getRead()) {
                initTable.insert(vector<string>(elem));
            }
        } else if (declarations[selectSyn] == "print") {
            for (const auto& elem : PKB::getPrint()) {
                initTable.insert(vector<string>(elem));
            }
        } else if (declarations[selectSyn] == "call") {
            for (const auto& elem : PKB::getCall()) {
                initTable.insert(vector<string>(elem));
            }
        } else if (declarations[selectSyn] == "while") {
            for (const auto& elem : PKB::getWhile()) {
                initTable.insert(vector<string>(elem));
            }
        } else if (declarations[selectSyn] == "if") {
            for (const auto& elem : PKB::getIf()) {
                initTable.insert(vector<string>(elem));
            }
        } else if (declarations[selectSyn] == "assign") {
            for (const auto& elem : PKB::getAssign()) {
                initTable.insert(vector<string>(elem));
            }
        } else if (declarations[selectSyn] == "variable") {
            for (const auto& elem : PKB::getVariable()) {
                initTable.insert(vector<string>(elem));
            }
        } else if (declarations[selectSyn] == "constant") {
            for (const auto& elem : PKB::getConstant()) {
                initTable.insert(vector<string>(elem));
            }
        } else if (declarations[selectSyn] == "prog_line") {
            for (const auto& elem : PKB::getProgLine()) {
                initTable.insert(vector<string>(elem));
            }
        } else if (declarations[selectSyn] == "procedure") {
            for (const auto& elem : PKB::getProcedure()) {
                initTable.insert(vector<string>(elem));
            }
        }        
        Result finalResult = Result(true, {{selectSyn, 0}}, initTable);

        // merge everything in intermediateResults
        for (auto& result : intermediateResults) {
            finalResult = Result::merge(finalResult, result);
        }

        // return results (projection)
        unordered_set<vector<string>> results = finalResult.getResults();
        list<string> selectResults = {};
        int selectSynIdx = finalResult.getSynonyms()[selectSyn];
        for (const auto& result : results) {
            selectResults.push_back(result[selectSynIdx]);
        }
        return selectResults;
    }
}
