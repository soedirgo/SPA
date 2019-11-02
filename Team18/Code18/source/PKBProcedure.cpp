#include "PKBProcedure.h"
using namespace std;

TABLE PKBProcedure::procedureTable;
TABLE PKBProcedure::procedureStartEndTable;

bool PKBProcedure::setProcedure(PROC_NAME procName, STMT_NO startStmtNo, STMT_LIST endStmtList) {
	vector<string> tuple = vector<string>();
	for (auto vectorIter : endStmtList) {
		STMT_NO endStmtNo = vectorIter.front();
		tuple.push_back(procName);
		tuple.push_back(startStmtNo);
		tuple.push_back(endStmtNo);
		procedureTable.emplace(tuple);
	}
	return true;
};

/*
bool PKBProcedure::setProcedureStartEnd(PROC_NAME procName, STMT_NO startStmtNo, STMT_NO endStmtNo) {
	TABLE procedureStartEndTable = getProcedureStartEndTable();
	for (auto vectorIter : procedureStartEndTable) {
		//check for same procedureName
		if (vectorIter.front() == procName) {
			//get the current value of endStmtNo from PKB
			//check if new endStmtNo value is bigger, if bigger insert the bigger value
			if (stoi(endStmtNo) > stoi(vectorIter[2]) ) {
				vectorIter[2] = endStmtNo;
			}
		}
		else {
			vector<string> tuple = vector<string>();
			tuple.push_back(procName);
			tuple.push_back(startStmtNo);
			tuple.push_back(endStmtNo);
			procedureStartEndTable.emplace(tuple);
		}
	}
	
	return true;
};
*/

TABLE PKBProcedure::getProcedureTable() {
	return procedureTable;
}

/*
TABLE PKBProcedure::getProcedureStartEndTable() {
	return procedureStartEndTable;
}
*/

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