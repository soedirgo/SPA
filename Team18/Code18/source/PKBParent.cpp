#include "PKBParent.h"
#include <system_error>

using namespace std;

unordered_set<vector<string>, VectorDoubleStringHash> PKBParent::parentTable;
unordered_set<vector<string>, VectorDoubleStringHash> PKBParent::parentStarTable;

bool PKBParent::setParent(STMT_NO parent, STMT_NO child) {
	vector<string> tuple = vector<string>();
	tuple.push_back(parent);
	tuple.push_back(child);
	parentTable.emplace(tuple);
	return true;
}

bool PKBParent::setParentStar(STMT_NO parent, STMT_NO child) {
	vector<string> tuple = vector<string>();
	tuple.push_back(parent);
	tuple.push_back(child);
	parentStarTable.emplace(tuple);
	return true;
}

STMT_LIST PKBParent::getChild(STMT_NO parent) {
	STMT_LIST list;
	for (auto vectorIter : parentTable) {
		vector<string> tuple = vector<string>();
		if (vectorIter.front() == parent) {
			tuple.push_back(vectorIter.back());
			list.emplace(tuple);
		}
	}
	return list;
}

STMT_NO PKBParent::getParent(STMT_NO child) {
	for (auto vectorIter : parentTable) {
		vector<string> tuple = vector<string>();
		if (vectorIter.back() == child) {
			return vectorIter.front();
		}
	}
	return "";
}

bool PKBParent::isParentExist(STMT_NO child) {
	STMT_NO parent = getParent(child);
	if (parent == "") {
		return false;
	}
	return true;
}

bool PKBParent::isParentRelationship(STMT_NO parent, STMT_NO child) {

	for (auto vectorIter : parentTable) {
		if (vectorIter.front() == parent) {
			if (vectorIter.back() == child) {
				return true;
			}
		}
	}
	return false;
}

bool PKBParent::isParentStarRelationship(STMT_NO parent, STMT_NO child) {

	for (auto vectorIter : parentStarTable) {
		if (vectorIter.front() == parent) {
			if (vectorIter.back() == child) {
				return true;
			}
		}
	}
	return false;
}

unordered_set<vector<string>, VectorDoubleStringHash> PKBParent::getParentTable() {
	return parentTable;
}

bool PKBParent::clear() {
	parentTable.clear();
	parentStarTable.clear();
	return true;
}