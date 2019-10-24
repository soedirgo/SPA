#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBPrint {
public:
	static bool setPrint(VAR_NAME varName);
	static VAR_LIST getAllPrintVar();
	// Clear
	static bool clear();

private:
	static TABLE printTable;
};