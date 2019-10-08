#include "PKBUses.h"

using namespace std;
unordered_set<vector<string>, VectorHash> PKBUses::usesStmtTable;
unordered_set<vector<string>, VectorHash> PKBUses::usesProcTable;

bool PKBUses::setUsesStmt(STMT_NO stmtNo, VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(to_string(stmtNo));
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


bool PKBUses::isUsesStmtRelationship(STMT_NO stmtNo, VAR_NAME varName) {
	for (auto vectorIter : usesStmtTable) {
		if (vectorIter.front() == to_string(stmtNo)) {
			if (vectorIter.back() == varName) {
				return true;
			}
		}
	}
	return false;
}
	

//Stmt s1 ; Select Uses(s1,__) 
STMT_LIST PKBUses::getAllUsesStmt() {
	STMT_LIST result = STMT_LIST();

	for (auto iter : usesStmtTable) {
		result.emplace(iter.front());
	}
	return result;
}

//Var v ; select s such that uses(s,v) 
STMT_LIST PKBUses::getUsesStmtByVar(VAR_NAME varName) {
	STMT_LIST stmtList;
	for (auto vectorIter : usesStmtTable) {
		if (vectorIter.back() == varName) {
			stmtList.emplace(stoi(vectorIter.front()));
		}
	}
	return stmtList;
}

// Uses(1, v)
//LHS is fixed as stmt 
VAR_LIST PKBUses::getUsesVarByStmt(STMT_NO stmtNo) {
	VAR_LIST stmtList;
	for (auto vectorIter : usesStmtTable) {
		if (vectorIter.front() == stmtNo) {
			stmtList.emplace(stoi(vectorIter.back()));
		}
	}
	return stmtList;
}


//Procedure p1 ; Select Uses(p1,__) 
PROC_LIST PKBUses::getAllUsesProc() {
	PROC_LIST result = PROC_LIST();

	for (auto iter : usesProcTable) {
		result.emplace(iter.front());
	}
	return result;
}

//Var v Proc p ; 
//select p such that uses(p,v) 
PROC_LIST PKBUses::getUsesProcByVar(VAR_NAME varName) {
	unordered_set<int> stmtList;
	for (auto vectorIter : usesProcTable) {
		if (vectorIter.back() == varName) {
			stmtList.emplace(stoi(vectorIter.front()));
		}
	}
	return stmtList;
}





bool PKBUses::clear() {
	usesStmtTable.clear();
	usesProcTable.clear(); 
	return true;
}