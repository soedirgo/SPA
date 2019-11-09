#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBModifies {
public:

	static bool setModifiesS(STMT_NO stmtNo, VAR_NAME varName);
	static bool setModifiesP(PROC_NAME procName, VAR_NAME varName);
	
	//Bool Evaluation
	static bool isModifiesSIdentAny(STMT_NO stmtNo);
	static bool isModifiesSIdentIdent(STMT_NO stmtNo, VAR_NAME varName);

	static bool isModifiesPIdentAny(PROC_NAME procName);
	static bool isModifiesPIdentIdent(PROC_NAME procName, VAR_NAME varName);

	//Table Evaluation
	static STMT_LIST getModifiesSEntAny(STMT_TYPE type);
	static TABLE getModifiesSEntIdent(STMT_TYPE type, VAR_NAME varName);
	static LIST_OF_VARIABLE_NAME getModifiesSIdentEnt(STMT_NO stmtNo);
	static TABLE getModifiesSEntEnt(STMT_TYPE type);

	static LIST_OF_PROC_NAME getModifiesPEntAny();
	static LIST_OF_PROC_NAME getModifiesPEntIdent(VAR_NAME varName);
	static LIST_OF_VARIABLE_NAME getModifiesPIdentEnt(PROC_NAME procName);
	static TABLE getModifiesPEntEnt();

	// Clear
	static void clear();

private:
	static TABLE  modifiesStmtTable;
	static TABLE modifiesProcTable;
};