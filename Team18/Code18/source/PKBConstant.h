#pragma once
#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBConstant {
public:

	static bool setConstant(CONST_VALUE constVal, STMT_NO stmtNo);
	static STMT_LIST getAllConstantStmtByVal(CONST_VALUE constVal);
	static CONST_LIST getAllConstantVal();
	// Clear
	bool clear();

private:
	static std::unordered_set<std::vector<std::string>, VectorHash> constantTable;
};