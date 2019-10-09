#pragma once

#include <unordered_map>
#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBFollows {
public:

	static bool setFollows(STMT_NO followedBy, STMT_NO follows);
	static bool setFollowsStar(STMT_NO followedBy, STMT_NO follows);
	static std::string getFollows(STMT_NO followedBy);
	static std::unordered_set<std::vector<std::string>, VectorDoubleStringHash> getFollowsTable();
	static bool isFollowsRelationship(STMT_NO followedBy, STMT_NO follows);
	static bool isFollowsStarRelationship(STMT_NO followedBy, STMT_NO follows);

	// Clear
	bool clear();

private:

	static std::unordered_set<std::vector<std::string>, VectorDoubleStringHash> followsTable;
	static std::unordered_set<std::vector<std::string>, VectorDoubleStringHash> followsStarTable;
};