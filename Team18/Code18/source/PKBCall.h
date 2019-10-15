#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBCall {
public:
	static bool setCallStmt(STMT_NO stmtNo, PROC_NAME q);
	static bool setCallProc(PROC_NAME caller, PROC_NAME callee);
	static bool setCallTProc(PROC_NAME caller, PROC_NAME callee);

	static PROC_NAME getCallProcByStmt(STMT_NO stmtNo); //not tested
	//	static STMT_LIST getCallStmtsByProc(STMT_NO stmtNo); //to be implemented
	static TABLE getCallProcTable();
	static TABLE getCallStmtTable();
	static PROC_LIST getCalleeProc(PROC_NAME caller);
	static PROC_LIST getCallerProc(PROC_NAME callee);
	static PROC_LIST getAllCallProc();

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
	static TABLE getCallsAnyEnt();
	static TABLE getCallsIdentEnt(PROC_NAME p1);
	static TABLE getCallsEntAny();
	static TABLE getCallsEntIdent(PROC_NAME p2);
	static TABLE getCallsEntEnt();

	static TABLE getCallsTAnyEnt();
	static TABLE getCallsTIdentEnt(PROC_NAME p1);
	static TABLE getCallsTEntAny();
	static TABLE getCallsTEntIdent(PROC_NAME p2);
	static TABLE getCallsTEntEnt();
	
	// Clear
	static bool clear();

private:
	static TABLE callsProcTable;
	static TABLE callsTProcTable;
	static TABLE callStmtTable;
};