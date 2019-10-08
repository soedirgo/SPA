#include "PKBModifies.h"

using namespace std;
unordered_set<vector<string>, VectorHash> PKBModifies::modifiesStmtTable;
unordered_set<vector<string>, VectorHash> PKBModifies::modifiesProcTable;

bool PKBModifies::setModifiesStmt(STMT_NO stmtNo, VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(to_string(stmtNo));
	tuple.push_back(varName);
	modifiesStmtTable.emplace(tuple);
	return true;
}

bool PKBModifies::setModifiesoc(PROC_NAME procName, VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(procName);
	tuple.push_back(varName);
	modifiesStmtTable.emplace(tuple);
	return true;
}

bool PKBModifies::isModifiesStmtRelationship(STMT_NO stmtNo, VAR_NAME varName) {

	for (auto vectorIter : modifiesStmtTable) {
		if (vectorIter.front() == to_string(stmtNo)) {
			if (vectorIter.back() == varName) {
				return true;
			}
		}
	}
	return false;
}

bool PKBModifies::clear() {
	modifiesStmtTable.clear();
	return true;
}