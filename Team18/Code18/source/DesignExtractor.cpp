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
			tempChildList = PKBParent::getChildrenStmtList(child);
			recurseParent(parent, tempChildList);
			/*
			for (auto tempChild : tempChildList = PKBParent::getChildrenStmtList(child)) {
				PKBParent::setParentStar(parent, tempChild);
			}
			*/
		}
	}
}

void DesignExtractor::extractFollowStar()
{
	unordered_set<int> followedByList = PKBFollow::getAllFollowedBy();
	unordered_set<int> followList;
	unordered_set<int> tempfollowedByList;
	bool statusCheck;
	for (auto followedBy : followedByList) {
		int follow = PKBFollow::getFollowStmt(followedBy);
		PKBFollow::setFollowStar(followedBy, follow);
		int tempFollow = PKBFollow::getFollowStmt(follow);
		recurseFollow(followedBy, tempFollow);
	}
}

void DesignExtractor::recurseFollow(int followedBy, int tempFollow) {
	if (!PKBFollow::isFollowExist(tempFollow)) {
		return;
	}
	PKBFollow::setFollowStar(followedBy, tempFollow);
	tempFollow = PKBFollow::getFollowStmt(tempFollow);
	recurseFollow(followedBy, tempFollow);
}


void DesignExtractor::recurseParent(int parent, unordered_set<int> tempChildList ) {
	if (tempChildList.empty()) {
		return;
	}
	for (auto tempChild : tempChildList) {
		PKBParent::setParentStar(parent, tempChild);
		unordered_set<int> tempChildList = PKBParent::getChildrenStmtList(tempChild);
		recurseParent(parent, tempChildList);
	}
}



