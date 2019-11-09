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
	static LIST_OF_PROC_NAME getCallsAnyEnt();
	static LIST_OF_PROC_NAME getCallsIdentEnt(PROC_NAME p1);
	static LIST_OF_PROC_NAME getCallsEntAny();
	static LIST_OF_PROC_NAME getCallsEntIdent(PROC_NAME p2);
	static TABLE getCallsEntEnt();

	static LIST_OF_PROC_NAME getCallsTAnyEnt();
	static LIST_OF_PROC_NAME getCallsTIdentEnt(PROC_NAME p1);
	static LIST_OF_PROC_NAME getCallsTEntAny();
	static LIST_OF_PROC_NAME getCallsTEntIdent(PROC_NAME p2);
	static TABLE getCallsTEntEnt();
	
	// Clear
	static void clear();

private:
	static TABLE callsProcTable;
	static TABLE callsTProcTable;
	static TABLE callStmtTable;
};