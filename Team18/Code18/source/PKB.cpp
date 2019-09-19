#include <iostream>
#include <string>
#include <vector>
#include "PKB.h"
#include "TNode.h"
#include "PKBParent.h"
#include "PKBFollow.h"

using namespace std;

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
unordered_map<string, unordered_set<int>> PKB::printTable;
unordered_map<string, unordered_set<int>> PKB::readTable;
unordered_set<string> PKB::procedureTable;
unordered_map<string, unordered_set<int>> PKB:: callTable;



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

STMT_LIST PKB::getFollowStarStmtList(STMT_NO follow) {
	return PKBFollow::getFollowStarStmtList(follow);
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

bool PKB::insertAssignRelation(STMT_NO stmtNo, string varName) {
	try {
		return setAssignStmt(stmtNo, varName) && setAssignStmtByVar(stmtNo, varName);
	}
	catch (errc) {
		return false;
	}
};

STMT_LIST PKB::getAllStmtByType(string type) {
	//stmtType typeEnum; 
	
	if (type.compare("read") == 0 ) {
		//typeEnum = Read;
		return getAllReadStmt(); 
	}
	else if (type.compare("print") == 0) {
		//typeEnum = Print;
		return getAllPrintStmt();
	}
	else if ( (type.compare("assign")) == 0) {
		//typeEnum = Assign;
		return getAllAssignStmt();
	}
	else if (type.compare("while") == 0 ) {
		//typeEnum = While;
		return getAllWhileStmt();
	}
	else if (type.compare("if") == 0) {
		//typeEnum = If;
		return getAllIfStmt();
	}
	else if (type.compare("call") == 0) {
		//typeEnum = Call;
		return getAllCallStmt();
	}

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

CONST_LIST PKB::getAllConstant() {
	return constantTable;
}

bool PKB::isConstantExist(string constantName) {
	//return true if element is found
	return (constantTable.find(constantName) != constantTable.end());
}

////////////////////////////////////
// stmtTable APIs
////////////////////////////////////

bool PKB::setStmt(STMT_NO stmtNo, stmtType type) {
	try {
		stmtTable.emplace(stmtNo, type);
		return true;
	}
	catch (errc) {
		return false;
	}
}

STMT_LIST PKB::getAllStmt() {
	unordered_set<int> stmtNoList;
	for (auto keyValue : stmtTable) {
		stmtNoList.emplace(keyValue.first);
	}
	return stmtNoList;
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
	return stmtUsesByVarTable[varName];
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

	try {
		//get varList from PKB then add variable to varList
		unordered_set<string> varList = getModifiesVarByStmt(stmtNo);
		varList.emplace(varName);
		//add it to varModifiesStmtTable
		varModifiesByStmtTable[stmtNo] = varList;
		return true;
	}
	catch (errc) {
		return false;
	}
}

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

////////////////////////////////////
// varUsesByStmtTable APIs
////////////////////////////////////
bool PKB::setUsesVarByStmt(STMT_NO stmtNo, string varName) {

	try {
		//get varList from PKB then add variable to varList
		unordered_set<string> varList = getUsesVarByStmt(stmtNo);
		varList.emplace(varName);
		//add it to varModifiesStmtTable
		varUsesByStmtTable[stmtNo] = varList;
		return true;
	}
	catch (errc) {
		return false;
	}
}

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

bool PKB::isModifiesStmtVar(STMT_NO stmtNo, string varName){
	unordered_set<string> varList = getModifiesVarByStmt(stmtNo);
	for (auto keyValue : varList) {
		if (keyValue._Equal(varName)) {
			return true;
		}
	}
	return false;
}

bool PKB::isUsesStmtVar(STMT_NO stmtNo, string varName) {
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

STMT_LIST PKB::getAllAssignStmt() {
	unordered_set<int> stmtList;
	stmtType printStmt = Assign;
	for (auto keyValue : stmtTable) {
		if (keyValue.second == printStmt) {
			stmtList.emplace(keyValue.first);

		}
	}
	return stmtList;
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
	return whileTable; 
};


bool PKB::setWhileStmt(STMT_NO stmtNo) {
	try {
		whileTable.insert(stmtNo);
		return true;
	}
	catch (errc) {
		return false;
	}
};

////////////////////////////////////
// ifTable APIs
////////////////////////////////////

STMT_LIST PKB::getAllIfStmt() {
	return ifTable;
};


bool PKB::setIfStmt(STMT_NO stmtNo) {
	try {
		ifTable.insert(stmtNo);
		return true;
	}
	catch (errc) {
		return false;
	}
};

////////////////////////////////////
// printTable APIs
////////////////////////////////////

STMT_LIST PKB::getAllPrintStmt() {
	unordered_set<int> stmtList;
	stmtType printStmt = Print;
	for (auto keyValue : stmtTable) {
		if (keyValue.second == printStmt) {
			stmtList.emplace(keyValue.first);

		}
	}
	return stmtList;
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
	unordered_set<int> stmtList;
	stmtType readStmt = Read;
	for (auto keyValue : stmtTable) {
		if (keyValue.second == readStmt) {
			stmtList.emplace(keyValue.first);

		}
	}
	return stmtList;
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
	return procedureTable;
};


bool PKB::setProc(string procName) {
	try {
		procedureTable.insert(procName);
		return true;
	}
	catch (errc) {
		return false;
	}
};


////////////////////////////////////
// CallTable APIs
////////////////////////////////////

STMT_LIST PKB::getAllCallStmt() {
	unordered_set<int> stmtList;
	stmtType callStmt = Call;
	for (auto keyValue : stmtTable) {
		if (keyValue.second == callStmt) {
			stmtList.emplace(keyValue.first);
		}
	}
	return stmtList;
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

	
	
	
