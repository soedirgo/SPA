#include "PKBNext.h"

using namespace std;
unordered_set<vector<string>, VectorHash> PKBNext::nextTable;

bool PKBNext::setNext(PROG_LINE n1, PROG_LINE n2) {
	vector<string> tuple = vector<string>();
	tuple.push_back(to_string(n1));
	tuple.push_back(to_string(n2));
	nextTable.emplace(tuple);
	return true;
}

bool PKBNext::clear() {
	nextTable.clear();
	return true;
}