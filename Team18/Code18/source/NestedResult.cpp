#include <string>
#include <utility>
#include "NestedResult.h"
using namespace std;

NestedResult::NestedResult() {
	lastStmtNo = 0;
}

void NestedResult::addModifies(string var) {
	modifiesList.push_back(var);
}

void NestedResult::addUses(string var) {
	usesList.push_back(var);
}

void NestedResult::addCondExpr(string var) {
	condExprList.push_back(var);
}

void NestedResult::addCalls(string proc) {
	callList.push_back(proc);
}

void NestedResult::setProcName(string name) {
	procName = name;
}

vector<string> NestedResult::getModifies() {
	return modifiesList;
}

vector<string> NestedResult::getUses() {
	return usesList;
}

vector<string> NestedResult::getCondExpr() {
	return condExprList;
}

vector<string> NestedResult::getCallList() {
	return callList;
}

string NestedResult::getProcName() {
	return procName;
}
