#include "PKBParent.h"
#include <system_error>

using namespace std;

unordered_map<int, int> PKBParent::parentTable;
unordered_map<int, std::unordered_set<int>>  PKBParent::childTable;
unordered_map<int, std::unordered_set<int>>  PKBParent::parentStarTable;


bool PKBParent::setParent(int parent, int child) {
	parentTable[child] = parent;
	return true;
}

bool PKBParent::setChildren(int parent, int child) {
	try {
		unordered_set<int> stmtList = getChildrenStmtList(parent);
		stmtList.emplace(child);
		childTable[parent] = stmtList;
		return true;
	}
	catch (errc e) {
		return false;
	}
}

bool PKBParent::setParentStar(int parent, int child) {
	try {
		unordered_set<int> stmtList = getParentStarStmtList(child);
		stmtList.emplace(parent);
		parentStarTable[child] = stmtList;
		return true;
	}
	catch (errc e) {
		return false;
	}
}

int PKBParent::getParentStmt(int child) {
	return parentTable[child];
}

unordered_set<int> PKBParent::getChildrenStmtList(int parent) {
	return childTable[parent];
}

unordered_set<int> PKBParent::getParentStarStmtList(int child) {
	return parentStarTable[child];
}

bool PKBParent::isParentExist(int stmtNo) {
	return parentTable.find(stmtNo) != parentTable.end();
}

bool PKBParent::isParentRelationship(int parent, int child) {
	unordered_set<int> stmtList = getChildrenStmtList(parent);
	for (auto keyValue : stmtList) {
		if (keyValue==child) {
			return true;
		}
	}
	return false;
}

bool PKBParent::isParentStarRelationship(int parent, int child) {
	unordered_set<int> stmtList = getParentStarStmtList(child);
	for (auto keyValue : stmtList) {
		if (keyValue == parent) {
			return true;
		}
	}
	return false;
}

bool PKBParent::isChildrenExist(int stmtNo) {
	return childTable.find(stmtNo) != childTable.end();
	//return false
}

bool PKBParent::clear() {
	parentTable.clear();
	return true;
}