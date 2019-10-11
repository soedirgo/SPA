#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBUses {
public:

	static bool setUsesStmt(STMT_NO stmtNo, VAR_NAME varName);
	static bool setUsesProc(PROC_NAME procName, VAR_NAME varName);
	
	static bool isUsesStmtRelationship(STMT_NO stmtNo, VAR_NAME varName);
	static bool isUsesProcRelationship(PROC_NAME procName, VAR_NAME varName);
	
	static STMT_LIST getAllUsesStmt(); 
	static STMT_LIST getAllUsesStmtByType(STMT_TYPE type);
	static STMT_LIST getUsesStmtByTypeAndVar(STMT_TYPE type, VAR_NAME varName);

	static STMT_LIST getUsesStmtByVar(VAR_NAME varName);
	static VAR_LIST getUsesVarByStmt(STMT_NO stmtNo); 

	static PROC_LIST getAllUsesProc(); 
	static PROC_LIST getUsesProcByVar(VAR_NAME varName);
	static VAR_LIST getUsesVarByProc(PROC_NAME procName); 

	// Clear
	static bool clear();

private:
	static TABLE usesStmtTable;
	static TABLE usesProcTable;
};