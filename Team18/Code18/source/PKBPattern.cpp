#include "PKBPattern.h"
#include "PKBModifies.h"

using namespace std;
TABLE PKBPattern::patternIfTable;
TABLE PKBPattern::patternWhileTable;
TABLE PKBPattern::patternAssignTable;

bool PKBPattern::setIfPattern(STMT_NO stmtNo, VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	tuple.push_back(varName);
	patternIfTable.emplace(tuple);
	return true;
}

STMT_LIST PKBPattern::getPatternIfAny() {
	STMT_LIST resultTable;
	STMT_LIST list;
	for (auto vectorIter : patternIfTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.front());
		resultTable.emplace(tuple);
	}
	return resultTable;
}

STMT_LIST PKBPattern::getPatternIfIdent(VAR_NAME varName) {
	STMT_LIST resultTable;
	STMT_LIST list;
	for (auto vectorIter : patternIfTable) {
		vector<string> tuple = vector<string>();
		if (vectorIter.back() == varName) {
			tuple.push_back(vectorIter.front());
			resultTable.emplace(tuple);
		}
	}
	return resultTable;
}

TABLE PKBPattern::getPatternIfEnt() {
	STMT_LIST resultTable;
	STMT_LIST list;
	for (auto vectorIter : patternIfTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.front());
		tuple.push_back(vectorIter.back());
		resultTable.emplace(tuple);
	}
	return resultTable;
}

bool PKBPattern::setWhilePattern(STMT_NO stmtNo, VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	tuple.push_back(varName);
	patternWhileTable.emplace(tuple);
	return true;
}

STMT_LIST PKBPattern::getPatternWhileAny() {
	STMT_LIST resultTable;
	STMT_LIST list;
	for (auto vectorIter : patternWhileTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.front());
		resultTable.emplace(tuple);
	}
	return resultTable;
}

STMT_LIST PKBPattern::getPatternWhileIdent(VAR_NAME varName) {
	STMT_LIST resultTable;
	STMT_LIST list;
	for (auto vectorIter : patternWhileTable) {
		vector<string> tuple = vector<string>();
		if (vectorIter.back() == varName) {
			tuple.push_back(vectorIter.front());
			resultTable.emplace(tuple);
		}
	}
	return resultTable;
}

TABLE PKBPattern::getPatternWhileEnt() {
	STMT_LIST resultTable;
	STMT_LIST list;
	for (auto vectorIter : patternWhileTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.front());
		tuple.push_back(vectorIter.back());
		resultTable.emplace(tuple);
	}
	return resultTable;
}

bool PKBPattern::setAssignPattern(STMT_NO stmtNo, EXPR_SPEC pattern) {
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	tuple.push_back(pattern);
	patternAssignTable.emplace(tuple);
	return true;
}

TABLE PKBPattern::getPatternAssignAnyAny() {
	TABLE resultTable;
	for (auto vectorIter : patternAssignTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.front());
		resultTable.emplace(tuple);
	}
	return resultTable;
}

TABLE PKBPattern::getPatternAssignAnyPartial(EXPR_SPEC expression) {
	TABLE resultTable;
	for (auto vectorIter : patternAssignTable) {
		vector<string> tuple = vector<string>();
		if (vectorIter.back().find(expression) != string::npos) {
			//found
			tuple.push_back(vectorIter.front());
			resultTable.emplace(tuple);
		}
	}
	return resultTable;
}

TABLE PKBPattern::getPatternAssignAnyFull(EXPR_SPEC expression) {
	TABLE resultTable;
	for (auto vectorIter : patternAssignTable) {
		vector<string> tuple = vector<string>();
		if (vectorIter.back() == expression) {
			tuple.push_back(vectorIter.front());
			resultTable.emplace(tuple);
		}
	}
	return resultTable;
}

TABLE PKBPattern::getPatternAssignIdentAny(VAR_NAME varName) {
	TABLE resultTable;
	resultTable = PKBModifies::getModifiesSEntIdent("assign",varName);
	return resultTable;
}

TABLE PKBPattern::getPatternAssignIdentPartial(VAR_NAME varName, EXPR_SPEC expression) {
	TABLE resultTable;
	TABLE list;
	STMT_NO stmtNo;
	list = PKBModifies::getModifiesSEntIdent("assign",varName);
	for (auto iter : list) {
		stmtNo = iter.front();
		for (auto vectorIter : patternAssignTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == stmtNo && 
				vectorIter.back().find(expression) != string::npos) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBPattern::getPatternAssignIdentFull(VAR_NAME varName, EXPR_SPEC expression) {
	TABLE resultTable;
	TABLE list;
	STMT_NO stmtNo;
	list = PKBModifies::getModifiesSEntIdent("assign", varName);
	for (auto iter : list) {
		stmtNo = iter.front();
		for (auto vectorIter : patternAssignTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == stmtNo && vectorIter.back() == expression) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBPattern::getPatternAssignEntAny() {
	TABLE resultTable;
	resultTable = PKBModifies::getModifiesSEntEnt("assign");
	return resultTable;
}

TABLE PKBPattern::getPatternAssignEntPartial(EXPR_SPEC expression) {
	TABLE resultTable;
	TABLE list;
	STMT_NO stmtNo;
	list = PKBModifies::getModifiesSEntEnt("assign");
	for (auto iter : list) {
		stmtNo = iter.front();
		for (auto vectorIter : patternAssignTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == stmtNo && 
				vectorIter.back().find(expression) != string::npos) {
				tuple.push_back(vectorIter.front());
				//Push variable
				tuple.push_back(iter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBPattern::getPatternAssignEntFull(EXPR_SPEC expression) {
	TABLE resultTable;
	TABLE list;
	STMT_NO stmtNo;
	list = PKBModifies::getModifiesSEntEnt("assign");
	for (auto iter : list) {
		stmtNo = iter.front();
		for (auto vectorIter : patternAssignTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == stmtNo && vectorIter.back() == expression) {
				tuple.push_back(vectorIter.front());
				//Push variable
				tuple.push_back(iter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}


bool PKBPattern::clear() {
	patternIfTable.clear();
	patternWhileTable.clear();
	patternAssignTable.clear();
	return true;
}