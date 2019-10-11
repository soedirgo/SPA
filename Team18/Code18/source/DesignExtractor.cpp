#include "DesignExtractor.h"
#include "PKB.h"
#include "PKBParent.h"
#include "PKBFollows.h"
#include "PKBCall.h"
#include "PKBNext.h"
#include "PKBStmt.h"

using namespace std;

void DesignExtractor::extractDesign()
{
	extractFollowsStar();
	extractParentStar();
	extractCallStar();
	extractNextStar();
}

void DesignExtractor::extractNextStar()
{
	TABLE nextTable = PKBNext::getNextTable();
	STMT_LIST whileList = PKBStmt::getAllStmtByType("WHILE");
	for (auto vectorIter : nextTable) {
		string n1 = vectorIter.front();
		string n2 = vectorIter.back();
		PKBNext::setNextStar(n1, n2);
		if (stoi(n2) > stoi(n1)) {
			recurseNext(n1, n2, whileList);
		}
	}
}

void DesignExtractor::extractParentStar()
{
	TABLE parentTable = PKBParent::getParentTable();
	for (auto vectorIter : parentTable) {
		string followedBy = vectorIter.front();
		string follows = vectorIter.back();
		PKBParent::setParentStar(followedBy, follows);
		recurseParent(followedBy, follows);
	}
}

void DesignExtractor::extractFollowsStar()
{
	TABLE followsTable = PKBFollows::getFollowsTable();
	for (auto vectorIter : followsTable) {
		string followedBy = vectorIter.front();
		string follows = vectorIter.back();
		PKBFollows::setFollowsStar(followedBy, follows);
		recurseFollows(followedBy, follows);
	}
}

void DesignExtractor::extractCallStar()
{
	TABLE callProcTable = PKBCall::getCallProcTable();
	for (auto vectorIter : callProcTable) {
		PROC_NAME caller = vectorIter.front();
		PROC_NAME callee = vectorIter.back();
		PKBCall::setCallTProc(caller, callee);
		recurseCall(caller, callee);
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
	PKBFollows::setFollowsStar(followedBy, newFollows);
	recurseFollows(followedBy, newFollows);
}

void DesignExtractor::recurseParent(STMT_NO parent, STMT_NO child) {
	PROC_LIST childList = PKBParent::getChild(child);
	if (childList.size() == 0) {
		return;
	}
	for (auto vectorIter : childList) {
		PROC_NAME newChild = vectorIter.back();
		PKBParent::setParentStar(parent, newChild);
		recurseParent(parent, newChild);
	}
}

void DesignExtractor::recurseNext(PROG_LINE nextByLine, PROG_LINE nextLine, STMT_LIST whileList) {
	LINE_LIST lineList = PKBNext::getNext(nextLine);
	if (lineList.size() == 0 ) {
		return;
	}
	
	for (auto vectorIter : lineList) {
		PROG_LINE newNextLine = vectorIter.back();
		if (PKBNext::isNextStarRelationship(nextByLine, newNextLine)) {
			STMT_NO follows = PKBFollows::getFollowsStmt(nextByLine);
			if (follows == "") {
				return;
			}
			else {
				recurseNext(nextByLine, follows, whileList);
			}
			/*
			for (auto vectorIter2 : whileList) {
				if (vectorIter2.front() == nextByLine) {
					return;
				}
			}
			*/
			return;
		}
		if (stoi(nextByLine) >= stoi(newNextLine)) {
			return;
		}
		PKBNext::setNextStar(nextByLine, newNextLine);
		recurseNext(nextByLine, newNextLine, whileList);
		
	}
}