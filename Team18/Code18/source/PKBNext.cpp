#include "PKBNext.h"
#include "PKBStmt.h"
#include "DesignExtractor.h"
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

bool PKBNext::setNextT(PROG_LINE nextByLine, PROG_LINE nextLine) {
	vector<string> tuple = vector<string>();
	tuple.push_back(nextByLine);
	tuple.push_back(nextLine);
	nextTTable.emplace(tuple);
	return true;
}

LINE_LIST PKBNext::getNext(PROG_LINE nextByLine) {
	LINE_LIST list;
	for (auto vectorIter : nextTable) {
		if (vectorIter.front() == nextByLine) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter.back());
			list.emplace(tuple);
		}
	}
	return list;
}

TABLE PKBNext::getNextTable() {
	return nextTable;
}

TABLE PKBNext::getNextTTable() {
	return nextTTable;
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
	clearNextT();
	DesignExtractor::extractNextT();
	bool status = !nextTTable.empty();
	clearNextT();
	return status;
}
bool PKBNext::isNextTAnyIdent(PROG_LINE nextLine) {
	clearNextT();
	DesignExtractor::extractNextT();
	for (auto vectorIter : nextTTable) {
		if (vectorIter.back() == nextLine) {
			clearNextT();
			return true;
		}
	}
	clearNextT();
	return false;
}
bool PKBNext::isNextTIdentAny(PROG_LINE currentLine) {
	clearNextT();
	DesignExtractor::extractNextT();
	for (auto vectorIter : nextTTable) {
		if (vectorIter.front() == currentLine) {
			clearNextT();
			return true;
		}
	}
	clearNextT();
	return false;
}
bool PKBNext::isNextTIdentIdent(PROG_LINE currentLine, PROG_LINE nextLine) {
	clearNextT();
	DesignExtractor::extractNextT();
	for (auto vectorIter : nextTTable) {
		if (vectorIter.front() == currentLine) {
			if (vectorIter.back() == nextLine) {
				clearNextT();
				return true;
			}
		}
	}
	clearNextT();
	return false;
}

bool PKBNext::isNextTInserted(PROG_LINE currentLine, PROG_LINE nextLine) {
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
	return true;
}

bool PKBNext::clearNextT() {
	nextTTable.clear();
	return true;
}

//NEW EVALUATION API
TABLE PKBNext::getNextAnyEnt(STMT_TYPE type) {
	TABLE resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getStmts();
	}
	else {
		list = PKBStmt::getStmtsByType(type);
	}
	for (auto iter : list) {
		s = iter.front();
		for (auto vectorIter : nextTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.back() == s) {
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBNext::getNextEntAny(STMT_TYPE type) {
	TABLE resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getStmts();
	}
	else {
		list = PKBStmt::getStmtsByType(type);
	}
	for (auto iter : list) {
		s = iter.front();
		for (auto vectorIter : nextTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == s) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBNext::getNextIdentEnt(PROG_LINE stmtNo, STMT_TYPE type) {
	TABLE resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getStmts();
	}
	else {
		list = PKBStmt::getStmtsByType(type);
	}
	for (auto iter : list) {
		s = iter.front();
		for (auto vectorIter : nextTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == stmtNo && vectorIter.back() == s) {
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBNext::getNextEntIdent(STMT_TYPE type, PROG_LINE stmtNo) {
	TABLE resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getStmts();
	}
	else {
		list = PKBStmt::getStmtsByType(type);
	}
	for (auto iter : list) {
		s = iter.front();
		for (auto vectorIter : nextTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == s && vectorIter.back() == stmtNo) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBNext::getNextEntEnt(STMT_TYPE type1, STMT_TYPE type2) {
	TABLE resultTable;
	if (type1 == "stmt" && type2 == "stmt") {
		return nextTable;
	}
	STMT_LIST list1, list2;
	if (type1 == "stmt" || type1 == "prog_line") {
		list1 = PKBStmt::getStmts();
	}
	else {
		list1 = PKBStmt::getStmtsByType(type1);
	}
	if (type2 == "stmt" || type2 == "prog_line") {
		list2 = PKBStmt::getStmts();
	}
	else {
		list2 = PKBStmt::getStmtsByType(type2);
	}

	STMT_NO s1;
	STMT_NO s2;
	for (auto iter1 : list1) {
		s1 = iter1.front();
		for (auto iter2 : list2) {
			s2 = iter2.front();
			for (auto vectorIter : nextTable) {
				vector<string> tuple = vector<string>();
				if (vectorIter.front() == s1 && vectorIter.back() == s2) {
					tuple.push_back(vectorIter.front());
					tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}
	}

	return resultTable;
}

TABLE PKBNext::getNextTAnyEnt(STMT_TYPE type) {
	clearNextT();
	DesignExtractor::extractNextT();
	TABLE resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getStmts();
	}
	else {
		list = PKBStmt::getStmtsByType(type);
	}
	for (auto iter : list) {
		s = iter.front();
		for (auto vectorIter : nextTTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.back() == s) {
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	clearNextT();
	return resultTable;
}

TABLE PKBNext::getNextTEntAny(STMT_TYPE type) {
	clearNextT();
	DesignExtractor::extractNextT();
	TABLE resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getStmts();
	}
	else {
		list = PKBStmt::getStmtsByType(type);
	}
	for (auto iter : list) {
		s = iter.front();
		for (auto vectorIter : nextTTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == s) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	clearNextT();
	return resultTable;
}

TABLE PKBNext::getNextTIdentEnt(PROG_LINE stmtNo, STMT_TYPE type) {
	clearNextT();
	DesignExtractor::extractNextT();
	TABLE resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getStmts();
	}
	else {
		list = PKBStmt::getStmtsByType(type);
	}
	for (auto iter : list) {
		s = iter.front();
		for (auto vectorIter : nextTTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == stmtNo && vectorIter.back() == s) {
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	clearNextT();
	return resultTable;
}

TABLE PKBNext::getNextTEntIdent(STMT_TYPE type, PROG_LINE stmtNo) {
	clearNextT();
	DesignExtractor::extractNextT();
	TABLE resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getStmts();
	}
	else {
		list = PKBStmt::getStmtsByType(type);
	}
	for (auto iter : list) {
		s = iter.front();
		for (auto vectorIter : nextTTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == s && vectorIter.back() == stmtNo) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	clearNextT();
	return resultTable;
}

TABLE PKBNext::getNextTEntEnt(STMT_TYPE type1, STMT_TYPE type2) {
	clearNextT();
	DesignExtractor::extractNextT();
	TABLE resultTable;
	if (type1 == "stmt" && type2 == "stmt") {
		return nextTTable;
	}
	STMT_LIST list1, list2;
	if (type1 == "stmt" || type1 == "prog_line") {
		list1 = PKBStmt::getStmts();
	}
	else {
		list1 = PKBStmt::getStmtsByType(type1);
	}
	if (type2 == "stmt" || type2 == "prog_line") {
		list2 = PKBStmt::getStmts();
	}
	else {
		list2 = PKBStmt::getStmtsByType(type2);
	}

	STMT_NO s1;
	STMT_NO s2;
	for (auto iter1 : list1) {
		s1 = iter1.front();
		for (auto iter2 : list2) {
			s2 = iter2.front();
			for (auto vectorIter : nextTTable) {
				vector<string> tuple = vector<string>();
				if (vectorIter.front() == s1 && vectorIter.back() == s2) {
					tuple.push_back(vectorIter.front());
					tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	clearNextT();
	return resultTable;
}

TABLE PKBNext::getNextTSelf(STMT_TYPE type) {
	clearNextT();
	DesignExtractor::extractNextT();
	PROC_LIST resultTable;
	LINE_LIST list;
	PROG_LINE n;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getStmts();
	}
	else {
		list = PKBStmt::getStmtsByType(type);
	}
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
	clearNextT();
	return resultTable;
}

