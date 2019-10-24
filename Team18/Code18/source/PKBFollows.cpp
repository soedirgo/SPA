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

TABLE PKBFollows::getFollowsTable() {
	return followsTable;
}

bool PKBFollows::isFollowsAnyAny() {
	return !followsTable.empty();
}
bool PKBFollows::isFollowsAnyIdent(STMT_NO follows) {
	for (auto vectorIter : followsTable) {
		if (vectorIter.back() == follows) {
			return true;
		}
	}
	return false;
}
bool PKBFollows::isFollowsIdentAny(STMT_NO followedBy) {
	for (auto vectorIter : followsTable) {
		if (vectorIter.front() == followedBy) {
			return true;
		}
	}
	return false;
}
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

bool PKBFollows::isFollowsTAnyAny() {
	return !followsTTable.empty();
}
bool PKBFollows::isFollowsTAnyIdent(STMT_NO follows) {
	for (auto vectorIter : followsTTable) {
		if (vectorIter.back() == follows) {
			return true;
		}
	}
	return false;
}
bool PKBFollows::isFollowsTIdentAny(STMT_NO followedBy) {
	for (auto vectorIter : followsTTable) {
		if (vectorIter.front() == followedBy) {
			return true;
		}
	}
	return false;
}
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

//NEW EVALUATION API
TABLE PKBFollows::getFollowsAnyEnt(STMT_TYPE type) {
	TABLE resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getStmts();
	}
	else {
		list = PKBStmt::getStmtsByType(type);
	}
	for (auto iter : list) {
		s = iter.front();
		for (auto vectorIter : followsTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.back() == s) {
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBFollows::getFollowsEntAny(STMT_TYPE type) {
	TABLE resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getStmts();
	}
	else {
		list = PKBStmt::getStmtsByType(type);
	}
	for (auto iter : list) {
		s = iter.front();
		for (auto vectorIter : followsTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == s) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBFollows::getFollowsIdentEnt(STMT_NO stmtNo, STMT_TYPE type) {
	TABLE resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getStmts();
	}
	else {
		list = PKBStmt::getStmtsByType(type);
	}
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
	return resultTable;
}

TABLE PKBFollows::getFollowsEntIdent(STMT_TYPE type, STMT_NO stmtNo) {
	TABLE resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getStmts();
	}
	else {
		list = PKBStmt::getStmtsByType(type);
	}
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
	return resultTable;
}

TABLE PKBFollows::getFollowsEntEnt(STMT_TYPE type1, STMT_TYPE type2) {
	TABLE resultTable;
	if ((type1 == "stmt" && type2 == "stmt") || (type1 == "prog_line" && type2 == "prog_line")
		|| (type1 == "prog_line" && type2 == "stmt") || (type1 == "stmt" && type2 == "prog_line")) {
		return followsTable;
	}
	STMT_LIST list1, list2;
	if (type1 == "stmt" || type1 == "prog_line") {
		list1 = PKBStmt::getStmts();
	}
	else {
		list1 = PKBStmt::getStmtsByType(type1);
	}
	if (type2 == "stmt" || type2 == "prog_line") {
		list2 = PKBStmt::getStmts();
	}
	else {
		list2 = PKBStmt::getStmtsByType(type2);
	}

	STMT_NO s1;
	STMT_NO s2;
	for (auto iter1 : list1) {
		s1 = iter1.front();
		for (auto iter2 : list2) {
			s2 = iter2.front();
			for (auto vectorIter : followsTable) {
				vector<string> tuple = vector<string>();
				if (vectorIter.front() == s1 && vectorIter.back() == s2) {
					tuple.push_back(vectorIter.front());
					tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}
	}

	return resultTable;
}

TABLE PKBFollows::getFollowsTAnyEnt(STMT_TYPE type) {
	TABLE resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getStmts();
	}
	else {
		list = PKBStmt::getStmtsByType(type);
	}
	for (auto iter : list) {
		s = iter.front();
		for (auto vectorIter : followsTTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.back() == s) {
				tuple.push_back(vectorIter.back());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBFollows::getFollowsTEntAny(STMT_TYPE type) {
	TABLE resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getStmts();
	}
	else {
		list = PKBStmt::getStmtsByType(type);
	}
	for (auto iter : list) {
		s = iter.front();
		for (auto vectorIter : followsTTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == s) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBFollows::getFollowsTIdentEnt(STMT_NO stmtNo, STMT_TYPE type) {
	TABLE resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getStmts();
	}
	else {
		list = PKBStmt::getStmtsByType(type);
	}
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
	return resultTable;
}

TABLE PKBFollows::getFollowsTEntIdent(STMT_TYPE type, STMT_NO stmtNo) {
	TABLE resultTable;
	STMT_LIST list;
	STMT_NO s;
	if (type == "stmt" || type == "prog_line") {
		list = PKBStmt::getStmts();
	}
	else {
		list = PKBStmt::getStmtsByType(type);
	}
	for (auto iter : list) {
		s = iter.front();
		for (auto vectorIter : followsTTable) {
			vector<string> tuple = vector<string>();
			if (vectorIter.front() == s && vectorIter.back() == stmtNo) {
				tuple.push_back(vectorIter.front());
				resultTable.emplace(tuple);
			}
		}
	}
	return resultTable;
}

TABLE PKBFollows::getFollowsTEntEnt(STMT_TYPE type1, STMT_TYPE type2) {
	TABLE resultTable;
	if ((type1 == "stmt" && type2 == "stmt") || (type1 == "prog_line" && type2 == "prog_line")
		|| (type1 == "prog_line" && type2 == "stmt") || (type1 == "stmt" && type2 == "prog_line")) {
		return followsTTable;
	}
	STMT_LIST list1, list2;
	if (type1 == "stmt" || type1 == "prog_line") {
		list1 = PKBStmt::getStmts();
	}
	else {
		list1 = PKBStmt::getStmtsByType(type1);
	}
	if (type2 == "stmt" || type2 == "prog_line") {
		list2 = PKBStmt::getStmts();
	}
	else {
		list2 = PKBStmt::getStmtsByType(type2);
	}

	STMT_NO s1;
	STMT_NO s2;
	for (auto iter1 : list1) {
		s1 = iter1.front();
		for (auto iter2 : list2) {
			s2 = iter2.front();
			for (auto vectorIter : followsTTable) {
				vector<string> tuple = vector<string>();
				if (vectorIter.front() == s1 && vectorIter.back() == s2) {
					tuple.push_back(vectorIter.front());
					tuple.push_back(vectorIter.back());
					resultTable.emplace(tuple);
				}
			}
		}
	}

	return resultTable;
}



bool PKBFollows::clear() {
	followsTable.clear();
	followsTTable.clear();
	return true;
}