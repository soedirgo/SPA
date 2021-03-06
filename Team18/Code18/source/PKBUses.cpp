#include "PKBUses.h"
#include "PKBStmt.h"
#include "PKBCall.h"
using namespace std;

TABLE PKBUses::usesStmtTable;
TABLE PKBUses::usesProcTable;

//Set UsesS relationship between a stmtNo and a variable name
void PKBUses::setUsesS(STMT_NO stmtNo, VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	tuple.push_back(varName);
	usesStmtTable.emplace(tuple);
}
//Set UsesP relationship between a procedeure name and a variable name
void PKBUses::setUsesP(PROC_NAME procName, VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(procName);
	tuple.push_back(varName);
	usesProcTable.emplace(tuple);
}

//Clear the UsesStmtTable and usesProcTable in the PKB
void PKBUses::clear() {
	usesStmtTable.clear();
	usesProcTable.clear();
}

//Uses(1 , _) -> True/False
//LHS fixed stmt, RHS _
bool PKBUses::isUsesSIdentAny(STMT_NO stmtNo) {
	for (auto vectorIter : usesStmtTable) {
		if (vectorIter.front() == stmtNo) {
			return true;
		}
	}
	return false;
}



//Uses(1, "x")  -> True/False
//LHS fixed stmt, RHS fixed  
bool PKBUses::isUsesSIdentIdent(STMT_NO stmtNo, VAR_NAME varName) {
	for (auto vectorIter : usesStmtTable) {
		if ( (vectorIter.front() == stmtNo) && (vectorIter.back() == varName)  ) {
			return true;
		}
	}
	return false;
}


//Uses(procName1, _) -> True/False
//LHS fixed proc, RHS _ 
bool PKBUses::isUsesPIdentAny(PROC_NAME procName) {
	for (auto vectorIter : usesProcTable) {
		if ( vectorIter.front() == procName) {
			return true;
		}
	}
	return false;
}

//Uses(procName1, "x") -> True/False
//LHS fixed proc, RHS fixed var 
bool PKBUses::isUsesPIdentIdent(PROC_NAME procName, VAR_NAME varName) {
	for (auto vectorIter : usesProcTable) {
		if (vectorIter.front() == procName && vectorIter.back() == varName) {
			return true;
		}
	}
	return false;
}


//LHS is either a stmt syn or print/if/while/assign/call syn
//RHS is _
//Uses(s1,__) , Uses(a1, _ ), Uses(ifs , _ ) 
STMT_LIST PKBUses::getUsesSEntAny(STMT_TYPE type) {
	STMT_LIST result; 
	if (type == "stmt" || type == "prog_line") {
		for (auto iter : usesStmtTable) {
			vector<string> myVector = vector<string>();
			myVector.push_back(iter.front());
			result.emplace(myVector);
		}
	}
	
	else { 
		STMT_LIST stmtList = PKBStmt::getStmtsByType(type);
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
STMT_LIST PKBUses::getUsesSEntIdent(STMT_TYPE type, VAR_NAME varName) {
	STMT_LIST result;
	if (type == "stmt" || type == "prog_line") {
		for (auto usesStmt : usesStmtTable) {
			if (usesStmt.back() == varName) {
				vector<string> myVector = vector<string>();
				myVector.push_back(usesStmt.front());
				result.emplace(myVector);
			}
		}
	}
	else {
		STMT_LIST stmtList = PKBStmt::getStmtsByType(type);

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
LIST_OF_VAR_NAME PKBUses::getUsesSIdentEnt(STMT_NO stmtNo) {
	LIST_OF_VAR_NAME varListResult;
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
TABLE PKBUses::getUsesSEntEnt(STMT_TYPE type) {
	TABLE resultTable;
	if (type == "stmt" || type == "prog_line") {
		return usesStmtTable; 
	}
	else{
		STMT_LIST stmtList = PKBStmt::getStmtsByType(type);
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
LIST_OF_PROC_NAME PKBUses::getUsesPEntAny() {
	LIST_OF_PROC_NAME result;

	for (auto iter : usesProcTable) {
		vector<string> myVector = vector<string>();
		myVector.push_back(iter.front());
		result.emplace(myVector);
	}
	return result;
}

//select p such that uses(p,"x") 
//LHS proc synnonym, RHS fixed var 
LIST_OF_PROC_NAME PKBUses::getUsesPEntIdent(VAR_NAME varName) {
	LIST_OF_PROC_NAME procListResult;
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
LIST_OF_PROC_NAME PKBUses::getUsesPIdentEnt(PROC_NAME procName) {
	LIST_OF_VAR_NAME varListResult;
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
TABLE PKBUses::getUsesPEntEnt() {
	TABLE pairResults;
	return usesProcTable; 
}
