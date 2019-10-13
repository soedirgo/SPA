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
	static TABLE getNextAnyEnt();
	static TABLE getNextIdentEnt(PROG_LINE n1);
	static TABLE getNextEntAny();
	static TABLE getNextEntIdent(PROG_LINE n2);
	static TABLE getNextEntEnt();

	static TABLE getNextTAnyEnt();
	static TABLE getNextTIdentEnt(PROG_LINE n1);
	static TABLE getNextTEntAny();
	static TABLE getNextTEntIdent(PROG_LINE n2);
	static TABLE getNextTEntEnt();
	static TABLE getNextTSelf();

	// Clear
	static bool clear();

private:
	static TABLE nextTable;
	static TABLE nextTTable;
};