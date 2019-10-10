#include "PKBUses.h"
#include "PKBStmt.h"
#include "PKBCall.h"
using namespace std;

unordered_set<vector<string>, VectorDoubleStringHash> PKBUses::usesStmtTable;
unordered_set<vector<string>, VectorDoubleStringHash> PKBUses::usesProcTable;

bool PKBUses::setUsesStmt(STMT_NO stmtNo, VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	tuple.push_back(varName);
	usesStmtTable.emplace(tuple);
	return true;
}

bool PKBUses::setUsesProc(PROC_NAME procName, VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(procName);
	tuple.push_back(varName);
	usesProcTable.emplace(tuple);
	return true;
}

bool PKBUses::clear() {
	usesStmtTable.clear();
	usesProcTable.clear();
	return true;
}


//Uses(1, "x")  -> True/False
//LHS fixed stmt, RHS fixed var 
bool PKBUses::isUsesStmtRelationship(STMT_NO stmtNo, VAR_NAME varName) {
	for (auto vectorIter : usesStmtTable) {
		if (vectorIter.front() == stmtNo) {
			if (vectorIter.back() == varName) {
				return true;
			}
		}
	}
	return false;
}


//Uses(procName1, "x") -> True/False
//LHS fixed proc, RHS fixed var 
bool PKBUses::isUsesProcRelationship(PROC_NAME procName, VAR_NAME varName) {
	for (auto vectorIter : usesProcTable) {
		if (vectorIter.front() == procName) {
			if (vectorIter.back() == varName) {
				return true;
			}
		}
	}
	return false;
}


//Uses(s1,__) 
//LHS stmt synnoym, RHS 
STMT_LIST PKBUses::getAllUsesStmt() {
	STMT_LIST stmtListResult;
	for (auto iter : usesStmtTable) {
		vector<string> myVector = vector<string>();
		myVector.push_back(iter.front());
		stmtListResult.emplace(myVector);
	}
	return stmtListResult;
}

//LHS is either a print/if/while/assign/call stmt and NOT a procedure
// e.g. Uses(a1, _ ), Uses(ifs , _ ) 
STMT_LIST PKBUses::getAllUsesStmtByType(STMT_TYPE type) {
	STMT_LIST stmtList = PKBStmt::getAllStmtByType(type);
	return stmtList;
}


//LHS is either a print/if/while/assign/call stmt and NOT a procedure
//RHS is a specific variable name 
// e.g. Uses(a1, "x" ), Uses(ifs ,"x" ) 

STMT_LIST PKBUses::getUsesStmtByTypeAndVar(STMT_TYPE type, VAR_NAME varName) {
	STMT_LIST stmtList = PKBStmt::getAllStmtByType(type);
	STMT_LIST result;
	if (type == "CALL") {
		for (auto callStmtNo : stmtList) {
			vector<string> call1;
			PROC_NAME procName = PKBCall::getCalledProcByStmt(callStmtNo.front());
			call1.push_back(procName);

			for (auto tuple : usesProcTable) { //check the proc table instead of usesStmtTable
				vector<string> call2ProcName;
				call2ProcName.push_back(tuple.front()); 
				VAR_NAME call2VarName = tuple.back();
				if (call2ProcName == call1 && call2VarName == varName) {
					result.emplace(callStmtNo);
				}
			}
		}
		return result;
	}
	//Else Type = is either a print/if/while/assign
	for (auto usesStmt1 : stmtList) {
		for (auto tuple : usesStmtTable) {

			vector<string> usesStmt2 = vector<string>();
			VAR_NAME usedVarName = tuple.back();
			usesStmt2.push_back(tuple.front());
			if (usesStmt2 == usesStmt1 && usedVarName == varName) {
				result.emplace(usesStmt1);
			}
		}
	}
	return result;
}



//uses(s, "x")
//LHS stmt syn, RHS fixed var 
STMT_LIST PKBUses::getUsesStmtByVar(VAR_NAME varName) {
	STMT_LIST stmtListResult;

	for (auto vectorIter : usesStmtTable) {
		if (vectorIter.back() == varName) {
			vector<string> myVector = vector<string>();
			myVector.push_back(vectorIter.front());
			stmtListResult.emplace(myVector);
		}
	}
	return stmtListResult;
}


// S Uses( 3 , v) 
//LHS fixed, RHS syn
VAR_LIST PKBUses::getUsesVarByStmt(STMT_NO stmtNo) {
	VAR_LIST varListResult;
	for (auto vectorIter : usesStmtTable) {

		if (vectorIter.front() == stmtNo) {
			vector<string> myVector = vector<string>();
			myVector.push_back(vectorIter.back());
			varListResult.emplace(myVector);
		}
	}
	return varListResult;
}


//Procedure p1 ; Select Uses(p1,__) 
PROC_LIST PKBUses::getAllUsesProc() {
	PROC_LIST result;

	for (auto iter : usesProcTable) {
		vector<string> myVector = vector<string>();
		myVector.push_back(iter.front());
		result.emplace(myVector);
	}
	return result;
}

//select p such that uses(p,"x") 
//LHS proc synnonym, RHS fixed var 
PROC_LIST PKBUses::getUsesProcByVar(VAR_NAME varName) {
	PROC_LIST procListResult;
	for (auto vectorIter : usesProcTable) {
		if (vectorIter.back() == varName) {
			vector<string> myVector = vector<string>();
			myVector.push_back(vectorIter.front());
			procListResult.emplace(myVector);
		}
	}
	return procListResult;
}


//select v such that uses("procName", v)  
//LHS proc name string, RHS var syn 
PROC_LIST PKBUses::getUsesVarByProc(PROC_NAME procName) {
	VAR_LIST varListResult;
	for (auto vectorIter : usesProcTable) {
		if (vectorIter.front() == procName) {
			vector<string> myVector = vector<string>();
			myVector.push_back(vectorIter.back());
			varListResult.emplace(myVector);
		}
	}
	return varListResult;
}

