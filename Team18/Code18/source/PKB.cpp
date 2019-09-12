#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "PKB.h"
#include "TNode.h"

unordered_set<string> PKB::varTable;
unordered_set<string> PKB::constantTable;
unordered_map<int, stmtType> PKB::stmtTable;
unordered_map<string, unordered_set<int>> PKB::stmtModifiesByVarTable;
unordered_map<string, unordered_set<int>> PKB::stmtUsesByVarTable;
unordered_map<int, unordered_set<string>> PKB::varModifiesByStmtTable;
unordered_map<int, unordered_set<string>> PKB::varUsesByStmtTable;
unordered_map<int, string> PKB::assignStmtTable;
unordered_map<string, unordered_set<int>> PKB::assignVarTable;
unordered_set<int> PKB::whileTable;
unordered_set<int> PKB::ifTable;

bool PKB::clear()
{
	varTable.clear();
	return true;
}

int PKB::setProcToAST(PROC p, TNode* r) {
	return 0;
}

TNode* PKB::getRootAST (PROC p){
	return nullptr;
}
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

bool PKB::setConstant(string constantName) {
	constantTable.emplace(constantName);
	return true;
}

unordered_set<string> PKB::getAllConstant() {
	return constantTable;
}

bool PKB::isConstantExist(string constantName) {
	//return true if element is found
	return (constantTable.find(constantName) != constantTable.end());
}

////////////////////////////////////
// stmtTable APIs
////////////////////////////////////

bool PKB::setStmt(int stmtNo, stmtType type) {
	try {
		stmtTable.emplace(stmtNo, type);
		return true;
	}
	catch (errc e) {
		return false;
	}
}

unordered_set<int> PKB::getAllStmt() {
	unordered_set<int> stmtNoList;
	for (auto keyValue : stmtTable) {
		stmtNoList.emplace(keyValue.first);
	}
	return stmtNoList;
}

bool PKB::isStmtExist(int stmtNo) {
	return (stmtTable.find(stmtNo) != stmtTable.end());
}

////////////////////////////////////
// varModifiesStmtTable APIs
////////////////////////////////////
bool PKB::setModifiesStmtByVar(int stmtNo, string varName) {
	
	try {
		//get stmtList from PKB then add variable to varList
		unordered_set<int> stmtList = getModifiesStmtByVar(varName);
		stmtList.emplace(stmtNo);
		//add it to varModifiesStmtTable
		stmtModifiesByVarTable[varName] = stmtList;
		return true;
	}
	catch (errc e) {
		return false;
	}
}

unordered_set<int> PKB::getModifiesStmtByVar(string varName) {
	return stmtModifiesByVarTable[varName];
}

unordered_set<string> PKB::getAllModifiesVar() {
	unordered_set<string> varList;
	for (auto keyValue : stmtModifiesByVarTable) {
		varList.emplace(keyValue.first);
	}
	return varList;
}

////////////////////////////////////
// varUsesStmtTable APIs
////////////////////////////////////
bool PKB::setUsesStmtByVar(int stmtNo, string varName) {

	try {
		//get varList from PKB then add variable to varList
		unordered_set<int> stmtList = getUsesStmtByVar(varName);
		stmtList.emplace(stmtNo);
		//add it to varModifiesStmtTable
		stmtUsesByVarTable[varName] = stmtList;
		return true;
	}
	catch (errc e) {
		return false;
	}
}

unordered_set<int> PKB::getUsesStmtByVar(string varName) {
	return stmtUsesByVarTable[varName];
}

unordered_set<string> PKB::getAllUsesVar() {
	unordered_set<string> varList;
	for (auto keyValue : stmtUsesByVarTable) {
		varList.emplace(keyValue.first);
	}
	return varList;
}

////////////////////////////////////
// varModifiesByStmtTable APIs
////////////////////////////////////
bool PKB::setModifiesVarByStmt(int stmtNo, string varName) {

	try {
		//get varList from PKB then add variable to varList
		unordered_set<string> varList = getModifiesVarByStmt(stmtNo);
		varList.emplace(varName);
		//add it to varModifiesStmtTable
		varModifiesByStmtTable[stmtNo] = varList;
		return true;
	}
	catch (errc e) {
		return false;
	}
}

unordered_set<string> PKB::getModifiesVarByStmt(int stmtNo) {
	return varModifiesByStmtTable[stmtNo];
}

unordered_set<int> PKB::getAllModifiesStmt() {
	unordered_set<int> stmtList;
	for (auto keyValue : varModifiesByStmtTable) {
		stmtList.emplace(keyValue.first);
	}
	return stmtList;
}

////////////////////////////////////
// varUsesByStmtTable APIs
////////////////////////////////////
bool PKB::setUsesVarByStmt(int stmtNo, string varName) {

	try {
		//get varList from PKB then add variable to varList
		unordered_set<string> varList = getUsesVarByStmt(stmtNo);
		varList.emplace(varName);
		//add it to varModifiesStmtTable
		varUsesByStmtTable[stmtNo] = varList;
		return true;
	}
	catch (errc e) {
		return false;
	}
}

unordered_set<string> PKB::getUsesVarByStmt(int stmtNo) {
	return varUsesByStmtTable[stmtNo];
}

unordered_set<int> PKB::getAllUsesStmt() {
	unordered_set<int> stmtList;
	for (auto keyValue : varUsesByStmtTable) {
		stmtList.emplace(keyValue.first);
	}
	return stmtList;
}

bool PKB::isModifiesStmtVar(int stmtNo, string varName){
	unordered_set<string> varList = getModifiesVarByStmt(stmtNo);
	for (auto keyValue : varList) {
		if (keyValue._Equal(varName)) {
			return true;
		}
	}
	return false;
}

bool PKB::isUsesStmtVar(int stmtNo, string varName) {
	unordered_set<string> varList = getUsesVarByStmt(stmtNo);
	for (auto keyValue : varList) {
		if (keyValue._Equal(varName)) {
			return true;
		}
	}
	return false;
}

////////////////////////////////////
// assignStmtTable APIs
////////////////////////////////////

unordered_set<int> PKB::getAllAssignStmt() {
	unordered_set<int> stmtList;
	for (auto keyValue : assignStmtTable) {
		stmtList.emplace(keyValue.first);
	}
	return stmtList;
}

bool PKB::setAssignStmt(int stmtNo, string varModified) {
	std::pair<int, string> entry(stmtNo, varModified);
	try {
		assignStmtTable.insert(entry);
		return true;
	}
	catch (errc e) {
		return false;
	}
};

string PKB::getVarModifiedByAssignStmt(int stmtNo) {
	return assignStmtTable[stmtNo]; 
}

////////////////////////////////////
// assignStmtByVarTable APIs
////////////////////////////////////

unordered_set<int> PKB::getAssignStmtByVar(string varName) {
	return assignVarTable[varName];
}


bool PKB::setAssignStmtByVar(int stmtNo, string varName) {
	try {
		//get stmtList from PKB then add variable to varList
		unordered_set<int> stmtList = getAssignStmtByVar(varName);
		stmtList.emplace(stmtNo);
		//add it to varModifiesStmtTable
		assignVarTable[varName] = stmtList;
		return true;
	}
	catch (errc e) {
		return false;
	}
}


////////////////////////////////////
// whileTable APIs
////////////////////////////////////

unordered_set<int> PKB::getAllWhileStmt() {
	return whileTable; 
};


bool PKB::setWhileStmt(int stmtNo) {
	try {
		whileTable.insert(stmtNo);
		return true;
	}
	catch (errc e) {
		return false;
	}
};

////////////////////////////////////
// ifTable APIs
////////////////////////////////////

unordered_set<int> PKB::getAllIfStmt() {
	return ifTable;
};


bool PKB::setIfStmt(int stmtNo) {
	try {
		ifTable.insert(stmtNo);
		return true;
	}
	catch (errc e) {
		return false;
	}
};



////////////////////////////////////
// Higher Level APIs that use one or more tables
////////////////////////////////////

/* 
//Archived as of 2019-09-11 
//Gets list of assignment statements that modifies a variable through an assignment statment
//Modifies(a,v) holds if variable v appears on the left side of A 
unordered_set<int> PKB::getStmtsThatModVarByAssign(string varName) {
	unordered_set<int> varList = getModifiesStmtByVar(varName);  //{3,5,7,etc}
	unordered_set<int> results;
	for (auto stmtNo : varList) {
		stmtType type = stmtTable[stmtNo];
		stmtType assignment = Assign;
		if (type == assignment) { //
			results.insert(stmtNo );
		}
	}
	for (auto stmNo : results) {
		printf("%d", stmNo);
	}
	
	return results;
}
*/

	
	
	
