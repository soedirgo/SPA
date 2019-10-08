#include "PKBConstant.h"
using namespace std;

unordered_set<vector<string>, VectorDoubleStringHash> PKBConstant::constantTable;

bool PKBConstant::setConstant(CONST_VALUE constValue, STMT_NO stmtNo) {
	vector<string> tuple = vector<string>();
	tuple.push_back(constValue);
	tuple.push_back(stmtNo);
	constantTable.emplace(tuple);
	return true;
}

STMT_LIST PKBConstant::getAllConstantStmtByVal(CONST_VALUE constValue) {
	STMT_LIST list;
	for (auto vectorIter : constantTable) {
		vector<string> tuple = vector<string>();
		if (vectorIter.front() == constValue) {
			tuple.push_back(vectorIter.back());
			list.emplace(tuple);
		}
	}
	return list;
}

CONST_LIST PKBConstant::getAllConstantVal() {
	CONST_LIST constList;
	for (auto vectorIter : constantTable) {
		constList.emplace(vectorIter.front());
	}
	return constList;
}


bool PKBConstant::clear() {
	constantTable.clear();
	return true;
}
