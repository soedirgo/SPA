#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBUses {
public:

	static bool setUsesStmt(STMT_NO stmtNo, VAR_NAME varName);
	static bool setUsesProc(PROC_NAME procName, VAR_NAME varName);
	
	static bool isUsesStmt(STMT_NO stmtNo, VAR_NAME varName);
	static bool isUsesProc(PROC_NAME procName, VAR_NAME varName);
	
	static STMT_LIST getAllUsesStmtByType(STMT_TYPE type);
	static STMT_LIST getUsesStmtByTypeAndVar(STMT_TYPE type, VAR_NAME varName);
	static VAR_LIST getUsesVarByStmt(STMT_NO stmtNo); 
	static DOUBLE_COL_TABLE getAllUsesStmtPair(STMT_TYPE type);

	static PROC_LIST getAllUsesProc(); 
	static PROC_LIST getUsesProcByVar(VAR_NAME varName);
	static VAR_LIST getUsesVarByProc(PROC_NAME procName); 
	static DOUBLE_COL_TABLE getAllUsesProcPair();

	// Clear
	static bool clear();

private:
	static TABLE usesStmtTable;
	static TABLE usesProcTable;
};