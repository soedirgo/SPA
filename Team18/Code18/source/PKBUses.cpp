#include "PKBUses.h"
#include "PKBStmt.h"
#include "PKBCall.h"
using namespace std;

TABLE PKBUses::usesStmtTable;
TABLE PKBUses::usesProcTable;

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
//Uses(1 , _) -> True/False
//LHS fixed stmt, RHS fixed var or _ 
bool PKBUses::isUsesStmt(STMT_NO stmtNo, VAR_NAME varName) {
	for (auto vectorIter : usesStmtTable) {
		if ( (varName == "_")  && (vectorIter.front() == stmtNo) ) {
			return true;
		}

		else if ( (vectorIter.front() == stmtNo) && (vectorIter.back() == varName)  ) {
			return true;
		}
	}
	return false;
}


//Uses(procName1, "x") -> True/False
//Uses(procName1, _) -> True/False
//LHS fixed proc, RHS fixed var or _ 
bool PKBUses::isUsesProc(PROC_NAME procName, VAR_NAME varName) {
	for (auto vectorIter : usesProcTable) {
		if (varName == "_"  && vectorIter.front() == procName ) {
			return true; 
		}
		else if (vectorIter.front() == procName && vectorIter.back() == varName) {
			return true;
		}
	}
	return false;
}




//LHS is either a stmt syn or print/if/while/assign/call syn
//RHS is _
//Uses(s1,__) , Uses(a1, _ ), Uses(ifs , _ ) 
STMT_LIST PKBUses::getAllUsesStmtByType(STMT_TYPE type) {
	STMT_LIST result; 
	if (type == "stmt") { 
		for (auto iter : usesStmtTable) {
			vector<string> myVector = vector<string>();
			myVector.push_back(iter.front());
			result.emplace(myVector);
		}
	}
	
	else { 
		STMT_LIST stmtList = PKBStmt::getAllStmtByType(type);
		for (auto stmt : stmtList) {
			for (auto usesStmt: usesStmtTable) {
				if (stmt.front() == usesStmt.front()) {
					result.emplace(stmt);
				}
			}
		}
	}
	
	return result;
}


//LHS is either a stmt syn or print/if/while/assign/call syn
//RHS is a specific variable name 
// e.g. Uses(s1, "x" ) , Uses(a1, "x" ), Uses(ifs ,"x" ) 
STMT_LIST PKBUses::getUsesStmtByTypeAndVar(STMT_TYPE type, VAR_NAME varName) {
	STMT_LIST result;
	if (type == "stmt") {
		for (auto usesStmt : usesStmtTable) {
			if (usesStmt.back() == varName) {
				vector<string> myVector = vector<string>();
				myVector.push_back(usesStmt.front());
				result.emplace(myVector);
			}
		}
	}
	else {
		STMT_LIST stmtList = PKBStmt::getAllStmtByType(type);

		for (auto stmt : stmtList) {
			for (auto usesStmt : usesStmtTable) {
				
				if (stmt.front() == usesStmt.front() && usesStmt.back() == varName) {
					result.emplace(stmt);
				}
			}
		}
	}
	return result; 
	
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


//Uses( if , v), Uses(call , v) , Uses (s,v) 
//LHS is either a stmt syn or print/if/while/assign/call syn
//RHS is a var syn
DOUBLE_COL_TABLE PKBUses::getAllUsesStmtPair(STMT_TYPE type) {
	DOUBLE_COL_TABLE resultTable;
	if (type == "stmt") {
		return usesStmtTable; 
	}
	else{
		STMT_LIST stmtList = PKBStmt::getAllStmtByType(type);
		for (auto stmt : stmtList) {
			for (auto usesStmt : usesStmtTable) {
				if (usesStmt.front() == stmt.front()) {
					resultTable.emplace(usesStmt);
				}
			}
		}
		
	}
	return resultTable;
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


//uses("procName", v)  
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



//Uses(p , v) 
//LHS proc syn, RHS var syn
DOUBLE_COL_TABLE PKBUses::getAllUsesProcPair() {
	DOUBLE_COL_TABLE pairResults;
	return usesProcTable; 
}
