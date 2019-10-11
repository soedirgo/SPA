#include "PKBParent.h"
#include "PKBStmt.h"
#include <system_error>

using namespace std;

TABLE PKBParent::parentTable;
TABLE PKBParent::parentStarTable;

bool PKBParent::setParent(STMT_NO parent, STMT_NO child) {
	vector<string> tuple = vector<string>();
	tuple.push_back(parent);
	tuple.push_back(child);
	parentTable.emplace(tuple);
	return true;
}

bool PKBParent::setParentStar(STMT_NO parent, STMT_NO child) {
	vector<string> tuple = vector<string>();
	tuple.push_back(parent);
	tuple.push_back(child);
	parentStarTable.emplace(tuple);
	return true;
}

STMT_LIST PKBParent::getChild(STMT_NO parent) {
	STMT_LIST list;
	for (auto vectorIter : parentTable) {
		vector<string> tuple = vector<string>();
		if (vectorIter.front() == parent) {
			tuple.push_back(vectorIter.back());
			list.emplace(tuple);
		}
	}
	return list;
}

STMT_NO PKBParent::getParent(STMT_NO child) {
	for (auto vectorIter : parentTable) {
		vector<string> tuple = vector<string>();
		if (vectorIter.back() == child) {
			return vectorIter.front();
		}
	}
	return "";
}

bool PKBParent::isParentExist(STMT_NO child) {
	STMT_NO parent = getParent(child);
	if (parent == "") {
		return false;
	}
	return true;
}

bool PKBParent::isParentRelationship(STMT_NO parent, STMT_NO child) {

	for (auto vectorIter : parentTable) {
		if (vectorIter.front() == parent) {
			if (vectorIter.back() == child) {
				return true;
			}
		}
	}
	return false;
}

bool PKBParent::isParentStarRelationship(STMT_NO parent, STMT_NO child) {

	for (auto vectorIter : parentStarTable) {
		if (vectorIter.front() == parent) {
			if (vectorIter.back() == child) {
				return true;
			}
		}
	}
	return false;
}

TABLE PKBParent::getParentTable() {
	return parentTable;
}

TABLE PKBParent::getAllParentChildStmt(STMT_TYPE type1, STMT_TYPE type2) {
	return PKBParent::getResultTableGenericBoth(type1, type2, parentTable);
}
STMT_LIST PKBParent::getAllParentStmt(STMT_TYPE type1, STMT_NO follows) {
	return PKBParent::getResultTableGenericLeft(type1, follows, parentTable);
}
STMT_LIST PKBParent::getAllChildStmt(STMT_NO followedBy, STMT_TYPE type) {
	return PKBParent::getResultTableGenericRight(followedBy, type, parentTable);
}
TABLE PKBParent::getAllParentChildStarStmt(STMT_TYPE type1, STMT_TYPE type2) {
	return PKBParent::getResultTableGenericBoth(type1, type2, parentStarTable);
}
STMT_LIST PKBParent::getAllParentStarStmt(STMT_TYPE type, STMT_NO follows) {
	return PKBParent::getResultTableGenericLeft(type, follows, parentStarTable);
}
STMT_LIST PKBParent::getAllChildStarStmt(STMT_NO followedBy, STMT_TYPE type) {
	return PKBParent::getResultTableGenericRight(followedBy, type, parentStarTable);
}

TABLE PKBParent::getResultTableGenericBoth(STMT_TYPE type1, STMT_TYPE type2, TABLE tableName) {
	TABLE resultTable;
	if (type1 != "_" && type2 != "_" && type1 == type2) {
		return resultTable;
	}
	if (type1 == "_" && type2 == "_") {
		return tableName;
	}
	STMT_LIST list1, list2;
	if (type1 == "_" || type1 == "STATEMENT") {
		list1 = PKBStmt::getAllStmt();
	}
	else {
		list1 = PKBStmt::getAllStmtByType(type1);
	}
	if (type2 == "_" || type2 == "STATEMENT") {
		list2 = PKBStmt::getAllStmt();
	}
	else {
		list2 = PKBStmt::getAllStmtByType(type2);
	}

	STMT_NO s1;
	STMT_NO s2;
	for (auto iter1 : list1) {
		s1 = iter1.front();
		for (auto iter2 : list2) {
			s2 = iter2.front();
			for (auto vectorIter : tableName) {
				vector<string> tuple = vector<string>();
				if (vectorIter.front() == s1 && vectorIter.back() == s2) {
					tuple.push_back(vectorIter.front());
					tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}
	}

	return resultTable;
}

STMT_LIST PKBParent::getResultTableGenericLeft(STMT_TYPE type, STMT_NO stmtNo, TABLE tableName) {
	STMT_LIST resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "_" || type == "STATEMENT") {
		list = PKBStmt::getAllStmt();
	}
	else {
		list = PKBStmt::getAllStmtByType(type);
	}
	for (auto iter : list) {
		s = iter.front();
		for (auto vectorIter : tableName) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == s && vectorIter.back() == stmtNo) {
				tuple.push_back(vectorIter.front());
				//tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

STMT_LIST PKBParent::getResultTableGenericRight(STMT_NO stmtNo, STMT_TYPE type, TABLE tableName) {
	STMT_LIST resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "_" || type == "STATEMENT") {
		list = PKBStmt::getAllStmt();
	}
	else {
		list = PKBStmt::getAllStmtByType(type);
	}
	for (auto iter : list) {
		s = iter.front();
		for (auto vectorIter : tableName) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == stmtNo && vectorIter.back() == s) {
				//tuple.push_back(vectorIter.front());
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

bool PKBParent::clear() {
	parentTable.clear();
	parentStarTable.clear();
	return true;
}