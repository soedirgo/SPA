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

vector<string> NestedResult::getModifies() {
	return modifiesList;
}

vector<string> NestedResult::getUses() {
	return usesList;
}