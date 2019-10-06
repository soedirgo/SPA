#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBUses {
public:

	static bool setUsesVarByStmt(STMT_NO stmtNo, VAR_NAME varName);
	static bool isUsesStmtVar(STMT_NO stmtNo, VAR_NAME varName);

	// Clear
	bool clear();

private:
	//static std::vector<std::string, std::string> stmtUsesByVarTable;
	static std::unordered_set<std::vector<std::string>, VectorHash> varUsesByStmtTable;
};