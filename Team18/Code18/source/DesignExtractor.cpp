#include "DesignExtractor.h"
#include "PKB.h"
#include "PKBAffects.h"
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_map>

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
	extractAffectsBip();
	extractAffectsBipT();
}

void DesignExtractor::affectsAny() {
	STMT_LIST assignStmtTable1 = PKB::getStmtsByType("assign");
	for (auto stmt1 : assignStmtTable1) {
		STMT_NO stmtNo1 = stmt1.front();
		VAR_NAME varNameModified;
		LIST_OF_VAR_NAME varList1 = PKB::getModifiesSIdentEnt(stmtNo1);
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
	LIST_OF_VAR_NAME varList1 = PKB::getModifiesSIdentEnt(a1);
	for (auto vectorIter4 : varList1) {
		varNameModified = vectorIter4.front();
	}
	traverseAffectsAny(a1, varNameModified);
}

void DesignExtractor::isAnyAffecting(STMT_NO a2) {
	STMT_LIST assignStmtTable = PKB::getStmtsByType("assign");
	for (auto stmt : assignStmtTable) {
		STMT_NO stmtNo = stmt.front();
		if (isAffects(stmtNo, a2)) {
			break;
		}
	}
}

void DesignExtractor::affectsAll() {
	STMT_LIST assignStmtTable1 = PKB::getStmtsByType("assign");
	for (auto stmt1 : assignStmtTable1) {
		STMT_NO stmtNo1 = stmt1.front();
		VAR_NAME varNameModified;
		LIST_OF_VAR_NAME varList1 = PKB::getModifiesSIdentEnt(stmtNo1);
		for (auto vectorIter4 : varList1) {
			varNameModified = vectorIter4.front();
		}
		traverseAffectsAll(stmtNo1, varNameModified);
	}
}

void DesignExtractor::affectedBy(STMT_NO a1) {
	VAR_NAME varNameModified;
	LIST_OF_VAR_NAME varList1 = PKB::getModifiesSIdentEnt(a1);
	for (auto vectorIter4 : varList1) {
		varNameModified = vectorIter4.front();
	}
	traverseAffectsAll(a1, varNameModified);
}

void DesignExtractor::isAffecting(STMT_NO a2) {
	STMT_LIST assignStmtTable = PKB::getStmtsByType("assign");
	for (auto stmt : assignStmtTable) {
		STMT_NO stmtNo = stmt.front();
		isAffects(stmtNo, a2);
	}
}

void DesignExtractor::isAffectsSelf() {
	STMT_LIST assignStmtTable = PKB::getStmtsByType("assign");
	for (auto stmt : assignStmtTable) {
		STMT_NO s = stmt.front();
		isAffects(s, s);
	}
}

bool DesignExtractor::isAffects(STMT_NO a1, STMT_NO a2) {
	if (PKBAffects::isCheckedAffects(a1, a2)) {
		return PKBAffects::isCheckedAffectsIdentIdent(a1, a2);
	}
	bool affectsHold = false;
	bool sameProc = true;
	STMT_LIST assignStmtTable = PKB::getAssigns();
	if (PKB::getProcByStmt(a1) != PKB::getProcByStmt(a2)) {
		sameProc = false;
	}
	if (PKB::getTypeByStmtNo(a1) == "assign" && PKB::getTypeByStmtNo(a2) == "assign" && sameProc) {
		// will only have 1 in varList
		LIST_OF_VAR_NAME varList1 = PKB::getModifiesSIdentEnt(a1);
		VAR_NAME varNameModified;
		VAR_NAME varNameUses;
		for (auto vectorIter4 : varList1) {
			varNameModified = vectorIter4.front();
		}
		LIST_OF_VAR_NAME varList2 = PKB::getUsesSIdentEnt(a2);
		for (auto vectorIter4 : varList2) {
			varNameUses = vectorIter4.front();
			if (varNameModified == varNameUses) {
				affectsHold = true;
			}
		}
		if (!traverseAffects(a1, a2, varNameModified)) {
			affectsHold = false;
		}
	}
	if (affectsHold == true) {
		PKB::setAffects(a1, a2);
		PKBAffects::setCheckedAffects(a1, a2);
		return true;
	}
	PKBAffects::setCheckedAffects(a1, a2);
	return false;
}

void DesignExtractor::affectsTAll() {
	STMT_LIST assignStmtTable1 = PKB::getStmtsByType("assign");
	for (auto stmt1 : assignStmtTable1) {
		STMT_NO stmtNo1 = stmt1.front();
		recurseAffectsTAll(stmtNo1);
	}
}

void DesignExtractor::affectedTBy(STMT_NO a1) {
	recurseAffectsTAll(a1);
}

void DesignExtractor::isAffectingT(STMT_NO a2) {
	STMT_LIST assignStmtTable = PKB::getStmtsByType("assign");
	for (auto stmt : assignStmtTable) {
		STMT_NO stmtNo = stmt.front();
		isAffectsT(stmtNo, a2);
	}
}

void DesignExtractor::affectsTAny() {
	STMT_LIST assignStmtTable1 = PKB::getStmtsByType("assign");
	for (auto stmt1 : assignStmtTable1) {
		STMT_NO stmtNo1 = stmt1.front();
		if (recurseAffectsTAny(stmtNo1)) {
			break;
		}
	}
}

void DesignExtractor::isAnyAffectedTBy(STMT_NO a1) {
	recurseAffectsTAny(a1);
}

void DesignExtractor::isAnyAffectingT(STMT_NO a2) {
	STMT_LIST assignStmtTable = PKB::getStmtsByType("assign");
	for (auto stmt : assignStmtTable) {
		STMT_NO stmtNo = stmt.front();
		if (isAffectsT(stmtNo, a2)) {
			break;
		}
	}
}

void DesignExtractor::isAffectsTSelf() {
	STMT_LIST assignStmtTable = PKB::getStmtsByType("assign");
	for (auto stmt : assignStmtTable) {
		STMT_NO s = stmt.front();
		isAffectsT(s, s);
	}
}

bool DesignExtractor::isAffectsT(STMT_NO a1, STMT_NO a2) {
	if (PKBAffects::isCheckedAffectsT(a1, a2)) {
		return PKBAffects::isCheckedAffectsTIdentIdent(a1, a2);
	}
	bool affectsTHold = false;
	bool sameProc = true;
	STMT_LIST assignStmtTable = PKB::getAssigns();
	if (PKB::getProcByStmt(a1) != PKB::getProcByStmt(a2)) {
		sameProc = false;
	}
	if (PKB::getTypeByStmtNo(a1) == "assign" && PKB::getTypeByStmtNo(a2) == "assign" && sameProc) {
		// will only have 1 in varList
		LIST_OF_VAR_NAME varList1 = PKB::getModifiesSIdentEnt(a1);
		VAR_NAME varNameModified;
		VAR_NAME varNameUses;
		for (auto vectorIter4 : varList1) {
			varNameModified = vectorIter4.front();
		}
		LIST_OF_VAR_NAME varList2 = PKB::getUsesSIdentEnt(a2);
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
		PKB::setAffectsT(a1, a2);
		PKBAffects::setCheckedAffectsT(a1, a2);
		return true;
	}
	PKBAffects::setCheckedAffectsT(a1, a2);
	return false;
}

void DesignExtractor::extractNextT(STMT_LIST nextTList1, STMT_LIST nextTList2)
{
	TABLE nextTable = PKB::getNextEntEnt("stmt", "stmt");
	//Check which stmtList size is smaller and do recursive forward / backward 
	if ((nextTList2.size() <= nextTList1.size() && nextTList2.size() > 0)|| nextTList1.size()==0) {

		for (auto vectorIter1 : nextTList2) {
			for (auto vectorIter2 : nextTable) {
				PROG_LINE next1 = vectorIter2.front();
				PROG_LINE next2 = vectorIter2.back();
				//optimization
				if (vectorIter1.front() == next2) {
					bool nextTValue = PKB::isNextT(next1, next2);
					//optimization
					if (nextTValue == false) {
						PKB::setNextT(next1, next2);
						//Recursive backward
						unordered_set<string> visited;
						visited.insert(next1);
						recurseNextReverse(next1, next2, visited);
					}
				}
			}
		}
	}
	else {
		for (auto vectorIter1 : nextTList1) {
			for (auto vectorIter2 : nextTable) {
				PROG_LINE next1 = vectorIter2.front();
				PROG_LINE next2 = vectorIter2.back();
				//optimization
				if (vectorIter1.front() == next1) {
					bool nextTValue = PKB::isNextT(next1, next2);
					//optimization
					if (nextTValue == false) {
						PKB::setNextT(next1, next2);
						unordered_set<string> visited;
						visited.insert(next2);
						//Recursive forward
						recurseNext(next1, next2, visited);
					}
				}
			}
		}
	}
}

void DesignExtractor::extractNextBip() {
	//Get the call table
	TABLE callProcTable = PKB::getCallsEntEnt();
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
	TABLE callTable = PKB::getCallStmtTable();
	for (auto vectorIter1 : procListWithoutCall) {
		
		PROC_NAME callee = vectorIter1.back();
		PROC_NAME caller = vectorIter1.front();
		//Get start and end stmtNo of the callee
		TABLE procedureStartEnd = PKB::getProcedureStartEnd(callee);

		for (auto vectorIter : callTable) {
			STMT_NO callStmt = vectorIter.front();
			//Check if the callee is being called
			if (callee == vectorIter.back()) {
				TABLE procedureStartEnd = PKB::getProcedureStartEnd(callee);
				//Get the stmtNo next after the call stmt
				TABLE nextCallStmts = PKB::getNextIdentEnt(callStmt,"stmt");

				STMT_NO startStmt, endStmt;
				for (auto vectorIter2 : procedureStartEnd) {
					startStmt = vectorIter2[0];
					endStmt = vectorIter2[1];

					PKB::setNextBip(callStmt, startStmt);
					if (nextCallStmts.size() > 0) {
						for (auto vectorIter3 : nextCallStmts) {
							STMT_NO nextStmt = vectorIter3.front();
							if (!(PKB::getTypeByStmtNo(endStmt) == "call")) {
								PKB::setNextBip(endStmt, nextStmt);
							}
						}
					}
					else {
						//Have no next stmt after the call, have to go to ancestor procedure then
						recurseProcedure(endStmt, callee, callTable);
					}
				}
			}
		}
		recurseNextBip(caller, callTable);
	}
	
	TABLE nextTable = PKB::getNextEntEnt("stmt","stmt");
	bool callStatus = false;
	for (auto vectorIter : nextTable) {
		string n1 = vectorIter.front();
		string n2 = vectorIter.back();
		callStatus = false;
		for (auto vectorIter2 : callTable) {
			if (n1 == vectorIter2.front()) {
				callStatus = true;
			}
		}
		//no call stmt
		if (callStatus == false) {
			PKB::setNextBip(n1, n2);
		}
	}
	
}

void DesignExtractor::recurseProcedure(STMT_NO endStmt, PROC_NAME callee, TABLE callTable) {
	TABLE callerList = PKB::getCallsEntIdent(callee);
	if (callerList.size() == 0) {
		return;
	}
	for (auto callerElem : callerList) {
		PROC_NAME newCaller = callerElem.front();
		for (auto vectorIter : callTable) {
			STMT_NO callStmt = vectorIter.front();
			//Check if the callee is being called
			if (callee == vectorIter.back()) {
				TABLE procedureStartEnd = PKB::getProcedureStartEnd(callee);
				TABLE nextCallValues = PKB::getNextIdentEnt(callStmt,"stmt");
				if (nextCallValues.size() > 0) {

					for (auto vectorIter3 : nextCallValues) {
						STMT_NO nextStmt = vectorIter3.front();
						if (!(PKB::getTypeByStmtNo(endStmt) == "call")) {
							PKB::setNextBip(endStmt, nextStmt);
						}
					}
				}
				else {
					//Have no next stmt after the call, have to go to ancestor procedure then
					recurseProcedure(endStmt, newCaller, callTable);
				}
			}
		}
	}
}

void DesignExtractor::recurseNextBip(PROC_NAME callee, TABLE callTable) {
	TABLE callerList = PKB::getCallsEntIdent(callee);
	if (callerList.size() == 0) {
		return;
	}
	for (auto callerElem : callerList) {
		PROC_NAME newCaller = callerElem.front();
		
		for (auto vectorIter : callTable) {
			STMT_NO callStmt = vectorIter.front();
			//Check if the callee is being called
			if (callee == vectorIter.back()) {
				TABLE procedureStartEnd = PKB::getProcedureStartEnd(callee);
				TABLE nextCallValues = PKB::getNextIdentEnt(callStmt,"stmt");

				if (procedureStartEnd.size() > 0) {
					STMT_NO startStmt, endStmt;
					for (auto vectorIter2 : procedureStartEnd) {
						startStmt = vectorIter2[0];
						endStmt = vectorIter2[1];

						PKB::setNextBip(callStmt, startStmt);
						if (nextCallValues.size() > 0) {
							for (auto vectorIter3 : nextCallValues) {
								STMT_NO nextStmt = vectorIter3.front();
								if (!(PKB::getTypeByStmtNo(endStmt) == "call")) {
									PKB::setNextBip(endStmt, nextStmt);
								}
							}
						}
						else {
							//Have no next stmt after the call, have to go to ancestor procedure then
							recurseProcedure(endStmt, newCaller, callTable);
						}

					}
				}
			}

		}
		recurseNextBip(newCaller, callTable);
	}
}

void DesignExtractor::extractNextBipT()
{
	TABLE nextBipTable = PKB::getNextBipEntEnt("stmt","stmt");
	for (auto vectorIter : nextBipTable) {
		string n1 = vectorIter.front();
		string n2 = vectorIter.back();
		bool nextBipTValue = PKB::isNextBipTIdentIdent(n1, n2);
		//optimization
		if (nextBipTValue == false) {
			PKB::setNextBipT(n1, n2);
			recurseNextBipT(n1, n2);
		}
	}
}

void DesignExtractor::extractParentT()
{
	TABLE parentTable = PKB::getParentEntEnt("stmt","stmt");
	for (auto vectorIter : parentTable) {
		string parent = vectorIter.front();
		string child = vectorIter.back();
		PKB::setParentT(parent, child);
		recurseParent(parent, child);
	}
}

void DesignExtractor::extractFollowsT()
{
	TABLE followsTable = PKB::getFollowsEntEnt("stmt","stmt");
	for (auto vectorIter : followsTable) {
		string followedBy = vectorIter.front();
		string follows = vectorIter.back();
		PKB::setFollowsT(followedBy, follows);
		recurseFollows(followedBy, follows);
	}
}

void DesignExtractor::extractCallsT()
{
	TABLE callStmtTable = PKB::getCallsEntEnt();
	for (auto vectorIter : callStmtTable) {
		PROC_NAME caller = vectorIter.front();
		PROC_NAME callee = vectorIter.back();
		PKB::setCallT(caller, callee);
		recurseCall(caller, callee);
	}
}

void DesignExtractor::extractModifiesP()
{
	TABLE callProcTable = PKB::getCallsEntEnt();
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
		TABLE usesPTable = PKB::getModifiesPIdentEnt(callee);
		for (auto vectorIter : usesPTable) {
			VAR_NAME varName = vectorIter.back();
			PKB::setModifiesP(caller, varName);
		}
		recurseModifies(caller);
	}
}

void DesignExtractor::recurseModifies(PROC_NAME callee) {
	TABLE callerList = PKB::getCallsEntIdent(callee);
	if (callerList.size() == 0) {
		return;
	}
	for (auto vectorIter : callerList) {
		PROC_NAME newCaller = vectorIter.front();
		TABLE varList = PKB::getModifiesPIdentEnt(callee);
		for (auto vectorIter : varList) {
			VAR_NAME varName = vectorIter.back();
			PKB::setModifiesP(newCaller, varName);
		}
		recurseModifies(newCaller);
	}
}

void DesignExtractor::extractUsesP()
{
	
	TABLE callProcTable = PKB::getCallsEntEnt();
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
		TABLE usesPTable = PKB::getUsesPIdentEnt(callee);
		for (auto vectorIter : usesPTable) {
			VAR_NAME varName = vectorIter.back();
			PKB::setUsesP(caller, varName);
		}
		recurseUses(caller);
	}
}

void DesignExtractor::extractUsesS()
{
	TABLE callStmtList = PKB::getCallStmtTable();

	for (auto vectorIter1 : callStmtList) {
		STMT_NO stmtNo = vectorIter1.front();
		PROC_NAME procName = vectorIter1.back();

		TABLE usesPTable = PKB::getUsesPIdentEnt(procName);
		for (auto vectorIter2 : usesPTable) {
			VAR_NAME varName = vectorIter2.back();
			PKB::setUsesS(stmtNo, varName);

			//To populate the if/while statement with the vars uses from the call stmt
			TABLE parentTTable = PKB::getParentTEntEnt("stmt","stmt");
			for (auto vectorIter1 : parentTTable) {
				STMT_NO parent = vectorIter1.front();
				STMT_NO children = vectorIter1.back();
				//Found the parent* and populate all the ancestors
				if (children == stmtNo) {
					PKB::setUsesS(parent, varName);
				}
			}
		}
	}
}

void DesignExtractor::extractModifiesS()
{
	TABLE callStmtList = PKB::getCallStmtTable();

	for (auto vectorIter1 : callStmtList) {
		STMT_NO stmtNo = vectorIter1.front();
		PROC_NAME procName = vectorIter1.back();

		TABLE usesPTable = PKB::getModifiesPIdentEnt(procName);
		for (auto vectorIter2 : usesPTable) {
			VAR_NAME varName = vectorIter2.back();
			PKB::setModifiesS(stmtNo, varName);

			//To populate the if/while statement with the vars modifies from the call stmt
			TABLE parentTTable = PKB::getParentTEntEnt("stmt","stmt");
			for (auto vectorIter1 : parentTTable) {
				STMT_NO parent = vectorIter1.front();
				STMT_NO children = vectorIter1.back();
				//Found the parent* and populate all the ancestors
				if (children == stmtNo) {
					PKB::setModifiesS(parent, varName);
				}
			}
		}
	}
}

void DesignExtractor::recurseUses(PROC_NAME callee) {
	TABLE callerList = PKB::getCallsEntIdent(callee);
	if (callerList.size() == 0) {
		return;
	}
	for (auto vectorIter : callerList) {
		PROC_NAME newCaller = vectorIter.front();
		TABLE varList = PKB::getUsesPIdentEnt(callee);
		for (auto vectorIter : varList) {
			VAR_NAME varName = vectorIter.back();
			PKB::setUsesP(newCaller, varName);
		}
		recurseUses(newCaller);
	}
}


void DesignExtractor::extractAffectsBip()
{
	STMT_LIST assignStmtTable1 = PKB::getStmtsByType("assign");
	for (auto stmt1 : assignStmtTable1) {
		STMT_NO stmtNo1 = stmt1.front();
		VAR_NAME varNameModified;
		LIST_OF_VAR_NAME varList1 = PKB::getModifiesSIdentEnt(stmtNo1);
		for (auto vectorIter4 : varList1) {
			varNameModified = vectorIter4.front();
		}
		traverseAffectsBipAll(stmtNo1, varNameModified);
	}
}

void DesignExtractor::extractAffectsBipT()
{
	STMT_LIST assignStmtTable1 = PKB::getStmtsByType("assign");
	for (auto stmt1 : assignStmtTable1) {
		STMT_NO stmtNo1 = stmt1.front();
		recurseAffectsBipTAll(stmtNo1);
	}
}


void DesignExtractor::recurseCall(PROC_NAME caller, PROC_NAME callee) {
	LIST_OF_PROC_NAME calleeList = PKB::getCallsIdentEnt(callee);
	if (calleeList.size() == 0) {
		return;
	}
	for (auto vectorIter : calleeList) {
		PROC_NAME newCallee = vectorIter.back();
		PKB::setCallT(caller, newCallee);
		recurseCall(caller, newCallee);
	}
}

void DesignExtractor::recurseFollows(STMT_NO followedBy, STMT_NO follows) {
	string newFollows = PKB::getFollowsStmt(follows);
	if (newFollows == "") {
		return;
	}
	PKB::setFollowsT(followedBy, newFollows);
	recurseFollows(followedBy, newFollows);
}

void DesignExtractor::recurseParent(STMT_NO parent, STMT_NO child) {
	LIST_OF_PROC_NAME childList = PKB::getParentIdentEnt(child,"stmt");
	if (childList.size() == 0) {
		return;
	}
	for (auto vectorIter : childList) {
		PROC_NAME newChild = vectorIter.back();
		PKB::setParentT(parent, newChild);
		recurseParent(parent, newChild);
	}
}

void DesignExtractor::recurseNext(PROG_LINE nextByLine, PROG_LINE nextLine, unordered_set<string> visited) {
	LINE_LIST lineList = PKB::getNextIdentEnt(nextLine,"stmt");
	if (lineList.size() == 0) {
		return;
	}

	for (auto vectorIter : lineList) {
		PROG_LINE newNextLine = vectorIter.back();
		bool visitedStatus = false;
		if (visited.find(newNextLine) == visited.end()) {
			visited.insert(newNextLine);
			PKB::setNextT(nextByLine, newNextLine);
			recurseNext(nextByLine, newNextLine, visited);
		}
	}
}

void DesignExtractor::recurseNextReverse(PROG_LINE nextByLine, PROG_LINE nextLine, unordered_set<string> visited) {

	LINE_LIST lineList = PKB::getNextEntIdent("stmt",nextByLine);
	if (lineList.size() == 0) {
		return;
	}

	for (auto vectorIter : lineList) {
		PROG_LINE newNextByLine = vectorIter.back();
		bool visitedStatus = false;
		if (visited.find(newNextByLine) == visited.end()) {
			visited.insert( newNextByLine);
			PKB::setNextT(newNextByLine, nextLine);
			recurseNextReverse(newNextByLine, nextLine, visited);
		}
	}
}

void DesignExtractor::recurseNextBipT(PROG_LINE nextByLine, PROG_LINE nextLine) {
	LINE_LIST lineList = PKB::getNextBipIdentEnt(nextLine,"stmt");
	if (lineList.size() == 0) {
		return;
	}

	for (auto vectorIter : lineList) {
		PROG_LINE newNextLine = vectorIter.back();
		if (!PKB::isNextBipTIdentIdent(nextByLine, newNextLine)) {
			PKB::setNextBipT(nextByLine, newNextLine);
			recurseNextBipT(nextByLine, newNextLine);
		}
	}
}

bool DesignExtractor::traverseAffects(STMT_NO a1, STMT_NO a2, VAR_NAME v) {
	queue<STMT_NO> q;
	unordered_map<STMT_NO, bool> visited;
	TABLE nexts = PKB::getNextIdentEnt(a1, "stmt");
	for (auto item : nexts) {
		for (auto stmt : item) {
			if (stmt == a2) {
				return true;
			}
			if (!PKB::isModifiesSIdentIdent(stmt, v) || PKB::getTypeByStmtNo(stmt) == "while" || PKB::getTypeByStmtNo(stmt) == "if") {
				q.push(stmt);
				visited.insert(make_pair(stmt, true));
				if (PKB::getTypeByStmtNo(stmt) == "assign") {
					VAR_NAME varNameUses;
					bool affects = false;
					LIST_OF_VAR_NAME varList2 = PKB::getUsesSIdentEnt(stmt);
					for (auto vectorIter4 : varList2) {
						varNameUses = vectorIter4.front();
						if (v == varNameUses) {
							affects = true;
						}
					}
					if (affects) {
						PKB::setAffects(a1, stmt);
						PKBAffects::setCheckedAffects(a1, stmt);
					}
				}
			}
			else {
				if (PKB::getTypeByStmtNo(stmt) == "assign") {
					VAR_NAME varNameUses;
					bool affects = false;
					LIST_OF_VAR_NAME varList2 = PKB::getUsesSIdentEnt(stmt);
					for (auto vectorIter4 : varList2) {
						varNameUses = vectorIter4.front();
						if (v == varNameUses) {
							affects = true;
						}
					}
					if (affects) {
						PKB::setAffects(a1, stmt);
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
		TABLE nexts = PKB::getNextIdentEnt(next, "stmt");
		for (auto item : nexts) {
			for (auto stmt : item) {
				if (visited.find(stmt) == visited.end()) {
					if (!PKB::isModifiesSIdentIdent(stmt, v) || PKB::getTypeByStmtNo(stmt) == "while" || PKB::getTypeByStmtNo(stmt) == "if") {
						q.push(stmt);
						visited.insert(make_pair(stmt, true));
						if (PKB::getTypeByStmtNo(stmt) == "assign") {
							VAR_NAME varNameUses;
							bool affects = false;
							LIST_OF_VAR_NAME varList2 = PKB::getUsesSIdentEnt(stmt);
							for (auto vectorIter4 : varList2) {
								varNameUses = vectorIter4.front();
								if (v == varNameUses) {
									affects = true;
								}
							}
							if (affects) {
								PKB::setAffects(a1, stmt);
								PKBAffects::setCheckedAffects(a1, stmt);
							}
						}
					}
					else {
						if (PKB::getTypeByStmtNo(stmt) == "assign") {
							VAR_NAME varNameUses;
							bool affects = false;
							LIST_OF_VAR_NAME varList2 = PKB::getUsesSIdentEnt(stmt);
							for (auto vectorIter4 : varList2) {
								varNameUses = vectorIter4.front();
								if (v == varNameUses) {
									affects = true;
								}
							}
							if (affects) {
								PKB::setAffects(a1, stmt);
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
	unordered_map<STMT_NO, bool> visited;
	TABLE nexts = PKB::getNextIdentEnt(a1, "stmt");
	for (auto item : nexts) {
		for (auto stmt : item) {
			if (!PKB::isModifiesSIdentIdent(stmt, v) || PKB::getTypeByStmtNo(stmt) == "while" || PKB::getTypeByStmtNo(stmt) == "if") {
				q.push(stmt);
				visited.insert(make_pair(stmt, true));
				if (PKB::getTypeByStmtNo(stmt) == "assign") {
					VAR_NAME varNameUses;
					bool affects = false;
					LIST_OF_VAR_NAME varList2 = PKB::getUsesSIdentEnt(stmt);
					for (auto vectorIter4 : varList2) {
						varNameUses = vectorIter4.front();
						if (v == varNameUses) {
							affects = true;
						}
					}
					if (affects) {
						PKB::setAffects(a1, stmt);
						PKBAffects::setCheckedAffects(a1, stmt);
					}
				}
			}
			else {
				if (PKB::getTypeByStmtNo(stmt) == "assign") {
					VAR_NAME varNameUses;
					bool affects = false;
					LIST_OF_VAR_NAME varList2 = PKB::getUsesSIdentEnt(stmt);
					for (auto vectorIter4 : varList2) {
						varNameUses = vectorIter4.front();
						if (v == varNameUses) {
							affects = true;
						}
					}
					if (affects) {
						PKB::setAffects(a1, stmt);
						PKBAffects::setCheckedAffects(a1, stmt);
					}
				}
			}
		}
	}
	while (!q.empty()) {
		STMT_NO next = q.front();
		TABLE nexts = PKB::getNextIdentEnt(next, "stmt");
		for (auto item : nexts) {
			for (auto stmt : item) {
				if (visited.find(stmt) == visited.end()) {
					if (!PKB::isModifiesSIdentIdent(stmt, v) || PKB::getTypeByStmtNo(stmt) == "while" || PKB::getTypeByStmtNo(stmt) == "if") {
						q.push(stmt);
						visited.insert(make_pair(stmt, true));
						if (PKB::getTypeByStmtNo(stmt) == "assign") {
							VAR_NAME varNameUses;
							bool affects = false;
							LIST_OF_VAR_NAME varList2 = PKB::getUsesSIdentEnt(stmt);
							for (auto vectorIter4 : varList2) {
								varNameUses = vectorIter4.front();
								if (v == varNameUses) {
									affects = true;
								}
							}
							if (affects) {
								PKB::setAffects(a1, stmt);
								PKBAffects::setCheckedAffects(a1, stmt);
							}
						}
					}
					else {
						if (PKB::getTypeByStmtNo(stmt) == "assign") {
							VAR_NAME varNameUses;
							bool affects = false;
							LIST_OF_VAR_NAME varList2 = PKB::getUsesSIdentEnt(stmt);
							for (auto vectorIter4 : varList2) {
								varNameUses = vectorIter4.front();
								if (v == varNameUses) {
									affects = true;
								}
							}
							if (affects) {
								PKB::setAffects(a1, stmt);
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

void DesignExtractor::traverseAffectsBipAll(STMT_NO a1, VAR_NAME v) {
	queue<STMT_NO> q;
	unordered_map<STMT_NO, bool> visited;
	TABLE nexts = PKB::getNextBipIdentEnt(a1, "stmt");
	for (auto item : nexts) {
		for (auto stmt : item) {
			if (!PKB::isModifiesSIdentIdent(stmt, v) || PKB::getTypeByStmtNo(stmt) == "while" || PKB::getTypeByStmtNo(stmt) == "if" || PKB::getTypeByStmtNo(stmt) == "call") {
				q.push(stmt);
				visited.insert(make_pair(stmt, true));
				if (PKB::getTypeByStmtNo(stmt) == "assign") {
					VAR_NAME varNameUses;
					bool affects = false;
					LIST_OF_VAR_NAME varList2 = PKB::getUsesSIdentEnt(stmt);
					for (auto vectorIter4 : varList2) {
						varNameUses = vectorIter4.front();
						if (v == varNameUses) {
							affects = true;
						}
					}
					if (affects) {
						PKB::setAffectsBip(a1, stmt);
						PKBAffects::setCheckedAffectsBip(a1, stmt);
					}
				}
			}
			else {
				if (PKB::getTypeByStmtNo(stmt) == "assign") {
					VAR_NAME varNameUses;
					bool affects = false;
					LIST_OF_VAR_NAME varList2 = PKB::getUsesSIdentEnt(stmt);
					for (auto vectorIter4 : varList2) {
						varNameUses = vectorIter4.front();
						if (v == varNameUses) {
							affects = true;
						}
					}
					if (affects) {
						PKB::setAffectsBip(a1, stmt);
						PKBAffects::setCheckedAffectsBip(a1, stmt);
					}
				}
			}
		}
	}
	while (!q.empty()) {
		STMT_NO next = q.front();
		TABLE nexts = PKB::getNextBipIdentEnt(next, "stmt");
		for (auto item : nexts) {
			for (auto stmt : item) {
				if (visited.find(stmt) == visited.end()) {
					if (!PKB::isModifiesSIdentIdent(stmt, v) || PKB::getTypeByStmtNo(stmt) == "while" || PKB::getTypeByStmtNo(stmt) == "if" || PKB::getTypeByStmtNo(stmt) == "call") {
						q.push(stmt);
						visited.insert(make_pair(stmt, true));
						if (PKB::getTypeByStmtNo(stmt) == "assign") {
							VAR_NAME varNameUses;
							bool affects = false;
							LIST_OF_VAR_NAME varList2 = PKB::getUsesSIdentEnt(stmt);
							for (auto vectorIter4 : varList2) {
								varNameUses = vectorIter4.front();
								if (v == varNameUses) {
									affects = true;
								}
							}
							if (affects) {
								PKB::setAffectsBip(a1, stmt);
								PKBAffects::setCheckedAffectsBip(a1, stmt);
							}
						}
					}
					else {
						if (PKB::getTypeByStmtNo(stmt) == "assign") {
							VAR_NAME varNameUses;
							bool affects = false;
							LIST_OF_VAR_NAME varList2 = PKB::getUsesSIdentEnt(stmt);
							for (auto vectorIter4 : varList2) {
								varNameUses = vectorIter4.front();
								if (v == varNameUses) {
									affects = true;
								}
							}
							if (affects) {
								PKB::setAffectsBip(a1, stmt);
								PKBAffects::setCheckedAffectsBip(a1, stmt);
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
	unordered_map<STMT_NO, bool> visited;
	TABLE nexts = PKB::getNextIdentEnt(a1, "stmt");
	for (auto item : nexts) {
		for (auto stmt : item) {
			if (!PKB::isModifiesSIdentIdent(stmt, v) || PKB::getTypeByStmtNo(stmt) == "while" || PKB::getTypeByStmtNo(stmt) == "if") {
				q.push(stmt);
				visited.insert(make_pair(stmt, true));
				if (PKB::getTypeByStmtNo(stmt) == "assign") {
					VAR_NAME varNameUses;
					bool affects = false;
					LIST_OF_VAR_NAME varList2 = PKB::getUsesSIdentEnt(stmt);
					for (auto vectorIter4 : varList2) {
						varNameUses = vectorIter4.front();
						if (v == varNameUses) {
							affects = true;
						}
					}
					if (affects) {
						PKB::setAffects(a1, stmt);
						PKBAffects::setCheckedAffects(a1, stmt);
						return true;
					}
				}
			}
			else {
				if (PKB::getTypeByStmtNo(stmt) == "assign") {
					VAR_NAME varNameUses;
					bool affects = false;
					LIST_OF_VAR_NAME varList2 = PKB::getUsesSIdentEnt(stmt);
					for (auto vectorIter4 : varList2) {
						varNameUses = vectorIter4.front();
						if (v == varNameUses) {
							affects = true;
						}
					}
					if (affects) {
						PKB::setAffects(a1, stmt);
						PKBAffects::setCheckedAffects(a1, stmt);
						return true;
					}
				}
			}
		}
	}
	while (!q.empty()) {
		STMT_NO next = q.front();
		TABLE nexts = PKB::getNextIdentEnt(next, "stmt");
		for (auto item : nexts) {
			for (auto stmt : item) {
				if (visited.find(stmt) == visited.end()) {
					if (!PKB::isModifiesSIdentIdent(stmt, v) || PKB::getTypeByStmtNo(stmt) == "while" || PKB::getTypeByStmtNo(stmt) == "if") {
						q.push(stmt);
						visited.insert(make_pair(stmt, true));
						if (PKB::getTypeByStmtNo(stmt) == "assign") {
							VAR_NAME varNameUses;
							bool affects = false;
							LIST_OF_VAR_NAME varList2 = PKB::getUsesSIdentEnt(stmt);
							for (auto vectorIter4 : varList2) {
								varNameUses = vectorIter4.front();
								if (v == varNameUses) {
									affects = true;
								}
							}
							if (affects) {
								PKB::setAffects(a1, stmt);
								PKBAffects::setCheckedAffects(a1, stmt);
								return true;
							}
						}
					}
					else {
						if (PKB::getTypeByStmtNo(stmt) == "assign") {
							VAR_NAME varNameUses;
							bool affects = false;
							LIST_OF_VAR_NAME varList2 = PKB::getUsesSIdentEnt(stmt);
							for (auto vectorIter4 : varList2) {
								varNameUses = vectorIter4.front();
								if (v == varNameUses) {
									affects = true;
								}
							}
							if (affects) {
								PKB::setAffects(a1, stmt);
								PKBAffects::setCheckedAffects(a1, stmt);
								return true;
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

bool DesignExtractor::recurseAffectsT(STMT_NO a1, STMT_NO a2) {
	TABLE affectsA1 = PKB::getAffectsIdentEnt(a1);
	stack<STMT_NO> frontier;
	unordered_map<STMT_NO, bool> visited;

	for (auto elem : affectsA1) {
		STMT_NO next = elem.back();
		PKB::setAffectsT(a1, next);
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
				PKB::setAffectsT(a1, curr);
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

void DesignExtractor::recurseAffectsTAll(STMT_NO a1) {
	TABLE affectsA1 = PKBAffects::getAffectsIdentEnt(a1);
	stack<STMT_NO> frontier;
	unordered_map<STMT_NO, bool> visited;

	for (auto elem : affectsA1) {
		STMT_NO next = elem.front();
		PKB::setAffectsT(a1, next);
		PKBAffects::setCheckedAffectsT(a1, next);
		frontier.push(next);
		visited.insert(make_pair(next, true));
	}

	while (!frontier.empty()) {
		STMT_NO item = frontier.top();
		frontier.pop();
		TABLE affectsCurr = PKBAffects::getAffectsIdentEnt(item);
		for (auto affect : affectsCurr) {
			STMT_NO curr = affect.front();
			if (visited.find(curr) == visited.end()) {
				PKB::setAffectsT(a1, curr);
				PKBAffects::setCheckedAffectsT(a1, curr);
				frontier.push(curr);
				visited.insert(make_pair(curr, true));
			}
		}
	}
}

void DesignExtractor::recurseAffectsBipTAll(STMT_NO a1) {
	TABLE affectsA1 = PKBAffects::getAffectsBipIdentEnt(a1);
	stack<STMT_NO> frontier;
	unordered_map<STMT_NO, bool> visited;

	for (auto elem : affectsA1) {
		STMT_NO next = elem.front();
		PKB::setAffectsBipT(a1, next);
		PKBAffects::setCheckedAffectsBipT(a1, next);
		frontier.push(next);
		visited.insert(make_pair(next, true));
	}

	while (!frontier.empty()) {
		STMT_NO item = frontier.top();
		frontier.pop();
		TABLE affectsCurr = PKBAffects::getAffectsBipIdentEnt(item);
		for (auto affect : affectsCurr) {
			STMT_NO curr = affect.front();
			if (visited.find(curr) == visited.end()) {
				PKB::setAffectsBipT(a1, curr);
				PKBAffects::setCheckedAffectsBipT(a1, curr);
				frontier.push(curr);
				visited.insert(make_pair(curr, true));
			}
		}
	}
}

bool DesignExtractor::recurseAffectsTAny(STMT_NO a1) {
	VAR_NAME varNameModified;
	LIST_OF_VAR_NAME varList1 = PKB::getModifiesSIdentEnt(a1);
	for (auto vectorIter4 : varList1) {
		varNameModified = vectorIter4.front();
	}
	if (traverseAffectsAny(a1, varNameModified)) {
		TABLE affectsA1 = PKBAffects::getAffectsIdentEnt(a1);
		for (auto elem : affectsA1) {
			STMT_NO next = elem.front();
			PKB::setAffectsT(a1, next);
			PKBAffects::setCheckedAffectsT(a1, next);
			return true;
		}
	}
	return false;
}