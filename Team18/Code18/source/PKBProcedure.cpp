#include "PKBProcedure.h"
using namespace std;

TABLE PKBProcedure::procedureTable;
HASHMAP PKBProcedure::procByStmtTable;

//Set procedure by stmtNo
void PKBProcedure::setProcByStmt(STMT_NO stmtNo, PROC_NAME proc) {
	procByStmtTable.insert(pair<STMT_NO, PROC_NAME>(stmtNo, proc));
};

//Get procedure name by stmtNo
PROC_NAME PKBProcedure::getProcByStmt(STMT_NO stmtNo) {
	if (procByStmtTable.find(stmtNo) != procByStmtTable.end()) {
		return procByStmtTable[stmtNo];
	}
	else {
		return "";
	}
};
//Set Procedure with procedureName and its start and end stmtNo
void PKBProcedure::setProcedure(PROC_NAME procName, STMT_NO startStmtNo, STMT_LIST endStmtList) {
	for (auto vectorIter : endStmtList) {
		vector<string> tuple = vector<string>();
		STMT_NO endStmtNo = vectorIter.front();
		tuple.push_back(procName);
		tuple.push_back(startStmtNo);
		tuple.push_back(endStmtNo);
		procedureTable.emplace(tuple);
	}
};

//Get LIST_OF_PROC_NAME for Select proc
LIST_OF_PROC_NAME PKBProcedure::getProcedures() {
	LIST_OF_PROC_NAME list;
	for (auto vectorIter : procedureTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.front());
		list.emplace(tuple);
	}
	return list;
};
//Get result table for start and end stmtNo for the given procedureName
TABLE PKBProcedure::getProcedureStartEnd(PROC_NAME procName) {
	TABLE list;
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
//Clear all PKB procedure Table
void PKBProcedure::clear() {
	procedureTable.clear();
	procByStmtTable.clear();
}