#pragma once

#include <unordered_map>
#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBParent {
public:

	static bool setParent(STMT_NO parent, STMT_NO child);
	static bool setParentStar(STMT_NO parent, STMT_NO child);
	static STMT_LIST getChild(STMT_NO parent);
	static std::unordered_set<std::vector<std::string>, VectorDoubleStringHash> getParentTable();
	static bool isParentRelationship(STMT_NO parent, STMT_NO child);
	static bool isParentStarRelationship(STMT_NO parent, STMT_NO child);

	// Clear
	bool clear();

private:

	static std::unordered_set<std::vector<std::string>, VectorDoubleStringHash> parentTable;
	static std::unordered_set<std::vector<std::string>, VectorDoubleStringHash> parentStarTable;
};