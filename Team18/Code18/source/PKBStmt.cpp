#include "PKBStmt.h"
using namespace std;

TABLE PKBStmt::stmtTable;

bool PKBStmt::setStmt(STMT_NO stmtNo, STMT_TYPE type) {
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	tuple.push_back(type);
	stmtTable.emplace(tuple);
	return true;
}

STMT_LIST PKBStmt::getStmts() {
	STMT_LIST list;
	for (auto vectorIter : stmtTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.front());
		list.emplace(tuple);
	}
	return list;
}

STMT_LIST PKBStmt::getStmtsByType(STMT_TYPE type) {
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

STMT_TYPE PKBStmt::getTypeByStmtNo(STMT_NO stmtNo) {
	for (auto vectorIter : stmtTable) {
		if (vectorIter.front() == stmtNo) {
			return vectorIter.back();
		}
	}
	return "";
};

bool PKBStmt::clear() {
	stmtTable.clear();
	return true;
}