#pragma once

#include "AbstractType.h"
#include <unordered_set>

class PKBProcedure {
public:

	static std::unordered_set<std::string> getAllProc();
	static bool setProc(std::string procName);

	// Clear
	bool clear();

private:
	static std::unordered_set<std::string> procedureTable;
};