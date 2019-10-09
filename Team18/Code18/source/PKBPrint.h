#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBPrint {
public:
	static bool setPrint(STMT_NO stmtNo, VAR_NAME varName);
	static VAR_LIST getPrintVar(STMT_NO stmtNo);
	// Clear
	bool clear();

private:
	static std::unordered_set<std::vector<std::string>, VectorDoubleStringHash> printTable;
};