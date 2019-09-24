#pragma once

#include <unordered_set>
#include <unordered_map>
#include <string>

class PKBParent {
public:

	// add parent to parentTable
	static bool setParent(int parent, int child);
	static bool setChildren(int parent, int child);
	static bool setParentStar(int parent, int child);

	// GETTERS
	static int getParentStmt(int child);
	static std::unordered_set<int> getParentStarStmtList(int child);
	static std::unordered_set<int> getChildrenStmtList(int parent);

	// Boolean Check
	static bool isParentExist(int stmtNo);
	static bool isChildrenExist(int stmtNo);

	static bool isParentRelationship(int parent, int child);
	static bool isParentStarRelationship(int parent, int child);
	// Clear
	bool clear();

	// Internal Use
	static std::unordered_set<int> getAllChildren();
	static std::unordered_set<int> getAllParent();

private:
	static std::unordered_map<int, int> childTable;
	static std::unordered_map<int, std::unordered_set<int>> parentTable;
	static std::unordered_map<int, std::unordered_set<int>> parentStarTable;
};