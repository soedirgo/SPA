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
	static TABLE getAllParentStmt(STMT_TYPE type1, STMT_NO follows);
	static TABLE getAllChildStmt(STMT_NO followedBy, STMT_TYPE type1);
	static TABLE getAllParentChildStarStmt(STMT_TYPE type1, STMT_TYPE type2);
	static TABLE getAllParentStarStmt(STMT_TYPE type1, STMT_NO follows);
	static TABLE getAllChildStarStmt(STMT_NO followedBy, STMT_TYPE type1);
	// Clear
	static bool clear();

private:
	static TABLE getResultTableGenericBoth(STMT_TYPE type1, STMT_TYPE type2, TABLE tableName);
	static TABLE getResultTableGenericLeft(STMT_TYPE type, STMT_NO child, TABLE tableName);
	static TABLE getResultTableGenericRight(STMT_NO parent, STMT_TYPE type, TABLE tableName);
	static std::unordered_set<std::vector<std::string>, VectorDoubleStringHash> parentTable;
	static std::unordered_set<std::vector<std::string>, VectorDoubleStringHash> parentStarTable;
};