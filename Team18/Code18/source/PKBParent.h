#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBParent {
public:

	static void setParent(STMT_NO parent, STMT_NO child);
	static void setParentT(STMT_NO parent, STMT_NO child);

	//Bool Evaluation
	static bool isParentAnyAny();
	static bool isParentAnyIdent(STMT_NO s2);
	static bool isParentIdentAny(STMT_NO s1);
	static bool isParentIdentIdent(STMT_NO s1, STMT_NO s2);

	static bool isParentTAnyAny();
	static bool isParentTAnyIdent(STMT_NO s2);
	static bool isParentTIdentAny(STMT_NO s1);
	static bool isParentTIdentIdent(STMT_NO s1, STMT_NO s2);

	//Table Evaluation
	static STMT_LIST getParentAnyEnt(STMT_TYPE s2);
	static STMT_LIST getParentIdentEnt(STMT_NO s1, STMT_TYPE s2);
	static STMT_LIST getParentEntAny(STMT_TYPE s1);
	static STMT_LIST getParentEntIdent(STMT_TYPE s1, STMT_NO s2);
	static TABLE getParentEntEnt(STMT_TYPE s1, STMT_TYPE s2);

	static STMT_LIST getParentTAnyEnt(STMT_TYPE s2);
	static STMT_LIST getParentTIdentEnt(STMT_NO s1, STMT_TYPE s2);
	static STMT_LIST getParentTEntAny(STMT_TYPE s1);
	static STMT_LIST getParentTEntIdent(STMT_TYPE s1, STMT_NO s2);
	static TABLE getParentTEntEnt(STMT_TYPE s1, STMT_TYPE s2);
	// Clear
	static void clear();

private:
	static TABLE parentTable;
	static TABLE parentTTable;
};