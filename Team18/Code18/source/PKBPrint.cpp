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

VAR_LIST PKBPrint::getPrintStmt(VAR_NAME varName) {
	VAR_LIST list;
	for (auto vectorIter : printTable) {
		vector<string> tuple = vector<string>();
		if (vectorIter.back() == varName) {
			tuple.push_back(vectorIter.front());
			list.emplace(tuple);
		}
	}
	return list;
}

VAR_NAME PKBPrint::getPrintVar(STMT_NO stmtNo) {
	for (auto vectorIter : printTable) {
		if (vectorIter.front() == stmtNo) {
			return vectorIter.back();
		}
	}
	return "";
}

bool PKBPrint::clear() {
	printTable.clear();
	return true;
}