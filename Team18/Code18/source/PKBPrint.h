#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBPrint {
public:
	static bool setPrint(STMT_NO stmtNo, VAR_NAME varName);
	static STMT_LIST getPrintStmt(VAR_NAME varName);
	static VAR_NAME getPrintVar(STMT_NO stmtNo);
	// Clear
	static bool clear();

private:
	static TABLE printTable;
};