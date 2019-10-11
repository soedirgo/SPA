#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBUses {
public:

	static bool setUsesS(STMT_NO stmtNo, VAR_NAME varName);
	static bool setUsesP(PROC_NAME procName, VAR_NAME varName);
	
	static bool isUsesS(STMT_NO stmtNo, VAR_NAME varName);
	static bool isUsesP(PROC_NAME procName, VAR_NAME varName);
	
	static STMT_LIST getAllUsesStmtByType(STMT_TYPE type);
	static STMT_LIST getUsesStmtByTypeAndVar(STMT_TYPE type, VAR_NAME varName);
	static VAR_LIST getUsesVarByStmt(STMT_NO stmtNo); 
	static TABLE getAllUsesStmtPair(STMT_TYPE type);

	static PROC_LIST getAllUsesProc(); 
	static PROC_LIST getUsesProcByVar(VAR_NAME varName);
	static VAR_LIST getUsesVarByProc(PROC_NAME procName); 
	static TABLE getAllUsesProcPair();

	// Clear
	static bool clear();

private:
	static TABLE usesStmtTable;
	static TABLE usesProcTable;
};