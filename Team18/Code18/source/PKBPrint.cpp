#include "PKBPrint.h"

using namespace std;
unordered_set<vector<string>, VectorDoubleStringHash> PKBPrint::printTable;

bool PKBPrint::setPrint(STMT_NO stmtNo, VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	tuple.push_back(varName);
	printTable.emplace(tuple);
	return true;
}

VAR_LIST PKBPrint::getPrintVar(STMT_NO stmtNo) {
	VAR_LIST list;
	for (auto vectorIter : printTable) {
		vector<string> tuple = vector<string>();
		if (vectorIter.front() == stmtNo) {
			tuple.push_back(vectorIter.back());
			list.emplace(tuple);
		}
	}
	return list;
}

bool PKBPrint::clear() {
	printTable.clear();
	return true;
}