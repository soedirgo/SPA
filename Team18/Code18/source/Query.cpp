#include <string>
#include <utility>
#include <unordered_map>
#include "Query.h"
#include "Clause.h"
using namespace std;

Query::Query(unordered_map<string, string> decl,
	string syn,
	vector<pair<string, pair<string, string>>> cl)
	: declarations(decl),
	selectSynonym(syn),
	clauses(cl) {}

unordered_map<string, string> Query::getDeclarations() {
	return this->declarations;
}

string Query::getSelectSynonym() {
	return this->selectSynonym;
}

vector<pair<string, pair<string, string>>> Query::getClauses() {
	return this->clauses;
}
