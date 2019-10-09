#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBProcedure {
public:
	static PROC_LIST getAllProc();
	static bool setProc(PROC_NAME procName);

	// Clear
	static bool clear();

private:
	static std::unordered_set<std::vector<std::string>, VectorSingleStringHash> procedureTable;
};