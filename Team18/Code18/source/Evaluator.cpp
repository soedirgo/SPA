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
		unordered_map<string, string> declarations;
		vector<pair<string, pair<string, string>>> clauses;
        vector<pair<string, pair<string, string>>> patterns;
		string selectSyn;
        // Forward declare
		bool evalClauses(vector<pair<string, pair<string, string>>> cls,
                         unordered_map<string, string> fil);

        // Returns a vector of strings corresponding to possible
        // values taken by stmtRef.
        // 
        // Example:
        // 
        // 1 -> { "1" }
        //
        // s -> { "1", "2", "3" } assuming there are 3 stmts 1, 2, and
        // 3 in the PKB
        //
        // s -> { "2" } assuming s has taken a value by earlier clauses (say,
        // by the Select clause
		unordered_set<string> enumerateStmt(string stmtRef,
                                            unordered_map<string, string> fil) {
			unordered_set<string> statements;
			if (fil.count(stmtRef)) { // stmtRef has been filtered before
				statements.insert(fil[stmtRef]);
			} else if (declarations.count(stmtRef)) { // stmtRef is a synonym
                string type = declarations[stmtRef];
                if (type == "stmt") {
                    for (const auto& stmt : PKB::getAllStmt()) {
                        statements.insert(to_string(stmt));
                    }
                } else if (type == "read") {
                    for (const auto& stmt : PKB::getAllReadStmt()) {
                        statements.insert(to_string(stmt));
                    }
                } else if (type == "print") {
                    for (const auto& stmt : PKB::getAllPrintStmt()) {
                        statements.insert(to_string(stmt));
                    }
                } else if (type == "while") {
                    for (const auto& stmt : PKB::getAllWhileStmt()) {
                        statements.insert(to_string(stmt));
                    }
                } else if (type == "if") {
                    for (const auto& stmt : PKB::getAllIfStmt()) {
                        statements.insert(to_string(stmt));
                    }
                } else if (type == "assign") {
                    for (const auto& stmt : PKB::getAllAssignStmt()) {
                        statements.insert(to_string(stmt));
                    }
                }
			} else if (stmtRef == "_") { // stmtRef is a ``_''
                for (const auto& stmt : PKB::getAllStmt()) {
                    statements.insert(to_string(stmt));
                }
            } else { // stmtRef is a stmtNum
				statements.insert(stmtRef);
			}
			return statements;
		}

		unordered_set<string> enumerateVar(string varRef,
                                           unordered_map<string, string> fil) {
			unordered_set<string> variables;
			if (fil.count(varRef)) { // varRef has been filtered before
				variables.insert(fil[varRef]);
			} else if (declarations.count(varRef)) { // varRef is a synonym
				for (const auto& var : PKB::getAllVar()) {
					variables.insert(var);
				}
			} else if (varRef.front() == '\"' && varRef.back() == '\"') { // varRef is an explicit name
				variables.insert(varRef.substr(1, varRef.size() - 2));
			} else { // varRef is a ``_''
				for (const auto& var : PKB::getAllVar()) {
					variables.insert(var);
				}
			}
			return variables;
		}

		unordered_set<string> enumerateFactor(string factorRef,
                                              unordered_map<string, string> fil) {
			unordered_set<string> factors;
			if (fil.count(factorRef)) { // factorRef has been filtered before
				factors.insert(fil[factorRef]);
			} else if (declarations.count(factorRef)) { // factorRef is a synonym
                if (declarations[factorRef] == "variable") {
                    for (const auto& var : PKB::getAllVar()) {
                        factors.insert(var);
                    }
                } else if (declarations[factorRef] == "constant") {
                    for (const auto& cons : PKB::getAllConstant()) {
                        factors.insert(cons);
                    }
                }
            } else if (factorRef.front() == '\"' && factorRef.back() == '\"') {
                // factorRef is an explicit name
                factors.insert(factorRef.substr(1, factorRef.length() - 2));
            } else { // factorRef is a ``_''
				for (const auto& var : PKB::getAllVar()) {
					factors.insert(var);
				}
                for (const auto& cons : PKB::getAllConstant()) {
					factors.insert(cons);
                }
			}
			return factors;
		}

		bool evalUses(pair<string, pair<string, string>>& clause,
                      vector<pair<string, pair<string, string>>> cls,
                      unordered_map<string, string> fil) {
			unordered_set<string> enumeratedStmt = enumerateStmt(clause.second.first, fil);
            unordered_set<string> enumeratedVar;
			for (const auto& s : enumeratedStmt) {
				if (declarations.count(clause.second.first))
					fil[clause.second.first] = s;
                enumeratedVar = enumerateVar(clause.second.second, fil);
				for (const auto& v : enumeratedVar) {
					if (declarations.count(clause.second.second))
						fil[clause.second.second] = v;
					if (PKB::isUsesStmtVar(stoi(s), v))
						return evalClauses(cls, fil);
				}
			}
			return false;
		}

		bool evalModifies(pair<string, pair<string, string>>& clause,
                          vector<pair<string, pair<string, string>>> cls,
                          unordered_map<string, string> fil) {
			unordered_set<string> enumeratedStmt = enumerateStmt(clause.second.first, fil);
			unordered_set<string> enumeratedVar;
			for (const auto& s : enumeratedStmt) {
				if (declarations.count(clause.second.first))
					fil[clause.second.first] = s;
                enumeratedVar = enumerateVar(clause.second.second, fil);
				for (const auto& v : enumeratedVar) {
					if (declarations.count(clause.second.second))
						fil[clause.second.second] = v;
					if (PKB::isModifiesStmtVar(stoi(s), v))
                        return evalClauses(cls, fil);
				}
			}
			return false;
		}

        bool evalFollows(pair<string, pair<string, string>>& clause,
                         vector<pair<string, pair<string, string>>> cls,
                         unordered_map<string, string> fil) {
            unordered_set<string> enumeratedLhs = enumerateStmt(clause.second.first, fil);
            unordered_set<string> enumeratedRhs;
            for (const auto& lhs : enumeratedLhs) {
				if (declarations.count(clause.second.first))
					fil[clause.second.first] = lhs;
                enumeratedRhs = enumerateStmt(clause.second.second, fil);
                for (const auto& rhs : enumeratedRhs) {
                    if (declarations.count(clause.second.first))
                        fil[clause.second.first] = rhs;
                    if (PKB::isFollowRelationship(stoi(lhs), stoi(rhs)))
                        return evalClauses(cls, fil);
                }
            }
            return false;
        }

        bool evalFollowsT(pair<string, pair<string, string>>& clause,
                          vector<pair<string, pair<string, string>>> cls,
                          unordered_map<string, string> fil) {
            unordered_set<string> enumeratedLhs = enumerateStmt(clause.second.first, fil);
            unordered_set<string> enumeratedRhs;
            for (const auto& lhs : enumeratedLhs) {
				if (declarations.count(clause.second.first))
					fil[clause.second.first] = lhs;
                enumeratedRhs = enumerateStmt(clause.second.second, fil);
                for (const auto& rhs : enumeratedRhs) {
                    if (declarations.count(clause.second.first))
                        fil[clause.second.first] = rhs;
                    if (PKB::isFollowStarRelationship(stoi(lhs), stoi(rhs)))
                        return evalClauses(cls, fil);
                }
            }
            return false;
        }

        bool evalParent(pair<string, pair<string, string>>& clause,
                        vector<pair<string, pair<string, string>>> cls,
                        unordered_map<string, string> fil) {
            unordered_set<string> enumeratedLhs = enumerateStmt(clause.second.first, fil);
            unordered_set<string> enumeratedRhs;
            for (const auto& lhs : enumeratedLhs) {
				if (declarations.count(clause.second.first))
					fil[clause.second.first] = lhs;
                enumeratedRhs = enumerateStmt(clause.second.second, fil);
                for (const auto& rhs : enumeratedRhs) {
                    if (declarations.count(clause.second.first))
                        fil[clause.second.first] = rhs;
                    if (PKB::isParentRelationship(stoi(lhs), stoi(rhs)))
                        return evalClauses(cls, fil);
                }
            }
            return false;
        }

        bool evalParentT(pair<string, pair<string, string>>& clause,
                         vector<pair<string, pair<string, string>>> cls,
                         unordered_map<string, string> fil) {
            unordered_set<string> enumeratedLhs = enumerateStmt(clause.second.first, fil);
            unordered_set<string> enumeratedRhs;
            for (const auto& lhs : enumeratedLhs) {
				if (declarations.count(clause.second.first))
					fil[clause.second.first] = lhs;
                enumeratedRhs = enumerateStmt(clause.second.second, fil);
                for (const auto& rhs : enumeratedRhs) {
                    if (declarations.count(clause.second.first))
                        fil[clause.second.first] = rhs;
                    if (PKB::isParentStarRelationship(stoi(lhs), stoi(rhs)))
                        return evalClauses(cls, fil);
                }
            }
            return false;
        }

        bool evalPattern(pair<string, pair<string, string>>& clause,
                         vector<pair<string, pair<string, string>>> cls,
                         unordered_map<string, string> fil) {
            // possible explicit ``a''s in pattern a(v, _)
            unordered_set<string> enumeratedStmt = enumerateStmt(clause.first, fil);
            // possible explicit ``v''s in pattern a(v, _)
            unordered_set<string> enumeratedLhs = enumerateVar(clause.second.first, fil);
            // possible explicit ``_''s in pattern a(v, _)
            unordered_set<string> enumeratedRhs = enumerateFactor(clause.second.second, fil);
            // for each a
            for (const auto& assign : enumeratedStmt) {
				if (declarations.count(clause.first))
					fil[clause.first] = assign;
                // for each of the modified variables
                for (const auto& lhs : enumeratedLhs) {
                    if (!PKB::isModifiesStmtVar(stoi(assign), lhs))
                        continue;
                    if (declarations.count(clause.second.first))
                        fil[clause.second.first] = lhs;
                    // for each possible explicit ``_'' in pattern a(v, _)
                    for (const auto& rhs : enumeratedRhs) {
                        if (declarations.count(clause.second.second))
                            fil[clause.second.second] = rhs;
                        // check if it is used in the assignment
                        if (PKB::isConstUsedInAssign(stoi(assign), rhs)
                            || PKB::isVarUsedInAssign(stoi(assign), rhs))
                            return evalClauses(cls, fil);
                        }
                }
            }
            return false;
        }

        bool evalClauses(vector<pair<string, pair<string, string>>> cls,
                         unordered_map<string, string> fil) {
			if (cls.size() == 0) {
				return true;
			}
			pair<string, pair<string, string>> clause = cls.back();
			cls.pop_back();
			string type = clause.first;
			if (type == "Uses") {
				return evalUses(clause, cls, fil);
			} else if (type == "Modifies") {
				return evalModifies(clause, cls, fil);
            } else if (type == "Follows") {
                return evalFollows(clause, cls, fil);
            } else if (type == "Follows*") {
                return evalFollowsT(clause, cls, fil);
            } else if (type == "Parent") {
                return evalParent(clause, cls, fil);
            } else if (type == "Parent*") {
                return evalParentT(clause, cls, fil);
            } else { // expected to be pattern (type == an assign synonym)
                return evalPattern(clause, cls, fil);
            }
        }
	}

  	list<string> evalQuery(Query q) {
		declarations = q.getDeclarations();
		selectSyn = q.getSelectSynonym();
		clauses = q.getClauses();
        patterns = q.getPatternClauses();

		string selectSynType = declarations[selectSyn];
		unordered_set<string> resultCandidates;
		if (selectSynType == "stmt") {
			for (const auto& stmt : PKB::getAllStmt()) {
				resultCandidates.insert(to_string(stmt));
			}
		} else if (selectSynType == "read") {
			for (const auto& stmt : PKB::getAllReadStmt()) {
				resultCandidates.insert(to_string(stmt));
			}
		} else if (selectSynType == "print") {
            for (const auto& stmt : PKB::getAllPrintStmt()) {
				resultCandidates.insert(to_string(stmt));
			}
		} else if (selectSynType == "while") {
			for (const auto& stmt : PKB::getAllWhileStmt()) {
				resultCandidates.insert(to_string(stmt));
			}
		} else if (selectSynType == "if") {
			for (const auto& stmt : PKB::getAllIfStmt()) {
				resultCandidates.insert(to_string(stmt));
			}
		} else if (selectSynType == "assign") {
			for (const auto& stmt : PKB::getAllAssignStmt()) {
				resultCandidates.insert(to_string(stmt));
			}
		} else if (selectSynType == "variable") {
			resultCandidates = PKB::getAllVar();
		} else if (selectSynType == "constant") {
			resultCandidates = PKB::getAllConstant();
		} else if (selectSynType == "procedure") {
			resultCandidates = PKB::getAllProc();
        }

        list<string> results;
        for (const auto& result : resultCandidates) {
            vector<pair<string, pair<string, string>>> cls = clauses;
            for (const auto& pattern : patterns) {
                cls.push_back({pattern.first,
                               {pattern.second.first, pattern.second.second}});
            }
            unordered_map<string, string> fil;
            fil[selectSyn] = result;
            if (evalClauses(cls, fil)) results.push_back(result);
        }
        return results;
    }
}
