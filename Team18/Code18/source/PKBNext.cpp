#include "PKBNext.h"
#include "PKBStmt.h"
#include "DesignExtractor.h"
#include <system_error>

using namespace std;

TABLE PKBNext::nextTable;
TABLE PKBNext::nextTTable;
TABLE PKBNext::nextBipTable;
TABLE PKBNext::nextBipTTable;

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

bool PKBNext::setNextBip(PROG_LINE nextByLine, PROG_LINE nextLine) {
	vector<string> tuple = vector<string>();
	tuple.push_back(nextByLine);
	tuple.push_back(nextLine);
	nextBipTable.emplace(tuple);
	return true;
}

bool PKBNext::setNextBipT(PROG_LINE nextByLine, PROG_LINE nextLine) {
	vector<string> tuple = vector<string>();
	tuple.push_back(nextByLine);
	tuple.push_back(nextLine);
	nextBipTTable.emplace(tuple);
	return true;
}


bool PKBNext::isNextT(PROG_LINE currentLine, PROG_LINE nextLine) {
	for (auto vectorIter : nextTTable) {
		if (vectorIter.front() == currentLine) {
			if (vectorIter.back() == nextLine) {
				return true;
			}
		}
	}
	return false;
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

LINE_LIST PKBNext::getNextBy(PROG_LINE nextLine) {
	LINE_LIST list;
	for (auto vectorIter : nextTable) {
		if (vectorIter.back() == nextLine) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter.front());
			list.emplace(tuple);
		}
	}
	return list;
}

LINE_LIST PKBNext::getNextBip(PROG_LINE nextByLine) {
	LINE_LIST list;
	for (auto vectorIter : nextBipTable) {
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

TABLE PKBNext::getNextBipTable() {
	return nextBipTable;
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
	return !nextTable.empty();
}
bool PKBNext::isNextTAnyIdent(PROG_LINE nextLine) {
	STMT_LIST emptyList, n2List;
	vector<string> tuple2 = vector<string>();
	tuple2.push_back(nextLine);
	n2List.emplace(tuple2);

	DesignExtractor::extractNextT(emptyList, n2List);
	for (auto vectorIter : nextTable) {
		if (vectorIter.back() == nextLine) {
			return true;
		}
	}
	return false;
}
bool PKBNext::isNextTIdentAny(PROG_LINE currentLine) {
	STMT_LIST n1List, emptyList;
	vector<string> tuple1 = vector<string>();
	tuple1.push_back(currentLine);
	n1List.emplace(tuple1);

	DesignExtractor::extractNextT(n1List, emptyList);
	for (auto vectorIter : nextTable) {
		if (vectorIter.front() == currentLine) {
			return true;
		}
	}
	return false;
}
bool PKBNext::isNextTIdentIdent(PROG_LINE currentLine, PROG_LINE nextLine) {
	
	STMT_LIST n1List, n2List;
	vector<string> tuple1 = vector<string>();
	tuple1.push_back(currentLine);
	n1List.emplace(tuple1);

	vector<string> tuple2 = vector<string>();
	tuple2.push_back(nextLine);
	n2List.emplace(tuple2);

	DesignExtractor::extractNextT(n1List, n2List);

	for (auto vectorIter : nextTTable) {
		if (vectorIter.front() == currentLine) {
			if (vectorIter.back() == nextLine) {
				return true;
			}
		}
	}
	return false;
}


bool PKBNext::isNextBipT(PROG_LINE currentLine, PROG_LINE nextLine) {
	for (auto vectorIter : nextBipTTable) {
		if (vectorIter.front() == currentLine) {
			if (vectorIter.back() == nextLine) {
				return true;
			}
		}
	}
	return false;
}

bool PKBNext::isNextBipAnyAny() {
	return !nextBipTable.empty();
}
bool PKBNext::isNextBipAnyIdent(PROG_LINE nextLine) {
	for (auto vectorIter : nextBipTable) {
		if (vectorIter.back() == nextLine) {
			return true;
		}
	}
	return false;
}
bool PKBNext::isNextBipIdentAny(PROG_LINE currentLine) {
	for (auto vectorIter : nextBipTable) {
		if (vectorIter.front() == currentLine) {
			return true;
		}
	}
	return false;
}
bool PKBNext::isNextBipIdentIdent(PROG_LINE currentLine, PROG_LINE nextLine) {
	for (auto vectorIter : nextBipTable) {
		if (vectorIter.front() == currentLine) {
			if (vectorIter.back() == nextLine) {
				return true;
			}
		}
	}
	return false;
}

bool PKBNext::isNextBipTAnyAny() {
	bool status = !nextBipTTable.empty();
	return status;
}
bool PKBNext::isNextBipTAnyIdent(PROG_LINE nextLine) {
	for (auto vectorIter : nextBipTTable) {
		if (vectorIter.back() == nextLine) {
			return true;
		}
	}
	return false;
}
bool PKBNext::isNextBipTIdentAny(PROG_LINE currentLine) {
	for (auto vectorIter : nextBipTTable) {
		if (vectorIter.front() == currentLine) {
			return true;
		}
	}
	return false;
}
bool PKBNext::isNextBipTIdentIdent(PROG_LINE currentLine, PROG_LINE nextLine) {
	for (auto vectorIter : nextBipTTable) {
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
	nextBipTable.clear();
	nextBipTTable.clear();
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
	if (type1 == "prog_line") {
		type1 = "stmt";
	}
	if (type2 == "prog_line") {
		type2 = "stmt";
	}
	if (type1 == "stmt" && type2 == "stmt") {
		return nextTable;
	}
	STMT_LIST list1, list2;
	if (type1 == "stmt") {
		list1 = PKBStmt::getStmts();
	}
	else {
		list1 = PKBStmt::getStmtsByType(type1);
	}
	if (type2 == "stmt") {
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
	
	TABLE resultTable;
	STMT_LIST list, emptyList;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getStmts();
	}
	else {
		list = PKBStmt::getStmtsByType(type);
	}
	DesignExtractor::extractNextT(emptyList, list);
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
	return resultTable;
}

TABLE PKBNext::getNextTEntAny(STMT_TYPE type) {
	
	TABLE resultTable;
	STMT_LIST list, emptyList;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getStmts();
	}
	else {
		list = PKBStmt::getStmtsByType(type);
	}
	DesignExtractor::extractNextT(list, emptyList);
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
	return resultTable;
}

TABLE PKBNext::getNextTIdentEnt(PROG_LINE stmtNo, STMT_TYPE type) {
	
	TABLE resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getStmts();
	}
	else {
		list = PKBStmt::getStmtsByType(type);
	}

	STMT_LIST n1List;
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	n1List.emplace(tuple);

	DesignExtractor::extractNextT(n1List, list);
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
	return resultTable;
}

TABLE PKBNext::getNextTEntIdent(STMT_TYPE type, PROG_LINE stmtNo) {
	TABLE resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getStmts();
	}
	else {
		list = PKBStmt::getStmtsByType(type);
	}

	STMT_LIST n2List;
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	n2List.emplace(tuple);

	DesignExtractor::extractNextT(list, n2List);
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
	return resultTable;
}

TABLE PKBNext::getNextTEntEnt(STMT_TYPE type1, STMT_TYPE type2) {
	
	TABLE resultTable;
	STMT_LIST list1, list2;
	if (type1 == "prog_line") {
		type1 = "stmt";
	}
	if (type2 == "prog_line") {
		type2 = "stmt";
	}
	if ((type1 == "stmt" && type2 == "stmt")) {
		list1 = PKBStmt::getStmts();
		list2 = PKBStmt::getStmts();
		DesignExtractor::extractNextT(list1, list2);
		return nextTTable;
	}
	if (type1 == "stmt") {
		list1 = PKBStmt::getStmts();
	}
	else {
		list1 = PKBStmt::getStmtsByType(type1);
	}
	if (type2 == "stmt") {
		list2 = PKBStmt::getStmts();
	}
	else {
		list2 = PKBStmt::getStmtsByType(type2);
	}

	DesignExtractor::extractNextT(list1,list2);

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
	return resultTable;
}

TABLE PKBNext::getNextTSelf(STMT_TYPE type) {
	
	PROC_LIST resultTable;
	LINE_LIST list;
	PROG_LINE n;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getStmts();
	}
	else {
		list = PKBStmt::getStmtsByType(type);
	}
	DesignExtractor::extractNextT(list, list);
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

TABLE PKBNext::getNextBipAnyEnt(STMT_TYPE type) {
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
		for (auto vectorIter : nextBipTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.back() == s) {
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBNext::getNextBipEntAny(STMT_TYPE type) {
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
		for (auto vectorIter : nextBipTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == s) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBNext::getNextBipIdentEnt(PROG_LINE stmtNo, STMT_TYPE type) {
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
		for (auto vectorIter : nextBipTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == stmtNo && vectorIter.back() == s) {
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBNext::getNextBipEntIdent(STMT_TYPE type, PROG_LINE stmtNo) {
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
		for (auto vectorIter : nextBipTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == s && vectorIter.back() == stmtNo) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBNext::getNextBipEntEnt(STMT_TYPE type1, STMT_TYPE type2) {
	TABLE resultTable;
	if (type1 == "prog_line") {
		type1 = "stmt";
	}
	if (type2 == "prog_line") {
		type2 = "stmt";
	}
	if (type1 == "stmt" && type2 == "stmt") {
		return nextBipTable;
	}
	STMT_LIST list1, list2;
	if (type1 == "stmt") {
		list1 = PKBStmt::getStmts();
	}
	else {
		list1 = PKBStmt::getStmtsByType(type1);
	}
	if (type2 == "stmt") {
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
			for (auto vectorIter : nextBipTable) {
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

TABLE PKBNext::getNextBipTAnyEnt(STMT_TYPE type) {
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
		for (auto vectorIter : nextBipTTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.back() == s) {
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBNext::getNextBipTEntAny(STMT_TYPE type) {
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
		for (auto vectorIter : nextBipTTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == s) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBNext::getNextBipTIdentEnt(PROG_LINE stmtNo, STMT_TYPE type) {
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
		for (auto vectorIter : nextBipTTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == stmtNo && vectorIter.back() == s) {
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBNext::getNextBipTEntIdent(STMT_TYPE type, PROG_LINE stmtNo) {
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
		for (auto vectorIter : nextBipTTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == s && vectorIter.back() == stmtNo) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBNext::getNextBipTEntEnt(STMT_TYPE type1, STMT_TYPE type2) {
	TABLE resultTable;
	if (type1 == "prog_line") {
		type1 = "stmt";
	}
	if (type2 == "prog_line") {
		type2 = "stmt";
	}
	if (type1 == "stmt" && type2 == "stmt") {
		return nextBipTTable;
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
			for (auto vectorIter : nextBipTTable) {
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

TABLE PKBNext::getNextBipTSelf(STMT_TYPE type) {
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
		for (auto vectorIter : nextBipTTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == n && vectorIter.back() == n) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}