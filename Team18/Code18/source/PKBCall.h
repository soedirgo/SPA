#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBCall {
public:
	static bool setCallStmt(STMT_NO stmtNo, PROC_NAME q);
	static bool setCallProc(PROC_NAME p, PROC_NAME q);
	static bool isCallRelationship(PROC_NAME p, PROC_NAME q);

	// Clear
	bool clear();

private:
	static std::unordered_set<std::vector<std::string>, VectorHash> callProcTable;
	static std::unordered_set<std::vector<std::string>, VectorHash> callStmtTable;
};