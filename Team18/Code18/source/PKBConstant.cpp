#include "PKBConstant.h"
using namespace std;

TABLE PKBConstant::constantTable;

void PKBConstant::setConstant(CONST_VAL constValue) {
	vector<string> tuple = vector<string>();
	tuple.push_back(constValue);
	constantTable.emplace(tuple);
}

LIST_OF_CONS_VAL PKBConstant::getConstants() {
	LIST_OF_CONS_VAL list;
	for (auto vectorIter : constantTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.back());
		list.emplace(tuple);
	}
	return list;
}

void PKBConstant::clear() {
	constantTable.clear();
}
