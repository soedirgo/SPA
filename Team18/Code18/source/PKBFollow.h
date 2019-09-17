#pragma once

#include <unordered_set>
#include <unordered_map>
#include <string>

class PKBFollow {
public:
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

	// Clear
	bool clear();

private:
	static std::unordered_map<int, int> followTable;
	static std::unordered_map<int, std::unordered_set<int>> followedByTable;
	static std::unordered_map<int, std::unordered_set<int>> followStarTable;
};