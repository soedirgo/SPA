#pragma once

#include "AbstractType.h"
#include <unordered_set>
#include <string>

class DesignExtractor {
public:
	static void extractDesign();

	static void extractNextT(STMT_LIST n1, STMT_LIST n2);
	static void affectsAll();
	static void affectsAny();
	static void isAnyAffectedBy(STMT_NO a1);
	static void isAnyAffecting(STMT_NO a2);
	static void affectedBy(STMT_NO a1);
	static void isAffecting(STMT_NO a2);
	static bool isAffects(STMT_NO a1, STMT_NO a2);
	static void affectsTAll();
	static void affectsTAny();
	static void isAnyAffectedTBy(STMT_NO a1);
	static void isAnyAffectingT(STMT_NO a2);
	static void affectedTBy(STMT_NO a1);
	static void isAffectingT(STMT_NO a2);
	static bool isAffectsT(STMT_NO a1, STMT_NO a2);
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
	static void extractAffectsBip();
	static void extractAffectsBipT();

	static bool traverseAffects(STMT_NO a1, STMT_NO a2, VAR_NAME v);
	static void traverseAffectsAll(STMT_NO a1, VAR_NAME v);
	static bool traverseAffectsAny(STMT_NO a1, VAR_NAME v);
	static bool recurseAffectsT(STMT_NO a1, STMT_NO a2);
	static void recurseAffectsTAll(STMT_NO a1);
	static bool recurseAffectsTAny(STMT_NO a1);
	static void traverseAffectsBipAll(STMT_NO a1, VAR_NAME v);
	static void recurseAffectsBipTAll(STMT_NO a1);
	static void recurseModifies(PROC_NAME p);
	static void recurseUses(PROC_NAME p);
	static void recurseCall(PROC_NAME p, PROC_NAME q);
	static void recurseParent(STMT_NO parent, STMT_NO child);
	static void recurseFollows(STMT_NO followedBy, STMT_NO follow);
	static void recurseNext(PROG_LINE n1, PROG_LINE n2, std::unordered_set<std::string> visited );
	static void recurseNextReverse(PROG_LINE n1, PROG_LINE n2, std::unordered_set<std::string> visited );
	static void recurseNextBipT(PROG_LINE n1, PROG_LINE n2);
	static void recurseNextBip(PROC_NAME p, TABLE callTable);
	static void recurseProcedure(STMT_NO nextStmt, PROC_NAME callee, TABLE callTable);
};