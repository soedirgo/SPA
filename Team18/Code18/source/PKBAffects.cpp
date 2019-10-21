#include "PKBAffects.h"
#include "PKBStmt.h"
#include <system_error>

using namespace std;

TABLE PKBAffects::affectsTable;
TABLE PKBAffects::affectsTTable;

bool PKBAffects::clear() {
	affectsTable.clear();
	affectsTTable.clear();
	return true;
}

bool PKBAffects::setAffects(STMT_NO a1, STMT_NO a2) {
	vector<string> tuple = vector<string>();
	tuple.push_back(a1);
	tuple.push_back(a2);
	affectsTable.emplace(tuple);
	return true;
}

bool PKBAffects::setAffectsT(STMT_NO a1, STMT_NO a2) {
	vector<string> tuple = vector<string>();
	tuple.push_back(a1);
	tuple.push_back(a2);
	affectsTTable.emplace(tuple);
	return true;
}

bool PKBAffects::isAffectsAnyAny() {
	bool status = !affectsTable.empty();
	clear();
	return status;
}
bool PKBAffects::isAffectsAnyIdent(STMT_NO stmtNo) {
	clear();
	for (auto vectorIter : affectsTable) {
		if (vectorIter.back() == stmtNo) {
			clear();
			return true;
		}
	}
	clear();
	return false;
}
bool PKBAffects::isAffectsIdentAny(STMT_NO stmtNo) {
	clear();
	for (auto vectorIter : affectsTable) {
		if (vectorIter.front() == stmtNo) {
			clear();
			return true;
		}
	}
	clear();
	return false;
}
bool PKBAffects::isAffectsIdentIdent(STMT_NO a1, STMT_NO a2) {
	clear();
	for (auto vectorIter : affectsTable) {
		if (vectorIter.front() == a1) {
			if (vectorIter.back() == a2) {
				clear();
				return true;
			}
		}
	}
	clear();
	return false;
}

bool PKBAffects::isAffectsTAnyAny() {
	return !affectsTTable.empty();
}
bool PKBAffects::isAffectsTAnyIdent(STMT_NO stmtNo) {
	for (auto vectorIter : affectsTTable) {
		if (vectorIter.back() == stmtNo) {
			return true;
		}
	}
	return false;
}
bool PKBAffects::isAffectsTIdentAny(STMT_NO stmtNo) {
	for (auto vectorIter : affectsTTable) {
		if (vectorIter.front() == stmtNo) {
			return true;
		}
	}
	return false;
}
bool PKBAffects::isAffectsTIdentIdent(STMT_NO a1, STMT_NO a2) {
	for (auto vectorIter : affectsTTable) {
		if (vectorIter.front() == a1) {
			if (vectorIter.back() == a2) {
				return true;
			}
		}
	}
	return false;
}

//NEW EVALUATION API
TABLE PKBAffects::getAffectsAnyEnt() {
	clear();
	PROC_LIST resultTable;
	LINE_LIST list;
	PROG_LINE n;
	list = PKBStmt::getAllStmt();
	for (auto iter : list) {
		n = iter.front();
		for (auto vectorIter : affectsTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.back() == n) {
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	clear();
	return resultTable;
}

TABLE PKBAffects::getAffectsEntAny() {
	clear();
	PROC_LIST resultTable;
	LINE_LIST list;
	PROG_LINE n;
	list = PKBStmt::getAllStmt();
	for (auto iter : list) {
		n = iter.front();
		for (auto vectorIter : affectsTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == n) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	clear();
	return resultTable;
}

TABLE PKBAffects::getAffectsIdentEnt(STMT_NO stmtNo) {
	clear();
	PROC_LIST resultTable;
	LINE_LIST list;
	PROG_LINE n;
	list = PKBStmt::getAllStmt();
	for (auto iter : list) {
		n = iter.front();
		for (auto vectorIter : affectsTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == stmtNo && vectorIter.back() == n) {
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	clear();
	return resultTable;
}

TABLE PKBAffects::getAffectsEntIdent(STMT_NO stmtNo) {
	clear();
	PROC_LIST resultTable;
	LINE_LIST list;
	PROG_LINE n;
	list = PKBStmt::getAllStmt();
	for (auto iter : list) {
		n = iter.front();
		for (auto vectorIter : affectsTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == n && vectorIter.back() == stmtNo) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	clear();
	return resultTable;
}

TABLE PKBAffects::getAffectsEntEnt() {
	TABLE resultTable = affectsTable;
	clear();
	return resultTable;
}

TABLE PKBAffects::getAffectsSelf() {
	clear();
	STMT_LIST resultTable;
	STMT_LIST list;
	STMT_NO s;
	list = PKBStmt::getAllStmt();
	for (auto iter1 : list) {
		s = iter1.front();
		for (auto vectorIter : affectsTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == s && vectorIter.back() == s) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	clear();
	return resultTable;
}

TABLE PKBAffects::getAffectsTAnyEnt() {
	PROC_LIST resultTable;
	LINE_LIST list;
	PROG_LINE n;
	list = PKBStmt::getAllStmt();
	for (auto iter : list) {
		n = iter.front();
		for (auto vectorIter : affectsTTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.back() == n) {
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBAffects::getAffectsTEntAny() {
	PROC_LIST resultTable;
	LINE_LIST list;
	PROG_LINE n;
	list = PKBStmt::getAllStmt();
	for (auto iter : list) {
		n = iter.front();
		for (auto vectorIter : affectsTTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == n) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBAffects::getAffectsTIdentEnt(STMT_NO stmtNo) {
	PROC_LIST resultTable;
	LINE_LIST list;
	PROG_LINE n;
	list = PKBStmt::getAllStmt();
	for (auto iter : list) {
		n = iter.front();
		for (auto vectorIter : affectsTTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == stmtNo && vectorIter.back() == n) {
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBAffects::getAffectsTEntIdent(STMT_NO stmtNo) {
	PROC_LIST resultTable;
	LINE_LIST list;
	PROG_LINE n;
	list = PKBStmt::getAllStmt();
	for (auto iter : list) {
		n = iter.front();
		for (auto vectorIter : affectsTTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == n && vectorIter.back() == stmtNo) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBAffects::getAffectsTEntEnt() {
	return affectsTTable;
}

TABLE PKBAffects::getAffectsTSelf() {
	STMT_LIST resultTable;
	STMT_LIST list;
	STMT_NO s;
	list = PKBStmt::getAllStmt();
	for (auto iter1 : list) {
		s = iter1.front();
		for (auto vectorIter : affectsTTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == s && vectorIter.back() == s) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}
