#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBPrint {
public:
	static bool setPrint(STMT_NO stmtNo, VAR_NAME varName);
	static VAR_NAME getPrintVariable(STMT_NO stmtNo);
	static VAR_LIST getAllPrintVar();
	// Clear
	static bool clear();

private:
	static TABLE printTable;
};