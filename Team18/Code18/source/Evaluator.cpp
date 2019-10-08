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

            Result(unordered_map<string, int> syn, unordered_set<vector<string>> res)
                : synonyms(syn),
                  results(res) {}

            static Result merge(Result& r1, Result& r2) {
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

                return Result(synonyms, results);
            }

            unordered_map<string, int> getSynonyms() const {
                return this->synonyms;
            }

            unordered_set<vector<string>> getResults() const {
                return this->results;
            }
        private:
            unordered_map<string, int> synonyms;
            unordered_set<vector<string>> results;
        };

        unordered_map<string, string> declarations;
        vector<pair<string, pair<string, string>>> suchThatClauses;
        vector<pair<string, pair<string, string>>> patternClauses;
        string selectSyn;
        vector<Result> intermediateResults;

        Result evalUses(string lhs, string rhs) {
            unordered_map<string, int> synonyms;
            unordered_set<vector<string>> results;
            /**
             * Cases:
             * - Uses("1", _)
             * - Uses("1", "x")
             * - Uses("1", v)
             * - Uses(s, _)
             * - Uses(s, "x")
             * - Uses(s, v)
             */
            if (lhs.front() == '\"' && lhs.back() == '\"') {
                if (rhs == "_") {
                    //TODO
                } else if (rhs.front() == '\"' && rhs.back() == '\"') {
                    //TODO
                } else {
                    synonyms[rhs] = 0;
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

        Result evalModifies(string lhs, string rhs) {
            unordered_map<string, int> synonyms;
            unordered_set<vector<string>> results;
            /**
             * Cases:
             * - Modifies("1", _)
             * - Modifies("1", "x")
             * - Modifies("1", v)
             * - Modifies(s, _)
             * - Modifies(s, "x")
             * - Modifies(s, v)
             */
            if (lhs.front() == '\"' && lhs.back() == '\"') {
                if (rhs == "_") {
                    //TODO
                } else if (rhs.front() == '\"' && rhs.back() == '\"') {
                    //TODO
                } else {
                    synonyms[rhs] = 0;
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

        Result evalFollows(string lhs, string rhs) {
            unordered_map<string, int> synonyms;
            unordered_set<vector<string>> results;
            /**
             * Cases:
             * - Follows(_, _)
             * - Follows(_, "1")
             * - Follows(_, s)
             * - Follows("1", _)
             * - Follows("1", "1")
             * - Follows("1", s)
             * - Follows(s, _)
             * - Follows(s, "1")
             * - Follows(s, s)
             */
            if (lhs == "_") {
                if (rhs == "_") {
                    //TODO
                } else if (rhs.front() == '\"' && rhs.back() == '\"') {
                    //TODO
                } else {
                    synonyms[rhs] = 0;
                    //TODO
                }
            } else if (lhs.front() == '\"' && lhs.back() == '\"') {
                if (rhs == "_") {
                    //TODO
                } else if (rhs.front() == '\"' && rhs.back() == '\"') {
                    //TODO
                } else {
                    synonyms[rhs] = 0;
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

        Result evalFollowsT(string lhs, string rhs) {
            unordered_map<string, int> synonyms;
            unordered_set<vector<string>> results;
            /**
             * Cases:
             * - FollowsT(_, _)
             * - FollowsT(_, "1")
             * - FollowsT(_, s)
             * - FollowsT("1", _)
             * - FollowsT("1", "1")
             * - FollowsT("1", s)
             * - FollowsT(s, _)
             * - FollowsT(s, "1")
             * - FollowsT(s, s)
             */
            if (lhs == "_") {
                if (rhs == "_") {
                    //TODO
                } else if (rhs.front() == '\"' && rhs.back() == '\"') {
                    //TODO
                } else {
                    synonyms[rhs] = 0;
                    //TODO
                }
            } else if (lhs.front() == '\"' && lhs.back() == '\"') {
                if (rhs == "_") {
                    //TODO
                } else if (rhs.front() == '\"' && rhs.back() == '\"') {
                    //TODO
                } else {
                    synonyms[rhs] = 0;
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

        Result evalParent(string lhs, string rhs) {
            unordered_map<string, int> synonyms;
            unordered_set<vector<string>> results;
            /**
             * Cases:
             * - Parent(_, _)
             * - Parent(_, "1")
             * - Parent(_, s)
             * - Parent("1", _)
             * - Parent("1", "1")
             * - Parent("1", s)
             * - Parent(s, _)
             * - Parent(s, "1")
             * - Parent(s, s)
             */
            if (lhs == "_") {
                if (rhs == "_") {
                    //TODO
                } else if (rhs.front() == '\"' && rhs.back() == '\"') {
                    //TODO
                } else {
                    synonyms[rhs] = 0;
                    //TODO
                }
            } else if (lhs.front() == '\"' && lhs.back() == '\"') {
                if (rhs == "_") {
                    //TODO
                } else if (rhs.front() == '\"' && rhs.back() == '\"') {
                    //TODO
                } else {
                    synonyms[rhs] = 0;
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

        Result evalParentT(string lhs, string rhs) {
            unordered_map<string, int> synonyms;
            unordered_set<vector<string>> results;
            /**
             * Cases:
             * - ParentT(_, _)
             * - ParentT(_, "1")
             * - ParentT(_, s)
             * - ParentT("1", _)
             * - ParentT("1", "1")
             * - ParentT("1", s)
             * - ParentT(s, _)
             * - ParentT(s, "1")
             * - ParentT(s, s)
             */
            if (lhs == "_") {
                if (rhs == "_") {
                    //TODO
                } else if (rhs.front() == '\"' && rhs.back() == '\"') {
                    //TODO
                } else {
                    synonyms[rhs] = 0;
                    //TODO
                }
            } else if (lhs.front() == '\"' && lhs.back() == '\"') {
                if (rhs == "_") {
                    //TODO
                } else if (rhs.front() == '\"' && rhs.back() == '\"') {
                    //TODO
                } else {
                    synonyms[rhs] = 0;
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
