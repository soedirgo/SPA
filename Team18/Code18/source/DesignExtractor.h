#pragma once

#include "AbstractType.h"
#include <unordered_set>
#include <unordered_map>
#include <string>

class DesignExtractor {
public:
	static void extractDesign();

private:
	static void extractFollowsStar();
	static void extractParentStar();
	static void extractCallStar();
	static void extractModifiesProc();
	static void extractUsesProc();

	static void recurseCall(PROC_NAME p, PROC_NAME q);
	static void recurseParent(STMT_NO parent, STMT_NO child);
	static void recurseFollows(STMT_NO followedBy, STMT_NO follow);
};