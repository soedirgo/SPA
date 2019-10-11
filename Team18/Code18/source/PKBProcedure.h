#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBProcedure {
public:
	static PROC_LIST getProcedures();
	static bool setProcedure(PROC_NAME procName);

	// Clear
	static bool clear();

private:
	static TABLE procedureTable;
};