#pragma once
#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBConstant {
public:

	static bool setConstant(CONST_VAL constVal);
	static CONST_LIST getConstants();
	// Clear
	static bool clear();

private:
	static TABLE constantTable;
};