#include "PKBProcedure.h"
using namespace std;

TABLE PKBProcedure::procedureTable;

bool PKBProcedure::setProcedure(PROC_NAME procName, STMT_NO startStmt, STMT_LIST endStmtList) {
	vector<string> tuple = vector<string>();
	for (auto vectorIter : endStmtList) {
		STMT_NO endStmt = vectorIter.front();
		tuple.push_back(procName);
		tuple.push_back(startStmt);
		tuple.push_back(endStmt);
		procedureTable.emplace(tuple);
	}
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
			list.emplace(tuple);
		}
	}
	return list;
};

bool PKBProcedure::clear() {
	procedureTable.clear();
	return true;
}