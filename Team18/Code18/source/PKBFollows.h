#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBFollows {
public:

	static bool setFollows(STMT_NO followedBy, STMT_NO follows);
	static bool setFollowsT(STMT_NO followedBy, STMT_NO follows);
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
	static STMT_LIST getFollowsAnyEnt(STMT_TYPE s2);
	static STMT_LIST getFollowsIdentEnt(STMT_NO s1, STMT_TYPE s2);
	static STMT_LIST getFollowsEntAny(STMT_TYPE s1);
	static STMT_LIST getFollowsEntIdent(STMT_TYPE s1, STMT_NO s2);
	static TABLE getFollowsEntEnt(STMT_TYPE s1, STMT_TYPE s2);

	static STMT_LIST getFollowsTAnyEnt(STMT_TYPE s2);
	static STMT_LIST getFollowsTIdentEnt(STMT_NO s1, STMT_TYPE s2);
	static STMT_LIST getFollowsTEntAny(STMT_TYPE s1);
	static STMT_LIST getFollowsTEntIdent(STMT_TYPE s1, STMT_NO s2);
	static TABLE getFollowsTEntEnt(STMT_TYPE s1, STMT_TYPE s2);

	// Clear
	static bool clear();

private:
	static TABLE followsTable;
	static TABLE followsTTable;
};