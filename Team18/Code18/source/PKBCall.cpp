#include "PKBCall.h"
#include "PKBProcedure.h"

using namespace std;
unordered_set<vector<string>, VectorDoubleStringHash> PKBCall::callProcTable;
unordered_set<vector<string>, VectorDoubleStringHash> PKBCall::callStarProcTable;
unordered_set<vector<string>, VectorDoubleStringHash> PKBCall::callStmtTable;

bool PKBCall::setCallProc(PROC_NAME caller, PROC_NAME callee) {
	vector<string> tuple = vector<string>();
	tuple.push_back(caller);
	tuple.push_back(callee);
	callProcTable.emplace(tuple);
	return true;
}

bool PKBCall::setCallStmt(STMT_NO stmtNo, PROC_NAME caller) {
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	tuple.push_back(caller);
	callStmtTable.emplace(tuple);
	return true;
}

PROC_LIST PKBCall::getCalleeProc(PROC_NAME caller) {
	PROC_LIST list;
	vector<string> tuple = vector<string>();
	for (auto vectorIter : callProcTable) {
		if (vectorIter.front() == caller) {
			tuple.push_back(vectorIter.back());
			list.emplace(tuple);
		}
	}
	return list;
}

bool PKBCall::isCallRelationship(PROC_NAME caller, PROC_NAME callee) {

	for (auto vectorIter : callProcTable) {
		if (vectorIter.front() == caller) {
			if (vectorIter.back() == callee) {
				return true;
			}
		}
	}
	return false;
}

bool PKBCall::isCallStarRelationship(PROC_NAME caller, PROC_NAME callee) {

	for (auto vectorIter : callStarProcTable) {
		if (vectorIter.front() == caller) {
			if (vectorIter.back() == callee) {
				return true;
			}
		}
	}
	return false;
}

bool PKBCall::setCallStarProc(PROC_NAME caller, PROC_NAME callee) {
	vector<string> tuple = vector<string>();
	tuple.push_back(caller);
	tuple.push_back(callee);
	callStarProcTable.emplace(tuple);
	return true;
}

TABLE PKBCall::getCallProcTable() {
	return callProcTable;
}

TABLE PKBCall::getAllCallerCalleeProc() {
	return PKBCall::getResultTableGenericBoth(callProcTable);
}
TABLE PKBCall::getAllCallerProc(PROC_NAME procName) {
	return PKBCall::getResultTableGenericLeft( procName, callProcTable);
}
TABLE PKBCall::getAllCalleProc(PROC_NAME procName) {
	return PKBCall::getResultTableGenericRight(procName, callProcTable);
}

TABLE PKBCall::getAllCallerCalleeStarProc() {
	return PKBCall::getResultTableGenericBoth(callStarProcTable);
}
TABLE PKBCall::getAllCallerStarProc(PROC_NAME procName) {
	return PKBCall::getResultTableGenericLeft(procName, callStarProcTable);
}
TABLE PKBCall::getAllCalleStarProc(PROC_NAME procName) {
	return PKBCall::getResultTableGenericRight(procName, callStarProcTable);
}

bool PKBCall::clear() {
	callProcTable.clear();
	callStarProcTable.clear();
	callStmtTable.clear();
	return true;
}

TABLE PKBCall::getResultTableGenericBoth(TABLE tableName) {
	return tableName;
}

TABLE PKBCall::getResultTableGenericLeft(PROC_NAME procName, TABLE tableName) {
	TABLE resultTable;
	PROC_LIST list;
	PROC_NAME p;
	list = PKBProcedure::getAllProc();
	for (auto iter : list) {
		p = iter.front();
		for (auto vectorIter : tableName) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == p && vectorIter.back() == procName) {
				tuple.push_back(vectorIter.front());
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBCall::getResultTableGenericRight(PROC_NAME procName, TABLE tableName) {
	TABLE resultTable;
	PROC_LIST list;
	PROC_NAME p;
	list = PKBProcedure::getAllProc();
	for (auto iter : list) {
		p = iter.front();
		for (auto vectorIter : tableName) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == procName && vectorIter.back() == p) {
				tuple.push_back(vectorIter.front());
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}
