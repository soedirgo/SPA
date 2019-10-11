#include "PKBWhile.h"

using namespace std;
TABLE PKBWhile::whileUsesTable;

bool PKBWhile::setWhileUses(STMT_NO stmtNo, VAR_NAME varName) {
	vector<string> tuple = vector<string>();
	tuple.push_back(stmtNo);
	tuple.push_back(varName);
	whileUsesTable.emplace(tuple);
	return true;
}

bool PKBWhile::isWhileUsesRelationship(STMT_NO stmtNo, VAR_NAME varName) {

	for (auto vectorIter : whileUsesTable) {
		if (vectorIter.front() == stmtNo) {
			if (vectorIter.back() == varName) {
				return true;
			}
		}
	}
	return false;
}

bool PKBWhile::clear() {
	whileUsesTable.clear();
	return true;
}