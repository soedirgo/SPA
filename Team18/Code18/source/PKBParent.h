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

	static bool isParent(STMT_REF stmt1, STMT_REF stmt2);
	static bool isParentT(STMT_REF stmt1, STMT_REF stmt2);

	static TABLE getParent(STMT_REF s1, STMT_REF s2);
	static TABLE getParentT(STMT_REF s1, STMT_REF s2);

	static TABLE getAllParentChildStmt(STMT_TYPE type1, STMT_TYPE type2);
	static STMT_LIST getAllParentStmt(STMT_TYPE type1, STMT_NO follows);
	static STMT_LIST getAllChildStmt(STMT_NO followedBy, STMT_TYPE type1);
	static TABLE getAllParentChildStarStmt(STMT_TYPE type1, STMT_TYPE type2);
	static STMT_LIST getAllParentStarStmt(STMT_TYPE type1, STMT_NO follows);
	static STMT_LIST getAllChildStarStmt(STMT_NO followedBy, STMT_TYPE type1);
	// Clear
	static bool clear();

private:
	static TABLE getResultGenericBoth(STMT_TYPE type1, STMT_TYPE type2, TABLE tableName);
	static STMT_LIST getResultGenericLeft(STMT_TYPE type, STMT_NO child, TABLE tableName);
	static STMT_LIST getResultGenericRight(STMT_NO parent, STMT_TYPE type, TABLE tableName);
	
	static bool isLeftGenericRightGeneric(TABLE tableName);
	static bool isLeftGenericRightFixed(STMT_NO follows, TABLE tableName);
	static bool isLeftFixedRightGeneric(STMT_NO followedBy, TABLE tableName);
	static bool isLeftFixedRightFixed(STMT_NO followedBy, STMT_NO follows, TABLE tableName);

	static TABLE parentTable;
	static TABLE parentTTable;
};