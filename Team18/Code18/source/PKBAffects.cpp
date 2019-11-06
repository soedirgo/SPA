#include "PKBAffects.h"
#include "PKBStmt.h"
#include <system_error>

using namespace std;

TABLE PKBAffects::affectsTable;
TABLE PKBAffects::affectsTTable;
TABLE PKBAffects::affectsChecked;
TABLE PKBAffects::affectsTChecked;
TABLE PKBAffects::affectsBipTable;
TABLE PKBAffects::affectsBipTTable;


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

bool PKBAffects::setAffectsBip(STMT_NO a1, STMT_NO a2) {
	vector<string> tuple = vector<string>();
	tuple.push_back(a1);
	tuple.push_back(a2);
	affectsBipTable.emplace(tuple);
	return true;
}

bool PKBAffects::setAffectsBipT(STMT_NO a1, STMT_NO a2) {
	vector<string> tuple = vector<string>();
	tuple.push_back(a1);
	tuple.push_back(a2);
	affectsBipTTable.emplace(tuple);
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
	DesignExtractor::affectsTAny();
	return !affectsTTable.empty();
}

bool PKBAffects::isAffectsTAnyIdent(STMT_NO stmtNo) {
	DesignExtractor::isAnyAffectingT(stmtNo);
	for (auto vectorIter : affectsTTable) {
		if (vectorIter.back() == stmtNo) {
			return true;
		}
	}
	return false;
}
bool PKBAffects::isAffectsTIdentAny(STMT_NO stmtNo) {
	DesignExtractor::isAnyAffectedTBy(stmtNo);
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

bool PKBAffects::isCheckedAffectsTIdentIdent(STMT_NO a1, STMT_NO a2) {
	for (auto vectorIter : affectsTTable) {
		if (vectorIter.front() == a1) {
			if (vectorIter.back() == a2) {
				return true;
			}
		}
	}
	return false;
}

bool PKBAffects::isAffectsBipAnyAny() {
	return !affectsBipTable.empty();
}
bool PKBAffects::isAffectsBipAnyIdent(STMT_NO stmtNo) {
	for (auto vectorIter : affectsBipTable) {
		if (vectorIter.back() == stmtNo) {
			return true;
		}
	}
	return false;
}
bool PKBAffects::isAffectsBipIdentAny(STMT_NO stmtNo) {
	for (auto vectorIter : affectsBipTable) {
		if (vectorIter.front() == stmtNo) {
			return true;
		}
	}
	return false;
}
bool PKBAffects::isAffectsBipIdentIdent(STMT_NO a1, STMT_NO a2) {
	for (auto vectorIter : affectsBipTable) {
		if (vectorIter.front() == a1) {
			if (vectorIter.back() == a2) {
				return true;
			}
		}
	}
	return false;
}

bool PKBAffects::isAffectsBipTAnyAny() {
	return !affectsBipTTable.empty();
}
bool PKBAffects::isAffectsBipTAnyIdent(STMT_NO stmtNo) {
	for (auto vectorIter : affectsBipTTable) {
		if (vectorIter.back() == stmtNo) {
			return true;
		}
	}
	return false;
}
bool PKBAffects::isAffectsBipTIdentAny(STMT_NO stmtNo) {
	for (auto vectorIter : affectsBipTTable) {
		if (vectorIter.front() == stmtNo) {
			return true;
		}
	}
	return false;
}
bool PKBAffects::isAffectsBipTIdentIdent(STMT_NO a1, STMT_NO a2) {
	for (auto vectorIter : affectsBipTTable) {
		if (vectorIter.front() == a1) {
			if (vectorIter.back() == a2) {
				return true;
			}
		}
	}
	return false;
}

//NEW EVALUATION API
STMT_LIST PKBAffects::getAffectsAnyEnt() {
	DesignExtractor::affectsAll();
	STMT_LIST resultTable;
	for (auto vectorIter : affectsTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.back());
		resultTable.emplace(tuple);
	}
	return resultTable;
}

STMT_LIST PKBAffects::getAffectsEntAny() {
	DesignExtractor::affectsAll();
	STMT_LIST resultTable;
	for (auto vectorIter : affectsTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.front());
		resultTable.emplace(tuple);
	}
	return resultTable;
}

STMT_LIST PKBAffects::getAffectsIdentEnt(STMT_NO stmtNo) {
	DesignExtractor::affectedBy(stmtNo);
	STMT_LIST resultTable;
	for (auto vectorIter : affectsTable) {
		if (vectorIter.front() == stmtNo) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter.back());
			resultTable.emplace(tuple);
		}
	}
	return resultTable;
}

STMT_LIST PKBAffects::getAffectsEntIdent(STMT_NO stmtNo) {
	DesignExtractor::isAffecting(stmtNo);
	STMT_LIST resultTable;
	for (auto vectorIter : affectsTable) {
		vector<string> tuple = vector<string>();
		if (vectorIter.back() == stmtNo) {
			tuple.push_back(vectorIter.front());
			resultTable.emplace(tuple);
		}
	}
	return resultTable;
}

TABLE PKBAffects::getAffectsEntEnt() {
	DesignExtractor::affectsAll();
	return affectsTable;
}

STMT_LIST PKBAffects::getAffectsSelf() {
	DesignExtractor::isAffectsSelf();
	STMT_LIST resultTable;
	for (auto vectorIter : affectsTable) {
		vector<string> tuple = vector<string>();
		if (vectorIter.front() == vectorIter.back()) {
			tuple.push_back(vectorIter.front());
			resultTable.emplace(tuple);
		}
	}
	return resultTable;
}

STMT_LIST PKBAffects::getAffectsTAnyEnt() {
	DesignExtractor::affectsTAll();
	STMT_LIST resultTable;
	for (auto vectorIter : affectsTTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.back());
		resultTable.emplace(tuple);
	}
	return resultTable;
}

STMT_LIST PKBAffects::getAffectsTEntAny() {
	DesignExtractor::affectsTAll();
	STMT_LIST resultTable;
	for (auto vectorIter : affectsTTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.front());
		resultTable.emplace(tuple);
	}
	return resultTable;
}

STMT_LIST PKBAffects::getAffectsTIdentEnt(STMT_NO stmtNo) {
	DesignExtractor::affectedTBy(stmtNo);
	STMT_LIST resultTable;
	for (auto vectorIter : affectsTTable) {	
		if (vectorIter.front() == stmtNo) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter.back());
			resultTable.emplace(tuple);
		}
	}
	return resultTable;
}

STMT_LIST PKBAffects::getAffectsTEntIdent(STMT_NO stmtNo) {
	DesignExtractor::isAffectingT(stmtNo);
	STMT_LIST resultTable;
	for (auto vectorIter : affectsTTable) {
		if (vectorIter.back() == stmtNo) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter.front());
			resultTable.emplace(tuple);
		}
	}
	return resultTable;
}

TABLE PKBAffects::getAffectsTEntEnt() {
	DesignExtractor::affectsTAll();
	return affectsTTable;
}

STMT_LIST PKBAffects::getAffectsTSelf() {
	DesignExtractor::isAffectsTSelf();
	STMT_LIST resultTable;
	for (auto vectorIter : affectsTTable) {
		vector<string> tuple = vector<string>();
		if (vectorIter.front() == vectorIter.back()) {
			tuple.push_back(vectorIter.front());
			resultTable.emplace(tuple);
		}
	}
	return resultTable;
}

STMT_LIST PKBAffects::getAffectsBipAnyEnt() {
	STMT_LIST resultTable;
	for (auto vectorIter : affectsBipTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.back());
		resultTable.emplace(tuple);
	}
	return resultTable;
}

STMT_LIST PKBAffects::getAffectsBipEntAny() {
	STMT_LIST resultTable;
	for (auto vectorIter : affectsBipTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.front());
		resultTable.emplace(tuple);
	}
	return resultTable;
}

STMT_LIST PKBAffects::getAffectsBipIdentEnt(STMT_NO stmtNo) {
	STMT_LIST resultTable;
	for (auto vectorIter : affectsBipTable) {
		if (vectorIter.front() == stmtNo) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter.back());
			resultTable.emplace(tuple);
		}
	}
	return resultTable;
}

STMT_LIST PKBAffects::getAffectsBipEntIdent(STMT_NO stmtNo) {
	STMT_LIST resultTable;
	for (auto vectorIter : affectsBipTable) {
		vector<string> tuple = vector<string>();
		if (vectorIter.back() == stmtNo) {
			tuple.push_back(vectorIter.front());
			resultTable.emplace(tuple);
		}
	}
	return resultTable;
}

TABLE PKBAffects::getAffectsBipEntEnt() {
	return affectsBipTable;
}

STMT_LIST PKBAffects::getAffectsBipSelf() {
	STMT_LIST resultTable;
	for (auto vectorIter : affectsBipTable) {
		vector<string> tuple = vector<string>();
		if (vectorIter.front() == vectorIter.back()) {
			tuple.push_back(vectorIter.front());
			resultTable.emplace(tuple);
		}
	}
	return resultTable;
}

STMT_LIST PKBAffects::getAffectsBipTAnyEnt() {
	STMT_LIST resultTable;
	for (auto vectorIter : affectsBipTTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.back());
		resultTable.emplace(tuple);
	}
	return resultTable;
}

STMT_LIST PKBAffects::getAffectsBipTEntAny() {
	STMT_LIST resultTable;
	for (auto vectorIter : affectsBipTTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.front());
		resultTable.emplace(tuple);
	}
	return resultTable;
}

STMT_LIST PKBAffects::getAffectsBipTIdentEnt(STMT_NO stmtNo) {
	STMT_LIST resultTable;
	for (auto vectorIter : affectsBipTTable) {
		if (vectorIter.front() == stmtNo) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter.back());
			resultTable.emplace(tuple);
		}
	}
	return resultTable;
}

STMT_LIST PKBAffects::getAffectsBipTEntIdent(STMT_NO stmtNo) {
	STMT_LIST resultTable;
	for (auto vectorIter : affectsBipTTable) {
		vector<string> tuple = vector<string>();
		if (vectorIter.back() == stmtNo) {
			tuple.push_back(vectorIter.front());
			resultTable.emplace(tuple);
		}
	}
	return resultTable;
}

TABLE PKBAffects::getAffectsBipTEntEnt() {
	return affectsBipTTable;
}

STMT_LIST PKBAffects::getAffectsBipTSelf() {
	STMT_LIST resultTable;
	for (auto vectorIter : affectsBipTTable) {
		vector<string> tuple = vector<string>();
		if (vectorIter.front() == vectorIter.back()) {
			tuple.push_back(vectorIter.front());
			resultTable.emplace(tuple);
		}
	}
	return resultTable;
}

