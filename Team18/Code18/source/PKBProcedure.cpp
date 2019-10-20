#include "PKBProcedure.h"
using namespace std;

TABLE PKBProcedure::procedureTable;

bool PKBProcedure::setProcedure(PROC_NAME procName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(procName);
	procedureTable.emplace(tuple);
	return true;
};

PROC_LIST PKBProcedure::getProcedures() {
	return procedureTable;
};

bool PKBProcedure::clear() {
	procedureTable.clear();
	return true;
}