#include "PKBPrint.h"

using namespace std;
TABLE PKBPrint::printTable;

bool PKBPrint::setPrint(VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(varName);
	printTable.emplace(tuple);
	return true;
}

VAR_LIST PKBPrint::getAllPrintVar() {
	VAR_LIST list;
	for (auto vectorIter : printTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.front());
		list.emplace(tuple);
	}
	return list;
}

bool PKBPrint::clear() {
	printTable.clear();
	return true;
}