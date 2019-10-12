#include <string>
#include <utility>
#include <unordered_map>
#include "Query.h"
#include "Clause.h"
using namespace std;

Query::Query(unordered_map<string, string> decl,
	string syn,
	vector<Clause> cls)
	: declarations(decl),
	selectSynonym(syn),
	clauses(cls) {}

unordered_map<string, string> Query::getDeclarations() const {
	return this->declarations;
}

string Query::getSelectSynonym() const {
	return this->selectSynonym;
}

vector<Clause> Query::getClauses() const {
	return this->clauses;
}

bool Query::operator== (const Query& other) const {
	return this->declarations == other.getDeclarations()
		&& this->selectSynonym == other.getSelectSynonym()
		&& this->clauses == other.getClauses();
}