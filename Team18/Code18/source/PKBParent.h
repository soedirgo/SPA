#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBParent {
public:

	static bool setParent(STMT_NO parent, STMT_NO child);
	static bool setParentStar(STMT_NO parent, STMT_NO child);
	static STMT_LIST getChild(STMT_NO parent);
	static STMT_NO getParent(STMT_NO parent);
	static bool isParentExist(STMT_NO child);
	static TABLE getParentTable();

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
	static TABLE getParentAnyEnt(STMT_TYPE s2);
	static TABLE getParentIdentEnt(STMT_NO s1, STMT_TYPE s2);
	static TABLE getParentEntAny(STMT_TYPE s1);
	static TABLE getParentEntIdent(STMT_TYPE s1, STMT_NO s2);
	static TABLE getParentEntEnt(STMT_TYPE s1, STMT_TYPE s2);

	static TABLE getParentTAnyEnt(STMT_TYPE s2);
	static TABLE getParentTIdentEnt(STMT_NO s1, STMT_TYPE s2);
	static TABLE getParentTEntAny(STMT_TYPE s1);
	static TABLE getParentTEntIdent(STMT_TYPE s1, STMT_NO s2);
	static TABLE getParentTEntEnt(STMT_TYPE s1, STMT_TYPE s2);
	// Clear
	static bool clear();

private:
	static TABLE parentTable;
	static TABLE parentTTable;
};