#include "DesignExtractor.h"
#include "PKB.h"
#include "PKBParent.h"
#include "PKBFollow.h"
#include "PKBCall.h"

using namespace std;

void DesignExtractor::extractDesign()
{
	extractFollowsStar();
	extractParentStar();
	extractCallStar();
}

/*
void DesignExtractor::extractParentStar()
{
	unordered_set<int> parentList = PKBParent::getAllParent();
	unordered_set<int> childList;
	unordered_set<int> tempChildList;
	for (auto parent : parentList) {
		for (auto child : childList = PKBParent::getChildrenStmtList(parent)) {
			PKBParent::setParentStar(parent,child);		
			recurseParent(parent, child);
		}
	}
}
*/
/*
void DesignExtractor::extractFollowStar()
{
	unordered_set<int> followedByList = PKBFollow::getAllFollowedBy();
	bool statusCheck;
	for (auto followedBy : followedByList) {
		int follow = PKBFollow::getFollowStmt(followedBy);
		PKBFollow::setFollowStar(followedBy, follow);
		recurseFollow(followedBy, follow);
	}
}
*/

void DesignExtractor::extractParentStar()
{
	unordered_set<vector<string>, VectorHash> parentTable = PKBParent::getParentTable();
	for (auto vectorIter : parentTable) {
		string followedBy = vectorIter.front();
		string follows = vectorIter.back();
		PKBParent::setParentStar(stoi(followedBy), stoi(follows));
		recurseParent(stoi(followedBy), stoi(follows));
	}
}


void DesignExtractor::extractFollowsStar()
{
	unordered_set<vector<string>, VectorHash> followsTable = PKBFollows::getFollowsTable();
	for (auto vectorIter : followsTable) {
		string followedBy = vectorIter.front();
		string follows = vectorIter.back();
		PKBFollows::setFollowsStar(stoi(followedBy), stoi(follows));
		recurseFollows(stoi(followedBy), stoi(follows));
	}
}

void DesignExtractor::extractCallStar()
{
	unordered_set<vector<string>, VectorHash> callProcTable = PKBCall::getCallProcTable();
	for (auto vectorIter : callProcTable) {
		PROC_NAME caller = vectorIter.front();
		PROC_NAME callee = vectorIter.back();
		PKBCall::setCallStarProc(caller, callee);
		recurseCall(caller, callee);
	}
}

void DesignExtractor::recurseCall(PROC_NAME caller, PROC_NAME callee) {
	unordered_set<PROC_NAME> calleeList = PKBCall::getCalleeProc(callee);
	if (calleeList.size() == 0) {
		return;
	}
	for (auto newCallee : calleeList) {
		PKBCall::setCallStarProc(caller, newCallee);
		recurseCall(caller, newCallee);
	}
}

void DesignExtractor::recurseFollows(STMT_NO followedBy, STMT_NO follows) {
	string newFollows = PKBFollows::getFollows(follows);
	if (newFollows == "") {
		return;
	}
	PKBFollows::setFollowsStar(followedBy, stoi(newFollows));
	recurseFollows(followedBy, stoi(newFollows));
}

void DesignExtractor::recurseParent(STMT_NO parent, STMT_NO child) {
	unordered_set<string> childList = PKBParent::getChild(child);
	if (childList.size()==0) {
		return;
	}
	for (auto newChild : childList) {
		PKBParent::setParentStar(parent, stoi(newChild));
		recurseParent(parent, stoi(newChild));
	}
}


/*
void DesignExtractor::recurseFollow(int followedBy, int follow) {
	follow = PKBFollow::getFollowStmt(follow);
	if (!PKBFollow::isFollowExist(follow)) {
		return;
	}
	PKBFollow::setFollowStar(followedBy, follow);
	recurseFollow(followedBy, follow);
}
*/

/*
void DesignExtractor::recurseParent(int parent, int child ) {
	unordered_set<int> childList = PKBParent::getChildrenStmtList(child);
	if (childList.empty()) {
		return;
	}
	for (auto tempChild : childList) {
		PKBParent::setParentStar(parent, tempChild);
		recurseParent(parent, tempChild);
	}
}
*/



