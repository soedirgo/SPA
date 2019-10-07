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
            Result() : synonyms({}), results({}) {}

            Result(unordered_map<string, int> syn, vector<vector<string>> res)
                : synonyms(syn),
                  results(res) {}

            static Result merge(Result r1, Result r2) {
                //TODO: implement merge
            }

            unordered_map<string, int> getSynonyms() {
                return this->synonyms;
            }

            vector<vector<string>> getResults() {
                return this->results;
            }
        private:
            unordered_map<string, int> synonyms;
            vector<vector<string>> results;
        };

        unordered_map<string, string> declarations;
        vector<pair<string, pair<string, string>>> suchThatClauses;
        vector<pair<string, pair<string, string>>> patternClauses;
        string selectSyn;
        vector<Result> intermediateResults;

        Result evalUses(string lhs, string rhs) {
            unordered_map<string, int> synonyms;
            vector<vector<string>> results;
            /**
             * Cases:
             * - ("1", _)
             * - ("1", "x")
             * - ("1", v)
             * - (s, _)
             * - (s, "x")
             * - (s, v)
             */
            if (lhs.front() == '\"' && lhs.back() == '\"') {
                if (rhs == "_") {
                    //TODO
                } else if (rhs.front() == '\"' && rhs.back() == '\"') {
                    //TODO
                } else {
                    synonyms[rhs] = 1;
                    //TODO
                }
            } else {
                synonyms[lhs] = 0;
                if (rhs == "_") {
                    //TODO
                } else if (rhs.front() == '\"' && rhs.back() == '\"') {
                    //TODO
                } else {
                    synonyms[rhs] = 1;
                    //TODO
                }
            }

            return Result(synonyms, results);
        }

        //TODO: all but Uses

        Result evalSuchThatClause(pair<string, pair<string, string>> clause) {
            string rel = clause.first;
            string lhs = clause.second.first;
            string rhs = clause.second.second;

            if (rel == "Uses") {
                return evalUses(lhs, rhs);
            } else if (rel == "Modifies") {
                return evalModifies(lhs, rhs);
            } else if (rel == "Follows") {
                return evalFollows(lhs, rhs);
            } else if (rel == "FollowsT") {
                return evalFollowsT(lhs, rhs);
            } else if (rel == "Parent") {
                return evalParent(lhs, rhs);
            } else if (rel == "ParentT") {
                return evalParentT(lhs, rhs);
            } else {
                throw "Unrecognized such-that relationship";
                return Result();
            }
        }

        Result evalPatternClause(pair<string, pair<string, string>> clause) {
            string syn = clause.first;
            string lhs = clause.second.first;
            string rhs = clause.second.second;

            unordered_map<string, int> synonyms;
            vector<vector<string>> results;
            /**
             * Cases:
             * - pattern a(_, _)
             * - pattern a(_, _"1"_)
             * - pattern a("x", _)
             * - pattern a("x", _"1"_)
             * - pattern a(v, _)
             * - pattern a(v, _"1"_)
             */
            if (lhs == "_") {
                if (rhs == "_") {
                    //TODO
                } else {
                    //TODO
                }
            } else if (lhs.front() == '\"' && lhs.back() == '\"') {
                if (rhs == "_") {
                    //TODO
                } else {
                    //TODO
                }
            } else {
                synonyms[lhs] = 0;
                if (rhs == "_") {
                    //TODO
                } else {
                    //TODO
                }
            }

            return Result(synonyms, results);
        }
    }

    list<string> evalQuery(Query q) {
        // extract info from query object
        declarations = q.getDeclarations();
        selectSyn = q.getSelectSynonym();
        suchThatClauses = q.getClauses();
        patternClauses = q.getPatternClauses();

        // for every such-that clauses, get results and store in
        // intermediateResults
        for (const auto& clause : suchThatClauses) {
            intermediateResults.push_back(evalSuchThatClause(clause));
        }

        // for every pattern clauses, get results and store in
        // intermediate results
        for (const auto& clause : patternClauses) {
            intermediateResults.push_back(evalPatternClause(clause));
        }

        // merge everything in intermediateResults
        Result finalResult = Result();
        for (const auto& result : intermediateResults) {
            finalResult = Result::merge(finalResult, result);
        }

        // return results (projection)
        vector<vector<string>> results = finalResult.getResults();
        list<string> selectResults = {};
        int selectSynIdx = finalResult.getSynonyms()[selectSyn];
        for (const auto& result : results) {
            selectResults.push_back(result[selectSynIdx]);
        }
        return selectResults;
    }
}
