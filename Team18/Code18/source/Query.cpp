#include <string>
#include <utility>
#include <unordered_map>
#include "Query.h"
#include "Clause.h"

using namespace std;
Query::Query(unordered_map<string, string> decl,
             vector<string> syn,
             vector<Clause> cls)
    : declarations(decl)
    , selectSynonyms(syn)
    , clauses(cls) {}

unordered_map<string, string> Query::getDeclarations() const {
    return this->declarations;
}

vector<string> Query::getSelectSynonyms() const {
    return this->selectSynonyms;
}

vector<Clause> Query::getClauses() const {
	return this->clauses;
}

bool Query::operator== (const Query& other) const {
	return this->declarations == other.getDeclarations()
		&& this->selectSynonyms == other.getSelectSynonyms()
		&& this->clauses == other.getClauses();
}
