#include "PKBConstant.h"
using namespace std;

unordered_set<vector<string>, VectorDoubleStringHash> PKBConstant::constantTable;

bool PKBConstant::setConstant(STMT_NO stmtNo, CONST_VAL constValue) {
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	tuple.push_back(constValue);
	constantTable.emplace(tuple);
	return true;
}

STMT_LIST PKBConstant::getAllConstantStmtByVal(CONST_VAL constValue) {
	STMT_LIST list;
	for (auto vectorIter : constantTable) {
		vector<string> tuple = vector<string>();
		if (vectorIter.back() == constValue) {
			tuple.push_back(vectorIter.front());
			list.emplace(tuple);
		}
	}
	return list;
}

CONST_LIST PKBConstant::getAllConstantVal() {
	CONST_LIST list;
	for (auto vectorIter : constantTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.front());
		list.emplace(tuple);
	}
	return list;
}

CONST_VAL PKBConstant::getConstantValByStmt(STMT_NO stmtNo) {
	for (auto vectorIter : constantTable) {
		if (vectorIter.front() == stmtNo) {
			return vectorIter.back();
		}
	}
	return "";
}


bool PKBConstant::clear() {
	constantTable.clear();
	return true;
}
