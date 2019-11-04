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

TABLE PKBNext::getNextBipTTable() {
	return nextBipTTable;
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
	for (auto vectorIter : nextTTable) {
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
	for (auto vectorIter : nextTTable) {
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
LINE_LIST PKBNext::getNextAnyEnt(STMT_TYPE type) {
	LINE_LIST resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		for (auto vectorIter : nextTable) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter.back());
			resultTable.emplace(tuple);
		}
	}
	else {
		list = PKBStmt::getStmtsByType(type);
		for (auto iter : list) {
			s = iter.front();
			for (auto vectorIter : nextTable) {
				if (vectorIter.back() == s) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	
	return resultTable;
}

LINE_LIST PKBNext::getNextEntAny(STMT_TYPE type) {
	LINE_LIST resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		for (auto vectorIter : nextTable) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter.front());
			resultTable.emplace(tuple);
		}
	}
	else {
		list = PKBStmt::getStmtsByType(type);
		for (auto iter : list) {
			s = iter.front();
			for (auto vectorIter : nextTable) {
				if (vectorIter.front() == s) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.front());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	
	return resultTable;
}

LINE_LIST PKBNext::getNextIdentEnt(PROG_LINE stmtNo, STMT_TYPE type) {
	LINE_LIST resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		for (auto vectorIter : nextTable) {
			if (vectorIter.front() == stmtNo) {
				vector<string> tuple = vector<string>();
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	else {
		list = PKBStmt::getStmtsByType(type);
		for (auto iter : list) {
			s = iter.front();
			for (auto vectorIter : nextTable) {
				if (vectorIter.front() == stmtNo && vectorIter.back() == s) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	
	return resultTable;
}

LINE_LIST PKBNext::getNextEntIdent(STMT_TYPE type, PROG_LINE stmtNo) {
	LINE_LIST resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		for (auto vectorIter : nextTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.back() == stmtNo) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	else {
		list = PKBStmt::getStmtsByType(type);
		for (auto iter : list) {
			s = iter.front();
			for (auto vectorIter : nextTable) {
				if (vectorIter.front() == s && vectorIter.back() == stmtNo) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.front());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	return resultTable;
}

TABLE PKBNext::getNextEntEnt(STMT_TYPE type1, STMT_TYPE type2) {
	TABLE resultTable;
	STMT_NO s1;
	STMT_NO s2;
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
	if (type1 == "stmt" && type2 != "stmt") {
		list1 = PKBStmt::getStmts();
		list2 = PKBStmt::getStmtsByType(type2);
		for (auto iter2 : list2) {
			s2 = iter2.front();
			for (auto vectorIter : nextTable) {
				if (vectorIter.back() == s2) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.front());
					tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	else if (type1 != "stmt" && type2 == "stmt") {
		list1 = PKBStmt::getStmtsByType(type1);
		list2 = PKBStmt::getStmts();
		for (auto iter1 : list1) {
			s1 = iter1.front();
			for (auto vectorIter : nextTable) {
				if (vectorIter.front() == s1) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.front());
					tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}

	}
	else if (type1 != "stmt" && type2 != "stmt") {
		list1 = PKBStmt::getStmtsByType(type1);
		list2 = PKBStmt::getStmtsByType(type2);
		for (auto iter1 : list1) {
			s1 = iter1.front();
			for (auto iter2 : list2) {
				s2 = iter2.front();
				for (auto vectorIter : nextTable) {
					if (vectorIter.front() == s1 && vectorIter.back() == s2) {
						vector<string> tuple = vector<string>();
						tuple.push_back(vectorIter.front());
						tuple.push_back(vectorIter.back());
						resultTable.emplace(tuple);
					}
				}
			}
		}
	}
	
	return resultTable;
}

LINE_LIST PKBNext::getNextTAnyEnt(STMT_TYPE type) {
	
	LINE_LIST resultTable;
	STMT_LIST list, emptyList;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getStmts();
		DesignExtractor::extractNextT(emptyList, list);
		for (auto vectorIter : nextTTable) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter.back());
			resultTable.emplace(tuple);
		}
	}
	else {
		list = PKBStmt::getStmtsByType(type);
		DesignExtractor::extractNextT(emptyList, list);
		for (auto iter : list) {
			s = iter.front();
			for (auto vectorIter : nextTTable) {
				if (vectorIter.back() == s) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	return resultTable;
}

LINE_LIST PKBNext::getNextTEntAny(STMT_TYPE type) {
	
	LINE_LIST resultTable;
	STMT_LIST list, emptyList;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getStmts();
		DesignExtractor::extractNextT(list, emptyList);
		for (auto vectorIter : nextTTable) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter.front());
			resultTable.emplace(tuple);
		}
	}
	else {
		list = PKBStmt::getStmtsByType(type);
		DesignExtractor::extractNextT(list, emptyList);
		for (auto iter : list) {
			s = iter.front();
			for (auto vectorIter : nextTTable) {
				if (vectorIter.front() == s) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.front());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	return resultTable;
}

LINE_LIST PKBNext::getNextTIdentEnt(PROG_LINE stmtNo, STMT_TYPE type) {
	
	LINE_LIST resultTable;
	STMT_LIST list;
	STMT_NO s;
	STMT_LIST n1List;
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	n1List.emplace(tuple);
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getStmts();
		DesignExtractor::extractNextT(n1List, list);
		for (auto vectorIter : nextTTable) {
			if (vectorIter.front() == stmtNo) {
				vector<string> tuple = vector<string>();
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	else {
		list = PKBStmt::getStmtsByType(type);
		DesignExtractor::extractNextT(n1List, list);
		for (auto iter : list) {
			s = iter.front();
			for (auto vectorIter : nextTTable) {
				if (vectorIter.front() == stmtNo && vectorIter.back() == s) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	return resultTable;
}

LINE_LIST PKBNext::getNextTEntIdent(STMT_TYPE type, PROG_LINE stmtNo) {
	LINE_LIST resultTable;
	STMT_LIST list;
	STMT_NO s;
	STMT_LIST n2List;
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	n2List.emplace(tuple);

	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getStmts();
		DesignExtractor::extractNextT(list, n2List);
		for (auto vectorIter : nextTTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.back() == stmtNo) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	else {
		list = PKBStmt::getStmtsByType(type);
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
	}

	

	
	
	return resultTable;
}

TABLE PKBNext::getNextTEntEnt(STMT_TYPE type1, STMT_TYPE type2) {
	TABLE resultTable;
	STMT_NO s1;
	STMT_NO s2;
	STMT_LIST list1, list2;
	if (type1 == "prog_line") {
		type1 = "stmt";
	}
	if (type2 == "prog_line") {
		type2 = "stmt";
	}
	if (type1 == "stmt" && type2 == "stmt") {
		list1 = PKBStmt::getStmts();
		list2 = PKBStmt::getStmts();
		DesignExtractor::extractNextT(list1, list2);
		return nextTTable;
	}
	if (type1 == "stmt" && type2 != "stmt") {
		list1 = PKBStmt::getStmts();
		list2 = PKBStmt::getStmtsByType(type2);
		DesignExtractor::extractNextT(list1, list2);
		for (auto iter2 : list2) {
			s2 = iter2.front();
			for (auto vectorIter : nextTTable) {
				if (vectorIter.back() == s2) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.front());
					tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	else if (type1 != "stmt" && type2 == "stmt") {
		list1 = PKBStmt::getStmtsByType(type1);
		list2 = PKBStmt::getStmts();
		DesignExtractor::extractNextT(list1, list2);
		for (auto iter1 : list1) {
			s1 = iter1.front();
			for (auto vectorIter : nextTTable) {
				if (vectorIter.front() == s1) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.front());
					tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}

	}
	else if (type1 != "stmt" && type2 != "stmt") {
		list1 = PKBStmt::getStmtsByType(type1);
		list2 = PKBStmt::getStmtsByType(type2);
		DesignExtractor::extractNextT(list1, list2);
		for (auto iter1 : list1) {
			s1 = iter1.front();
			for (auto iter2 : list2) {
				s2 = iter2.front();
				for (auto vectorIter : nextTTable) {
					if (vectorIter.front() == s1 && vectorIter.back() == s2) {
						vector<string> tuple = vector<string>();
						tuple.push_back(vectorIter.front());
						tuple.push_back(vectorIter.back());
						resultTable.emplace(tuple);
					}
				}
			}
		}
	}
	return resultTable;
}

LINE_LIST PKBNext::getNextTSelf(STMT_TYPE type) {
	
	LINE_LIST resultTable;
	LINE_LIST list;
	PROG_LINE n;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getStmts();
		DesignExtractor::extractNextT(list, list);
		for (auto vectorIter : nextTTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == vectorIter.back()) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	else {
		list = PKBStmt::getStmtsByType(type);
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
	}
	
	return resultTable;
}

TABLE PKBNext::getNextBipAnyEnt(STMT_TYPE type) {
	TABLE resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		for (auto vectorIter : nextBipTable) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter.back());
			resultTable.emplace(tuple);
		}
	}
	else {
		list = PKBStmt::getStmtsByType(type);
		for (auto iter : list) {
			s = iter.front();
			for (auto vectorIter : nextBipTable) {
				if (vectorIter.back() == s) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	
	return resultTable;
}

LINE_LIST PKBNext::getNextBipEntAny(STMT_TYPE type) {
	LINE_LIST resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		for (auto vectorIter : nextBipTable) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter.front());
			resultTable.emplace(tuple);
		}
	}
	else {
		list = PKBStmt::getStmtsByType(type);
		for (auto iter : list) {
			s = iter.front();
			for (auto vectorIter : nextBipTable) {
				if (vectorIter.front() == s) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.front());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	
	return resultTable;
}

LINE_LIST PKBNext::getNextBipIdentEnt(PROG_LINE stmtNo, STMT_TYPE type) {
	LINE_LIST resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		for (auto vectorIter : nextBipTable) {
			if (vectorIter.front() == stmtNo) {
				vector<string> tuple = vector<string>();
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	else {
		list = PKBStmt::getStmtsByType(type);
		for (auto iter : list) {
			s = iter.front();
			for (auto vectorIter : nextBipTable) {
				if (vectorIter.front() == stmtNo && vectorIter.back() == s) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	
	return resultTable;
}

LINE_LIST PKBNext::getNextBipEntIdent(STMT_TYPE type, PROG_LINE stmtNo) {
	LINE_LIST resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		for (auto vectorIter : nextBipTable) {
			if (vectorIter.back() == stmtNo) {
				vector<string> tuple = vector<string>();
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	else {
		list = PKBStmt::getStmtsByType(type);
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
	}
	
	return resultTable;
}

TABLE PKBNext::getNextBipEntEnt(STMT_TYPE type1, STMT_TYPE type2) {
	TABLE resultTable;
	STMT_NO s1;
	STMT_NO s2;
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
	if (type1 == "stmt" && type2 != "stmt") {
		list1 = PKBStmt::getStmts();
		list2 = PKBStmt::getStmtsByType(type2);
		for (auto iter2 : list2) {
			s2 = iter2.front();
			for (auto vectorIter : nextBipTable) {
				if (vectorIter.back() == s2) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.front());
					tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	else if (type1 != "stmt" && type2 == "stmt") {
		list1 = PKBStmt::getStmtsByType(type1);
		list2 = PKBStmt::getStmts();
		for (auto iter1 : list1) {
			s1 = iter1.front();
			for (auto vectorIter : nextBipTable) {
				if (vectorIter.front() == s1) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.front());
					tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}

	}
	else if (type1 != "stmt" && type2 != "stmt") {
		list1 = PKBStmt::getStmtsByType(type1);
		list2 = PKBStmt::getStmtsByType(type2);
		for (auto iter1 : list1) {
			s1 = iter1.front();
			for (auto iter2 : list2) {
				s2 = iter2.front();
				for (auto vectorIter : nextBipTable) {
					if (vectorIter.front() == s1 && vectorIter.back() == s2) {
						vector<string> tuple = vector<string>();
						tuple.push_back(vectorIter.front());
						tuple.push_back(vectorIter.back());
						resultTable.emplace(tuple);
					}
				}
			}
		}
	}

	return resultTable;
}

LINE_LIST PKBNext::getNextBipTAnyEnt(STMT_TYPE type) {
	LINE_LIST resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		for (auto vectorIter : nextBipTTable) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter.back());
			resultTable.emplace(tuple);
		}
	}
	else {
		list = PKBStmt::getStmtsByType(type);
		for (auto iter : list) {
			s = iter.front();
			for (auto vectorIter : nextBipTTable) {
				if (vectorIter.back() == s) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	
	return resultTable;
}

LINE_LIST PKBNext::getNextBipTEntAny(STMT_TYPE type) {
	LINE_LIST resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		for (auto vectorIter : nextBipTTable) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter.front());
			resultTable.emplace(tuple);
		}
	}
	else {
		list = PKBStmt::getStmtsByType(type);
		for (auto iter : list) {
			s = iter.front();
			for (auto vectorIter : nextBipTTable) {
				if (vectorIter.front() == s) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.front());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	
	return resultTable;
}

LINE_LIST PKBNext::getNextBipTIdentEnt(PROG_LINE stmtNo, STMT_TYPE type) {
	LINE_LIST resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		for (auto vectorIter : nextBipTTable) {
			if (vectorIter.front() == stmtNo) {
				vector<string> tuple = vector<string>();
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	else {
		list = PKBStmt::getStmtsByType(type);
		for (auto iter : list) {
			s = iter.front();
			for (auto vectorIter : nextBipTTable) {
				if (vectorIter.front() == stmtNo && vectorIter.back() == s) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	
	return resultTable;
}

LINE_LIST PKBNext::getNextBipTEntIdent(STMT_TYPE type, PROG_LINE stmtNo) {
	LINE_LIST resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		for (auto vectorIter : nextBipTTable) {
			if (vectorIter.back() == stmtNo) {
				vector<string> tuple = vector<string>();
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	else {
		list = PKBStmt::getStmtsByType(type);
		for (auto iter : list) {
			s = iter.front();
			for (auto vectorIter : nextBipTTable) {
				if (vectorIter.front() == s && vectorIter.back() == stmtNo) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.front());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	
	return resultTable;
}

TABLE PKBNext::getNextBipTEntEnt(STMT_TYPE type1, STMT_TYPE type2) {
	TABLE resultTable;
	STMT_NO s1;
	STMT_NO s2;
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
	if (type1 == "stmt" && type2 != "stmt") {
		list1 = PKBStmt::getStmts();
		list2 = PKBStmt::getStmtsByType(type2);
		for (auto iter2 : list2) {
			s2 = iter2.front();
			for (auto vectorIter : nextBipTTable) {
				if (vectorIter.back() == s2) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.front());
					tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	else if (type1 != "stmt" && type2 == "stmt") {
		list1 = PKBStmt::getStmtsByType(type1);
		list2 = PKBStmt::getStmts();
		for (auto iter1 : list1) {
			s1 = iter1.front();
			for (auto vectorIter : nextBipTTable) {
				if (vectorIter.front() == s1) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.front());
					tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}

	}
	else if (type1 != "stmt" && type2 != "stmt") {
		list1 = PKBStmt::getStmtsByType(type1);
		list2 = PKBStmt::getStmtsByType(type2);
		for (auto iter1 : list1) {
			s1 = iter1.front();
			for (auto iter2 : list2) {
				s2 = iter2.front();
				for (auto vectorIter : nextBipTTable) {
					if (vectorIter.front() == s1 && vectorIter.back() == s2) {
						vector<string> tuple = vector<string>();
						tuple.push_back(vectorIter.front());
						tuple.push_back(vectorIter.back());
						resultTable.emplace(tuple);
					}
				}
			}
		}
	}
}

LINE_LIST PKBNext::getNextBipTSelf(STMT_TYPE type) {
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