#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBIf {
public:

	static bool setIfUses(STMT_NO stmtNo, VAR_NAME varName);
	static bool isIfUsesRelationship(STMT_NO stmtNo, VAR_NAME varName);

	// Clear
	static bool clear();

private:
	static std::unordered_set<std::vector<std::string>, VectorDoubleStringHash> ifUsesTable;
};