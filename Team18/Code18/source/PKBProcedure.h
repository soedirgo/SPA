#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>
#include <unordered_map>

class PKBProcedure {
public:
	static LIST_OF_PROC_NAME getProcedures();
	static bool setProcByStmt(STMT_NO stmtNo, PROC_NAME proc);
	static PROC_NAME getProcByStmt(STMT_NO stmtNo);
	static bool setProcedure(PROC_NAME procName, STMT_NO start, STMT_LIST end);
	static TABLE getProcedureTable();
	static STMT_LIST getProcedureStartEnd(PROC_NAME procName);

	// Clear
	static void clear();

private:
	static HASHMAP procByStmtTable;
	static TABLE procedureTable;
	static TABLE procedureStartEndTable;
};