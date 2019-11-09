#pragma once
#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBConstant {
public:

	static bool setConstant(CONST_VAL constVal);
	static LIST_OF_CONS_VAL getConstants();
	// Clear
	static void clear();

private:
	static TABLE constantTable;
};