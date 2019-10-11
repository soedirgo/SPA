#include <iostream>
#include <string>
#include <vector>
#include "PKB.h"
#include "TNode.h"
#include "PKBParent.h"
#include "PKBFollows.h"
#include "PKBUses.h"
#include "PKBModifies.h"
#include "PKBStmt.h"
#include "PKBProcedure.h"
#include "PKBVariable.h"
#include "PKBCall.h"
#include "PKBNext.h"
#include "PKBPrint.h"
#include "PKBRead.h"
#include "PKBConstant.h"
#include "PKBWhile.h"
#include "PKBIf.h"
using namespace std;

unordered_map<int, string> PKB::assignStmtTable;
unordered_map<string, unordered_set<int>> PKB::assignVarTable;


bool PKB::clear()
{
	
	PKBCall::clear();
	PKBConstant::clear();
	PKBFollows::clear();
	PKBIf::clear();
	PKBModifies::clear();
	PKBNext::clear();
	PKBParent::clear();
	PKBPrint::clear();
	PKBProcedure::clear();
	PKBRead::clear();
	PKBStmt::clear();
	PKBUses::clear();
	PKBVariable::clear();
	PKBWhile::clear();

	return true;
}

int PKB::setProcToAST(PROC p, TNode* r) {
	return 0;
}

TNode* PKB::getRootAST (PROC p){
	return nullptr;
}

////////////////////////////////////
// Higher order wrapper functions APIs
////////////////////////////////////


//Follows 
bool PKB::setFollows(STMT_NO followedBy, STMT_NO follow) {
	return PKBFollows::setFollows(followedBy, follow);
}

bool PKB::setFollowsT(STMT_NO followedBy, STMT_NO follow) {
	return PKBFollows::setFollowsStar(followedBy, follow);
}

bool PKB::isFollowsRelationship(STMT_NO followedBy, STMT_NO follow) {
	return PKBFollows::isFollowsRelationship(followedBy, follow);
}

bool PKB::isFollowsStarRelationship(STMT_NO followedBy, STMT_NO follow) {
	return PKBFollows::isFollowsStarRelationship(followedBy, follow);
}

//Parents
bool PKB::setParent(STMT_NO parent, STMT_NO child) {
	return PKBParent::setParent(parent, child);
}

bool PKB::setParentT(STMT_NO parent, STMT_NO child) {
	return PKBParent::setParentStar(parent, child);
}

bool PKB::isParentRelationship(STMT_NO parent, STMT_NO child) {
	return PKBParent::isParentRelationship(parent, child);
}

bool PKB::isParentStarRelationship(STMT_NO parent, STMT_NO child) {
	return PKBParent::isParentStarRelationship(parent, child);
}

bool PKB::isParentExist(STMT_NO child) {
	return PKBParent::isParentExist(child);
}

STMT_NO PKB::getParentStmt(STMT_NO child) {
	return PKBParent::getParent(child);
}


//Modifies
bool PKB::setModifiesStmt(STMT_NO stmtNo, VAR_NAME varName) {
	return PKBModifies::setModifiesStmt(stmtNo, varName);
};

bool PKB::setModifiesProc(PROC_NAME procName, VAR_NAME varName) {
	return PKBModifies::setModifiesProc(procName, varName);
};

bool PKB::isModifiesStmtRelationship(STMT_NO stmtNo, VAR_NAME varName) {
	return PKBModifies::isModifiesStmtRelationship(stmtNo, varName);
}

bool PKB::isModifiesProcRelationship(PROC_NAME procName, VAR_NAME varName) {
	return PKBModifies::isModifiesProcRelationship(procName, varName);
}


//Uses
bool PKB::setUsesStmt(STMT_NO stmtNo, VAR_NAME varName) {
	return PKBUses::setUsesStmt(stmtNo, varName);

};

bool PKB::setUsesProc(PROC_NAME procName, VAR_NAME varName) {
	return PKBUses::setUsesProc(procName, varName);
};

bool PKB::isUsesStmtRelationship(STMT_NO stmtNo, VAR_NAME varName) {
	return PKBUses::isUsesStmtRelationship(stmtNo, varName);
}

bool PKB::isUsesProcRelationship(PROC_NAME procName, VAR_NAME varName) {
	return PKBUses::isUsesProcRelationship(procName, varName);
}

/*
bool PKB::isConstUsedInAssign(STMT_NO assignStmtNo, string c) {
	//STMT_LIST stmtList = getStmtByConst(c); 
	STMT_LIST stmtList = PKBConstant::getAllConstantStmtByVal(c);
	for (auto stmt : stmtList) {
		if (stmt == assignStmtNo) {
			return true;
		}
	}
	return false; 
}
*/

/*
bool PKB::isVarUsedInAssign(STMT_NO assignStmtNo, string varName) {
	STMT_LIST stmtList = PKBUses::getUsesStmt(varName);
	STMT_LIST assignStmtList = getAllAssignStmt();
	for (auto stmt : stmtList) {
		if (stmt == assignStmtNo) {
			for (auto assignStmt : assignStmtList) {
				if (stmt == assignStmt) {
					return true;
				}
			}
			
		}
	}
	return false;
}
*/




/*
bool PKB::insertAssignRelation(int stmtNo, string varModified, unordered_set<string> varUsed, unordered_set<string> constUsed) {
	try {
		setAssignStmt(stmtNo, varModified);
		setAssignStmtByVar(stmtNo, varModified);
		PKBModifies::setModifiesStmt(stmtNo, varModified);
		if (!varUsed.empty()) {
			for (string var : varUsed) {
				setUsesStmt(stmtNo, var);
				setUsesVarByStmt(stmtNo, var);
			}
		}
		if (!constUsed.empty()) {
			for (string c : constUsed) {
				setConstant(c, stmtNo);
			}
		}
		
		return true; 
	}
	catch (errc) {
		return false;
	}
};
*/

//Variable

bool PKB::setVar(VAR_NAME varName) {
	return PKBVariable::setVar(varName);
}

VAR_LIST PKB::getAllVar() {
	return PKBVariable::getAllVar();
}

// constantTable APIs

bool PKB::setConstant(STMT_NO stmtNo, CONST_VAL constantVal) {
	return PKBConstant::setConstant(stmtNo, constantVal);
}

/*
CONST_VAL PKB::getConstantValByStmt(STMT_NO stmtNo) {
	return PKBConstant::getConstantValByStmt(stmtNo);
}
*/

CONST_LIST PKB::getAllConstant() {
	return PKBConstant::getAllConstantVal();
}

// stmtTable APIs

bool PKB::setStmt(STMT_NO stmtNo, STMT_TYPE type) {
	return PKBStmt::setStmt(stmtNo, type);
}

STMT_LIST PKB::getStmts() {
	return PKBStmt::getAllStmt();
}

// assignStmtTable APIs

STMT_LIST PKB::getAssigns() {
	return PKBStmt::getAllStmtByType("ASSIGN");
}

/*
bool PKB::setAssignStmt(STMT_NO stmtNo, string varModified) {
	std::pair<int, string> entry(stmtNo, varModified);
	try {
		assignStmtTable.insert(entry);
		
		return true;
	}
	catch (errc) {
		return false;
	}
};

string PKB::getVarModifiedByAssignStmt(STMT_NO stmtNo) {
	return assignStmtTable[stmtNo]; 
}
*/

////////////////////////////////////
// assignStmtByVarTable APIs
////////////////////////////////////

/*
STMT_LIST PKB::getAssignStmtByVar(string varName) {
	return assignVarTable[varName];
}


bool PKB::setAssignStmtByVar(STMT_NO stmtNo, string varName) {
	try {
		//get stmtList from PKB then add variable to varList
		unordered_set<int> stmtList = getAssignStmtByVar(varName);
		stmtList.emplace(stmtNo);
		//add it to varModifiesStmtTable
		assignVarTable[varName] = stmtList;
		return true;
	}
	catch (errc) {
		return false;
	}
}
*/


////////////////////////////////////
// whileTable APIs
////////////////////////////////////

STMT_LIST PKB::getWhiles() {
	return PKBStmt::getAllStmtByType("WHILE");
};


////////////////////////////////////
// ifTable APIs
////////////////////////////////////

STMT_LIST PKB::getIfs() {
	return PKBStmt::getAllStmtByType("IF");
};

////////////////////////////////////
// printTable APIs
////////////////////////////////////

STMT_LIST PKB::getPrints() {
	return PKBStmt::getAllStmtByType("PRINT");
};

bool PKB::setPrint(STMT_NO stmtNo, VAR_NAME varName) {
	return PKBPrint::setPrint(stmtNo, varName);
};

////////////////////////////////////
// ReadTable APIs
////////////////////////////////////

STMT_LIST PKB::getReads() {
	return PKBStmt::getAllStmtByType("READ");
};

bool PKB::setRead(STMT_NO stmtNo, VAR_NAME varName) {
	return PKBRead::setRead(stmtNo, varName);
};


////////////////////////////////////
// ProecedureTable APIs
////////////////////////////////////

PROC_LIST PKB::getAllProc() {
	return PKBProcedure::getAllProc();
};


bool PKB::setProc(PROC_NAME procName) {
	return PKBProcedure::setProc(procName);
};


////////////////////////////////////
// CallTable APIs
////////////////////////////////////

STMT_LIST PKB::getCalls() {
	return PKBStmt::getAllStmtByType("CALL");
};

bool PKB::setCallProc(PROC_NAME caller, PROC_NAME callee) {
	return PKBCall::setCallProc(caller, callee);
}

bool PKB::setCallStmt(STMT_NO stmtNo, PROC_NAME procName) {
	return PKBCall::setCallStmt(stmtNo, procName);
};

bool PKB::setCallT(PROC_NAME caller, PROC_NAME callee) {
	return PKBCall::setCallTProc(caller, callee);
};

bool PKB::isCallRelationship(PROC_NAME caller, PROC_NAME callee) {
	return PKBCall::isCallRelationship(caller, callee);
}

bool PKB::isCallStarRelationship(PROC_NAME caller, PROC_NAME callee) {
	return PKBCall::isCallStarRelationship(caller, callee);
}

////////////////////////////////////
// NextTable APIs
////////////////////////////////////
bool PKB::setNext(PROG_LINE n1, PROG_LINE n2) {
	return PKBNext::setNext(n1, n2);
};

bool PKB::isNextRelationship(PROG_LINE n1, PROG_LINE n2) {
	return PKBNext::isNextRelationship(n1, n2);
}

bool PKB::isNextStarRelationship(PROG_LINE n1, PROG_LINE n2) {
	return PKBNext::isNextStarRelationship(n1, n2);
}


// New While Uses
bool PKB::setWhileCondition(STMT_NO stmtNo, VAR_NAME varName) {
	return PKBWhile::setWhileUses(stmtNo, varName);
}

// New If Uses
bool PKB::setIfCondition(STMT_NO stmtNo, VAR_NAME varName) {
	return PKBIf::setIfUses(stmtNo, varName);
}

