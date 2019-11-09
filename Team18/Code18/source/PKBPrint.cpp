#include "PKBPrint.h"

using namespace std;
TABLE PKBPrint::printTable;

//Set the print stmtNo and its variable name into PKB printTable
bool PKBPrint::setPrint(STMT_NO stmtNo, VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	tuple.push_back(varName);
	printTable.emplace(tuple);
	return true;
}
//Get variable name from printTable given the stmtNo
VAR_NAME PKBPrint::getPrintVariable(STMT_NO stmtNo) {
	for (auto vectorIter : printTable) {
		if (vectorIter.front() == stmtNo) {
			return vectorIter.back();
		}
	}
}
//Get variable list from printTable
LIST_OF_VARIABLE_NAME PKBPrint::getAllPrintVar() {
	LIST_OF_VARIABLE_NAME list;
	for (auto vectorIter : printTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.front());
		tuple.push_back(vectorIter.back());
		list.emplace(tuple);
	}
	return list;
}
//Clear the PKB printTable
void PKBPrint::clear() {
	printTable.clear();
}