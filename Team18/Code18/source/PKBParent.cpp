#include "PKBParent.h"
#include "PKBStmt.h"
#include <system_error>

using namespace std;

TABLE PKBParent::parentTable;
TABLE PKBParent::parentTTable;

bool PKBParent::setParent(STMT_NO parent, STMT_NO child) {
	vector<string> tuple = vector<string>();
	tuple.push_back(parent);
	tuple.push_back(child);
	parentTable.emplace(tuple);
	return true;
}

bool PKBParent::setParentT(STMT_NO parent, STMT_NO child) {
	vector<string> tuple = vector<string>();
	tuple.push_back(parent);
	tuple.push_back(child);
	parentTTable.emplace(tuple);
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

TABLE PKBParent::getParentTable() {
	return parentTable;
}

TABLE PKBParent::getParentTTable() {
	return parentTTable;
}

bool PKBParent::isParentAnyAny() {
	return !parentTable.empty();
}
bool PKBParent::isParentAnyIdent(STMT_NO child) {
	for (auto vectorIter : parentTable) {
		if (vectorIter.back() == child) {
			return true;
		}
	}
	return false;
}
bool PKBParent::isParentIdentAny(STMT_NO parent) {
	for (auto vectorIter : parentTable) {
		if (vectorIter.front() == parent) {
			return true;
		}
	}
	return false;
}
bool PKBParent::isParentIdentIdent(STMT_NO parent, STMT_NO child) {
	for (auto vectorIter : parentTable) {
		if (vectorIter.front() == parent) {
			if (vectorIter.back() == child) {
				return true;
			}
		}
	}
	return false;
}

bool PKBParent::isParentTAnyAny() {
	return !parentTTable.empty();
}
bool PKBParent::isParentTAnyIdent(STMT_NO childT) {
	for (auto vectorIter : parentTTable) {
		if (vectorIter.back() == childT) {
			return true;
		}
	}
	return false;
}
bool PKBParent::isParentTIdentAny(STMT_NO parent) {
	for (auto vectorIter : parentTTable) {
		if (vectorIter.front() == parent) {
			return true;
		}
	}
	return false;
}
bool PKBParent::isParentTIdentIdent(STMT_NO parent, STMT_NO childT) {
	for (auto vectorIter : parentTTable) {
		if (vectorIter.front() == parent) {
			if (vectorIter.back() == childT) {
				return true;
			}
		}
	}
	return false;
}

//NEW EVALUATION API
TABLE PKBParent::getParentAnyEnt(STMT_TYPE type) {
	TABLE resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getAllStmt();
	}
	else {
		list = PKBStmt::getAllStmtByType(type);
	}
	for (auto iter : list) {
		s = iter.front();
		for (auto vectorIter : parentTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.back() == s) {
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBParent::getParentEntAny(STMT_TYPE type) {
	TABLE resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getAllStmt();
	}
	else {
		list = PKBStmt::getAllStmtByType(type);
	}
	for (auto iter : list) {
		s = iter.front();
		for (auto vectorIter : parentTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == s) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBParent::getParentIdentEnt(STMT_NO stmtNo, STMT_TYPE type) {
	TABLE resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getAllStmt();
	}
	else {
		list = PKBStmt::getAllStmtByType(type);
	}
	for (auto iter : list) {
		s = iter.front();
		for (auto vectorIter : parentTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == stmtNo && vectorIter.back() == s) {
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBParent::getParentEntIdent(STMT_TYPE type, STMT_NO stmtNo) {
	TABLE resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getAllStmt();
	}
	else {
		list = PKBStmt::getAllStmtByType(type);
	}
	for (auto iter : list) {
		s = iter.front();
		for (auto vectorIter : parentTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == s && vectorIter.back() == stmtNo) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBParent::getParentEntEnt(STMT_TYPE type1, STMT_TYPE type2) {
	TABLE resultTable;
	if ((type1 == "stmt" && type2 == "stmt") || (type1 == "prog_line" && type2 == "prog_line")
		|| (type1 == "prog_line" && type2 == "stmt") || (type1 == "stmt" && type2 == "prog_line")) {
		return parentTable;
	}
	STMT_LIST list1, list2;
	if (type1 == "stmt" || type1 == "prog_line") {
		list1 = PKBStmt::getAllStmt();
	}
	else {
		list1 = PKBStmt::getAllStmtByType(type1);
	}
	if (type2 == "stmt" || type2 == "prog_line") {
		list2 = PKBStmt::getAllStmt();
	}
	else {
		list2 = PKBStmt::getAllStmtByType(type2);
	}

	STMT_NO s1;
	STMT_NO s2;
	for (auto iter1 : list1) {
		s1 = iter1.front();
		for (auto iter2 : list2) {
			s2 = iter2.front();
			for (auto vectorIter : parentTable) {
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

TABLE PKBParent::getParentTAnyEnt(STMT_TYPE type) {
	TABLE resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getAllStmt();
	}
	else {
		list = PKBStmt::getAllStmtByType(type);
	}
	for (auto iter : list) {
		s = iter.front();
		for (auto vectorIter : parentTTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.back() == s) {
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBParent::getParentTEntAny(STMT_TYPE type) {
	TABLE resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getAllStmt();
	}
	else {
		list = PKBStmt::getAllStmtByType(type);
	}
	for (auto iter : list) {
		s = iter.front();
		for (auto vectorIter : parentTTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == s) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBParent::getParentTIdentEnt(STMT_NO stmtNo, STMT_TYPE type) {
	TABLE resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getAllStmt();
	}
	else {
		list = PKBStmt::getAllStmtByType(type);
	}
	for (auto iter : list) {
		s = iter.front();
		for (auto vectorIter : parentTTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == stmtNo && vectorIter.back() == s) {
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBParent::getParentTEntIdent(STMT_TYPE type, STMT_NO stmtNo) {
	TABLE resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getAllStmt();
	}
	else {
		list = PKBStmt::getAllStmtByType(type);
	}
	for (auto iter : list) {
		s = iter.front();
		for (auto vectorIter : parentTTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == s && vectorIter.back() == stmtNo) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBParent::getParentTEntEnt(STMT_TYPE type1, STMT_TYPE type2) {
	TABLE resultTable;
	if ((type1 == "stmt" && type2 == "stmt") || (type1 == "prog_line" && type2 == "prog_line")
		|| (type1 == "prog_line" && type2 == "stmt") || (type1 == "stmt" && type2 == "prog_line")) {
		return parentTTable;
	}
	STMT_LIST list1, list2;
	if (type1 == "stmt" || type1 == "prog_line") {
		list1 = PKBStmt::getAllStmt();
	}
	else {
		list1 = PKBStmt::getAllStmtByType(type1);
	}
	if (type2 == "stmt" || type2 == "prog_line") {
		list2 = PKBStmt::getAllStmt();
	}
	else {
		list2 = PKBStmt::getAllStmtByType(type2);
	}

	STMT_NO s1;
	STMT_NO s2;
	for (auto iter1 : list1) {
		s1 = iter1.front();
		for (auto iter2 : list2) {
			s2 = iter2.front();
			for (auto vectorIter : parentTTable) {
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


bool PKBParent::clear() {
	parentTable.clear();
	parentTTable.clear();
	return true;
}