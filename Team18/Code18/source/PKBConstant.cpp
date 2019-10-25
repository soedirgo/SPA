#include "PKBConstant.h"
using namespace std;

TABLE PKBConstant::constantTable;

bool PKBConstant::setConstant(CONST_VAL constValue) {
	vector<string> tuple = vector<string>();
	tuple.push_back(constValue);
	constantTable.emplace(tuple);
	return true;
}

CONST_LIST PKBConstant::getConstants() {
	CONST_LIST list;
	for (auto vectorIter : constantTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.back());
		list.emplace(tuple);
	}
	return list;
}

bool PKBConstant::clear() {
	constantTable.clear();
	return true;
}
