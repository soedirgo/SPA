#include "PKBUses.h"
#include "PKBStmt.h"
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


//Stmt s1 ; Select Uses(s1,__) 
//LHS stmt syn, RHS 
STMT_LIST PKBUses::getAllUsesStmt() {
	STMT_LIST stmtListResult;
	for (auto iter : usesStmtTable) {
		vector<string> myVector = vector<string>();
		myVector.push_back(iter.front());
		stmtListResult.emplace(myVector);
	}
	return stmtListResult;
}


//Stmt s1, Assign a1 ; e.g. Select s1 such that Uses(s1, "x") pattern a1("x",_)
//s1 is either a print/if/while/assign/call stmt and NOT a procedure
STMT_LIST PKBUses::getAllUsesStmtByType(STMT_TYPE type ) {
	STMT_LIST stmtList = PKBStmt::getAllStmtByType(type);
	STMT_LIST result;
	for (auto iter : stmtList) {
		for (auto iter2 : usesStmtTable) {
			vector<string> tuple = vector<string>();
			tuple.push_back(iter2.front());
			if (iter == tuple) {
				result.emplace(iter2);
			}
		}
	}
	return result;
}

	
//Select s such that uses(s, "x")
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


// Select v such that Uses( 3 , v) 
//LHS fixed, RHS syn
VAR_LIST PKBUses::getUsesVarByStmt(STMT_NO stmtNo) {
	VAR_LIST varListResult;
	for (auto vectorIter : usesStmtTable) {
		
		if (vectorIter.front() == stmtNo) {
			vector<string> myVector = vector<string>(); 
			myVector.push_back(vectorIter.front()); 
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
			myVector.push_back(vectorIter.back() );
			varListResult.emplace(myVector);
		}
	}
	return varListResult;
}

