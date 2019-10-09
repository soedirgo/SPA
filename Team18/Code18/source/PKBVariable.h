#pragma once
#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBVariable {
public:

	static bool setVar(VAR_NAME varName);
	static VAR_LIST getAllVar();

	// Clear
	bool clear();

private:
	static std::unordered_set<std::vector<std::string>, VectorSingleStringHash> varTable;
};