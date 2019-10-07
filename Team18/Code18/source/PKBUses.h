#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBUses {
public:

	static bool setUsesStmt(STMT_NO stmtNo, VAR_NAME varName);
	static bool isUsesStmtRelationship(STMT_NO stmtNo, VAR_NAME varName);

	static STMT_LIST getUsesStmt(VAR_NAME varName);

	// Clear
	bool clear();

private:
	static std::unordered_set<std::vector<std::string>, VectorHash> usesStmtTable;
};