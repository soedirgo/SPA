#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBFollows {
public:

	static bool setFollows(STMT_NO followedBy, STMT_NO follows);
	static bool setFollowsStar(STMT_NO followedBy, STMT_NO follows);
	static STMT_NO getFollowsStmt(STMT_NO followedBy);
	static TABLE getFollowsTable();

	//Bool Evaluation
	static bool isFollowsAnyAny();
	static bool isFollowsAnyIdent(STMT_NO s2);
	static bool isFollowsIdentAny(STMT_NO s1);
	static bool isFollowsIdentIdent(STMT_NO s1, STMT_NO s2);

	static bool isFollowsTAnyAny();
	static bool isFollowsTAnyIdent(STMT_NO s2);
	static bool isFollowsTIdentAny(STMT_NO s1);
	static bool isFollowsTIdentIdent(STMT_NO s1, STMT_NO s2);

	//Table Evaluation
	static TABLE getFollowsAnyEnt(STMT_TYPE s2);
	static TABLE getFollowsIdentEnt(STMT_NO s1, STMT_TYPE s2);
	static TABLE getFollowsEntAny(STMT_TYPE s1);
	static TABLE getFollowsEntIdent(STMT_TYPE s1, STMT_NO s2);
	static TABLE getFollowsEntEnt(STMT_TYPE s1, STMT_TYPE s2);

	static TABLE getFollowsTAnyEnt(STMT_TYPE s2);
	static TABLE getFollowsTIdentEnt(STMT_NO s1, STMT_TYPE s2);
	static TABLE getFollowsTEntAny(STMT_TYPE s1);
	static TABLE getFollowsTEntIdent(STMT_TYPE s1, STMT_NO s2);
	static TABLE getFollowsTEntEnt(STMT_TYPE s1, STMT_TYPE s2);

	// Clear
	static bool clear();

private:
	static TABLE followsTable;
	static TABLE followsTTable;
};