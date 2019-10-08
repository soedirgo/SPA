#include "PKBFollow.h"

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

unordered_set<vector<string>, VectorDoubleStringHash> PKBFollows::getFollowsTable() {
	return followsTable;
}

bool PKBFollows::clear() {
	followsTable.clear();
	followsStarTable.clear();
	return true;
}

/*
unordered_map<int, int> PKBFollow::followTable;
unordered_map<int, unordered_set<int>> PKBFollow::followedByTable;
unordered_map<int, unordered_set<int>> PKBFollow::followStarTable;

bool PKBFollow::setFollow(int followedBy, int follow) {
	followTable[followedBy] = follow;
	return true;
}

bool PKBFollow::setFollowedBy(int followedBy, int follow) {
	try {
		unordered_set<int> stmtList = getFollowedByStmtList(follow);
		stmtList.emplace(followedBy);
		followedByTable[follow] = stmtList;
		return true;
	}
	catch (errc e) {
		return false;
	}
}

bool PKBFollow::setFollowStar(int followedBy, int follow) {
	try {
		unordered_set<int> stmtList = getFollowStarStmtList(followedBy);
		stmtList.emplace(follow);
		followStarTable[followedBy] = stmtList;
		return true;
	}
	catch (errc e) {
		return false;
	}
}

unordered_set<int> PKBFollow::getFollowStarStmtList(int followedBy) {
	return followStarTable[followedBy];
}

int PKBFollow::getFollowStmt(int followedBy) {
	return followTable[followedBy];
}

unordered_set<int> PKBFollow::getAllFollowedBy() {
	unordered_set<int> followedByList;
	for (auto keyValue : followTable) {
		followedByList.emplace(keyValue.first);
	}
	return followedByList;
}

unordered_set<int> PKBFollow::getFollowedByStmtList(int follow) {
	return followedByTable[follow];
}

bool PKBFollow::isFollowRelationship(int followedBy, int follow) {
	for (auto keyValue : followTable) {
		if (keyValue.first == followedBy) {
			if (keyValue.second == follow) {
				return true;
			}
		}
	}
	return false;
}

bool PKBFollow::isFollowStarRelationship(int followedBy, int follow) {
	unordered_set<int> stmtList = getFollowStarStmtList(followedBy);
	for (auto keyValue : stmtList) {
		if (keyValue == follow) {
			return true;
		}
	}
	return false;
}

bool PKBFollow::isFollowExist(int stmtNo) {
	return followedByTable.find(stmtNo) != followedByTable.end();
}
bool PKBFollow::isFollowedByExist(int stmtNo) {
	return followTable.find(stmtNo) != followTable.end();
}

bool PKBFollow::clear() {
	followTable.clear();
	followedByTable.clear();
	followStarTable.clear();
	return true;
}

*/