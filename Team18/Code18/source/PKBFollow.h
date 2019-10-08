#pragma once

#include <unordered_map>
#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBFollows {
public:
	/*
	// add follower to followTable
	static bool setFollow(int followedBy, int follow);
	static bool setFollowedBy(int followedBy, int follow);
	static bool setFollowStar (int followedBy, int follow);

	// GETTERS
	static int getFollowStmt(int followedBy);
	static std::unordered_set<int> getFollowStarStmtList(int followedBy);
	static std::unordered_set<int> getFollowedByStmtList(int follow);

	// Boolean Check
	static bool isFollowRelationship(int followedBy, int follow);
	static bool isFollowStarRelationship(int followedBy, int follow);
	static bool isFollowExist(int stmtNo);
	static bool isFollowedByExist(int stmtNo);

	*/

	static bool setFollows(STMT_NO followedBy, STMT_NO follows);
	static bool setFollowsStar(STMT_NO followedBy, STMT_NO follows);
	static std::string getFollows(STMT_NO followedBy);
	static std::unordered_set<std::vector<std::string>, VectorDoubleStringHash> getFollowsTable();
	static bool isFollowsRelationship(STMT_NO followedBy, STMT_NO follows);
	static bool isFollowsStarRelationship(STMT_NO followedBy, STMT_NO follows);

	// Clear
	bool clear();

	// Internal Use
	//static std::unordered_set<int> getAllFollowedBy();

private:
	//static std::unordered_map<int, int> followTable;
	//static std::unordered_map<int, std::unordered_set<int>> followedByTable;
	//static std::unordered_map<int, std::unordered_set<int>> followStarTable;

	static std::unordered_set<std::vector<std::string>, VectorDoubleStringHash> followsTable;
	static std::unordered_set<std::vector<std::string>, VectorDoubleStringHash> followsStarTable;
};