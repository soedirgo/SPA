#include "PKBNext.h"
#include <system_error>

using namespace std;

unordered_set<vector<string>, VectorDoubleStringHash> PKBNext::nextTable;
unordered_set<vector<string>, VectorDoubleStringHash> PKBNext::nextStarTable;

bool PKBNext::setNext(PROG_LINE nextByLine, PROG_LINE nextLine) {
	vector<string> tuple = vector<string>();
	tuple.push_back(nextByLine);
	tuple.push_back(nextLine);
	nextTable.emplace(tuple);
	return true;
}

bool PKBNext::setNextStar(PROG_LINE nextByLine, PROG_LINE nextLine) {
	vector<string> tuple = vector<string>();
	tuple.push_back(nextByLine);
	tuple.push_back(nextLine);
	nextStarTable.emplace(tuple);
	return true;
}

LINE_LIST PKBNext::getNext(PROG_LINE nextByLine) {
	LINE_LIST list;
	for (auto vectorIter : nextTable) {
		vector<string> tuple = vector<string>();
		if (vectorIter.front() == nextByLine) {
			tuple.push_back(vectorIter.back());
			list.emplace(tuple);
		}
	}
	return list;
}

bool PKBNext::isNextRelationship(PROG_LINE nextByLine, PROG_LINE nextLine) {

	for (auto vectorIter : nextTable) {
		if (vectorIter.front() == nextByLine) {
			if (vectorIter.back() == nextLine) {
				return true;
			}
		}
	}
	return false;
}

bool PKBNext::isNextStarRelationship(PROG_LINE nextByLine, PROG_LINE nextLine) {

	for (auto vectorIter : nextStarTable) {
		if (vectorIter.front() == nextByLine) {
			if (vectorIter.back() == nextLine) {
				return true;
			}
		}
	}
	return false;
}

unordered_set<vector<string>, VectorDoubleStringHash> PKBNext::getNextTable() {
	return nextTable;
}

bool PKBNext::clear() {
	nextTable.clear();
	nextStarTable.clear();
	return true;
}
