#include "PKBPrint.h"

using namespace std;
TABLE PKBPrint::printTable;

bool PKBPrint::setPrint(STMT_NO stmtNo, VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	tuple.push_back(varName);
	printTable.emplace(tuple);
	return true;
}

VAR_NAME PKBPrint::getPrintVariable(STMT_NO stmtNo) {
	for (auto vectorIter : printTable) {
		if (vectorIter.front() == stmtNo) {
			return vectorIter.back();
		}
	}
}

VAR_LIST PKBPrint::getAllPrintVar() {
	VAR_LIST list;
	for (auto vectorIter : printTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.front());
		tuple.push_back(vectorIter.back());
		list.emplace(tuple);
	}
	return list;
}

bool PKBPrint::clear() {
	printTable.clear();
	return true;
}