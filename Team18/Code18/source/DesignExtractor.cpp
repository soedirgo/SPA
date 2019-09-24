#include "DesignExtractor.h"
#include "PKB.h"
#include "PKBParent.h"
#include "PKBFollow.h"

using namespace std;

void DesignExtractor::extractDesign()
{
	extractFollowStar();
	extractParentStar();
}

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

void DesignExtractor::recurseFollow(int followedBy, int follow) {
	follow = PKBFollow::getFollowStmt(follow);
	if (!PKBFollow::isFollowedByExist(follow)) {
		return;
	}
	PKBFollow::setFollowStar(followedBy, follow);
	recurseFollow(followedBy, follow);
}


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



