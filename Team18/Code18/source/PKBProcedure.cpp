#include "PKBProcedure.h"
using namespace std;

unordered_set<string> PKBProcedure::procedureTable;

unordered_set<string> PKBProcedure::getAllProc() {
	return procedureTable;
};


bool PKBProcedure::setProc(string procName) {
	procedureTable.insert(procName);
	return true;
};

bool PKBProcedure::clear() {
	procedureTable.clear();
	return true;
}