#include "PKBPrint.h"

using namespace std;
unordered_set<vector<string>, VectorHash> PKBPrint::printTable;

bool PKBPrint::setPrint(STMT_NO stmtNo, VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(to_string(stmtNo));
	tuple.push_back(varName);
	printTable.emplace(tuple);
	return true;
}

unordered_set<string> PKBPrint::getPrintVar(STMT_NO stmtNo) {
	unordered_set<string> stmtList;
	for (auto vectorIter : printTable) {
		if (vectorIter.front() == to_string(stmtNo)) {
			stmtList.emplace(vectorIter.back());
		}
	}
	return stmtList;
}

bool PKBPrint::clear() {
	printTable.clear();
	return true;
}