#include "PKBParent.h"
#include <system_error>

using namespace std;

unordered_map<int, int> PKBParent::childTable;
unordered_map<int, std::unordered_set<int>>  PKBParent::parentTable;
unordered_map<int, std::unordered_set<int>>  PKBParent::parentStarTable;


bool PKBParent::setParent(int parent, int child) {
	childTable[child] = parent;
	return true;
}

bool PKBParent::setChildren(int parent, int child) {
	try {
		unordered_set<int> stmtList = getChildrenStmtList(parent);
		stmtList.emplace(child);
		parentTable[parent] = stmtList;
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

unordered_set<int> PKBParent::getAllParent() {
	unordered_set<int> parentList;
	for (auto keyValue : parentTable) {
		parentList.emplace(keyValue.first);
	}
	return parentList;
}

unordered_set<int> PKBParent::getAllChildren() {
	unordered_set<int> childrenList;
	for (auto keyValue : childTable) {
		childrenList.emplace(keyValue.first);
	}
	return childrenList;
}

int PKBParent::getParentStmt(int child) {
	return childTable[child];
}

unordered_set<int> PKBParent::getChildrenStmtList(int parent) {
	return parentTable[parent];
}

unordered_set<int> PKBParent::getParentStarStmtList(int child) {
	return parentStarTable[child];
}

bool PKBParent::isParentExist(int stmtNo) {
	return childTable.find(stmtNo) != childTable.end();
}

bool PKBParent::isParentRelationship(int parent, int child) {
	if (parent == getParentStmt(child)) {
		return true;
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
	return parentTable.find(stmtNo) != parentTable.end();
	//return false
}

bool PKBParent::clear() {
	childTable.clear();
	parentTable.clear();
	parentStarTable.clear();
	return true;
}