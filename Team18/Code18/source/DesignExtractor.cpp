#include "DesignExtractor.h"
#include "PKB.h"
#include "PKBParent.h"
#include "PKBFollow.h"

using namespace std;

void DesignExtractor::extractDesign()
{
	//extractFollowStar();
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
			for (auto tempChild : tempChildList = PKBParent::getChildrenStmtList(child)) {
				PKBParent::setParentStar(parent, tempChild);
			}
		}
	}
}