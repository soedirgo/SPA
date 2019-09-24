#include <string>
#include <utility>
#include <unordered_map>
#include "Query.h"
#include "Clause.h"
using namespace std;

Query::Query(unordered_map<string, string> decl,
	string syn,
	vector<pair<string, pair<string, string>>> suchcl, vector<pair<string, pair<string, string>>> patterncl)
	: declarations(decl),
	selectSynonym(syn),
	clauses(suchcl),
	patternclauses(patterncl) {}

unordered_map<string, string> Query::getDeclarations() const {
	return this->declarations;
}

string Query::getSelectSynonym() const {
	return this->selectSynonym;
}

vector<pair<string, pair<string, string>>> Query::getClauses() const {
	return this->clauses;
}

vector<pair<string, pair<string, string>>> Query::getPatternClauses() const {
	return this->patternclauses;
}

bool Query::operator== (const Query& other) const {
    return getDeclarations() == other.getDeclarations()
        && getSelectSynonym() == other.getSelectSynonym()
        && getClauses() == other.getClauses()
        && getPatternClauses() == other.getPatternClauses();
}