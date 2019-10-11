#include "PKBFollows.h"
#include "PKBStmt.h"

using namespace std;

TABLE PKBFollows::followsTable;
TABLE PKBFollows::followsTTable;

bool PKBFollows::setFollows(STMT_NO followedBy, STMT_NO follows) {
	vector<string> tuple = vector<string>();
	tuple.push_back(followedBy);
	tuple.push_back(follows);
	followsTable.emplace(tuple);
	return true;
}

bool PKBFollows::setFollowsStar(STMT_NO followedBy, STMT_NO follows) {
	vector<string> tuple = vector<string>();
	tuple.push_back(followedBy);
	tuple.push_back(follows);
	followsTTable.emplace(tuple);
	return true;
}

STMT_NO PKBFollows::getFollowsStmt(STMT_NO followedBy) {
	for (auto vectorIter : followsTable) {
		if (vectorIter.front() == followedBy) {
			return vectorIter.back();
		}
	}
	return "";
}

/*
bool PKBFollows::isFollowsRelationship(STMT_NO followedBy, STMT_NO follows) {

	for (auto vectorIter : followsTable) {
		if (vectorIter.front() == followedBy) {
			if (vectorIter.back() == follows) {
				return true;
			}
		}
	}
	return false;
}

bool PKBFollows::isFollowsStarRelationship(STMT_NO followedBy, STMT_NO follows) {

	for (auto vectorIter : followsTTable) {
		if (vectorIter.front() == followedBy) {
			if (vectorIter.back() == follows) {
				return true;
			}
		}
	}
	return false;
}
*/

TABLE PKBFollows::getFollowsTable() {
	return followsTable;
}

bool PKBFollows::isFollows(STMT_REF s1, STMT_REF s2){
	if (s1 == "_" && s2 == "_") {
		return PKBFollows::isLeftGenericRightGeneric(followsTable);
	}
	else if (s1 == "_" && isdigit(s2.at(0))) {
		return PKBFollows::isLeftGenericRightFixed(s2, followsTable);
	}
	else if (isdigit(s1.at(0)) && s2 == "_") {
		return PKBFollows::isLeftFixedRightGeneric(s1, followsTable);
	}
	else if (isdigit(s1.at(0)) && isdigit(s2.at(0))) {
		return PKBFollows::isLeftFixedRightFixed(s1,s2, followsTable);
	}
	return false;
}

bool PKBFollows::isFollowsT(STMT_REF s1, STMT_REF s2) {
	if (s1 == "_" && s2 == "_") {
		return PKBFollows::isLeftGenericRightGeneric(followsTTable);
	}
	else if (s1 == "_" && isdigit(s2.at(0))) {
		return PKBFollows::isLeftGenericRightFixed(s2, followsTTable);
	}
	else if (isdigit(s1.at(0)) && s2 == "_") {
		return PKBFollows::isLeftFixedRightGeneric(s1, followsTTable);
	}
	else if (isdigit(s1.at(0)) && isdigit(s2.at(0))) {
		return PKBFollows::isLeftFixedRightFixed(s1, s2, followsTTable);
	}
	return false;
}
bool PKBFollows::isLeftGenericRightGeneric(TABLE tableName) {
	return !tableName.empty();
}
bool PKBFollows::isLeftGenericRightFixed(STMT_NO follows, TABLE tableName) {
	for (auto vectorIter : tableName) {
		if (vectorIter.back() == follows) {
			return true;
		}
	}
	return false;
}
bool PKBFollows::isLeftFixedRightGeneric(STMT_NO followedBy, TABLE tableName) {
	for (auto vectorIter : tableName) {
		if (vectorIter.front() == followedBy) {
			return true;
		}
	}
	return false;
}
bool PKBFollows::isLeftFixedRightFixed(STMT_NO followedBy, STMT_NO follows, TABLE tableName) {
	for (auto vectorIter : tableName) {
		if (vectorIter.front() == followedBy) {
			if (vectorIter.back() == follows) {
				return true;
			}
		}
	}
	return false;
}

//NEW EVALUATION API

TABLE PKBFollows::getFollows(STMT_REF s1, STMT_REF s2) {
	if (s1 == "_") {
		return PKBFollows::getResultGenericLeft("_", s2, followsTable);
	}
	else if (isdigit(s1.at(0))) {
		return PKBFollows::getResultGenericRight(s1, s2, followsTable);
	}
	else if (s2 == "_") {
		return PKBFollows::getResultGenericRight(s1, "_", followsTable);
	}
	else if (isdigit(s2.at(0))) {
		return PKBFollows::getResultGenericLeft(s1, s2, followsTable);
	}
	return PKBFollows::getResultTableGenericBoth(s1, s2, followsTable);
}

TABLE PKBFollows::getFollowsT(STMT_REF s1, STMT_REF s2) {
	if (s1 == "_") {
		return PKBFollows::getResultGenericLeft("_", s2, followsTTable);
	}
	else if (isdigit(s1.at(0))) {
		return PKBFollows::getResultGenericRight(s1, s2, followsTTable);
	}
	else if (s2 == "_") {
		return PKBFollows::getResultGenericRight(s1, "_", followsTTable);
	}
	else if (isdigit(s2.at(0))) {
		return PKBFollows::getResultGenericLeft(s1, s2, followsTTable);
	}
	return PKBFollows::getResultTableGenericBoth(s1, s2, followsTTable);
}

TABLE PKBFollows::getResultTableGenericBoth(STMT_TYPE type1, STMT_TYPE type2, TABLE tableName) {
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

TABLE PKBFollows::getResultGenericLeft(STMT_TYPE type, STMT_NO stmtNo, TABLE tableName) {
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

TABLE PKBFollows::getResultGenericRight(STMT_NO stmtNo, STMT_TYPE type, TABLE tableName) {
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


bool PKBFollows::clear() {
	followsTable.clear();
	followsTTable.clear();
	return true;
}