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
#include "PKBProcedure.h"
#include <algorithm>
#include <queue>
#include <stack>
#include <map>

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
	extractNextBip();
	extractNextBipT();

	TABLE test = PKBNext::getNextBipTable();
	int i = test.size();
	//TABLE test = PKBUses::getUsesPTable();
	//int i = test.size();
	//TABLE test2 = PKBCall::getCallProcTable();
	//int i2 = test2.size();

	//extractAffectsT();
}

void DesignExtractor::affectsAny() {
	STMT_LIST assignStmtTable1 = PKBStmt::getStmtsByType("assign");
	for (auto stmt1 : assignStmtTable1) {
		STMT_NO stmtNo1 = stmt1.front();
		VAR_NAME varNameModified;
		VAR_LIST varList1 = PKBModifies::getModifiesSIdentEnt(stmtNo1);
		for (auto vectorIter4 : varList1) {
			varNameModified = vectorIter4.front();
		}
		if (traverseAffectsAny(stmtNo1, varNameModified)) {
			break;
		}
	}
}
void DesignExtractor::isAnyAffectedBy(STMT_NO a1) {
	VAR_NAME varNameModified;
	VAR_LIST varList1 = PKBModifies::getModifiesSIdentEnt(a1);
	for (auto vectorIter4 : varList1) {
		varNameModified = vectorIter4.front();
	}
	traverseAffectsAny(a1, varNameModified);
}

void DesignExtractor::isAnyAffecting(STMT_NO a2) {
	STMT_LIST assignStmtTable = PKBStmt::getStmtsByType("assign");
	for (auto stmt : assignStmtTable) {
		STMT_NO stmtNo = stmt.front();
		if (isAffects(stmtNo, a2)) {
			break;
		}	
	}
}

void DesignExtractor::affectsAll() {
	STMT_LIST assignStmtTable1 = PKBStmt::getStmtsByType("assign");
	for (auto stmt1 : assignStmtTable1) {
		STMT_NO stmtNo1 = stmt1.front();
		VAR_NAME varNameModified;
		VAR_LIST varList1 = PKBModifies::getModifiesSIdentEnt(stmtNo1);
		for (auto vectorIter4 : varList1) {
			varNameModified = vectorIter4.front();
		}
		traverseAffectsAll(stmtNo1, varNameModified);
	}
}

void DesignExtractor::affectedBy(STMT_NO a1) {
	VAR_NAME varNameModified;
	VAR_LIST varList1 = PKBModifies::getModifiesSIdentEnt(a1);
	for (auto vectorIter4 : varList1) {
		varNameModified = vectorIter4.front();
	}
	traverseAffectsAll(a1, varNameModified);
}

void DesignExtractor::isAffecting(STMT_NO a2) {
	STMT_LIST assignStmtTable = PKBStmt::getStmtsByType("assign");
	for (auto stmt : assignStmtTable) {
		STMT_NO stmtNo = stmt.front();
		isAffects(stmtNo, a2);
	}
}

void DesignExtractor::isAffectsSelf() {
	STMT_LIST assignStmtTable = PKBStmt::getStmtsByType("assign");
	for (auto stmt : assignStmtTable) {
		STMT_NO s = stmt.front();
		isAffects(s, s);
	}
}

bool DesignExtractor::isAffects(STMT_NO a1, STMT_NO a2) {
	if (PKBAffects::isCheckedAffects(a1, a2)) {
		return;
	}
	bool affectsHold = false;
	bool sameProc = true;
	STMT_LIST assignStmtTable = PKB::getAssigns();
	if (PKB::getProcByStmt(a1) != PKB::getProcByStmt(a2)) {
		sameProc = false;
	}
	if (PKBStmt::getTypeByStmtNo(a1) == "assign" && PKBStmt::getTypeByStmtNo(a2) == "assign" && sameProc) {
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
			if (varNameModified == varNameUses) {
				affectsHold = true;
			}
		}
		/*if (!PKB::isNextTIdentIdent(a1, a2)) {
			affectsHold = false;
		}*/
		if (!traverseAffects(a1, a2, varNameModified)) {
			affectsHold = false;
		}
	}
	if (affectsHold == true) {
		PKBAffects::setAffects(a1, a2);
		PKBAffects::setCheckedAffects(a1, a2);
		return true;
	}
	else {
		PKBAffects::setCheckedAffects(a1, a2);
		return false;
	}
}

void DesignExtractor::affectsTAll() {
	STMT_LIST assignStmtTable1 = PKBStmt::getStmtsByType("assign");
	STMT_LIST assignStmtTable2 = PKBStmt::getStmtsByType("assign");
	for (auto stmt1 : assignStmtTable1) {
		STMT_NO stmtNo1 = stmt1.front();
		for (auto stmt2 : assignStmtTable2) {
			STMT_NO stmtNo2 = stmt2.front();
			isAffectsT(stmtNo1, stmtNo2);
		}
	}
}

void DesignExtractor::affectedTBy(STMT_NO a1) {
	STMT_LIST assignStmtTable = PKBStmt::getStmtsByType("assign");
	for (auto stmt : assignStmtTable) {
		STMT_NO stmtNo = stmt.front();
		isAffectsT(a1, stmtNo);
	}
}

void DesignExtractor::isAffectingT(STMT_NO a2) {
	STMT_LIST assignStmtTable = PKBStmt::getStmtsByType("assign");
	for (auto stmt : assignStmtTable) {
		STMT_NO stmtNo = stmt.front();
		isAffectsT(stmtNo, a2);
	}
}

void DesignExtractor::isAffectsTSelf() {
	STMT_LIST assignStmtTable = PKBStmt::getStmtsByType("assign");
	for (auto stmt : assignStmtTable) {
		STMT_NO s = stmt.front();
		isAffectsT(s, s);
	}
}

void DesignExtractor::isAffectsT(STMT_NO a1, STMT_NO a2) {
	if (PKBAffects::isCheckedAffectsT(a1, a2)) {
		return;
	}
	bool affectsTHold = false;
	bool sameProc = true;
	STMT_LIST assignStmtTable = PKB::getAssigns();
	if (PKB::getProcByStmt(a1) != PKB::getProcByStmt(a2)) {
		sameProc = false;
	}
	if (PKBStmt::getTypeByStmtNo(a1) == "assign" && PKBStmt::getTypeByStmtNo(a2) == "assign" && sameProc) {
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
			if (varNameModified == varNameUses) {
				affectsTHold = true;
			}
		}
		TABLE affectsA1 = PKB::getAffectsIdentEnt(a1);
		if (!recurseAffectsT(a1, a2)) {
			affectsTHold = false;
		}
	}
	if (affectsTHold == true) {
		PKBAffects::setAffectsT(a1, a2);
	}
	PKBAffects::setCheckedAffectsT(a1, a2);
}

void DesignExtractor::extractNextT(STMT_LIST nextTList1, STMT_LIST nextTList2)
{
	//Check which stmtList size is smaller and do recursive forward / backward 
	if (nextTList2.size() <= nextTList1.size() && nextTList2.size() > 0) {
		for (auto vectorIter1 : nextTList2) {
			TABLE nextTable = PKBNext::getNextTable();
			for (auto vectorIter2 : nextTable) {
				PROG_LINE next1 = vectorIter2.front();
				PROG_LINE next2 = vectorIter2.back();
				//optimization
				if (vectorIter1.front() == next2) {
					bool nextTValue = PKBNext::isNextT(next1, next2);
					//optimization
					if (nextTValue == false) {
						PKBNext::setNextT(next1, next2);
						//Recursive backward
						vector<string> visted = {};
						visted.push_back(next1);
						recurseNextReverse(next1, next2, visted);
					}
				}
			}
		}
	}
	else {
		for (auto vectorIter1 : nextTList1) {
			TABLE nextTable = PKBNext::getNextTable();
			for (auto vectorIter2 : nextTable) {
				PROG_LINE next1 = vectorIter2.front();
				PROG_LINE next2 = vectorIter2.back();
				//optimization
				if (vectorIter1.front() == next1) {
					bool nextTValue = PKBNext::isNextT(next1, next2);
					//optimization
					if (nextTValue == false) {
						PKBNext::setNextT(next1, next2);
						vector<string> visted = {};
						visted.push_back(next2);
						//Recursive forward
						recurseNext(next1, next2, visted);
					}
				}
			}
		}
		
	}
	/*
	else {
		for (auto vectorIter1 : nextTList1) {
			TABLE nextTable = PKBNext::getNextTable();
			for (auto vectorIter2 : nextTable) {
				PROG_LINE next1 = vectorIter2.front();
				PROG_LINE next2 = vectorIter2.back();
				//optimization
				if (vectorIter1.front() == next1) {
					bool nextTValue = PKBNext::isNextT(next1, next2);
					//optimization
					if (nextTValue == false) {
						PKBNext::setNextT(next1, next2);
						//Recursive forward
						recurseNext(next1, next2);
					}
				}
			}
		}
		for (auto vectorIter1 : nextTList2) {
			TABLE nextTable = PKBNext::getNextTable();
			for (auto vectorIter2 : nextTable) {
				PROG_LINE next1 = vectorIter2.front();
				PROG_LINE next2 = vectorIter2.back();
				//optimization
				if (vectorIter1.front() == next2) {
					bool nextTValue = PKBNext::isNextT(next1, next2);
					//optimization
					if (nextTValue == false) {
						PKBNext::setNextT(next1, next2);
						//Recursive backward
						recurseNextReverse(next1, next2);
					}
				}
			}
		}
	}
	*/
}

void DesignExtractor::extractNextBip() {
	TABLE nextTable = PKBNext::getNextTable();
	TABLE callTable = PKBCall::getCallStmtTable();

	STMT_NO startStmt, endStmt, endAltStmt;
	for (auto vectorIter : nextTable) {
		string n1 = vectorIter.front();
		string n2 = vectorIter.back();
		for (auto vectorIter2 : callTable) {
			if (n2 == vectorIter2.front()) {
				PROC_NAME callee = vectorIter2.back();
				TABLE procedureTable = PKBProcedure::getProcedureStartEnd(callee);

				if (procedureTable.size() > 0) {

					for (auto vectorIter3 : procedureTable) {
						startStmt = vectorIter3[0];
						endStmt = vectorIter3[1];
					}
					PKBNext::setNextBip(n2, startStmt);
					STMT_NO nextStmt;
					TABLE nextValue = PKBNext::getNextIdentEnt(n2, "prog_line");
					for (auto vectorIter3 : nextValue) {
						nextStmt = vectorIter3.front();
						if (!(nextStmt == "")) {
							PKBNext::setNextBip(endStmt, nextStmt);
						}
					}
				}
			}
			//no call stmt
			PKBNext::setNextBip(n1, n2);
		}
	}
}

void DesignExtractor::extractNextBipT()
{
	TABLE nextBipTable = PKBNext::getNextBipTable();
	for (auto vectorIter : nextBipTable) {
		string n1 = vectorIter.front();
		string n2 = vectorIter.back();
		bool nextBipTValue = PKBNext::isNextBipT(n1, n2);
		//optimization
		if (nextBipTValue == false) {
			PKBNext::setNextBipT(n1, n2);
			recurseNextBipT(n1, n2);
		}
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

/*
void DesignExtractor::extractAffects()
{
	extractNextT();
	TABLE assignStmtTable = PKBStmt::getStmtsByType("assign");
	TABLE callStmtTable = PKBStmt::getStmtsByType("call");
	TABLE nextTTable = PKBNext::getNextTTable();

	for (auto vectorIter3 : nextTTable) {
		STMT_NO a1 = vectorIter3.front();
		STMT_NO a2 = vectorIter3.back();
		if (PKBStmt::getTypeByStmtNo(a1) == "assign" && PKBStmt::getTypeByStmtNo(a2) == "assign") {
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
			TABLE stmtList = PKBNext::getNextTIdentEnt(a1, "stmt");
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
*/

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

void DesignExtractor::recurseNext(PROG_LINE nextByLine, PROG_LINE nextLine, vector<string> visited) {
	LINE_LIST lineList = PKBNext::getNext(nextLine);
	if (lineList.size() == 0) {
		return;
	}

	for (auto vectorIter : lineList) {
		PROG_LINE newNextLine = vectorIter.back();
		bool visitedStatus = false;
		for (auto vectorIter2 : visited) {
			if (vectorIter2 == newNextLine) {
				visitedStatus = true;
				break;
			}
		}
		if (visitedStatus == false) {
			visited.push_back(newNextLine);
			PKBNext::setNextT(nextByLine, newNextLine);
			recurseNext(nextByLine, newNextLine, visited);

		}

	}
}

void DesignExtractor::recurseNextReverse(PROG_LINE nextByLine, PROG_LINE nextLine,  vector<string> visited) {
	
	LINE_LIST lineList = PKBNext::getNextBy(nextByLine);
	if (lineList.size() == 0) {
		return;
	}

	for (auto vectorIter : lineList) {
		PROG_LINE newNextByLine = vectorIter.back();
		bool visitedStatus = false;
		for (auto vectorIter2 : visited) {
			if (vectorIter2 == newNextByLine) {
				visitedStatus = true;
				break;
			}
		}
		if (visitedStatus == false) {
			visited.push_back(newNextByLine);
			PKBNext::setNextT(newNextByLine, nextLine);
			recurseNextReverse(newNextByLine, nextLine, visited);
		}
	}
}

void DesignExtractor::recurseNextBipT(PROG_LINE nextByLine, PROG_LINE nextLine) {
	LINE_LIST lineList = PKBNext::getNextBip(nextLine);
	if (lineList.size() == 0) {
		return;
	}

	for (auto vectorIter : lineList) {
		PROG_LINE newNextLine = vectorIter.back();
		if (!PKBNext::isNextBipT(nextByLine, newNextLine)) {
			PKBNext::setNextBipT(nextByLine, newNextLine);
			recurseNextBipT(nextByLine, newNextLine);

		}

	}
}

/*
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
*/

bool DesignExtractor::traverseAffects(STMT_NO a1, STMT_NO a2, VAR_NAME v) {
	queue<STMT_NO> q;
	map<STMT_NO, bool> visited;
	TABLE nexts = PKBNext::getNextIdentEnt(a1, "stmt");
	for (auto item : nexts) {
		for (auto stmt : item) {
			if (stmt == a2) {
				return true;
			}
			if (!PKB::isModifiesSIdentIdent(stmt, v) || PKBStmt::getTypeByStmtNo(stmt) == "while" || PKBStmt::getTypeByStmtNo(stmt) == "if") {
				q.push(stmt);
				visited.insert(make_pair(stmt, true));
				if (PKBStmt::getTypeByStmtNo(stmt) == "assign") {
					VAR_NAME varNameUses;
					bool affects = false;
					VAR_LIST varList2 = PKBUses::getUsesSIdentEnt(stmt);
					for (auto vectorIter4 : varList2) {
						varNameUses = vectorIter4.front();
						if (v == varNameUses) {
							affects = true;
						}
					}
					if (affects) {
						PKBAffects::setAffects(a1, stmt);
						PKBAffects::setCheckedAffects(a1, stmt);
					}
				}
			}
			else {
				if (PKBStmt::getTypeByStmtNo(stmt) == "assign") {
					VAR_NAME varNameUses;
					bool affects = false;
					VAR_LIST varList2 = PKBUses::getUsesSIdentEnt(stmt);
					for (auto vectorIter4 : varList2) {
						varNameUses = vectorIter4.front();
						if (v == varNameUses) {
							affects = true;
						}
					}
					if (affects) {
						PKBAffects::setAffects(a1, stmt);
						PKBAffects::setCheckedAffects(a1, stmt);
					}
				}
			}
		}
	}
	while (!q.empty()) {
		STMT_NO next = q.front();
		if (next == a2) {
			return true;
		}
		TABLE nexts = PKBNext::getNextIdentEnt(next, "stmt");
		for (auto item : nexts) {
			for (auto stmt : item) {
				if (visited.find(stmt) == visited.end()) {
					if (!PKB::isModifiesSIdentIdent(stmt, v) || PKBStmt::getTypeByStmtNo(stmt) == "while" || PKBStmt::getTypeByStmtNo(stmt) == "if") {
						q.push(stmt);
						visited.insert(make_pair(stmt, true));
						if (PKBStmt::getTypeByStmtNo(stmt) == "assign") {
							VAR_NAME varNameUses;
							bool affects = false;
							VAR_LIST varList2 = PKBUses::getUsesSIdentEnt(stmt);
							for (auto vectorIter4 : varList2) {
								varNameUses = vectorIter4.front();
								if (v == varNameUses) {
									affects = true;
								}
							}
							if (affects) {
								PKBAffects::setAffects(a1, stmt);
								PKBAffects::setCheckedAffects(a1, stmt);
							}
						}
					}
					else {
						if (PKBStmt::getTypeByStmtNo(stmt) == "assign") {
							VAR_NAME varNameUses;
							bool affects = false;
							VAR_LIST varList2 = PKBUses::getUsesSIdentEnt(stmt);
							for (auto vectorIter4 : varList2) {
								varNameUses = vectorIter4.front();
								if (v == varNameUses) {
									affects = true;
								}
							}
							if (affects) {
								PKBAffects::setAffects(a1, stmt);
								PKBAffects::setCheckedAffects(a1, stmt);
							}
						}
					}
				}
			}
		}
		q.pop();
	}
	return false;
}

void DesignExtractor::traverseAffectsAll(STMT_NO a1, VAR_NAME v) {
	queue<STMT_NO> q;
	map<STMT_NO, bool> visited;
	TABLE nexts = PKBNext::getNextIdentEnt(a1, "stmt");
	for (auto item : nexts) {
		for (auto stmt : item) {
			if (!PKB::isModifiesSIdentIdent(stmt, v) || PKBStmt::getTypeByStmtNo(stmt) == "while" || PKBStmt::getTypeByStmtNo(stmt) == "if") {
				q.push(stmt);
				visited.insert(make_pair(stmt, true));
				if (PKBStmt::getTypeByStmtNo(stmt) == "assign") {
					VAR_NAME varNameUses;
					bool affects = false;
					VAR_LIST varList2 = PKBUses::getUsesSIdentEnt(stmt);
					for (auto vectorIter4 : varList2) {
						varNameUses = vectorIter4.front();
						if (v == varNameUses) {
							affects = true;
						}
					}
					if (affects) {
						PKBAffects::setAffects(a1, stmt);
						PKBAffects::setCheckedAffects(a1, stmt);
					}
				}
			}
			else {
				if (PKBStmt::getTypeByStmtNo(stmt) == "assign") {
					VAR_NAME varNameUses;
					bool affects = false;
					VAR_LIST varList2 = PKBUses::getUsesSIdentEnt(stmt);
					for (auto vectorIter4 : varList2) {
						varNameUses = vectorIter4.front();
						if (v == varNameUses) {
							affects = true;
						}
					}
					if (affects) {
						PKBAffects::setAffects(a1, stmt);
						PKBAffects::setCheckedAffects(a1, stmt);
					}
				}
			}
		}
	}
	while (!q.empty()) {
		STMT_NO next = q.front();
		TABLE nexts = PKBNext::getNextIdentEnt(next, "stmt");
		for (auto item : nexts) {
			for (auto stmt : item) {
				if (visited.find(stmt) == visited.end()) {
					if (!PKB::isModifiesSIdentIdent(stmt, v) || PKBStmt::getTypeByStmtNo(stmt) == "while" || PKBStmt::getTypeByStmtNo(stmt) == "if") {
						q.push(stmt);
						visited.insert(make_pair(stmt, true));
						if (PKBStmt::getTypeByStmtNo(stmt) == "assign") {
							VAR_NAME varNameUses;
							bool affects = false;
							VAR_LIST varList2 = PKBUses::getUsesSIdentEnt(stmt);
							for (auto vectorIter4 : varList2) {
								varNameUses = vectorIter4.front();
								if (v == varNameUses) {
									affects = true;
								}
							}
							if (affects) {
								PKBAffects::setAffects(a1, stmt);
								PKBAffects::setCheckedAffects(a1, stmt);
							}
						}
					}
					else {
						if (PKBStmt::getTypeByStmtNo(stmt) == "assign") {
							VAR_NAME varNameUses;
							bool affects = false;
							VAR_LIST varList2 = PKBUses::getUsesSIdentEnt(stmt);
							for (auto vectorIter4 : varList2) {
								varNameUses = vectorIter4.front();
								if (v == varNameUses) {
									affects = true;
								}
							}
							if (affects) {
								PKBAffects::setAffects(a1, stmt);
								PKBAffects::setCheckedAffects(a1, stmt);
							}
						}
					}
				}
			}
		}
		q.pop();
	}
}

bool DesignExtractor::traverseAffectsAny(STMT_NO a1, VAR_NAME v) {
	queue<STMT_NO> q;
	map<STMT_NO, bool> visited;
	TABLE nexts = PKBNext::getNextIdentEnt(a1, "stmt");
	for (auto item : nexts) {
		for (auto stmt : item) {
			if (!PKB::isModifiesSIdentIdent(stmt, v) || PKBStmt::getTypeByStmtNo(stmt) == "while" || PKBStmt::getTypeByStmtNo(stmt) == "if") {
				q.push(stmt);
				visited.insert(make_pair(stmt, true));
				if (PKBStmt::getTypeByStmtNo(stmt) == "assign") {
					VAR_NAME varNameUses;
					bool affects = false;
					VAR_LIST varList2 = PKBUses::getUsesSIdentEnt(stmt);
					for (auto vectorIter4 : varList2) {
						varNameUses = vectorIter4.front();
						if (v == varNameUses) {
							affects = true;
						}
					}
					if (affects) {
						PKBAffects::setAffects(a1, stmt);
						PKBAffects::setCheckedAffects(a1, stmt);
						return true;
					}
				}
			}
			else {
				if (PKBStmt::getTypeByStmtNo(stmt) == "assign") {
					VAR_NAME varNameUses;
					bool affects = false;
					VAR_LIST varList2 = PKBUses::getUsesSIdentEnt(stmt);
					for (auto vectorIter4 : varList2) {
						varNameUses = vectorIter4.front();
						if (v == varNameUses) {
							affects = true;
						}
					}
					if (affects) {
						PKBAffects::setAffects(a1, stmt);
						PKBAffects::setCheckedAffects(a1, stmt);
						return true;
					}
				}
			}
		}
		return false;
	}
	while (!q.empty()) {
		STMT_NO next = q.front();
		TABLE nexts = PKBNext::getNextIdentEnt(next, "stmt");
		for (auto item : nexts) {
			for (auto stmt : item) {
				if (visited.find(stmt) == visited.end()) {
					if (!PKB::isModifiesSIdentIdent(stmt, v) || PKBStmt::getTypeByStmtNo(stmt) == "while" || PKBStmt::getTypeByStmtNo(stmt) == "if") {
						q.push(stmt);
						visited.insert(make_pair(stmt, true));
						if (PKBStmt::getTypeByStmtNo(stmt) == "assign") {
							VAR_NAME varNameUses;
							bool affects = false;
							VAR_LIST varList2 = PKBUses::getUsesSIdentEnt(stmt);
							for (auto vectorIter4 : varList2) {
								varNameUses = vectorIter4.front();
								if (v == varNameUses) {
									affects = true;
								}
							}
							if (affects) {
								PKBAffects::setAffects(a1, stmt);
								PKBAffects::setCheckedAffects(a1, stmt);
							}
						}
					}
					else {
						if (PKBStmt::getTypeByStmtNo(stmt) == "assign") {
							VAR_NAME varNameUses;
							bool affects = false;
							VAR_LIST varList2 = PKBUses::getUsesSIdentEnt(stmt);
							for (auto vectorIter4 : varList2) {
								varNameUses = vectorIter4.front();
								if (v == varNameUses) {
									affects = true;
								}
							}
							if (affects) {
								PKBAffects::setAffects(a1, stmt);
								PKBAffects::setCheckedAffects(a1, stmt);
							}
						}
					}
				}
			}
		}
		q.pop();
	}
}

bool DesignExtractor::recurseAffectsT(STMT_NO a1, STMT_NO a2) {
	TABLE affectsA1 = PKB::getAffectsIdentEnt(a1);
	stack<STMT_NO> frontier;
	map<STMT_NO, bool> visited;

	for (auto elem : affectsA1) {
		STMT_NO next = elem.back();
		PKBAffects::setAffectsT(a1, next);
		PKBAffects::setCheckedAffectsT(a1, next);
		if (next == a2) {
			return true;
		}
		frontier.push(next);
		visited.insert(make_pair(next, true));
	}

	while (!frontier.empty()) {
		STMT_NO item = frontier.top();
		frontier.pop();
		TABLE affectsCurr = PKB::getAffectsIdentEnt(item);
		for (auto affect : affectsCurr) {
			STMT_NO curr = affect.back();
			if (visited.find(curr) == visited.end()) {
				PKBAffects::setAffectsT(a1, curr);
				PKBAffects::setCheckedAffectsT(a1, curr);
				if (curr == a2) {
					return true;
				}
				frontier.push(curr);
				visited.insert(make_pair(curr, true));
			}
		}
	}
	return false;
}