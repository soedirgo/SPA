#pragma once

#include "AbstractType.h"
#include <unordered_set>
#include <string>

class DesignExtractor {
public:
	static void extractDesign();

private:
	static void extractFollowsT();
	static void extractParentT();
	static void extractCallsT();
	static void extractNextT();
	static void extractModifiesP();
	static void extractUsesP();
	static void extractAffects();
	static void extractAffectsT();
	static void extractUsesS();
	static void extractModifiesS();

	static void recurseAffects(STMT_NO a1, STMT_NO a2);
	static void recurseModifies(PROC_NAME p);
	static void recurseUses(PROC_NAME p);
	static void recurseCall(PROC_NAME p, PROC_NAME q);
	static void recurseParent(STMT_NO parent, STMT_NO child);
	static void recurseFollows(STMT_NO followedBy, STMT_NO follow);
	static void recurseNext(PROG_LINE n1, PROG_LINE n2);
};