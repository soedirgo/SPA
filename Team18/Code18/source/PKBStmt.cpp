#include "PKBStmt.h"
using namespace std;

TABLE PKBStmt::stmtTable;
//Set StmtNo and its type into PKB stmtTable
bool PKBStmt::setStmt(STMT_NO stmtNo, STMT_TYPE type) {
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	tuple.push_back(type);
	stmtTable.emplace(tuple);
	return true;
}
//Get all Stmt from stmtTable
STMT_LIST PKBStmt::getStmts() {
	STMT_LIST list;
	for (auto vectorIter : stmtTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.front());
		list.emplace(tuple);
	}
	return list;
}
//Get all Stmt of that given type from stmtTable
STMT_LIST PKBStmt::getStmtsByType(STMT_TYPE type) {
	STMT_LIST list;
	for (auto vectorIter : stmtTable) {
		if (vectorIter.back() == type) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter.front());
			list.emplace(tuple);
		}
	}
	return list;
};
//Get stmt type from stmtTable given the stmtNo 
STMT_TYPE PKBStmt::getTypeByStmtNo(STMT_NO stmtNo) {
	for (auto vectorIter : stmtTable) {
		if (vectorIter.front() == stmtNo) {
			return vectorIter.back();
		}
	}
	return "";
};

//Clear the PKB stmtTable
bool PKBStmt::clear() {
	stmtTable.clear();
	return true;
}