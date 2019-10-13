#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBNext {
public:

	static bool setNext(PROG_LINE nextByLine, PROG_LINE nextLine);
	static bool setNextT(PROG_LINE nextByLine, PROG_LINE nextLine);
	static LINE_LIST getNext(PROG_LINE nextByLine);

	static TABLE getNextTable();
	static TABLE getNextTTable();

	//Bool Evaluation
	static bool isNextAnyAny();
	static bool isNextAnyIdent(PROG_LINE n2);
	static bool isNextIdentAny(PROG_LINE n1);
	static bool isNextIdentIdent(PROG_LINE n1, PROG_LINE n2);

	static bool isNextTAnyAny();
	static bool isNextTAnyIdent(PROG_LINE n2);
	static bool isNextTIdentAny(PROG_LINE n1);
	static bool isNextTIdentIdent(PROG_LINE n1, PROG_LINE n2);

	//Table Evaluation
	static TABLE getNextAnyEnt(STMT_TYPE stmtType);
	static TABLE getNextIdentEnt(PROG_LINE n1, STMT_TYPE stmtType);
	static TABLE getNextEntAny(STMT_TYPE stmtType);
	static TABLE getNextEntIdent(STMT_TYPE stmtType,PROG_LINE n2);
	static TABLE getNextEntEnt(STMT_TYPE stmtType1, STMT_TYPE stmtType2);

	static TABLE getNextTAnyEnt(STMT_TYPE stmtType);
	static TABLE getNextTIdentEnt(PROG_LINE n1, STMT_TYPE stmtType);
	static TABLE getNextTEntAny(STMT_TYPE stmtType);
	static TABLE getNextTEntIdent(STMT_TYPE stmtType, PROG_LINE n2);
	static TABLE getNextTEntEnt(STMT_TYPE stmtType1, STMT_TYPE stmtType2);
	static TABLE getNextTSelf(STMT_TYPE stmtType);

	// Clear
	static bool clear();

private:
	static TABLE nextTable;
	static TABLE nextTTable;
};