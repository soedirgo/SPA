#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBRead {
public:
	static void setRead(STMT_NO stmtNo, VAR_NAME varName);
	static VAR_NAME getReadVariable(STMT_NO);
	static LIST_OF_VAR_NAME getAllReadVar();
	// Clear
	static void clear();

private:
	static TABLE readTable;
};