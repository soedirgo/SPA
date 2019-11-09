#include "PKBVariable.h"
using namespace std;

TABLE PKBVariable::varTable;

//Set the variable name into the PKB varTable
bool PKBVariable::setVariable(VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(varName);
	varTable.emplace(tuple);
	return true;
}
//Get Variable List for Select variable
LIST_OF_VARIABLE_NAME PKBVariable::getVariables() {
	return varTable;
}
//Clear the PKB data for varTable
void PKBVariable::clear() {
	varTable.clear();
}
