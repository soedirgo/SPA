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
#include "PKBPattern.h"
#include <algorithm>
#include <queue>

using namespace std;

void DesignExtractor::extractDesign()
{
	extractFollowsT();
	extractParentT();
	extractCallsT();
	extractModifiesP();
	extractModifiesS();
	extractUsesP();
	extractUsesS();
	
	//TABLE test = PKBPattern::getPa();
	//int i = test.size();
	//TABLE test = PKBUses::getUsesPTable();
	//int i = test.size();
	//TABLE test2 = PKBCall::getCallProcTable();
	//int i2 = test2.size();
	//TABLE test = PKBNext::getNextTable();
	//int i = test.size();
	//extractAffectsT();
}

void DesignExtractor::affectsAll() {
	STMT_LIST assignStmtTable1 = PKB::getAssigns();
	STMT_LIST assignStmtTable2 = PKB::getAssigns();
	for (auto stmt1 : assignStmtTable1) {
		STMT_NO stmtNo1 = stmt1.front();
		for (auto stmt2 : assignStmtTable2) {
			STMT_NO stmtNo2 = stmt2.front();
			isAffects(stmtNo1, stmtNo2);
		}
	}
}

void DesignExtractor::affectedBy(STMT_NO a1) {
	STMT_LIST assignStmtTable = PKB::getAssigns();
	for (auto stmt : assignStmtTable) {
		STMT_NO stmtNo = stmt.front();
		isAffects(a1, stmtNo);
	}
}

void DesignExtractor::isAffecting(STMT_NO a2) {
	STMT_LIST assignStmtTable = PKB::getAssigns();
	for (auto stmt : assignStmtTable) {
		STMT_NO stmtNo = stmt.front();
		isAffects(stmtNo, a2);
	}
}

void DesignExtractor::isAffectsSelf() {
	STMT_LIST assignStmtTable = PKB::getAssigns();
	for (auto stmt : assignStmtTable) {
		STMT_NO s = stmt.front();
		isAffects(s, s);
	}
}

void DesignExtractor::isAffects(STMT_NO a1, STMT_NO a2) {
	bool affectsHold = false;
	STMT_LIST assignStmtTable = PKB::getAssigns();
	if (PKBStmt::getTypeByStmtNo(a1) == "assign" && PKBStmt::getTypeByStmtNo(a2) == "assign") {
		// will only have 1 in varList
		VAR_LIST varList1 = PKBModifies::getModifiesSIdentEnt(a1);
		VAR_NAME varNameModified;
		VAR_NAME varNameUses;
		for (auto vectorIter4 : varList1) {
			varNameModified = vectorIter4.front();
		}
		VAR_LIST varList2 = PKBUses::getUsesSIdentEnt(a2);
		for (auto vectorIter4 : varList2) {
			varNameUses = vectorIter4.front();
		}
		if (varNameModified == varNameUses) {
			affectsHold = true;
		}
		if (!PKB::isNextTIdentIdent(a1, a2)) {
			affectsHold = false;
		}
		//Validate if affects Hold and var is not modified in between
		TABLE stmtList = PKBNext::getNextIdentEnt(a1, "stmt");
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
	}
	if (affectsHold == true) {
		PKBAffects::setAffects(a1, a2);
	}
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
	STMT_LIST procListWithoutCall;
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
			vector<string> tuple = vector<string>();
			tuple.push_back(caller);
			tuple.push_back(callee);
			procListWithoutCall.emplace(tuple);
		}
	}
	for (auto vectorIter1 : procListWithoutCall) {
		PROC_NAME callee = vectorIter1.back();
		PROC_NAME caller = vectorIter1.front();
		TABLE usesPTable = PKBModifies::getModifiesPIdentEnt(callee);
		for (auto vectorIter : usesPTable) {
			VAR_NAME varName = vectorIter.back();
			PKBModifies::setModifiesP(caller, varName);
		}
		recurseModifies(caller);
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
	STMT_LIST procListWithoutCall;
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
			vector<string> tuple = vector<string>();
			tuple.push_back(caller);
			tuple.push_back(callee);
			procListWithoutCall.emplace(tuple);
		}
	}
	for (auto vectorIter1 : procListWithoutCall) {
		PROC_NAME callee = vectorIter1.back();
		PROC_NAME caller = vectorIter1.front();
		TABLE usesPTable = PKBUses::getUsesPIdentEnt(callee);
		for (auto vectorIter : usesPTable) {
			VAR_NAME varName = vectorIter.back();
			PKBUses::setUsesP(caller, varName);
		}
		recurseUses(caller);
	}
}

void DesignExtractor::extractUsesS()
{
	TABLE callStmtList = PKBCall::getCallStmtTable();

	for (auto vectorIter1 : callStmtList) {
		STMT_NO stmtNo = vectorIter1.front();
		PROC_NAME procName = vectorIter1.back();

		TABLE usesPTable = PKBUses::getUsesPIdentEnt(procName);
		for (auto vectorIter2 : usesPTable) {
			VAR_NAME varName = vectorIter2.back();
			PKBUses::setUsesS(stmtNo, varName);

			//To populate the if/while statement with the vars uses from the call stmt
			TABLE parentTTable = PKBParent::getParentTTable();
			for (auto vectorIter1 : parentTTable) {
				STMT_NO parent = vectorIter1.front();
				STMT_NO children = vectorIter1.back();
				//Found the parent* and populate all the ancestors
				if (children == stmtNo) {
					PKBUses::setUsesS(parent, varName);
				}
			}
		}
	}
}

void DesignExtractor::extractModifiesS()
{
	TABLE callStmtList = PKBCall::getCallStmtTable();

	for (auto vectorIter1 : callStmtList) {
		STMT_NO stmtNo = vectorIter1.front();
		PROC_NAME procName = vectorIter1.back();

		TABLE usesPTable = PKBModifies::getModifiesPIdentEnt(procName);
		for (auto vectorIter2 : usesPTable) {
			VAR_NAME varName = vectorIter2.back();
			PKBModifies::setModifiesS(stmtNo, varName);

			//To populate the if/while statement with the vars modifies from the call stmt
			TABLE parentTTable = PKBParent::getParentTTable();
			for (auto vectorIter1 : parentTTable) {
				STMT_NO parent = vectorIter1.front();
				STMT_NO children = vectorIter1.back();
				//Found the parent* and populate all the ancestors
				if (children == stmtNo) {
					PKBModifies::setModifiesS(parent, varName);
				}
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


void DesignExtractor::extractAffects()
{
	TABLE assignStmtTable = PKBStmt::getStmtsByType("assign");
	TABLE callStmtTable = PKBStmt::getStmtsByType("call");
	TABLE nextTTable = PKBNext::getNextTable();

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
			TABLE stmtList = PKBNext::getNextIdentEnt(a1,"stmt");
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
		if (PKBNext::isNextTInserted(nextByLine, newNextLine)) {
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

bool DesignExtractor::traverseAffects(STMT_NO a1, STMT_NO a2, VAR_NAME v) {
	queue<STMT_NO> q;
	TABLE nexts = PKBNext::getNextIdentEnt(a1, "stmt");
	for (auto item : nexts) {
		for (auto stmt : item) {
			if (stmt == a2) {
				return true;
			}
 			if (!PKB::isModifiesSIdentIdent(stmt, v) && !(PKBStmt::getTypeByStmtNo(stmt) == "if") && !(PKBStmt::getTypeByStmtNo(stmt) == "while")) {
				q.push(stmt);
			}
		}
	}
	while (!q.empty()) {
		TABLE nexts = PKBNext::getNextIdentEnt(a1, "stmt");
		for (auto item : nexts) {
			for (auto stmt : item) {
				if (stmt == a2) {
					return true;
				}
				if (!PKB::isModifiesSIdentIdent(stmt, v) && !(PKBStmt::getTypeByStmtNo(stmt) == "if") && !(PKBStmt::getTypeByStmtNo(stmt) == "while")) {
					q.push(stmt);
				}
			}
		}
	}
	return false;
}