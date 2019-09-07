#include <string>
#include <vector>
#include <utility>
#include <unordered_set>
#include <unordered_map>
#include "Entity.h"
#include "Evaluator.h"
#include "PKB.h"
#include "Query.h"
#include "Clause.h"
using namespace std;

// string Evaluator::evalQuery(Query q) {
//     Evaluator::declarations = q.getDeclarations();
//     clauses = q.getClause();
// }

namespace Evaluator {
    namespace {
        unordered_map<string, string> declarations;
        vector<Clause> clauses;
        string selectSyn;
        unordered_map<string, unordered_set<string> > currentResults;
        unordered_set<string> statements = PKB::getStatements();
        unordered_set<string> variables = PKB::getVariables();

        vector<string> expandStmt(string stmtRef) {
            vector<string> res;
            if (currentResults.count(stmtRef)) {
                for (auto iter = currentResults[stmtRef].begin(); iter != currentResults[stmtRef].end(); iter++) {
                    res.push_back(*iter);
                }
            } else if (declarations.count(stmtRef)) {
                for (auto iter = statements.begin(); iter != statements.end(); iter++) {
                    res.push_back(*iter);
                }
            } else if (statements.contains(stmtRef)) {
                res.push_back(stmtRef);
                return res;
            } else {
                for (auto iter = statements.begin(); iter != statements.end(); iter++) {
                    res.push_back(*iter);
                }
            }
            return res;
        }

        vector<string> expandVar(string varRef) {
            vector<string> res;
            if (currentResults.count(varRef)) {
                for (auto iter = currentResults[varRef].begin(); iter != currentResults[varRef].end(); iter++) {
                    res.push_back(*iter);
                }
            } else if (declarations.count(varRef)) {
                for (auto iter = variables.begin(); iter != variables.end(); iter++) {
                    res.push_back(*iter);
                }
            } else if (variables.contains(varRef)) {
                res.push_back(varRef);
                return res;
            } else {
                for (auto iter = variables.begin(); iter != variables.end(); iter++) {
                    res.push_back(*iter);
                }
            }
            return res;
        }

        // bool isStmtNum(string arg) {
        //     return statements.counts(arg);
        // }

        // bool isStmtSyn(string arg) {
        //     return declarations.counts(arg);
        // }

        // bool isVarName(string arg) {
        //     return variables.counts(arg);
        // }

        // bool isVarSyn(string arg) {
        //     return declarations.counts(arg);
        // }
        
        bool evalUses(string lhs, string rhs) {
            vector<string> expandedStmt = expandStmt(lhs);
            vector<string> expandedVar = expandVar(rhs);
            for (auto s : expandedStmt) {
                for (auto v : expandedVar) {
                    if (PKB::isUses(s, v)) return evalClauses();
                }
            }
            return false;
        }

        bool evalModifies(string lhs, string rhs) {
            vector<string> expandedStmt = expandStmt(lhs);
            vector<string> expandedVar = expandVar(rhs);
            for (auto s : expandedStmt) {
                for (auto v : expandedVar) {
                    if (PKB::isModifies(s, v)) return evalClauses();
                }
            }
            return false;
        }

        bool evalClauses() {
            if (clauses.size() == 0) {
                return true;
            }
            Clause clause = clauses.back();
            clauses.pop_back();
            string type = clause.getType();
            if (type == "uses") {
                return evalUses(clause.getLhs(), clause.getRhs());
            } else {
                return evalModifies(clause.getLhs(), clause.getRhs());
            }
        }

        string formatResults(vector<string> res) {
            string result = "";
            int started = 0;
            for (string elem : res) {
                if (!started) {
                    started = 1;
                    result += elem;
                }
                result += ", ";
                result += elem;
            }
        }
    }

    string evalQuery(Query q) {
        Evaluator::declarations = q.getDeclarations();
        Evaluator::clauses = q.getClauses();
        Evaluator::selectSyn = q.getSelectSynonym();

        string selectSynType = declarations[selectSyn];
        vector<string> possibleResults;
        if (selectSynType == "stmt") {
            possibleResults = statements;
        } else {
            possibleResults = variables;
        }

        vector<string> results;
        for (auto res : possibleResults) {
            if (evalClauses()) results.push_back(res);
        }
        
        return formatResults(results);
    }
}
