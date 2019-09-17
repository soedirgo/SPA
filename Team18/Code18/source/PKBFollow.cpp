#include "PKBFollow.h"
#include <system_error>

using namespace std;

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

unordered_set<int> PKBFollow::getFollowedByStmtList(int follow) {
	return followedByTable[follow];
}

bool PKBFollow::isFollowRelationship(int followedBy, int follow) {
	unordered_set<int> stmtList = getFollowedByStmtList(follow);
	for (auto keyValue : stmtList) {
		if (keyValue == followedBy) {
			return true;
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

bool PKBFollow::clear() {
	followTable.clear();
	followedByTable.clear();
	return true;
}