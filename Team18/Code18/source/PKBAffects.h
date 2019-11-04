#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include "DesignExtractor.h"
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
	static bool isCheckedAffectsIdentIdent(STMT_NO a1, STMT_NO a2);
	static bool isCheckedAffects(STMT_NO a1, STMT_NO a2);
	static bool setCheckedAffects(STMT_NO a1, STMT_NO a2);

	static bool isAffectsTAnyAny();
	static bool isAffectsTAnyIdent(STMT_NO a2);
	static bool isAffectsTIdentAny(STMT_NO a1);
	static bool isAffectsTIdentIdent(STMT_NO a1, STMT_NO a2);
	static bool isCheckedAffectsTIdentIdent(STMT_NO a1, STMT_NO a2);
	static bool isCheckedAffectsT(STMT_NO a1, STMT_NO a2);
	static bool setCheckedAffectsT(STMT_NO a1, STMT_NO a2);

	//Table Evaluation
	static STMT_LIST getAffectsAnyEnt();
	static STMT_LIST getAffectsIdentEnt(STMT_NO a1);
	static STMT_LIST getAffectsEntAny();
	static STMT_LIST getAffectsEntIdent(STMT_NO a2);
	static TABLE getAffectsEntEnt();
	static STMT_LIST getAffectsSelf();

	static STMT_LIST getAffectsTAnyEnt();
	static STMT_LIST getAffectsTIdentEnt(STMT_NO a1);
	static STMT_LIST getAffectsTEntAny();
	static STMT_LIST getAffectsTEntIdent(STMT_NO a2);
	static TABLE getAffectsTEntEnt();
	static STMT_LIST getAffectsTSelf();

	// Clear
	static bool clear();

private:
	static TABLE affectsChecked;
	static TABLE affectsTChecked;
	static TABLE affectsTable;
	static TABLE affectsTTable;
};