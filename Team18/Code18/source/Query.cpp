#include <string>
#include <utility>
#include "Query.h"
#include "Clause.h"
using namespace std;

Query::Query(unordered_map<string, string> declerationVariables, string selectVars,
	vector<pair<string, pair<string, string>>> suchThat)
	: declerationVariables(declerationVariables), selectVars(selectVars), suchThat(suchThat) {}

unordered_map<string, string> Query::getDeclarations() {
    return this->declerationVariables;
}

vector<pair<string, pair<string, string>>> Query::getClauses() {
	return this->suchThat;
}