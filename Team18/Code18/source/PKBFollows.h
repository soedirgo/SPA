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
	static bool isFollowsRelationship(STMT_NO followedBy, STMT_NO follows);
	static bool isFollowsStarRelationship(STMT_NO followedBy, STMT_NO follows);

	static bool isFollows(STMT_REF stmt1, STMT_REF stmt2);

	//Internal//
	static bool isFollowsS1GenericS2Generic();
	static bool isFollowsS1GenericS2StmtNo(STMT_NO follows);
	static bool isFollowsS1StmtNoS2Generic(STMT_NO followedBy);
	static bool isFollowsS1StmtNoS2StmtNo(STMT_NO followedBy, STMT_NO follows);
	static TABLE getFollowsS1S2Same(STMT_TYPE s1, STMT_TYPE s2);
	//End of Internal//

	static TABLE getFollows(STMT_REF s1, STMT_REF s2);

	static TABLE getAllFollowedByFollowsStmt(STMT_TYPE type1, STMT_TYPE type2);
	static STMT_LIST getAllFollowedByStmt(STMT_TYPE type, STMT_NO follows);
	static STMT_LIST getAllFollowsStmt(STMT_NO followedBy, STMT_TYPE type1);
	
	static TABLE getAllFollowedByFollowsStarStmt(STMT_TYPE type1, STMT_TYPE type2);
	static STMT_LIST getAllFollowedByStarStmt(STMT_TYPE type, STMT_NO follows);
	static STMT_LIST getAllFollowsStarStmt(STMT_NO followedBy, STMT_TYPE type);
	// Clear
	static bool clear();

private:
	static TABLE getResultTableGenericBoth(STMT_TYPE type1, STMT_TYPE type2, TABLE tableName);
	static STMT_LIST getResultGenericLeft(STMT_TYPE type, STMT_NO follows, TABLE tableName);
	static STMT_LIST getResultGenericRight(STMT_NO followedBy, STMT_TYPE type, TABLE tableName);
	static TABLE followsTable;
	static TABLE followsStarTable;
};