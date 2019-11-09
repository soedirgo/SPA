#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBPattern {
public:

	static bool setIfPattern(STMT_NO stmtNo, VAR_NAME varName);
	static bool setWhilePattern(STMT_NO stmtNo, VAR_NAME varName);
	static bool setAssignPattern(STMT_NO stmtNo, EXPR_SPEC pattern);

	//Pattern Evaluation

	static STMT_LIST getPatternIfAny();
	static STMT_LIST getPatternIfIdent(VAR_NAME varName);
	static TABLE getPatternIfEnt();

	//Debugging
	static TABLE getAssignPatternTable();

	static STMT_LIST getPatternWhileAny();
	static STMT_LIST getPatternWhileIdent(VAR_NAME varName);
	static TABLE getPatternWhileEnt();

	static STMT_LIST getPatternAssignAnyAny();
	static STMT_LIST getPatternAssignAnyPartial(EXPR_SPEC expression);
	static STMT_LIST getPatternAssignAnyFull(EXPR_SPEC expression);
	static STMT_LIST getPatternAssignIdentAny(VAR_NAME varName);
	static STMT_LIST getPatternAssignIdentPartial(VAR_NAME varName, EXPR_SPEC expression);
	static STMT_LIST getPatternAssignIdentFull(VAR_NAME varName, EXPR_SPEC expression);
	static TABLE getPatternAssignEntAny();
	static TABLE getPatternAssignEntPartial(EXPR_SPEC expression);
	static TABLE getPatternAssignEntFull(EXPR_SPEC expression);

	// Clear
	static void clear();

private:
	static TABLE patternIfTable;
	static TABLE patternWhileTable;
	static TABLE patternAssignTable;
};