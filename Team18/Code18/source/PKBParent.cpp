#include "PKBParent.h"
#include "PKBStmt.h"
#include <system_error>

using namespace std;

TABLE PKBParent::parentTable;
TABLE PKBParent::parentTTable;

void PKBParent::setParent(STMT_NO parent, STMT_NO child) {
	vector<string> tuple = vector<string>();
	tuple.push_back(parent);
	tuple.push_back(child);
	parentTable.emplace(tuple);
}

void PKBParent::setParentT(STMT_NO parent, STMT_NO child) {
	vector<string> tuple = vector<string>();
	tuple.push_back(parent);
	tuple.push_back(child);
	parentTTable.emplace(tuple);
}

//Get boolean for Parent(_,_)
bool PKBParent::isParentAnyAny() {
	return !parentTable.empty();
}
//Get boolean for Parent(_,2)
bool PKBParent::isParentAnyIdent(STMT_NO child) {
	for (auto vectorIter : parentTable) {
		if (vectorIter.back() == child) {
			return true;
		}
	}
	return false;
}
//Get boolean for Parent(1,_)
bool PKBParent::isParentIdentAny(STMT_NO parent) {
	for (auto vectorIter : parentTable) {
		if (vectorIter.front() == parent) {
			return true;
		}
	}
	return false;
}
//Get boolean for Parent(1,2)
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
//Get boolean for Parent*(_,_)
bool PKBParent::isParentTAnyAny() {
	return !parentTTable.empty();
}
//Get boolean for Parent*(s,2)
bool PKBParent::isParentTAnyIdent(STMT_NO childT) {
	for (auto vectorIter : parentTTable) {
		if (vectorIter.back() == childT) {
			return true;
		}
	}
	return false;
}
//Get boolean for Parent*(1,s)
bool PKBParent::isParentTIdentAny(STMT_NO parent) {
	for (auto vectorIter : parentTTable) {
		if (vectorIter.front() == parent) {
			return true;
		}
	}
	return false;
}
//Get boolean for Parent*(1,2)
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

//Get STMT_LIST for Parent(_,s)
STMT_LIST PKBParent::getParentAnyEnt(STMT_TYPE type) {
	STMT_LIST resultTable, list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		for (auto vectorIter : parentTable) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter.back());
			resultTable.emplace(tuple);
		}
	}
	else {
		list = PKBStmt::getStmtsByType(type);
		for (auto iter : list) {
			s = iter.front();
			for (auto vectorIter : parentTable) {
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
//Get STMT_LIST for Parent(s,_)
STMT_LIST PKBParent::getParentEntAny(STMT_TYPE type) {
	STMT_LIST resultTable, list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		for (auto vectorIter : parentTable) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter.front());
			resultTable.emplace(tuple);
		}
	}
	else {
		list = PKBStmt::getStmtsByType(type);
		for (auto iter : list) {
			s = iter.front();
			for (auto vectorIter : parentTable) {
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
//Get STMT_LIST for Parent(1,s)
STMT_LIST PKBParent::getParentIdentEnt(STMT_NO stmtNo, STMT_TYPE type) {
	TABLE resultTable, list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		for (auto vectorIter : parentTable) {
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
			for (auto vectorIter : parentTable) {
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
//Get STMT_LIST for Parent(s,2)
STMT_LIST PKBParent::getParentEntIdent(STMT_TYPE type, STMT_NO stmtNo) {
	TABLE resultTable, list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		for (auto vectorIter : parentTable) {
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
			for (auto vectorIter : parentTable) {
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
//Get STMT_LIST for Parent(s1,s2)
TABLE PKBParent::getParentEntEnt(STMT_TYPE type1, STMT_TYPE type2) {
	TABLE resultTable;
	STMT_NO s1;
	STMT_NO s2;
	if (type1 == "prog_line") {
		type1 = "stmt";
	}
	if (type2 == "prog_line") {
		type2 = "stmt";
	}
	if ((type1 == "stmt" && type2 == "stmt")) {
		return parentTable;
	}
	STMT_LIST list1, list2;
	if (type1 == "stmt" && type2 != "stmt") {
		list1 = PKBStmt::getStmts();
		list2 = PKBStmt::getStmtsByType(type2);
		for (auto iter2 : list2) {
			s2 = iter2.front();
			for (auto vectorIter : parentTable) {
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
			for (auto vectorIter : parentTable) {
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
				for (auto vectorIter : parentTable) {
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
//Get STMT_LIST for Parent*(_,s)
STMT_LIST PKBParent::getParentTAnyEnt(STMT_TYPE type) {
	STMT_LIST resultTable, list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		for (auto vectorIter : parentTTable) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter.back());
			resultTable.emplace(tuple);
		}
	}
	else {
		list = PKBStmt::getStmtsByType(type);
		for (auto iter : list) {
			s = iter.front();
			for (auto vectorIter : parentTTable) {
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
//Get STMT_LIST for Parent*(s,_)
STMT_LIST PKBParent::getParentTEntAny(STMT_TYPE type) {
	STMT_LIST resultTable, list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		for (auto vectorIter : parentTTable) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter.front());
			resultTable.emplace(tuple);
		}
	}
	else {
		list = PKBStmt::getStmtsByType(type);
		for (auto iter : list) {
			s = iter.front();
			for (auto vectorIter : parentTTable) {
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
//Get STMT_LIST for Parent*(1,s)
STMT_LIST PKBParent::getParentTIdentEnt(STMT_NO stmtNo, STMT_TYPE type) {
	STMT_LIST resultTable, list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		for (auto vectorIter : parentTTable) {
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
			for (auto vectorIter : parentTTable) {
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
//Get STMT_LIST for Parent*(s,2)
STMT_LIST PKBParent::getParentTEntIdent(STMT_TYPE type, STMT_NO stmtNo) {
	STMT_LIST resultTable, list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		for (auto vectorIter : parentTTable) {
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
			for (auto vectorIter : parentTTable) {
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
//Get STMT_LIST for Parent*(s1,s2)
TABLE PKBParent::getParentTEntEnt(STMT_TYPE type1, STMT_TYPE type2) {
	TABLE resultTable;
	STMT_NO s1;
	STMT_NO s2;
	if (type1 == "prog_line") {
		type1 = "stmt";
	}
	if (type2 == "prog_line") {
		type2 = "stmt";
	}
	if ((type1 == "stmt" && type2 == "stmt")) {
		return parentTTable;
	}
	STMT_LIST list1, list2;
	if (type1 == "stmt" && type2 != "stmt") {
		list1 = PKBStmt::getStmts();
		list2 = PKBStmt::getStmtsByType(type2);
		for (auto iter2 : list2) {
			s2 = iter2.front();
			for (auto vectorIter : parentTTable) {
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
			for (auto vectorIter : parentTTable) {
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
				for (auto vectorIter : parentTTable) {
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
//Clear all PKB Parent, Parent* tables
void PKBParent::clear() {
	parentTable.clear();
	parentTTable.clear();
}