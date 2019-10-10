#include "PKBNext.h"
#include "PKBStmt.h"
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

TABLE PKBNext::getAllNextByLineNextLineStmt() {
	return PKBNext::getResultTableGenericBoth(nextTable);
}
LINE_LIST PKBNext::getAllNextByLineStmt(PROG_LINE progLine) {
	return PKBNext::getResultTableGenericLeft(progLine, nextTable);
}
LINE_LIST PKBNext::getAllNextLineStmt(PROG_LINE progLine) {
	return PKBNext::getResultTableGenericRight(progLine, nextTable);
}
TABLE PKBNext::getAllNextByLineNextLineStarStmt() {
	return PKBNext::getResultTableGenericBoth(nextStarTable);
}
LINE_LIST PKBNext::getAllNextByLineStarStmt(PROG_LINE progLine) {
	return PKBNext::getResultTableGenericLeft(progLine, nextStarTable);
}
LINE_LIST PKBNext::getAllNextLineStarStmt(PROG_LINE progLine) {
	return PKBNext::getResultTableGenericRight(progLine, nextStarTable);
}

bool PKBNext::clear() {
	nextTable.clear();
	nextStarTable.clear();
	return true;
}

TABLE PKBNext::getResultTableGenericBoth(TABLE tableName) {
	return tableName;
}

LINE_LIST PKBNext::getResultTableGenericLeft(PROG_LINE progLine, TABLE tableName) {
	LINE_LIST resultTable;
	LINE_LIST list;
	PROG_LINE n;
	list = PKBStmt::getAllStmt();
	for (auto iter : list) {
		n = iter.front();
		for (auto vectorIter : tableName) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == n && vectorIter.back() == progLine) {
				tuple.push_back(vectorIter.front());
				//tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

LINE_LIST PKBNext::getResultTableGenericRight(PROG_LINE progLine, TABLE tableName) {
	LINE_LIST resultTable;
	LINE_LIST list;
	PROG_LINE n;
	list = PKBStmt::getAllStmt();
	for (auto iter : list) {
		n = iter.front();
		for (auto vectorIter : tableName) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == progLine && vectorIter.back() == n) {
				//tuple.push_back(vectorIter.front());
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

