#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>
#include <unordered_map>

class PKBStmt {
public:

	static bool setStmt(STMT_NO stmtNo, STMT_TYPE type);

	static std::unordered_set<STMT_NO> getAllStmt();
	static std::unordered_set<STMT_NO> getAllStmtByType(STMT_TYPE type);
	
	// Clear
	bool clear();

private:
	static std::unordered_map<STMT_NO, STMT_TYPE> stmtTable;
};