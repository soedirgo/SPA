#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBFollows {
public:

	static bool setFollows(STMT_NO followedBy, STMT_NO follows);
	static bool setFollowsStar(STMT_NO followedBy, STMT_NO follows);
	static std::string getFollows(STMT_NO followedBy);
	static TABLE getFollowsTable();
	static bool isFollowsRelationship(STMT_NO followedBy, STMT_NO follows);
	static bool isFollowsStarRelationship(STMT_NO followedBy, STMT_NO follows);
	static TABLE getAllFollowedByFollowsStmt(STMT_TYPE type1, STMT_TYPE type2);
	static TABLE getAllFollowedByStmt(STMT_TYPE type, STMT_NO follows);
	static TABLE getAllFollowsStmt(STMT_NO followedBy, STMT_TYPE type1);
	static TABLE getAllFollowedByFollowsStarStmt(STMT_TYPE type1, STMT_TYPE type2);
	static TABLE getAllFollowedByStarStmt(STMT_TYPE type, STMT_NO follows);
	static TABLE getAllFollowsStarStmt(STMT_NO followedBy, STMT_TYPE type);
	// Clear
	static bool clear();

private:
	static TABLE getResultTableGenericBoth(STMT_TYPE type1, STMT_TYPE type2, TABLE tableName);
	static TABLE getResultTableGenericLeft(STMT_TYPE type, STMT_NO follows, TABLE tableName);
	static TABLE getResultTableGenericRight(STMT_NO followedBy, STMT_TYPE type, TABLE tableName);
	static std::unordered_set<std::vector<std::string>, VectorDoubleStringHash> followsTable;
	static std::unordered_set<std::vector<std::string>, VectorDoubleStringHash> followsStarTable;
};