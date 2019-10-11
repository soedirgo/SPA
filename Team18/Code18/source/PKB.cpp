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

//Follow Bool Evaluation
bool PKB::isFollowsAnyAny() {
	return PKBFollows::isFollowsAnyAny();
}
bool PKB::isFollowsAnyIdent(STMT_NO s2) {
	return PKBFollows::isFollowsAnyIdent(s2);
}
bool PKB::isFollowsIdentAny(STMT_NO s1) {
	return PKBFollows::isFollowsIdentAny(s1);
}
bool PKB::isFollowsIdentIdent(STMT_NO s1, STMT_NO s2) {
	return PKBFollows::isFollowsIdentIdent(s1, s2);
}

bool PKB::isFollowsTAnyAny() {
	return PKBFollows::isFollowsTAnyAny();
}
bool PKB::isFollowsTAnyIdent(STMT_NO s2) {
	return PKBFollows::isFollowsTAnyIdent(s2);
}
bool PKB::isFollowsTIdentAny(STMT_NO s1) {
	return PKBFollows::isFollowsTIdentAny(s1);
}
bool PKB::isFollowsTIdentIdent(STMT_NO s1, STMT_NO s2) {
	return PKBFollows::isFollowsTIdentIdent(s1, s2);
}

//Follow Table Evaluation
TABLE PKB::getFollowsAnyEnt(STMT_TYPE s2) {
	return PKBFollows::getFollowsAnyEnt(s2);
}
TABLE PKB::getFollowsIdentEnt(STMT_NO s1, STMT_TYPE s2) {
	return PKBFollows::getFollowsIdentEnt(s1, s2);
}
TABLE PKB::getFollowsEntAny(STMT_TYPE s1) {
	return PKBFollows::getFollowsEntAny(s1);
}
TABLE PKB::getFollowsEntIdent(STMT_TYPE s1, STMT_NO s2) {
	return PKBFollows::getFollowsEntIdent(s1, s2);
}
TABLE PKB::getFollowsEntEnt(STMT_TYPE s1, STMT_TYPE s2) {
	return PKBFollows::getFollowsEntEnt(s1, s2);
}

TABLE PKB::getFollowsTAnyEnt(STMT_TYPE s2) {
	return PKBFollows::getFollowsTAnyEnt(s2);
}
TABLE PKB::getFollowsTIdentEnt(STMT_NO s1, STMT_TYPE s2) {
	return PKBFollows::getFollowsTIdentEnt(s1, s2);
}
TABLE PKB::getFollowsTEntAny(STMT_TYPE s1) {
	return PKBFollows::getFollowsTEntAny(s1);
}
TABLE PKB::getFollowsTEntIdent(STMT_TYPE s1, STMT_NO s2) {
	return PKBFollows::getFollowsTEntIdent(s1, s2);
}
TABLE PKB::getFollowsTEntEnt(STMT_TYPE s1, STMT_TYPE s2) {
	return PKBFollows::getFollowsTEntEnt(s1, s2);
}

//Parents
bool PKB::setParent(STMT_NO parent, STMT_NO child) {
	return PKBParent::setParent(parent, child);
}

bool PKB::setParentT(STMT_NO parent, STMT_NO child) {
	return PKBParent::setParentStar(parent, child);
}


bool PKB::isParentExist(STMT_NO child) {
	return PKBParent::isParentExist(child);
}

STMT_NO PKB::getParentStmt(STMT_NO child) {
	return PKBParent::getParent(child);
}

//Parent Evaluation Bool Functions
bool PKB::isParentAnyAny() { 
	return PKBParent::isParentAnyAny();
}
bool PKB::isParentAnyIdent(STMT_NO s2) {
	return PKBParent::isParentAnyIdent(s2);
}
bool PKB::isParentIdentAny(STMT_NO s1) {
	return PKBParent::isParentIdentAny(s1);
}
bool PKB::isParentIdentIdent(STMT_NO s1, STMT_NO s2) {
	return PKBParent::isParentIdentIdent(s1, s2);
}

bool PKB::isParentTAnyAny() {
	return PKBParent::isParentTAnyAny();
}
bool PKB::isParentTAnyIdent(STMT_NO s2) {
	return PKBParent::isParentTAnyIdent(s2);
}
bool PKB::isParentTIdentAny(STMT_NO s1) {
	return PKBParent::isParentTIdentAny(s1);
}
bool PKB::isParentTIdentIdent(STMT_NO s1, STMT_NO s2) {
	return PKBParent::isParentTIdentIdent(s1, s2);
}

//Parent Evaluation Table Functions
TABLE PKB::getParentAnyEnt(STMT_TYPE s2) {
	return PKBParent::getParentAnyEnt(s2);
}
TABLE PKB::getParentIdentEnt(STMT_NO s1, STMT_TYPE s2) {
	return PKBParent::getParentIdentEnt(s1,s2);
}
TABLE PKB::getParentEntAny(STMT_TYPE s1) {
	return PKBParent::getParentEntAny(s1);
}
TABLE PKB::getParentEntIdent(STMT_TYPE s1, STMT_NO s2) {
	return PKBParent::getParentEntIdent(s1, s2);
}
TABLE PKB::getParentEntEnt(STMT_TYPE s1, STMT_TYPE s2) {
	return PKBParent::getParentEntEnt(s1, s2);
}

TABLE PKB::getParentTAnyEnt(STMT_TYPE s2) {
	return PKBParent::getParentTAnyEnt(s2);
}
TABLE PKB::getParentTIdentEnt(STMT_NO s1, STMT_TYPE s2) {
	return PKBParent::getParentTIdentEnt(s1, s2);
}
TABLE PKB::getParentTEntAny(STMT_TYPE s1) {
	return PKBParent::getParentTEntAny(s1);
}
TABLE PKB::getParentTEntIdent(STMT_TYPE s1, STMT_NO s2) {
	return PKBParent::getParentTEntIdent(s1,s2);
}
TABLE PKB::getParentTEntEnt(STMT_TYPE s1, STMT_TYPE s2) {
	return PKBParent::getParentTEntEnt(s1, s2);
}


//Modifies
bool PKB::setModifiesS(STMT_NO stmtNo, VAR_NAME varName) {
	return PKBModifies::setModifiesS(stmtNo, varName);
};

bool PKB::setModifiesP(PROC_NAME procName, VAR_NAME varName) {
	return PKBModifies::setModifiesP(procName, varName);
};

//Modifies Bool Evaluation
bool PKB::isModifiesSIdentAny(STMT_NO stmtNo) {
	return PKBModifies::isModifiesSIdentAny(stmtNo);
}
bool PKB::isModifiesSIdentIdent(STMT_NO stmtNo, VAR_NAME varName) {
	return PKBModifies::isModifiesSIdentIdent(stmtNo, varName);
}

bool PKB::isModifiesPIdentAny(PROC_NAME procName) {
	return PKBModifies::isModifiesPIdentAny(procName);
}
bool PKB::isModifiesPIdentIdent(PROC_NAME procName, VAR_NAME varName) {
	return PKBModifies::isModifiesPIdentIdent(procName, varName);
}

//Modifies Table Evaluation
STMT_LIST PKB::getModifiesSEntAny(STMT_TYPE type) {
	return PKBModifies::getModifiesSEntAny(type);
}
TABLE PKB::getModifiesSEntIdent(STMT_TYPE type, VAR_NAME varName) {
	return PKBModifies::getModifiesSEntIdent(type, varName);
}
VAR_LIST PKB::getModifiesSIdentEnt(STMT_NO stmtNo) {
	return PKBModifies::getModifiesSIdentEnt(stmtNo);
}
TABLE PKB::getModifiesSEntEnt(STMT_TYPE type) {
	return PKBModifies::getModifiesSEntEnt(type);
}

PROC_LIST PKB::getModifiesPEntAny() {
	return PKBModifies::getModifiesPEntAny();
}
PROC_LIST PKB::getModifiesPEntIdent(VAR_NAME varName) {
	return PKBModifies::getModifiesPEntIdent(varName);
}
VAR_LIST PKB::getModifiesPIdentEnt(PROC_NAME procName) {
	return PKBModifies::getModifiesPIdentEnt(procName);
}
TABLE PKB::getModifiesPEntEnt() {
	return PKBModifies::getModifiesPEntEnt();
}


//Uses
bool PKB::setUsesS(STMT_NO stmtNo, VAR_NAME varName) {
	return PKBUses::setUsesS(stmtNo, varName);

};

bool PKB::setUsesP(PROC_NAME procName, VAR_NAME varName) {
	return PKBUses::setUsesP(procName, varName);
};

//Uses Bool Evaluation
bool PKB::isUsesSIdentAny(STMT_NO stmtNo) {
	return PKBUses::isUsesSIdentAny(stmtNo);
}
bool PKB::isUsesSIdentIdent(STMT_NO stmtNo, VAR_NAME varName) {
	return PKBUses::isUsesSIdentIdent(stmtNo, varName);
}

bool PKB::isUsesPIdentAny(PROC_NAME procName) {
	return PKBUses::isUsesPIdentAny(procName);
}
bool PKB::isUsesPIdentIdent(PROC_NAME procName, VAR_NAME varName) {
	return PKBUses::isUsesPIdentIdent(procName, varName);
}

//Uses Table Evaluation
STMT_LIST PKB::getUsesSEntAny(STMT_TYPE type) {
	return PKBUses::getUsesSEntAny(type);
}
STMT_LIST PKB::getUsesSEntIdent(STMT_TYPE type, VAR_NAME varName) {
	return  PKBUses::getUsesSEntIdent(type, varName);
}
VAR_LIST PKB::getUsesSIdentEnt(STMT_NO stmtNo) {
	return  PKBUses::getUsesSIdentEnt(stmtNo);
}
TABLE PKB::getUsesSEntEnt(STMT_TYPE type) {
	return PKBUses::getUsesSEntEnt(type);
}

PROC_LIST PKB::getUsesPEntAny() {
	return PKBUses::getUsesPEntAny();
}
PROC_LIST PKB::getUsesPEntIdent(VAR_NAME varName) {
	return PKB::getUsesPEntIdent(varName);
}
VAR_LIST PKB::getUsesPIdentEnt(PROC_NAME procName) {
	return PKB::getUsesPIdentEnt(procName);
}
TABLE PKB::getUsesPEntEnt() {
	return PKB::getUsesPEntEnt();
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
		PKBModifies::setModifiesS(stmtNo, varModified);
		if (!varUsed.empty()) {
			for (string var : varUsed) {
				setUsesS(stmtNo, var);
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

bool PKB::setVariable(VAR_NAME varName) {
	return PKBVariable::setVariable(varName);
}

VAR_LIST PKB::getVariables() {
	return PKBVariable::getVariables();
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

CONST_LIST PKB::getConstants() {
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
	return PKBStmt::getAllStmtByType("assign");
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
	return PKBStmt::getAllStmtByType("while");
};


////////////////////////////////////
// ifTable APIs
////////////////////////////////////

STMT_LIST PKB::getIfs() {
	return PKBStmt::getAllStmtByType("if");
};

////////////////////////////////////
// printTable APIs
////////////////////////////////////

STMT_LIST PKB::getPrints() {
	return PKBStmt::getAllStmtByType("print");
};

bool PKB::setPrint(STMT_NO stmtNo, VAR_NAME varName) {
	return PKBPrint::setPrint(stmtNo, varName);
};

////////////////////////////////////
// ReadTable APIs
////////////////////////////////////

STMT_LIST PKB::getReads() {
	return PKBStmt::getAllStmtByType("read");
};

bool PKB::setRead(STMT_NO stmtNo, VAR_NAME varName) {
	return PKBRead::setRead(stmtNo, varName);
};


////////////////////////////////////
// ProecedureTable APIs
////////////////////////////////////

PROC_LIST PKB::getProcedures() {
	return PKBProcedure::getProcedures();
};


bool PKB::setProcedure(PROC_NAME procName) {
	return PKBProcedure::setProcedure(procName);
};


////////////////////////////////////
// CallTable APIs
////////////////////////////////////

STMT_LIST PKB::getCalls() {
	return PKBStmt::getAllStmtByType("call");
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

//Call Bool Evaluation
bool PKB::isCallsAnyAny() {
	return PKBCall::isCallsAnyAny();
}
bool PKB::isCallsAnyIdent(PROC_NAME p2) {
	return PKBCall::isCallsAnyIdent(p2);
}
bool PKB::isCallsIdentAny(PROC_NAME p1) {
	return PKBCall::isCallsIdentAny(p1);
}
bool PKB::isCallsIdentIdent(PROC_NAME p1, PROC_NAME p2) {
	return PKBCall::isCallsIdentIdent(p1,p2);
}

bool PKB::isCallsTAnyAny() {
	return PKBCall::isCallsTAnyAny();
}
bool PKB::isCallsTAnyIdent(PROC_NAME p2) {
	return PKBCall::isCallsTAnyIdent(p2);
}
bool PKB::isCallsTIdentAny(PROC_NAME p1) {
	return PKBCall::isCallsTIdentAny(p1);
}
bool PKB::isCallsTIdentIdent(PROC_NAME p1, PROC_NAME p2) {
	return PKBCall::isCallsTIdentIdent(p1,p2);
}

//Call Table Evaluation
TABLE PKB::getCallsAnyEnt() {
	return PKBCall::getCallsAnyEnt();
}
TABLE PKB::getCallsIdentEnt(PROC_NAME p1) {
	return PKBCall::getCallsIdentEnt(p1);
}
TABLE PKB::getCallsEntAny() {
	return PKBCall::getCallsEntAny();
}
TABLE PKB::getCallsEntIdent(PROC_NAME p2) {
	return PKBCall::getCallsEntIdent(p2);
}
TABLE PKB::getCallsEntEnt() {
	return PKBCall::getCallsEntEnt();
}

TABLE PKB::getCallsTAnyEnt() {
	return PKBCall::getCallsTAnyEnt();
}
TABLE PKB::getCallsTIdentEnt(PROC_NAME p1) {
	return PKBCall::getCallsTIdentEnt(p1);
}
TABLE PKB::getCallsTEntAny() {
	return PKBCall::getCallsTEntAny();
}
TABLE PKB::getCallsTEntIdent(PROC_NAME p2) {
	return PKBCall::getCallsTEntIdent(p2);
}
TABLE PKB::getCallsTEntEnt() {
	return PKBCall::getCallsTEntEnt();
}

////////////////////////////////////
// NextTable APIs
////////////////////////////////////
STMT_LIST PKB::getProgLines() {
	return PKBStmt::getAllStmt();
}

bool PKB::setNext(PROG_LINE n1, PROG_LINE n2) {
	return PKBNext::setNext(n1, n2);
};

//Next Bool Evaluation
bool PKB::isNextAnyAny() {
	return PKBNext::isNextAnyAny();
}
bool PKB::isNextAnyIdent(PROG_LINE n2) {
	return PKBNext::isNextAnyIdent(n2);
}
bool PKB::isNextIdentAny(PROG_LINE n1) {
	return PKBNext::isNextIdentAny(n1);
}
bool PKB::isNextIdentIdent(PROG_LINE n1, PROG_LINE n2) {
	return PKBNext::isNextIdentIdent(n1,n2);
}

bool PKB::isNextTAnyAny() {
	return PKBNext::isNextTAnyAny();
}
bool PKB::isNextTAnyIdent(PROG_LINE n2) {
	return PKBNext::isNextTAnyIdent(n2);
}
bool PKB::isNextTIdentAny(PROG_LINE n1) {
	return PKBNext::isNextTIdentAny(n1);
}
bool PKB::isNextTIdentIdent(PROG_LINE n1, PROG_LINE n2) {
	return PKBNext::isNextTIdentIdent(n1,n2);
}

//Next Table Evaluation
TABLE PKB::getNextAnyEnt() {
	return PKBNext::getNextAnyEnt();
}
TABLE PKB::getNextIdentEnt(PROG_LINE n1) {
	return PKBNext::getNextIdentEnt(n1);
}
TABLE PKB::getNextEntAny() {
	return PKBNext::getNextEntAny();
}
TABLE PKB::getNextEntIdent(PROG_LINE n2) {
	return PKBNext::getNextEntIdent(n2);
}
TABLE PKB::getNextEntEnt() {
	return PKBNext::getNextEntEnt();
}

TABLE PKB::getNextTAnyEnt() {
	return PKBNext::getNextTAnyEnt();
}
TABLE PKB::getNextTIdentEnt(PROG_LINE n1) {
	return PKBNext::getNextTIdentEnt(n1);
}
TABLE PKB::getNextTEntAny() {
	return PKBNext::getNextTEntAny();
}
TABLE PKB::getNextTEntIdent(PROG_LINE n2) {
	return PKBNext::getNextTEntIdent(n2);
}
TABLE PKB::getNextTEntEnt() {
	return PKBNext::getNextTEntEnt();
}


// New While Uses
bool PKB::setWhileCondition(STMT_NO stmtNo, VAR_NAME varName) {
	return PKBWhile::setWhileUses(stmtNo, varName);
}

// New If Uses
bool PKB::setIfCondition(STMT_NO stmtNo, VAR_NAME varName) {
	return PKBIf::setIfUses(stmtNo, varName);
}

