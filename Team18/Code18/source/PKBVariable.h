#pragma once
#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBVariable {
public:

	static bool setVariable(VAR_NAME varName);
	static VAR_LIST getVariables();

	// Clear
	static bool clear();

private:
	static TABLE varTable;
};