#pragma once

#include <unordered_map>
#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBParent {
public:

	/*
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
	*/

	static bool setParent(STMT_NO parent, STMT_NO child);
	static bool setParentStar(STMT_NO parent, STMT_NO child);
	static std::unordered_set<std::string> getChild(STMT_NO parent);
	static std::unordered_set<std::vector<std::string>, VectorHash> getParentTable();
	static bool isParentRelationship(STMT_NO parent, STMT_NO child);
	static bool isParentStarRelationship(STMT_NO parent, STMT_NO child);

	// Clear
	bool clear();

private:
	/*
	static std::unordered_map<int, int> childTable;
	static std::unordered_map<int, std::unordered_set<int>> parentTable;
	static std::unordered_map<int, std::unordered_set<int>> parentStarTable;
	*/

	static std::unordered_set<std::vector<std::string>, VectorHash> parentTable;
	static std::unordered_set<std::vector<std::string>, VectorHash> parentStarTable;
};