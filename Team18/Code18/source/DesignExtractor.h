#pragma once

#include "AbstractType.h"
#include <unordered_set>
#include <string>

class DesignExtractor {
public:
	static void extractDesign();

private:
	static void extractFollowsStar();
	static void extractParentStar();
	static void extractCallStar();
	static void extractNextStar();
	static void extractModifiesP();
	static void extractUsesP();
	static void extractAffects();

	static void recurseModifies(PROC_NAME p);
	static void recurseUses(PROC_NAME p);
	static void recurseCall(PROC_NAME p, PROC_NAME q);
	static void recurseParent(STMT_NO parent, STMT_NO child);
	static void recurseFollows(STMT_NO followedBy, STMT_NO follow);
	static void recurseNext(PROG_LINE n1, PROG_LINE n2);
};