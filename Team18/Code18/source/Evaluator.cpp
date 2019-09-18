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
                    for (int stmt : PKB::getAllStmt()) {
                        statements.push_back(to_string(stmt));
                    }
                } else if (type == "read") {
                    for (auto stmt : PKB::getAllReadStmt()) {
                        statements.push_back(to_string(stmt));
                    }
                } else if (type == "print") {
                    for (auto stmt : PKB::getAllPrintStmt()) {
                        statements.push_back(to_string(stmt));
                    }
                } else if (type == "while") {
                    for (auto stmt : PKB::getAllWhileStmt()) {
                        statements.push_back(to_string(stmt));
                    }
                } else if (type == "if") {
                    for (auto stmt : PKB::getAllIfStmt()) {
                        statements.push_back(to_string(stmt));
                    }
                } else if (type == "assign") {
                    for (auto stmt : PKB::getAllAssignStmt()) {
                        statements.push_back(to_string(stmt));
                    }
                }
			} else if (PKB::getAllStmt().count(stoi(stmtRef))) { // stmtRef is a stmtNo
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

        bool evalClauses(vector<pair<string, pair<string, string>>> cls,
                         unordered_map<string, string> fil) {
			if (cls.size() == 0) {
				return true;
			}
			pair<string, pair<string, string>> clause = cls.back();
			cls.pop_back();
			string type = clause.first;
			if (type == "uses") {
				return evalUses(clause, cls, fil);
			} else if (type == "modifies") {
				return evalModifies(clause, cls, fil);
            }
            else if (type == "follows") {
                return evalFollows(clause, cls, fil);
            }
            else if (type == "follows*") {
                return evalFollowsT(clause, cls, fil);
            }
            else if (type == "parent") {
                return evalParent(clause, cls, fil);
            }
            else if (type == "parent*") {
                return evalParentT(clause, cls, fil);
            }
        }

		string formatResults(vector<string> res) {
			string result = "";
			int started = 0;
			for (string elem : res) {
				if (!started) {
					started = 1;
					result += elem;
				} else {
					result += ", ";
					result += elem;
				}
			}
			return result;
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
                pair<string, pair<string, string>> uses = { "uses", {pattern.first, pattern.second.second} };
                pair<string, pair<string, string>> modifies = { "modifies", {pattern.first, pattern.second.first} };
                cls.push_back(uses);
                cls.push_back(modifies);
            }
            unordered_map<string, string> fil;
            fil[selectSyn] = result;
            if (evalClauses(cls, fil)) results.push_back(result);
        }
        return results;
        //return formatResults(results);
    }
}
