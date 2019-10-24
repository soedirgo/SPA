#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBStmt {
public:
	static bool setStmt(STMT_NO stmtNo, STMT_TYPE type);
	static STMT_LIST getStmts();
	static STMT_LIST getStmtsByType(STMT_TYPE type);
	static STMT_TYPE getTypeByStmtNo(STMT_NO stmtNo);
	// Clear
	static bool clear();

private:
	static TABLE stmtTable;
};