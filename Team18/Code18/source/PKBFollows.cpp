#include "PKBFollows.h"
#include "PKBStmt.h"

using namespace std;

TABLE PKBFollows::followsTable;
TABLE PKBFollows::followsTTable;

bool PKBFollows::setFollows(STMT_NO followedBy, STMT_NO follows) {
	vector<string> tuple = vector<string>();
	tuple.push_back(followedBy);
	tuple.push_back(follows);
	followsTable.emplace(tuple);
	return true;
}

bool PKBFollows::setFollowsT(STMT_NO followedBy, STMT_NO follows) {
	vector<string> tuple = vector<string>();
	tuple.push_back(followedBy);
	tuple.push_back(follows);
	followsTTable.emplace(tuple);
	return true;
}

STMT_NO PKBFollows::getFollowsStmt(STMT_NO followedBy) {
	for (auto vectorIter : followsTable) {
		if (vectorIter.front() == followedBy) {
			return vectorIter.back();
		}
	}
	return "";
}

//Get boolean for Follows(_,_)
bool PKBFollows::isFollowsAnyAny() {
	return !followsTable.empty();
}
//Get boolean for Follows(_,2)
bool PKBFollows::isFollowsAnyIdent(STMT_NO follows) {
	for (auto vectorIter : followsTable) {
		if (vectorIter.back() == follows) {
			return true;
		}
	}
	return false;
}
//Get boolean for Follows(1,_)
bool PKBFollows::isFollowsIdentAny(STMT_NO followedBy) {
	for (auto vectorIter : followsTable) {
		if (vectorIter.front() == followedBy) {
			return true;
		}
	}
	return false;
}
//Get boolean for Follows(1,2)
bool PKBFollows::isFollowsIdentIdent(STMT_NO followedBy, STMT_NO follows) {
	for (auto vectorIter : followsTable) {
		if (vectorIter.front() == followedBy) {
			if (vectorIter.back() == follows) {
				return true;
			}
		}
	}
	return false;
}
//Get boolean for Follows*(_,_)
bool PKBFollows::isFollowsTAnyAny() {
	return !followsTTable.empty();
}
//Get boolean for Follows*(_,2)
bool PKBFollows::isFollowsTAnyIdent(STMT_NO follows) {
	for (auto vectorIter : followsTTable) {
		if (vectorIter.back() == follows) {
			return true;
		}
	}
	return false;
}
//Get boolean for Follows*(1,_)
bool PKBFollows::isFollowsTIdentAny(STMT_NO followedBy) {
	for (auto vectorIter : followsTTable) {
		if (vectorIter.front() == followedBy) {
			return true;
		}
	}
	return false;
}
//Get boolean for Follows*(1,2)
bool PKBFollows::isFollowsTIdentIdent(STMT_NO followedBy, STMT_NO follows) {
	for (auto vectorIter : followsTTable) {
		if (vectorIter.front() == followedBy) {
			if (vectorIter.back() == follows) {
				return true;
			}
		}
	}
	return false;
}

//Get STMT_LIST for Follows(_,s)
STMT_LIST PKBFollows::getFollowsAnyEnt(STMT_TYPE type) {
	STMT_LIST resultTable, list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		for (auto vectorIter : followsTable) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter.back());
			resultTable.emplace(tuple);
		}
	}
	else {
		list = PKBStmt::getStmtsByType(type);
		for (auto iter : list) {
			s = iter.front();
			for (auto vectorIter : followsTable) {
				if (vectorIter.back() == s) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	
	return resultTable;
}
//Get STMT_LIST for Follows(s,_)
STMT_LIST PKBFollows::getFollowsEntAny(STMT_TYPE type) {
	STMT_LIST resultTable, list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		for (auto vectorIter : followsTable) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter.front());
			resultTable.emplace(tuple);
		}
	}
	else {
		list = PKBStmt::getStmtsByType(type);
		for (auto iter : list) {
			s = iter.front();
			for (auto vectorIter : followsTable) {
				if (vectorIter.front() == s) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.front());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	
	return resultTable;
}
//Get STMT_LIST for Follows(1,s)
STMT_LIST PKBFollows::getFollowsIdentEnt(STMT_NO stmtNo, STMT_TYPE type) {
	STMT_LIST resultTable, list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		for (auto vectorIter : followsTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == stmtNo) {
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	else {
		list = PKBStmt::getStmtsByType(type);
		for (auto iter : list) {
			s = iter.front();
			for (auto vectorIter : followsTable) {
				vector<string> tuple = vector<string>();
				if (vectorIter.front() == stmtNo && vectorIter.back() == s) {
					tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	
	return resultTable;
}
//Get STMT_LIST for Follows(s,2)
STMT_LIST PKBFollows::getFollowsEntIdent(STMT_TYPE type, STMT_NO stmtNo) {
	STMT_LIST resultTable, list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		for (auto vectorIter : followsTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.back() == stmtNo) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	else {
		list = PKBStmt::getStmtsByType(type);
		for (auto iter : list) {
			s = iter.front();
			for (auto vectorIter : followsTable) {
				vector<string> tuple = vector<string>();
				if (vectorIter.front() == s && vectorIter.back() == stmtNo) {
					tuple.push_back(vectorIter.front());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	
	return resultTable;
}
//Get result table for Follows(s1,s2)
TABLE PKBFollows::getFollowsEntEnt(STMT_TYPE type1, STMT_TYPE type2) {
	TABLE resultTable;
	STMT_NO s1;
	STMT_NO s2;
	if (type1 == "prog_line") {
		type1 = "stmt";
	}
	if (type2 == "prog_line") {
		type2 = "stmt";
	}
	if ((type1 == "stmt" && type2 == "stmt")) {
		return followsTable;
	}
	STMT_LIST list1, list2;
	if (type1 == "stmt" && type2 != "stmt") {
		list1 = PKBStmt::getStmts();
		list2 = PKBStmt::getStmtsByType(type2);
		for (auto iter2 : list2) {
			s2 = iter2.front();
			for (auto vectorIter : followsTable) {
				if (vectorIter.back() == s2) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.front());
					tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	else if (type1 != "stmt" && type2 == "stmt") {
		list1 = PKBStmt::getStmtsByType(type1);
		list2 = PKBStmt::getStmts();
		for (auto iter1 : list1) {
			s1 = iter1.front();
			for (auto vectorIter : followsTable) {
				if (vectorIter.front() == s1) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.front());
					tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	else if (type1 != "stmt" && type2 != "stmt") {
		list1 = PKBStmt::getStmtsByType(type1);
		list2 = PKBStmt::getStmtsByType(type2);
		for (auto iter1 : list1) {
			s1 = iter1.front();
			for (auto iter2 : list2) {
				s2 = iter2.front();
				for (auto vectorIter : followsTable) {
					if (vectorIter.front() == s1 && vectorIter.back() == s2) {
						vector<string> tuple = vector<string>();
						tuple.push_back(vectorIter.front());
						tuple.push_back(vectorIter.back());
						resultTable.emplace(tuple);
					}
				}
			}
		}
	}

	return resultTable;
}
//Get STMT_LIST for Follows*(_,s)
STMT_LIST PKBFollows::getFollowsTAnyEnt(STMT_TYPE type) {
	STMT_LIST resultTable, list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		for (auto vectorIter : followsTTable) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter.back());
			resultTable.emplace(tuple);
		}
	}
	else {
		list = PKBStmt::getStmtsByType(type);
		for (auto iter : list) {
			s = iter.front();
			for (auto vectorIter : followsTTable) {
				if (vectorIter.back() == s) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	
	return resultTable;
}
//Get STMT_LIST for Follows*(s,_)
STMT_LIST PKBFollows::getFollowsTEntAny(STMT_TYPE type) {
	STMT_LIST resultTable, list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		for (auto vectorIter : followsTTable) {
			vector<string> tuple = vector<string>();
			tuple.push_back(vectorIter.front());
			resultTable.emplace(tuple);
		}
	}
	else {
		list = PKBStmt::getStmtsByType(type);
		for (auto iter : list) {
			s = iter.front();
			for (auto vectorIter : followsTTable) {
				if (vectorIter.front() == s) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.front());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	
	return resultTable;
}
//Get STMT_LIST for Follows*(1,s)
STMT_LIST PKBFollows::getFollowsTIdentEnt(STMT_NO stmtNo, STMT_TYPE type) {
	STMT_LIST resultTable, list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		for (auto vectorIter : followsTTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == stmtNo) {
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	else {
		list = PKBStmt::getStmtsByType(type);
		for (auto iter : list) {
			s = iter.front();
			for (auto vectorIter : followsTTable) {
				vector<string> tuple = vector<string>();
				if (vectorIter.front() == stmtNo && vectorIter.back() == s) {
					tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	
	return resultTable;
}
//Get STMT_LIST for Follows*(s,2)
STMT_LIST PKBFollows::getFollowsTEntIdent(STMT_TYPE type, STMT_NO stmtNo) {
	STMT_LIST resultTable, list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		for (auto vectorIter : followsTTable) {
			if (vectorIter.back() == stmtNo) {
				vector<string> tuple = vector<string>();
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	else {
		list = PKBStmt::getStmtsByType(type);
		for (auto iter : list) {
			s = iter.front();
			for (auto vectorIter : followsTTable) {
				if (vectorIter.front() == s && vectorIter.back() == stmtNo) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.front());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	
	return resultTable;
}
//Get result table for Follows*(s1,s2)
TABLE PKBFollows::getFollowsTEntEnt(STMT_TYPE type1, STMT_TYPE type2) {
	TABLE resultTable;
	STMT_NO s1;
	STMT_NO s2;
	if (type1 == "prog_line") {
		type1 = "stmt";
	}
	if (type2 == "prog_line") {
		type2 = "stmt";
	}
	if ((type1 == "stmt" && type2 == "stmt")) {
		return followsTTable;
	}
	STMT_LIST list1, list2;
	if (type1 == "stmt" && type2 != "stmt") {
		list1 = PKBStmt::getStmts();
		list2 = PKBStmt::getStmtsByType(type2);
		for (auto iter2 : list2) {
			s2 = iter2.front();
			for (auto vectorIter : followsTTable) {
				if (vectorIter.back() == s2) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.front());
					tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	else if (type1 != "stmt" && type2 == "stmt") {
		list1 = PKBStmt::getStmtsByType(type1);
		list2 = PKBStmt::getStmts();
		for (auto iter1 : list1) {
			s1 = iter1.front();
			for (auto vectorIter : followsTTable) {
				if (vectorIter.front() == s1) {
					vector<string> tuple = vector<string>();
					tuple.push_back(vectorIter.front());
					tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}
	}
	else if (type1 != "stmt" && type2 != "stmt") {
		list1 = PKBStmt::getStmtsByType(type1);
		list2 = PKBStmt::getStmtsByType(type2);
		for (auto iter1 : list1) {
			s1 = iter1.front();
			for (auto iter2 : list2) {
				s2 = iter2.front();
				for (auto vectorIter : followsTTable) {
					if (vectorIter.front() == s1 && vectorIter.back() == s2) {
						vector<string> tuple = vector<string>();
						tuple.push_back(vectorIter.front());
						tuple.push_back(vectorIter.back());
						resultTable.emplace(tuple);
					}
				}
			}
		}
	}
	return resultTable;
}
//clear PKB Follows, Follows* relationship data
void PKBFollows::clear() {
	followsTable.clear();
	followsTTable.clear();
}