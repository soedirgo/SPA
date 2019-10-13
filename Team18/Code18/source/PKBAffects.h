#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBAffects {
public:

	static bool setAffects(STMT_NO a1, STMT_NO a2);
	static bool setAffectsT(STMT_NO a1, STMT_NO a2);

	//Bool Evaluation
	static bool isAffectsAnyAny();
	static bool isAffectsAnyIdent(STMT_NO a2);
	static bool isAffectsIdentAny(STMT_NO a1);
	static bool isAffectsIdentIdent(STMT_NO a1, STMT_NO a2);

	static bool isAffectsTAnyAny();
	static bool isAffectsTAnyIdent(STMT_NO a2);
	static bool isAffectsTIdentAny(STMT_NO a1);
	static bool isAffectsTIdentIdent(STMT_NO a1, STMT_NO a2);

	//Table Evaluation
	static TABLE getAffectsAnyEnt();
	static TABLE getAffectsIdentEnt(STMT_NO a1);
	static TABLE getAffectsEntAny();
	static TABLE getAffectsEntIdent(STMT_NO a2);
	static TABLE getAffectsEntEnt();
	static TABLE getAffectsSelf();

	/*
	static TABLE getAffectsTAnyEnt();
	static TABLE getAffectsTIdentEnt(STMT_NO a1);
	static TABLE getAffectsTEntAny();
	static TABLE getAffectsTEntIdent(STMT_NO a2);
	static TABLE getAffectsTEntEnt();
	static TABLE getAffectsTSelf();
	*/

	// Clear
	static bool clear();

private:
	static TABLE affectsTable;
	static TABLE affectsTTable;
};