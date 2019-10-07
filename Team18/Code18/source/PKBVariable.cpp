#include "PKBVariable.h"
using namespace std;

unordered_set<string> PKBVariable::varTable;

bool PKBVariable::setVar(VAR_NAME varName) {
	varTable.emplace(varName);
	return true;
}

VAR_LIST PKBVariable::getAllVar() {
	return varTable;
}

bool PKBVariable::clear() {
	varTable.clear();
	return true;
}

/*
bool PKBVariable::isVarExist(string varName) {
	//return true if element is found
	return (varTable.find(varName) != varTable.end());
}
*/
