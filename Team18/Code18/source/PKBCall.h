#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBCall {
public:
	static bool setCallStmt(STMT_NO stmtNo, PROC_NAME q);
	static bool setCallProc(PROC_NAME caller, PROC_NAME callee);
	static bool setCallTProc(PROC_NAME caller, PROC_NAME callee);

	static PROC_NAME getCallProcByStmt(STMT_NO stmtNo);
	static PROC_LIST getCalleeProc(PROC_NAME caller);
	static PROC_LIST getCallerProc(PROC_NAME callee);
	static PROC_LIST getAllCallProc();
	static TABLE getCallStmtTable();
	
	//Bool Evaluation
	static bool isCallsAnyAny();
	static bool isCallsAnyIdent(PROC_NAME p2);
	static bool isCallsIdentAny(PROC_NAME p1);
	static bool isCallsIdentIdent(PROC_NAME p1, PROC_NAME p2);

	static bool isCallsTAnyAny();
	static bool isCallsTAnyIdent(PROC_NAME p2);
	static bool isCallsTIdentAny(PROC_NAME p1);
	static bool isCallsTIdentIdent(PROC_NAME p1, PROC_NAME p2);

	//Table Evaluation
	static PROC_LIST getCallsAnyEnt();
	static PROC_LIST getCallsIdentEnt(PROC_NAME p1);
	static PROC_LIST getCallsEntAny();
	static PROC_LIST getCallsEntIdent(PROC_NAME p2);
	static TABLE getCallsEntEnt();

	static PROC_LIST getCallsTAnyEnt();
	static PROC_LIST getCallsTIdentEnt(PROC_NAME p1);
	static PROC_LIST getCallsTEntAny();
	static PROC_LIST getCallsTEntIdent(PROC_NAME p2);
	static TABLE getCallsTEntEnt();
	
	// Clear
	static bool clear();

private:
	static TABLE callsProcTable;
	static TABLE callsTProcTable;
	static TABLE callStmtTable;
};