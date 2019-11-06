#include "PKBCall.h"
#include "PKBProcedure.h"

using namespace std;
TABLE PKBCall::callsProcTable;
TABLE PKBCall::callsTProcTable;
TABLE PKBCall::callStmtTable;


//Set Call Relationship between two procedures
bool PKBCall::setCallProc(PROC_NAME caller, PROC_NAME callee) {
	vector<string> tuple = vector<string>();
	tuple.push_back(caller);
	tuple.push_back(callee);
	callsProcTable.emplace(tuple);
	return true;
}

//Set Call stmt and its procedures
bool PKBCall::setCallStmt(STMT_NO stmtNo, PROC_NAME callee) {
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	tuple.push_back(callee);
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
	for (auto vectorIter : callsProcTable) {
		vector<string> tuple = vector<string>();
		if (vectorIter.back() == callee) {
			tuple.push_back(vectorIter.front());
			list.emplace(tuple);
		}
	}
	return list;
}

PROC_LIST PKBCall::getCalleeProc(PROC_NAME caller) {
	PROC_LIST list;
	for (auto vectorIter : callsProcTable) {
		vector<string> tuple = vector<string>();
		if (vectorIter.front() == caller) {
			tuple.push_back(vectorIter.back());
			list.emplace(tuple);
		}
	}
	return list;
}

PROC_LIST PKBCall::getAllCallProc() {
	PROC_LIST list;
	for (auto vectorIter : callsProcTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.front());
		list.emplace(tuple);
	}
	return list;
}

//Set Call* Relationship between 2 procedures
bool PKBCall::setCallTProc(PROC_NAME caller, PROC_NAME callee) {
	vector<string> tuple = vector<string>();
	tuple.push_back(caller);
	tuple.push_back(callee);
	callsTProcTable.emplace(tuple);
	return true;
}


TABLE PKBCall::getCallStmtTable() {
	return callStmtTable;
}

//Clear all PKB Calls, Calls* and Call stmtNo tables
bool PKBCall::clear() {
	callsProcTable.clear();
	callsTProcTable.clear();
	callStmtTable.clear();
	return true;
}

//Get boolean for Calls (_,_)
bool PKBCall::isCallsAnyAny() {
	return !callsProcTable.empty();
}
//Get boolean for Calls (_,"Second")
bool PKBCall::isCallsAnyIdent(PROC_NAME callee) {
	for (auto vectorIter : callsProcTable) {
		if (vectorIter.back() == callee) {
			return true;
		}
	}
	return false;
}
//Get boolean for Calls ("First",_)
bool PKBCall::isCallsIdentAny(PROC_NAME caller) {
	for (auto vectorIter : callsProcTable) {
		if (vectorIter.front() == caller) {
			return true;
		}
	}
	return false;
}
//Get boolean for Calls ("First", "Second")
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
//Get boolean for Calls* (_,_)
bool PKBCall::isCallsTAnyAny() {
	return !callsTProcTable.empty();
}
//Get boolean for Calls* (_,"Second")
bool PKBCall::isCallsTAnyIdent(PROC_NAME calleeT) {
	for (auto vectorIter : callsTProcTable) {
		if (vectorIter.back() == calleeT) {
			return true;
		}
	}
	return false;
}
//Get boolean for Calls* ("First",_)
bool PKBCall::isCallsTIdentAny(PROC_NAME caller) {
	for (auto vectorIter : callsTProcTable) {
		if (vectorIter.front() == caller) {
			return true;
		}
	}
	return false;
}
//Get boolean for Calls* ("First","Second")
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
//Get proc_list for Calls (_,procedure)
PROC_LIST PKBCall::getCallsAnyEnt() {
	PROC_LIST resultTable;
	for (auto vectorIter : callsProcTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.back());
		resultTable.emplace(tuple);
	}
	return resultTable;
}
//Get proc_list for Calls (procedure,_)
PROC_LIST PKBCall::getCallsEntAny() {
	PROC_LIST resultTable;
	for (auto vectorIter : callsProcTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.front());
		resultTable.emplace(tuple);
	}
	return resultTable;
}
//Get Result Table for Calls ("First",procedure)
PROC_LIST PKBCall::getCallsIdentEnt(PROC_NAME procName) {
	PROC_LIST resultTable;
	for (auto vectorIter : callsProcTable) {
		if (vectorIter.front() == procName) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter.back());
			resultTable.emplace(tuple);
		}
	}
	return resultTable;
}
//Get proc_list for Calls (procedure,"Second")
PROC_LIST PKBCall::getCallsEntIdent(PROC_NAME procName) {
	PROC_LIST resultTable;
	for (auto vectorIter : callsProcTable) {
		if (vectorIter.back() == procName) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter.front());
			resultTable.emplace(tuple);
		}
	}
	return resultTable;
}
//Get Result Table for Calls (procedure1,procedure2)
TABLE PKBCall::getCallsEntEnt() {
	return callsProcTable;
}
//Get proc_list for Calls*(_,procedure2)
PROC_LIST PKBCall::getCallsTAnyEnt() {
	PROC_LIST resultTable;
	for (auto vectorIter : callsTProcTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.back());
		resultTable.emplace(tuple);
	}
	return resultTable;
}
//Get proc_list for Calls*(procedure1,_)
PROC_LIST PKBCall::getCallsTEntAny() {
	PROC_LIST resultTable;
	for (auto vectorIter : callsTProcTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.front());
		resultTable.emplace(tuple);
	}
	return resultTable;
}
//Get proc_list for Calls*("First",procedure2)
PROC_LIST PKBCall::getCallsTIdentEnt(PROC_NAME procName) {
	PROC_LIST resultTable;
	for (auto vectorIter : callsTProcTable) {
		if (vectorIter.front() == procName) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter.back());
			resultTable.emplace(tuple);
		}
	}
	return resultTable;
}
//Get proc_list for Calls*(procedure1,"Second")
PROC_LIST PKBCall::getCallsTEntIdent(PROC_NAME procName) {
	PROC_LIST resultTable;
	for (auto vectorIter : callsTProcTable) {
		if (vectorIter.back() == procName) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter.front());
			resultTable.emplace(tuple);
		}
	}
	return resultTable;
}
//Get Result Table for Calls*(procedure1,procedure2)
TABLE PKBCall::getCallsTEntEnt() {
	return callsTProcTable;
}