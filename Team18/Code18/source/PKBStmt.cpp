#include "PKBStmt.h"
using namespace std;

unordered_set<vector<string>, VectorDoubleStringHash> PKBStmt::stmtTable;

bool PKBStmt::setStmt(STMT_NO stmtNo, STMT_TYPE type) {
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	tuple.push_back(type);
	stmtTable.emplace(tuple);
	return true;
}

STMT_LIST PKBStmt::getAllStmt() {
	STMT_LIST list;
	for (auto vectorIter : stmtTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.front());
		list.emplace(tuple);
	}
	return list;
}

STMT_LIST PKBStmt::getAllStmtByType(STMT_TYPE type) {
	STMT_LIST list;
	for (auto vectorIter : stmtTable) {
		vector<string> tuple = vector<string>();
		if (vectorIter.back() == type) {
			tuple.push_back(vectorIter.front());
			list.emplace(tuple);
		}
	}
	return list;
};

bool PKBStmt::clear() {
	stmtTable.clear();
	return true;
}