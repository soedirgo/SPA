#include "PKBUses.h"

using namespace std;
unordered_set<vector<string>, VectorHash> PKBUses::varUsesByStmtTable;

bool PKBUses::setUsesVarByStmt(STMT_NO stmtNo, VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(to_string(stmtNo));
	tuple.push_back(varName);
	varUsesByStmtTable.emplace(tuple);
	return true;
}

bool PKBUses::isUsesStmtVar(STMT_NO stmtNo, VAR_NAME varName) {

	for (auto vectorIter : varUsesByStmtTable) {
		if (vectorIter.front() == to_string(stmtNo)) {
			if (vectorIter.back() == varName) {
				return true;
			}
		}
	}
	return false;
}


bool PKBUses::clear() {
	varUsesByStmtTable.clear();
	return true;
}