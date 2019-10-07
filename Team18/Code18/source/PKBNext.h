#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBNext {
public:

	static bool setNext(PROG_LINE n1, PROG_LINE n2);
	//static bool isModifiesStmtRelationship(STMT_NO stmtNo, VAR_NAME varName);

	// Clear
	bool clear();

private:
	static std::unordered_set<std::vector<std::string>, VectorHash> nextTable;
};