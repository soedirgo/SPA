#include "PKBCall.h"

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

PROC_NAME PKBCall::getCalledProcByStmt(STMT_NO stmtNo) {
	PROC_NAME result;

	for (auto vectorIter : callProcTable) {
		if (vectorIter.front() == stmtNo) {
			return vectorIter.back(); 
		}
	}
	return result; 

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

unordered_set<vector<string>, VectorDoubleStringHash> PKBCall::getCallProcTable() {
	return callProcTable;
}

bool PKBCall::clear() {
	callProcTable.clear();
	callStarProcTable.clear();
	callStmtTable.clear();
	return true;
}