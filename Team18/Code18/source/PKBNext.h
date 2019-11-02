#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBNext {
public:

	static bool setNext(PROG_LINE nextByLine, PROG_LINE nextLine);
	static bool setNextT(PROG_LINE nextByLine, PROG_LINE nextLine);
	static bool setNextBip(PROG_LINE nextByLine, PROG_LINE nextLine);
	static bool setNextBipT(PROG_LINE nextByLine, PROG_LINE nextLine);
	static STMT_LIST getNext(PROG_LINE nextByLine);
	static STMT_LIST getNextBy(PROG_LINE nextLine);

	static TABLE getNextTable();
	static TABLE getNextTTable();
	static TABLE getNextBipTable();

	//Helper
	static bool isNextBipT(PROG_LINE n1, PROG_LINE n2);
	static bool isNextT(PROG_LINE nextByLine, PROG_LINE nextLine);

	//Bool Evaluation
	static bool isNextAnyAny();
	static bool isNextAnyIdent(PROG_LINE n2);
	static bool isNextIdentAny(PROG_LINE n1);
	static bool isNextIdentIdent(PROG_LINE n1, PROG_LINE n2);

	static bool isNextTAnyAny();
	static bool isNextTAnyIdent(PROG_LINE n2);
	static bool isNextTIdentAny(PROG_LINE n1);
	static bool isNextTIdentIdent(PROG_LINE n1, PROG_LINE n2);

	static bool isNextBipAnyAny();
	static bool isNextBipAnyIdent(PROG_LINE n2);
	static bool isNextBipIdentAny(PROG_LINE n1);
	static bool isNextBipIdentIdent(PROG_LINE n1, PROG_LINE n2);

	static bool isNextBipTAnyAny();
	static bool isNextBipTAnyIdent(PROG_LINE n2);
	static bool isNextBipTIdentAny(PROG_LINE n1);
	static bool isNextBipTIdentIdent(PROG_LINE n1, PROG_LINE n2);

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

	static TABLE getNextBipAnyEnt(STMT_TYPE stmtType);
	static TABLE getNextBipIdentEnt(PROG_LINE n1, STMT_TYPE stmtType);
	static TABLE getNextBipEntAny(STMT_TYPE stmtType);
	static TABLE getNextBipEntIdent(STMT_TYPE stmtType, PROG_LINE n2);
	static TABLE getNextBipEntEnt(STMT_TYPE stmtType1, STMT_TYPE stmtType2);

	static TABLE getNextBipTAnyEnt(STMT_TYPE stmtType);
	static TABLE getNextBipTIdentEnt(PROG_LINE n1, STMT_TYPE stmtType);
	static TABLE getNextBipTEntAny(STMT_TYPE stmtType);
	static TABLE getNextBipTEntIdent(STMT_TYPE stmtType, PROG_LINE n2);
	static TABLE getNextBipTEntEnt(STMT_TYPE stmtType1, STMT_TYPE stmtType2);
	static TABLE getNextBipTSelf(STMT_TYPE stmtType);

	// Clear
	static bool clear();

	// Clear Next*
	static bool clearNextT();

private:
	static TABLE nextTable;
	static TABLE nextTTable;
	static TABLE nextBipTable;
	static TABLE nextBipTTable;
};