#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBStmt {
public:
	static bool setStmt(STMT_NO stmtNo, STMT_TYPE type);
	static STMT_LIST getAllStmt();
	static STMT_LIST getAllStmtByType(STMT_TYPE type);
	// Clear
	static bool clear();

private:
	static std::unordered_set<std::vector<std::string>, VectorDoubleStringHash> stmtTable;
};