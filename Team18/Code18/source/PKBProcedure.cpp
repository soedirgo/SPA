#include "PKBProcedure.h"
using namespace std;

unordered_set<vector<string>, VectorSingleStringHash> PKBProcedure::procedureTable;

bool PKBProcedure::setProc(PROC_NAME procName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(procName);
	procedureTable.emplace(tuple);
	return true;
};

PROC_LIST PKBProcedure::getAllProc() {
	return procedureTable;
};

bool PKBProcedure::clear() {
	procedureTable.clear();
	return true;
}