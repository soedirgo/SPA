#include "PKBParent.h"
#include "PKBStmt.h"
#include <system_error>

using namespace std;

TABLE PKBParent::parentTable;
TABLE PKBParent::parentTTable;

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
	parentTTable.emplace(tuple);
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

	for (auto vectorIter : parentTTable) {
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

bool PKBParent::isParent(STMT_REF s1, STMT_REF s2) {
	if (s1 == "_" && s2 == "_") {
		return PKBParent::isLeftGenericRightGeneric(parentTable);
	}
	else if (s1 == "_" && isdigit(s2.at(0))) {
		return PKBParent::isLeftGenericRightFixed(s2, parentTable);
	}
	else if (isdigit(s1.at(0)) && s2 == "_") {
		return PKBParent::isLeftFixedRightGeneric(s1, parentTable);
	}
	else if (isdigit(s1.at(0)) && isdigit(s2.at(0))) {
		return PKBParent::isLeftFixedRightFixed(s1, s2, parentTable);
	}
	return false;
}

bool PKBParent::isParentT(STMT_REF s1, STMT_REF s2) {
	if (s1 == "_" && s2 == "_") {
		return PKBParent::isLeftGenericRightGeneric(parentTTable);
	}
	else if (s1 == "_" && isdigit(s2.at(0))) {
		return PKBParent::isLeftGenericRightFixed(s2, parentTTable);
	}
	else if (isdigit(s1.at(0)) && s2 == "_") {
		return PKBParent::isLeftFixedRightGeneric(s1, parentTTable);
	}
	else if (isdigit(s1.at(0)) && isdigit(s2.at(0))) {
		return PKBParent::isLeftFixedRightFixed(s1, s2, parentTTable);
	}
	return false;
}

bool PKBParent::isLeftGenericRightGeneric(TABLE tableName) {
	return !tableName.empty();
}

TABLE PKBParent::getParent(STMT_REF s1, STMT_REF s2) {
	if (s1 == "_") {
		return PKBParent::getResultGenericLeft("_", s2, parentTable);
	}
	else if (isdigit(s1.at(0))) {
		return PKBParent::getResultGenericRight(s1, s2, parentTable);
	}
	else if (s2 == "_") {
		return PKBParent::getResultGenericRight(s1, "_", parentTable);
	}
	else if (isdigit(s2.at(0))) {
		return PKBParent::getResultGenericLeft(s1, s2, parentTable);
	}
	return PKBParent::getResultGenericBoth(s1, s2, parentTable);
}

TABLE PKBParent::getParentT(STMT_REF s1, STMT_REF s2) {
	if (s1 == "_") {
		return PKBParent::getResultGenericLeft("_", s2, parentTTable);
	}
	else if (isdigit(s1.at(0))) {
		return PKBParent::getResultGenericRight(s1, s2, parentTTable);
	}
	else if (s2 == "_") {
		return PKBParent::getResultGenericRight(s1, "_", parentTTable);
	}
	else if (isdigit(s2.at(0))) {
		return PKBParent::getResultGenericLeft(s1, s2, parentTTable);
	}
	return PKBParent::getResultGenericBoth(s1, s2, parentTTable);
}

bool PKBParent::isLeftGenericRightFixed(STMT_NO follows, TABLE tableName) {
	for (auto vectorIter : tableName) {
		if (vectorIter.back() == follows) {
			return true;
		}
	}
	return false;
}
bool PKBParent::isLeftFixedRightGeneric(STMT_NO followedBy, TABLE tableName) {
	for (auto vectorIter : tableName) {
		if (vectorIter.front() == followedBy) {
			return true;
		}
	}
	return false;
}
bool PKBParent::isLeftFixedRightFixed(STMT_NO followedBy, STMT_NO follows, TABLE tableName) {
	for (auto vectorIter : tableName) {
		if (vectorIter.front() == followedBy) {
			if (vectorIter.back() == follows) {
				return true;
			}
		}
	}
	return false;
}

TABLE PKBParent::getResultGenericBoth(STMT_TYPE type1, STMT_TYPE type2, TABLE tableName) {
	TABLE resultTable;
	if (type1 == "stmt" && type2 == "stmt") {
		return tableName;
	}
	STMT_LIST list1, list2;
	if (type1 == "_" || type1 == "stmt") {
		list1 = PKBStmt::getAllStmt();
	}
	else {
		list1 = PKBStmt::getAllStmtByType(type1);
	}
	if (type2 == "_" || type2 == "stmt") {
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

TABLE PKBParent::getResultGenericLeft(STMT_TYPE type, STMT_NO stmtNo, TABLE tableName) {
	TABLE resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt") {
		list = PKBStmt::getAllStmt();
	}
	else {
		list = PKBStmt::getAllStmtByType(type);
	}
	if (type == "_") {
		for (auto iter : list) {
			s = iter.front();
			for (auto vectorIter : tableName) {
				vector<string> tuple = vector<string>();
				if (vectorIter.front() == s) {
					tuple.push_back(vectorIter.front());
					//tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	else {
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
	}
	return resultTable;
}

TABLE PKBParent::getResultGenericRight(STMT_NO stmtNo, STMT_TYPE type, TABLE tableName) {
	TABLE resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt") {
		list = PKBStmt::getAllStmt();
	}
	else {
		list = PKBStmt::getAllStmtByType(type);
	}
	if (type == "_") {
		for (auto iter : list) {
			s = iter.front();
			for (auto vectorIter : tableName) {
				vector<string> tuple = vector<string>();
				if (vectorIter.back() == s) {
					tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	else {
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
	}
	return resultTable;
}

bool PKBParent::clear() {
	parentTable.clear();
	parentTTable.clear();
	return true;
}