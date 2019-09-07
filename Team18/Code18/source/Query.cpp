#include <string>
#include <utility>
#include "Query.h"
#include "Clause.h"
using namespace std;

Query::Query(unordered_map<string, string> declerationVariables, vector<string> selectVars,
	vector<pair<string, pair<string, string>>> suchThat){}

unordered_map<string, string> Query::getDeclarations() {
    return this->declarationVariables;
}

vector<pair<string, pair<string, string>>> Query::getSuchThatClauses() {
    return this->suchThat;
}
