#include "PKBConstant.h"
using namespace std;

TABLE PKBConstant::constantTable;

//Set constant value such as 1 or 2 into the PKB
void PKBConstant::setConstant(CONST_VAL constValue) {
	vector<string> tuple = vector<string>();
	tuple.push_back(constValue);
	constantTable.emplace(tuple);
}

//Returns all the constant values in the PKB into a list
LIST_OF_CONS_VAL PKBConstant::getConstants() {
	LIST_OF_CONS_VAL list;
	for (auto vectorIter : constantTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.back());
		list.emplace(tuple);
	}
	return list;
}

//Clears the constantTable in the PKB
void PKBConstant::clear() {
	constantTable.clear();
}
