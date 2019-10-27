#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBRead {
public:
	static bool setRead(STMT_NO stmtNo, VAR_NAME varName);
	static VAR_NAME getReadVariable(STMT_NO);
	static VAR_LIST getAllReadVar();
	// Clear
	static bool clear();

private:
	static TABLE readTable;
};