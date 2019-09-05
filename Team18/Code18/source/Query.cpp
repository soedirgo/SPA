#include <string>
#include <utility>
#include "Query.h"
#include "Clause.h"
using namespace std;

Query::Query(vector<pair<string, string>> decl, vector<Clause> cl)
    : declarations(decl), clauses(cl) {}

vector<pair<string, string> > Query::getDeclarations() {
    return this->declarations;
}

vector<Clause> Query::getClauses() {
    return this->clauses;
}
