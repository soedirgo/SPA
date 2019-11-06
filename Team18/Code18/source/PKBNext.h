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
	static STMT_LIST getNextBip(PROG_LINE nextLine);

	static TABLE getNextTable();
	static TABLE getNextTTable();
	static TABLE getNextBipTable();
	static TABLE getNextBipTTable();

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
	static LINE_LIST getNextAnyEnt(STMT_TYPE stmtType);
	static LINE_LIST getNextIdentEnt(PROG_LINE n1, STMT_TYPE stmtType);
	static LINE_LIST getNextEntAny(STMT_TYPE stmtType);
	static LINE_LIST getNextEntIdent(STMT_TYPE stmtType,PROG_LINE n2);
	static TABLE getNextEntEnt(STMT_TYPE stmtType1, STMT_TYPE stmtType2);

	static LINE_LIST getNextTAnyEnt(STMT_TYPE stmtType);
	static LINE_LIST getNextTIdentEnt(PROG_LINE n1, STMT_TYPE stmtType);
	static LINE_LIST getNextTEntAny(STMT_TYPE stmtType);
	static LINE_LIST getNextTEntIdent(STMT_TYPE stmtType, PROG_LINE n2);
	static TABLE getNextTEntEnt(STMT_TYPE stmtType1, STMT_TYPE stmtType2);
	static LINE_LIST getNextTSelf(STMT_TYPE stmtType);

	static LINE_LIST getNextBipAnyEnt(STMT_TYPE stmtType);
	static LINE_LIST getNextBipIdentEnt(PROG_LINE n1, STMT_TYPE stmtType);
	static LINE_LIST getNextBipEntAny(STMT_TYPE stmtType);
	static LINE_LIST getNextBipEntIdent(STMT_TYPE stmtType, PROG_LINE n2);
	static TABLE getNextBipEntEnt(STMT_TYPE stmtType1, STMT_TYPE stmtType2);

	static LINE_LIST getNextBipTAnyEnt(STMT_TYPE stmtType);
	static LINE_LIST getNextBipTIdentEnt(PROG_LINE n1, STMT_TYPE stmtType);
	static LINE_LIST getNextBipTEntAny(STMT_TYPE stmtType);
	static LINE_LIST getNextBipTEntIdent(STMT_TYPE stmtType, PROG_LINE n2);
	static TABLE getNextBipTEntEnt(STMT_TYPE stmtType1, STMT_TYPE stmtType2);
	static LINE_LIST getNextBipTSelf(STMT_TYPE stmtType);

	// Clear
	static bool clear();

	// Clear Next*
	static bool clearCache();

private:
	static TABLE nextTable;
	static TABLE nextTTable;
	static TABLE nextBipTable;
	static TABLE nextBipTTable;
};