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

VAR_LIST PKBRead::getReadVar(STMT_NO stmtNo) {
	VAR_LIST list;
	vector<string> tuple = vector<string>();
	for (auto vectorIter : readTable) {
		if (vectorIter.front() == stmtNo) {
			tuple.push_back(vectorIter.back());
			list.emplace(tuple);
		}
	}
	return list;
}

bool PKBRead::clear() {
	readTable.clear();
	return true;
}