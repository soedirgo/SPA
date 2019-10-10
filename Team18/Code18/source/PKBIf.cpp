#include "PKBIf.h"

using namespace std;
unordered_set<vector<string>, VectorDoubleStringHash> PKBIf::ifUsesTable;

bool PKBIf::setIfUses(STMT_NO stmtNo, VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	tuple.push_back(varName);
	ifUsesTable.emplace(tuple);
	return true;
}

bool PKBIf::isIfUsesRelationship(STMT_NO stmtNo, VAR_NAME varName) {
	for (auto vectorIter : ifUsesTable) {
		if (vectorIter.front() == stmtNo) {
			if (vectorIter.back() == varName) {
				return true;
			}
		}
	}
	return false;
}

bool PKBIf::clear() {
	ifUsesTable.clear();
	return true;
}