#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBModifies {
public:

	static bool setModifiesStmt(STMT_NO stmtNo, VAR_NAME varName);
	static bool setModifiesProc(PROC_NAME procName, VAR_NAME);
	static bool isModifiesStmtRelationship(STMT_NO stmtNo, VAR_NAME varName);

	// Clear
	bool clear();

private:
	//static std::vector<std::string, std::string> stmtUsesByVarTable;
	static std::unordered_set<std::vector<std::string>, VectorHash> modifiesStmtTable;
	static std::unordered_set<std::vector<std::string>, VectorHash> modifiesProcTable;
};