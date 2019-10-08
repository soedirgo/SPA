#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBNext {
public:

	static bool setNext(PROG_LINE n1, PROG_LINE n2);
	static bool setNextStar(PROG_LINE n1, PROG_LINE n2);

	static bool isNextRelationship(PROG_LINE n1, PROG_LINE n2);
	static bool isNextStarRelationship(PROG_LINE n1, PROG_LINE n2);

	// Clear
	bool clear();

private:
	static std::unordered_set<std::vector<std::string>, VectorDoubleStringHash> nextTable;
	static std::unordered_set<std::vector<std::string>, VectorDoubleStringHash> nextStarTable;
};