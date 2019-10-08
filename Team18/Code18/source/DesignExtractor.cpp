#include "DesignExtractor.h"
#include "PKB.h"
#include "PKBParent.h"
#include "PKBFollow.h"
#include "PKBCall.h"
#include "PKBNext.h"

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
	unordered_set<vector<string>, VectorDoubleStringHash> nextTable = PKBNext::getNextTable();
	for (auto vectorIter : nextTable) {
		string n1 = vectorIter.front();
		string n2 = vectorIter.back();
		PKBNext::setNextStar(n1, n2);
		recurseNext(n1, n2);
	}
}

void DesignExtractor::extractParentStar()
{
	unordered_set<vector<string>, VectorDoubleStringHash> parentTable = PKBParent::getParentTable();
	for (auto vectorIter : parentTable) {
		string followedBy = vectorIter.front();
		string follows = vectorIter.back();
		PKBParent::setParentStar(followedBy, follows);
		recurseParent(followedBy, follows);
	}
}

void DesignExtractor::extractFollowsStar()
{
	unordered_set<vector<string>, VectorDoubleStringHash> followsTable = PKBFollows::getFollowsTable();
	for (auto vectorIter : followsTable) {
		string followedBy = vectorIter.front();
		string follows = vectorIter.back();
		PKBFollows::setFollowsStar(followedBy, follows);
		recurseFollows(followedBy, follows);
	}
}

void DesignExtractor::extractCallStar()
{
	unordered_set<vector<string>, VectorDoubleStringHash> callProcTable = PKBCall::getCallProcTable();
	for (auto vectorIter : callProcTable) {
		PROC_NAME caller = vectorIter.front();
		PROC_NAME callee = vectorIter.back();
		PKBCall::setCallStarProc(caller, callee);
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
		PKBCall::setCallStarProc(caller, newCallee);
		recurseCall(caller, newCallee);
	}
}

void DesignExtractor::recurseFollows(STMT_NO followedBy, STMT_NO follows) {
	string newFollows = PKBFollows::getFollows(follows);
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

void DesignExtractor::recurseNext(PROG_LINE n1, PROG_LINE n2) {
	PROC_LIST nextList = PKBNext::getNext(n1);
	if (nextList.size() == 0) {
		return;
	}
	for (auto vectorIter : nextList) {
		PROC_NAME newNext = vectorIter.back();
		PKBNext::setNextStar(n1, newNext);
		recurseNext(n1, newNext);
	}
}