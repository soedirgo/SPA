#include "PKBPattern.h"
#include "PKBModifies.h"

using namespace std;
TABLE PKBPattern::patternIfTable;
TABLE PKBPattern::patternWhileTable;
TABLE PKBPattern::patternAssignTable;

TABLE PKBPattern::getAssignPatternTable() {
	return patternAssignTable;
}

//Set If Pattern into PKB
bool PKBPattern::setIfPattern(STMT_NO stmtNo, VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	tuple.push_back(varName);
	patternIfTable.emplace(tuple);
	return true;
}
//Get STMT_LIST for pattern ifs(_, _, _)
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
//Get STMT_LIST for pattern ifs(“x”, _, _)
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
//Get result table for pattern ifs(v, _, _)
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
//Set While Pattern into PKB
bool PKBPattern::setWhilePattern(STMT_NO stmtNo, VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	tuple.push_back(varName);
	patternWhileTable.emplace(tuple);
	return true;
}
//Get STMT_LIST for pattern w(_, _)
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
//Get STMT_LIST for pattern w(“x”, _)
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
//Get result table for pattern w(v, _)
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
//Set Assign Pattern into PKB
bool PKBPattern::setAssignPattern(STMT_NO stmtNo, EXPR_SPEC pattern) {
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	tuple.push_back(pattern);
	patternAssignTable.emplace(tuple);
	return true;
}
//Get STMT_LIST for pattern a(_, _)
TABLE PKBPattern::getPatternAssignAnyAny() {
	TABLE resultTable;
	for (auto vectorIter : patternAssignTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.front());
		resultTable.emplace(tuple);
	}
	return resultTable;
}
//Get STMT_LIST for pattern a(_, _“a+b”_)
STMT_LIST PKBPattern::getPatternAssignAnyPartial(EXPR_SPEC expression) {
	STMT_LIST resultTable;
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
//Get STMT_LIST for pattern a(_, “a+b”)
STMT_LIST PKBPattern::getPatternAssignAnyFull(EXPR_SPEC expression) {
	STMT_LIST resultTable;
	for (auto vectorIter : patternAssignTable) {
		vector<string> tuple = vector<string>();
		if (vectorIter.back() == expression) {
			tuple.push_back(vectorIter.front());
			resultTable.emplace(tuple);
		}
	}
	return resultTable;
}
//Get STMT_LIST for pattern a(“x”, _)
STMT_LIST PKBPattern::getPatternAssignIdentAny(VAR_NAME varName) {
	STMT_LIST resultTable;
	resultTable = PKBModifies::getModifiesSEntIdent("assign",varName);
	return resultTable;
}
//Get STMT_LIST for pattern a(“x”, _“a+b”_)
STMT_LIST PKBPattern::getPatternAssignIdentPartial(VAR_NAME varName, EXPR_SPEC expression) {
	STMT_LIST resultTable;
	STMT_LIST list;
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
//Get STMT_LIST for pattern a(“x”, “a + b”)
STMT_LIST PKBPattern::getPatternAssignIdentFull(VAR_NAME varName, EXPR_SPEC expression) {
	STMT_LIST resultTable;
	STMT_LIST list;
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
//Get result table for pattern a(v, _)
TABLE PKBPattern::getPatternAssignEntAny() {
	TABLE resultTable;
	resultTable = PKBModifies::getModifiesSEntEnt("assign");
	return resultTable;
}
//Get result talbe for pattern a(v, _“a+b”_)
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
//Get result talbe for pattern a(v, “a+b”)
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


void PKBPattern::clear() {
	patternIfTable.clear();
	patternWhileTable.clear();
	patternAssignTable.clear();
}