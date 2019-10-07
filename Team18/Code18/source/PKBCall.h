#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBCall {
public:
	static bool setCallStmt(STMT_NO stmtNo, PROC_NAME q);
	static bool setCallProc(PROC_NAME caller, PROC_NAME callee);
	static bool setCallStarProc(PROC_NAME caller, PROC_NAME callee);
	static bool isCallRelationship(PROC_NAME caller, PROC_NAME callee);
	static bool isCallStarRelationship(PROC_NAME caller, PROC_NAME callee);

	static std::unordered_set<std::vector<std::string>, VectorHash> getCallProcTable();
	static PROC_LIST getCalleeProc(PROC_NAME caller);
	// Clear
	bool clear();

private:
	static std::unordered_set<std::vector<std::string>, VectorHash> callProcTable;
	static std::unordered_set<std::vector<std::string>, VectorHash> callStarProcTable;
	static std::unordered_set<std::vector<std::string>, VectorHash> callStmtTable;
};