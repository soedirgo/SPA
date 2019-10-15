#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBUses {
public:

	static bool setUsesS(STMT_NO stmtNo, VAR_NAME varName);
	static bool setUsesP(PROC_NAME procName, VAR_NAME varName);
	
	//Bool Evaluation
	static bool isUsesSIdentAny(STMT_NO stmtNo);
	static bool isUsesSIdentIdent(STMT_NO stmtNo, VAR_NAME varName);

	static bool isUsesPIdentAny(PROC_NAME procName);
	static bool isUsesPIdentIdent(PROC_NAME procName, VAR_NAME varName);

	//Table Evaluation
	static STMT_LIST getUsesSEntAny(STMT_TYPE type);
	static STMT_LIST getUsesSEntIdent(STMT_TYPE type, VAR_NAME varName);
	static VAR_LIST getUsesSIdentEnt(STMT_NO stmtNo); 
	static TABLE getUsesSEntEnt(STMT_TYPE type);

	static PROC_LIST getUsesPEntAny(); 
	static PROC_LIST getUsesPEntIdent(VAR_NAME varName);
	static VAR_LIST getUsesPIdentEnt(PROC_NAME procName); 
	static TABLE getUsesPEntEnt();
	
	static TABLE getUsesProcTable();

	// Clear
	static bool clear();

private:
	static TABLE usesStmtTable;
	static TABLE usesProcTable;
};