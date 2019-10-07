#include "PKBCall.h"

using namespace std;
unordered_set<vector<string>, VectorHash> PKBCall::callProcTable;
unordered_set<vector<string>, VectorHash> PKBCall::callStmtTable;

bool PKBCall::setCallProc(PROC_NAME p, PROC_NAME q) {
	vector<string> tuple = vector<string>();
	tuple.push_back(p);
	tuple.push_back(q);
	callProcTable.emplace(tuple);
	return true;
}

bool PKBCall::setCallStmt(STMT_NO stmtNo, PROC_NAME q) {
	vector<string> tuple = vector<string>();
	tuple.push_back(to_string(stmtNo));
	tuple.push_back(q);
	callStmtTable.emplace(tuple);
	return true;
}

bool PKBCall::isCallRelationship(PROC_NAME p, PROC_NAME q) {

	for (auto vectorIter : callProcTable) {
		if (vectorIter.front() == p) {
			if (vectorIter.back() == q) {
				return true;
			}
		}
	}
	return false;
}

bool PKBCall::clear() {
	callProcTable.clear();
	callStmtTable.clear();
	return true;
}