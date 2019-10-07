#include <iostream>
#include <string>
#include <vector>
#include "PKB.h"
#include "TNode.h"
#include "PKBParent.h"
#include "PKBFollow.h"
#include "PKBUses.h"
#include "PKBModifies.h"
#include "PKBStmt.h"
#include "PKBProcedure.h"
#include "PKBVariable.h"
#include "PKBCall.h"
#include "PKBNext.h"
#include "PKBPrint.h"
#include "PKBRead.h"


using namespace std;

unordered_map<string, unordered_set<int>> PKB::constantTable;
unordered_map<string, unordered_set<int>> PKB::stmtUsesByVarTable;
unordered_map<int, string> PKB::assignStmtTable;
unordered_map<string, unordered_set<int>> PKB::assignVarTable;


bool PKB::clear()
{
	PKBFollows pkbFollow;
	pkbFollow.clear();

	PKBParent pkbParent;
	pkbParent.clear();

	PKBStmt pkbStmt;
	pkbStmt.clear();

	PKBUses pkbUses;
	pkbUses.clear();

	constantTable.clear(); 
	stmtUsesByVarTable.clear();
	assignStmtTable.clear();
	assignVarTable.clear();

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

bool PKB::setFollowsRelation(STMT_NO followedBy, STMT_NO follow) {
	return PKBFollows::setFollows(followedBy, follow);
}

bool PKB::setFollowsStarRelation(STMT_NO followedBy, STMT_NO follow) {
	return PKBFollows::setFollowsStar(followedBy, follow);
}

bool PKB::isFollowsRelationship(STMT_NO followedBy, STMT_NO follow) {
	return PKBFollows::isFollowsRelationship(followedBy, follow);
}

bool PKB::isFollowsStarRelationship(STMT_NO followedBy, STMT_NO follow) {
	return PKBFollows::isFollowsStarRelationship(followedBy, follow);
}

bool PKB::setParentRelation(STMT_NO parent, STMT_NO child) {
	return PKBParent::setParent(parent, child);
}

bool PKB::setParentStarRelation(STMT_NO parent, STMT_NO child) {
	return PKBParent::setParentStar(parent, child);
}

bool PKB::isParentRelationship(STMT_NO parent, STMT_NO child) {
	return PKBParent::isParentRelationship(parent, child);
}

bool PKB::isParentStarRelationship(STMT_NO parent, STMT_NO child) {
	return PKBParent::isParentStarRelationship(parent, child);
}

bool PKB::isConstUsedInAssign(STMT_NO assignStmtNo, string c) {
	STMT_LIST stmtList = getStmtByConst(c); 
	for (auto stmt : stmtList) {
		if (stmt == assignStmtNo) {
			return true;
		}
	}
	return false; 
}

bool PKB::isVarUsedInAssign(STMT_NO assignStmtNo, string varName) {
	STMT_LIST stmtList = getUsesStmtByVar(varName);
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


bool PKB::setModifiesRelation(STMT_NO stmtNo, string varName) {
	return PKBModifies::setModifiesStmt(stmtNo, varName);
};

bool PKB::insertUsesRelation(STMT_NO stmtNo, string varName) {
	try {
		return setUsesStmt(stmtNo, varName) && setUsesVarByStmt(stmtNo, varName);
	}
	catch (errc) {
		return false;
	}

};


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

////////////////////////////////////
// varTable APIs
////////////////////////////////////

bool PKB::setVar(VAR_NAME varName) {
	return PKBVariable::setVar(varName);
}

VAR_LIST PKB::getAllVar() {
	return PKBVariable::getAllVar();
}

////////////////////////////////////
// constantTable APIs
////////////////////////////////////

bool PKB::setConstant(string constantName, int stmtNo) {
	
	try {
		unordered_set<int> stmtList = getStmtByConst(constantName);
		stmtList.emplace(stmtNo);
		constantTable[constantName] = stmtList;
		return true;
	}
	catch (errc) {
		return false;
	}
}

unordered_set<int> PKB::getStmtByConst(string constantName) {
	unordered_set<int> empty;
	if (PKB::isConstantExist(constantName)) {
		return constantTable[constantName];
	}
	else {
		return empty;
	}
}


unordered_set<string> PKB::getAllConstant() {
	unordered_set<string> stmtNoList;
	for (auto keyValue : constantTable) {
		stmtNoList.emplace(keyValue.first);
	}
	return stmtNoList;
}

bool PKB::isConstantExist(string constantName) {
	//return true if element is found
	unordered_set<string> constantList = getAllConstant();
	return (constantList.find(constantName) != constantList.end());
}

////////////////////////////////////
// stmtTable APIs
////////////////////////////////////

bool PKB::setStmt(STMT_NO stmtNo, STMT_TYPE type) {
	return PKBStmt::setStmt(stmtNo, type);
}

STMT_LIST PKB::getAllStmt() {
	return PKBStmt::getAllStmt();
}

bool PKB::isStmtExist(STMT_NO stmtNo) {
	//return (stmtTable.find(stmtNo) != stmtTable.end());
	return false;
}

////////////////////////////////////
// varUsesStmtTable APIs
////////////////////////////////////
bool PKB::setUsesStmt(STMT_NO stmtNo, VAR_NAME varName) {
	

	try {
		//get varList from PKB then add variable to varList
		unordered_set<int> stmtList = getUsesStmtByVar(varName);
		stmtList.emplace(stmtNo);
		//add it to varModifiesStmtTable
		stmtUsesByVarTable[varName] = stmtList;
		return true;
	}
	catch (errc) {
		return false;
	}
}

STMT_LIST PKB::getUsesStmtByVar(string varName) {
	unordered_set<int> empty;
	unordered_set<string> varList = getAllUsesVar();
	if (varList.find(varName) != varList.end()) {
		return stmtUsesByVarTable[varName];
	}
	else {
		return empty;
	}
	
}

VAR_LIST PKB::getAllUsesVar() {
	unordered_set<string> varList;
	for (auto keyValue : stmtUsesByVarTable) {
		varList.emplace(keyValue.first);
	}
	return varList;
}

////////////////////////////////////
// varUsesByStmtTable APIs
////////////////////////////////////
bool PKB::setUsesVarByStmt(STMT_NO stmtNo, string varName) {
	return PKBUses::setUsesStmt(stmtNo, varName);
}

bool PKB::isModifiesStmtRelationship(STMT_NO stmtNo, VAR_NAME varName){
	return PKBModifies::isModifiesStmtRelationship(stmtNo, varName);
}

bool PKB::isUsesStmtRelationship(STMT_NO stmtNo, VAR_NAME varName) {
	return PKBUses::isUsesStmtRelationship(stmtNo, varName);
}

////////////////////////////////////
// assignStmtTable APIs
////////////////////////////////////

STMT_LIST PKB::getAllAssignStmt() {
	return PKBStmt::getAllStmtByType(Assign);
}

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

////////////////////////////////////
// assignStmtByVarTable APIs
////////////////////////////////////

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


////////////////////////////////////
// whileTable APIs
////////////////////////////////////

STMT_LIST PKB::getAllWhileStmt() {
	return PKBStmt::getAllStmtByType(While);
};


////////////////////////////////////
// ifTable APIs
////////////////////////////////////

STMT_LIST PKB::getAllIfStmt() {
	return PKBStmt::getAllStmtByType(If);
};

////////////////////////////////////
// printTable APIs
////////////////////////////////////

STMT_LIST PKB::getAllPrintStmt() {
	return PKBStmt::getAllStmtByType(Print);
};

bool PKB::setPrintStmt(STMT_NO stmtNo, string varName) {
	return PKBPrint::setPrint(stmtNo, varName);
};

////////////////////////////////////
// ReadTable APIs
////////////////////////////////////

STMT_LIST PKB::getAllReadStmt() {
	return PKBStmt::getAllStmtByType(Read);
};

bool PKB::setReadStmt(STMT_NO stmtNo, string varName) {
	return PKBRead::setRead(stmtNo, varName);
};


////////////////////////////////////
// ProecedureTable APIs
////////////////////////////////////

unordered_set<string> PKB::getAllProc() {
	return PKBProcedure::getAllProc();
};


bool PKB::setProc(string procName) {
	return PKBProcedure::setProc(procName);
};


////////////////////////////////////
// CallTable APIs
////////////////////////////////////

STMT_LIST PKB::getAllCallStmt() {
	return PKBStmt::getAllStmtByType(Call);
};

bool PKB::setCallProcRelation(PROC_NAME caller, PROC_NAME callee) {
	return PKBCall::setCallProc(caller, callee);
}

bool PKB::setCallStmt(STMT_NO stmtNo, PROC_NAME procName) {
	return PKBCall::setCallStmt(stmtNo, procName);
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
bool PKB::setNextRelation(PROG_LINE n1, PROG_LINE n2) {
	return PKBNext::setNext(n1, n2);
};

bool PKB::isNextRelationship(PROG_LINE n1, PROG_LINE n2) {
	return PKBNext::isNextRelationship(n1, n2);
}

bool PKB::isNextStarRelationship(PROG_LINE n1, PROG_LINE n2) {
	return PKBNext::isNextStarRelationship(n1, n2);
}