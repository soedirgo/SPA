#include "PKBProcedure.h"
using namespace std;

TABLE PKBProcedure::procedureTable;

bool PKBProcedure::setProcedure(PROC_NAME procName, STMT_NO start, STMT_NO end, STMT_NO endAlt) {
	vector<string> tuple = vector<string>();
	tuple.push_back(procName);
	tuple.push_back(start);
	tuple.push_back(end);
	tuple.push_back(endAlt);
	procedureTable.emplace(tuple);
	return true;
};

PROC_LIST PKBProcedure::getProcedures() {
	PROC_LIST list;
	for (auto vectorIter : procedureTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.front());
		list.emplace(tuple);
	}
	return list;
};

PROC_LIST PKBProcedure::getProcedureStartEnd(PROC_NAME procName) {
	PROC_LIST list;
	for (auto vectorIter : procedureTable) {
		if (procName == vectorIter[0]) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter[1]);
			tuple.push_back(vectorIter[2]);
			tuple.push_back(vectorIter[3]);
			list.emplace(tuple);
		}
	}
	return list;
};

bool PKBProcedure::clear() {
	procedureTable.clear();
	return true;
}