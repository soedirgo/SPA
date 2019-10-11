#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBCall {
public:
	static bool setCallStmt(STMT_NO stmtNo, PROC_NAME q);
	static bool setCallProc(PROC_NAME caller, PROC_NAME callee);
	static bool setCallTProc(PROC_NAME caller, PROC_NAME callee);
	static bool isCallRelationship(PROC_NAME caller, PROC_NAME callee);
	static bool isCallStarRelationship(PROC_NAME caller, PROC_NAME callee);

	static PROC_NAME getCalledProcByStmt(STMT_NO stmtNo); //not tested
	static TABLE getCallProcTable();
	static PROC_LIST getCalleeProc(PROC_NAME caller);

	static TABLE getAllCallerCalleeProc();
	static PROC_LIST getAllCallerProc(PROC_NAME procName);
	static PROC_LIST getAllCalleProc(PROC_NAME procName);
	static TABLE getAllCallerCalleeStarProc();
	static PROC_LIST getAllCallerStarProc(PROC_NAME procName);
	static PROC_LIST getAllCalleStarProc(PROC_NAME procName);
	// Clear
	static bool clear();

private:
	static TABLE getResultTableGenericBoth(TABLE tableName);
	static PROC_LIST getResultTableGenericLeft(PROC_NAME procName, TABLE tableName);
	static PROC_LIST getResultTableGenericRight(PROC_NAME procName, TABLE tableName);
	static std::unordered_set<std::vector<std::string>, VectorDoubleStringHash> callProcTable;
	static std::unordered_set<std::vector<std::string>, VectorDoubleStringHash> callStarProcTable;
	static std::unordered_set<std::vector<std::string>, VectorDoubleStringHash> callStmtTable;
};