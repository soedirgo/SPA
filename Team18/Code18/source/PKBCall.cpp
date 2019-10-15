#include "PKBCall.h"
#include "PKBProcedure.h"

using namespace std;
TABLE PKBCall::callsProcTable;
TABLE PKBCall::callsTProcTable;
TABLE PKBCall::callStmtTable;

bool PKBCall::setCallProc(PROC_NAME caller, PROC_NAME callee) {
	vector<string> tuple = vector<string>();
	tuple.push_back(caller);
	tuple.push_back(callee);
	callsProcTable.emplace(tuple);
	return true;
}

bool PKBCall::setCallStmt(STMT_NO stmtNo, PROC_NAME caller) {
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	tuple.push_back(caller);
	callStmtTable.emplace(tuple);
	return true;
}

PROC_NAME PKBCall::getCallProcByStmt(STMT_NO stmtNo) {
	PROC_NAME result;

	for (auto vectorIter : callStmtTable) {
		if (vectorIter.front() == stmtNo) {
			return vectorIter.back(); 
		}
	}
	return result; 

}

PROC_LIST PKBCall::getCallerProc(PROC_NAME callee) {
	PROC_LIST list;
	vector<string> tuple = vector<string>();
	for (auto vectorIter : callsProcTable) {
		if (vectorIter.back() == callee) {
			tuple.push_back(vectorIter.front());
			list.emplace(tuple);
		}
	}
	return list;
}

PROC_LIST PKBCall::getCalleeProc(PROC_NAME caller) {
	PROC_LIST list;
	vector<string> tuple = vector<string>();
	for (auto vectorIter : callsProcTable) {
		if (vectorIter.front() == caller) {
			tuple.push_back(vectorIter.back());
			list.emplace(tuple);
		}
	}
	return list;
}

PROC_LIST PKBCall::getAllCallProc() {
	PROC_LIST list;
	vector<string> tuple = vector<string>();
	for (auto vectorIter : callsProcTable) {
		tuple.push_back(vectorIter.front());
		list.emplace(tuple);
	}
	return list;
}

bool PKBCall::setCallTProc(PROC_NAME caller, PROC_NAME callee) {
	vector<string> tuple = vector<string>();
	tuple.push_back(caller);
	tuple.push_back(callee);
	callsTProcTable.emplace(tuple);
	return true;
}

TABLE PKBCall::getCallProcTable() {
	return callsProcTable;
}

TABLE PKBCall::getCallStmtTable() {
	return callStmtTable;
}

bool PKBCall::clear() {
	callsProcTable.clear();
	callsTProcTable.clear();
	callStmtTable.clear();
	return true;
}

bool PKBCall::isCallsAnyAny() {
	return !callsProcTable.empty();
}
bool PKBCall::isCallsAnyIdent(PROC_NAME callee) {
	for (auto vectorIter : callsProcTable) {
		if (vectorIter.back() == callee) {
			return true;
		}
	}
	return false;
}
bool PKBCall::isCallsIdentAny(PROC_NAME caller) {
	for (auto vectorIter : callsProcTable) {
		if (vectorIter.front() == caller) {
			return true;
		}
	}
	return false;
}
bool PKBCall::isCallsIdentIdent(PROC_NAME caller, PROC_NAME callee) {
	for (auto vectorIter : callsProcTable) {
		if (vectorIter.front() == caller) {
			if (vectorIter.back() == callee) {
				return true;
			}
		}
	}
	return false;
}

bool PKBCall::isCallsTAnyAny() {
	return !callsTProcTable.empty();
}
bool PKBCall::isCallsTAnyIdent(PROC_NAME calleeT) {
	for (auto vectorIter : callsTProcTable) {
		if (vectorIter.back() == calleeT) {
			return true;
		}
	}
	return false;
}
bool PKBCall::isCallsTIdentAny(PROC_NAME caller) {
	for (auto vectorIter : callsTProcTable) {
		if (vectorIter.front() == caller) {
			return true;
		}
	}
	return false;
}
bool PKBCall::isCallsTIdentIdent(PROC_NAME caller, PROC_NAME calleeT) {
	for (auto vectorIter : callsTProcTable) {
		if (vectorIter.front() == caller) {
			if (vectorIter.back() == calleeT) {
				return true;
			}
		}
	}
	return false;
}

//NEW EVALUATION API
TABLE PKBCall::getCallsAnyEnt() {
	PROC_LIST resultTable;
	PROC_LIST list;
	PROC_NAME p;
	list = PKBProcedure::getProcedures();
	for (auto iter : list) {
		p = iter.front();
		for (auto vectorIter : callsProcTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.back() == p) {
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBCall::getCallsEntAny() {
	PROC_LIST resultTable;
	PROC_LIST list;
	PROC_NAME p;
	list = PKBProcedure::getProcedures();
	for (auto iter : list) {
		p = iter.front();
		for (auto vectorIter : callsProcTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == p) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBCall::getCallsIdentEnt(PROC_NAME procName) {
	PROC_LIST resultTable;
	PROC_LIST list;
	PROC_NAME p;
	list = PKBProcedure::getProcedures();
	for (auto iter : list) {
		p = iter.front();
		for (auto vectorIter : callsProcTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == procName && vectorIter.back() == p) {
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBCall::getCallsEntIdent(PROC_NAME procName) {
	PROC_LIST resultTable;
	PROC_LIST list;
	PROC_NAME p;
	list = PKBProcedure::getProcedures();
	for (auto iter : list) {
		p = iter.front();
		for (auto vectorIter : callsProcTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == p && vectorIter.back() == procName) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBCall::getCallsEntEnt() {
	return callsProcTable;
}

TABLE PKBCall::getCallsTAnyEnt() {
	PROC_LIST resultTable;
	PROC_LIST list;
	PROC_NAME p;
	list = PKBProcedure::getProcedures();
	for (auto iter : list) {
		p = iter.front();
		for (auto vectorIter : callsTProcTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.back() == p) {
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBCall::getCallsTEntAny() {
	PROC_LIST resultTable;
	PROC_LIST list;
	PROC_NAME p;
	list = PKBProcedure::getProcedures();
	for (auto iter : list) {
		p = iter.front();
		for (auto vectorIter : callsTProcTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == p) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBCall::getCallsTIdentEnt(PROC_NAME procName) {
	PROC_LIST resultTable;
	PROC_LIST list;
	PROC_NAME p;
	list = PKBProcedure::getProcedures();
	for (auto iter : list) {
		p = iter.front();
		for (auto vectorIter : callsTProcTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == procName && vectorIter.back() == p) {
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBCall::getCallsTEntIdent(PROC_NAME procName) {
	PROC_LIST resultTable;
	PROC_LIST list;
	PROC_NAME p;
	list = PKBProcedure::getProcedures();
	for (auto iter : list) {
		p = iter.front();
		for (auto vectorIter : callsTProcTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == p && vectorIter.back() == procName) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBCall::getCallsTEntEnt() {
	return callsTProcTable;
}