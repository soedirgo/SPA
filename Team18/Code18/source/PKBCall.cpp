#include "PKBCall.h"
#include "PKBProcedure.h"

using namespace std;
TABLE PKBCall::callsProcTable;
TABLE PKBCall::callsTProcTable;
TABLE PKBCall::callStmtTable;


//Set Call Relationship between two procedures
void PKBCall::setCallProc(PROC_NAME caller, PROC_NAME callee) {
	vector<string> tuple = vector<string>();
	tuple.push_back(caller);
	tuple.push_back(callee);
	callsProcTable.emplace(tuple);
}

//Set Call stmt and its procedures
void PKBCall::setCallStmt(STMT_NO stmtNo, PROC_NAME callee) {
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	tuple.push_back(callee);
	callStmtTable.emplace(tuple);
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

//Set Call* Relationship between 2 procedures
void PKBCall::setCallTProc(PROC_NAME caller, PROC_NAME callee) {
	vector<string> tuple = vector<string>();
	tuple.push_back(caller);
	tuple.push_back(callee);
	callsTProcTable.emplace(tuple);
}


TABLE PKBCall::getCallStmtTable() {
	return callStmtTable;
}

//Clear all PKB Calls, Calls* and Call stmtNo tables
void PKBCall::clear() {
	callsProcTable.clear();
	callsTProcTable.clear();
	callStmtTable.clear();
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
LIST_OF_PROC_NAME PKBCall::getCallsAnyEnt() {
	LIST_OF_PROC_NAME resultTable;
	for (auto vectorIter : callsProcTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.back());
		resultTable.emplace(tuple);
	}
	return resultTable;
}
//Get proc_list for Calls (procedure,_)
LIST_OF_PROC_NAME PKBCall::getCallsEntAny() {
	LIST_OF_PROC_NAME resultTable;
	for (auto vectorIter : callsProcTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.front());
		resultTable.emplace(tuple);
	}
	return resultTable;
}
//Get Result Table for Calls ("First",procedure)
LIST_OF_PROC_NAME PKBCall::getCallsIdentEnt(PROC_NAME procName) {
	LIST_OF_PROC_NAME resultTable;
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
LIST_OF_PROC_NAME PKBCall::getCallsEntIdent(PROC_NAME procName) {
	LIST_OF_PROC_NAME resultTable;
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
LIST_OF_PROC_NAME PKBCall::getCallsTAnyEnt() {
	LIST_OF_PROC_NAME resultTable;
	for (auto vectorIter : callsTProcTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.back());
		resultTable.emplace(tuple);
	}
	return resultTable;
}
//Get proc_list for Calls*(procedure1,_)
LIST_OF_PROC_NAME PKBCall::getCallsTEntAny() {
	LIST_OF_PROC_NAME resultTable;
	for (auto vectorIter : callsTProcTable) {
		vector<string> tuple = vector<string>();
		tuple.push_back(vectorIter.front());
		resultTable.emplace(tuple);
	}
	return resultTable;
}
//Get proc_list for Calls*("First",procedure2)
LIST_OF_PROC_NAME PKBCall::getCallsTIdentEnt(PROC_NAME procName) {
	LIST_OF_PROC_NAME resultTable;
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
LIST_OF_PROC_NAME PKBCall::getCallsTEntIdent(PROC_NAME procName) {
	LIST_OF_PROC_NAME resultTable;
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