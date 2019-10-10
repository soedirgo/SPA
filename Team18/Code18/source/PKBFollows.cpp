#include "PKBFollows.h"
#include "PKBStmt.h"

using namespace std;

unordered_set<vector<string>, VectorDoubleStringHash> PKBFollows::followsTable;
unordered_set<vector<string>, VectorDoubleStringHash> PKBFollows::followsStarTable;

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
	followsStarTable.emplace(tuple);
	return true;
}

string PKBFollows::getFollows(STMT_NO followedBy) {
	for (auto vectorIter : followsTable) {
		if (vectorIter.front() == followedBy) {
			return vectorIter.back();
		}
	}
	return "";
}

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

	for (auto vectorIter : followsStarTable) {
		if (vectorIter.front() == followedBy) {
			if (vectorIter.back() == follows) {
				return true;
			}
		}
	}
	return false;
}

TABLE PKBFollows::getFollowsTable() {
	return followsTable;
}

TABLE PKBFollows::getAllFollowedByFollowsStmt(STMT_TYPE type1, STMT_TYPE type2) {
	return PKBFollows::getResultTableGenericBoth(type1, type2, followsTable);
}
TABLE PKBFollows::getAllFollowedByStmt(STMT_TYPE type1, STMT_NO follows) {
	return PKBFollows::getResultTableGenericLeft(type1, follows, followsTable);
}
TABLE PKBFollows::getAllFollowsStmt(STMT_NO followedBy, STMT_TYPE type) {
	return PKBFollows::getResultTableGenericRight(followedBy, type, followsTable);
}
TABLE PKBFollows::getAllFollowedByFollowsStarStmt(STMT_TYPE type1, STMT_TYPE type2) {
	return PKBFollows::getResultTableGenericBoth(type1, type2, followsStarTable);
}
TABLE PKBFollows::getAllFollowedByStarStmt(STMT_TYPE type, STMT_NO follows) {
	return PKBFollows::getResultTableGenericLeft(type, follows, followsStarTable);
}
TABLE PKBFollows::getAllFollowsStarStmt(STMT_NO followedBy, STMT_TYPE type) {
	return PKBFollows::getResultTableGenericRight(followedBy, type, followsStarTable);
}

TABLE PKBFollows::getResultTableGenericBoth(STMT_TYPE type1, STMT_TYPE type2, TABLE tableName) {
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

TABLE PKBFollows::getResultTableGenericLeft(STMT_TYPE type, STMT_NO stmtNo, TABLE tableName) {
	TABLE resultTable;
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
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBFollows::getResultTableGenericRight(STMT_NO stmtNo, STMT_TYPE type, TABLE tableName) {
	TABLE resultTable;
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
				tuple.push_back(vectorIter.front());
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}


bool PKBFollows::clear() {
	followsTable.clear();
	followsStarTable.clear();
	return true;
}