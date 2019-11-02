#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>
#include <unordered_map>

class PKBProcedure {
public:
	static PROC_LIST getProcedures();
	static bool setProcByStmt(STMT_NO stmtNo, PROC_NAME proc);
	static PROC_NAME getProcByStmt(STMT_NO stmtNo);
	static bool setProcedure(PROC_NAME procName, STMT_NO start, STMT_LIST end);
	//static bool setProcedureStartEnd(PROC_NAME procName, STMT_NO start, STMT_NO end);
	static TABLE getProcedureTable();
	static STMT_LIST getProcedureStartEnd(PROC_NAME procName);
	//static TABLE getProcedureStartEndTable();

	// Clear
	static bool clear();

private:
	static HASHMAP procByStmtTable;
	static TABLE procedureTable;
	static TABLE procedureStartEndTable;
};