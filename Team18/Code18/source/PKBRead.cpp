#include "PKBRead.h"

using namespace std;
unordered_set<vector<string>, VectorDoubleStringHash> PKBRead::readTable;

bool PKBRead::setRead(STMT_NO stmtNo, VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	tuple.push_back(varName);
	readTable.emplace(tuple);
	return true;
}

VAR_LIST PKBRead::getReadStmt(VAR_NAME varName) {
	VAR_LIST list;
	for (auto vectorIter : readTable) {
		vector<string> tuple = vector<string>();
		if (vectorIter.back() == varName) {
			tuple.push_back(vectorIter.front());
			list.emplace(tuple);
		}
	}
	return list;
}

VAR_NAME PKBRead::getReadVar(STMT_NO stmtNo) {
	for (auto vectorIter : readTable) {
		if (vectorIter.front() == stmtNo) {
			return vectorIter.back();
		}
	}
	return "";
}

bool PKBRead::clear() {
	readTable.clear();
	return true;
}