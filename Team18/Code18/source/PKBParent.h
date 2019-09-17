#pragma once

#include <unordered_set>
#include <unordered_map>
#include <string>

class PKBParent {
public:

	// add parent to parentTable
	static bool setParentByChild(int parent, int child);
	static bool setChildrenByParent(int parent, int child);

	// GETTERS
	static int getParentStmt(int stmtNo);
	static std::unordered_set<int> getChildrenStmtList(int stmtNo);

	// Boolean Check
	static bool isParentExist(int stmtNo);
	static bool isChildrenExist(int stmtNo);

	static bool isParentRelationship(int parent, int child);

	// Clear
	bool clear();

private:
	static std::unordered_map<int, int> parentTable;
	static std::unordered_map<int, std::unordered_set<int>> childTable;
};