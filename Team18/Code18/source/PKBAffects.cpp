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
	return !affectsTable.empty();
}
bool PKBAffects::isAffectsAnyIdent(STMT_NO stmtNo) {
	for (auto vectorIter : affectsTable) {
		if (vectorIter.back() == stmtNo) {
			return true;
		}
	}
	return false;
}
bool PKBAffects::isAffectsIdentAny(STMT_NO stmtNo) {
	for (auto vectorIter : affectsTable) {
		if (vectorIter.front() == stmtNo) {
			return true;
		}
	}
	return false;
}
bool PKBAffects::isAffectsIdentIdent(STMT_NO a1, STMT_NO a2) {
	for (auto vectorIter : affectsTable) {
		if (vectorIter.front() == a1) {
			if (vectorIter.back() == a2) {
				return true;
			}
		}
	}
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
	return resultTable;
}

TABLE PKBAffects::getAffectsEntAny() {
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
	return resultTable;
}

TABLE PKBAffects::getAffectsIdentEnt(STMT_NO stmtNo) {
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
	return resultTable;
}

TABLE PKBAffects::getAffectsEntIdent(STMT_NO stmtNo) {
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
	return resultTable;
}

TABLE PKBAffects::getAffectsEntEnt() {
	return affectsTable;
}
