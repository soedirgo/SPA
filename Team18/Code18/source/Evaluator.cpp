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

        // Result evalUsesS(string lhs, string rhs) {
        //     bool resultExists;
        //     unordered_map<string, int> synonyms = {};
        //     unordered_set<vector<string>> results = {};
        //     /**
        //      * Cases:
        //      * - Uses("1", _)
        //      * - Uses("1", "x")
        //      * - Uses("1", v)
        //      * - Uses(s, _)
        //      * - Uses(s, "x")
        //      * - Uses(s, v)
        //      */
        //     if (lhs.front() == '\"' && lhs.back() == '\"') {
        //         if (rhs == "_"
        //             || rhs.front() == '\"' && rhs.back() == '\"') {
        //             resultExists = PKB::isUsesS(lhs, rhs);
        //         } else {
        //             synonyms[rhs] = 0;
        //             results = PKB::getUsesS(lhs, declarations[rhs]);
        //             resultExists = results.size();
        //         }
        //     } else {
        //         synonyms[lhs] = 0;
        //         if (rhs == "_"
        //             || rhs.front() == '\"' && rhs.back() == '\"') {
        //             results = PKB::getUsesS(declarations[lhs], rhs);
        //         } else {
        //             synonyms[rhs] = 0;
        //             results = PKB::getUsesS(declarations[lhs], declarations[rhs]);
        //         }
        //         resultExists = results.size();
        //     }

        //     return Result(resultExists, synonyms, results);
        // }

        // Result evalUsesP(string lhs, string rhs) {
        //     bool resultExists;
        //     unordered_map<string, int> synonyms;
        //     unordered_set<vector<string>> results;
        //     /**
        //      * Cases:
        //      * - UsesP("main", _)
        //      * - UsesP("main", "x")
        //      * - UsesP("main", v)
        //      * - UsesP(p, _)
        //      * - UsesP(p, "x")
        //      * - UsesP(p, v)
        //      */
        //     if (lhs.front() == '\"' && lhs.back() == '\"') {
        //         if (rhs == "_"
        //             || rhs.front() == '\"' && rhs.back() == '\"') {
        //             resultExists = PKB::isUsesP(lhs, rhs);
        //         } else {
        //             synonyms[rhs] = 0;
        //             results = PKB::getUsesP(lhs, declarations[rhs]);
        //             resultExists = results.size();
        //         }
        //     } else {
        //         synonyms[lhs] = 0;
        //         if (rhs == "_"
        //             || rhs.front() == '\"' && rhs.back() == '\"') {
        //             results = PKB::getUsesP(declarations[lhs], rhs);
        //         } else {
        //             synonyms[rhs] = 0;
        //             results = PKB::getUsesP(declarations[lhs], declarations[rhs]);
        //         }
        //         resultExists = results.size();
        //     }

        //     return Result(resultExists, synonyms, results);
        // }

        // Result evalModifiesS(string lhs, string rhs) {
        //     bool resultExists;
        //     unordered_map<string, int> synonyms;
        //     unordered_set<vector<string>> results;
        //     /**
        //      * Cases:
        //      * - Modifies("1", _)
        //      * - Modifies("1", "x")
        //      * - Modifies("1", v)
        //      * - Modifies(s, _)
        //      * - Modifies(s, "x")
        //      * - Modifies(s, v)
        //      */
        //     if (lhs.front() == '\"' && lhs.back() == '\"') {
        //         if (rhs == "_"
        //             || rhs.front() == '\"' && rhs.back() == '\"') {
        //             resultExists = PKB::isModifiesS(lhs, rhs);
        //         } else {
        //             synonyms[rhs] = 0;
        //             results = PKB::getModifiesS(lhs, declarations[rhs]);
        //             resultExists = results.size();
        //         }
        //     } else {
        //         synonyms[lhs] = 0;
        //         if (rhs == "_"
        //             || rhs.front() == '\"' && rhs.back() == '\"') {
        //             results = PKB::getModifiesS(declarations[lhs], rhs);
        //         } else {
        //             synonyms[rhs] = 0;
        //             results = PKB::getModifiesS(declarations[lhs], declarations[rhs]);
        //         }
        //         resultExists = results.size();
        //     }

        //     return Result(resultExists, synonyms, results);
        // }

        // Result evalModifiesP(string lhs, string rhs) {
        //     bool resultExists;
        //     unordered_map<string, int> synonyms;
        //     unordered_set<vector<string>> results;
        //     /**
        //      * Cases:
        //      * - ModifiesP("1", _)
        //      * - ModifiesP("1", "x")
        //      * - ModifiesP("1", v)
        //      * - ModifiesP(p, _)
        //      * - ModifiesP(p, "x")
        //      * - ModifiesP(p, v)
        //      */
        //     if (lhs.front() == '\"' && lhs.back() == '\"') {
        //         if (rhs == "_"
        //             || rhs.front() == '\"' && rhs.back() == '\"') {
        //             resultExists = PKB::isModifiesP(lhs, rhs);
        //         } else {
        //             synonyms[rhs] = 0;
        //             results = PKB::getModifiesP(lhs, declarations[rhs]);
        //             resultExists = results.size();
        //         }
        //     } else {
        //         synonyms[lhs] = 0;
        //         if (rhs == "_"
        //             || rhs.front() == '\"' && rhs.back() == '\"') {
        //             results = PKB::getModifiesP(declarations[lhs], rhs);
        //         } else {
        //             synonyms[rhs] = 0;
        //             results = PKB::getModifiesP(declarations[lhs], declarations[rhs]);
        //         }
        //         resultExists = results.size();
        //     }

        //     return Result(resultExists, synonyms, results);
        // }

        // Result evalCalls(string lhs, string rhs) {
        //     bool resultExists;
        //     unordered_map<string, int> synonyms;
        //     unordered_set<vector<string>> results;
        //     /**
        //      * Cases:
        //      * - Calls(_, _)
        //      * - Calls(_, "main")
        //      * - Calls(_, p)
        //      * - Calls("main", _)
        //      * - Calls("main", "main")
        //      * - Calls("main", p)
        //      * - Calls(p, _)
        //      * - Calls(p, "main")
        //      * - Calls(p, p)
        //      */
        //     if (lhs == "_"
        //         || lhs.front() == '\"' && lhs.back() == '\"') {
        //         if (rhs == "_"
        //             || rhs.front() == '\"' && rhs.back() == '\"') {
        //             resultExists = PKB::isCalls(lhs, rhs);
        //         } else {
        //             synonyms[rhs] = 0;
        //             results = PKB::getCalls(lhs, declarations[rhs]);
        //             resultExists = results.size();
        //         }
        //     } else {
        //         synonyms[lhs] = 0;
        //         if (rhs == "_"
        //             || rhs.front() == '\"' && rhs.back() == '\"') {
        //             results = PKB::getCalls(declarations[lhs], rhs);
        //         } else {
        //             synonyms[rhs] = 0;
        //             results = PKB::getCalls(declarations[lhs], declarations[rhs]);
        //         }
        //         resultExists = results.size();
        //     }

        //     return Result(resultExists, synonyms, results);
        // }

        // Result evalCallsT(string lhs, string rhs) {
        //     bool resultExists;
        //     unordered_map<string, int> synonyms;
        //     unordered_set<vector<string>> results;
        //     /**
        //      * Cases:
        //      * - CallsT(_, _)
        //      * - CallsT(_, "main")
        //      * - CallsT(_, p)
        //      * - CallsT("main", _)
        //      * - CallsT("main", "main")
        //      * - CallsT("main", p)
        //      * - CallsT(p, _)
        //      * - CallsT(p, "main")
        //      * - CallsT(p, p)
        //      */
        //     if (lhs.front() == '\"' && lhs.back() == '\"') {
        //         if (rhs == "_"
        //             || rhs.front() == '\"' && rhs.back() == '\"') {
        //             resultExists = PKB::isUsesS(lhs, rhs);
        //         } else {
        //             synonyms[rhs] = 0;
        //             results = PKB::getUsesS(lhs, declarations[rhs]);
        //             resultExists = results.size();
        //         }
        //     } else {
        //         synonyms[lhs] = 0;
        //         if (rhs == "_"
        //             || rhs.front() == '\"' && rhs.back() == '\"') {
        //             results = PKB::getUsesS(declarations[lhs], rhs);
        //         } else {
        //             synonyms[rhs] = 0;
        //             results = PKB::getUsesS(declarations[lhs], declarations[rhs]);
        //         }
        //         resultExists = results.size();
        //     }

        //     return Result(resultExists, synonyms, results);
        // }

        // Result evalFollows(string lhs, string rhs) {
        //     bool resultExists;
        //     unordered_map<string, int> synonyms;
        //     unordered_set<vector<string>> results;
        //     /**
        //      * Cases:
        //      * - Follows(_, _)
        //      * - Follows(_, "1")
        //      * - Follows(_, s)
        //      * - Follows("1", _)
        //      * - Follows("1", "1")
        //      * - Follows("1", s)
        //      * - Follows(s, _)
        //      * - Follows(s, "1")
        //      * - Follows(s, s)
        //      */
        //     if (lhs.front() == '\"' && lhs.back() == '\"') {
        //         if (rhs == "_"
        //             || rhs.front() == '\"' && rhs.back() == '\"') {
        //             resultExists = PKB::isUsesS(lhs, rhs);
        //         } else {
        //             synonyms[rhs] = 0;
        //             results = PKB::getUsesS(lhs, declarations[rhs]);
        //             resultExists = results.size();
        //         }
        //     } else {
        //         synonyms[lhs] = 0;
        //         if (rhs == "_"
        //             || rhs.front() == '\"' && rhs.back() == '\"') {
        //             results = PKB::getUsesS(declarations[lhs], rhs);
        //         } else {
        //             synonyms[rhs] = 0;
        //             results = PKB::getUsesS(declarations[lhs], declarations[rhs]);
        //         }
        //         resultExists = results.size();
        //     }

        //     return Result(resultExists, synonyms, results);
        // }

        // Result evalFollowsT(string lhs, string rhs) {
        //     bool resultExists;
        //     unordered_map<string, int> synonyms;
        //     unordered_set<vector<string>> results;
        //     /**
        //      * Cases:
        //      * - FollowsT(_, _)
        //      * - FollowsT(_, "1")
        //      * - FollowsT(_, s)
        //      * - FollowsT("1", _)
        //      * - FollowsT("1", "1")
        //      * - FollowsT("1", s)
        //      * - FollowsT(s, _)
        //      * - FollowsT(s, "1")
        //      * - FollowsT(s, s)
        //      */
        //     if (lhs.front() == '\"' && lhs.back() == '\"') {
        //         if (rhs == "_"
        //             || rhs.front() == '\"' && rhs.back() == '\"') {
        //             resultExists = PKB::isUsesS(lhs, rhs);
        //         } else {
        //             synonyms[rhs] = 0;
        //             results = PKB::getUsesS(lhs, declarations[rhs]);
        //             resultExists = results.size();
        //         }
        //     } else {
        //         synonyms[lhs] = 0;
        //         if (rhs == "_"
        //             || rhs.front() == '\"' && rhs.back() == '\"') {
        //             results = PKB::getUsesS(declarations[lhs], rhs);
        //         } else {
        //             synonyms[rhs] = 0;
        //             results = PKB::getUsesS(declarations[lhs], declarations[rhs]);
        //         }
        //         resultExists = results.size();
        //     }

        //     return Result(resultExists, synonyms, results);
        // }

        // Result evalParent(string lhs, string rhs) {
        //     bool resultExists;
        //     unordered_map<string, int> synonyms;
        //     unordered_set<vector<string>> results;
        //     /**
        //      * Cases:
        //      * - Parent(_, _)
        //      * - Parent(_, "1")
        //      * - Parent(_, s)
        //      * - Parent("1", _)
        //      * - Parent("1", "1")
        //      * - Parent("1", s)
        //      * - Parent(s, _)
        //      * - Parent(s, "1")
        //      * - Parent(s, s)
        //      */
        //     if (lhs.front() == '\"' && lhs.back() == '\"') {
        //         if (rhs == "_"
        //             || rhs.front() == '\"' && rhs.back() == '\"') {
        //             resultExists = PKB::isUsesS(lhs, rhs);
        //         } else {
        //             synonyms[rhs] = 0;
        //             results = PKB::getUsesS(lhs, declarations[rhs]);
        //             resultExists = results.size();
        //         }
        //     } else {
        //         synonyms[lhs] = 0;
        //         if (rhs == "_"
        //             || rhs.front() == '\"' && rhs.back() == '\"') {
        //             results = PKB::getUsesS(declarations[lhs], rhs);
        //         } else {
        //             synonyms[rhs] = 0;
        //             results = PKB::getUsesS(declarations[lhs], declarations[rhs]);
        //         }
        //         resultExists = results.size();
        //     }

        //     return Result(resultExists, synonyms, results);
        // }

        // Result evalParentT(string lhs, string rhs) {
        //     bool resultExists;
        //     unordered_map<string, int> synonyms;
        //     unordered_set<vector<string>> results;
        //     /**
        //      * Cases:
        //      * - ParentT(_, _)
        //      * - ParentT(_, "1")
        //      * - ParentT(_, s)
        //      * - ParentT("1", _)
        //      * - ParentT("1", "1")
        //      * - ParentT("1", s)
        //      * - ParentT(s, _)
        //      * - ParentT(s, "1")
        //      * - ParentT(s, s)
        //      */
        //     if (lhs.front() == '\"' && lhs.back() == '\"') {
        //         if (rhs == "_"
        //             || rhs.front() == '\"' && rhs.back() == '\"') {
        //             resultExists = PKB::isUsesS(lhs, rhs);
        //         } else {
        //             synonyms[rhs] = 0;
        //             results = PKB::getUsesS(lhs, declarations[rhs]);
        //             resultExists = results.size();
        //         }
        //     } else {
        //         synonyms[lhs] = 0;
        //         if (rhs == "_"
        //             || rhs.front() == '\"' && rhs.back() == '\"') {
        //             results = PKB::getUsesS(declarations[lhs], rhs);
        //         } else {
        //             synonyms[rhs] = 0;
        //             results = PKB::getUsesS(declarations[lhs], declarations[rhs]);
        //         }
        //         resultExists = results.size();
        //     }

        //     return Result(resultExists, synonyms, results);
        // }

        // Result evalNext(string lhs, string rhs) {
        //     bool resultExists;
        //     unordered_map<string, int> synonyms;
        //     unordered_set<vector<string>> results;
        //     /**
        //      * Cases:
        //      * - Next(_, _)
        //      * - Next(_, "1")
        //      * - Next(_, s)
        //      * - Next("1", _)
        //      * - Next("1", "1")
        //      * - Next("1", s)
        //      * - Next(s, _)
        //      * - Next(s, "1")
        //      * - Next(s, s)
        //      */
        //     if (lhs.front() == '\"' && lhs.back() == '\"') {
        //         if (rhs == "_"
        //             || rhs.front() == '\"' && rhs.back() == '\"') {
        //             resultExists = PKB::isUsesS(lhs, rhs);
        //         } else {
        //             synonyms[rhs] = 0;
        //             results = PKB::getUsesS(lhs, declarations[rhs]);
        //             resultExists = results.size();
        //         }
        //     } else {
        //         synonyms[lhs] = 0;
        //         if (rhs == "_"
        //             || rhs.front() == '\"' && rhs.back() == '\"') {
        //             results = PKB::getUsesS(declarations[lhs], rhs);
        //         } else {
        //             synonyms[rhs] = 0;
        //             results = PKB::getUsesS(declarations[lhs], declarations[rhs]);
        //         }
        //         resultExists = results.size();
        //     }

        //     return Result(resultExists, synonyms, results);
        // }

        // Result evalNextT(string lhs, string rhs) {
        //     bool resultExists;
        //     unordered_map<string, int> synonyms;
        //     unordered_set<vector<string>> results;
        //     /**
        //      * Cases:
        //      * - NextT(_, _)
        //      * - NextT(_, "1")
        //      * - NextT(_, s)
        //      * - NextT("1", _)
        //      * - NextT("1", "1")
        //      * - NextT("1", s)
        //      * - NextT(s, _)
        //      * - NextT(s, "1")
        //      * - NextT(s, s)
        //      */
        //     if (lhs.front() == '\"' && lhs.back() == '\"') {
        //         if (rhs == "_"
        //             || rhs.front() == '\"' && rhs.back() == '\"') {
        //             resultExists = PKB::isUsesS(lhs, rhs);
        //         } else {
        //             synonyms[rhs] = 0;
        //             results = PKB::getUsesS(lhs, declarations[rhs]);
        //             resultExists = results.size();
        //         }
        //     } else {
        //         synonyms[lhs] = 0;
        //         if (rhs == "_"
        //             || rhs.front() == '\"' && rhs.back() == '\"') {
        //             results = PKB::getUsesS(declarations[lhs], rhs);
        //         } else {
        //             synonyms[rhs] = 0;
        //             results = PKB::getUsesS(declarations[lhs], declarations[rhs]);
        //         }
        //         resultExists = results.size();
        //     }

        //     return Result(resultExists, synonyms, results);
        // }

        Result evalSuchThatClause(pair<string, pair<string, string>> clause) {
            string rel = clause.first;
            string lhs = clause.second.first;
            string rhs = clause.second.second;
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
                                   (string, string)>> tableIdentApiMap =
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
