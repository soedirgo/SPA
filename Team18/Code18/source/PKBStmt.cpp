#include "PKBStmt.h"

using namespace std;
unordered_map<STMT_NO, STMT_TYPE> PKBStmt::stmtTable;

bool PKBStmt::setStmt(STMT_NO stmtNo, STMT_TYPE type) {
	stmtTable.emplace(stmtNo, type);
	return true;
}

STMT_LIST PKBStmt::getAllStmt() {
	unordered_set<STMT_NO> List;
	for (auto keyValue : stmtTable) {
		List.emplace(keyValue.first);
	}
	return List;
}

STMT_LIST PKBStmt::getAllStmtByType(STMT_TYPE type) {
	unordered_set<STMT_NO> List;
	for (auto keyValue : stmtTable) {
		if (keyValue.second == type) {
			List.emplace(keyValue.first);

		}
	}
	return List;
};

bool PKBStmt::clear() {
	stmtTable.clear();
	return true;
}