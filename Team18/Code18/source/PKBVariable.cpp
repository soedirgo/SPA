#include "PKBVariable.h"
using namespace std;

TABLE PKBVariable::varTable;

bool PKBVariable::setVar(VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(varName);
	varTable.emplace(tuple);
	return true;
}

VAR_LIST PKBVariable::getVariable() {
	return varTable;
}

bool PKBVariable::clear() {
	varTable.clear();
	return true;
}
