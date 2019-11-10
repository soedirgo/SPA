#include "PKBModifies.h"
#include "PKBStmt.h"
#include "PKBCall.h"

using namespace std;
TABLE PKBModifies::modifiesStmtTable;
TABLE PKBModifies::modifiesProcTable;

//Clears the modifiesStmtTable and modifiesProcTable in the PKB 
void PKBModifies::clear() {
	modifiesStmtTable.clear();
	modifiesProcTable.clear();
}

//Set the modifies relationship between a statement number and a variable name
void PKBModifies::setModifiesS(STMT_NO stmtNo, VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	tuple.push_back(varName);
	modifiesStmtTable.emplace(tuple);
}


//Set the modifies relationship between a procedure name and a variable name
void PKBModifies::setModifiesP(PROC_NAME procName, VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(procName);
	tuple.push_back(varName);
	modifiesProcTable.emplace(tuple);
}

//ModifiesS(1,"x")
bool PKBModifies::isModifiesSIdentIdent(STMT_NO stmtNo, VAR_NAME varName) {

	for (auto vectorIter : modifiesStmtTable) {
		if (vectorIter.front() == stmtNo && vectorIter.back() == varName) {
			return true;
		}
	}
	return false;
}

//ModifiesS(1,_)
bool PKBModifies::isModifiesSIdentAny(STMT_NO stmtNo) {

	for (auto vectorIter : modifiesStmtTable) {
		if (vectorIter.front() == stmtNo) {
				return true;
		}
	}
	return false;
}
//ModifiesP("First",_)
bool PKBModifies::isModifiesPIdentAny(PROC_NAME procName) {
	for (auto vectorIter : modifiesProcTable) {
		if (vectorIter.front() == procName) {
			return true;
		}
	}
	return false;
}
//ModifiesP("First","x")
bool PKBModifies::isModifiesPIdentIdent(PROC_NAME procName, VAR_NAME varName) {

	for (auto vectorIter : modifiesProcTable) {
		if (vectorIter.front() == procName) {
			if (vectorIter.back() == varName) {
				return true;
			}
		}
	}
	return false;
}


//LHS is either a stmt syn or print/if/while/assign/call syn
//RHS is _
//Modifies(s1,__) , Modifies(a1, _ ), Modifies(ifs , _ ) 
STMT_LIST PKBModifies::getModifiesSEntAny(STMT_TYPE type) {
	STMT_LIST result;
	if (type == "stmt" || type == "prog_line") {
		for (auto iter : modifiesStmtTable) {
			vector<string> myVector = vector<string>();
			myVector.push_back(iter.front());
			result.emplace(myVector);
		}
	}

	else {
		STMT_LIST stmtList = PKBStmt::getStmtsByType(type);
		for (auto stmt : stmtList) {
			for (auto ModifiesStmt : modifiesStmtTable) {
				if (stmt.front() == ModifiesStmt.front()) {
					result.emplace(stmt);
				}
			}
		}
	}

	return result;
}


//LHS is either a stmt syn or print/if/while/assign/call syn
//RHS is a specific variable name 
// e.g. Modifies(s1, "x" ) , Modifies(a1, "x" ), Modifies(ifs ,"x" ) 
STMT_LIST PKBModifies::getModifiesSEntIdent(STMT_TYPE type, VAR_NAME varName) {
	STMT_LIST result;
	if (type == "stmt" || type == "prog_line") {
		for (auto ModifiesStmt : modifiesStmtTable) {
			if (ModifiesStmt.back() == varName) {
				vector<string> myVector = vector<string>();
				myVector.push_back(ModifiesStmt.front());
				result.emplace(myVector);
			}
		}
	}
	else {
		STMT_LIST stmtList = PKBStmt::getStmtsByType(type);

		for (auto stmt : stmtList) {
			for (auto ModifiesStmt : modifiesStmtTable) {

				if (stmt.front() == ModifiesStmt.front() && ModifiesStmt.back() == varName) {
					result.emplace(stmt);
				}
			}
		}
	}
	return result;

}



// Modifies( 3 , v) 
//LHS fixed, RHS syn
LIST_OF_VAR_NAME PKBModifies::getModifiesSIdentEnt(STMT_NO stmtNo) {
	LIST_OF_VAR_NAME varListResult;
	for (auto vectorIter : modifiesStmtTable) {

		if (vectorIter.front() == stmtNo) {
			vector<string> myVector = vector<string>();
			myVector.push_back(vectorIter.back());
			varListResult.emplace(myVector);
		}
	}
	return varListResult;
}


//Modifies( if , v), Modifies(call , v) , Modifies (s,v) 
//LHS is either a stmt syn or print/if/while/assign/call syn
//RHS is a var syn
TABLE PKBModifies::getModifiesSEntEnt(STMT_TYPE type) {
	TABLE resultTable;
	if (type == "stmt" || type == "prog_line") {
		return modifiesStmtTable;
	}
	else {
		STMT_LIST stmtList = PKBStmt::getStmtsByType(type);
		for (auto stmt : stmtList) {
			for (auto ModifiesStmt : modifiesStmtTable) {
				if (ModifiesStmt.front() == stmt.front()) {
					resultTable.emplace(ModifiesStmt);
				}
			}
		}

	}
	return resultTable;
}

//Procedure p1 ; Select Modifies(p1,__) 
LIST_OF_PROC_NAME PKBModifies::getModifiesPEntAny() {
	LIST_OF_PROC_NAME result;

	for (auto iter : modifiesProcTable) {
		vector<string> myVector = vector<string>();
		myVector.push_back(iter.front());
		result.emplace(myVector);
	}
	return result;
}

//select p such that Modifies(p,"x") 
//LHS proc synnonym, RHS fixed var 
LIST_OF_PROC_NAME PKBModifies::getModifiesPEntIdent(VAR_NAME varName) {
	LIST_OF_PROC_NAME procListResult;
	for (auto vectorIter : modifiesProcTable) {
		if (vectorIter.back() == varName) {
			vector<string> myVector = vector<string>();
			myVector.push_back(vectorIter.front());
			procListResult.emplace(myVector);
		}
	}
	return procListResult;
}


//Modifies("procName", v)  
//LHS proc name string, RHS var syn 
LIST_OF_PROC_NAME PKBModifies::getModifiesPIdentEnt(PROC_NAME procName) {
	LIST_OF_VAR_NAME varListResult;
	for (auto vectorIter : modifiesProcTable) {
		if (vectorIter.front() == procName) {
			vector<string> myVector = vector<string>();
			myVector.push_back(vectorIter.back());
			varListResult.emplace(myVector);
		}
	}
	return varListResult;
}



//Modifies(p , v) 
//LHS proc syn, RHS var syn
TABLE PKBModifies::getModifiesPEntEnt() {
	TABLE pairResults;
	return modifiesProcTable;
}
