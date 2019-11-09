#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBPrint {
public:
	static bool setPrint(STMT_NO stmtNo, VAR_NAME varName);
	static VAR_NAME getPrintVariable(STMT_NO stmtNo);
	static LIST_OF_VARIABLE_NAME getAllPrintVar();
	// Clear
	static void clear();

private:
	static TABLE printTable;
};