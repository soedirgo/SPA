#include "PKBRead.h"

using namespace std;
unordered_set<vector<string>, VectorHash> PKBRead::readTable;

bool PKBRead::setRead(STMT_NO stmtNo, VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(to_string(stmtNo));
	tuple.push_back(varName);
	readTable.emplace(tuple);
	return true;
}

unordered_set<string> PKBRead::getReadVar(STMT_NO stmtNo) {
	unordered_set<string> stmtList;
	for (auto vectorIter : readTable) {
		if (vectorIter.front() == to_string(stmtNo)) {
			stmtList.emplace(vectorIter.back());
		}
	}
	return stmtList;
}

bool PKBRead::clear() {
	readTable.clear();
	return true;
}