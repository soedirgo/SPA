#include "DesignExtractor.h"
#include "PKB.h"
#include "PKBParent.h"
#include "PKBFollows.h"
#include "PKBCall.h"
#include "PKBNext.h"
#include "PKBStmt.h"
#include "PKBUses.h"
#include "PKBModifies.h"
#include "PKBAffects.h"
#include <algorithm>

using namespace std;

void DesignExtractor::extractDesign()
{
	extractFollowsT();
	extractParentT();
	extractCallsT();
	extractNextT();
	extractModifiesP();
	extractUsesP();
	extractAffects();
	//extractAffectsT();
}

void DesignExtractor::extractAffectsT()
{
	TABLE affectsTable = PKBAffects::getAffectsEntEnt();
	for (auto vectorIter : affectsTable) {
		string n1 = vectorIter.front();
		string n2 = vectorIter.back();
		PKBAffects::setAffectsT(n1, n2);
		recurseAffects(n1, n2);
	}
}

void DesignExtractor::extractNextT()
{
	TABLE nextTable = PKBNext::getNextTable();
	for (auto vectorIter : nextTable) {
		string n1 = vectorIter.front();
		string n2 = vectorIter.back();
		PKBNext::setNextT(n1, n2);
		recurseNext(n1, n2);
	}
}

void DesignExtractor::extractParentT()
{
	TABLE parentTable = PKBParent::getParentTable();
	for (auto vectorIter : parentTable) {
		string parent = vectorIter.front();
		string child = vectorIter.back();
		PKBParent::setParentT(parent, child);
		recurseParent(parent, child);
	}
}

void DesignExtractor::extractFollowsT()
{
	TABLE followsTable = PKBFollows::getFollowsTable();
	for (auto vectorIter : followsTable) {
		string followedBy = vectorIter.front();
		string follows = vectorIter.back();
		PKBFollows::setFollowsT(followedBy, follows);
		recurseFollows(followedBy, follows);
	}
}

void DesignExtractor::extractCallsT()
{
	TABLE callStmtTable = PKBCall::getCallProcTable();
	for (auto vectorIter : callStmtTable) {
		PROC_NAME caller = vectorIter.front();
		PROC_NAME callee = vectorIter.back();
		PKBCall::setCallTProc(caller, callee);
		recurseCall(caller, callee);
	}
}

void DesignExtractor::extractModifiesP()
{
	TABLE callProcTable = PKBCall::getCallProcTable();
	for (auto vectorIter1 : callProcTable) {
		PROC_NAME callee = vectorIter1.back();
		PROC_NAME caller = vectorIter1.front();
		bool isCaller = false;
		for (auto vectorIter2 : callProcTable) {
			//Check if callee is a caller then set flag to true
			if (callee == vectorIter2.front()) {
				isCaller = true;
				break;
			}
		}
		if (isCaller == false) {
			TABLE usesPTable = PKBModifies::getModifiesPIdentEnt(callee);
			for (auto vectorIter : usesPTable) {
				VAR_NAME varName = vectorIter.back();
				PKBModifies::setModifiesP(caller, varName);
			}
			recurseModifies(caller);
		}	
	}
}

void DesignExtractor::recurseModifies(PROC_NAME callee) {
	TABLE callerList = PKBCall::getCallerProc(callee);
	if (callerList.size() == 0) {
		return;
	}
	for (auto vectorIter : callerList) {
		PROC_NAME newCaller = vectorIter.front();
		TABLE varList = PKBModifies::getModifiesPIdentEnt(callee);
		for (auto vectorIter : varList) {
			VAR_NAME varName = vectorIter.back();
			PKBModifies::setModifiesP(newCaller, varName);
		}
		recurseModifies(newCaller);
	}
}

void DesignExtractor::extractUsesP()
{
	TABLE callProcTable = PKBCall::getCallProcTable();
	for (auto vectorIter1 : callProcTable) {
		PROC_NAME callee = vectorIter1.back();
		PROC_NAME caller = vectorIter1.front();
		bool isCaller = false;
		for (auto vectorIter2 : callProcTable) {
			//Check if callee is a caller then set flag to true
			if (callee == vectorIter2.front()) {
				isCaller = true;
				break;
			}
		}
		if (isCaller == false) {
			TABLE usesPTable = PKBUses::getUsesPIdentEnt(callee);
			for (auto vectorIter : usesPTable) {
				VAR_NAME varName = vectorIter.back();
				PKBUses::setUsesP(caller, varName);
			}
			recurseUses(caller);
		}
	}
}


void DesignExtractor::extractAffects()
{
	TABLE assignStmtTable = PKBStmt::getAllStmtByType("assign");
	TABLE callStmtTable = PKBStmt::getAllStmtByType("call");
	TABLE nextTTable = PKBNext::getNextTEntEnt();

	for (auto vectorIter3 : nextTTable) {
		STMT_NO a1 = vectorIter3.front();
		STMT_NO a2 = vectorIter3.back();
		if (PKBStmt::getTypeByStmtNo(a1)=="assign" && PKBStmt::getTypeByStmtNo(a2) == "assign") {
			bool affectsHold = false;
			// will only have 1 in varList
			VAR_LIST varList1 = PKBModifies::getModifiesSIdentEnt(a1);
			VAR_NAME varNameModified;
			for (auto vectorIter4 : varList1) {
				varNameModified = vectorIter4.front();
			}
			VAR_LIST varList2 = PKBUses::getUsesSIdentEnt(a2);
			for (auto vectorIter4 : varList2) {
				VAR_NAME varNameUses = vectorIter4.front();
				//Means Affects Hold but havent check if modifies changed in between
				if (varNameModified == varNameUses) {
					affectsHold = true;
				}
			}
			//Validate if affects Hold and var is not modified in between
			TABLE stmtList = PKBNext::getNextTIdentEnt(a1);
			vector<int> v;
			for (auto vectorIter1 : stmtList) {
				if (stoi(vectorIter1.front()) < stoi(a2)) {
					v.push_back(stoi(vectorIter1.front()));
				}
			}
			sort(v.begin(), v.end());
			int followIterator = 0;
			for (auto i : v) {
				if (i >= followIterator) {
					//for (int i = stoi(a1) + 1; i < stoi(a2); i++) {
					if (PKBStmt::getTypeByStmtNo(to_string(i)) == "while" || PKBStmt::getTypeByStmtNo(to_string(i)) == "if") {
						STMT_NO follows = PKBFollows::getFollowsStmt(to_string(i));
						if (follows != "" && stoi(follows) <= stoi(a2)) {						
							followIterator = stoi(follows);
						}
					}
					else {
						if (i != stoi(a1)) {
							if (PKBStmt::getTypeByStmtNo(to_string(i)) == "call" || PKBStmt::getTypeByStmtNo(to_string(i)) == "assign") {
								VAR_LIST varList3 = PKBModifies::getModifiesSIdentEnt(to_string(i));
								for (auto vectorIter4 : varList3) {
									if (varNameModified == vectorIter4.front()) {
										affectsHold = false;
									}
								}
							}
						}
					}
				}
			}
			if (affectsHold == true) {
				PKBAffects::setAffects(a1, a2);
			}
		}
	}
}

void DesignExtractor::recurseUses(PROC_NAME callee) {
	TABLE callerList = PKBCall::getCallerProc(callee);
	if (callerList.size() == 0) {
		return;
	}
	for (auto vectorIter : callerList) {
		PROC_NAME newCaller = vectorIter.front();
		TABLE varList = PKBUses::getUsesPIdentEnt(callee);
		for (auto vectorIter : varList) {
			VAR_NAME varName = vectorIter.back();
			PKBUses::setUsesP(newCaller, varName);
		}
		recurseUses(newCaller);
	}
}

void DesignExtractor::recurseCall(PROC_NAME caller, PROC_NAME callee) {
	PROC_LIST calleeList = PKBCall::getCalleeProc(callee);
	if (calleeList.size() == 0) {
		return;
	}
	for (auto vectorIter : calleeList) {
		PROC_NAME newCallee = vectorIter.back();
		PKBCall::setCallTProc(caller, newCallee);
		recurseCall(caller, newCallee);
	}
}

void DesignExtractor::recurseFollows(STMT_NO followedBy, STMT_NO follows) {
	string newFollows = PKBFollows::getFollowsStmt(follows);
	if (newFollows == "") {
		return;
	}
	PKBFollows::setFollowsT(followedBy, newFollows);
	recurseFollows(followedBy, newFollows);
}

void DesignExtractor::recurseParent(STMT_NO parent, STMT_NO child) {
	PROC_LIST childList = PKBParent::getChild(child);
	if (childList.size() == 0) {
		return;
	}
	for (auto vectorIter : childList) {
		PROC_NAME newChild = vectorIter.back();
		PKBParent::setParentT(parent, newChild);
		recurseParent(parent, newChild);
	}
}

void DesignExtractor::recurseNext(PROG_LINE nextByLine, PROG_LINE nextLine) {
	LINE_LIST lineList = PKBNext::getNext(nextLine);
	if (lineList.size() == 0 ) {
		return;
	}
	
	for (auto vectorIter : lineList) {
		PROG_LINE newNextLine = vectorIter.back();
		if (PKBNext::isNextTIdentIdent(nextByLine, newNextLine)) {
			//STMT_NO follows = PKBFollows::getFollowsStmt(nextByLine);
			//if (follows == "") {
				return;
			//}
		}
		PKBNext::setNextT(nextByLine, newNextLine);
		recurseNext(nextByLine, newNextLine);
		
	}
}

void DesignExtractor::recurseAffects(STMT_NO a1, STMT_NO a2) {
	STMT_LIST lineList = PKBAffects::getAffectsIdentEnt(a2);
	if (lineList.size() == 0) {
		return;
	}

	for (auto vectorIter : lineList) {
		PROG_LINE newAssignStmt = vectorIter.back();
		if (PKBAffects::isAffectsTIdentIdent(a1, newAssignStmt)) {
			return;
			//if (PKBStmt::getTypeByStmtNo(newAssignStmt) == "while") {
				//STMT_NO follows = PKBFollows::getFollowsStmt(newAssignStmt);
				//if (follows == "") {
					//return;
				//}
			//}
		}
		PKBAffects::setAffectsT(a1, newAssignStmt);
		recurseAffects(a1, newAssignStmt);

	}
}