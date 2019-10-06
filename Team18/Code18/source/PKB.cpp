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


using namespace std;

unordered_set<string> PKB::varTable;
unordered_map<string, unordered_set<int>> PKB::constantTable;
unordered_map<int, STMT_TYPE> PKB::stmtTable;
unordered_map<string, unordered_set<int>> PKB::stmtModifiesByVarTable;
unordered_map<string, unordered_set<int>> PKB::stmtUsesByVarTable;
unordered_map<int, string> PKB::assignStmtTable;
unordered_map<string, unordered_set<int>> PKB::assignVarTable;
unordered_map<string, unordered_set<int>> PKB::printTable;
unordered_map<string, unordered_set<int>> PKB::readTable;
unordered_map<string, unordered_set<int>> PKB:: callTable;


bool PKB::clear()
{
	PKBFollow pkbFollow;
	pkbFollow.clear();

	PKBParent pkbParent;
	pkbParent.clear();

	PKBStmt pkbStmt;
	pkbStmt.clear();

	PKBUses pkbUses;
	pkbUses.clear();

	varTable.clear();
	constantTable.clear(); 
	stmtTable.clear();
	stmtModifiesByVarTable.clear();
	stmtUsesByVarTable.clear();
	assignStmtTable.clear();
	assignVarTable.clear();
	printTable.clear();
	readTable.clear();
	callTable.clear();

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

bool PKB::insertFollowRelation(STMT_NO followedBy, STMT_NO follow) {
	return PKBFollow::setFollow(followedBy, follow) && PKBFollow::setFollowedBy(followedBy, follow);
}

bool PKB::insertFollowStarRelation(STMT_NO followedBy, STMT_NO follow) {
	return PKBFollow::setFollowStar(followedBy, follow);
}

bool PKB::isFollowRelationship(STMT_NO followedBy, STMT_NO follow) {
	return PKBFollow::isFollowRelationship(followedBy, follow);
}

bool PKB::isFollowStarRelationship(STMT_NO followedBy, STMT_NO follow) {
	return PKBFollow::isFollowStarRelationship(followedBy, follow);
}

STMT_NO PKB::getFollowStmt(STMT_NO followedBy) {
	return PKBFollow::getFollowStmt(followedBy);
}

STMT_LIST PKB::getFollowedByStmtList(STMT_NO follow) {
	return PKBFollow::getFollowedByStmtList(follow);
}

STMT_LIST PKB::getFollowStarStmtList(STMT_NO followedBy) {
	return PKBFollow::getFollowStarStmtList(followedBy);
}

bool PKB::insertParentRelation(STMT_NO parent, STMT_NO child) {
	return PKBParent::setChildren(parent,child) && PKBParent::setParent(parent,child);
}

bool PKB::insertParentStarRelation(STMT_NO parent, STMT_NO child) {
	return PKBParent::setParentStar(parent, child);
}

bool PKB::isParentRelationship(STMT_NO parent, STMT_NO child) {
	return PKBParent::isParentRelationship(parent, child);
}

bool PKB::isParentStarRelationship(STMT_NO parent, STMT_NO child) {
	return PKBParent::isParentStarRelationship(parent, child);
}

STMT_LIST PKB::getParentStarStmtList(STMT_NO child) {
	return PKBParent::getParentStarStmtList(child);
}

STMT_LIST PKB::getChildrenStmtList(STMT_NO parent) {
	return PKBParent::getChildrenStmtList(parent);
}

STMT_NO PKB::getParentStmt(STMT_NO child) {
	return PKBParent::getParentStmt(child);
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


bool PKB::insertModifiesRelation(STMT_NO stmtNo, string varName) {
	try {
		return setModifiesStmtByVar(stmtNo, varName) && setModifiesVarByStmt(stmtNo, varName);
	}
	catch (errc) {
		return false;
	}
};

bool PKB::insertUsesRelation(STMT_NO stmtNo, string varName) {
	try {
		return setUsesStmtByVar(stmtNo, varName) && setUsesVarByStmt(stmtNo, varName);
	}
	catch (errc) {
		return false;
	}

};


bool PKB::insertAssignRelation(int stmtNo, string varModified, unordered_set<string> varUsed, unordered_set<string> constUsed) {
	try {
		setAssignStmt(stmtNo, varModified);
		setAssignStmtByVar(stmtNo, varModified);
		
		setModifiesStmtByVar(stmtNo, varModified);
		setModifiesVarByStmt(stmtNo, varModified);
		if (!varUsed.empty()) {
			for (string var : varUsed) {
				setUsesStmtByVar(stmtNo, var);
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

bool PKB::setVar(string varName) {
	varTable.emplace(varName);
	return true;
}

unordered_set<string> PKB::getAllVar() {
	return varTable;
}

bool PKB::isVarExist(string varName) {
	//return true if element is found
	return (varTable.find(varName) != varTable.end());
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
	return (stmtTable.find(stmtNo) != stmtTable.end());
}

////////////////////////////////////
// varModifiesStmtTable APIs
////////////////////////////////////
bool PKB::setModifiesStmtByVar(STMT_NO stmtNo, string varName) {
	
	try {
		//get stmtList from PKB then add variable to varList
		unordered_set<int> stmtList = getModifiesStmtByVar(varName);
		stmtList.emplace(stmtNo);
		//add it to varModifiesStmtTable
		stmtModifiesByVarTable[varName] = stmtList;
		return true;
	}
	catch (errc) {
		return false;
	}
}

STMT_LIST PKB::getModifiesStmtByVar(string varName) {
	return stmtModifiesByVarTable[varName];
}

VAR_LIST PKB::getAllModifiesVar() {
	unordered_set<string> varList;
	for (auto keyValue : stmtModifiesByVarTable) {
		varList.emplace(keyValue.first);
	}
	return varList;
}

////////////////////////////////////
// varUsesStmtTable APIs
////////////////////////////////////
bool PKB::setUsesStmtByVar(STMT_NO stmtNo, string varName) {
	

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
// varModifiesByStmtTable APIs
////////////////////////////////////
bool PKB::setModifiesVarByStmt(STMT_NO stmtNo, string varName) {
	return PKBModifies::setModifiesVarByStmt(stmtNo, varName);
}
/*
VAR_LIST PKB::getModifiesVarByStmt(STMT_NO stmtNo) {
	return varModifiesByStmtTable[stmtNo];
}

STMT_LIST PKB::getAllModifiesStmt() {
	unordered_set<int> stmtList;
	for (auto keyValue : varModifiesByStmtTable) {
		stmtList.emplace(keyValue.first);
	}
	return stmtList;
}
*/

////////////////////////////////////
// varUsesByStmtTable APIs
////////////////////////////////////
bool PKB::setUsesVarByStmt(STMT_NO stmtNo, string varName) {
	return PKBUses::setUsesVarByStmt(stmtNo, varName);
}

/*
VAR_LIST PKB::getUsesVarByStmt(STMT_NO stmtNo) {
	return varUsesByStmtTable[stmtNo];
}

STMT_LIST PKB::getAllUsesStmt() {
	unordered_set<int> stmtList;
	for (auto keyValue : varUsesByStmtTable) {
		stmtList.emplace(keyValue.first);
	}
	return stmtList;
}
*/

bool PKB::isModifiesStmtVar(STMT_NO stmtNo, string varName){
	return PKBModifies::isModifiesStmtVar(stmtNo, varName);
}

bool PKB::isUsesStmtVar(STMT_NO stmtNo, string varName) {
	return PKBUses::isUsesStmtVar(stmtNo, varName);
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


STMT_LIST PKB::getPrintStmtByVar(string varName) {
	return printTable[varName];
}


bool PKB::setPrintStmt(STMT_NO stmtNo, string varName) {
	try {
		//get stmtList from PKB then add variable to varList
		unordered_set<int> stmtList = getPrintStmtByVar(varName);
		stmtList.emplace(stmtNo);
		//add it to varModifiesStmtTable
		printTable[varName] = stmtList;
		return true;
	}
	catch (errc) {
		return false;
	}
};




////////////////////////////////////
// ReadTable APIs
////////////////////////////////////

STMT_LIST PKB::getAllReadStmt() {
	return PKBStmt::getAllStmtByType(Read);
};


STMT_LIST PKB::getReadStmtByVar(string varName) {
	return readTable[varName];
}


bool PKB::setReadStmt(STMT_NO stmtNo, string varName) {
	try {
		//get stmtList from PKB then add variable to varList
		unordered_set<int> stmtList = getReadStmtByVar(varName);
		stmtList.emplace(stmtNo);
		//add it to varModifiesStmtTable
		readTable[varName] = stmtList;
		return true;
	}
	catch (errc) {
		return false;
	}
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


STMT_LIST PKB::getCallStmtByVar(string varName) {
	return callTable[varName];
}


bool PKB::setCallStmt(STMT_NO stmtNo, string varName) {
	try {
		//get stmtList from PKB then add variable to varList
		unordered_set<int> stmtList = getCallStmtByVar(varName);
		stmtList.emplace(stmtNo);
		//add it to varModifiesStmtTable
		callTable[varName] = stmtList;
		return true;
	}
	catch (errc) {
		return false;
	}
};