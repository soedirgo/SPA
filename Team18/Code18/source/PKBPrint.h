#pragma once

#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBPrint {
public:
	static bool setPrint(STMT_NO stmtNo, VAR_NAME varName);
	//static bool isCallStarRelationship(PROC_NAME caller, PROC_NAME callee);

	//static std::unordered_set<std::vector<std::string>, VectorHash> getCallProcTable();
	static std::unordered_set<std::string> getPrintVar(STMT_NO stmtNo);
	// Clear
	bool clear();

private:
	static std::unordered_set<std::vector<std::string>, VectorHash> printTable;
};