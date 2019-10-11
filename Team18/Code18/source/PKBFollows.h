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

	static bool isFollows(STMT_REF stmt1, STMT_REF stmt2);
	static bool isFollowsT(STMT_REF stmt1, STMT_REF stmt2);

	static TABLE getFollows(STMT_REF s1, STMT_REF s2);
	static TABLE getFollowsT(STMT_REF s1, STMT_REF s2);

	// Clear
	static bool clear();

private:
	static TABLE getResultTableGenericBoth(STMT_TYPE type1, STMT_TYPE type2, TABLE tableName);
	static TABLE getResultGenericLeft(STMT_TYPE type, STMT_NO follows, TABLE tableName);
	static TABLE getResultGenericRight(STMT_NO followedBy, STMT_TYPE type, TABLE tableName);
	
	static bool isLeftGenericRightGeneric(TABLE tableName);
	static bool isLeftGenericRightFixed(STMT_NO follows, TABLE tableName);
	static bool isLeftFixedRightGeneric(STMT_NO followedBy, TABLE tableName);
	static bool isLeftFixedRightFixed(STMT_NO followedBy, STMT_NO follows, TABLE tableName);

	static TABLE followsTable;
	static TABLE followsTTable;
};