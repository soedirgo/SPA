#include "PKBPattern.h"

using namespace std;
TABLE PKBPattern::ifUsesTable;
TABLE PKBPattern::whileUsesTable;

bool PKBPattern::setIfUses(STMT_NO stmtNo, VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	tuple.push_back(varName);
	ifUsesTable.emplace(tuple);
	return true;
}

bool PKBPattern::isIfUsesRelationship(STMT_NO stmtNo, VAR_NAME varName) {
	for (auto vectorIter : ifUsesTable) {
		if (vectorIter.front() == stmtNo) {
			if (vectorIter.back() == varName) {
				return true;
			}
		}
	}
	return false;
}

bool PKBPattern::setWhileUses(STMT_NO stmtNo, VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	tuple.push_back(varName);
	whileUsesTable.emplace(tuple);
	return true;
}

bool PKBPattern::isWhileUsesRelationship(STMT_NO stmtNo, VAR_NAME varName) {

	for (auto vectorIter : whileUsesTable) {
		if (vectorIter.front() == stmtNo) {
			if (vectorIter.back() == varName) {
				return true;
			}
		}
	}
	return false;
}

bool PKBPattern::clear() {
	ifUsesTable.clear();
	whileUsesTable.clear();
	return true;
}