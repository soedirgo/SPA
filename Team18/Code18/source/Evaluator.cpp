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
		bool evalClauses(vector<pair<string, pair<string, string>>> cls,
                         unordered_map<string, string> fil);

		vector<string> expandStmt(string stmtRef,
                                  unordered_map<string, string> fil) {
			vector<string> statements;
			if (fil.count(stmtRef)) { // stmtRef has been filtered before
				statements.push_back(fil[stmtRef]);
			} else if (declarations.count(stmtRef)) { // stmtRef is a synonym
                string type = declarations[stmtRef];
                if (type == "stmt") {
                    for (int stmtNum : PKB::getAllStmt()) {
                        statements.push_back(to_string(stmtNum));
                    }
                } else if (type == "read") {
                    for (auto stmtNum : PKB::getAllReadStmt()) {
                        statements.push_back(to_string(stmtNum));
                    }
                } else if (type == "print") {
                    for (auto stmtNum : PKB::getAllPrintStmt()) {
                        statements.push_back(to_string(stmtNum));
                    }
                } else if (type == "while") {
                    for (auto stmtNum : PKB::getAllWhileStmt()) {
                        statements.push_back(to_string(stmtNum));
                    }
                } else if (type == "if") {
                    for (auto stmtNum : PKB::getAllIfStmt()) {
                        statements.push_back(to_string(stmtNum));
                    }
                } else if (type == "assign") {
                    for (auto stmtNum : PKB::getAllAssignStmt()) {
                        statements.push_back(to_string(stmtNum));
                    }
                }
			} else if (PKB::getAllStmt().count(stoi(stmtRef))) { // stmtRef is a stmtNum
				statements.push_back(stmtRef);
			} else { // stmtRef is a ``_''
				for (int stmtNum : PKB::getAllStmt()) {
					statements.push_back(to_string(stmtNum));
				}
			}
			return statements;
		}

		vector<string> expandVar(string varRef,
                                 unordered_map<string, string> fil) {
			vector<string> variables;
			if (fil.count(varRef)) { // varRef has been filtered before
				variables.push_back(fil[varRef]);
			} else if (declarations.count(varRef)) { // varRef is a synonym
				for (string var : PKB::getAllVar()) {
					variables.push_back(var);
				}
			} else if (PKB::getAllVar().count(varRef)) { // varRef is an explicit name
				variables.push_back(varRef);
			} else { // varRef is a ``_''
				for (string var : PKB::getAllVar()) {
					variables.push_back(var);
				}
			}
			return variables;
		}

		vector<string> expandFactor(string factorRef,
                                    unordered_map<string, string> fil) {
			vector<string> factors;
			if (fil.count(factorRef)) { // factorRef has been filtered before
				factors.push_back(fil[factorRef]);
			} else if (declarations.count(factorRef)) { // factorRef is a synonym
                if (declarations[factorRef] == "variable") {
                    for (string var : PKB::getAllVar()) {
                        factors.push_back(var);
                    }
                } else if (declarations[factorRef] == "constant") {
                    for (string cons : PKB::getAllConstant()) {
                        factors.push_back(cons);
                    }
                }
			} else if (PKB::getAllVar().count(factorRef)
                       || PKB::getAllConstant().count(factorRef)) {
                // factorRef is an explicit name
				factors.push_back(factorRef);
			} else { // factorRef is a ``_''
				for (string var : PKB::getAllVar()) {
					factors.push_back(var);
				}
                for (string cons : PKB::getAllConstant()) {
					factors.push_back(cons);
                }
			}
			return factors;
		}

		bool evalUses(pair<string, pair<string, string>> clause,
                      vector<pair<string, pair<string, string>>> cls,
                      unordered_map<string, string> fil) {
			vector<string> expandedStmt = expandStmt(clause.second.first, fil);
			vector<string> expandedVar = expandVar(clause.second.second, fil);
			for (auto s : expandedStmt) {
				if (declarations.count(clause.second.first))
					fil[clause.second.first] = s;
				for (auto v : expandedVar) {
					if (declarations.count(clause.second.second))
						fil[clause.second.second] = v;
					if (PKB::isUsesStmtVar(stoi(s), v))
						return evalClauses(cls, fil);
				}
			}
			return false;
		}

		bool evalModifies(pair<string, pair<string, string>> clause,
                          vector<pair<string, pair<string, string>>> cls,
                          unordered_map<string, string> fil) {
			vector<string> expandedStmt = expandStmt(clause.second.first, fil);
			vector<string> expandedVar = expandVar(clause.second.second, fil);
			for (auto s : expandedStmt) {
				for (auto v : expandedVar) {
					if (PKB::isModifiesStmtVar(stoi(s), v)) return evalClauses(cls, fil);
				}
			}
			return false;
		}

        bool evalFollows(pair<string, pair<string, string>> clause,
                         vector<pair<string, pair<string, string>>> cls,
                         unordered_map<string, string> fil) {
            vector<string> expandedLhs = expandStmt(clause.second.first, fil);
            vector<string> expandedRhs = expandStmt(clause.second.second, fil);
            for (auto lhs : expandedLhs) {
                for (auto rhs : expandedRhs) {
                    if (PKB::isFollowRelationship(stoi(lhs), stoi(rhs))) return evalClauses(cls, fil);
                }
            }
            return false;
        }

        bool evalFollowsT(pair<string, pair<string, string>> clause,
                          vector<pair<string, pair<string, string>>> cls,
                          unordered_map<string, string> fil) {
            vector<string> expandedLhs = expandStmt(clause.second.first, fil);
            vector<string> expandedRhs = expandStmt(clause.second.second, fil);
            for (auto lhs : expandedLhs) {
                for (auto rhs : expandedRhs) {
                    if (PKB::isFollowStarRelationship(stoi(lhs), stoi(rhs))) return evalClauses(cls, fil);
                }
            }
            return false;
        }

        bool evalParent(pair<string, pair<string, string>> clause,
                        vector<pair<string, pair<string, string>>> cls,
                        unordered_map<string, string> fil) {
            vector<string> expandedLhs = expandStmt(clause.second.first, fil);
            vector<string> expandedRhs = expandStmt(clause.second.second, fil);
            for (auto lhs : expandedLhs) {
                for (auto rhs : expandedRhs) {
                    if (PKB::isParentRelationship(stoi(lhs), stoi(rhs))) return evalClauses(cls, fil);
                }
            }
            return false;
        }

        bool evalParentT(pair<string, pair<string, string>> clause,
                         vector<pair<string, pair<string, string>>> cls,
                         unordered_map<string, string> fil) {
            vector<string> expandedLhs = expandStmt(clause.second.first, fil);
            vector<string> expandedRhs = expandStmt(clause.second.second, fil);
            for (auto lhs : expandedLhs) {
                for (auto rhs : expandedRhs) {
                    if (PKB::isParentStarRelationship(stoi(lhs), stoi(rhs))) return evalClauses(cls, fil);
                }
            }
            return false;
        }

        bool evalPattern(pair<string, pair<string, string>> clause,
                         vector<pair<string, pair<string, string>>> cls,
                         unordered_map<string, string> fil) {
            vector<string> expandedLhs = expandVar(clause.second.first, fil);
            vector<string> expandedRhs = expandFactor(clause.second.second, fil);
            for (auto lhs : expandedLhs) {
                for (auto rhs : expandedRhs) {
                    if (PKB::isFactorAssignedToVar(lhs, rhs)) return evalClauses(cls, fil);
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
            } else if (type == "pattern") {
                return evalPattern(clause, cls, fil);
            }
        }

		// string formatResults(vector<string> res) {
		// 	string result = "";
		// 	int started = 0;
		// 	for (string elem : res) {
		// 		if (!started) {
		// 			started = 1;
		// 			result += elem;
		// 		} else {
		// 			result += ", ";
		// 			result += elem;
		// 		}
		// 	}
		// 	return result;
		// }
	}

	list<string> evalQuery(Query q) {
		declarations = q.getDeclarations();
		selectSyn = q.getSelectSynonym();
		clauses = q.getClauses();
        patterns = q.getPatternClauses();

		string selectSynType = declarations[selectSyn];
		unordered_set<string> resultCandidates;
		if (selectSynType == "stmt") {
			for (auto stmt : PKB::getAllStmt()) {
				resultCandidates.insert(to_string(stmt));
			}
		} else if (selectSynType == "read") {
			for (auto stmt : PKB::getAllReadStmt()) {
				resultCandidates.insert(to_string(stmt));
			}
		} else if (selectSynType == "print") {
            for (auto stmt : PKB::getAllPrintStmt()) {
				resultCandidates.insert(to_string(stmt));
			}
		} else if (selectSynType == "while") {
			for (auto stmt : PKB::getAllWhileStmt()) {
				resultCandidates.insert(to_string(stmt));
			}
		} else if (selectSynType == "if") {
			for (auto stmt : PKB::getAllIfStmt()) {
				resultCandidates.insert(to_string(stmt));
			}
		} else if (selectSynType == "assign") {
			for (auto stmt : PKB::getAllAssignStmt()) {
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
        for (auto result : resultCandidates) {
            vector<pair<string, pair<string, string>>> cls = clauses;
            for (auto pattern : patterns) {
                cls.push_back({ "pattern", {pattern.second.first, pattern.second.second} });
            }
            unordered_map<string, string> fil;
            fil[selectSyn] = result;
            if (evalClauses(cls, fil)) results.push_back(result);
        }
        return results;
        //return formatResults(results);
    }
}
