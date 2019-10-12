#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBPattern {
public:

	static bool setIfUses(STMT_NO stmtNo, VAR_NAME varName);
	static bool isIfUsesRelationship(STMT_NO stmtNo, VAR_NAME varName);

	static bool setWhileUses(STMT_NO stmtNo, VAR_NAME varName);
	static bool isWhileUsesRelationship(STMT_NO stmtNo, VAR_NAME varName);

	// Clear
	static bool clear();

private:
	static TABLE ifUsesTable;
	static TABLE whileUsesTable;
};