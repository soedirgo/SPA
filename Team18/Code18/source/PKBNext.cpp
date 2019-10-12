#include "PKBNext.h"
#include "PKBStmt.h"
#include <system_error>

using namespace std;

TABLE PKBNext::nextTable;
TABLE PKBNext::nextTTable;

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
	nextTTable.emplace(tuple);
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

TABLE PKBNext::getNextTable() {
	return nextTable;
}

bool PKBNext::isNextAnyAny() {
	return !nextTable.empty();
}
bool PKBNext::isNextAnyIdent(PROG_LINE nextLine) {
	for (auto vectorIter : nextTable) {
		if (vectorIter.back() == nextLine) {
			return true;
		}
	}
	return false;
}
bool PKBNext::isNextIdentAny(PROG_LINE currentLine) {
	for (auto vectorIter : nextTable) {
		if (vectorIter.front() == currentLine) {
			return true;
		}
	}
	return false;
}
bool PKBNext::isNextIdentIdent(PROG_LINE currentLine, PROG_LINE nextLine) {
	for (auto vectorIter : nextTable) {
		if (vectorIter.front() == currentLine) {
			if (vectorIter.back() == nextLine) {
				return true;
			}
		}
	}
	return false;
}

bool PKBNext::isNextTAnyAny() {
	return !nextTTable.empty();
}
bool PKBNext::isNextTAnyIdent(PROG_LINE nextLine) {
	for (auto vectorIter : nextTTable) {
		if (vectorIter.back() == nextLine) {
			return true;
		}
	}
	return false;
}
bool PKBNext::isNextTIdentAny(PROG_LINE currentLine) {
	for (auto vectorIter : nextTTable) {
		if (vectorIter.front() == currentLine) {
			return true;
		}
	}
	return false;
}
bool PKBNext::isNextTIdentIdent(PROG_LINE currentLine, PROG_LINE nextLine) {
	for (auto vectorIter : nextTTable) {
		if (vectorIter.front() == currentLine) {
			if (vectorIter.back() == nextLine) {
				return true;
			}
		}
	}
	return false;
}

bool PKBNext::clear() {
	nextTable.clear();
	nextTTable.clear();
	return true;
}

//NEW EVALUATION API
TABLE PKBNext::getNextAnyEnt() {
	PROC_LIST resultTable;
	LINE_LIST list;
	PROG_LINE n;
	list = PKBStmt::getAllStmt();
	for (auto iter : list) {
		n = iter.front();
		for (auto vectorIter : nextTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.back() == n) {
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBNext::getNextEntAny() {
	PROC_LIST resultTable;
	LINE_LIST list;
	PROG_LINE n;
	list = PKBStmt::getAllStmt();
	for (auto iter : list) {
		n = iter.front();
		for (auto vectorIter : nextTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == n) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBNext::getNextIdentEnt(PROG_LINE progLine) {
	PROC_LIST resultTable;
	LINE_LIST list;
	PROG_LINE n;
	list = PKBStmt::getAllStmt();
	for (auto iter : list) {
		n = iter.front();
		for (auto vectorIter : nextTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == progLine && vectorIter.back() == n) {
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBNext::getNextEntIdent(PROG_LINE progLine) {
	PROC_LIST resultTable;
	LINE_LIST list;
	PROG_LINE n;
	list = PKBStmt::getAllStmt();
	for (auto iter : list) {
		n = iter.front();
		for (auto vectorIter : nextTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == n && vectorIter.back() == progLine) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBNext::getNextEntEnt() {
	return nextTable;
}

TABLE PKBNext::getNextTAnyEnt() {
	PROC_LIST resultTable;
	LINE_LIST list;
	PROG_LINE n;
	list = PKBStmt::getAllStmt();
	for (auto iter : list) {
		n = iter.front();
		for (auto vectorIter : nextTTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.back() == n) {
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBNext::getNextTEntAny() {
	PROC_LIST resultTable;
	LINE_LIST list;
	PROG_LINE n;
	list = PKBStmt::getAllStmt();
	for (auto iter : list) {
		n = iter.front();
		for (auto vectorIter : nextTTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == n) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBNext::getNextTIdentEnt(PROG_LINE progLine) {
	PROC_LIST resultTable;
	LINE_LIST list;
	PROG_LINE n;
	list = PKBStmt::getAllStmt();
	for (auto iter : list) {
		n = iter.front();
		for (auto vectorIter : nextTTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == progLine && vectorIter.back() == n) {
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBNext::getNextTEntIdent(PROG_LINE progLine) {
	PROC_LIST resultTable;
	LINE_LIST list;
	PROG_LINE n;
	list = PKBStmt::getAllStmt();
	for (auto iter : list) {
		n = iter.front();
		for (auto vectorIter : nextTTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == n && vectorIter.back() == progLine) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBNext::getNextTEntEnt() {
	return nextTTable;
}

TABLE PKBNext::getNextTSelf() {
	PROC_LIST resultTable;
	LINE_LIST list;
	PROG_LINE n;
	list = PKBStmt::getAllStmt();
	for (auto iter1 : list) {
		n = iter1.front();
		for (auto vectorIter : nextTTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == n && vectorIter.back() == n) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

