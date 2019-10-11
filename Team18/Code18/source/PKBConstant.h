#pragma once
#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBConstant {
public:

	static bool setConstant(STMT_NO stmtNo, CONST_VAL constVal);
	static STMT_LIST getAllConstantStmtByVal(CONST_VAL constVal);
	static CONST_VAL getConstantValByStmt(STMT_NO stmtNo);
	static CONST_LIST getAllConstantVal();
	// Clear
	static bool clear();

private:
	static TABLE constantTable;
};