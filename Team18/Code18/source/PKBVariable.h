#pragma once
#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBVariable {
public:

	static bool setVar(VAR_NAME varName);
	static VAR_LIST getVariable();

	// Clear
	static bool clear();

private:
	static TABLE varTable;
};