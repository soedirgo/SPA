#pragma once

#include "AbstractType.h"
#include <unordered_set>
#include <string>

class DesignExtractor {
public:
	static void extractDesign();
	static void extractNextT();

	static void affectsAll();
	static void affectedBy(STMT_NO a1);
	static void isAffecting(STMT_NO a2);
	static void isAffects(STMT_NO a1, STMT_NO a2);
	static void affectsTAll();
	static void affectedTBy(STMT_NO a1);
	static void isAffectingT(STMT_NO a2);
	static void isAffectsT(STMT_NO a1, STMT_NO a2);
	static void isAffectsSelf();
	static void isAffectsTSelf();

private:
	static void extractFollowsT();
	static void extractParentT();
	static void extractCallsT();
	static void extractModifiesP();
	static void extractUsesP();
	static void extractUsesS();
	static void extractModifiesS();
	static void extractNextBip();
	static void extractNextBipT();

	static bool traverseAffects(STMT_NO a1, STMT_NO a2, VAR_NAME v);
	static bool recurseAffectsT(STMT_NO a1, STMT_NO a2);
	static void recurseModifies(PROC_NAME p);
	static void recurseUses(PROC_NAME p);
	static void recurseCall(PROC_NAME p, PROC_NAME q);
	static void recurseParent(STMT_NO parent, STMT_NO child);
	static void recurseFollows(STMT_NO followedBy, STMT_NO follow);
	static void recurseNext(PROG_LINE n1, PROG_LINE n2);
	static void recurseNextBipT(PROG_LINE n1, PROG_LINE n2);
};