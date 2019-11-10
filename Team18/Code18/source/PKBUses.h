#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBUses {
public:

	static void setUsesS(STMT_NO stmtNo, VAR_NAME varName);
	static void setUsesP(PROC_NAME procName, VAR_NAME varName);
	
	//Bool Evaluation
	static bool isUsesSIdentAny(STMT_NO stmtNo);
	static bool isUsesSIdentIdent(STMT_NO stmtNo, VAR_NAME varName);

	static bool isUsesPIdentAny(PROC_NAME procName);
	static bool isUsesPIdentIdent(PROC_NAME procName, VAR_NAME varName);

	//Table Evaluation
	static STMT_LIST getUsesSEntAny(STMT_TYPE type);
	static STMT_LIST getUsesSEntIdent(STMT_TYPE type, VAR_NAME varName);
	static LIST_OF_VAR_NAME getUsesSIdentEnt(STMT_NO stmtNo); 
	static TABLE getUsesSEntEnt(STMT_TYPE type);

	static LIST_OF_PROC_NAME getUsesPEntAny(); 
	static LIST_OF_PROC_NAME getUsesPEntIdent(VAR_NAME varName);
	static LIST_OF_VAR_NAME getUsesPIdentEnt(PROC_NAME procName); 
	static TABLE getUsesPEntEnt();


	// Clear
	static void clear();

private:
	static TABLE usesStmtTable;
	static TABLE usesProcTable;
};