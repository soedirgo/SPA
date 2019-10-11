#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBParent {
public:

	static bool setParent(STMT_NO parent, STMT_NO child);
	static bool setParentStar(STMT_NO parent, STMT_NO child);
	static STMT_LIST getChild(STMT_NO parent);
	static STMT_NO getParent(STMT_NO parent);
	static bool isParentExist(STMT_NO child);
	static bool isParentRelationship(STMT_NO parent, STMT_NO child);
	static bool isParentStarRelationship(STMT_NO parent, STMT_NO child);
	static TABLE getParentTable();

	static TABLE getAllParentChildStmt(STMT_TYPE type1, STMT_TYPE type2);
	static STMT_LIST getAllParentStmt(STMT_TYPE type1, STMT_NO follows);
	static STMT_LIST getAllChildStmt(STMT_NO followedBy, STMT_TYPE type1);
	static TABLE getAllParentChildStarStmt(STMT_TYPE type1, STMT_TYPE type2);
	static STMT_LIST getAllParentStarStmt(STMT_TYPE type1, STMT_NO follows);
	static STMT_LIST getAllChildStarStmt(STMT_NO followedBy, STMT_TYPE type1);
	// Clear
	static bool clear();

private:
	static TABLE getResultTableGenericBoth(STMT_TYPE type1, STMT_TYPE type2, TABLE tableName);
	static STMT_LIST getResultTableGenericLeft(STMT_TYPE type, STMT_NO child, TABLE tableName);
	static STMT_LIST getResultTableGenericRight(STMT_NO parent, STMT_TYPE type, TABLE tableName);
	static TABLE parentTable;
	static TABLE parentStarTable;
};