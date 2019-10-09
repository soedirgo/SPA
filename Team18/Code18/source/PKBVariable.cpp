#include "PKBVariable.h"
using namespace std;

unordered_set<vector<string>, VectorSingleStringHash> PKBVariable::varTable;

bool PKBVariable::setVar(VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(varName);
	varTable.emplace(tuple);
	return true;
}

VAR_LIST PKBVariable::getAllVar() {
	return varTable;
}

bool PKBVariable::clear() {
	varTable.clear();
	return true;
}
