#include "PKBFollows.h"
#include "PKBStmt.h"

using namespace std;

TABLE PKBFollows::followsTable;
TABLE PKBFollows::followsStarTable;

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

bool PKBFollows::isFollows(string s1, string s2){
	if (s1 == "_" && s2 == "_") {
		return PKBFollows::isFollowsS1GenericS2Generic();
	}
	else if (s1 == "_" && isdigit(s2.at(0))) {
		return PKBFollows::isFollowsS1GenericS2StmtNo(s2);
	}
	else if (isdigit(s1.at(0)) && s2 == "_") {
		return PKBFollows::isFollowsS1StmtNoS2Generic(s1);
	}
	else if (isdigit(s1.at(0)) && isdigit(s2.at(0))) {
		return PKBFollows::isFollowsS1StmtNoS2StmtNo(s1,s2);
	}
}
bool PKBFollows::isFollowsS1GenericS2Generic() {
	return !followsTable.empty();
}
bool PKBFollows::isFollowsS1GenericS2StmtNo(STMT_NO follows) {
	for (auto vectorIter : followsStarTable) {
		if (vectorIter.back() == follows) {
			return true;
		}
	}
	return false;
}
bool PKBFollows::isFollowsS1StmtNoS2Generic(STMT_NO followedBy) {
	for (auto vectorIter : followsStarTable) {
		if (vectorIter.front() == followedBy) {
			return true;
		}
	}
	return false;
}
bool PKBFollows::isFollowsS1StmtNoS2StmtNo(STMT_NO followedBy, STMT_NO follows) {
	for (auto vectorIter : followsStarTable) {
		if (vectorIter.front() == followedBy) {
			if (vectorIter.back() == follows) {
				return true;
			}
		}
	}
	return false;
}

//NEW EVALUATION API

STMT_LIST PKBFollows::getFollowsS2(STMT_TYPE type) {
	return PKBFollows::getResultGenericLeft("_", type, followsTable);
}
STMT_LIST PKBFollows::getFollowsS2WithS1StmtNo(STMT_NO s1, STMT_TYPE s2) {
	return PKBFollows::getResultGenericRight(s1, s2, followsTable);
}
STMT_LIST PKBFollows::getFollowsS1(STMT_TYPE s2) {
	return PKBFollows::getResultGenericRight(s2, "_", followsTable);
}
STMT_LIST PKBFollows::getFollowsS1WithS2StmtNo(STMT_TYPE s1, STMT_NO s2) {
	return PKBFollows::getResultGenericLeft(s1, s2, followsTable);
}
TABLE PKBFollows::getFollowsS1S2(STMT_TYPE s1, STMT_TYPE s2) {
	return PKBFollows::getResultTableGenericBoth(s1, s2, followsTable);
}

TABLE PKBFollows::getFollowsS1S2Same(STMT_TYPE s1, STMT_TYPE s2) {
	TABLE resultTable;
	return resultTable;
}

TABLE PKBFollows::getAllFollowedByFollowsStarStmt(STMT_TYPE type1, STMT_TYPE type2) {
	return PKBFollows::getResultTableGenericBoth(type1, type2, followsStarTable);
}
STMT_LIST PKBFollows::getAllFollowedByStarStmt(STMT_TYPE type, STMT_NO follows) {
	return PKBFollows::getResultGenericLeft(type, follows, followsStarTable);
}
STMT_LIST PKBFollows::getAllFollowsStarStmt(STMT_NO followedBy, STMT_TYPE type) {
	return PKBFollows::getResultGenericRight(followedBy, type, followsStarTable);
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

STMT_LIST PKBFollows::getResultGenericLeft(STMT_TYPE type, STMT_NO stmtNo, TABLE tableName) {
	STMT_LIST resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "STATEMENT") {
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

STMT_LIST PKBFollows::getResultGenericRight(STMT_NO stmtNo, STMT_TYPE type, TABLE tableName) {
	STMT_LIST resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "STATEMENT") {
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
	followsStarTable.clear();
	return true;
}