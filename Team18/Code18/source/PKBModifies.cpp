#include "PKBModifies.h"

using namespace std;
unordered_set<vector<string>, VectorHash> PKBModifies::varModifiesByStmtTable;

bool PKBModifies::setModifiesVarByStmt(STMT_NO stmtNo, VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(to_string(stmtNo));
	tuple.push_back(varName);
	varModifiesByStmtTable.emplace(tuple);
	return true;
}

bool PKBModifies::isModifiesStmtVar(STMT_NO stmtNo, VAR_NAME varName) {

	for (auto vectorIter : varModifiesByStmtTable) {
		if (vectorIter.front() == to_string(stmtNo)) {
			if (vectorIter.back() == varName) {
				return true;
			}
		}
	}
	return false;
}

bool PKBModifies::clear() {
	varModifiesByStmtTable.clear();
	return true;
}