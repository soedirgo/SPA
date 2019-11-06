#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include "DesignExtractor.h"
#include <unordered_set>

class PKBAffects {
public:
	static bool setAffects(STMT_NO a1, STMT_NO a2);
	static bool setAffectsT(STMT_NO a1, STMT_NO a2);
	static bool setAffectsBip(STMT_NO a1, STMT_NO a2);
	static bool setAffectsBipT(STMT_NO a1, STMT_NO a2);

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

	static bool isAffectsBipAnyAny();
	static bool isAffectsBipAnyIdent(STMT_NO a2);
	static bool isAffectsBipIdentAny(STMT_NO a1);
	static bool isAffectsBipIdentIdent(STMT_NO a1, STMT_NO a2);

	static bool isAffectsBipTAnyAny();
	static bool isAffectsBipTAnyIdent(STMT_NO a2);
	static bool isAffectsBipTIdentAny(STMT_NO a1);
	static bool isAffectsBipTIdentIdent(STMT_NO a1, STMT_NO a2);

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

	static STMT_LIST getAffectsBipAnyEnt();
	static STMT_LIST getAffectsBipIdentEnt(STMT_NO a1);
	static STMT_LIST getAffectsBipEntAny();
	static STMT_LIST getAffectsBipEntIdent(STMT_NO a2);
	static TABLE getAffectsBipEntEnt();
	static STMT_LIST getAffectsBipSelf();

	static STMT_LIST getAffectsBipTAnyEnt();
	static STMT_LIST getAffectsBipTIdentEnt(STMT_NO a1);
	static STMT_LIST getAffectsBipTEntAny();
	static STMT_LIST getAffectsBipTEntIdent(STMT_NO a2);
	static TABLE getAffectsBipTEntEnt();
	static STMT_LIST getAffectsBipTSelf();

	// Clear
	static bool clear();

private:
	static TABLE affectsChecked;
	static TABLE affectsTChecked;
	static TABLE affectsTable;
	static TABLE affectsTTable;
	static TABLE affectsBipTable;
	static TABLE affectsBipTTable;
};