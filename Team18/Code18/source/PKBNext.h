#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBNext {
public:

	static bool setNext(PROG_LINE nextByLine, PROG_LINE nextLine);
	static bool setNextStar(PROG_LINE nextByLine, PROG_LINE nextLine);
	static LINE_LIST getNext(PROG_LINE nextByLine);

	static bool isNextRelationship(PROG_LINE nextByLine, PROG_LINE nextLine);
	static bool isNextStarRelationship(PROG_LINE nextByLine, PROG_LINE nextLine);

	static std::unordered_set<std::vector<std::string>, VectorDoubleStringHash> getNextTable();

	static TABLE getAllNextByLineNextLineStmt();
	static TABLE getAllNextByLineStmt(PROG_LINE progLine);
	static TABLE getAllNextLineStmt(PROG_LINE progLine);
	static TABLE getAllNextByLineNextLineStarStmt();
	static TABLE getAllNextByLineStarStmt(PROG_LINE progLine);
	static TABLE getAllNextLineStarStmt(PROG_LINE progLine);

	// Clear
	static bool clear();

private:
	static TABLE getResultTableGenericBoth(TABLE tableName);
	static TABLE getResultTableGenericLeft(PROG_LINE progLine, TABLE tableName);
	static TABLE getResultTableGenericRight(PROG_LINE progLine, TABLE tableName);
	static std::unordered_set<std::vector<std::string>, VectorDoubleStringHash> nextTable;
	static std::unordered_set<std::vector<std::string>, VectorDoubleStringHash> nextStarTable;
};