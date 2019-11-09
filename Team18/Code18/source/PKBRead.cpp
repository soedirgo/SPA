#include "PKBRead.h"

using namespace std;
TABLE PKBRead::readTable;

//Set the read stmtNo and its variable name into PKB readTable
bool PKBRead::setRead(STMT_NO stmtNo, VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	tuple.push_back(varName);
	readTable.emplace(tuple);
	return true;
}
//Get variable name from readTable given the stmtNo
VAR_NAME PKBRead::getReadVariable(STMT_NO stmtNo) {
	for (auto vectorIter : readTable) {
		if (vectorIter.front() == stmtNo) {
			return vectorIter.back();
		}
	}
}
//Get variable list from readTable
LIST_OF_VARIABLE_NAME PKBRead::getAllReadVar() {
	LIST_OF_VARIABLE_NAME list;
	for (auto vectorIter : readTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.front());
		tuple.push_back(vectorIter.back());
		list.emplace(tuple);
	}
	return list;
}
//Clear the PKB readTable
void PKBRead::clear() {
	readTable.clear();
}