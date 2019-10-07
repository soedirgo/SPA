#include "PKBUses.h"

using namespace std;
unordered_set<vector<string>, VectorHash> PKBUses::usesStmtTable;
unordered_set<vector<string>, VectorHash> PKBUses::usesProcTable;

bool PKBUses::setUsesStmt(STMT_NO stmtNo, VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(to_string(stmtNo));
	tuple.push_back(varName);
	usesStmtTable.emplace(tuple);
	return true;
}

bool PKBUses::setUsesProc(PROC_NAME procName, VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(procName);
	tuple.push_back(varName);
	usesProcTable.emplace(tuple);
	return true;
}


bool PKBUses::isUsesStmtRelationship(STMT_NO stmtNo, VAR_NAME varName) {

	for (auto vectorIter : usesStmtTable) {
		if (vectorIter.front() == to_string(stmtNo)) {
			if (vectorIter.back() == varName) {
				return true;
			}
		}
	}
	return false;
}

STMT_LIST PKBUses::getUsesStmt(VAR_NAME varName) {
	unordered_set<int> stmtList;
	for (auto vectorIter : usesStmtTable) {
		if (vectorIter.back() == varName) {
			stmtList.emplace(stoi(vectorIter.front()));
		}
	}
	return stmtList;
}
//Uses(s1,__)
/*
unordered_set<string> PKBUses::getAllS1() {

	// container for results
	unordered_set<string> result = unordered_set<string>();
	/*
	if (isStmtType(firstArgType)) {
		// stmt set to check
		unordered_set<string> stmts;

		// check through the arg types
		if (firstArgType == ARG_ASSIGN) {
			stmts = stmtTable->getAssgStmts();
		}
		else if (firstArgType == ARG_WHILE) {
			stmts = stmtTable->getWhileStmts();
		}
		else if (firstArgType == ARG_IF) {
			stmts = stmtTable->getIfStmts();
		}
		else if (firstArgType == ARG_CALL) {
			stmts = stmtTable->getCallStmts();
		}
		else {
			stmts = stmtTable->getAllStmts();
		}

		BOOST_FOREACH(auto s, stmts) {
			if (!s->getUses().empty()) {
				result.insert(lexical_cast<string>(s->getStmtNum()));
			}
		}

		// dealing with set of proc
	}
	else {
		// get all procs
		unordered_set<Procedure*> allProcs = procTable->getAllProcs();

		BOOST_FOREACH(auto p, allProcs) {
			if (!p->getUses().empty()) {
				result.insert(p->getProcName());
			}
		}
	}
	

	return result;
}
*/


bool PKBUses::clear() {
	usesStmtTable.clear();
	return true;
}