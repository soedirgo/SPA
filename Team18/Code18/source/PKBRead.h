#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBRead {
public:
	static bool setRead(STMT_NO stmtNo, VAR_NAME varName);
	static STMT_LIST getReadStmt(VAR_NAME varName);
	static VAR_NAME getReadVar(STMT_NO stmtNo);
	// Clear
	static bool clear();

private:
	static std::unordered_set<std::vector<std::string>, VectorDoubleStringHash> readTable;
};