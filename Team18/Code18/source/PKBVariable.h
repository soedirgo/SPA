#pragma once
#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBVariable {
public:

	static bool setVariable(VAR_NAME varName);
	static LIST_OF_VARIABLE_NAME getVariables();

	// Clear
	static void clear();

private:
	static TABLE varTable;
};