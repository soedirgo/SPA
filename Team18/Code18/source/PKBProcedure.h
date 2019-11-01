#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBProcedure {
public:
	static PROC_LIST getProcedures();
	static bool setProcedure(PROC_NAME procName, STMT_NO start, STMT_NO end, STMT_NO endAlt);
	static STMT_LIST getProcedureStartEnd(PROC_NAME procName);

	// Clear
	static bool clear();

private:
	static TABLE procedureTable;
};