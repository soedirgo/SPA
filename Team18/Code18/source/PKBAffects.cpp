#include "PKBAffects.h"
#include "PKBStmt.h"
#include <system_error>

using namespace std;

TABLE PKBAffects::affectsTable;
TABLE PKBAffects::affectsTTable;
TABLE PKBAffects::affectsChecked;
TABLE PKBAffects::affectsTChecked;

bool PKBAffects::clear() {
	affectsTable.clear();
	affectsTTable.clear();
	affectsChecked.clear();
	affectsTChecked.clear();
	return true;
}

bool PKBAffects::isCheckedAffects(STMT_NO a1, STMT_NO a2) {
	for (auto vectorIter : affectsChecked) {
		if (vectorIter.front() == a1) {
			if (vectorIter.back() == a2) {
				return true;
			}
		}
	}
	return false;
}

bool PKBAffects::setCheckedAffects(STMT_NO a1, STMT_NO a2) {
	vector<string> tuple = vector<string>();
	tuple.push_back(a1);
	tuple.push_back(a2);
	affectsChecked.emplace(tuple);
	return true;
}

bool PKBAffects::isCheckedAffectsT(STMT_NO a1, STMT_NO a2) {
	for (auto vectorIter : affectsTChecked) {
		if (vectorIter.front() == a1) {
			if (vectorIter.back() == a2) {
				return true;
			}
		}
	}
	return false;
}

bool PKBAffects::setCheckedAffectsT(STMT_NO a1, STMT_NO a2) {
	vector<string> tuple = vector<string>();
	tuple.push_back(a1);
	tuple.push_back(a2);
	affectsTChecked.emplace(tuple);
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
	DesignExtractor::affectsAny();
	bool status = !affectsTable.empty();
	return status;
}
bool PKBAffects::isAffectsAnyIdent(STMT_NO stmtNo) {
	DesignExtractor::isAnyAffecting(stmtNo);
	for (auto vectorIter : affectsTable) {
		if (vectorIter.back() == stmtNo) {
			return true;
		}
	}
	return false;
}
bool PKBAffects::isAffectsIdentAny(STMT_NO stmtNo) {
	DesignExtractor::isAnyAffectedBy(stmtNo);
	for (auto vectorIter : affectsTable) {
		if (vectorIter.front() == stmtNo) {
			return true;
		}
	}
	return false;
}
bool PKBAffects::isAffectsIdentIdent(STMT_NO a1, STMT_NO a2) {
	DesignExtractor::isAffects(a1, a2);
	for (auto vectorIter : affectsTable) {
		if (vectorIter.front() == a1) {
			if (vectorIter.back() == a2) {
				return true;
			}
		}
	}
	return false;
}

bool PKBAffects::isCheckedAffectsIdentIdent(STMT_NO a1, STMT_NO a2) {
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
	DesignExtractor::affectsTAll();
	return !affectsTTable.empty();
}

bool PKBAffects::isAffectsTAnyIdent(STMT_NO stmtNo) {
	DesignExtractor::isAffectingT(stmtNo);
	for (auto vectorIter : affectsTTable) {
		if (vectorIter.back() == stmtNo) {
			return true;
		}
	}
	return false;
}
bool PKBAffects::isAffectsTIdentAny(STMT_NO stmtNo) {
	DesignExtractor::affectedTBy(stmtNo);
	for (auto vectorIter : affectsTTable) {
		if (vectorIter.front() == stmtNo) {
			return true;
		}
	}
	return false;
}
bool PKBAffects::isAffectsTIdentIdent(STMT_NO a1, STMT_NO a2) {
	DesignExtractor::isAffectsT(a1, a2);
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
	DesignExtractor::affectsAll();
	PROC_LIST resultTable;
	LINE_LIST list;
	PROG_LINE n;
	list = PKBStmt::getStmts();
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
	DesignExtractor::affectsAll();
	PROC_LIST resultTable;
	LINE_LIST list;
	PROG_LINE n;
	list = PKBStmt::getStmts();
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
	DesignExtractor::affectedBy(stmtNo);
	PROC_LIST resultTable;
	LINE_LIST list;
	PROG_LINE n;
	list = PKBStmt::getStmts();
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
	DesignExtractor::isAffecting(stmtNo);
	PROC_LIST resultTable;
	LINE_LIST list;
	PROG_LINE n;
	list = PKBStmt::getStmts();
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
	DesignExtractor::affectsAll();
	TABLE resultTable = affectsTable;
	return resultTable;
}

TABLE PKBAffects::getAffectsSelf() {
	DesignExtractor::isAffectsSelf();
	STMT_LIST resultTable;
	STMT_LIST list;
	STMT_NO s;
	list = PKBStmt::getStmts();
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
	return resultTable;
}

TABLE PKBAffects::getAffectsTAnyEnt() {
	DesignExtractor::affectsTAll();
	PROC_LIST resultTable;
	LINE_LIST list;
	PROG_LINE n;
	list = PKBStmt::getStmts();
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
	DesignExtractor::affectsTAll();
	PROC_LIST resultTable;
	LINE_LIST list;
	PROG_LINE n;
	list = PKBStmt::getStmts();
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
	DesignExtractor::affectedTBy(stmtNo);
	PROC_LIST resultTable;
	LINE_LIST list;
	PROG_LINE n;
	list = PKBStmt::getStmts();
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
	DesignExtractor::isAffectingT(stmtNo);
	PROC_LIST resultTable;
	LINE_LIST list;
	PROG_LINE n;
	list = PKBStmt::getStmts();
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
	DesignExtractor::affectsTAll();
	return affectsTTable;
}

TABLE PKBAffects::getAffectsTSelf() {
	DesignExtractor::isAffectsTSelf();
	STMT_LIST resultTable;
	STMT_LIST list;
	STMT_NO s;
	list = PKBStmt::getStmts();
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
