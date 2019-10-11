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

	static TABLE getNextTable();

	static TABLE getAllNextByLineNextLineStmt();
	static LINE_LIST getAllNextByLineStmt(PROG_LINE progLine);
	static LINE_LIST getAllNextLineStmt(PROG_LINE progLine);
	static TABLE getAllNextByLineNextLineStarStmt();
	static LINE_LIST getAllNextByLineStarStmt(PROG_LINE progLine);
	static LINE_LIST getAllNextLineStarStmt(PROG_LINE progLine);

	// Clear
	static bool clear();

private:
	static TABLE getResultGenericBoth(TABLE tableName);
	static LINE_LIST getResultGenericLeft(PROG_LINE progLine, TABLE tableName);
	static LINE_LIST getResultGenericRight(PROG_LINE progLine, TABLE tableName);
	static TABLE nextTable;
	static TABLE nextStarTable;
};