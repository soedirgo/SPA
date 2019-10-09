#include "PKBNext.h"

using namespace std;
unordered_set<vector<string>, VectorDoubleStringHash> PKBNext::nextTable;
unordered_set<vector<string>, VectorDoubleStringHash> PKBNext::nextStarTable;

bool PKBNext::setNext(PROG_LINE n1, PROG_LINE n2) {
	vector<string> tuple = vector<string>();
	tuple.push_back(n1);
	tuple.push_back(n2);
	nextTable.emplace(tuple);
	return true;
}

bool PKBNext::setNextStar(PROG_LINE n1, PROG_LINE n2) {
	vector<string> tuple = vector<string>();
	tuple.push_back(n1);
	tuple.push_back(n2);
	nextStarTable.emplace(tuple);
	return true;
}

bool PKBNext::isNextRelationship(PROG_LINE n1, PROG_LINE n2) {
	for (auto vectorIter : nextTable) {
		if (vectorIter.front() == n1) {
			if (vectorIter.back() == n2) {
				return true;
			}
		}
	}
	return false;
}

bool PKBNext::isNextStarRelationship(PROG_LINE n1, PROG_LINE n2) {
	for (auto vectorIter : nextStarTable) {
		if (vectorIter.front() == n1) {
			if (vectorIter.back() == n2) {
				return true;
			}
		}
	}
	return false;
}

bool PKBNext::clear() {
	nextTable.clear();
	nextStarTable.clear();
	return true;
}