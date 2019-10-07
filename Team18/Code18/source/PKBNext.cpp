#include "PKBNext.h"

using namespace std;
unordered_set<vector<string>, VectorHash> PKBNext::nextTable;
unordered_set<vector<string>, VectorHash> PKBNext::nextStarTable;

bool PKBNext::setNext(PROG_LINE n1, PROG_LINE n2) {
	vector<string> tuple = vector<string>();
	tuple.push_back(to_string(n1));
	tuple.push_back(to_string(n2));
	nextTable.emplace(tuple);
	return true;
}

bool PKBNext::setNextStar(PROG_LINE n1, PROG_LINE n2) {
	vector<string> tuple = vector<string>();
	tuple.push_back(to_string(n1));
	tuple.push_back(to_string(n2));
	nextStarTable.emplace(tuple);
	return true;
}

bool PKBNext::isNextRelationship(PROG_LINE n1, PROG_LINE n2) {
	for (auto vectorIter : nextTable) {
		if (vectorIter.front() == to_string(n1)) {
			if (vectorIter.back() == to_string(n2)) {
				return true;
			}
		}
	}
	return false;
}

bool PKBNext::isNextStarRelationship(PROG_LINE n1, PROG_LINE n2) {
	for (auto vectorIter : nextStarTable) {
		if (vectorIter.front() == to_string(n1)) {
			if (vectorIter.back() == to_string(n2)) {
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