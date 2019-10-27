#include "PKBRead.h"

using namespace std;
TABLE PKBRead::readTable;

bool PKBRead::setRead(STMT_NO stmtNo, VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	tuple.push_back(varName);
	readTable.emplace(tuple);
	return true;
}

VAR_LIST PKBRead::getAllReadVar() {
	VAR_LIST list;
	for (auto vectorIter : readTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.front());
		tuple.push_back(vectorIter.back());
		list.emplace(tuple);
	}
	return list;
}

bool PKBRead::clear() {
	readTable.clear();
	return true;
}