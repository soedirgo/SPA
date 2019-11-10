#pragma once
#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBVariable {
public:

	static void setVariable(VAR_NAME varName);
	static LIST_OF_VAR_NAME getVariables();

	// Clear
	static void clear();

private:
	static TABLE varTable;
};