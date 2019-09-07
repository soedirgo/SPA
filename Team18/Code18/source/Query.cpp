#include <string>
#include <utility>
#include <unordered_map>
#include "Query.h"
#include "Clause.h"
using namespace std;

Query::Query(unordered_map<string, string> decl, string syn, vector<Clause> cl)
    : declarations(decl), selectSyn(syn), clauses(cl) {}

unordered_map<string, string> Query::getDeclarations() {
    return this->declarations;
}

string Query::getSelectSynonym() {
    return this->selectSyn;
}

vector<Clause> Query::getClauses() {
    return this->clauses;
}
