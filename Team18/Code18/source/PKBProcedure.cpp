#include "PKBProcedure.h"
using namespace std;

TABLE PKBProcedure::procedureTable;
HASHMAP PKBProcedure::procByStmtTable;

//Set procedure by stmtNo
bool PKBProcedure::setProcByStmt(STMT_NO stmtNo, PROC_NAME proc) {
	procByStmtTable.insert(pair<STMT_NO, PROC_NAME>(stmtNo, proc));
	return true;
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
bool PKBProcedure::setProcedure(PROC_NAME procName, STMT_NO startStmtNo, STMT_LIST endStmtList) {
	for (auto vectorIter : endStmtList) {
		vector<string> tuple = vector<string>();
		STMT_NO endStmtNo = vectorIter.front();
		tuple.push_back(procName);
		tuple.push_back(startStmtNo);
		tuple.push_back(endStmtNo);
		procedureTable.emplace(tuple);
	}
	return true;
};

//Get Procedure Table
TABLE PKBProcedure::getProcedureTable() {
	return procedureTable;
}

//Get PROC_LIST for Select proc
PROC_LIST PKBProcedure::getProcedures() {
	PROC_LIST list;
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
bool PKBProcedure::clear() {
	procedureTable.clear();
	procByStmtTable.clear();
	return true;
}